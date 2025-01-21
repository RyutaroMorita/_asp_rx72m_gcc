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
 *  @(#) $Id: ip6_var.h,v 1.5 2009/12/24 05:48:16 abe Exp $
 */

/*	$FreeBSD: src/sys/netinet6/ip6_var.h,v 1.10 2002/10/16 01:54:45 sam Exp $	*/
/*	$KAME: ip6_var.h,v 1.62 2001/05/03 14:51:48 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ip_var.h	8.1 (Berkeley) 6/10/93
 */
 
#ifndef _IP6_VAR_H_
#define _IP6_VAR_H_

#ifdef SUPPORT_INET6

/*
 *  IPv6 �w�b�_�E�y�C���[�h�A�N�Z�X�}�N��
 */

#define IF_IP6_HDR_SIZE			(IF_HDR_SIZE + IP6_HDR_SIZE)

#define GET_IP6_HDR(nbuf)		((T_IP6_HDR*)((nbuf)->buf + IF_HDR_SIZE))
#define GET_IP6_SDU(nbuf)		((uint8_t*)((nbuf)->buf) + GET_IF_IP6_HDR_SIZE(nbuf))
#define GET_IP6_NEXT_HDR(nbuf)		((uint8_t*)((nbuf)->buf) + IF_IP6_HDR_SIZE)

#define GET_IP6_HDR_SIZE(iph)		(get_ip6_hdr_size(iph))
#define GET_IP6_SDU_SIZE(iph)		(ntohs((iph)->plen))
#define GET_IF_IP6_HDR_SIZE(nbuf)	(IF_HDR_SIZE + (GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf))))

#define SET_IP6_SDU_SIZE(iph,slen)	((iph)->plen=htons(slen))

/* ip6_output �̃t���O */

#define IPV6_OUT_FLG_DAD		0x0100	/* �d���A�h���X���o	*/
#define IPV6_OUT_FLG_HOP_LIMIT		0x0200	/* �z�b�v���~�b�g�w��	*/

/* �z�b�v���~�b�g�t���O���t�����A�z�b�v���~�b�g�l�𑀍삷��}�N�� */

#define IPV6_OUT_GET_HOP_LIMIT(f)	((f)&0x00ff)
#define IPV6_OUT_SET_HOP_LIMIT(f,l)	((f)|(l))

/*
 *  ip6_unknown_opt -- ���m�̃I�v�V�����̏���
 *
 *    �߂�l:
 *
 *      0 �ȏ� 			����A�I�v�V�������B
 *      IP6_OPT_RET_ERR (-1)	�G���[�A�ďo���Ńl�b�g���[�N�o�b�t�@���J������B
 *      IP6_OPT_RET_REL (-2)	�G���[�A�l�b�g���[�N�o�b�t�@�͊J������Ă���B
 */

#define IP6_OPT_RET_ERR		(-1)
#define IP6_OPT_RET_REL		(-2)

/*
 *  IPv4 �� IPv6 ���R���p�C�����ɑI�����邽�߂̃}�N��
 */

#define T_TCP_IP_Q_HDR			T_TCP_IP6_Q_HDR

#define IF_IP_HDR_SIZE			IF_IP6_HDR_SIZE

#define GET_IP_HDR(nbuf)		GET_IP6_HDR(nbuf)
#define GET_IP_SDU(nbuf)		GET_IP6_SDU(nbuf)

#define GET_IP_HDR_SIZE(iph)		GET_IP6_HDR_SIZE(iph)
#define GET_IP_SDU_SIZE(iph)		GET_IP6_SDU_SIZE(iph)
#define GET_IF_IP_HDR_SIZE(nbuf)	GET_IF_IP6_HDR_SIZE(nbuf)

#define SET_IP_SDU_SIZE(iph,len)	SET_IP6_SDU_SIZE(iph,len)

#define IP_OUTPUT(nbuf,tmout)		ip6_output(nbuf,0,tmout)
#define IP_INIT()			ip6_init()
#define IP_REMOVE_OPTIONS(nbuf)		ip6_remove_exthdrs(nbuf)

/*
 *  IPv6 �� MMTU �T�C�Y�̃l�b�g���[�N�o�b�t�@
 */

typedef struct t_net_buf_ipv6_mmtu {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		unit;	/* �C���^�t�F�[�X�ԍ�	*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_HDR_SIZE + IPV6_MMTU];
				/* �o�b�t�@�{��		*/
	} T_NET_BUF_IPV6_MMTU;

/*
 *  65536 �I�N�e�b�g�T�C�Y�̃l�b�g���[�N�o�b�t�@
 */

typedef struct t_net_buf6_65536 {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_IP6_HDR_SIZE + 65536];
				/* �o�b�t�@�{��		*/
#if defined(IF_PDU_HDR_PADDING)
	uint8_t		padding[IF_PDU_HDR_PADDING];
#endif				/* �w�b�_�̗]��		*/
	} T_NET_BUF6_65536;

#ifdef IP6_CFG_FRAGMENT

/*
 *  �č\���L���[�p IPv6 �w�b�_�̒�`
 */

