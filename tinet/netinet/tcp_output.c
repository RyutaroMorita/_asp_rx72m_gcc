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
 *  @(#) $Id: tcp_output.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 *
 *	@(#)tcp_output.c	8.4 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_output.c,v 1.32.2.2 1999/08/29 16:29:55 peter Exp $
 */

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
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>

#ifdef SUPPORT_TCP

/*
 *  �֐�
 */

static ER send_segment (bool_t *sendalot, T_TCP_CEP *cep, uint_t doff, uint_t win, uint_t len, uint8_t flags);
static void tcp_output (T_TCP_CEP *cep);

/*
 *  �ϐ�
 */

/* �o�͎��̃t���O�� FSM ��Ԃɂ��I�����邽�߂̕\ */

const static uint8_t tcp_outflags[] = {
	TCP_FLG_RST | TCP_FLG_ACK,	/*  0, �N���[�Y				*/
	0,				/*  1, �󓮃I�[�v��			*/
	TCP_FLG_SYN,			/*  2, �\���I�[�v���ASYN ���M�ς�	*/
	TCP_FLG_SYN | TCP_FLG_ACK,	/*  3, SYM ����M���ASYN ���M�ς�	*/
	TCP_FLG_ACK,			/*  4, �R�l�N�V�����J�݊���		*/
	TCP_FLG_ACK,			/*  5, FIN ��M�A�N���[�Y�҂�		*/
	TCP_FLG_FIN | TCP_FLG_ACK,	/*  6, �I�����āAFIN ���M�ς�		*/
	TCP_FLG_FIN | TCP_FLG_ACK,	/*  7, �I���AFIN �����ς݁AACK �҂�	*/
	TCP_FLG_FIN | TCP_FLG_ACK,	/*  8, FIN ��M�A�I���AACK �҂�		*/
	TCP_FLG_ACK,			/*  9, �I���AFIN �`�B�m�F��M�AFIN�҂�	*/
	TCP_FLG_ACK,			/* 10, �I���A���ԑ҂�			*/
	};

/*
 *  send_segment -- TCP �o�͏���
 */

static ER
send_segment (bool_t *sendalot, T_TCP_CEP *cep, uint_t doff, uint_t win, uint_t len, uint8_t flags)
{
	T_NET_BUF	*output;
	T_TCP_HDR	*tcph;
	uint_t		optlen;
	ER		error;

#ifdef TCP_CFG_OPT_MSS

	uint8_t		*optp;

	if (flags & TCP_FLG_SYN)
		optlen = TCP_OPT_LEN_MAXSEG;
	else
		optlen = 0;

#else/* of #ifdef TCP_CFG_OPT_MSS */

	optlen = 0;

#endif/* of #ifdef TCP_CFG_OPT_MSS */

	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_SEGS], 1);
	NET_COUNT_MIB(tcp_stats.tcpOutSegs, 1);

	/*
	 *  �Z�O�����g�����A����̍ő��M�Z�O�����g���ɒ�������B
	 *  �����A�����Ă���ꍇ�́A������������ő��M����B
	 *  ���̂��߁AFIN �r�b�g���N���A����B
	 *
	 *  �I���W�i���ł́At_maxopd �𐧌����ɂ��Ă��邪�A
	 *  �{�����ł́A����̍ő��M�Z�O�����g�ɂ���B
	 */
	if (len + optlen > cep->maxseg) {
		flags &= ~TCP_FLG_FIN;
		len = cep->maxseg - optlen;
		*sendalot = true;
		}

	/*
	 *  ���M�o�b�t�@����ɂȂ�Ƃ��� PUSH �t���O��ݒ肷��B
	 */
	if (len && doff + len >= cep->swbuf_count)
		flags |= TCP_FLG_PUSH;

#if defined(TCP_CFG_SWBUF_CSAVE_ONLY)
		
	if (len > 0 && ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SEND_READY ||
	                (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SENT)) {

		/*
		 *  ���M�E�C���h�o�b�t�@���J������Ȃ��悤�ɂ��āA
		 *  �l�b�g���[�N�o�b�t�@���o�͂Ɉڂ��B
		 */
		cep->swbufq->flags |= NB_FLG_NOREL_IFOUT;
		output = cep->swbufq; 
		}
	else {

		/*
		 *  ACK ������ԂŁA���̊֐����Ăяo����邱�Ƃ�����B
		 *  ���̎��́Alen �� 0 �ɂ��āA�������p������B
		 */
		len = 0;
		if ((error = tcp_get_segment(&output, cep, optlen,
	                                    len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
	                                    NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
			if (cep->timer[TCP_TIM_REXMT] == 0)
				cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			goto err_ret;
			}
		}

#elif defined(TCP_CFG_SWBUF_CSAVE)	/* of #if defined(TCP_CFG_SWBUF_CSAVE_ONLY) */

	if (IS_PTR_DEFINED(cep->sbuf)) {
		if ((error = tcp_get_segment(&output, cep, optlen,
		                             len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
		                             NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
			if (cep->timer[TCP_TIM_REXMT] == 0)
				cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			goto err_ret;
			}
		}
	else if (len > 0 && ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SEND_READY ||
	                     (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SENT)) {

		/*
		 *  ���M�E�C���h�o�b�t�@���J������Ȃ��悤�ɂ��āA
		 *  �l�b�g���[�N�o�b�t�@���o�͂Ɉڂ��B
		 */
		cep->swbufq->flags |= NB_FLG_NOREL_IFOUT;
		output = cep->swbufq; 
		}
	else {

		/*
		 *  ACK ������ԂŁA���̊֐����Ăяo����邱�Ƃ�����B
		 *  ���̎��́Alen �� 0 �ɂ��āA�������p������B
		 */
		len = 0;
		if ((error = tcp_get_segment(&output, cep, optlen,
	                                    len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
	                                    NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
			if (cep->timer[TCP_TIM_REXMT] == 0)
				cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			goto err_ret;
			}
		}

#else	/* of #if defined(TCP_CFG_SWBUF_CSAVE_ONLY) */

	if ((error = tcp_get_segment(&output, cep, optlen,
	                             len, (uint_t)(net_buf_max_siz() - IF_IP_TCP_HDR_SIZE),
	                             NBA_SEARCH_ASCENT, TMO_TCP_GET_NET_BUF)) != E_OK) {
		if (cep->timer[TCP_TIM_REXMT] == 0)
			cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
		goto err_ret;
		}

#endif	/* of #if defined(TCP_CFG_SWBUF_CSAVE_ONLY) */

	/*
	 *  TCP �I�v�V�����̐ݒ���s���B
	 *  �{�����ł́A�ő�Z�O�����g�T�C�Y�̂ݐݒ肷��B
	 */
	if (flags & TCP_FLG_SYN) {
		cep->snd_nxt = cep->iss;

#ifdef TCP_CFG_OPT_MSS

		optp = GET_TCP_OPT(output, IF_IP_TCP_HDR_OFFSET);
		*optp ++ = TCP_OPT_MAXSEG;
		*optp ++ = TCP_OPT_LEN_MAXSEG;
		*(uint16_t*)optp = htons(DEF_TCP_RCV_SEG);

#endif/* of #ifdef TCP_CFG_OPT_MSS */

		}

	/* TCP SDU �ɑ��M�f�[�^���R�s�[����B*/

	if (len > 0) {
		if (SEQ_LT(cep->snd_nxt, cep->snd_max)) {
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_REXMIT_SEGS], 1);
			NET_COUNT_MIB(tcp_stats.tcpRetransSegs, 1);
			}
		TCP_READ_SWBUF(cep, output, len, doff);
		}
	else {
		if (cep->flags & TCP_CEP_FLG_ACK_NOW)
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_ACKS], 1);
		if (flags & (TCP_FLG_FIN | TCP_FLG_SYN | TCP_FLG_RST))
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_CNTL_SEGS],  1);


#ifdef TCP_CFG_EXTENTIONS

		if (SEQ_LT(cep->snd_up, cep->snd_una))
			NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_URG_SEGS], 1);

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		}

	/*
	 * snd_max: ���M�����ő� SEQ
	 * snd_nxt: ���ɑ��M���� SEQ
	 *
	 *  ���肩�� FIN ����M���A�܂� FIN �𑗐M���Ă��Ȃ����A
	 *  ����f�[�^���Ȃ��Ƃ��́AFIN �𑊎�ɓ͂��邽�߁A
	 *  �Z�O�����g�𑗐M���邪�ASEQ �͐i�߂Ȃ��B
	 */
	if ((flags & TCP_FLG_FIN) && (cep->flags & TCP_CEP_FLG_SENT_FIN) &&
	    cep->snd_nxt == cep->snd_max) {
		cep->snd_nxt --;
		}

	tcph = GET_TCP_HDR(output, IF_IP_TCP_HDR_OFFSET);

	/*
	 *  SEQ�AACK�A�t���O�̐ݒ�B
	 */
	if (len > 0 || (flags & (TCP_FLG_SYN | TCP_FLG_FIN)) || cep->timer[TCP_TIM_PERSIST] != 0)
		tcph->seq = htonl(cep->snd_nxt);
	else
		tcph->seq = htonl(cep->snd_max);

	/*
	 *  rcv_nxt: ��M�����҂��Ă���ŏ��� SEQ
	 */
	tcph->ack   = htonl(cep->rcv_nxt);
	tcph->flags = flags;

	/*
	 *  ��M�E�B���h�̌v�Z
	 *
	 *  rbufsz: ��M�p�o�b�t�@�T�C�Y
	 *  maxseg: ����̍ő��M�Z�O�����g�T�C�Y	
	 */
	if (win < (cep->rbufsz / 4) && win < cep->maxseg)
		win = 0;

	/*
	 *  rcv_nxt: ��M�����҂��Ă���ŏ��� SEQ
	 *  rcv_adv: ��M�����҂��Ă���ő�� SEQ
	 */
	if ((int32_t)win < (int32_t)(cep->rcv_adv - cep->rcv_nxt))
		win = (uint_t)(cep->rcv_adv - cep->rcv_nxt);

	tcph->win = htons(win);

