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
 *  @(#) $Id: net_count.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1994, 1995
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
 */

#ifndef _NET_COUNT_H_
#define _NET_COUNT_H_

/*
 *  �l�b�g���[�N���v���̌v��
 */

#if NET_COUNT_ENABLE != 0

#ifndef _MACRO_ONLY

#ifdef _int64_
typedef uint64_t T_NET_COUNT_VAL;
#else
typedef uint32_t T_NET_COUNT_VAL;
#endif

typedef struct t_net_count {
	T_NET_COUNT_VAL	in_octets;		/* ��M�I�N�e�b�g��	*/
	T_NET_COUNT_VAL	out_octets;		/* ���M�I�N�e�b�g��	*/
	T_NET_COUNT_VAL	in_packets;		/* ��M�o�P�b�g��	*/
	T_NET_COUNT_VAL	out_packets;		/* ���M�o�P�b�g��	*/
	T_NET_COUNT_VAL	in_err_packets;		/* ��M�G���[�o�P�b�g��	*/
	T_NET_COUNT_VAL	out_err_packets;	/* ���M�G���[�o�P�b�g��	*/
	} T_NET_COUNT;

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #if NET_COUNT_ENABLE != 0 */

#ifdef SUPPORT_PPP

/* PPP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP

#define NET_COUNT_PPP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_ppp;
extern T_NET_COUNT_VAL	net_count_ppp_no_bufs;	/* net_buf ���蓖�Ď��s��	*/

#endif	/* of #ifndef _MACRO_ONLY */

#define NC_PPP_SIZE	7			/* �J�E���^�� */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP */

#define NET_COUNT_PPP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP */

/* PPP HDLC */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC

#define NET_COUNT_PPP_HDLC(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_hdlc;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC */

#define NET_COUNT_PPP_HDLC(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC */

/* PPP LCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP

#define NET_COUNT_PPP_LCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_lcp_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_lcp_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP */

#define NET_COUNT_PPP_LCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP */

/* PPP IPCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP

#define NET_COUNT_PPP_IPCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_ipcp_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_ipcp_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP */

#define NET_COUNT_PPP_IPCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP */

/* PPP CCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_CCP

#define NET_COUNT_PPP_CCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_ccp_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_ccp_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_CCP */

#define NET_COUNT_PPP_CCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_CCP */

/* PPP PAP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP

#define NET_COUNT_PPP_PAP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ppp_upap_in_octets;
extern T_NET_COUNT_VAL net_count_ppp_upap_in_packets;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP */

#define NET_COUNT_PPP_PAP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP */

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_LOOP

/* ���[�v�o�b�N */

#if NET_COUNT_ENABLE & PROTO_FLG_LOOP

#define NET_COUNT_LOOP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_loop;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_LOOP */

#define NET_COUNT_LOOP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_LOOP */

#endif	/* of #ifdef SUPPORT_LOOP */

#ifdef SUPPORT_ETHER

/* Ethernet */

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER

#define NET_COUNT_ETHER(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_ether;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER */

#define NET_COUNT_ETHER(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER */

/* NIC (if_ed) */

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC

#define NC_ETHER_NIC_RESETS		0	/* ���Z�b�g��			*/
#define NC_ETHER_NIC_TXB_QOVRS		1	/* ���M�Z�}�t�H�����ԋp����I�[�o�[��*/
#define NC_ETHER_NIC_TIMEOUTS		2	/* ���M�^�C���A�E�g��		*/
#define NC_ETHER_NIC_COLS		3	/* �R���W������			*/
#define NC_ETHER_NIC_OUT_ERR_PACKETS	4	/* ���M�G���[�o�P�b�g��		*/
#define NC_ETHER_NIC_OUT_PACKETS	5	/* ���M�o�P�b�g��		*/
#define NC_ETHER_NIC_OUT_OCTETS		6	/* ���M�I�N�e�b�g��		*/
#define NC_ETHER_NIC_RXB_QOVRS		7	/* ��M�Z�}�t�H�����ԋp����I�[�o�[��*/
#define NC_ETHER_NIC_NO_BUFS		8	/* net_buf ���蓖�Ď��s��	*/
#define NC_ETHER_NIC_IN_ERR_PACKETS	9	/* ��M�G���[�o�P�b�g��		*/
#define NC_ETHER_NIC_IN_PACKETS		10	/* ��M�o�P�b�g��		*/
#define NC_ETHER_NIC_IN_OCTETS		11	/* ��M�I�N�e�b�g��		*/
#define NC_ETHER_NIC_SIZE		12	/* �J�E���^��			*/

#define NET_COUNT_ETHER_NIC(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ether_nic[NC_ETHER_NIC_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC */

#define NET_COUNT_ETHER_NIC(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC */

#endif	/* of #ifdef SUPPORT_ETHER */

/* �l�b�g���[�N�o�b�t�@ */

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

#define NET_COUNT_NET_BUF(v,c)		((v)+=(c))

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

#define NET_COUNT_NET_BUF(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

#if defined(SUPPORT_INET4)

/* ARP */

#if NET_COUNT_ENABLE & PROTO_FLG_ARP

#define NET_COUNT_ARP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_arp;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ARP */

#define NET_COUNT_ARP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ARP */

/* IPv4 */

#if NET_COUNT_ENABLE & PROTO_FLG_IP4

#define NC_IP4_FRAG_OUT_FRAGS		0	/* �������M�A�t���O�����g��	*/
#define NC_IP4_FRAG_OUT			1	/* �������M��			*/
#define NC_IP4_OUT_ERR_PACKETS		2	/* ���M�G���[�f�[�^�O������	*/
#define NC_IP4_OUT_PACKETS		3	/* ���M�f�[�^�O������		*/
#define NC_IP4_OUT_OCTETS		4	/* ���M�I�N�e�b�g��		*/
#define NC_IP4_FRAG_IN_TMOUT		5	/* ������M�^�C���A�E�g��		*/
#define NC_IP4_FRAG_IN_NO_BUF		6	/* ������M�o�b�t�@�蓖�Ď��s��	*/
#define NC_IP4_FRAG_IN_DROP		7	/* ������M�j����		*/
#define NC_IP4_FRAG_IN_OK		8	/* ������M�č\��������		*/
#define NC_IP4_FRAG_IN_FRAGS		9	/* ������M�t���O�����g��		*/
#define NC_IP4_FRAG_IN			10	/* ������M��			*/
#define NC_IP4_OPTS			11	/* �I�v�V�������͐�		*/
#define NC_IP4_IN_ERR_PROTO		12	/* �v���g�R���G���[��		*/
#define NC_IP4_IN_ERR_ADDR		13	/* �A�h���X�G���[��		*/
#define NC_IP4_IN_ERR_VER		14	/* �o�[�W�����G���[��		*/
#define NC_IP4_IN_ERR_SHORT		15	/* �����G���[��			*/
#define NC_IP4_IN_ERR_CKSUM		16	/* �`�F�b�N�T���G���[��		*/
#define NC_IP4_IN_ERR_PACKETS		17	/* ��M�G���[�f�[�^�O������	*/
#define NC_IP4_IN_PACKETS		18	/* ��M�f�[�^�O������		*/
#define NC_IP4_IN_OCTETS		19	/* ��M�I�N�e�b�g��		*/
#define NC_IP4_SIZE			20	/* �J�E���^��			*/

#define NET_COUNT_IP4(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ip4[NC_IP4_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP4 */

#define NET_COUNT_IP4(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP4 */

/* ICMP4 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP4

#define NET_COUNT_ICMP4(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_icmp4;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP4 */

#define NET_COUNT_ICMP4(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP4 */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

/* IPv6 */

#if NET_COUNT_ENABLE & PROTO_FLG_IP6

#define NC_IP6_FRAG_OUT_FRAGS		0	/* �������M�A�t���O�����g��	*/
#define NC_IP6_FRAG_OUT			1	/* �������M��			*/
#define NC_IP6_OUT_ERR_PACKETS		2	/* ���M�G���[�f�[�^�O������	*/
#define NC_IP6_OUT_PACKETS		3	/* ���M�f�[�^�O������		*/
#define NC_IP6_OUT_OCTETS		4	/* ���M�I�N�e�b�g��		*/
#define NC_IP6_FRAG_IN_TMOUT		5	/* ������M�^�C���A�E�g��		*/
#define NC_IP6_FRAG_IN_NO_BUF		6	/* ������M�o�b�t�@�蓖�Ď��s��	*/
#define NC_IP6_FRAG_IN_DROP		7	/* ������M�j����		*/
#define NC_IP6_FRAG_IN_OK		8	/* ������M�č\��������		*/
#define NC_IP6_FRAG_IN_FRAGS		9	/* ������M�t���O�����g��		*/
#define NC_IP6_FRAG_IN			10	/* ������M��			*/
#define NC_IP6_IN_ERR_PROTO		11	/* �v���g�R���G���[��		*/
#define NC_IP6_IN_ERR_ADDR		12	/* �A�h���X�G���[��		*/
#define NC_IP6_IN_ERR_VER		13	/* �o�[�W�����G���[��		*/
#define NC_IP6_IN_ERR_SHORT		14	/* �����G���[��			*/
#define NC_IP6_IN_ERR_PACKETS		15	/* ��M�G���[�f�[�^�O������	*/
#define NC_IP6_IN_PACKETS		16	/* ��M�f�[�^�O������		*/
#define NC_IP6_IN_OCTETS		17	/* ��M�I�N�e�b�g��		*/
#define NC_IP6_SIZE			18	/* �J�E���^��			*/

#define NET_COUNT_IP6(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_ip6[NC_IP6_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP6 */

#define NET_COUNT_IP6(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP6

#define NC_ICMP6_OUT_ERR_PACKETS	0	/* ���M�G���[ ICMP �f�[�^��	*/
#define NC_ICMP6_OUT_PACKETS		1	/* ���M ICMP �f�[�^��		*/
#define NC_ICMP6_OUT_OCTETS		2	/* ���M ICMP �I�N�e�b�g��		*/
#define NC_ICMP6_IN_ERR_CKSUM		3	/* �����G���[��			*/
#define NC_ICMP6_IN_ERR_PACKETS		4	/* ��M�G���[ ICMP �f�[�^��	*/
#define NC_ICMP6_IN_PACKETS		5	/* ��M ICMP �f�[�^��		*/
#define NC_ICMP6_IN_OCTETS		6	/* ��M ICMP �I�N�e�b�g��		*/
#define NC_ICMP6_SIZE			7	/* �J�E���^��			*/

#define NET_COUNT_ICMP6(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL	net_count_icmp6[NC_ICMP6_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP6 */

#define NET_COUNT_ICMP6(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ND6

#define NC_ND6_DAD_OUT_PACKETS		0	/* �d���A�h���X���o���M��		*/
#define NC_ND6_NS_OUT_PACKETS		1	/* �ߗחv�����M��		*/
#define NC_ND6_NS_IN_PACKETS		2	/* �ߗחv����M��		*/
#define NC_ND6_NA_OUT_PACKETS		3	/* �ߗגʒm���M��		*/
#define NC_ND6_NA_IN_PACKETS		4	/* �ߗגʒm��M��		*/
#define NC_ND6_RS_OUT_PACKETS		5	/* ���[�^�v���o�͐�		*/
#define NC_ND6_RA_IN_PACKETS		6	/* ���[�^�ʒm��M��		*/
#define NC_ND6_SIZE			7	/* �J�E���^��			*/

#define NET_COUNT_ND6(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL	net_count_nd6[NC_ND6_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ND6 */

#define NET_COUNT_ND6(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ND6 */

#endif	/* of #if defined(SUPPORT_INET6) */

#ifdef SUPPORT_TCP

/* TCP */

#if NET_COUNT_ENABLE & PROTO_FLG_TCP

#define NC_TCP_CONNECTS			0	/* �\���I�[�v����		*/
#define NC_TCP_ACCEPTS			1	/* �󓮃I�[�v����		*/
#define NC_TCP_RTT_UPDATES		2	/* RTT �X�V��			*/
#define NC_TCP_SEND_RSTS		3	/* ���M�ARST ��			*/
#define NC_TCP_SEND_ACKS		4	/* ���M�AACK ��			*/
#define NC_TCP_SEND_URG_SEGS		5	/* ���M�A�ً}�Z�O�����g��	*/
#define NC_TCP_SEND_DATA_SEGS		6	/* ���M�f�[�^�Z�O�����g��	*/
#define NC_TCP_SEND_REXMIT_SEGS		7	/* �đ��M�Z�O�����g��		*/
#define NC_TCP_SEND_SEGS		8	/* ���M�Z�O�����g��		*/
#define NC_TCP_SEND_CNTL_SEGS		9	/* ���M����Z�O�����g��		*/
#define NC_TCP_SEND_DATA_OCTETS		10	/* ���M�f�[�^�I�N�e�b�g��	*/
#define NC_TCP_FREE_RCV_QUEUE		11	/* ��M�L���[�����		*/
#define NC_TCP_RECV_DUP_SEGS		12	/* ��M�A���d��			*/
#define NC_TCP_RECV_DROP_SEGS		13	/* ��M�A�j����			*/
#define NC_TCP_RECV_RSTS		14	/* ��M�ARST ��			*/
#define NC_TCP_RECV_DUP_ACKS		15	/* ��M�A���d ACK ��		*/
#define NC_TCP_RECV_ACKS		16	/* ��M�AACK ��			*/
#define NC_TCP_RECV_BAD_CKSUMS		17	/* ��M�A�`�F�b�N�T���s����	*/
#define NC_TCP_RECV_BAD_HEADERS		18	/* ��M�A�w�b�_�s����		*/
#define NC_TCP_RECV_URG_SEGS		19	/* ��M�A�ً}�Z�O�����g��	*/
#define NC_TCP_RECV_DATA_SEGS		20	/* ��M�f�[�^�Z�O�����g��	*/
#define NC_TCP_RECV_SEGS		21	/* ��M�Z�O�����g��		*/
#define NC_TCP_RECV_DATA_OCTETS		22	/* ��M�f�[�^�I�N�e�b�g��	*/
#define NC_TCP_RECV_OCTETS		23	/* ��M�I�N�e�b�g��		*/
#define NC_TCP_SIZE			24	/* �J�E���^��			*/

#define NET_COUNT_TCP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT_VAL net_count_tcp[NC_TCP_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_TCP */

#define NET_COUNT_TCP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_TCP */

#endif	/* of #ifdef SUPPORT_TCP */

#ifdef SUPPORT_UDP

/* UDP */

#if NET_COUNT_ENABLE & PROTO_FLG_UDP

#define NET_COUNT_UDP(v,c)	((v)+=(c))

#ifndef _MACRO_ONLY

extern T_NET_COUNT	net_count_udp;

#endif	/* of #ifndef _MACRO_ONLY */

#else	/* of #if NET_COUNT_ENABLE & PROTO_FLG_UDP */

#define NET_COUNT_UDP(v,c)

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_UDP */

#endif	/* of #ifdef SUPPORT_UDP */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

#define NET_COUNT_MIB(v, c)		((v)+=(c))

#else	/* of #ifdef SUPPORT_MIB */

#define NET_COUNT_MIB(v, c)

#endif	/* of #ifdef SUPPORT_MIB */

#endif	/* of #ifndef _NET_COUNT_H_ */