typedef struct t_qip6_hdr {
	uint32_t		vcf;		/* Version:        4 bit		*/
					/* Traffic Class:  8 bit		*/
					/* Flow Label:    20 bit		*/
	uint16_t	plen;		/* Payload Length			*/
	uint8_t		next;		/* Next Header				*/
	uint8_t		hlim;		/* Hop Limit				*/
	T_IN6_ADDR	src;		/* Source Address			*/
	T_NET_BUF	*next_frag;	/* ���� IPv6 �t���O�����g	*/
	uint16_t	foff;		/* �f�Ѓw�b�_�̃I�t�Z�b�g		*/
	uint16_t	flen;		/* �f�В�				*/
	uint16_t	ftim;		/* �č\���^�C���A�E�g			*/
	uint16_t	dummy1;
	uint8_t		dummy2[sizeof(T_IN6_ADDR) - (sizeof(T_NET_BUF*) + sizeof(uint16_t) * 4)];
	} T_QIP6_HDR;

#define QIP6_HDR_SIZE			(sizeof(T_QIP6_HDR))
#define IF_QIP6_HDR_SIZE		(IF_HDR_SIZE + QIP6_HDR_SIZE)

#define GET_QIP6_HDR(nbuf)		((T_QIP6_HDR*)((nbuf)->buf + IF_HDR_SIZE))
#define GET_QIP6_SDU(nbuf)		((uint8_t*)(nbuf)->buf + GET_IF_QIP6_HDR_SIZE(nbuf))

#define GET_QIP6_HDR_SIZE(iph)		((uint8_t)IP6_VHL_HL((iph)->vhl) << 2)
#define GET_IF_QIP6_HDR_SIZE(nbuf)	(IF_HDR_SIZE + (GET_QIP6_HDR_SIZE(GET_QIP6_HDR(nbuf))))

/*
 *  �f�[�^�O�����č\���p�l�b�g���[�N�o�b�t�@
 */

typedef struct t_net_buf6_reassm {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		align[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IP6_CFG_FRAG_REASSM_SIZE];
				/* �o�b�t�@�{��		*/
	} T_NET_BUF6_REASSM;

#endif	/* of #ifdef IP6_CFG_FRAGMENT */

/*
 *  TCP �̍č\���L���[�ɂ����� IPv6 �w�b�_�̒�`
 */

typedef struct t_tcp_ip6_q_hdr {
	uint8_t vc;		/* Version:        4 bit		*/
	uint8_t cf;		/* Traffic Class:  8 bit		*/
			/* Flow Label:     4 bit (20 bit)	*/
	uint16_t thoff;	/* TCP �w�b�_�̃I�t�Z�b�g		*/
	uint16_t plen;	/* Payload Length			*/
	uint8_t next;	/* Next Header				*/
	uint8_t hlim;	/* Hop Limit				*/
	T_IN6_ADDR src;	/* Source Address			*/
	T_IN6_ADDR dst;	/* Destination Address			*/
	} T_TCP_IP6_Q_HDR;

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

typedef struct t_in6_ifstat {
	uint32_t	ipv6IfStatsInReceives;
	uint32_t	ipv6IfStatsInHdrErrors;
/*	uint32_t	ipv6IfStatsInTooBigErrors;*/
/*	uint32_t	ipv6IfStatsInNoRoutes;*/
	uint32_t	ipv6IfStatsInAddrErrors;
	uint32_t	ipv6IfStatsInUnknownProtos;
	uint32_t	ipv6IfStatsInTruncatedPkts;
/*	uint32_t	ipv6IfStatsInDiscards;*/
/*	uint32_t	ipv6IfStatsInDelivers;*/
/*	uint32_t	ipv6IfStatsOutForwDatagrams;*/
	uint32_t	ipv6IfStatsOutRequests;
	uint32_t	ipv6IfStatsOutDiscards;
	uint32_t	ipv6IfStatsOutFragOKs;
	uint32_t	ipv6IfStatsOutFragFails;
	uint32_t	ipv6IfStatsOutFragCreates;
	uint32_t	ipv6IfStatsReasmReqds;
	uint32_t	ipv6IfStatsReasmOKs;
	uint32_t	ipv6IfStatsReasmFails;
	uint32_t	ipv6IfStatsInMcastPkts;
	uint32_t	ipv6IfStatsOutMcastPkts;
} T_IN6_IFSTAT;

extern T_IN6_IFSTAT in6_ifstat;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �֐�
 */

extern ER ip6_output (T_NET_BUF *output, uint16_t flags, TMO tmout);
extern void ip6_init (void);
extern uint8_t *ip6_get_prev_hdr (T_NET_BUF *nbuf, uint_t off);
extern uint_t get_ip6_hdr_size (T_IP6_HDR *iph);
extern ER_UINT ip6_nexthdr (T_NET_BUF *nbuf, uint_t off, uint_t proto, uint_t *nextp);
extern ER_UINT ip6_lasthdr (T_NET_BUF *nbuf, uint_t off, uint_t proto, uint_t *nextp);
extern ER_UINT ip6_unknown_opt (T_NET_BUF *input, uint8_t *opt);
extern uint_t dest6_input  (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern uint_t route6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern uint_t frag6_input  (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern void frag6_timer (void);
extern ER ip6_remove_exthdrs (T_NET_BUF *nbuf);

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _IP6_VAR_H_ */
