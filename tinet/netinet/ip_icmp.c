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
 *  @(#) $Id: ip_icmp.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	@(#)ip_icmp.c	8.2 (Berkeley) 1/4/94
 * $FreeBSD: src/sys/netinet/ip_icmp.c,v 1.33.2.3 1999/10/14 11:49:38 des Exp $
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

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>

/*
 *  �ϐ�
 */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

T_ICMP_STATS icmp_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �֐�
 */

static void icmp_echo (T_NET_BUF *input, uint_t ihoff);
static void icmp_unreach (T_NET_BUF *input, uint_t ihoff);

#if NUM_REDIRECT_ROUTE_ENTRY > 0

static void icmp_redirect (T_NET_BUF *input, uint_t ihoff);

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  icmp_echo -- �G�R�[�v������M�����Ƃ��̏���
 *
 *    input �ɂ� IF �w�b�_�� IP �w�b�_���܂܂�Ă���B
 */

static void
icmp_echo (T_NET_BUF *input, uint_t ihoff)
{
	T_IP4_HDR	*ip4h;
	T_ICMP4_HDR	*icmp4h;
	T_IN4_ADDR	addr;

	NET_COUNT_MIB(icmp_stats.icmpInEchos, 1);

	/* ���b�Z�[�W�̌^���G�R�[�v�� (8) ���� �G�R�[���� (0) ��	*/
	/* �ύX���đ���Ԃ��B					*/

	icmp4h = GET_ICMP4_HDR(input, ihoff);
	icmp4h->type = ICMP4_ECHO_REPLY;

	/* IP �w�b�_�̈���Ɣ��M������������B*/
	ip4h      = GET_IP4_HDR(input);
	addr      = ip4h->src;
	ip4h->src = ip4h->dst;
	ip4h->dst = addr;

	/* �`�F�b�N�T�����v�Z����B*/
	icmp4h->sum = 0;
	icmp4h->sum = in_cksum(icmp4h,
	                       (uint_t)(((input->len - GET_IF_IP4_HDR_SIZE(input)) + 3) >> 2 << 2));

	/* ���M����B*/
	NET_COUNT_ICMP4(net_count_icmp4.out_octets,
	               input->len - GET_IF_IP4_HDR_SIZE(input));
	NET_COUNT_ICMP4(net_count_icmp4.out_packets, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutMsgs, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutEchoReps, 1);
	ip_output(input, TMO_ICMP_OUTPUT);
	}

/*
 *  icmp_unreach -- ICMP4_UNREACH ����M�����Ƃ��̏���
 */

static const int8_t code2error[] = {
	EV_HURCH,	/* ICMP4_UNREACH_NET			 0 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST			 1 */
	EV_CNNRF,	/* ICMP4_UNREACH_PROTOCOL		 2 */
	EV_CNNRF,	/* ICMP4_UNREACH_PORT			 3 */
	EV_MSIZE,	/* ICMP4_UNREACH_FLAG			 4 */
	EV_HURCH,	/* ICMP4_UNREACH_SRC_FAIL		 5 */
	EV_HURCH,	/* ICMP4_UNREACH_NET_UNKNOWN		 6 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST_UNKNOWN		 7 */
	EV_HURCH,	/* ICMP4_UNREACH_ISOLATED		 8 */
	EV_HURCH,	/* ICMP4_UNREACH_NET_PROHIB		 9 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST_PROHIB		10 */
	EV_HURCH,	/* ICMP4_UNREACH_TOS_NET		11 */
	EV_HURCH,	/* ICMP4_UNREACH_TOS_HOST		12 */
	EV_HURCH,	/* ICMP4_UNREACH_FILTER_PROHIB		13 */
	EV_HURCH,	/* ICMP4_UNREACH_HOST_PRECEDENCE	14 */
	EV_HURCH,	/* ICMP4_UNREACH_PRECEDENCE_CUTOFF	15 */
	};

static void
icmp_unreach (T_NET_BUF *input, uint_t ihoff)
{
	T_IP4_HDR	*ip4h;
	uint8_t		code;
	ER		error;

	NET_COUNT_MIB(icmp_stats.icmpInDestUnreachs, 1);

	ip4h   = (T_IP4_HDR*)GET_ICMP4_SDU(input, ihoff);
	code  = GET_ICMP4_HDR(input, ihoff)->code;
	error = code2error[code];
	if (ip4h->proto == IPPROTO_TCP) {

#ifdef SUPPORT_TCP

		memcpy(GET_IP4_HDR(input), ip4h, input->len - (IP4_HDR_SIZE + ICMP4_HDR_SIZE));
		input->len -= IP4_HDR_SIZE + ICMP4_HDR_SIZE;
		tcp_notify(input, error);

#endif	/* of #ifdef SUPPORT_TCP */

		}
	else
		syslog(LOG_NOTICE, "[ICMP] error, code: %d.", code);
	}

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  icmp_redirect -- �����������b�Z�[�W����M�����Ƃ��̏���
 *
 *    input �ɂ� IF �w�b�_�� IP �w�b�_���܂܂�Ă���B
 */

static void
icmp_redirect (T_NET_BUF *input, uint_t ihoff)
{
	T_IP4_HDR	*ip4h, *sip4h;
	T_ICMP4_HDR	*icmp4h;

	ip4h   = GET_IP4_HDR(input);
	icmp4h = GET_ICMP4_HDR(input, ihoff);
	sip4h  = (T_IP4_HDR *)GET_ICMP4_SDU(input, ihoff);

	/*
	 *  ���e�`�F�b�N�A�ȉ��̏ꍇ�̓G���[
	 *
	 *    �EICMP �R�[�h���AICMP4_REDIRECT_PORT_AND_HOST (3) �ȏ�
	 *    �E�f�[�^�O���������AICMP �̍ŏ������Z�� (IP �w�b�_ + ICMP �w�b�_ + IP �w�b�_ + 8)
	 *    �E�f�[�^�O���������AICMP �̍ő咷���Z��
	 *    �E
	 */
	if (icmp4h->code > ICMP4_REDIRECT_PORT_AND_HOST ||
	    ip4h->len < GET_IP4_ICMP4_HDR_SIZE(input) + 8 + IP4_HDR_SIZE ||
	    ip4h->len < GET_IP4_ICMP4_HDR_SIZE(input) + 8 + (IP4_VHL_HL(sip4h->vhl) << 2)) {
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		return;
		}

	in4_rtredirect(icmp4h->data.addr, sip4h->dst, IN_RTF_REDIRECT, TMO_IN_REDIRECT);
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  icmp_input -- ICMP �̓��͊֐�
 *
 *    input �ɂ� IF �w�b�_�� IP �w�b�_���܂܂�Ă���B
 */

uint_t
icmp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_ICMP4_HDR	*icmp4h;
	T_IN4_ADDR	addr;
	uint_t		len, align;

	NET_COUNT_ICMP4(net_count_icmp4.in_octets,
	               input->len - GET_IF_IP4_HDR_SIZE(input));
	NET_COUNT_ICMP4(net_count_icmp4.in_packets, 1);

	/* ICMP �w�b�_�̒������`�F�b�N����B*/
	if (input->len < IF_IP4_ICMP4_HDR_SIZE) {
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		NET_COUNT_MIB(icmp_stats.icmpInErrors, 1);
		goto buf_rel;
		}

	icmp4h = (T_ICMP4_HDR *)(input->buf + *offp);

	/* 4 �I�N�e�b�g���E�̃f�[�^�� */
	len   = input->len - *offp;
	align = (len + 3) >> 2 << 2;

	/* 4 �I�N�e�b�g���E�܂Ńp�f�B���O�Ŗ��߂�B*/
	if (align > len)
		memset((uint8_t*)input->buf + input->len, 0, (size_t)(align - len));

	/* �`�F�b�N�T�����v�Z����B*/
	if (in_cksum(icmp4h, align) != 0) {
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		goto buf_rel;
		}

	/* ���b�Z�[�W�̌^�ɂ�蕪�򂷂�B*/
	switch (icmp4h->type) {
	case ICMP4_ECHO_REQUEST:
		icmp_echo(input, *offp);
		return IPPROTO_DONE;
		break;
	case ICMP4_ECHO_REPLY:

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

		icmp_echo_reply(input, *offp);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

		break;
	case ICMP4_UNREACH:
		icmp_unreach(input, *offp);
		break;
	case ICMP4_REDIRECT:

#if NUM_REDIRECT_ROUTE_ENTRY > 0

		addr = ntohl(icmp4h->data.addr);
		syslog(LOG_INFO, "[ICMP] redirect, addr: %s.", ip2str(NULL, &addr));
		icmp_redirect(input, *offp);

#else	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		addr = ntohl(icmp4h->data.addr);
		syslog(LOG_INFO, "[ICMP] redirect ignored, addr: %s.", ip2str(NULL, &addr));

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		break;
	default:
		syslog(LOG_INFO, "[ICMP] unknown type: %d.", icmp4h->type);
		NET_COUNT_ICMP4(net_count_icmp4.in_err_packets, 1);
		break;
		}

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#ifdef ICMP_REPLY_ERROR

/*
 *  icmp_error -- ICMP �G���[���M�֐��B
 *
 *    input �ɂ� IF �w�b�_�� IP �w�b�_���܂܂�Ă���B
 *    icmp_error �ł́A�l�b�g���[�N�o�b�t�@ input ��ԋp���Ȃ��̂ŁA
 *    �ďo�����ŁA�J�����Ă���I������B	
 */

void
icmp_error (uint8_t code, T_NET_BUF *input)
{
	T_IP4_HDR	*ip4h;
	T_ICMP4_HDR	*icmp4h;
	T_NET_BUF	*output;
	T_IN4_ADDR	saddr;
	uint_t		len, ip4hl, align;

	ip4h  = GET_IP4_HDR(input);
	ip4hl = GET_IP4_HDR_SIZE(ip4h);

	/* ���M�p�� IP �f�[�^�O�������l������B*/
	if (input->len - ip4hl < 8)
		len = input->len - ip4hl;
	else
		len = 8;
	
	saddr = ntohl(ip4h->src);
	if (in4_get_datagram(&output, (uint_t)(ICMP4_HDR_SIZE + ip4hl + len), 0,
	                     &saddr, NULL, IPPROTO_ICMP, IP4_DEFTTL, 
	                     NBA_SEARCH_ASCENT, TMO_ICMP_OUTPUT) != E_OK)
		return;

	/* ICMP �w�b�_��ݒ肷��B*/
	icmp4h		= GET_ICMP4_HDR(output, IF_IP4_ICMP4_HDR_OFFSET);
	icmp4h->type	= ICMP4_UNREACH;
	icmp4h->code	= code;
	icmp4h->data.addr= 0;

	/* �G���[���������� IP �w�b�_�� �f�[�^ 8 �I�N�e�b�g���R�s�[����B*/
	memcpy(GET_ICMP4_SDU(output, IF_IP4_ICMP4_HDR_OFFSET),
	       GET_IP4_HDR(input), (size_t)(ip4hl + len));

	/* 4 �I�N�e�b�g���E�̃f�[�^�� */
	align = (len + 3) >> 2 << 2;

	/* 4 �I�N�e�b�g���E�܂Ńp�f�B���O�Ŗ��߂�B*/
	if (align > len)
		memset((uint8_t*)GET_ICMP4_SDU(output, IF_IP4_ICMP4_HDR_OFFSET) + ip4hl + len,
		       0, (size_t)(align - len));

	/* �`�F�b�N�T�����v�Z����B*/
	icmp4h->sum = 0;
	icmp4h->sum = in_cksum(icmp4h, (uint_t)(ICMP4_HDR_SIZE + ip4hl + align));

	/* ���M����B*/
	NET_COUNT_ICMP4(net_count_icmp4.out_octets,
	               output->len - GET_IF_IP4_HDR_SIZE(output));
	NET_COUNT_ICMP4(net_count_icmp4.out_packets, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutMsgs, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutDestUnreachs, 1);
	ip_output(output, TMO_ICMP_OUTPUT);
	}

#endif	/* of #ifdef ICMP_REPLY_ERROR */
