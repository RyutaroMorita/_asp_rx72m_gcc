/******************************************************************************
* NORTi Network DHCP client sample                                            *
*                                                                             *
*  Copyright (c) 1998-2006, MiSPO Co., Ltd.                                   *
*  All rights reserved.                                                       *
*                                                                             *
* 24/Jan/2000                                                                 *
* 06/Oct/2002 Removed len variable from dhcp_snd_dat. Now all requests        *
*             transmitted with zero padding bytes.                         YS *
* 15/Apr/2003 Added dhcp_reb_data.                                         YS *
* 16/Dec/2003 Modified for Multichannel                                    AK *
* 25/Feb/2003 Added dhcp_ren_data                                          YS *
* 25/Feb/2003 Added Re transmission for each request                       YS *
* 20/Apr/2005 Modified for multi-channel                                   PK *
* 13/May/2005 Added DHCP Uninitialization code.                            AK *
*             Modified V3 -> V4                                            AK *
* 27/Jan/2006 Address is updated through netif_chg_ipa.                    MK *
* 07/Mar/2006 DHCP_TMOUT changed to 4sec by default.                       MK *
* 13/Mar/2006 vcan_wup to clear any pending requests by dhcp callback      AK *
******************************************************************************/
#include <string.h>
#ifndef NULL
#include <stdio.h>
#endif
#ifdef GAIO
#include <memory.h>
#endif
#ifdef TOPPERS_ASP
#include "pinkie.h"
#ifdef SIMULATOR
#include "./WIN32/nosio.h"
#else
#include "nosio.h"
#endif
#include "./INC/typdefn.h"	//WORD,BYTE
#include "./INC/ws_RS232C.h"
#include "system.h"
#include <netinet/in.h>
#include <netinet/in_itron.h>
#include "cfg.h"
#include "ecom.h"
#include "tinet_cfg.h"
#else	// TOPPERS_ASP
#include "kernel.h"
#include "nonet.h"
#include "nonets.h"
#endif	// TOPPERS_ASP
#include "nondhcp.h"
#ifdef TOPPERS_ASP
//extern SYSTEM_REGISTRY	g_SystemRegistry;
extern SYSTEM_INFORMATION	g_SystemInformation;
#else	// TOPPERS_ASP
#define INCLUDED_FROM_NONET
#include "nonetc.h"
#endif	// TOPPERS_ASP

UB dhcp_ipaddr[4];

#ifndef DHCP_TMO
#define DHCP_TMO           4000/MSEC
#endif

/* DHCP Option */

static const UB opt1[] = { 99, 130, 83, 99, DHCP_OP_MSGTYP, 1, DHCPDISCOVER, 255 };

static const UB opt2[] =
{
  99, 130, 83, 99,
  DHCP_OP_MSGTYP, 1, DHCPREQUEST,
  DHCP_OP_PRMLST, 6, DHCP_OP_SUBNET, DHCP_OP_ROUTER, DHCP_OP_DNS,
  DHCP_OP_ADDRTM, DHCP_OP_RENETM, DHCP_OP_REBITM
};

static const UB opt3[] =
{
  99, 130, 83, 99,
  DHCP_OP_MSGTYP, 1, DHCPREQUEST,
  DHCP_OP_PRMLST, 3, DHCP_OP_ADDRTM, DHCP_OP_RENETM, DHCP_OP_REBITM, 255
};

/* Resource */

#ifdef TOPPERS_ASP
//
#else	// TOPPERS_ASP
static ER dhcp_callback(ID cepid, FN fncd, VP parblk);
static T_UDP_CCEP dhcp_cep = {0, {0, UDP_PORT_BOOTPC}, (FP)dhcp_callback};
#endif	// TOPPERS_ASP
ER dhcp_sta_tsk(ID tskid, ID cepid, ID almid, DHCP_CALLBACK callback);

