/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̏����𖞂������ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 *  @(#) $Id: ethernet.c,v 1.5.4.1 2015/02/05 02:09:13 abe Exp abe $
 */

/* 
 *  Ethernet �����^�X�N�̖{��
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/ethernet.h>
#include <net/if_llc.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/if_ether.h>
#include <netinet6/if6_ether.h>
#include <netinet6/nd6.h>

#include <net/if_var.h>
#include <net/if6_var.h>

#ifdef SUPPORT_ETHER

/*
 *  �ϐ�
 */

#if defined(SUPPORT_INET4)

const uint8_t ether_broad_cast_addr[ETHER_ADDR_LEN] = {
	UINT_C(0xff), UINT_C(0xff), UINT_C(0xff),
	UINT_C(0xff), UINT_C(0xff), UINT_C(0xff)
	};

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  �ϐ�
 */

/* �l�b�g���[�N�C���^�t�F�[�X�\���� */

#if defined(SUPPORT_INET4)

static T_IFNET ether_ifnet = {
	NULL,			/* �l�b�g���[�N�C���^�t�F�[�X�̃\�t�g�E�F�A���	*/
	{
		IPV4_ADDR_LOCAL,	/* IPv4 �A�h���X		*/
		IPV4_ADDR_LOCAL_MASK,	/* �T�u�l�b�g�}�X�N		*/
		},
	};

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

static T_IFNET ether_ifnet = {
	NULL,			/* �l�b�g���[�N�C���^�t�F�[�X�̃\�t�g�E�F�A���	*/
	{},			/* IPv6 �A�h���X���				*/
	{},			/* �}���`�L���X�g IPv6 �A�h���X			*/
	0,			/* �t���O					*/
	};

#endif	/* of #if defined(SUPPORT_INET6) */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

T_IF_STATS if_stats;

#endif	/* of #ifdef SUPPORT_MIB */

#ifdef ETHER_CFG_802_WARNING

/*
 *  �֐�
 */

static void ieee_802_input (T_NET_BUF *input);

/*
 *  ieee_802_input -- IEEE 802.3 ���͏���
 */

static void
ieee_802_input (T_NET_BUF *input)
{
	T_8023MAC_HDR	*mhdr;
	T_8022SNAP_HDR	*shdr;

	mhdr = GET_8023MAC_HDR(input);
	shdr = GET_8022SNAP_HDR(input);
	syslog(LOG_WARNING, "[ETHER] unexp 802.3 from: %s, proto: 0x%04x.",
	                    mac2str(NULL, mhdr->shost), ntohs(*(uint16_t*)&shdr->type));
	}

#endif	/* of #ifdef ETHER_CFG_802_WARNING */

/*
 *  ether_get_ifnet -- �l�b�g���[�N�C���^�t�F�[�X�\���̂�Ԃ��B
 */

T_IFNET *
ether_get_ifnet (void)
{
	return &ether_ifnet;
	}

#if defined(SUPPORT_INET6)

/*
 *  ether_in6_resolve_multicast -- �C�[�T�l�b�g�̃}���`�L���X�g�A�h���X�ւ̕ϊ�
 */

ER
ether_in6_resolve_multicast (T_ETHER_ADDR *ifaddr, T_IN6_ADDR *maddr)
{
	/* �}���`�L���X�g�A�h���X���`�F�b�N����B*/
	if (!IN6_IS_ADDR_MULTICAST(maddr))
		return E_PAR;

	/* �C�[�T�l�b�g�̃}���`�L���X�g�A�h���X�ւ̕ϊ� */
	ether_map_ipv6_multicast(ifaddr, maddr);

	return E_OK;
	}

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  ether_raw_output -- Ethernet �C���^�t�F�[�X�̏o�͊֐��AMAC �A�h���X��������
 */

ER
ether_raw_output (T_NET_BUF *output, TMO tmout)
{
	ER error = E_OK;

	/* Ethernet �o�̓L���[�ɓ�������B*/
	if ((error = tsnd_dtq(DTQ_ETHER_OUTPUT, (intptr_t)output, tmout)) != E_OK) {
		NET_COUNT_ETHER(net_count_ether.out_err_packets, 1);
		NET_COUNT_MIB(if_stats.ifOutDiscards, 1);

		/* IF �Ńl�b�g���[�N�o�b�t�@���J�����Ȃ��t���O���`�F�b�N����B*/
		if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
			syscall(rel_net_buf(output));
			}
		else {
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;
			}
		IF_ETHER_NIC_RESET(IF_ETHER_NIC_GET_SOFTC());
		}
	return error;
	}

/*
 *  ether_output -- Ethernet �C���^�t�F�[�X�̏o�͊֐��AMAC �A�h���X�����L��
 */

ER
ether_output (T_NET_BUF *output, void *dst, T_IF_ADDR *gw, TMO tmout)
{
	T_IF_SOFTC	*ic;
	ER		error = E_OK;

	/* ���M�� MAC �A�h���X��ݒ肷��B*/
	ic = IF_ETHER_NIC_GET_SOFTC();
	memcpy(GET_ETHER_HDR(output)->shost, ic->ifaddr.lladdr, ETHER_ADDR_LEN);

	switch(ntohs(GET_ETHER_HDR(output)->type)) {

#if defined(SUPPORT_INET4)

	case ETHER_TYPE_IP:		/* IPv4	*/
		if (arp_resolve(&ic->ifaddr, output, *(uint32_t*)dst)) {	/* true �Ȃ�A�h���X������ */
			error = ether_raw_output(output, tmout);
			}
		break;

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

	case ETHER_TYPE_IPV6:		/* IPv6	*/
		error = nd6_storelladdr((T_ETHER_ADDR*)GET_ETHER_HDR(output)->dhost,
		                        (T_IN6_ADDR*)dst, gw);
		if (error == E_OK)
			error = ether_raw_output(output, tmout);

		/* IF �Ńl�b�g���[�N�o�b�t�@���J�����Ȃ��t���O���`�F�b�N����B*/
		else if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
			syscall(rel_net_buf(output));
			}
		else {
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;
			}
		break;

#endif	/* of #if defined(SUPPORT_INET6) */

	default:
		NET_COUNT_MIB(if_stats.ifOutErrors, 1);

		/* IF �Ńl�b�g���[�N�o�b�t�@���J�����Ȃ��t���O���`�F�b�N����B*/
		if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
			syscall(rel_net_buf(output));
			}
		else {
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;
			}
		error = E_PAR;
		break;
		}

	if (error != E_OK)
		NET_COUNT_ETHER(net_count_ether.out_err_packets, 1);
	return error;
	}

