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
 *  @(#) $Id: route6.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/route6.c,v 1.6 2002/10/16 01:54:45 sam Exp $	*/
/*	$KAME: route6.c,v 1.24 2001/03/14 03:07:05 itojun Exp $	*/

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
#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/ppp_ipcp.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>

#ifdef SUPPORT_INET6

#if 0
	/*
	 *  �ʐM�ш��H���Ԃ��U���ւ̑Ή��̂��߁A
	 *  �^�C�v 0 �o�H����w�b�_�̏������s��Ȃ��B
	 */

/*
 *  ip6_rthdr0 -- �^�C�v 0 �o�H����w�b�_�̓��͊֐�
 */

static ER
ip6_rthdr0 (T_NET_BUF *input, T_IP6_RT0_HDR *rt0h)
{
	if (rt0h->segleft == 0) {
		/* ���p�m�[�h���� 0 �Ȃ̂ŁA�I�_�m�[�h */
		return E_OK;
		}

	/* len �� segleft �̐������`�F�b�N */
#ifdef IP6_CFG_COMPAT_RFC1883
	if ((rt0h->len % 2) || (rt0h->len > 46)) {
#else
	if (rt0h->len % 2) {
#endif
		/*
		 *  len �͋����ŁA(23 * 2) �܂ŁB
		 *  �������A(23 * 2) �̐����� RFC 2462 �ō폜����Ă���B
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rt0h->len - input->buf) - IF_HDR_SIZE);
		return E_PAR;
		}

	/* len �����p�m�[�h���Ɩ������Ă��Ȃ����`�F�b�N����B*/
	if ((rt0h->len / 2) < rt0h->segleft) {
		/*
		 *  len �� 8�I�N�e�b�g�P�ʁAsegleft �� 16�I�N�e�b�g�P�ʂȂ̂ŁA
		 *  len / 2 == segleft �ƂȂ�͂��B
		 *  len / 2 <  segleft �̓G���[�B
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rt0h->segleft - input->buf) - IF_HDR_SIZE);
		return E_PAR;
		}

	/*
	 *  �c��̒��p�m�[�h���� 1 �ȏ�ł���΁A���̃m�[�h�͍ŏI�I��
	 *  �I�_�m�[�h�ł͂Ȃ��B�{�����ł́A���p�����Ȃ��̂ŁA
	 *  ���̓f�[�^�O�����̏������I������B
	 */
	syscall(rel_net_buf(input));
	return E_PAR;
	}

#endif

/*
 *  route6_input -- �o�H����w�b�_�̓��͊֐�
 */

uint_t
route6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_IP6_RT_HDR	*rth;
	uint_t		len, off = *offp;

	/* �l�b�g���[�N�o�b�t�@�̎c��̒������`�F�b�N����B*/
	if (input->len - off < sizeof(T_IP6_RT_HDR))
		goto buf_rel;

	rth = (T_IP6_RT_HDR *)(input->buf + off);
	len = (rth->len + 1) << 3;

	/* �o�H����w�b�_�̒������`�F�b�N����B*/
	if (input->len < off + len)
		goto buf_rel;

#if 0
	/*
	 *  �ʐM�ш��H���Ԃ��U���ւ̑Ή��̂��߁A
	 *  �^�C�v 0 �o�H����w�b�_�̏������s��Ȃ��B
	 */
	if (rth->type == IPV6_RTHDR_TYPE_0) {
		if (ip6_rthdr0(input, (T_IP6_RT0_HDR*)rth) != E_OK) {

			/* �G���[�̏ꍇ�́Aip6_rthdr0 �Ńo�b�t�@���J�����Ă���B*/
			return IPPROTO_DONE;
			}
		}
	else if (rth->segleft != 0) {

		/*
		 *  �c��̒��p�m�[�h���� 1 �ȏ�ł���΁A���̃m�[�h�͍ŏI�I��
		 *  �I�_�m�[�h�ł͂Ȃ��B�{�����ł́A���p�����Ȃ��̂ŁA
		 *  ICMP6 �G���[��ԑ����ď������I������B
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rth->type - input->buf) - IF_HDR_SIZE);
		return IPPROTO_DONE;
		}
#else
	if (rth->segleft != 0) {

		/*
		 *  �c��̒��p�m�[�h���� 1 �ȏ�ł���΁A���̃m�[�h�͍ŏI�I��
		 *  �I�_�m�[�h�ł͂Ȃ��B�{�����ł́A���p�����Ȃ��̂ŁA
		 *  ICMP6 �G���[��ԑ����ď������I������B
		 */
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   ((uint8_t*)&rth->type - input->buf) - IF_HDR_SIZE);
		return IPPROTO_DONE;
		}
#endif

	*nextp = *offp - IF_HDR_SIZE + offsetof(T_IP6_RT_HDR, next);
	*offp += len;
	return rth->next;

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#endif /* of #ifdef SUPPORT_INET6 */