#ifdef TCP_CFG_EXTENTIONS

	/*
	 *  �ً}�|�C���^�̐ݒ�
	 */
	if (SEQ_GT(cep->snd_up, cep->snd_nxt)) {
		if (TCP_CFG_URG_OFFSET)
			tcph->urp    = htons((uint16_t)(cep->snd_up - cep->snd_nxt));
		else
			tcph->urp    = htons((uint16_t)(cep->snd_up - cep->snd_nxt - 1));
		tcph->flags |= TCP_FLG_URG;
		}
	else
		cep->snd_up  = cep->snd_una;

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	/*
	 *  �`�F�b�N�T����ݒ肷��B
	 */
	tcph->sum = 0;
	tcph->sum = IN_CKSUM(output, IPPROTO_TCP, (uint_t)GET_TCP_HDR_OFFSET(output),
		             GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET) + len);

	/* �l�b�g���[�N�o�b�t�@���𒲐�����B*/
	output->len = (uint16_t)(GET_IF_IP_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET) + len);

	/*
	 *  �^�C�}�̒���
	 */
	if ((cep->flags & TCP_CEP_FLG_FORCE) == 0 || cep->timer[TCP_TIM_PERSIST] == 0) {
		T_TCP_SEQ startseq = cep->snd_nxt;

		/*
		 *  ���ɑ��M���� SEQ (snd_nxt) �����񑗐M����f�[�^�����i�߂�B
		 */
		if (flags & TCP_FLG_SYN)
			cep->snd_nxt ++;
		if (flags & TCP_FLG_FIN) {
			cep->flags |= TCP_CEP_FLG_SENT_FIN;
			cep->snd_nxt ++;
			}

		cep->snd_nxt += len;

		/*
		 *  ���ɑ��M���� SEQ (snd_nxt) ��
		 *  ���M�����ő� SEQ (snd_max) ���i��ł���΁A
		 *  ���M�����ő� SEQ (snd_max) ���X�V����B
		 */
		if (SEQ_GT(cep->snd_nxt, cep->snd_max)) {
			cep->snd_max = cep->snd_nxt;
			/*
			 *  �����A�������Ԍv�����s���Ă��Ȃ���΁A
			 *  ���̑��M�Ɏ��Ԃ����킹��B
			 */
			if (cep->rtt == 0) {
				cep->rtt   = 1;
				cep->rtseq = startseq;	/* �X�V�O�� cep->snd_nxt */
				}
			}

		/*
		 *  �����ݒ肳��Ă��Ȃ����AACK �܂��͕ۗ����������Ă��Ȃ���΁A
		 *  �đ��^�C�}��ݒ肷��B�ݒ肷�鏉���l�́A
		 * �u���炩�ȉ������� + 2 �~ �������ԕϓ��v�ł���B
		 *  �đ����Ԃ̃o�b�N�I�t�Ɏg����V�t�g�J�E���g������������B
		 */
		if (cep->timer[TCP_TIM_REXMT] == 0 && cep->snd_nxt != cep->snd_una) {
			cep->timer[TCP_TIM_REXMT] = cep->rxtcur;
			if (cep->timer[TCP_TIM_PERSIST] != 0) {
				cep->timer[TCP_TIM_PERSIST] = 0;
				cep->rxtshift = 0;
				}
			}
		}

	/*
	 *  ���ɑ��M���� SEQ (snd_nxt) + ���񑗐M����f�[�^�� (len) ��
	 *  ���M�����ő� SEQ (snd_max) ���i��ł���΁A
	 *  ���M�����ő� SEQ (snd_max) ���X�V����B
	 */
	else if (SEQ_GT(cep->snd_nxt + len, cep->snd_max))
		cep->snd_max = cep->snd_nxt + len;