/*
 *  Ethernet �o�̓^�X�N
 */

void
ether_output_task(intptr_t exinf)
{
	T_IF_SOFTC	*ic;
	T_NET_BUF	*output;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[ETHER OUTPUT:%d] started.", tskid);

	ic = IF_ETHER_NIC_GET_SOFTC();

	while (true) {
		while (rcv_dtq(DTQ_ETHER_OUTPUT, (intptr_t*)&output) == E_OK) {
			NET_COUNT_ETHER(net_count_ether.out_octets,  output->len);
			NET_COUNT_MIB(if_stats.ifOutOctets, output->len + 8);
			NET_COUNT_ETHER(net_count_ether.out_packets, 1);

#ifdef SUPPORT_MIB
			if ((*(GET_ETHER_HDR(output)->dhost) & ETHER_MCAST_ADDR) == 0) {
				NET_COUNT_MIB(if_stats.ifOutUcastPkts, 1);
				}
			else {
				NET_COUNT_MIB(if_stats.ifOutNUcastPkts, 1);
				}
#endif	/* of #ifdef SUPPORT_MIB */

			syscall(wai_sem(ic->semid_txb_ready));

			IF_ETHER_NIC_START(ic, output);

#ifndef ETHER_NIC_CFG_RELEASE_NET_BUF

			if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
				syscall(rel_net_buf(output));
				}
			else {
				output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;

#ifdef SUPPORT_TCP
				sig_sem(SEM_TCP_POST_OUTPUT);
#endif	/* of #ifdef SUPPORT_TCP */
				}

#endif	/* of #ifndef ETHER_NIC_CFG_RELEASE_NET_BUF */

			}
		}
	}

/*
 *  Ethernet ���̓^�X�N
 */