#ifdef TOPPERS_ASP
TASK dhcp_req_tsk(void);
#else	// TOPPERS_ASP
static TASK dhcp_req_tsk(void);
static const T_CTSK dhcp_res_ctsk = {TA_HLNG, NULL, (FP)dhcp_req_tsk, DHCP_REQTSK_PRI, DHCP_REQTSK_SSZ, NULL, "dhcp_res_ctsk"};
#endif	// TOPPERS_ASP

#ifdef TOPPERS_ASP
void ex_ip_lease(void);
#else	// TOPPERS_ASP
static void ex_ip_lease(void);
static T_CALM dalm = {TA_HLNG, NULL, ex_ip_lease};
#endif	// TOPPERS_ASP

#ifdef LENDIAN
static const UH			order = 0x1234;
#endif
static T_DHCP_CB    dhcp_cb;
static UW           lease_time;
static UW           xid = 1711959080;

#ifdef TOPPERS_ASP

static T_DHCP	m_rcv_pkt;
static T_DHCP	m_snd_pkt;
static T_NIF	m_NIF;
static BOOL	m_fStop;


T_NIF *getnif_from_name(const char *name)  { return NULL; }


T_NIF *getnif_default(void) {
	UB*			pMAC;
	const T_IN4_ADDR*	pIP;
	
	pMAC = (UB*)in4_get_lladdr(0);
	m_NIF.hwaddr[0] = *pMAC++;
	m_NIF.hwaddr[1] = *pMAC++;
	m_NIF.hwaddr[2] = *pMAC++;
	m_NIF.hwaddr[3] = *pMAC++;
	m_NIF.hwaddr[4] = *pMAC++;
	m_NIF.hwaddr[5] = *pMAC;
	pIP = in4_get_ifaddr(0);
	m_NIF.ipaddr[0] = (UB)(*pIP >> 24);
	m_NIF.ipaddr[1] = (UB)(*pIP >> 16);
	m_NIF.ipaddr[2] = (UB)(*pIP >>  8);
	m_NIF.ipaddr[3] = (UB)(*pIP >>  0);
	
	return &m_NIF;
}


#ifdef LENDIAN
/************************************************/
/* 32-bit Host/Network Byte Order Convertsion   */
/************************************************/

UW htonl(UW hl)
{
    UW nl;

    /* Nothing to do for BIG ENDIAN */

    if (*(UB *)(&order) == 0x12)
        return hl;

    /* Reverse the Byte Order */

    nl = hl;
    nl <<= 8; hl >>= 8; nl |= (UB)hl;
    nl <<= 8; hl >>= 8; nl |= (UB)hl;
    nl <<= 8; hl >>= 8; nl |= (UB)hl;
    return nl;
}

#endif
#ifdef LENDIAN
/************************************************/
/* 16-bit Host/Network Byte Order Convertsion   */
/************************************************/

UH htons(UH hs)
{
    UH ns;

    /* Nothing to do for BIG ENDIAN */

    if (*(UB *)(&order) == 0x12)
        return hs;

    /* Reverse the Byte Order */

    ns = hs;
    ns <<= 8; hs >>= 8; ns |= (UB)hs;
    return ns;
}
#endif

/************************************************/
/* 4 bytes Array to Long Integer                */
/************************************************/

UW byte4_to_long(const UB *b)
{
    UW d;

    d  = b[0]; d <<= 8;
    d |= b[1]; d <<= 8;
    d |= b[2]; d <<= 8;
    d |= b[3];

    return d;
}

/************************************************/
/* Long Integer to 4 bytes Array                */
/************************************************/

void long_to_byte4(UB *b, UW d)
{
    b[3] = (UB)d; d >>= 8;
    b[2] = (UB)d; d >>= 8;
    b[1] = (UB)d; d >>= 8;
    b[0] = (UB)d;
}


#endif	// TOPPERS_ASP

#ifdef TOPPERS_ASP
ER dhcp_callback(ID cepid, FN fncd, VP parblk)
#else
static ER dhcp_callback(ID cepid, FN fncd, VP parblk)
#endif
{
#ifdef TOPPERS_ASP
	ER er = *(ER*)parblk;
	if ( er == E_RLWAI )	return E_OK;
#endif
    if(dhcp_cb.btskid != 0) {
        wup_tsk(dhcp_cb.btskid);
    }
    return E_OK;
}


