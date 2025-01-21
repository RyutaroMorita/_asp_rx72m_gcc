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
 *  @(#) $Id: net_count.c,v 1.5 2009/12/24 05:42:40 abe Exp $
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

/* 
 *  �l�b�g���[�N���v���̌v��
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/net.h>
#include <net/net_count.h>

/*
 *  �v���p�ϐ�
 */

#ifdef SUPPORT_PPP

#if NET_COUNT_ENABLE & PROTO_FLG_PPP

T_NET_COUNT	net_count_ppp;
T_NET_COUNT_VAL	net_count_ppp_no_bufs;		/* net_buf ���蓖�Ď��s��	*/

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP

T_NET_COUNT_VAL	net_count_ppp_lcp_in_octets;
T_NET_COUNT_VAL	net_count_ppp_lcp_in_packets;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_LCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP

T_NET_COUNT_VAL	net_count_ppp_ipcp_in_octets;
T_NET_COUNT_VAL	net_count_ppp_ipcp_in_packets;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_IPCP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP

T_NET_COUNT_VAL	net_count_ppp_upap_in_octets;
T_NET_COUNT_VAL	net_count_ppp_upap_in_packets;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_PAP */

#if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC

T_NET_COUNT	net_count_hdlc;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_PPP_HDLC */

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_LOOP

#if NET_COUNT_ENABLE & PROTO_FLG_LOOP

T_NET_COUNT	net_count_loop;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_LOOP */

#endif	/* of #ifdef SUPPORT_LOOP */

#ifdef SUPPORT_ETHER

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER

T_NET_COUNT	net_count_ether;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER */

#if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC

T_NET_COUNT_VAL net_count_ether_nic[NC_ETHER_NIC_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ETHER_NIC */

#endif	/* of #ifdef SUPPORT_ETHER */

#if defined(SUPPORT_INET4)

#if NET_COUNT_ENABLE & PROTO_FLG_ARP

T_NET_COUNT	net_count_arp;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ARP */

#if NET_COUNT_ENABLE & PROTO_FLG_IP4

T_NET_COUNT_VAL net_count_ip4[NC_IP4_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP4 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP4

T_NET_COUNT	net_count_icmp4;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP4 */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#if NET_COUNT_ENABLE & PROTO_FLG_IP6

T_NET_COUNT_VAL net_count_ip6[NC_IP6_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_IP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ICMP6

T_NET_COUNT_VAL	net_count_icmp6[NC_ICMP6_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ICMP6 */

#if NET_COUNT_ENABLE & PROTO_FLG_ND6

T_NET_COUNT_VAL	net_count_nd6[NC_ND6_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_ND6 */

#endif	/* of #if defined(SUPPORT_INET6) */

#ifdef SUPPORT_TCP

#if NET_COUNT_ENABLE & PROTO_FLG_TCP

T_NET_COUNT_VAL net_count_tcp[NC_TCP_SIZE];

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_TCP */

#endif	/* of #ifdef SUPPORT_TCP */

#ifdef SUPPORT_UDP

#if NET_COUNT_ENABLE & PROTO_FLG_UDP

T_NET_COUNT	net_count_udp;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_UDP */

#endif	/* of #ifdef SUPPORT_PPP */
