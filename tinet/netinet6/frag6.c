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
 *  @(#) $Id: frag6.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/frag6.c,v 1.9 2002/04/19 04:46:22 suz Exp $	*/
/*	$KAME: frag6.c,v 1.33 2002/01/07 11:34:48 kjc Exp $	*/

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

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
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
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_var.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>

#ifdef SUPPORT_INET6

#ifdef IP6_CFG_FRAGMENT

/*
 *  �f�[�^�O�����č\���L���[�z��
 */

static T_NET_BUF	*ip6_frag_queue[NUM_IP6_FRAG_QUEUE];
static T_IN6_ADDR	 ip6_frag_dest [NUM_IP6_FRAG_QUEUE];

/*
 *  ip6_get_frag_queue -- �f�[�^�O�����č\���L���[���l������B
 */

const T_NET_BUF **
ip6_get_frag_queue (void)
{
	return (const T_NET_BUF **)ip6_frag_queue;
	}

/*
 *  frag6_free_queue -- �f�[�^�O�����č\���L���[���������B
 *
 *    ����: �f�[�^�O�����č\���L���[�z������b�N���Ă���Ăяo�����ƁB
 */

static void
frag6_free_queue (T_NET_BUF **queue)
{
	T_NET_BUF 	*frag, *next;
	T_QIP6_HDR	*qip6h;

	frag = *queue;
	while (frag != NULL) {
		qip6h = GET_QIP6_HDR(frag);
		next  = qip6h->next_frag;
		syscall(rel_net_buf(frag));
		frag = next;
		}
	*queue = NULL;
	}

/*
 *  frag6_timer -- �f�[�^�O�����č\���Ǘ��^�C�}
 */

void
frag6_timer (void)
{
	T_NET_BUF	*frag;
	T_QIP6_HDR	*qip6h;
	T_IP6_FRAG_HDR	*qip6fh;
	int_t		ix;

	syscall(wai_sem(SEM_IP6_FRAG_QUEUE));
	for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {
		frag = ip6_frag_queue[ix];
		if (frag != NULL) {
			qip6h = GET_QIP6_HDR(frag);
			if (qip6h->ftim > 0 && -- qip6h->ftim == 0) {

				qip6fh = (T_IP6_FRAG_HDR *)(frag->buf + qip6h->foff);
				if (ntohs(qip6fh->off_flag & IP6F_OFF_MASK) == 0) {

					/*
					 *  �擪�̒f�Ђ̃I�t�Z�b�g�� 0 �̎��̂�
					 *  ICMPv6 �G���[���b�Z�[�W�𑗐M����B
					 */

					/* �擪�̒f�Ђ��f�[�^�O�����č\���L���[����O���B*/
					ip6_frag_queue[ix] = qip6h->next_frag;

					/* ���Đ�A�h���X�����ɖ߂��B*/
					GET_IP6_HDR(frag)->dst = ip6_frag_dest[ix];

					/* ICMPv6 �G���[���b�Z�[�W�𑗐M����B*/
					icmp6_error(frag, ICMP6_TIME_EXCEEDED,
					                  ICMP6_TIME_EXCEED_REASSEMBLY, 0);
					}

				/* �f�[�^�O�����č\���L���[���������B*/
				NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_TMOUT], 1);
				NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_DROP], 1);
				frag6_free_queue(&ip6_frag_queue[ix]);
				}
			}
		}
	syscall(sig_sem(SEM_IP6_FRAG_QUEUE));
	}

#endif	/* #ifdef IP6_CFG_FRAGMENT */

/*
 *  frag6_input -- �f�Ѓw�b�_�̓��͊֐�
 */

uint_t
frag6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_IP6_HDR	*ip6h;
	T_IP6_FRAG_HDR	*ip6fh;
	T_NET_BUF	*input = *inputp;
	uint_t		off = *offp;

#ifdef IP6_CFG_FRAGMENT

	T_QIP6_HDR	*qip6h, *rip6h;
	T_IP6_FRAG_HDR	*qip6fh = NULL;
	T_NET_BUF	**ip6fq = NULL, *prev, *next, *frag;
	int_t		ix;
	int32_t		unfraglen, diff;
	uint16_t	fragpartlen, qfragpartlen, fragoff, qfragoff, plen;
	uint8_t		ftim, *prev_next;
	uint_t		nextproto = IPPROTO_DONE;