/************************************************/
/* Search DHCP Vender Option                    */
/************************************************/

static UB* search_option(UB tag, UB* opt)
{
    INT i;
    UB n;

    if (opt == NULL)
        return NULL;

    /* Skip Magic cookie */

    opt += 4;

   /* Serach Option */

    for (i = 0; i < 312; i++) {
        if (*opt == 255)
            return NULL;
        if (*opt++ == tag){
            return (++opt);
        }
        n = *opt++;
        opt += n;
    }
    return NULL;
}

/************************************************/
/* Send DHCP Data                               */
/************************************************/
#ifdef TOPPERS_ASP
static T_IPV4EP dstaddr;
#else
static T_IPEP dstaddr;
#endif

static ER dhcp_snd_dat(ID cepid, UB code, UB flg, T_DHCP* snd_pkt, T_DHCP* rcv_pkt, TMO tmout, T_NIF *nif)
{
    ER ercd;
    UB *p;
    
#ifdef TOPPERS_ASP
	// TOPPERSでは通信端点を削除しない！
	if ( m_fStop )
		return E_DLT;	// 送信完了を待つ間にUDP通信端点が削除された（擬似的なエラー）
#endif

    /* Send DHCP */

    memset(snd_pkt, 0, sizeof(T_DHCP));
    snd_pkt->op = BOOT_REQUEST;
    snd_pkt->htype = 1; /* (10MbEthernet) */
    snd_pkt->hlen = 6;
    snd_pkt->xid = htonl(++xid);
    snd_pkt->flag = htons(0x8000);
    memcpy(snd_pkt->chaddr, nif->hwaddr, 6);
    dstaddr.portno = UDP_PORT_BOOTPS;

    switch(code) {
    case DHCPDISCOVER:
        dstaddr.ipaddr = 0xFFFFFFFF; /* Broad Cast */
        memcpy(snd_pkt->option, opt1, sizeof(opt1));
        if (flg == REQ_REBIND)
            snd_pkt->ciaddr = htonl(byte4_to_long(nif->ipaddr));
        break;
    case DHCPREQUEST:
        /* DHCPREQUEST Selecing state */
        if (flg == REQ_SELECT){
            dstaddr.ipaddr = 0xFFFFFFFF; /* Broad Cast */
            memcpy(snd_pkt->option, opt2, sizeof(opt2));
            p = (UB *)(snd_pkt->option + sizeof(opt2));
            *p++ = DHCP_OP_SERVID;
            *p++ = 4;
            memcpy(p, nif->dhcp_ipaddr, 4);
            p += 4;
            *p++ = DHCP_OP_ADRREQ;
            *p++ = 4;
            /* Use the Address got from the server - (Offer) */
            long_to_byte4(p, ntohl(rcv_pkt->yiaddr));
            p += 4;
            *p = 255;
        }
        /* DHCPREQUEST Lease Extension state */
        else {
            snd_pkt->flag = 0;
            snd_pkt->ciaddr = htonl(byte4_to_long(nif->ipaddr));
            if (flg == REQ_REBIND)
                dstaddr.ipaddr = 0xFFFFFFFF; /* Broad Cast */
            else
                dstaddr.ipaddr = byte4_to_long(nif->dhcp_ipaddr);
            memcpy(snd_pkt->option, opt3, sizeof(opt3));
        }
        break;
    }

    ercd = udp_rcv_dat(cepid, &dstaddr, (VP)rcv_pkt, sizeof(T_DHCP), TMO_NBLK);
    if (ercd != E_WBLK)
        return ercd;

    ercd = udp_snd_dat(cepid, &dstaddr, snd_pkt, sizeof(T_DHCP), tmout);
    if (ercd <= 0)
        return ercd;

    return E_OK;
}

/************************************************/
/* Receive DHCP Data                            */
/************************************************/