#ifdef TCP_CFG_SWBUF_CSAVE

	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SEND_READY)
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_SENT;

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

#ifdef TCP_CFG_TRACE

	tcp_output_trace(output, cep);

#endif	/* of #ifdef TCP_CFG_TRACE */

	/* �l�b�g���[�N�w (IP) �̏o�͊֐����Ăяo���B*/
	if ((error = IP_OUTPUT(output, TMO_TCP_OUTPUT)) != E_OK)
		goto err_ret;

	/*
	 *  ����ɓ`�����E�B���h�E�T�C�Y (win) �� 0 �ȏ�ŁA
	 *  ��M�����҂��Ă���ŏ��� SEQ (rcv_nxt) + win ��
	 *  ��M�����҂��Ă���ő�� SEQ (rcv_adv) ���i��ł����
	 *  ��M�����҂��Ă���ő�� SEQ ���X�V����B
	 */
	if (win > 0 && SEQ_GT(cep->rcv_nxt + win, cep->rcv_adv)) {
		cep->rcv_adv = cep->rcv_nxt + win;
		}

	/*
	 *  �Ō�ɑ��M���� ACK (last_ack_sent) ���X�V����B
	 */
	cep->last_ack_sent = cep->rcv_nxt;

	/*
	 *  �t���O�̐ݒ���s���B
	 */
	cep->flags &= ~(TCP_CEP_FLG_ACK_NOW | TCP_CEP_FLG_DEL_ACK);
	if (cep->flags & TCP_CEP_FLG_FORCE_CLEAR)
		cep->flags &= ~(TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR);

	return E_OK;

