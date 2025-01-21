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
 *  @(#) $Id: udp_output.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1995
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
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/nd6.h>
#include <netinet/icmp6.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

#ifdef SUPPORT_UDP

#ifdef UDP_CFG_NON_BLOCKING

/*
 *  �֐�
 */

static void udp_output (T_UDP_CEP *cep);

/*
 *  UDP �o�̓^�X�N
 *  �m���u���b�L���O�R�[����g�ݍ��񂾂Ƃ��g�p����B
 */

static void
udp_output (T_UDP_CEP *cep)
{
	T_NET_BUF	*output;
	T_UDP_HDR	*udph;
	ER_UINT		error;

#ifdef UDP_CFG_OUT_CHECKSUM
	uint16_t	sum;
#endif	/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	/* IP �f�[�^�O���������蓖�Ă�B*/
	if ((error = IN_GET_DATAGRAM(&output, (uint_t)(UDP_HDR_SIZE + cep->snd_len), 0,
	                             &cep->snd_p_dstaddr->ipaddr,
	                             &cep->myaddr.ipaddr,
	                             IPPROTO_UDP, IP_DEFTTL, 
	                             NBA_SEARCH_ASCENT, TMO_UDP_OUTPUT)) != E_OK) {
		goto err_ret;
		}

	/* UDP �w�b�_�ɏ���ݒ肷��B*/
	udph		= GET_UDP_HDR(output, IF_IP_UDP_HDR_OFFSET);
	udph->sport	= htons(cep->myaddr.portno);
	udph->dport	= htons(cep->snd_p_dstaddr->portno);
	udph->ulen	= htons(UDP_HDR_SIZE + cep->snd_len);
	udph->sum	= 0;

	/* �f�[�^���R�s�[����B*/
	memcpy((void*)GET_UDP_SDU(output, IF_IP_UDP_HDR_OFFSET),
	       cep->snd_data, (size_t)cep->snd_len);

#ifdef UDP_CFG_OUT_CHECKSUM

	sum = IN_CKSUM(output, IPPROTO_UDP, IF_IP_UDP_HDR_OFFSET,
	               (uint_t)(UDP_HDR_SIZE + cep->snd_len));

	/* �v�Z�����`�F�b�N�T���̒l�� 0 �Ȃ� 0xffff ������B*/
	if (sum == 0)
		sum = UINT_C(0xffff);
	udph->sum = sum;

#endif/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	/* �l�b�g���[�N�o�b�t�@���𒲐�����B*/
	output->len = (uint16_t)(IF_IP_UDP_HDR_SIZE + cep->snd_len);

	/* �l�b�g���[�N�w (IP) �̏o�͊֐����Ăяo���B*/
	if ((error = IP_OUTPUT(output, TMO_UDP_OUTPUT)) != E_OK)
		goto err_ret;


	NET_COUNT_MIB(udp_stats.udpOutDatagrams, 1);

	if (IS_PTR_DEFINED(cep->callback)) {

		if (error == E_OK)
			error = cep->snd_len;

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		}
	else
		syslog(LOG_WARNING, "[UDP] no call back, CEP: %d.", GET_UDP_CEPID(cep));
	cep->snd_p_dstaddr = NULL;
	return;

err_ret:
	NET_COUNT_UDP(net_count_udp.out_err_packets, 1);
	if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)E_NOMEM);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		error = E_NOMEM;
		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		}
	else
		syslog(LOG_WARNING, "[UDP] no call back, CEP: %d.", GET_UDP_CEPID(cep));
	cep->snd_p_dstaddr = NULL;
	return;
	}

/*
 *  UDP �o�̓^�X�N
 *  �m���u���b�L���O�R�[����g�ݍ��񂾂Ƃ��g�p����B
 */

void
udp_output_task (intptr_t exinf)
{
	ID	tskid;
	int_t	ix;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP OUTPUT:%d] started.", tskid);


#if defined(SUPPORT_INET6) && !defined(SUPPORT_TCP)

	/* IPv6 �̃X�e�[�g���X�E�A�h���X�����ݒ�����s����B*/
	in6_if_up(IF_GET_IFNET());

#endif	/* of #if defined(SUPPORT_INET6) && !defined(SUPPORT_TCP) */

	while (true) {

		/* �o�͂��|�X�g�����܂ő҂B*/
		syscall(wai_sem(SEM_UDP_POST_OUTPUT));

		for (ix = tmax_udp_ccepid; ix -- > 0; ) {

			if (udp_cep[ix].flags & UDP_CEP_FLG_POST_OUTPUT) {
				udp_cep[ix].flags &= ~UDP_CEP_FLG_POST_OUTPUT;
				udp_output(&udp_cep[ix]);
				}
			}
		}
	}

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#endif	/* of #ifdef SUPPORT_UDP */