#endif	/* #ifdef IP6_CFG_FRAGMENT */

	/* �l�b�g���[�N�o�b�t�@�̎c��̒������`�F�b�N����B*/
	if (input->len - off < sizeof(T_IP6_FRAG_HDR))
		goto buf_rel;

	/* 
	 *  ����y�C���[�h�I�v�V�����ƒf�Ѓw�b�_�𓯎��Ɏg�p���邱�Ƃ�
	 *  �ł��Ȃ��B�y�C���[�h������ 0 �Ȃ�A����y�C���[�h�I�v�V������
	 *  �w�肳��Ă��邱�ƂɂȂ�̂� ICMP �ŃG���[�𑗐M�҂�
	 *  �ʒm����B
	 */
	ip6h = GET_IP6_HDR(input);
	if (ip6h->plen == 0) {
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   off - IF_HDR_SIZE);
		NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
		return IPPROTO_DONE;
		}

	/*
	 *  �I�t�Z�b�g�� 0 �ŁA�ŏI�t���O�����g�ł���΁A
	 *  �����s�v�̃f�[�^�O�����Ȃ̂ŁA
	 *  ���w�b�_���w���ϐ��𒲐����ďI������B
	 */
	ip6fh = (T_IP6_FRAG_HDR *)(input->buf + off);
	if (ip6fh->off_flag == 0) {
		*nextp = *offp - IF_HDR_SIZE + offsetof(T_IP6_FRAG_HDR, next);
		*offp = off + sizeof(T_IP6_FRAG_HDR);
		return ip6fh->next;
		}