err_ret:
	/*
	 * �ȉ��Ɋ֌W���Ȃ��t���O���N���A�[����B
	 * �E����M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\
	 * �E���I�ȒʐM�[�_�̐����E�폜�@�\
	 */
	cep->flags &= (TCP_CEP_FLG_WBCS_NBUF_REQ | TCP_CEP_FLG_WBCS_MASK | 
	               TCP_CEP_FLG_DYNAMIC       | TCP_CEP_FLG_VALID);

	return error;
	}

/*
 *  tcp_output -- TCP �o�͏���
 */

void
tcp_output (T_TCP_CEP *cep)
{
	bool_t	sendalot = true, idle;
	ER	error = E_OK;
	int32_t	len;
	uint_t	doff, win;
	uint8_t	flags;

	/*
	 *  snd_una: ���m�F�̍ŏ����M SEQ	 �܂��́A�m�F���ꂽ�ő呗�M SEQ
	 *  snd_max: ���M�����ő� SEQ
	 */
	idle = (cep->snd_max == cep->snd_una);

	/*
	 *  idle:   �A�C�h������
	 *  rxtcur: ���݂̍đ��^�C���A�E�g
	 */
	if (idle && cep->idle >= cep->rxtcur)

		/*
		 *  snd_cwnd: �t�s�E�B���h�T�C�Y
		 *  maxseg  : ����̍ő��M�Z�O�����g�T�C�Y
		 *
		 *  �����ԃA�C�h���������̂ŃX���[�X�^�[�g����ɐݒ肷��B
		 */
		cep->snd_cwnd = cep->maxseg;

	while (error == E_OK && sendalot) {
		sendalot = false;

		/*
		 *  snd_nxt: ���ɑ��M���� SEQ�A���̎��_�ł́A�O�񑗐M���� SEQ
		 *  snd_una: ���m�F�̍ŏ����M SEQ�A�܂��͊m�F���ꂽ�ő呗�M SEQ
		 *
		 *  doff: ���M���J�n����I�t�Z�b�g�B
		 *                                    swbuf_count (���M�o�b�t�@�ɂ���I�N�e�b�g��)
		 *    0                               V
		 *    +-------------------------------------------+
		 *    |                    sbuf                   |
		 *    +-------------------------------------------+
		 *    ^               ^
		 *    |<------------->snd_nxt (�O�񑗐M���� SEQ)
		 *    |       doff
		 *    snd_una (�܂��m�F����Ă��Ȃ�)
		 */
		doff = (uint_t)(cep->snd_nxt - cep->snd_una);

		/*
		 *  snd_wnd:  ����̎�M�\�E�B���h�T�C�Y
		 *  snd_cwnd: �t�s�E�B���h�T�C�Y
		 *
		 *  win: �ǂ��炩�������E�B���h�T�C�Y�ɐݒ肷��B
		 */
		win   = cep->snd_wnd < cep->snd_cwnd ? cep->snd_wnd : cep->snd_cwnd;
	
		/* �o�̓t���O�̐ݒ� */
		flags = tcp_outflags[cep->fsm_state];
		if (cep->flags & TCP_CEP_FLG_NEED_FIN)
			flags |= TCP_FLG_FIN;
		if (cep->flags & TCP_CEP_FLG_NEED_SYN)
			flags |= TCP_FLG_SYN;
		if (cep->flags & TCP_CEP_FLG_FORCE) {

			/*
			 *  �����A���M�E�C���h�T�C�Y (win) �� 0 �Ȃ� 1 �I�N�e�b�g���M����B
			 *  �����łȂ���΁A�����^�C���A�E�g���L�����Z�����A
			 *  �đ��M�� (rxtshift) �� 0 �ɂ���B
			 */
			if (win == 0) {

				/*
				 *  doff:        ���M����I�N�e�b�g���B
				 *  swbuf_count: ���M�o�b�t�@�̎g�p���T�C�Y
				 *
				 *  ���M�o�b�t�@�Ɏc���Ă���I�N�e�b�g���A���ꂩ��
				 *  ���M���悤�Ƃ��Ă���I�N�e�b�g����葽�����
				 *  FIN �t���O���N���A����B
				 */
				if (doff < cep->swbuf_count)
					flags &=~TCP_FLG_FIN;
				win = 1;
				}
			else {
				/*
				 *  TCP_TIM_PERSIST: �����^�C�}
				 *  rxtshift:        �đ��M�񐔂� log(2)
				 */
				cep->timer[TCP_TIM_PERSIST] = 0;
				cep->rxtshift = 0;
				}
		 	}

		/*
		 *  len: ���񑗐M����I�N�e�b�g��
		 *        swbuf_count (���M�o�b�t�@�ɂ���I�N�e�b�g��)
		 *                                    |
		 *    0                               V
		 *    +-------------------------------------------+
		 *    |                    sbuf       |           |
		 *    +-------------------------------------------+
		 *    ^               ^<------------->
		 *    |               |      len
		 *    |<------------->snd_nxt (�O�񑗐M���� SEQ)
		 *    |       doff
		 *    snd_una (�܂��m�F����Ă��Ȃ�)
		 */
		if (cep->swbuf_count < win)
			len = (int32_t)cep->swbuf_count - doff;
		else
			len = (int32_t)win - doff;

		/*
		 *  ���łɑ��M����Ă���΁ASYN �r�b�g���I�t����B
		 *  �������A�ȉ��̏����ł͑��M���T����B
		 *
		 *    �E��Ԃ� SYN ���M�B
		 *    �E�Z�O�����g���f�[�^���܂�ł���B
		 */
		if ((flags & TCP_FLG_SYN) && SEQ_GT(cep->snd_nxt, cep->snd_una)) {
			flags &= ~TCP_FLG_SYN;
			doff --;		/* -1 �� SYN �t���O�� */
			len ++;			/* +1 �� SYN �t���O�� */
			if (len > 0 && cep->fsm_state == TCP_FSM_SYN_SENT)
				break;
			}

		if (flags & TCP_FLG_SYN) {
			len = 0;
			flags &= ~TCP_FLG_FIN;
			}

		if (len < 0) {

			/*
			 *  len �� 0 �ȉ��Ȃ�A0 �ɐݒ肷��B
			 *  �����A���M�E�B���h�E�T�C�Y�� 0 �Ȃ�A
			 *  �đ��M�^�C�}���L�����Z�����A
			 *  �O�񑗐M���� SEQ (snd_nxt) ��
			 *  �m�F���ꂽ�ő呗�M SEQ (snd_una) �ɖ߂��B
			 *  �����āA�����^�C�}�[���~�܂��Ă���΁A�Đݒ肷��B
			 */
			len = 0;
			if (win == 0) {
				cep->timer[TCP_TIM_REXMT] = 0;
				cep->rxtshift = 0;
				cep->snd_nxt  = cep->snd_una;
				if (cep->timer[TCP_TIM_PERSIST] == 0)
					tcp_set_persist_timer(cep);
				}
			}


		/*
		 *  ���񑗐M����I�N�e�b�g�� (len) �́A
		 *  ����̍ő��M�Z�O�����g�T�C�Y (maxseg) �𒴂��Ȃ��悤�ɂ���B
		 */
		if (len > cep->maxseg) {
			len = cep->maxseg;
			sendalot = true;
			}

		/*
                 *        swbuf_count (���M�o�b�t�@�ɂ���I�N�e�b�g��)
                 *                                           |
		 *    0                                      V
		 *    +-------------------------------------------+
		 *    |                    sbuf       |           |
		 *    +-------------------------------------------+
		 *    ^               ^<------------->
		 *    |               |      len
		 *    |<------------->snd_nxt (�O�񑗐M���� SEQ)
		 *    |       doff
		 *    snd_una (�܂��m�F����Ă��Ȃ�)
		 *
		 *  ���񑗐M����A���M�o�b�t�@�Ƀf�[�^���c���Ă����
		 *  FIN �t���O���N���A����B
		 */
		if (SEQ_LT(cep->snd_nxt + len, cep->snd_una + cep->swbuf_count))
			flags &= ~TCP_FLG_FIN;

		/*
		 *  �������� win �́A��M�E�B���h�E�T�C�Y�B
		 *  ��M�o�b�t�@�̋󂫗e��
		 */
		win = cep->rbufsz - cep->rwbuf_count;

		/*
		 *  �����ȃE�B���h�E�E�V���h���[���̉������ (���M��)
		 *
		 *  �ȉ��̏����ŁA���M���s���B
		 *
		 *    �E�t���T�C�Y (maxseg) �̃Z�O�����g�𑗂邱�Ƃ��ł���B
		 *    �E����̍ő�̎�M�E�B���h�E�T�C�Y�� 1/2 �̃f�[�^��
		 *      ���邱�Ƃ��ł���B
		 *    �E���M�o�b�t�@����ɂł��A�A�C�h������x���I�v�V�������L���ȂƂ��B
		 */
		if (len) {

			/*
			 *  ���񑗐M����I�N�e�b�g�� (len) ��
			 *  ����̍ő��M�Z�O�����g�T�C�Y (maxseg) ��
			 *  ��v����Ƃ��͑��M����B
			 */
			if (len == cep->maxseg) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}

			/*
			 *  ����̑��M�ŁA���M�o�b�t�@����ɂł��A
			 *  �A�C�h������ PUSH �I�v�V�������L���ȂƂ��B
			 */
			if ((idle || (cep->flags & TCP_CEP_FLG_NO_DELAY)) &&
			    (cep->flags & TCP_CEP_FLG_NO_PUSH) == 0 &&
			    len + doff >= cep->swbuf_count) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}

			/*
			 *  max_sndwnd: ���܂ł̍ő呗�M�E�B���h�T�C�Y
			 *  snd_nxt:    ���ɑ��M���� SEQ
			 *  snd_max:    ���M�����ő� SEQ
			 *
			 *  ���̏����ł͑��M���s���B
			 *
			 *    �E�������M�t���O���Z�b�g����Ă���B
			 *    �E�f�[�^��������̍ő�̎�M�E�B���h�E�T�C�Y�� 1/2 �ȏ�ŁA
			 *      ����̍ő�̎�M�E�B���h�E�T�C�Y�� 0 ���傫���B
			 *    �E���ɑ��M���� SEQ �����M�����ő� SEQ ��菬�����A
			 *      �܂�A�đ�����Ƃ��B
			 */
			if ((cep->flags & TCP_CEP_FLG_FORCE) ||
			    (len >= cep->max_sndwnd / 2 && cep->max_sndwnd > 0) ||
			    SEQ_LT(cep->snd_nxt, cep->snd_max)) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}
			}


		/*
		 *  �����ȃE�B���h�E�E�V���h���[���̉������ (��M��)
		 *
		 *  �E�B���h�E�T�C�Y���t���T�C�Y�� 2 �{�̃Z�O�����g�A���邢��
		 *  ��M�o�b�t�@�e�ʂ� 1/2 �́A�����ꂩ�������ق���
		 *  �T�C�Y�ő��������ꍇ�́A�E�B���h�E�T�C�Y�̍X�V���s���B
		 */
		if (win > 0) {
			long adv;

			/*
			 *  win:              ��M�o�b�t�@�̋󂫗e��
			 *  MAX_TCP_WIN_SIZE: TCP �w�b�_�� win �t�B�[���h�ɐݒ�ł���ő�l
			 *  rcv_adv:          ��M�����҂��Ă���ő�� SEQ
			 *  rcv_nxt:          ��M�����҂��Ă���ŏ��� SEQ
			 */
			if (win < MAX_TCP_WIN_SIZE)
				adv = win - (cep->rcv_adv - cep->rcv_nxt);
			else
				adv = MAX_TCP_WIN_SIZE - (cep->rcv_adv - cep->rcv_nxt);

			if (adv     >= (long)(cep->maxseg * 2) ||
			    adv * 2 >= (long) cep->rbufsz) {
				error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
				continue;
				}
			}
	
		/*
		 *  ACK �𑗐M����B
		 */
		if (cep->flags & TCP_CEP_FLG_ACK_NOW) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

		if ( (flags & TCP_FLG_RST) ||
		    ((flags & TCP_FLG_SYN) && (cep->flags & TCP_CEP_FLG_NEED_SYN) == 0)) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

