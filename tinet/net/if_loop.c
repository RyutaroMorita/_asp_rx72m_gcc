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
 *  @(#) $Id: if_loop.c,v 1.5 2009/12/24 05:42:40 abe Exp $
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
 *	@(#)if_loop.c	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if_loop.c,v 1.37.2.1 1999/08/29 16:28:19 peter Exp $
 */

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include <net/if_var.h>
#include <net/if6_var.h>

#ifdef SUPPORT_LOOP

/*
 *  ���[�J�����[�v�o�b�N�C���^�t�F�[�X
 */

/*
 *  �O���֐��̒�`
 */

extern const char *itron_strerror (ER ercd);

/*
 *  �ϐ�
 */

/* �l�b�g���[�N�C���^�t�F�[�X�\���� */

#if defined(SUPPORT_INET4)

static T_IFNET loop_ifnet = {
	NULL,			/* �l�b�g���[�N�C���^�t�F�[�X�̃\�t�g�E�F�A���	*/
	{
		IPV4_ADDR_LOOPBACK,		/* IPv4 �A�h���X			*/
		IPV4_ADDR_LOOPBACK_MASK,	/* �T�u�l�b�g�}�X�N			*/
		},
	};

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

static T_IFNET loop_ifnet = {
	NULL,			/* �l�b�g���[�N�C���^�t�F�[�X�̃\�t�g�E�F�A���	*/
	{},			/* IPv6 �A�h���X���				*/
	{},			/* �}���`�L���X�g IPv6 �A�h���X			*/
	};

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  loop_get_ifnet -- �l�b�g���[�N�C���^�t�F�[�X�\���̂�Ԃ��B
 */

T_IFNET *
loop_get_ifnet (void)
{
	return &loop_ifnet;
	}

/*
 *  looutput -- ���[�J�����[�v�o�b�N�C���^�t�F�[�X�̏o�͊֐�
 */

ER
looutput (T_NET_BUF *output, TMO tmout)
{
	ER error;

	NET_COUNT_LOOP(net_count_loop.out_octets,  output->len);
	NET_COUNT_LOOP(net_count_loop.out_packets, 1);

	if ((error = tsnd_dtq(DTQ_LOOP_OUTPUT, output, tmout)) != E_OK)
		syslog(LOG_NOTICE, "[LOOP] drop error: %s", itron_strerror(error));
	return error;
	}

/*
 *  ���[�J�����[�v�o�b�N�C���^�t�F�[�X�E�o�̓^�X�N
 */

void
if_loop_output_task (intptr_t exinf)
{
	T_NET_BUF	*output;
	ER		error;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[LOOP OUTPUT:%d] started.", tskid);
	while (true) {
		if (rcv_dtq(DTQ_LOOP_OUTPUT, (intptr_t*)&output) == E_OK) {
			NET_COUNT_LOOP(net_count_loop.in_octets,  output->len);
			NET_COUNT_LOOP(net_count_loop.in_packets, 1);
			if ((error = snd_dtq(DTQ_LOOP_INPUT, output)) != E_OK)
				syslog(LOG_NOTICE, "[LOOP OUTPUT] drop error: %s", itron_strerror(error));
			}
		}
	}

/*
 *  ���[�J�����[�v�o�b�N�C���^�t�F�[�X�E���̓^�X�N
 */

void
if_loop_input_task (intptr_t exinf)
{
	T_NET_BUF	*input;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[LOOP INPUT:%d] started.", tskid);
	while (true) {
		if (rcv_dtq(DTQ_LOOP_INPUT, (intptr_t)&input) == E_OK) {
			NET_COUNT_LOOP(net_count_loop.in_octets,  input->len);
			NET_COUNT_LOOP(net_count_loop.in_packets, 1);

#if defined(SUPPORT_INET4)

			/* IPv4 ���͊֐����Ăяo�� */
			if (IP4_VHL_V(GET_IP4_HDR(input)->vhl) == IPV4_VERSION)
				ip_input(input);

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

			/* IPv6 ���͊֐����Ăяo�� */
			if (IP6_VCF_V(ntohl(GET_IP6_HDR(input)->vcf)) == IPV6_VERSION)
				ip6_input(input);

#endif	/* of #if defined(SUPPORT_INET6) */

			}
		}
	}

#endif	/* of #ifdef SUPPORT_LOOP */
