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
 *  @(#) $Id: icmp6.h,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet/icmp6.h,v 1.2.2.3 2001/07/06 05:36:35 sumikawa Exp $	*/
/*	$KAME: icmp6.h,v 1.46 2001/04/27 15:09:48 itojun Exp $	*/

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
 *	@(#)ip_icmp.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _IP_ICMP6_H_
#define _IP_ICMP6_H_

#ifdef SUPPORT_INET6

/*
 *  ICMPv6 �w�b�_
 */

typedef struct t_icmp6_hdr {
	uint8_t		type;		/* ���b�Z�[�W�̌^	*/
	uint8_t		code;		/* �T�u�^		*/
	uint16_t	sum;		/* �`�F�b�N�T��		*/
	union {
		uint32_t	data32;
		uint16_t	data16[2];
		uint8_t		data8[4];
		} data;
	} T_ICMP6_HDR;

#define icmp6_data32			data.data32
#define icmp6_data16			data.data16
#define icmp6_data8			data.data8
#define icmp6_pptr			data.data32		/* �p�����[�^�ُ�	*/
#define icmp6_mtu			data.data32		/* �p�����[�^�ُ�	*/
#define icmp6_id			data.data16[0]		/* �G�R�[�v���Ɖ���	*/
#define icmp6_seq			data.data16[1]		/* �G�R�[�v���Ɖ���	*/

#define ICMP6_HDR_SIZE			(sizeof(T_ICMP6_HDR))
#define IF_IP6_ICMP6_HDR_OFFSET		(IF_IP6_HDR_SIZE)

#define GET_ICMP6_HDR(nbuf,ihoff)	((T_ICMP6_HDR*)((uint8_t*)((nbuf)->buf) + ihoff))
#define GET_ICMP6_SDU(nbuf,ihoff)	((uint8_t*)((nbuf)->buf) + ihoff + ICMP6_HDR_SIZE)

#define GET_IP6_ICMP6_HDR_SIZE(nbuf)	(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + ICMP6_HDR_SIZE)
#define GET_IF_IP6_ICMP6_HDR_SIZE(nbuf)	(IF_HDR_SIZE + GET_IP6_ICMP6_HDR_SIZE(nbuf))

/*
 *  ICMP6 �^�C�v
 */

#define ICMP6_DST_UNREACH		UINT_C(1)	/* ���擞�B�s�\		*/
#define ICMP6_PACKET_TOO_BIG		UINT_C(2)	/* �p�P�b�g���傫������B	*/
#define ICMP6_TIME_EXCEEDED		UINT_C(3)	/* TTL �𒴉߂����B		*/
#define ICMP6_PARAM_PROB		UINT_C(4)	/* IPv6 �w�b�_���s���B		*/

#define ICMP6_ECHO_REQUEST		UINT_C(128)	/* �G�R�[�v��			*/
#define ICMP6_ECHO_REPLY		UINT_C(129)	/* �G�R�[����			*/

#define ICMP6_MEMBERSHIP_QUERY		UINT_C(130)	/* �O���[�v�����o�Ɖ�		*/
#define ICMP6_MEMBERSHIP_REPORT		UINT_C(131)	/* �O���[�v�����o��		*/
#define ICMP6_MEMBERSHIP_REDUCTION	UINT_C(132)	/* �O���[�v�����o�I��		*/

#define MLD_LISTENER_QUERY		UINT_C(130)	/* �}���`�L���X�g��M�ҏƉ�	*/
#define MLD_LISTENER_REPORT		UINT_C(131)	/* �}���`�L���X�g��M�ҕ�	*/
#define MLD_LISTENER_DONE		UINT_C(132)	/* �}���`�L���X�g��M�ҏI��	*/

#define ND_ROUTER_SOLICIT		UINT_C(133)	/* ���[�^�v��			*/
#define ND_ROUTER_ADVERT		UINT_C(134)	/* ���[�^�ʒm			*/
#define ND_NEIGHBOR_SOLICIT		UINT_C(135)	/* �ߗחv��			*/
#define ND_NEIGHBOR_ADVERT		UINT_C(136)	/* �ߗגʒm			*/
#define ND_REDIRECT			UINT_C(137)	/* ��������			*/

#define ICMP6_ROUTER_RENUMBERING	UINT_C(138)	/* ���[�^�ԍ��Đݒ�		*/

#define ICMP6_WRU_REQUEST		UINT_C(139)	/* �v���m�[�h�T��		*/
#define ICMP6_WRU_REPLY			UINT_C(140)	/* �����m�[�h�T��		*/

#define ICMP6_FQDN_QUERY		UINT_C(139)	/* FQDN �Ɖ�			*/
#define ICMP6_FQDN_REPLY		UINT_C(140)	/* FQDN ����			*/

#define ICMP6_NI_QUERY			UINT_C(139)	/* �m�[�h���Ɖ�		*/
#define ICMP6_NI_REPLY			UINT_C(140)	/* �m�[�h��񉞓�		*/

#define ICMP6_MAX_TYPE			UINT_C(203)	/* ICMP6 �^�C�v�̍ő�l		*/

/*
 *  ICMP6 �R�[�h
 */

/* ���擞�B�s�\ */

#define ICMP6_DST_UNREACH_NOROUTE	UINT_C(0)	/* ���B���[�g�Ȃ��B		*/
#define ICMP6_DST_UNREACH_ADMIN		UINT_C(1)	/* �Ǘ��҂ɂ�薳�������B	*/
#define ICMP6_DST_UNREACH_NOTEIGHBOR	UINT_C(2)	/* �ߗ׎҂ł͂Ȃ��Ȃ����B	*/
#define ICMP6_DST_UNREACH_BEYOND_SCOPE	UINT_C(2)	/* �X�R�[�v�𒴂��Ă���B	*/
#define ICMP6_DST_UNREACH_ADDR		UINT_C(3)	/* ����A�h���X�ɓ��B�s�\�B	*/
#define ICMP6_DST_UNREACH_NOPORT	UINT_C(4)	/* ����|�[�g�ɓ��B�s�\�B	*/

/* TTL ���� */

#define ICMP6_TIME_EXCEED_TRANSIT	UINT_C(0)	/* �]������ TTL==0 �ɂȂ����B	*/
#define ICMP6_TIME_EXCEED_REASSEMBLY	UINT_C(1)	/* IP �č\���Ń^�C���A�E�g�����B*/

/* �w�b�_�s�� */

#define ICMP6_PARAMPROB_HEADER		UINT_C(0)	/* �w�b�_�ɕs�����������B	*/
#define ICMP6_PARAMPROB_NEXT_HEADER	UINT_C(1)	/* ���w�b�_���F���ł��Ȃ��B	*/
#define ICMP6_PARAMPROB_OPTION		UINT_C(2)	/* �I�v�V�������F���ł��Ȃ��B	*/

/* �����g�p */
#define ND_REDIRECT_ONLINK		UINT_C(0)	/* �I�������N�ւ̌�������	*/
#define ND_REDIRECT_ROUTER		UINT_C(1)	/* ���[�^�ւ̌�������		*/

/*
 *  �����l
 */

							/* ICMPv6 �̍ő�y�C���[�h��	*/
#define ICMPV6_PAYLOAD_MAXLEN		(IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE))

/*
 *  �ߗחv��
 */

typedef struct t_neighbor_solicit_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;
	/* ���̌�ɃI�v�V���������� */
	} T_NEIGHBOR_SOLICIT_HDR;

#define NEIGHBOR_SOLICIT_HDR_SIZE	(sizeof(T_NEIGHBOR_SOLICIT_HDR))
#define IF_IP6_NEIGHBOR_SOLICIT_HDR_OFFSET	\
					(IF_IP6_HDR_SIZE)

#define GET_NEIGHBOR_SOLICIT_HDR(nbuf,nhoff)	\
					((T_NEIGHBOR_SOLICIT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_NEIGHBOR_SOLICIT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + NEIGHBOR_SOLICIT_HDR_SIZE)

#define GET_IP6_NEIGHBOR_SOLICIT_HDR_SIZE(nbuf)		\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + NEIGHBOR_SOLICIT_HDR_SIZE)
#define GET_IF_IP6_NEIGHBOR_SOLICIT_HDR_SIZE(nbuf)	\
					(GET_IP6_NEIGHBOR_SOLICIT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  �ߗגʒm
 */

typedef struct t_neighbor_advert_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;
	/* ���̌�ɃI�v�V���������� */
	} T_NEIGHBOR_ADVERT_HDR;

/* ICMP6 �w�b�_�̃f�[�^���̒�` */

#define nd_na_flags_reserved		hdr.data.data32

#define NEIGHBOR_ADVERT_HDR_SIZE	(sizeof(T_NEIGHBOR_ADVERT_HDR))
#define IP6_NEIGHBOR_ADVERT_HDR_SIZE	(IP6_HDR_SIZE + NEIGHBOR_ADVERT_HDR_SIZE)
#define IF_IP6_NEIGHBOR_ADVERT_HDR_SIZE	\
					(IF_IP6_HDR_SIZE + NEIGHBOR_ADVERT_HDR_SIZE)
#define IF_IP6_NEIGHBOR_ADVERT_HDR_OFFSET	\
					(IF_IP6_HDR_SIZE)

#define GET_NEIGHBOR_ADVERT_HDR(nbuf,nhoff)	\
					((T_NEIGHBOR_ADVERT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_NEIGHBOR_ADVERT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + NEIGHBOR_ADVERT_HDR_SIZE)

#define GET_IP6_NEIGHBOR_ADVERT_HDR_SIZE(nbuf)		\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + NEIGHBOR_ADVERT_HDR_SIZE)
#define GET_IF_IP6_NEIGHBOR_ADVERT_HDR_SIZE(nbuf)	\
					(GET_IP6_NEIGHBOR_ADVERT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  �ߗגʒm�t���O�And_na_flags_reserved (hdr.data32) �ɐݒ肷��B
 */

#if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN

#define ND_NA_FLG_OVERRIDE		ULONG_C(0x20000000)	/* �ߗ׃L���b�V���㏑��	*/
#define ND_NA_FLG_SOLICITED		ULONG_C(0x40000000)	/* �ߗחv���ւ̉���	*/
#define ND_NA_FLG_ROUTER		ULONG_C(0x80000000)	/* ���[�^�ʒm		*/

#elif _NET_CFG_BYTE_ORDER == _NET_CFG_LITTLE_ENDIAN

#define ND_NA_FLG_OVERRIDE		ULONG_C(0x00000020)	/* �ߗ׃L���b�V���㏑��	*/
#define ND_NA_FLG_SOLICITED		ULONG_C(0x00000040)	/* �ߗחv���ւ̉���	*/
#define ND_NA_FLG_ROUTER		ULONG_C(0x00000080)	/* ���[�^�ʒm		*/

#endif	/* #if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN */

/*
 *  ���[�^�ʒm
 */

typedef struct t_router_advert_hdr {
	T_ICMP6_HDR	hdr;
	uint32_t	reachable;		/* [ms] ���B�\����	*/
	uint32_t	retransmit;		/* [ms] �ߗחv�����M�Ԋu	*/
	/* ���̌�ɃI�v�V���������� */
	} T_ROUTER_ADVERT_HDR;

/* ICMP6 �w�b�_�̃f�[�^���̒�` */

#define nd_ra_current_hoplimit		hdr.data.data8[0]
#define nd_ra_flags			hdr.data.data8[1]
#define nd_ra_router_lifetime		hdr.data.data16[1]	/* [s] ���[�^�L������	*/

#define ROUTER_ADVERT_HDR_SIZE		(sizeof(T_ROUTER_ADVERT_HDR))
#define IP6_ROUTER_ADVERT_HDR_SIZE	(IP6_HDR_SIZE + ROUTER_ADVERT_HDR_SIZE)
#define IF_IP6_ROUTER_ADVERT_HDR_SIZE	(IF_IP6_HDR_SIZE + ROUTER_ADVERT_HDR_SIZE)
#define IF_IP6_ROUTER_ADVERT_HDR_OFFSET	(IF_IP6_HDR_SIZE)

#define GET_ROUTER_ADVERT_HDR(nbuf,nhoff)	\
					((T_ROUTER_ADVERT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_ROUTER_ADVERT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + ROUTER_ADVERT_HDR_SIZE)

#define GET_IP6_ROUTER_ADVERT_HDR_SIZE(nbuf)	\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + ROUTER_ADVERT_HDR_SIZE)
#define GET_IF_IP6_ROUTER_ADVERT_HDR_SIZE(nbuf)	\
					(GET_IP6_ROUTER_ADVERT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  ���[�^�ʒm�w�b�_�̃t���O
 */

#define ND_RA_FLAG_MANAGED		UINT_C(0x80)
#define ND_RA_FLAG_OTHER		UINT_C(0x40)
#define ND_RA_FLAG_HA			UINT_C(0x20)

/*
 *  ���[�^�v��
 */

typedef struct t_router_solicit_hdr {
	T_ICMP6_HDR	hdr;
	} T_ROUTER_SOLICIT_HDR;

/* ICMP6 �w�b�_�̃f�[�^���̒�` */

#define nd_rs_reserved			hdr.data.data32

#define ROUTER_SOLICIT_HDR_SIZE		(sizeof(T_ROUTER_SOLICIT_HDR))
#define IP6_ROUTER_SOLICIT_HDR_SIZE	(IP6_HDR_SIZE + ROUTER_SOLICIT_HDR_SIZE)
#define IF_IP6_ROUTER_SOLICIT_HDR_SIZE	(IF_IP6_HDR_SIZE + ROUTER_SOLICIT_HDR_SIZE)
#define IF_IP6_ROUTER_SOLICIT_HDR_OFFSET	\
					(IF_IP6_HDR_SIZE)

#define GET_ROUTER_SOLICIT_HDR(nbuf,nhoff)	\
					((T_ROUTER_SOLICIT_HDR*)((uint8_t*)((nbuf)->buf) + nhoff))
#define GET_ROUTER_SOLICIT_SDU(nbuf,nhoff)	\
					((uint8_t*)((nbuf)->buf) + nhoff + ROUTER_SOLICIT_HDR_SIZE)

#define GET_IP6_ROUTER_SOLICIT_HDR_SIZE(nbuf)		\
					(GET_IP6_HDR_SIZE(GET_IP6_HDR(nbuf)) + ROUTER_SOLICIT_HDR_SIZE)
#define GET_IF_IP6_ROUTER_SOLICIT_HDR_SIZE(nbuf)	\
					(GET_IP6_ROUTER_SOLICIT_HDR_SIZE(nbuf) + IF_HDR_SIZE)

/*
 *  �ߗגT���I�v�V����
 */

/* �ߗגT���w�b�_ */

typedef struct t_neighbor_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;
	} T_NEIGHBOR_HDR;

/* �ߗגT���I�v�V�����w�b�_ */

typedef struct t_nd_opt_hdr {
	uint8_t		type;			/* �I�v�V�����^�C�v			*/
	uint8_t		len;			/* �I�v�V�������A�P�ʂ� 8 �o�C�g	*/
	} T_ND_OPT_HDR;

#define ND_OPT_HDR_SIZE			(sizeof(T_ND_OPT_HDR))

#define ND_OPT_SOURCE_LINKADDR		UINT_C(1)	/* ���M��l�b�g���[�N�C���^�t�F�[�X�̃A�h���X	*/
#define ND_OPT_TARGET_LINKADDR		UINT_C(2)	/* �Ώۃl�b�g���[�N�C���^�t�F�[�X�̃A�h���X	*/
#define ND_OPT_PREFIX_INFORMATION	UINT_C(3)	/* �v���t�B�b�N�X���				*/
#define ND_OPT_REDIRECTED_HEADER	UINT_C(4)	/* ���_�C���N�g�E�w�b�_				*/
#define ND_OPT_MTU			UINT_C(5)	/* MTU						*/

#define ND_OPT_PREFIX_INFO_COUNT	UINT_C(6)	/* �v���t�B�b�N�X���̌�			*/
#define ND_OPT_OFF_ARRAY_SIZE		UINT_C(7)	/* ND �I�v�V�����̃I�t�Z�b�g���L�^����z��T�C�Y*/

#define ND_OPT_OFF_ARRAY_IX(t)		((t)-1)		/* �I�t�Z�b�g�z��̃C���f�b�N�X			*/

/* �v���t�B�b�N�X�I�v�V���� */

typedef struct t_nd_opt_prefix_info {
	uint8_t		type;		/* �ߗגT���I�v�V�����^�C�v = 3	*/
	uint8_t		len;		/* �I�v�V������ = 8�~4=32	*/
	uint8_t		prefix_len;	/* �v���t�B�b�N�X��		*/
	uint8_t		flags;		/* �t���O			*/
	uint32_t	valid;		/* [s] �L������			*/
	uint32_t	preferred;	/* [s] �����L������		*/
	uint32_t	reserved;
	T_IN6_ADDR	prefix;		/* �v���t�B�b�N�X		*/
	} T_ND_OPT_PREFIX_INFO;

#define ND_OPT_PI_FLAG_ONLINK	UINT_C(0x80)		/* �I�������N�v���t�B�b�N�X	*/
#define ND_OPT_PI_FLAG_AUTO	UINT_C(0x40)		/* �X�e�[�g���X�E�A�h���X�����ݒ�*/

/* MTU �I�v�V�����w�b�_ */

typedef struct t_nd_opt_mtu_hdr {
	uint8_t		type;		/* �I�v�V�����^�C�v		*/
	uint8_t		len;		/* �I�v�V�������A�P�ʂ� 8 �o�C�g*/
	uint16_t	reserved;
	uint32_t	mtu;		/* MTU				*/
	} T_ND_OPT_MTU_HDR;

/*
 *  ��������
 */

typedef struct t_nd_redirect_hdr {
	T_ICMP6_HDR	hdr;
	T_IN6_ADDR	target;		/* ���[�^�̃A�h���X		*/
	T_IN6_ADDR	dst;		/* ���������̏I�_�A�h���X		*/
	/* ���̌�ɃI�v�V���������� */
	} T_ND_REDIRECT_HDR;

#define ND_REDIRECT_HDR_SIZE		(sizeof(T_ND_REDIRECT_HDR))

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

typedef struct t_icmp6_ifstat {
	uint32_t	ipv6IfIcmpInMsgs;
	uint32_t	ipv6IfIcmpInErrors;
	uint32_t	ipv6IfIcmpInDestUnreachs;
/*	uint32_t	ipv6IfIcmpInAdminProhibs;*/
	uint32_t	ipv6IfIcmpInTimeExcds;
	uint32_t	ipv6IfIcmpInParmProblems;
	uint32_t	ipv6IfIcmpInPktTooBigs;
	uint32_t	ipv6IfIcmpInEchos;
	uint32_t	ipv6IfIcmpInEchoReplies;
/*	uint32_t	ipv6IfIcmpInRouterSolicits;*/
	uint32_t	ipv6IfIcmpInRouterAdvertisements;
	uint32_t	ipv6IfIcmpInNeighborSolicits;
	uint32_t	ipv6IfIcmpInNeighborAdvertisements;
	uint32_t	ipv6IfIcmpInRedirects;
/*	uint32_t	ipv6IfIcmpInGroupMembQueries;*/
/*	uint32_t	ipv6IfIcmpInGroupMembResponses;*/
/*	uint32_t	ipv6IfIcmpInGroupMembReductions;*/
	uint32_t	ipv6IfIcmpOutMsgs;
	uint32_t	ipv6IfIcmpOutErrors;
	uint32_t	ipv6IfIcmpOutDestUnreachs;
/*	uint32_t	ipv6IfIcmpOutAdminProhibs;*/
/*	uint32_t	ipv6IfIcmpOutTimeExcds;*/
	uint32_t	ipv6IfIcmpOutParmProblems;
	uint32_t	ipv6IfIcmpOutPktTooBigs;
	uint32_t	ipv6IfIcmpOutEchos;
	uint32_t	ipv6IfIcmpOutEchoReplies;
	uint32_t	ipv6IfIcmpOutRouterSolicits;
/*	uint32_t	ipv6IfIcmpOutRouterAdvertisements;*/
	uint32_t	ipv6IfIcmpOutNeighborSolicits;
	uint32_t	ipv6IfIcmpOutNeighborAdvertisements;
/*	uint32_t	ipv6IfIcmpOutRedirects;*/
/*	uint32_t	ipv6IfIcmpOutGroupMembQueries;*/
/*	uint32_t	ipv6IfIcmpOutGroupMembResponses;*/
/*	uint32_t	ipv6IfIcmpOutGroupMembReductions;*/
} T_ICMP6_IFSTAT;

extern T_ICMP6_IFSTAT icmp6_ifstat;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �֐�
 */

extern uint_t icmp6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern void icmp6_error (T_NET_BUF *input, uint8_t type, uint8_t code, uint32_t param);

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

extern void icmp6_echo_reply (T_NET_BUF *input, uint_t ihoff);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _IP_ICMP6_H_ */