#ifdef TCP_CFG_EXTENTIONS

		if (SEQ_GT(cep->snd_up, cep->snd_una)) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		/*
		 *  snd_nxt: ���ɑ��M���� SEQ
		 *  snd_una: ���m�F�̍ŏ����M SEQ�A�܂��͊m�F���ꂽ�ő呗�M SEQ
		 *
		 *  ���肩�� FIN ����M���A�܂� FIN �𑗐M���Ă��Ȃ����A
		 *  ����f�[�^���Ȃ��Ƃ��́AFIN �𑊎�ɓ͂��邽�߁A
		 *  �Z�O�����g�𑗐M����B
		 */
		if ((flags & TCP_FLG_FIN) &&
		    ((cep->flags & TCP_CEP_FLG_SENT_FIN) == 0 || cep->snd_nxt == cep->snd_una)) {
			error = send_segment(&sendalot, cep, doff, win, (uint_t)len, flags);
			continue;
			}

		/*
		 *  ���M���ׂ��f�[�^������A�đ��^�C�}�Ǝ����^�C�}���؂�Ă���Ƃ���
		 *  �����^�C�}��ݒ肷��B
		 */
		if (cep->swbuf_count && cep->timer[TCP_TIM_REXMT  ] == 0 &&
		                        cep->timer[TCP_TIM_PERSIST] == 0) {
			cep->rxtshift = 0;
			tcp_set_persist_timer(cep);
			break;
			}
		
		}
	}