static ER dhcp_rcv_dat(ID cepid, UB code, UB flg, T_DHCP *pkt, TMO tmout, T_NIF *nif)
{
    ER ercd;
    UB *p;
    T_NIF_ADDR addr;
    UB mask[4], gateway[4], new_ipaddr[4];
#ifdef TOPPERS_ASP
//	T_IN4_ADDR	IP_ADDRESS;
//	T_IN4_ADDR	SUBNET_MASK;
//	T_IN4_ADDR	DEFAULT_GATEWAY;
#endif

#ifdef TOPPERS_ASP
	// TOPPERSでは通信端点を削除しない！
	if ( m_fStop )
		return E_DLT;	// 送信完了を待つ間にUDP通信端点が削除された（擬似的なエラー）
#endif

    /* Wait for Receive */

    ercd = tslp_tsk(tmout);
    if (ercd != E_OK) {
        udp_can_cep(cepid, TFN_UDP_RCV_DAT);
        goto ERR;
    }

#ifdef TOPPERS_ASP
	// TOPPERSでは通信端点を削除しない！
	if ( m_fStop )
		return E_DLT;	// 送信完了を待つ間にUDP通信端点が削除された（擬似的なエラー）
	udp_can_cep(cepid, TFN_UDP_RCV_DAT);
#endif

    /* Receive DHCP Response */

    for (;;){
        p = search_option(DHCP_OP_MSGTYP, pkt->option);
        if (p != NULL){
            if (ntohl(pkt->xid) == xid && pkt->op == BOOT_REPLY && *p == code)
                break;
        }
        ercd = udp_rcv_dat(cepid, &dstaddr, (VP)pkt, sizeof(T_DHCP), tmout);
        if (ercd <= 0)
            goto ERR;
    }

    switch(code) {
    case DHCPOFFER:
        /* Set DHCP Server Address */
        p = search_option(DHCP_OP_SERVID, pkt->option);
        if (p != NULL)
            memcpy(nif->dhcp_ipaddr, p, 4);
        break;
    case DHCPACK:
        /* Set Local IP Address */
        long_to_byte4(new_ipaddr, ntohl(pkt->yiaddr));
        addr.ipaddr = new_ipaddr;
        addr.hwaddr = nif->hwaddr;
        addr.mask = nif->mask;
        addr.gateway = nif->gateway;
        if (flg == REQ_SELECT){
            /* Set Subnetmask */
            p = search_option(DHCP_OP_SUBNET, pkt->option);
            if (p != NULL) {
                memcpy(mask, p, 4);
                addr.mask = mask;
            }
            /* Set Router Address */
            p = search_option(DHCP_OP_ROUTER, pkt->option);
            if (p != NULL) {
                memcpy(gateway, p, 4);
                addr.gateway = gateway;
            }
            /* Set DNS Address */
            p = search_option(DHCP_OP_DNS, pkt->option);
            if (p != NULL)
                memcpy(nif->dns_ipaddr, p, 4);
        }
        /* Change the IP address of nif and TCP/UDP CEP's */
#ifdef TOPPERS_ASP
	g_SystemInformation.ubIPAddress[0] = (UB)addr.ipaddr[0];
	g_SystemInformation.ubIPAddress[1] = (UB)addr.ipaddr[1];
	g_SystemInformation.ubIPAddress[2] = (UB)addr.ipaddr[2];
	g_SystemInformation.ubIPAddress[3] = (UB)addr.ipaddr[3];
	if (flg == REQ_SELECT){
		g_SystemInformation.ubSubnetMask[0] = (UB)addr.mask[0];
		g_SystemInformation.ubSubnetMask[1] = (UB)addr.mask[1];
		g_SystemInformation.ubSubnetMask[2] = (UB)addr.mask[2];
		g_SystemInformation.ubSubnetMask[3] = (UB)addr.mask[3];
		g_SystemInformation.ubGateway[0] = (UB)addr.gateway[0];
		g_SystemInformation.ubGateway[1] = (UB)addr.gateway[1];
		g_SystemInformation.ubGateway[2] = (UB)addr.gateway[2];
		g_SystemInformation.ubGateway[3] = (UB)addr.gateway[3];
	}
	chg_ipa(FALSE);
#else
        netif_chg_ipa(nif, &addr, 2);
#endif
        /* Get Time */
        p = search_option(DHCP_OP_RENETM, pkt->option);
        if (p == NULL) {
            p = search_option(DHCP_OP_REBITM, pkt->option);
            if (p == NULL) {
                p = search_option(DHCP_OP_ADDRTM, pkt->option);
                if (p == NULL){
                    ercd = E_OBJ;
                    goto ERR;
                }
            }
        }
        lease_time = byte4_to_long(p);
        break;
    }
ERR:
    if (ercd <= 0)
        return ercd;
    return E_OK;
}