#ifdef IP6_CFG_FRAGMENT

	/*
	 *  �y�C���[�h�����`�F�b�N����B
	 */
	if ((ip6fh->off_flag & IP6F_MORE_FRAG) && 
	    ((ntohs(ip6h->plen) - (off - IF_HDR_SIZE)) & 0x7) != 0) {
		icmp6_error(input, ICMP6_PARAM_PROB,
		                   ICMP6_PARAMPROB_HEADER,
		                   offsetof(T_IP6_HDR, plen));
		NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
		return nextproto;
		}
	NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmReqds, 1);

	syscall(wai_sem(SEM_IP6_FRAG_QUEUE));

	/*
 	 *  �f�[�^�O�����č\���L���[�z�񂩂�A�Ή�����G���g����T���B
 	 */
	for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {
		if (ip6_frag_queue[ix] != NULL) {
			qip6h  = GET_QIP6_HDR(ip6_frag_queue[ix]);
			qip6fh = (T_IP6_FRAG_HDR *)(ip6_frag_queue[ix]->buf + qip6h->foff);
			if (ip6fh->ident == qip6fh->ident               &&
			    IN6_ARE_ADDR_EQUAL(&ip6h->src, &qip6h->src) &&
			    IN6_ARE_ADDR_EQUAL(&ip6h->dst, &ip6_frag_dest[ix])) {
				ip6fq = &ip6_frag_queue[ix];
			    	break;
			    	}
			}
		}

 	if (ip6fq == NULL) {

		/*
	 	 *  �f�Ђ̐��������`�F�b�N����B
		 */
		unfraglen = 0;
		fragoff = ntohs(ip6fh->off_flag & IP6F_OFF_MASK);
		if (fragoff == 0) {

			/*
		 	 *  ���͂����f�Ђ��擪�̒f��
			 *  �����ł��Ȃ������̒��� unfraglen ���v�Z����B
			 */
			unfraglen = (off - IF_HDR_SIZE) - sizeof(T_IP6_HDR);
			}

		/*
		 *             off
		 *  |<--------------------------->|
		 *  |          off - IF_HDR_SIZE  |
		 *  |        |<------------------>|
		 *  |        | off - IF_HDR_SIZE + IP6_FRAG_HDR_SIZE |
		 *  |        |<------------------------------------->|
		 *  +--------+----------+---------+------------------+-------------+
		 *  | IF HDR | IPv6 HDR | EXT HDR |     FRAG HDR     |   Payload   |
		 *  +--------+----------+---------+------------------+-------------+
		 *                      |<---------------------------------------->|
		 *                      |             Payload Size                 |
		 *           |<--------------------------------------------------->|
		 *           |         IP6_HDR_SIZE + Payload Size                 |
		 *                                                   |<----------->|
		 *                                                   | fragpartlen |
		 */
		fragpartlen = sizeof(T_IP6_HDR) + ntohs(ip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));
		if (unfraglen + fragoff + fragpartlen > IPV6_MAXPACKET) {
			icmp6_error(input, ICMP6_PARAM_PROB,
			                   ICMP6_PARAMPROB_HEADER,
			                   (off - IF_HDR_SIZE) +
			                   offsetof(T_IP6_FRAG_HDR, off_flag));
			goto sig_ret;
			}

		/*
	 	 *  ip6fq == NULL �ł���΁A�Ή�����G���g���͖����̂ŁA
	 	 *  �f�[�^�O�����č\���L���[�z��ɁA�G���g����ǉ�����B
	 	 */
		for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {

			/* �󂫃G���g����T���B*/
			if (ip6_frag_queue[ix] == NULL) {
				ip6fq = &ip6_frag_queue[ix];
				break;
				}
			}

		/*
		 *  ip6fq == NULL �ł���΁A�󂫃G���g���������̂ŁA
		 *  �^�C���A�E�g�ihlim�j���Z���G���g�����J������B
		 */
 		if (ip6fq == NULL) {

		 	ftim = IPV6_MAXHLIM;
			for (ix = NUM_IP6_FRAG_QUEUE; ix -- > 0; ) {
				if (ip6_frag_queue[ix] != NULL) {
					rip6h  = GET_QIP6_HDR(ip6_frag_queue[ix]);
					if (rip6h->ftim < ftim) {
						ftim  = rip6h->ftim;
						ip6fq = &ip6_frag_queue[ix];
						}
					}
				}
			frag6_free_queue(ip6fq);
			}

		/*
		 *  �G���g����ݒ肷��B
		 */
		*ip6fq = input; 
		ip6_frag_dest[ip6fq - ip6_frag_queue] = ip6h->dst;
		qip6h  = GET_QIP6_HDR(*ip6fq);
		qip6h->ftim = IPV6_FRAGTTL;
		qip6h->foff = off;
		qip6h->flen = fragpartlen;
		qip6h->next_frag = NULL;
 		}
 	else {

		/*
	 	 *  �f�Ђ̐��������`�F�b�N����B
		 */
		unfraglen = 0;
		fragoff = ntohs(((T_IP6_FRAG_HDR *)((*ip6fq)->buf + GET_QIP6_HDR(*ip6fq)->foff))->off_flag & IP6F_OFF_MASK);
		if (fragoff == 0) {

			/*
		 	 *  �f�[�^�O�����č\���L���[�̍ŏ��̒f�Ђ��擪�̒f��
			 *  �����ł��Ȃ������̒��� unfraglen ���v�Z����B
			 */
			unfraglen = (GET_QIP6_HDR(*ip6fq)->foff - IF_HDR_SIZE) - sizeof(T_IP6_HDR);
			}

		fragoff = ntohs(ip6fh->off_flag & IP6F_OFF_MASK);
		if (fragoff == 0) {

			/*
		 	 *  ���͂����f�Ђ��擪�̒f��
			 *  �����ł��Ȃ������̒��� unfraglen ���v�Z����B
			 */
			unfraglen = (off - IF_HDR_SIZE) - sizeof(T_IP6_HDR);
			}

		/*
		 *             off
		 *  |<--------------------------->|
		 *  |          off - IF_HDR_SIZE  |
		 *  |        |<------------------>|
		 *  |        | off - IF_HDR_SIZE + IP6_FRAG_HDR_SIZE |
		 *  |        |<------------------------------------->|
		 *  +--------+----------+---------+------------------+-------------+
		 *  | IF HDR | IPv6 HDR | EXT HDR |     FRAG HDR     |   Payload   |
		 *  +--------+----------+---------+------------------+-------------+
		 *                      |<---------------------------------------->|
		 *                      |             Payload Size                 |
		 *           |<--------------------------------------------------->|
		 *           |         IP6_HDR_SIZE + Payload Size                 |
		 *                                                   |<----------->|
		 *                                                   | fragpartlen |
		 */
		fragpartlen = sizeof(T_IP6_HDR) + ntohs(ip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));
		if (unfraglen + fragoff + fragpartlen > IPV6_MAXPACKET) {
			icmp6_error(input, ICMP6_PARAM_PROB,
			                   ICMP6_PARAMPROB_HEADER,
			                   (off - IF_HDR_SIZE) +
			                   offsetof(T_IP6_FRAG_HDR, off_flag));
			goto sig_ret;
			}
		
		if (ntohs(ip6fh->off_flag & IP6F_OFF_MASK) == 0) {

			/*
		 	 *  ���͂����f�Ђ��擪�̒f��
		 	 *  �f�[�^�O�����č\���L���[�̍Ō�̒f�Ђ��A
		 	 *  �f�[�^�O�����̍ő咷�𒴂��Ă��Ȃ����`�F�b�N����B
			 */

			/* �Ō�̒f�Ђ�T������B*/
			next = *ip6fq;
			while ((qip6h = GET_QIP6_HDR(next))->next_frag != NULL)
				next = qip6h->next_frag;

			/* �Ō�̒f�Ђ̃I�t�Z�b�g�ƒf�ЃT�C�Y���v�Z����B*/
			qip6fh = (T_IP6_FRAG_HDR *)(next->buf + qip6h->foff);
			fragoff = ntohs(qip6fh->off_flag & IP6F_OFF_MASK);
			fragpartlen = sizeof(T_IP6_HDR) + ntohs(qip6h->plen) - (qip6h->foff - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));
			if (unfraglen + fragoff + fragpartlen > IPV6_MAXPACKET) {

				/*
				 *  �f�[�^�O�����̍ő咷�𒴂��Ă���ꍇ�́A
			 	 *  �f�[�^�O�����č\���L���[�S�̂�j������B
			 	 */
				frag6_free_queue(ip6fq);
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			}

		/* ECN �̐������`�F�b�N�͖����� */

		/*
		 *  �f�Ђ��G���g���ɑ}������B
	 	 *  �f�[�^�O�����č\���L���[����A���͂����f�Ђ��O�̒f�Ђ�T������B
		 */
		prev = NULL;
		next = *ip6fq;
		while (next != NULL) {
			qip6h  = GET_QIP6_HDR(next);
			qip6fh = (T_IP6_FRAG_HDR *)(next->buf + qip6h->foff);
			if (ntohs(ip6fh->off_flag & IP6F_OFF_MASK) <= ntohs(qip6fh->off_flag & IP6F_OFF_MASK))
				break;
			prev = next;
			next = qip6h->next_frag;
			}

		/*
		 *  prev �́A���͂����f�Ђ��O�̒f�ЁB������ NULL �̏ꍇ�́A
		 *  ���͂����f�Ђ��f�[�^�O�����č\���L���[�̒��ōł��O�̒f�ЁB
		 *  next �́A���͂����f�Ђ���̒f�ЁB������ NULL �̏ꍇ�́A
		 *  ���͂����f�Ђ��f�[�^�O�����č\���L���[�̒��ōł���̒f�ЁB
		 */
		fragoff = ntohs(ip6fh->off_flag & IP6F_OFF_MASK);
		if (prev != NULL) {

			/*
			 *  �O�̒f�ЂƁA���͂����f�Ђ��d�Ȃ��Ă��Ȃ����`�F�b�N����B
			 *
			 *    qfragoff
			 *    |   qfragparglen
			 *    |<------------------>|
			 *    +--------------------+
			 *    |        prev        |
			 *    +--------------------+
			 *
			 *                         +--------------------+
			 *                         |        input       |
			 *                         +--------------------+
			 *                         |
			 *                         fragoff
			 */
			qip6h  = GET_QIP6_HDR(prev);
			qip6fh = (T_IP6_FRAG_HDR *)(prev->buf + qip6h->foff);
			qfragoff = ntohs(qip6fh->off_flag & IP6F_OFF_MASK);
			qfragpartlen = sizeof(T_IP6_HDR) + ntohs(qip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));

			diff = ((int32_t)qfragoff + qfragpartlen) - fragoff;
			if (diff > 0) {

				/* �d�Ȃ��Ă���΁A���͂����f�Ђ�j�����ďI������B*/
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			}

		if (next != NULL) {

			/*
			 *  ��̒f�ЂƁA���͂����f�Ђ��d�Ȃ��Ă��Ȃ����`�F�b�N����B
			 *
			 *    fragoff
			 *    |    fragparglen
			 *    |<------------------>|
			 *    +--------------------+
			 *    |       input        |
			 *    +--------------------+
			 *
			 *                         +--------------------+
			 *                         |         next       |
			 *                         +--------------------+
			 *                         |
			 *                         qfragoff
			 */
			qip6h  = GET_QIP6_HDR(next);
			qip6fh = (T_IP6_FRAG_HDR *)(next->buf + qip6h->foff);
			qfragoff = ntohs(qip6fh->off_flag & IP6F_OFF_MASK);
			fragpartlen = sizeof(T_IP6_HDR) + ntohs(ip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));

			diff = ((int32_t)fragoff + fragpartlen) - qfragoff;
			if (diff > 0) {

				/* �d�Ȃ��Ă���΁A���͂����f�Ђ�j�����ďI������B*/
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			}

		/* ���͂����f�Ђ�ݒ肷��B*/
		qip6h  = GET_QIP6_HDR(input);
		qip6h->foff = off;
		qip6h->flen = sizeof(T_IP6_HDR) + ntohs(qip6h->plen) - (off - IF_HDR_SIZE + sizeof(T_IP6_FRAG_HDR));

		if (prev == NULL) {
			*ip6fq = input;
			qip6h->ftim = IPV6_FRAGTTL;
			}
		else
			GET_QIP6_HDR(prev)->next_frag = input;
		qip6h->next_frag = next;

		/*
		 *  �S�Ă̒f�Ђ���M�������`�F�b�N����B
		 */
		plen = 0;
		frag = *ip6fq;
		while (frag != NULL) {
			qip6h  = GET_QIP6_HDR(frag);
			qip6fh = (T_IP6_FRAG_HDR *)(frag->buf + qip6h->foff);
			if (ntohs(qip6fh->off_flag & IP6F_OFF_MASK) != plen) {

				/* �f�Ђ��A�����Ă��Ȃ��B*/
				goto sig_ret;
				}
			plen += qip6h->flen;
			frag = qip6h->next_frag;
			}
		if (ntohs(qip6fh->off_flag & IP6F_MORE_FRAG) != 0) {

			/* �Ō�̒f�Ђ���M���Ă��Ȃ��B*/
			goto sig_ret;
			}

		/*
		 *  �S�Ă̒f�Ђ���M�����̂ŁA�č\������B
		 */

		/* �l�b�g���[�N�o�b�t�@���l������B*/
		qip6h  = GET_QIP6_HDR(*ip6fq);
		qip6fh = (T_IP6_FRAG_HDR *)((*ip6fq)->buf + qip6h->foff);
		if (tget_net_buf(inputp, qip6h->foff + plen, TMO_IP6_FRAG_GET_NET_BUF) == E_OK) {

			/*
			 *  �f�Ѓw�b�_�̒��O�̃w�b�_�� NEXT �t�B�[���h�̃A�h���X���l�����A
			 *  ���ɖ߂��B
			 */
			if ((prev_next = ip6_get_prev_hdr(*ip6fq, qip6h->foff)) == NULL) {
				syscall(rel_net_buf(input));
				goto sig_ret;
				}
			*prev_next = qip6fh->next;
			input = *inputp;

			NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_OK], 1);
			NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmOKs, 1);

			/*
			 *  IPv6 �w�b�_�ƕ����ł��Ȃ�������
			 *  �f�[�^�O�����č\���L���[�̒��̐擪�̒f�Ђ���R�s�[����B
			 */
			memcpy(input->buf, (*ip6fq)->buf, qip6h->foff);

			/* ���M��A�h���X�����ɖ߂��B*/
			ip6h = GET_IP6_HDR(input);
			ip6h->dst = ip6_frag_dest[ip6fq - ip6_frag_queue];

			/* offp ���A�č\�������f�Ђ̐擪�ɐݒ肷��B*/
			*offp = qip6h->foff;

			/* �l�b�g���[�N�o�b�t�@����ݒ肷��B*/
			input->len = plen + qip6h->foff;

			/*
			 *  �S�Ă̒f�Ђ��R�s�[����B
			 */
			frag = *ip6fq;
			off  = qip6h->foff;
			while (frag != NULL) {
				qip6h  = GET_QIP6_HDR(frag);
				memcpy(input->buf + off,
				       frag->buf + qip6h->foff + sizeof(T_IP6_FRAG_HDR),
				       qip6h->flen);
				off += qip6h->flen;
				frag = qip6h->next_frag;
				}

			/* �y�C���[�h����ݒ肷��B*/
			ip6h->plen = htons(plen);

			*nextp = offsetof(T_IP6_HDR, next);
			nextproto = ip6h->next;
			}
		else {
			NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_NO_BUF], 1);
			NET_COUNT_IP6(net_count_ip6[NC_IP6_FRAG_IN_DROP], 1);
			NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
			}

		/* �f�[�^�O�����č\���L���[���������B*/
		frag6_free_queue(ip6fq);
 		}

sig_ret:
	syscall(sig_sem(SEM_IP6_FRAG_QUEUE));
	return nextproto;

#else	/* #ifdef IP6_CFG_FRAGMENT */

	/*
	 *  �f�[�^�O�����̕����E�č\���s��Ȃ��ꍇ�́A�S�f�Ђ�j�����A
	 *  �Ō�̒f�Ђ���M�����Ƃ��A
	 *  ICMP �G���[�𑗐M�҂ɒʒm����B
	 */
	if ((ip6fh->off_flag & IP6F_MORE_FRAG) == 0) {
		icmp6_error(input, ICMP6_TIME_EXCEEDED,
		                   ICMP6_TIME_EXCEED_REASSEMBLY, 0);
		NET_COUNT_MIB(in6_stats.ipv6IfStatsReasmFails, 1);
		return IPPROTO_DONE;
		}

#endif	/* #ifdef IP6_CFG_FRAGMENT */

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#endif /* of #ifdef SUPPORT_INET6 */