#ifdef TCP_CFG_SWBUF_CSAVE

/*
 *  tcptsk_alloc_swbufq -- ���M�E�B���h�o�b�t�@���蓖��
 */

static void
tcptsk_alloc_swbufq (T_TCP_CEP *cep)
{
 	ER	error;
	uint_t	win;

	/*
	 *  snd_wnd:  ����̎�M�\�E�B���h�T�C�Y
	 *  snd_cwnd: �t�s�E�B���h�T�C�Y
	 *
	 *  win: �ǂ��炩�������E�B���h�T�C�Y�ɐݒ肷��B
	 */
	win = cep->snd_wnd < cep->snd_cwnd ? cep->snd_wnd : cep->snd_cwnd;

	/*
	 *  ����̎�M�E�B���h�����Ă���ꍇ�́A�J���܂őҋ@����B
	 */
	if (win == 0) {
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_WOPEN_PEND;
		}
	else {

#ifdef TCP_CFG_NON_BLOCKING

		/* �m���u���b�L���O�R�[�� */
		if (!IS_PTR_DEFINED(cep->callback)) {
			syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

			/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
			cep->snd_tskid = TA_NULL;
			cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
			return;
			}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		if ((error = tcp_get_segment(&cep->swbufq, cep, 0,
		                             (uint_t) TCP_CFG_SWBUF_CSAVE_MIN_SIZE,
		                             (uint_t)(TCP_CFG_SWBUF_CSAVE_MAX_SIZE - IF_IP_TCP_HDR_SIZE),
		                             (ATR)(NBA_SEARCH_DESCENT |
		                                   NBA_RESERVE_TCP    |
		                                   (GET_TCP_CEPID(cep) & NBA_ID_MASK)), TMO_POL)) != E_OK) {

			/* �l�b�g���[�N�o�b�t�@��\�񂷂�B*/
			cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_NBUF_PEND;
			}
		else {

			/* ���M�E�B���h�o�b�t�@������������B*/
			tcp_init_swbuf(cep);

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->snd_nblk_tfn == TFN_TCP_GET_BUF) {

				uint_t len;

				/* ���M�E�B���h�o�b�t�@�̏������݃A�h���X��ݒ肷��B*/
				len = TCP_GET_SWBUF_ADDR(cep, cep->snd_p_buf);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				/* �R�[���o�b�N�֐����Ăяo���B*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				/* �R�[���o�b�N�֐����Ăяo���B*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */


				/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}

			else {	/* cep->snd_nblk_tfn == TFN_TCP_SND_DAT || */
				/* cep->snd_nblk_tfn == TFN_TCP_SND_OOB    */

				uint_t len;

				/* ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB*/
				len = TCP_WRITE_SWBUF(cep, cep->snd_data, (uint_t)cep->snd_len);

#ifdef TCP_CFG_EXTENTIONS

				/* ���M�ً}�|�C���^��ݒ肷��B*/
			        if (cep->snd_nblk_tfn == TFN_TCP_SND_OOB)
					cep->snd_up = cep->snd_una + len;

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

				/* �t���O���A���M�\�ɐݒ肵�A�����I�ɑ��M����B*/
				cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR | TCP_CEP_FLG_POST_OUTPUT;
#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				/* �R�[���o�b�N�֐����Ăяo���B*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				/* �R�[���o�b�N�֐����Ăяo���B*/
				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */


				/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			}
		}
	}