void
ether_input_task(intptr_t exinf)
{
	T_IF_SOFTC	*ic;
	T_NET_BUF	*input;
	T_ETHER_HDR	*eth;
	ID		tskid;
	uint16_t	proto;

	/* �l�b�g���[�N�C���^�t�F�[�X�Ǘ�������������B*/
	ifinit();

	/* NIC ������������B*/
	ic = IF_ETHER_NIC_GET_SOFTC();
	IF_ETHER_NIC_PROBE(ic);
	IF_ETHER_NIC_INIT(ic);

	/* Ethernet �o�̓^�X�N���N������ */
	syscall(act_tsk(ETHER_OUTPUT_TASK));

	/* �l�b�g���[�N�^�C�}�^�X�N���N������ */
	syscall(act_tsk(NET_TIMER_TASK));

	get_tid(&tskid);

	syslog(LOG_NOTICE, "[ETHER INPUT:%2d] started on MAC Addr: %s.",
	                   tskid, mac2str(NULL, ic->ifaddr.lladdr));

#if defined(SUPPORT_INET4)

	/* ARP ������������B*/
	arp_init();

#endif	/* of #if defined(SUPPORT_INET4) */

	ether_ifnet.ic = ic;

	while (true) {
		syscall(wai_sem(ic->semid_rxb_ready));
		if ((input = IF_ETHER_NIC_READ(ic)) != NULL) {
			NET_COUNT_ETHER(net_count_ether.in_octets,  input->len);
			NET_COUNT_MIB(if_stats.ifInOctets, input->len + 8);
			NET_COUNT_ETHER(net_count_ether.in_packets, 1);
			eth = GET_ETHER_HDR(input);
			proto = ntohs(eth->type);

#ifdef SUPPORT_MIB
			if ((*eth->dhost & ETHER_MCAST_ADDR) == 0) {
				NET_COUNT_MIB(if_stats.ifInUcastPkts, 1);
				}
			else {
				NET_COUNT_MIB(if_stats.ifInNUcastPkts, 1);
				}
#endif	/* of #ifdef SUPPORT_MIB */

#if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL)

			if ((*eth->dhost & ETHER_MCAST_ADDR) && *eth->dhost != 0xff) {

#ifdef ETHER_CFG_MCAST_WARNING

				if (proto <= 1500)
					proto = ntohs(*(uint16_t*)&(GET_8022SNAP_HDR(input)->type));
				syslog(LOG_WARNING, "[ETHER] mcast addr  from: %s, to: %s, proto: 0x%04x.",
				                    mac2str(NULL, eth->shost), mac2str(NULL, eth->dhost), proto);

#endif	/* of #ifdef ETHER_CFG_MCAST_WARNING */

				NET_COUNT_ETHER(net_count_ether.in_err_packets, 1);
				NET_COUNT_MIB(if_stats.ifInErrors, 1);
				syscall(rel_net_buf(input));
				continue;
				}

#endif	/* of #if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) */

			switch(proto) {

#if defined(SUPPORT_INET4)

			case ETHER_TYPE_IP:		/* IP	*/
				ip_input(input);
				break;

			case ETHER_TYPE_ARP:		/* ARP	*/
				arp_input(&ic->ifaddr, input);
				break;

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

			case ETHER_TYPE_IPV6:		/* IPv6	*/
				ip6_input(input);
				break;

#endif	/* of #if defined(SUPPORT_INET6) */

			default:

#ifdef ETHER_CFG_UNEXP_WARNING

#ifdef ETHER_CFG_802_WARNING

				if (proto <= 1500)
					ieee_802_input(input);
				else
					syslog(LOG_NOTICE, "[ETHER] unexp proto from: %s, proto: 0x%04x.",
					                   mac2str(NULL, GET_ETHER_HDR(input)->shost), proto);

#else	/* of #ifdef ETHER_CFG_802_WARNING */

				syslog(LOG_INFO, "[ETHER] unexp proto from: %s, proto: 0x%04x.",
				                   mac2str(NULL, GET_ETHER_HDR(input)->shost), proto);

#endif	/* of #ifdef ETHER_CFG_802_WARNING */

#endif	/* of #ifdef ETHER_CFG_UNEXP_WARNING */

				NET_COUNT_ETHER(net_count_ether.in_err_packets, 1);
				NET_COUNT_MIB(if_stats.ifUnknownProtos, 1);
				syscall(rel_net_buf(input));
				break;
				}
			}
		}
	}

#ifdef SUPPORT_E1

void
ether_set_lladdr (uint8_t* p)
{
	T_IF_SOFTC	*ic;
	ic = IF_ETHER_NIC_GET_SOFTC();
	IF_ETHER_NIC_SET_MACADDR(ic, p);
	}

#endif	// SUPPORT_E1

#endif /* of #ifdef SUPPORT_ETHER */
