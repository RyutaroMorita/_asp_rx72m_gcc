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
 *  @(#) $Id: ethernet.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
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
 * Fundamental constants relating to ethernet.
 *
 * $FreeBSD: src/sys/net/ethernet.h,v 1.9.2.1 1999/08/29 16:28:13 peter Exp $
 *
 */

#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#ifdef SUPPORT_ETHER

/*
 *  �t�B�[���h��
 */

#define ETHER_ADDR_LEN		6	/* Ethernet (MAC) Address	*/
#define ETHER_TYPE_LEN		2	/* Type		*/
#define ETHER_CRC_LEN		4	/* CRC		*/

/*
 *  �t���[���� (Ethernet �w�b�_�� CRC ���܂�)
 */

#define ETHER_MIN_LEN		64
#define ETHER_MAX_LEN		(IF_MTU + sizeof(T_ETHER_HDR) + ETHER_CRC_LEN)

/*
 *  Ethernet �w�b�_
 */

#ifndef IF_ETHER_NIC_HDR_ALIGN
#error IF_ETHER_NIC_HDR_ALIGN expected.
#endif	/* of #ifndef IF_ETHER_NIC_HDR_ALIGN */

typedef struct t_ether_header {

#if IF_ETHER_NIC_HDR_ALIGN != 0

	uint8_t		align[IF_ETHER_NIC_HDR_ALIGN];	/* �A���C������ */

#endif	/* of #if IF_ETHER_NIC_HDR_ALIGN != 0 */

	uint8_t		dhost[ETHER_ADDR_LEN];
	uint8_t		shost[ETHER_ADDR_LEN];
	uint16_t	type;
	} __attribute__((packed))T_ETHER_HDR;

#define GET_ETHER_HDR(nbuf)		((T_ETHER_HDR*)((nbuf)->buf))

/*
 *  MAC �A�h���X�̒�`
 */

#define ETHER_MCAST_ADDR	UINT_C(0x01)	/* �}���`�L���X�g�E�A�h���X	*/
#define ETHER_LOCAL_ADDR	UINT_C(0x02)	/* ���[�J���E�A�h���X		*/

typedef struct t_ether_addr {
	uint8_t		lladdr[ETHER_ADDR_LEN];
	} T_ETHER_ADDR;

/*
 *  Type �t�B�[���h
 */

#define ETHER_TYPE_IP		UINT_C(0x0800)	/* IPv4	*/
#define ETHER_TYPE_ARP		UINT_C(0x0806)	/* ARP	*/
#define ETHER_TYPE_IPV6		UINT_C(0x86dd)	/* IPv6	*/

/*
 *  �C���^�t�F�[�X�̑I���}�N��
 */

#define T_IF_HDR		T_ETHER_HDR		/* �C���^�t�F�[�X�̃w�b�_				*/
#define T_IF_ADDR		T_ETHER_ADDR		/* �C���^�t�F�[�X�̃A�h���X			*/
#define IF_HDR_ALIGN		2			/* �w�b�_�̃A���C���P��				*/
#define IF_MTU			1500			/* �C���^�t�F�[�X�� MTU				*/

#define IF_OUTPUT(o,d,g,t)	ether_output(o,d,g,t)	/* �C���^�t�F�[�X�̏o�͊֐�			*/
#define IF_RAW_OUTPUT(o,t)	ether_raw_output(o,t)	/* �C���^�t�F�[�X�̏o�͊֐��A�A�h���X��������	*/
#define IF_SET_PROTO(b,p)	(GET_ETHER_HDR(b)->type = htons(p))
							/* �C���^�t�F�[�X�̃v���g�R���ݒ�֐�		*/
#define IF_SOFTC_TO_IFADDR(s)	((T_IF_ADDR*)(s)->ifaddr.lladdr)
							/* �\�t�g�E�F�A��񂩂� MAC �A�h���X�����o��	*/
#define IF_GET_IFNET()		ether_get_ifnet()	/* �l�b�g���[�N�C���^�t�F�[�X�\���̂�Ԃ��B		*/
#define IF_TYPE			IFT_ETHER		/* �C���^�[�t�F�[�X�̌^				*/

/* IPv4 �֌W */

#define IF_PROTO_IP		ETHER_TYPE_IP		/* �C���^�t�F�[�X�� IP �v���g�R���w��		*/
#define IF_PROTO_ARP		ETHER_TYPE_ARP		/* �C���^�t�F�[�X�� ARP �v���g�R���w��		*/

/* IPv6 �֌W */

#define MAX_IF_MADDR_CNT	2			/* �C���^�t�F�[�X�̃}���`�L���X�g�A�h���X�z��̍ő�T�C�Y	*/
#define IF_MADDR_INIT		{ { { 0, 0, 0, 0, 0, 0 } }, { { 0, 0, 0, 0, 0, 0 } } }
							/* �C���^�t�F�[�X�̃}���`�L���X�g�A�h���X�z��̏�����	*/
#define IF_PROTO_IPV6		ETHER_TYPE_IPV6		/* �C���^�t�F�[�X�� IP �v���g�R���w��			*/
#define IF_ADDMULTI(s)		IF_ETHER_NIC_ADDMULTI(s)
							/* �}���`�L���X�g�A�h���X�̓o�^				*/
#define IF_IN6_NEED_CACHE(i)	(true)			/* �ߗגT���L���b�V�����g�p����B				*/
#define IF_IN6_IFID(i,a)	IF_ETHER_NIC_IN6_IFID(i,a)
							/* �C���^�t�F�[�X���ʎq�̐ݒ�				*/
#define IF_IN6_RESOLVE_MULTICAST(i,m)	\
				ether_in6_resolve_multicast(i,m)
							/* �C���^�t�F�[�X�̃}���`�L���X�g�A�h���X�ւ̕ϊ�		*/

#ifdef SUPPORT_E1
#define IF_SET_MACADDR(a)	ether_set_lladdr(a)
#endif

/*
 *  �O���Q��
 */

#ifndef T_IFNET_DEFINED

typedef struct t_ifnet T_IFNET;

#define T_IFNET_DEFINED

#endif	/* of #ifndef T_IFNET_DEFINED */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_IN4_ADDR_DEFINED

typedef uint32_t T_IN4_ADDR;

#define T_IN4_ADDR_DEFINED

#endif	/* of #ifndef T_IN4_ADDR_DEFINED */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�Ɉˑ����Ȃ��\�t�g�E�F�A���
 */

#ifdef T_IF_ETHER_NIC_SOFTC

struct t_if_softc {
	T_IF_ADDR		ifaddr;			/* �l�b�g���[�N�C���^�t�F�[�X�̃A�h���X	*/
	uint16_t		timer;			/* ���M�^�C���A�E�g			*/
	T_IF_ETHER_NIC_SOFTC	*sc;			/* �f�B�o�C�X�ˑ��̃\�t�g�E�F�A���	*/
	ID			semid_txb_ready;	/* ���M�Z�}�t�H				*/
	ID			semid_rxb_ready;	/* ��M�Z�}�t�H				*/

#ifdef SUPPORT_INET6

	T_IF_ADDR 	maddrs[MAX_IF_MADDR_CNT];	/* �}���`�L���X�g�A�h���X���X�g	*/

#endif	/* of #ifdef SUPPORT_INET6 */
	};

#endif	/* of #ifdef T_IF_ETHER_NIC_SOFTC */

#ifdef SUPPORT_INET6

/* �O���Q�� */

#ifndef T_IN6_ADDR_DEFINED

typedef struct t_in6_addr T_IN6_ADDR;

#define T_IN6_ADDR_DEFINED

#endif	/* of #ifndef T_IN6_ADDR_DEFINED */

/*
 *  �֐�
 */

extern ER ether_in6_resolve_multicast(T_ETHER_ADDR *ifaddr, T_IN6_ADDR *maddr);

#endif	/* of #ifdef SUPPORT_INET6 */

/*
 *  �֐�
 */

extern T_IFNET *ether_get_ifnet (void);
extern ER ether_output (T_NET_BUF *data, void *dst, T_IF_ADDR *gw, TMO tmout);
extern ER ether_raw_output (T_NET_BUF *data, TMO tmout);
#ifdef SUPPORT_E1
extern void ether_set_lladdr (uint8_t* p);
#endif

#endif	/* of #ifdef SUPPORT_ETHER */

#endif	/* of #ifndef _ETHERNET_H_ */