/*
 *  tcptsk_free_swbufq -- ���M�E�B���h�o�b�t�@�J��
 */

static void
tcptsk_free_swbufq (T_TCP_CEP *cep)
{
	/*
	 *  ��M�m�F���������A�l�b�g���[�N�C���^�t�F�[�X�����
	 *  �o�͂����������Ƃ��́A���M�E�B���h�o�b�t�@�L���[���������B
	 */

	/* ���M�E�B���h�o�b�t�@�̎g�p���T�C�Y�����Z�b�g����B*/
	cep->swbuf_count = 0;

	/* ���M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B*/
	syscall(rel_net_buf(cep->swbufq));
	cep->swbufq = NULL;

	/* �t���O���󂫂ɐݒ肷��B*/
	cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_FREE;

	/* ���M�E�B���h�o�b�t�@�ɋ󂫂��ł������Ƃ�m�点��B*/
	syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

	/* ���M�E�B���h�o�b�t�@�̋󂫑҂��̂Ƃ��́ATCP �o�̓^�X�N���N������B*/
	if ((cep->flags & TCP_CEP_FLG_WBCS_NBUF_REQ) != 0) {
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

/*
 *  TCP �o�̓^�X�N
 */

void
tcp_output_task (intptr_t exinf)
{
	static int_t last_ix = 0;

	T_TCP_CEP	*cep;
	ID		tskid;
 	int_t		ix, sel_ix;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP OUTPUT:%d] started.", tskid);

	tcp_init();

#ifdef SUPPORT_INET6

	/* IPv6 �̃X�e�[�g���X�E�A�h���X�����ݒ�����s����B*/
	in6_if_up(IF_GET_IFNET());

#endif	/* of #ifdef SUPPORT_INET6 */

	while (true) {

		/* �o�͂��|�X�g�����܂ő҂B*/
		syscall(wai_sem(SEM_TCP_POST_OUTPUT));

		if (++ last_ix == tmax_tcp_cepid)
			last_ix = 0;
		sel_ix = ix = last_ix;
		do {
			cep = &tcp_cep[ix];

#ifdef TCP_CFG_SWBUF_CSAVE

			if ((cep->flags & TCP_CEP_FLG_WBCS_NBUF_REQ) != 0 &&
			    ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_FREE ||
			     (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_RSVD)) {
				tcptsk_alloc_swbufq(cep);
				sel_ix = ix;
				}

			if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_ACKED &&
			    (cep->swbufq->flags & NB_FLG_NOREL_IFOUT) == 0) {
				tcptsk_free_swbufq(cep);
				sel_ix = ix;
				}

			/*
			 *  �l�b�g���[�N�C���^�t�F�[�X���瑗�M���I����Ă��Ȃ��Ƃ��́A
			 *  ���M��\�񂷂�B
			 */
			if (cep->flags & TCP_CEP_FLG_POST_OUTPUT &&
			   (cep->flags & TCP_CEP_FLG_WBCS_MASK) >= TCP_CEP_FLG_WBCS_SENT) {
				syscall(wai_sem(cep->semid_lock));
				if (cep->swbufq == NULL)
					cep->flags &= ~TCP_CEP_FLG_POST_OUTPUT;
				else if (cep->swbufq->flags & NB_FLG_NOREL_IFOUT) {
					cep->flags &= ~TCP_CEP_FLG_POST_OUTPUT;
					cep->flags |=  TCP_CEP_FLG_RESERVE_OUTPUT;
					}
				syscall(sig_sem(cep->semid_lock));
				}

			/*
			 *  ���M�\�񒆂ɁA�l�b�g���[�N�C���^�t�F�[�X���瑗�M���I��������A
			 *  ���M���J�n����B�������A���S�ɑ��M���I�������Ƃ��͉������Ȃ��B
			 */
			if (cep->flags & TCP_CEP_FLG_RESERVE_OUTPUT) {
				syscall(wai_sem(cep->semid_lock));
				if (cep->swbufq != NULL && (cep->swbufq->flags & NB_FLG_NOREL_IFOUT) == 0) {
					cep->flags |=  TCP_CEP_FLG_POST_OUTPUT;
					}
				syscall(sig_sem(cep->semid_lock));
				cep->flags &= ~TCP_CEP_FLG_RESERVE_OUTPUT;
				}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

			if (cep->flags & TCP_CEP_FLG_POST_OUTPUT) {

				cep->flags &= ~TCP_CEP_FLG_POST_OUTPUT;

#ifdef TCP_CFG_NON_BLOCKING

				if (cep->snd_nblk_tfn == TFN_TCP_CON_CEP && cep->myaddr.portno == TCP_PORTANY) {
				 	ER	error;

					/*
					 *  tcp_con_cep �̃m���u���b�L���O�R�[���ŁA
					 *  �������̂̏ꍇ�́A�|�[�g�ԍ������蓖�Ă�B
					 *  p_myaddr �� NADR (-1) ���A
					 *  ���|�[�g�ԍ��� TCP_PORTANY �Ȃ�A�����Ŋ��蓖�Ă�B
					 */
					if (cep->p_myaddr == NADR || cep->p_myaddr->portno == TCP_PORTANY)
						tcp_alloc_auto_port(cep);
					else if ((error = tcp_alloc_port(cep, cep->p_myaddr->portno)) != E_OK) {

						if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

							(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

							(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

						else
							syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

						/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
						cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
						cep->snd_tskid = TA_NULL;
						continue;
						}
					}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

				tcp_output(cep);

				if (cep->flags & TCP_CEP_FLG_CLOSE_AFTER_OUTPUT) {
					/* �R�l�N�V���������B*/
					tcp_close(cep);
					cep->flags &= ~TCP_CEP_FLG_CLOSE_AFTER_OUTPUT;
					}

				if (cep->flags & TCP_CEP_FLG_RESTORE_NEXT_OUTPUT) {
					/* snd_nxt �����ɖ߂��B*/
					if (SEQ_GT(cep->snd_old_nxt, cep->snd_nxt))
						cep->snd_nxt = cep->snd_old_nxt;
					cep->flags &= ~TCP_CEP_FLG_RESTORE_NEXT_OUTPUT;
					}

				sel_ix = ix;
				}

			if (++ ix == tmax_tcp_cepid)
				ix = 0;
			} while (ix != last_ix);

		/* ����́A���������ʐM�[�_����񂵂ɂ���B*/
		last_ix = sel_ix;
		}
	}

#endif	/* of #ifdef SUPPORT_TCP */