/************************************************/
/* Get DHCP Data                                */
/************************************************/

ER dhcp_get_byname(ID cepid, const char *ch_name)
{
    ER ercd;
    T_DHCP *rcv_pkt, *snd_pkt;
    T_NIF *nif;
    TMO tmo;
    int i;

    nif = getnif_from_name(ch_name);
    if(nif == NULL)
        nif = getnif_default();

#ifdef TOPPERS_ASP
#else
    dhcp_cep.myaddr.ipaddr = byte4_to_long(nif->ipaddr);
#endif

    /* Create CEP for DHCP */

#ifdef TOPPERS_ASP
	rcv_pkt = &m_rcv_pkt;
	snd_pkt = &m_snd_pkt;
	cepid = ID_UDP4DHCP;
#else
    if (!cepid){
        cepid = udp_vcre_cep(&dhcp_cep);
        if (cepid <= 0)
            return cepid;
    }
    else {
        ercd = udp_cre_cep(cepid, &dhcp_cep);
        if (ercd != E_OK)
            return ercd;
    }

    ercd = udp_set_opt(cepid, IP_IF_NAME, nif->name, 0);
    if (ercd != E_OK)
        goto END2;

    /* Set Broadcast Option */
    ercd = udp_set_opt(cepid, IP_BROADCAST, (VP)TRUE, 1);
    if (ercd != E_OK)
        goto END2;

    /* Get memory buffer for receiving DHCP pakcet */
    ercd = get_mpf(ID_ETH_MPF, &rcv_pkt);
    if (ercd != E_OK)
        goto END1;

    /* Get memory buffer for sending DHCP pakcet */
    ercd = get_mpf(ID_ETH_MPF, &snd_pkt);
    if (ercd != E_OK)
        goto END1;
#endif

    dhcp_cb.btskid = vget_tid();
    dhcp_cb.cepid = cepid;

    for (i = 0, tmo = DHCP_TMO; i < DHCP_RETRY; i++, tmo*=2) {

        /* Send DHCPDISCOVER */

        ercd = dhcp_snd_dat(cepid, DHCPDISCOVER, 0, snd_pkt, rcv_pkt, tmo, nif);
        if (ercd == E_TMOUT)
            continue;
        else if (ercd != E_OK)
            goto END1;

        /* Receive DHCPOFFER */

        ercd = dhcp_rcv_dat(cepid, DHCPOFFER, 0, rcv_pkt, tmo, nif);
        if (ercd == E_OK)
            break;
        else if (ercd != E_TMOUT)
            goto END1;
    }
    if (ercd != E_OK) /* Timeout Error */
        goto END1;

    for (i = 0, tmo = DHCP_TMO; i < DHCP_RETRY; i++, tmo*=2) {

        /* Send DHCPREQUEST */

        ercd = dhcp_snd_dat(cepid, DHCPREQUEST, REQ_SELECT, snd_pkt, rcv_pkt, tmo, nif);
        if (ercd == E_TMOUT)
            continue;
        else if (ercd != E_OK)
            goto END1;

        /* Receive DHCPACK */

        ercd = dhcp_rcv_dat(cepid, DHCPACK, REQ_SELECT, rcv_pkt, tmo, nif);
        if (ercd == E_OK || ercd != E_TMOUT)
            break;
    }

END1:
    dhcp_cb.cepid = 0;
    dhcp_cb.btskid = 0;
    vcan_wup();  /* AK 13MAR06 - Clear any pending wakeup call issued by dhcp callback */
#ifdef TOPPERS_ASP
#else
    udp_set_opt(cepid, IP_BROADCAST, (VP)FALSE, 1);
#endif
    udp_del_cep(cepid);
#ifdef TOPPERS_ASP
#else
    rel_mpf(ID_ETH_MPF, rcv_pkt);
    rel_mpf(ID_ETH_MPF, snd_pkt);
#endif

    if(ercd == E_OK)
        ercd = dhcp_sta_tsk(0, 0, 0, NULL);

    return ercd;
#ifdef TOPPERS_ASP
#else
END2:
#endif
    /* Set Option Broadcast Off */

#ifdef TOPPERS_ASP
#else
    udp_set_opt(cepid, IP_BROADCAST, (VP)FALSE, 1);
#endif
    udp_del_cep(cepid);
    return ercd;
}

