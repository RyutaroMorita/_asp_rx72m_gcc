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
 *  @(#) $Id: ip_var.h,v 1.5 2009/12/24 05:47:21 abe Exp $
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
 *	@(#)ip_var.h	8.2 (Berkeley) 1/9/95
 * $FreeBSD: src/sys/netinet/ip_var.h,v 1.45.2.1 1999/08/29 16:29:51 peter Exp $
 */
 
#ifndef _IP_VAR_H_
#define _IP_VAR_H_

/*
 *  IPv4 �w�b�_�E�y�C���[�h�A�N�Z�X�}�N��
 */

#define IF_IP4_HDR_SIZE			(IF_HDR_SIZE + IP4_HDR_SIZE)

#define GET_IP4_HDR(nbuf)		((T_IP4_HDR*)((nbuf)->buf + IF_HDR_SIZE))
#define GET_IP4_SDU(nbuf)		((uint8_t*)((nbuf)->buf) + GET_IF_IP4_HDR_SIZE(nbuf))

#define GET_IP4_HDR_SIZE(iph)		((uint8_t)IP4_VHL_HL((iph)->vhl) << 2)
#define GET_IP4_SDU_SIZE(iph)		(ntohs((iph)->len) - GET_IP4_HDR_SIZE(iph))
#define GET_IF_IP4_HDR_SIZE(nbuf)	(IF_HDR_SIZE + (GET_IP4_HDR_SIZE(GET_IP4_HDR(nbuf))))

#define SET_IP4_SDU_SIZE(iph,slen)	((iph)->len=(uint16_t)htons((slen) + IP4_HDR_SIZE))

/*
 *  IPv4 �� IPv6 ���R���p�C�����ɑI�����邽�߂̃}�N��
 */

#if defined(SUPPORT_INET4)

#define T_TCP_IP_Q_HDR			T_TCP_IP4_Q_HDR

#define IF_IP_HDR_SIZE			IF_IP4_HDR_SIZE

#define GET_IP_HDR(nbuf)		GET_IP4_HDR(nbuf)
#define GET_IP_SDU(nbuf)		GET_IP4_SDU(nbuf)

#define GET_IP_HDR_SIZE(iph)		GET_IP4_HDR_SIZE(iph)
#define GET_IP_SDU_SIZE(iph)		GET_IP4_SDU_SIZE(iph)
#define GET_IF_IP_HDR_SIZE(nbuf)	GET_IF_IP4_HDR_SIZE(nbuf)

#define SET_IP_SDU_SIZE(iph,len)	SET_IP4_SDU_SIZE(iph,len)

#define IP_OUTPUT(nbuf,tmout)		ip_output(nbuf,tmout)
#define IP_INIT()			ip_init()
#define IP_REMOVE_OPTIONS(nbuf)		ip_remove_options(nbuf)

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  IP �� MSS �T�C�Y�̃l�b�g���[�N�o�b�t�@
 */

typedef struct t_net_buf_ip_mss {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_HDR_SIZE + IP4_MSS];
				/* �o�b�t�@�{��		*/
	} T_NET_BUF_IP_MSS;

/*
 *  65536 �I�N�e�b�g�T�C�Y�̃l�b�g���[�N�o�b�t�@
 */

typedef struct t_net_buf4_65536 {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_IP4_HDR_SIZE + 65536];
				/* �o�b�t�@�{��		*/
#if defined(IF_PDU_HDR_PADDING)
	uint8_t		padding[IF_PDU_HDR_PADDING];
#endif				/* �w�b�_�̗]��		*/
	} T_NET_BUF4_65536;

#ifdef IP4_CFG_FRAGMENT

/*
 *  �č\���L���[�p IPv4 �w�b�_�̒�`
 */

typedef struct t_qip4_hdr {
	uint8_t		vhl;		/* version << 4 | header length >> 2	*/
					/* length �� 4 octets �P��		*/
	uint8_t		type;		/* type of services			*/
	uint16_t	len;		/* total length				*/

	uint16_t	id;		/* identification			*/
	uint16_t	flg_off;	/* fragment flag & offset		*/

	uint8_t		ttl;		/* time to live				*/
	uint8_t		proto;		/* protocol				*/
	uint16_t	sum;		/* checksum				*/

	uint32_t	src;		/* source address			*/

	T_NET_BUF	*next;		/* ���� IPv4 �t���O�����g			*/
	} T_QIP4_HDR;

#define QIP4_HDR_SIZE			(sizeof(T_QIP4_HDR))
#define IF_QIP4_HDR_SIZE		(IF_HDR_SIZE + QIP4_HDR_SIZE)

#define GET_QIP4_HDR(nbuf)		((T_QIP4_HDR*)((nbuf)->buf + IF_HDR_SIZE))
#define GET_QIP4_SDU(nbuf)		((uint8_t*)(nbuf)->buf + GET_IF_QIP4_HDR_SIZE(nbuf))

#define GET_QIP4_HDR_SIZE(iph)		((uint8_t)IP4_VHL_HL((iph)->vhl) << 2)
#define GET_IF_QIP4_HDR_SIZE(nbuf)	(IF_HDR_SIZE + (GET_QIP4_HDR_SIZE(GET_QIP4_HDR(nbuf))))

/*
 *  �f�[�^�O�����č\���p�l�b�g���[�N�o�b�t�@
 */

typedef struct t_net_buf4_reassm {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		align[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IP4_CFG_FRAG_REASSM_SIZE];
				/* �o�b�t�@�{��		*/
	} T_NET_BUF4_REASSM;

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

/*
 *  TCP �̍č\���L���[�ɂ����� IPv4 �w�b�_�̒�`
 */

typedef struct t_tcp_ip4_q_hdr {
	uint8_t		vhl;		/* version << 4 | header length >> 2	*/
					/* length �� 4 octets �P��		*/
	uint8_t		type;		/* type of services			*/
	uint16_t	len;		/* total length				*/

	uint16_t	id;		/* identification			*/
	uint16_t	flg_off;	/* fragment flag & offset		*/

	uint8_t		ttl;		/* time to live				*/
	uint8_t		proto;		/* protocol				*/
	uint16_t	thoff;		/* TCP �w�b�_�̃I�t�Z�b�g		*/

	T_IN4_ADDR	src;		/* source address			*/
	T_IN4_ADDR	dst;		/* destination address			*/
	} T_TCP_IP4_Q_HDR;

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

typedef struct t_ip_stats {
	uint32_t	ipInReceives;
	uint32_t	ipInHdrErrors;
	uint32_t	ipInAddrErrors;
/*	uint32_t	ipForwDatagrams;*/
	uint32_t	ipInUnknownProtos;
/*	uint32_t	ipInDiscards;*/
	uint32_t	ipInDelivers;
	uint32_t	ipOutRequests;
	uint32_t	ipOutDiscards;
/*	uint32_t	ipOutNoRoutes;*/

#ifdef IP4_CFG_FRAGMENT

	uint32_t	ipReasmReqds;
	uint32_t	ipReasmOKs;
	uint32_t	ipReasmFails;
	uint32_t	ipFragOKs;
	uint32_t	ipFragFails;
	uint32_t	ipFragCreates;

#else	/* of #ifdef IP4_CFG_FRAGMENT */

	uint32_t	ipReasmReqds;
/*	uint32_t	ipReasmOKs;*/
	uint32_t	ipReasmFails;
/*	uint32_t	ipFragOKs;*/
/*	uint32_t	ipFragFails;*/
/*	uint32_t	ipFragCreates;*/

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

} T_IP_STATS;

extern T_IP_STATS ip_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �֐�
 */

extern void ip_frag_timer (void);
extern void ip_init (void);
extern ER ip_remove_options (T_NET_BUF *nbuf);
extern ER ip_output (T_NET_BUF *nbuf, TMO tmout);

#endif	/* of #ifndef _IP_VAR_H_ */
