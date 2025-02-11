/******************************************************************************
* NORTi3 Network DHCP sample  Header                                          *
*                                                                             *
*  Copyright (c) 1998-2005, MiSPO Co., Ltd.                                   *
*  All rights reserved.                                                       *
*                                                                             *
* 25/Feb/2000                                                                 *
* 12/Feb/2001 Change Task priority 4 -> 5  DHCP_REQTSK_PRI                    *
* 16/Dec/2003 Modified for Multichannel                                    AK *
* 20/Apr/2005 Modified for Multichannel                                    PK *
* 13/May/2005 Added dhcp_ext                                               AK *
******************************************************************************/
#ifndef NONDHCP_H
#define NONDHCP_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef TOPPERS_ASP

#define UDP_PORT_BOOTPS     67      /* Bootstrap Protocol Server */

typedef struct t_nif {
	struct t_nif *next;	/* Pointer to Next Parameter Block */
	char name[8];		/* Channel Name */
	UB  hwaddr[6];		/* Hardware Address ex. MAC Address */
	UB  ipaddr[4];		/* Default IP Address */
	UB  gateway[4];		/* Default Gateway */
	UB  mask[4];		/* Subnet Mask */
	UB dhcp_ipaddr[4];	/* DHCP ipaddr of this Interface */
	UB dns_ipaddr[4];	/* DNS ipaddr of this Interface */
} T_NIF ;

typedef struct t_nif_addr {
	UB *hwaddr;		/* Hardware Address ex. MAC Address */
	UB *ipaddr;		/* Default IP Address */
	UB *gateway;		/* Default Gateway */
	UB *mask;		/* Subnet Mask */
#ifdef DUAL_STK
	UB *host_id;		/* Host I/F ID */
#endif
} T_NIF_ADDR;

#ifndef LENDIAN
#define htonl(x)    (x)
#define htons(x)    (x)
#define ntohl(x)    (x)
#define ntohs(x)    (x)
#else
UW htonl(UW);
UH htons(UH);
#define ntohl(x)    htonl(x)
#define ntohs(x)    htons(x)
#endif

#endif	// TOPPERS_ASP

/* Constant */

#define DHCP_REQTSK_PRI    5    /* DHCP Request Task Priority */
#ifndef DHCP_REQTSK_SSZ
#define DHCP_REQTSK_SSZ    512  /* DHCP Request Task Stack Size */
#endif

/* DHCP Callback Routine */

typedef void (*DHCP_CALLBACK)(ER);

/* DHCP Control Block */

typedef struct t_dhcp_cb {
    ID cepid;
    ID btskid;
    ID rtskid;
    ID almid;
    DHCP_CALLBACK callback;
} T_DHCP_CB;

/* DHCP Packet */

typedef struct t_dhcp {
    UB      op;         /* Message Operation */
#define BOOT_REQUEST    1
#define BOOT_REPLY      2
    UB      htype;      /* Hardware Address Type */
    UB      hlen;       /* Hardware Address Length */
    UB      hops;       /* Hardware Option */
    UW      xid;        /* Transaction ID */
    UH      secs;       /* Progress Time */
    UH      flag;       /* Flag field */
    UW      ciaddr;     /* Client IP Address */
    UW      yiaddr;     /* Your Address */
    UW      siaddr;     /* Server IP Address */
    UW      giaddr;     /* Gateway IP Address */
    UB      chaddr[16]; /* Client Hardware Address */
    UB      sname[64];  /* Server Name(Option) */
    UB      file[128];  /* Boot File Name */
#define DHCP_OP_SIZ 312
    UB      option[DHCP_OP_SIZ]; /* Option */
} T_DHCP;

#define REQ_SELECT 1
#define REQ_RENEW  2
#define REQ_REBIND 3

/* DHCP Option */

#define DHCP_OP_SUBNET  1   /* Subnet Mask */
#define DHCP_OP_ROUTER  3   /* Router Address */
#define DHCP_OP_DNS     6   /* Name Server Address */
#define DHCP_OP_ADRREQ  50  /* Address Request */
#define DHCP_OP_ADDRTM  51  /* IP Address Lease Time */
#define DHCP_OP_MSGTYP  53  /* Message Type */
#define DHCP_OP_SERVID  54  /* DHCP Server ID */
#define DHCP_OP_PRMLST  55  /* Parameter Request List */
#define DHCP_OP_RENETM  58  /* Renewal Time */
#define DHCP_OP_REBITM  59  /* Rebinding Time */
#define DHCP_OP_CLIENT  61  /* Client ID */

/* DHCP Message Type */

#define DHCPDISCOVER    1
#define DHCPOFFER       2
#define DHCPREQUEST     3
#define DHCPDECLINE     4
#define DHCPACK         5
#define DHCPNAK         6
#define DHCPRELEASE     7

/* Defined for backward compatibility of IPv6 dns resolution */
#define dns_name_resolver   dns_resolver

/* Configuration */

#define DHCP_RETRY      3

ER dhcp_get_data(ID cepid);
ER dhcp_get_byname(ID cepid, const char *ch_name);

ER dhcp_reb_data(ID cepid);
ER dhcp_reb_byname(ID cepid, const char *ch_name);

void dhcp_ext(void);

#ifdef __cplusplus
}
#endif
#endif /* NONDHCP_H */