ER dhcp_get_data(ID cepid)
{
    ER ercd;
    T_NIF *nif;

#ifdef TOPPERS_ASP
	m_fStop = FALSE;	// TOPPERSでは通信端点を削除しない！
#endif
	
    nif = getnif_default();
    ercd = dhcp_get_byname(cepid, nif->name);
    if(ercd == E_OK) {
#ifdef TOPPERS_ASP
#else
        memcpy(default_ipaddr, nif->ipaddr, 4);
        memcpy(default_gateway, nif->gateway, 4);
        memcpy(subnet_mask, nif->mask, 4);
        memcpy(dns_ipaddr, nif->dns_ipaddr, 4);
#endif
        memcpy(dhcp_ipaddr, nif->dhcp_ipaddr, 4);
    }
    return ercd;
}

/************************************************/
/* Re-Get DHCP Data                             */
/************************************************/

static ER dhcp_rget_data(ID cepid, int flg, T_NIF *nif)
{
    ER ercd;
    T_DHCP *rcv_pkt, *snd_pkt;
    TMO tmo;
    int i;

#ifdef TOPPERS_ASP
	rcv_pkt = &m_rcv_pkt;
	snd_pkt = &m_snd_pkt;
	cepid = ID_UDP4DHCP;
#else
    dhcp_cep.myaddr.ipaddr = byte4_to_long(nif->ipaddr);

    if (!cepid){
        cepid = udp_vcre_cep(&dhcp_cep);
        if (cepid <= 0)
            return cepid;
    }

    else {
        ercd = udp_cre_cep(cepid, &dhcp_cep);
        if (ercd != E_OK)
            return ercd;
    }

    ercd = udp_set_opt(cepid, IP_IF_NAME, nif->name, 0);
    if (ercd != E_OK)
        goto ERR;

    /* Set Broadcast Option */

    ercd = udp_set_opt(cepid, IP_BROADCAST, (VP)TRUE, 1);
    if (ercd != E_OK) {
        udp_del_cep(cepid);
        return ercd;
    }

    /* Get memory buffer for receiving DHCP pakcet */

    ercd = get_mpf(ID_ETH_MPF, &rcv_pkt);
    if (ercd != E_OK)
        goto ERR;

    /* Get memory buffer for sending DHCP pakcet */

    ercd = get_mpf(ID_ETH_MPF, &snd_pkt);
    if (ercd != E_OK)
        goto ERR;
#endif

    dhcp_cb.btskid = vget_tid();
    dhcp_cb.cepid = cepid;

    for (i = 0, tmo = DHCP_TMO; i < DHCP_RETRY; i++, tmo*=2) {

        /* Send DHCPREQUEST */

        ercd = dhcp_snd_dat(cepid, DHCPREQUEST, flg, snd_pkt, rcv_pkt, tmo, nif);
        if (ercd == E_TMOUT)
            continue;
        else if (ercd != E_OK)
            goto ERR;

        /* Receive DHCPACK */

        ercd = dhcp_rcv_dat(cepid, DHCPACK, flg, rcv_pkt, tmo, nif);
        if (ercd == E_OK || ercd != E_TMOUT)
            break;
    }

ERR:
    dhcp_cb.cepid = 0;
    dhcp_cb.btskid = 0;
    vcan_wup();  /* AK 13MAR06 - Clear any pending wakeup call issued by dhcp callback */
#ifdef TOPPERS_ASP
#else
    rel_mpf(ID_ETH_MPF, snd_pkt);
    rel_mpf(ID_ETH_MPF, rcv_pkt);
    udp_set_opt(cepid, IP_BROADCAST, (VP)FALSE, 1);
#endif
    udp_del_cep(cepid);

    return ercd;
}

