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
 *  @(#) $Id: ip6.h,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet/ip6.h,v 1.2.2.2 2001/07/03 11:01:46 ume Exp $	*/
/*	$KAME: ip6.h,v 1.18 2001/03/29 05:34:30 itojun Exp $	*/

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
 *	@(#)ip.h	8.1 (Berkeley) 6/10/93
 */
 
#ifndef _IP6_H_
#define _IP6_H_

#ifdef SUPPORT_INET6

/*
 *  IPv6 �̒�`�ARFC2460 �Q��
 */

#define IPV6_VERSION	6

/*
 *  IPv6 �w�b�_�̒�`
 */

typedef struct t_ip6_hdr {
	uint32_t	vcf;		/* Version:        4 bit		*/
					/* Traffic Class:  8 bit		*/
					/* Flow Label:    20 bit		*/
	uint16_t	plen;		/* Payload Length			*/
	uint8_t		next;		/* Next Header				*/
	uint8_t		hlim;		/* Hop Limit				*/
	T_IN6_ADDR 	src;		/* Source Address			*/
	T_IN6_ADDR 	dst;		/* Destination Address			*/
	} T_IP6_HDR;

#define IP6_HDR_SIZE		(sizeof(T_IP6_HDR))

/*
 *  IPv6 �w�b�_�\���̃����o�A�N�Z�X�}�N��
 */

#define IP6_MAKE_VCF(v,cf)	(((uint32_t)(v)<<28)|(cf))
#define IP6_VCF_V(vcf)		((uint32_t)(vcf)>>28)
#define IP6_VCF_C(vcf)		(((uint32_t)(vcf)>>20)&ULONG_C(0xff))
#define IP6_VCF_F(vcf)		((uint32_t)(vcf)&ULONG_C(0x000fffff))
#define IP6_VCF_CF(vcf)		((uint32_t)(vcf)&ULONG_C(0x0fffffff))

/*
 *  �g���w�b�_
 */

typedef struct t_ip6_ext_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �I�N�e�b�g�P�ʂ̒���	*/
	} T_IP6_EXT_HDR;

/*
 *  ���p�_ (Hop-by-Hop) �I�v�V�����w�b�_
 */

typedef struct t_ip6_hbh_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �I�N�e�b�g�P�ʂ̒����B�������A
					 * ���̃I�v�V�����w�b�_�S�̂̃I�N�e�b�g����
					 * 8 �Ŋ������l�� - 1 ������B
					 */
	} T_IP6_HBH_HDR;

/*
 *  �I�_ (Destination) �I�v�V�����w�b�_
 */

typedef struct t_ip6_dest_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �I�N�e�b�g�P�ʂ̒����B�������A
					 * ���̃I�v�V�����w�b�_�S�̂̃I�N�e�b�g����
					 * 8 �Ŋ������l�� - 1 ������B
					 */
	} T_IP6_DEST_HDR;

/* ���p�_ (Hop-by-Hop) �I�v�V���� */

#define IP6OPT_PAD1		UINT_C(0x00)	/* 00 0 00000 */
#define IP6OPT_PADN		UINT_C(0x01)	/* 00 0 00001 */
#define IP6OPT_JUMBO		UINT_C(0xc2)	/* 11 0 00010 */
#define IP6OPT_NSAP_ADDR	UINT_C(0xc3)	/* 11 0 00011 */
#define IP6OPT_TUNNEL_LIMIT	UINT_C(0x04)	/* 00 0 00100 */
#define IP6OPT_RTR_ALERT	UINT_C(0x05)	/* 00 0 00101 */

#define IP6OPT_MINLEN		2	/* �I�v�V�����̍ŒZ��		*/

/* ���m�̃I�v�V�����̏����̎w�� */

#define IP6OPT_TYPE_SKIP	UINT_C(0x00)	/* ��������B			*/
#define IP6OPT_TYPE_DISCARD	UINT_C(0x40)	/* �f�[�^�O������j������B	*/
#define IP6OPT_TYPE_FORCEICMP	UINT_C(0x80)	/* �j�����āAICMP ��ԑ�����B	*/
#define IP6OPT_TYPE_ICMP	UINT_C(0xc0)
		/* �j�����āA�}���`�L���X�g�łȂ���� ICMP ��ԑ�����B	*/