/************************************************/
/* Renewing DHCP Data                           */
/************************************************/

ER dhcp_ren_byname(ID cepid, const char *ch_name)
{
    T_NIF *nif;

    nif = getnif_from_name(ch_name);
    if(nif == NULL)
        nif = getnif_default();

    return dhcp_rget_data(cepid, REQ_RENEW, nif);
}

ER dhcp_ren_data(ID cepid)
{
    ER ercd;
    T_NIF *nif;

#ifdef TOPPERS_ASP
	m_fStop = FALSE;	// TOPPERSでは通信端点を削除しない！
#endif

    nif = getnif_default();
    ercd = dhcp_ren_byname(cepid, nif->name);
    if(ercd == E_OK) {
#ifdef TOPPERS_ASP
#else
        memcpy(default_ipaddr, nif->ipaddr, 4);
        memcpy(default_gateway, nif->gateway, 4);
        memcpy(subnet_mask, nif->mask, 4);
        memcpy(dns_ipaddr, nif->dns_ipaddr, 4);
#endif
        memcpy(dhcp_ipaddr, nif->dhcp_ipaddr, 4);
    }
    return ercd;
}

/************************************************/
/* Rebind DHCP Data                             */
/************************************************/

ER dhcp_reb_byname(ID cepid, const char *ch_name)
{
    T_NIF *nif;

    nif = getnif_from_name(ch_name);
    if(nif == NULL)
        nif = getnif_default();

    return dhcp_rget_data(cepid, REQ_REBIND, nif);
}

ER dhcp_reb_data(ID cepid)
{
    ER ercd;
    T_NIF *nif;

#ifdef TOPPERS_ASP
	m_fStop = FALSE;	// TOPPERSでは通信端点を削除しない！
#endif

    nif = getnif_default();
    ercd = dhcp_reb_byname(cepid, nif->name);
    if(ercd == E_OK) {
#ifdef TOPPERS_ASP
#else
        memcpy(default_ipaddr, nif->ipaddr, 4);
        memcpy(default_gateway, nif->gateway, 4);
        memcpy(subnet_mask, nif->mask, 4);
        memcpy(dns_ipaddr, nif->dns_ipaddr, 4);
#endif
        memcpy(dhcp_ipaddr, nif->dhcp_ipaddr, 4);
    }
    return ercd;
}

/************************************************/
/* Delete DHCP resources                        */
/************************************************/

void dhcp_ext(void)
{
    /* Delete all the resources used by DHCP */

#ifdef TOPPERS_ASP
	m_fStop = TRUE;		// TOPPERSでは通信端点を削除しない！
    udp_can_cep(ID_UDP4DHCP, TFN_UDP_ALL);
#else
    udp_can_cep(dhcp_cb.cepid, TFN_UDP_ALL);
    udp_del_cep(dhcp_cb.cepid);
#endif
    dhcp_cb.cepid = 0;

    if (dhcp_cb.btskid != 0) {
        wup_tsk(dhcp_cb.btskid);
        dhcp_cb.btskid = 0;
    }

    ter_tsk(dhcp_cb.rtskid);
#ifdef TOPPERS_ASP
#else
    del_tsk(dhcp_cb.rtskid);
#endif
    dhcp_cb.rtskid = 0;

#ifdef TOPPERS_ASP
#else
    del_alm(dhcp_cb.almid);
#endif
    dhcp_cb.almid = 0;
}

/************************************************/
/* Start DHCP Task                              */
/************************************************/

ER dhcp_sta_tsk(ID tskid, ID cepid, ID almid, DHCP_CALLBACK callback)
{
    ER ercd;

    if(dhcp_cb.rtskid != 0)
        return E_OK;

    /* Create Task */

#ifdef TOPPERS_ASP
	tskid = TSK_DHCP;
#else
    if (tskid != 0) {
        ercd = cre_tsk(tskid, &dhcp_res_ctsk);
        if (ercd != E_OK)
            return ercd;
    }
    else{
        tskid = acre_tsk(&dhcp_res_ctsk);
        if (tskid <= 0)
            return tskid;
    }
#endif

    dhcp_cb.cepid = cepid;
    dhcp_cb.rtskid = tskid;
    dhcp_cb.callback = callback;

    /* Start Task */

    sta_tsk(tskid, 0);

    /* Set Alarm */

  #ifdef DEBUG
    lease_time = 10;
  #endif

#ifdef TOPPERS_ASP
	dhcp_cb.almid = ALM_DHCP;
#else
    if (almid != 0) {
        ercd = cre_alm(almid, &dalm);
        if (ercd != E_OK)
            goto ERR;
        dhcp_cb.almid = almid;
    }
    else {
        ercd = acre_alm(&dalm);
        if (ercd <= 0)
            goto ERR;
        dhcp_cb.almid = ercd;
    }
#endif

    if (!(lease_time&0xFFF00000))
        ercd = sta_alm(dhcp_cb.almid, (lease_time*1000/MSEC));
    else
        ercd = sta_alm(dhcp_cb.almid, (0xFFFFFFFF));

    if (ercd != E_OK)
        goto ERR;

    return E_OK;

ERR:
#ifdef TOPPERS_ASP
#else
    del_tsk(dhcp_cb.rtskid);
    del_alm(dhcp_cb.almid);
#endif
    dhcp_cb.rtskid = 0;
    dhcp_cb.almid = 0;
    return ercd;
}

/************************************************/
/* DHCP Alarm Handler                           */
/************************************************/

#ifdef TOPPERS_ASP
void ex_ip_lease(void)
#else
static void ex_ip_lease(void)
#endif
{
#ifdef TOPPERS_ASP
    iwup_tsk(dhcp_cb.rtskid);
#else
    wup_tsk(dhcp_cb.rtskid);
#endif
}

/************************************************/
/* DHCPREQUEST Send Task                        */
/************************************************/

#ifdef TOPPERS_ASP
TASK dhcp_req_tsk(void)
#else
static TASK dhcp_req_tsk(void)
#endif
{
    ER ercd;
    T_NIF *nif;
    DHCP_CALLBACK func;

    func = dhcp_cb.callback;

    for(;;) {
        vcan_wup();
        ercd = tslp_tsk(TMO_FEVR);
        if (ercd == E_RLWAI)
            break;

        /* Renew DHCP Data */
        for(nif = getnif_default(); nif != NULL; nif=nif->next) {
            if(byte4_to_long(nif->dhcp_ipaddr) != 0L) {
                ercd = dhcp_ren_byname(dhcp_cb.cepid, (char *) nif->name);
#ifdef TOPPERS_ASP
                if ( ercd != E_OK ) {
                    // 再取得に失敗した場合は既知のリース期間後に再実行する（仕方ない）
//                    break;
                    set_flg(FLG_ETH, EVENT_ETH_DHCP_RESET);
                    goto ERR;
		}
#else
                if (ercd != E_OK)
                    goto ERR;
#endif
            }
        }

        /* Restart Alarm */
      #ifdef DEBUG
        lease_time = 10;
      #endif
        if (!(lease_time&0xFFF00000))
            ercd = sta_alm(dhcp_cb.almid, (lease_time*1000/MSEC));
        else
            ercd = sta_alm(dhcp_cb.almid, (0xFFFFFFFF));

        if (ercd != E_OK)
            goto ERR;

ERR:
        if (func != NULL)
            (func)(ercd);
    }
    exd_tsk();
}

/* END */