#define IP6OPT_TYPE(o)		((o)&UINT_C(0xc0))

/*
 *  �o�H����w�b�_
 */

typedef struct t_ip6_rt_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �I�N�e�b�g�P�ʂ̒����B�������A
					 * ���̃I�v�V�����w�b�_�S�̂̃I�N�e�b�g����
					 * 8 �Ŋ������l�� - 1 ������B
					 */
	uint8_t		type;		/* �o�H����^�C�v		*/
	uint8_t		segleft;	/* �Z�O�����g�̎c��		*/
	} T_IP6_RT_HDR;

/*
 *  �^�C�v 0 �o�H����w�b�_
 */

typedef struct t_ip6_rt0_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		len;		/* 8 �I�N�e�b�g�P�ʂ̒����B�������A
					 * ���̃I�v�V�����w�b�_�S�̂̃I�N�e�b�g����
					 * 8 �Ŋ������l�� - 1 ������B
					 */
	uint8_t		type;		/* �o�H����^�C�v		*/
	uint8_t		segleft;	/* �Z�O�����g�̎c��		*/
	uint32_t	reserved;	/* �\��				*/
	} T_IP6_RT0_HDR;

/*
 *  �f�Ѓw�b�_
 */

typedef struct t_ip6_frag_hdr {
	uint8_t		next;		/* Next Header			*/
	uint8_t		reserved;
	uint16_t	off_flag;	/* �I�t�Z�b�g�ƃt���O		*/
	uint32_t	ident;		/* �������ʎq			*/
	} T_IP6_FRAG_HDR;

/* �f�Ѓw�b�_�̃I�t�Z�b�g�ƃt���O */

#ifdef _NET_CFG_BYTE_ORDER

#if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN

#define IP6F_OFF_MASK		UINT_C(0xfff8)		/* �I�t�Z�b�g����o���}�X�N	*/
#define IP6F_RESERVED_MASK	UINT_C(0x0006)		/* �\�����o���}�X�N		*/
#define IP6F_MORE_FRAG		UINT_C(0x0001)		/* ���ԃt���O�����g		*/

#elif _NET_CFG_BYTE_ORDER == _NET_CFG_LITTLE_ENDIAN

#define IP6F_OFF_MASK		UINT_C(0xf8ff)		/* �I�t�Z�b�g����o���}�X�N	*/
#define IP6F_RESERVED_MASK	UINT_C(0x0600)		/* �\�����o���}�X�N		*/
#define IP6F_MORE_FRAG		UINT_C(0x0100)		/* ���ԃt���O�����g		*/

#endif	/* #if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN */

#endif	/* of #ifdef _NET_CFG_BYTE_ORDER */

/*
 *  �����l
 */

#define IPV6_MAXHLIM	UINT_C(255)	/* �z�b�v���~�b�g�̍ő�l				*/
#define IPV6_DEFHLIM	UINT_C(64)	/* �z�b�v���~�b�g�̋K��l				*/
#define IPV6_FRAGTTL	UINT_C(60)	/* �������ꂽ�f�[�^�O�����̐������ԁi�b�j	*/
#define IPV6_MMTU	UINT_C(1280)	/* �ŏ� MTU�B�y�C���[�h (1024) + �w�b�_ (256)	*/
#define IPV6_MAXPACKET	UINT_C(65535)	/* �W�����{�y�C���[�h�������ő�p�P�b�g�T�C�Y	*/

/*
 *  IPv4 �� IPv6 ���R���p�C�����ɑI�����邽�߂̃}�N��
 */

/*
 *  �z�b�v���~�b�g�̋K��l�́A���[�^�ʒm�ɂ��ύX����邱�Ƃ�����
 */

#if NUM_ND6_DEF_RTR_ENTRY > 0

/* ���[�^�ʒm����M����ꍇ�́A�ʒm���ꂽ�l */

#define IP_DEFTTL	ip6_defhlim

#else	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/* ���[�^�ʒm����M���Ȃ��ꍇ�̒l�͊���l */

#define IP_DEFTTL	IPV6_DEFHLIM

#endif	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

#define IP_HDR_SIZE	IP6_HDR_SIZE
#define T_IP_HDR	T_IP6_HDR

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _IP6_H_ */
