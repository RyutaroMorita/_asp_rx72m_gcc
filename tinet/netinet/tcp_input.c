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
 *  @(#) $Id: tcp_input.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 *
 *	@(#)tcp_input.c	8.12 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_input.c,v 1.82.2.3 1999/10/14 11:49:38 des Exp $
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
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>

#ifdef SUPPORT_TCP

/*
 *  �߂�l
 *
 *      RET_OK		����
 *	RET_DROP	�G���[�A�Z�O�����g��j������B
 *	RET_RST_DROP	�G���[�ARST �𑗐M���A�Z�O�����g��j������B
 */

#define RET_OK		(0)
#define RET_NEED_OUTPUT	(1)
#define RET_RETURN	(2)
#define RET_DROP	(-1)
#define RET_RST_DROP	(-2)

/*
 *  �֐�
 */

static void close_connection	(T_TCP_CEP *cep, bool_t *needoutput);
static void set_rexmt_timer	(T_TCP_CEP *cep,  T_TCP_TIME rtt);
static uint8_t reassemble		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, uint8_t flags);
static ER drop_after_ack	(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff);
static ER listening		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, T_TCP_SEQ iss);
static ER proc_ack1		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput);
static ER proc_ack2		(T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput);
static ER syn_sent		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static void trim_length		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static void parse_option	(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static bool_t update_wnd		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);
static void proc_urg		(T_TCP_HDR *tcph,  T_TCP_CEP *cep);

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

/*
 *  �^�X�N����� Time Wait ��� CEP �����@�\
 */

/*
 *  �֐�
 */

static T_TCP_TWCEP*tcp_find_twcep (T_IN_ADDR *dstaddr,  uint16_t dstport,
                                   T_IN_ADDR *peeraddr, uint16_t peerport);

/*
 *  �ϐ�
 */

T_TCP_TWCEP tcp_twcep[NUM_TCP_TW_CEP_ENTRY];

/*
 *  tcp_find_twcep -- �|�[�g�ԍ����� Time Wait �p TCP �ʐM�[�_�𓾂�B
 *
 *    ����: dstaddr �́A�l�b�g���[�N�o�C�g�I�[�_
 */

static T_TCP_TWCEP*
tcp_find_twcep (T_IN_ADDR *dstaddr, uint16_t dstport, T_IN_ADDR *peeraddr, uint16_t peerport)
{
	T_TCP_TWCEP*	twcep;
	
	/*
	 *  ��Ԃ� TIME WAIT �ŁA
	 *  IP �A�h���X�ƃ|�[�g�ԍ�����v����ʐM�[�_��T������B
	 */
	for (twcep = &tcp_twcep[NUM_TCP_TW_CEP_ENTRY]; twcep -- != tcp_twcep; ) {
		if (twcep->fsm_state == TCP_FSM_TIME_WAIT                   &&
		    IN_IS_DSTADDR_ACCEPT (&twcep->myaddr.ipaddr,  dstaddr)  &&
		    IN_ARE_NET_ADDR_EQUAL(&twcep->dstaddr.ipaddr, peeraddr) &&
		    dstport  == twcep->myaddr.portno                        &&
		    peerport == twcep->dstaddr.portno)
			return twcep;
		}

	return NULL;
	}

/*
 *  �K�v�ȏ��� Time Wait �p TCP �ʐM�[�_�Ɉڂ��āA
 *  �W���� TCP �ʐM�[�_���J������B
 */

void
tcp_move_twcep (T_TCP_CEP *cep)
{
	T_TCP_TWCEP*	twcep;

	/* �󂫂� Time Wait �p TCP �ʐM�[�_��T������B*/
	for (twcep = &tcp_twcep[NUM_TCP_TW_CEP_ENTRY]; twcep -- != tcp_twcep; ) {
		if (twcep->fsm_state != TCP_FSM_TIME_WAIT) {

			/*
			 *  �ʐM�[�_�����b�N���A
			 *  �K�v�ȏ��� Time Wait �p TCP �ʐM�[�_�Ɉڂ��B
			 */
			syscall(wai_sem(cep->semid_lock));
			twcep->rbufsz		= cep->rbufsz;
			twcep->dstaddr		= cep->dstaddr;
			twcep->myaddr		= cep->myaddr;
			twcep->snd_una		= cep->snd_una;
			twcep->rcv_nxt		= cep->rcv_nxt;
			twcep->rwbuf_count	= cep->rwbuf_count;
			twcep->fsm_state	= cep->fsm_state;
			twcep->timer_2msl	= cep->timer[TCP_TIM_2MSL];

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));

			/* �W�� TCP �ʐM�[�_���J������B*/
			tcp_close(cep);

			break;
			}
		}
	}

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

/*
 *  parse_option -- TCP �w�b�_�̃I�v�V��������͂���B
 */

static void
parse_option (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	uint8_t	*opt, type = 0;
	uint_t	len, ol, ssize;

	opt = (uint8_t*)tcph + TCP_HDR_SIZE;
	len = (uint_t)(TCP_HDR_LEN(tcph->doff) - TCP_HDR_SIZE);
	while (len > 0 && (type = *opt) != TCP_OPT_EOL) {
		if (type == TCP_OPT_NOP)
			ol = 1u;
		else {
			if (len < 2)
				break;
			ol = *(opt + 1);
			if (ol < 2 || ol > len)
				break;
			}
		switch (type) {
		case TCP_OPT_NOP:
			break;
		case TCP_OPT_MAXSEG:
			if ((ol == TCP_OPT_LEN_MAXSEG) && (tcph->flags & TCP_FLG_SYN)) {
				ssize = ntohs(*(uint16_t*)(opt + 2));
				if (ssize > MAX_TCP_SND_SEG)
					cep->maxseg = MAX_TCP_SND_SEG;
				else if (ssize < TCP_MINMSS)
					cep->maxseg = TCP_MINMSS;
				else
					cep->maxseg = ssize;
				}
			break;

		case TCP_OPT_WINDOW:
		case TCP_OPT_SACK_PERM:
		case TCP_OPT_TIMESTAMP:
		case TCP_OPT_CC:
		case TCP_OPT_CCNEW:
		case TCP_OPT_CCECHO:
			syslog(LOG_INFO, "[TCP] unsup opt: %d.", type);
			break;

		default:
			syslog(LOG_NOTICE, "[TCP] unexp opt: %d.", type);
			break;
			}
		opt += ol;
		len -= ol;
		}
	}

/*
 *  set_rexmt_timer -- �V�����������Ԃ����W���A�đ��^�C�}���X�V����B
 */

static void
set_rexmt_timer (T_TCP_CEP *cep, T_TCP_TIME rtt)
{
	T_TCP_TIME delta;

	NET_COUNT_TCP(net_count_tcp[NC_TCP_RTT_UPDATES], 1);
	if (cep->srtt != 0) {
		/*
		 *  srtt: ���������ꂽ RTT
		 *
		 *  �v�����ꂽ RTT (rtt) �ƌ��݂̕��������ꂽ RTT (srtt) �̍� (delta) �����߂�B
		 *
		 *  delta �� 2 �r�b�g���V�t�g ( 4 �{) �����l�ŕێ�����B
		 *  srtt  �� 5 �r�b�g���V�t�g (32 �{) �����l�ŕێ�����Ă���B
		 *
		 *    delta = rtt / 8 - srtt / 8
		 *
		 *  �V���� srtt ��
		 *
		 *    srtt = rtt / 8 + srtt * 7 / 8
		 *         = srtt + (rtt / 8 - srtt / 8)
		 *
		 *  �Ōv�Z����B
		 *  ���̂��߁Artt �� 2 �r�b�g���V�t�g���Asrtt �� (5 - 2) �r�b�g�E�V�t�g���� delta �����߂�B
		 */
		delta = ((rtt - 1) << TCP_DELTA_SHIFT) - (cep->srtt >> (TCP_SRTT_SHIFT - TCP_DELTA_SHIFT));
		cep->srtt += delta;
		if (cep->srtt <= 0)
			cep->srtt = 1;

		/*
		 *  delta �̐�Βl | delta | �����߂�B
		 */
		if (delta < 0)
			delta = - delta;

		/*
		 *  rttvar: ���������ꂽ���U
		 *
		 *  rttvar �� 4 �r�b�g���V�t�g (16 �{) �����l�ŕێ�����Ă���B
		 *
		 *    delta = |delta| / 4 - rttvar / 4
		 *
		 *  �V���� rttvar ��
		 *
		 *    rttvar = |delta|/ 4 + rttvar * 3 /4
		 *           = rttvar + (|delta| / 4 - rttvar / 4)
		 *
		 *  �Ōv�Z����B
		 */
		delta -= cep->rttvar >> (TCP_RTTVAR_SHIFT - TCP_DELTA_SHIFT);
		cep->rttvar += delta;
		if (cep->rttvar <= 0)
			cep->rttvar = 1;
		}
	else {
		/*
		 *  �܂� srtt �̐ݒ肪�s���Ă��Ȃ��Ƃ��́A����v�����ꂽ RTT ���g�p����B
		 *  ���������ꂽ RTT (srtt) �ɂ́ARTT �� 5 �r�b�g���V�t�g (32�{) �����l�B
		 *  ���������ꂽ���U (rttvar) �ɂ́ARTT �� 1/2 �� 4 �r�b�g���V�t�g (16�{) �����l�B
		 */
		cep->srtt   = rtt <<  TCP_SRTT_SHIFT;
		cep->rttvar = rtt << (TCP_RTTVAR_SHIFT - 1);
		}

	/*
	 *  rtt �̑�����I�����A�đ��񐔂����Z�b�g����B
	 */
	cep->rtt = cep->rxtshift = 0;

	/*
	 *  RTT �ɋ������ŏ��l �� rtt + 2 �̑傫�Ȓl�̕����đ��^�C���A�E�g�̍ŏ��l�ɂ���B
	 */
	if (rtt + 2 < TCP_TVAL_MIN)
		cep->rxtcur = tcp_range_set(tcp_rexmt_val(cep),
		                            (T_TCP_TIME)TCP_TVAL_MIN,
		                            (T_TCP_TIME)TCP_TVAL_MAX_REXMT);
	else
		cep->rxtcur = tcp_range_set(tcp_rexmt_val(cep),
		                            (T_TCP_TIME)(rtt + 2),
		                            (T_TCP_TIME)TCP_TVAL_MAX_REXMT);
	}

/*
 *  reassemble -- ��M�Z�O�����g���č\������B���Ԓʂ�Ɏ�M�����Ƃ��̏���
 */

static uint8_t
reassemble (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, uint8_t flags)
{
	T_TCP_Q_HDR 	*qhdr;
	T_TCP_HDR	*tcph;

	tcph = GET_TCP_HDR(input, thoff);
	if (tcph->sum > cep->rbufsz - cep->rwbuf_count) {
		/*
		 *  ��M�E�B���h�o�b�t�@�ɋ󂫂��Ȃ��Ƃ��͔j������B
		 */
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DROP_SEGS], 1);
		syscall(rel_net_buf(input));
		cep->flags |= TCP_CEP_FLG_ACK_NOW;
		flags &= ~TCP_FLG_FIN;
		}
	else if (tcph->seq == cep->rcv_nxt &&
	         cep->reassq == NULL &&
	         cep->fsm_state == TCP_FSM_ESTABLISHED) {
		/*
		 *  ���Ԓʂ�ɃZ�O�����g����M�������̏���
		 *  ��M�Z�O�����g�̕��בւ��͕s�v�Ȃ̂�
		 *  ���̂܂܎�M�E�B���h�o�b�t�@�ɏ������ށB
		 */

#ifdef TCP_CFG_DELAY_ACK

		cep->flags |= TCP_CEP_FLG_DEL_ACK;

#else/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->flags |= TCP_CEP_FLG_ACK_NOW;

#endif/* of #ifdef TCP_CFG_DELAY_ACK */

		qhdr = GET_TCP_Q_HDR(input, thoff);

		/*  TCP �w�b�_�̈ʒu��ۑ�����B*/
		GET_TCP_IP_Q_HDR(input)->thoff = thoff;

		/* SDU �̃I�t�Z�b�g�i���̓E�B���h�T�C�Y�j�����Z�b�g����B*/
		qhdr->soff = 0;

		/* �f�[�^����M�E�B���h�o�b�t�@�ɏ������ށB*/
		TCP_WRITE_RWBUF(cep, input, thoff);
		}
	else {
		flags = tcp_write_raque(input, cep, thoff, flags);
		cep->flags |= TCP_CEP_FLG_ACK_NOW;
		}
	return flags;
	}

/*
 *  listening -- �󓮃I�[�v�����āC��Ԃ� LISTEN �̏���
 *
 *    �߂�l:
 *      RET_OK		����
 *	RET_DROP	�G���[�A�Z�O�����g��j������B
 *	RET_RST_DROP	�G���[�ARST �𑗐M���A�Z�O�����g��j������B
 */

static ER
listening (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, T_TCP_SEQ iss)
{
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;

	iph  = GET_IP_HDR(input);
	tcph = GET_TCP_HDR(input, thoff);

	/* 
	 *  �t���O�� RST ���Z�b�g����Ă���Δj������B
	 */
	if (tcph->flags & TCP_FLG_RST)
		return RET_DROP;

	/*  
	 *  �t���O�� ACK ���Z�b�g���Ăꂢ��΁A
	 *  ���Z�b�g�𑗂��Ĕj������B
	 */
	if (tcph->flags & TCP_FLG_ACK)
		return RET_RST_DROP;

	/* 
	 *  �t���O�� SYN ���Z�b�g����Ă��Ȃ���΂�Δj������B
	 */
	if ((tcph->flags & TCP_FLG_SYN) == 0)
		return RET_DROP;

#if defined(SUPPORT_INET4)

#ifdef SUPPORT_LOOP

	/*
	 *  ���̂Ƃ��͔j������B
	 *    �E�|�[�g�ԍ�������ŁA����M IP �A�h���X ������B
	 *      �������A���[�J�����[�v�o�b�N (127.0.0.1) �Ȃ�ǂ��B
	 *    �E�}���`�L���X�g�A�h���X
	 */

	if (tcph->dport == tcph->sport &&
	    (iph->dst == iph->src && ntohl(iph->src) != IPV4_ADDR_LOOPBACK))
		return RET_DROP;

#else	/* of #ifdef SUPPORT_LOOP */

	/*
	 *  ���̂Ƃ��͔j������B
	 *    �E�|�[�g�ԍ�������ŁA����M IP �A�h���X ������B
	 *    �E�}���`�L���X�g�A�h���X
	 */

	if (tcph->dport == tcph->sport && iph->dst == iph->src)
		return RET_DROP;

#endif	/* of #ifdef SUPPORT_LOOP */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

	/*
	 *  ���̂Ƃ��͔j������B
	 *    �E�|�[�g�ԍ�������ŁA����M IP �A�h���X ������B
	 *    �E�}���`�L���X�g�A�h���X
	 */

	if (tcph->dport == tcph->sport && IN_ARE_ADDR_EQUAL(&iph->dst, &iph->src))
		return RET_DROP;

#endif	/* of #if defined(SUPPORT_INET6) */

	if (IN_IS_NET_ADDR_MULTICAST(&iph->dst))
		return RET_DROP;

	/* ����̃A�h���X���L�^����B*/
	IN_COPY_TO_HOST(&cep->dstaddr.ipaddr, &iph->src);
	cep->dstaddr.portno = tcph->sport;

	/* �I�v�V��������������B*/
	parse_option(tcph, cep);

	/* �V�[�P���X�ԍ�������������B*/
	if (tcp_iss == 0)
		tcp_init_iss();

	/* �����̃V�[�P���X�ԍ��̏����l���L�^����B*/
	if (iss != 0)
		cep->iss = iss;
	else
		cep->iss = tcp_iss;

	tcp_iss += TCP_ISS_INCR() / 4;

	/* ����̃V�[�P���X�ԍ��̏����l���L�^����B*/
	cep->irs = tcph->seq;

	/* ����M�V�[�P���X�ԍ�������������B*/
	init_send_seq(cep);
	init_receive_seq(cep);

	/* ���M�E�C���h�T�C�Y��ݒ肷��B*/
	cep->snd_wnd = tcph->win;

	/* �ŏI�ݒ� */
	cep->flags    |= TCP_CEP_FLG_ACK_NOW;
	cep->fsm_state = TCP_FSM_SYN_RECVD;
	cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_INIT;

	return RET_OK;
	}

/*
 *  syn_sent -- �\���I�[�v�����āA��Ԃ� SYN ���M�ς̏���
 *
 *    �߂�l:
 *      RET_OK		����
 *	RET_DROP	�G���[�A�Z�O�����g��j������B
 *	RET_RST_DROP	�G���[�ARST �𑗐M���A�Z�O�����g��j������B
 */

static ER
syn_sent (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	ER error = RET_OK;

	/*
	 *  ���肩���M�m�F�������ė��Ă��A
	 *
	 *    ACK <= iss && ���M�����ő� SEQ (snd_max) < ACK
	 *
	 *  �Ȃ�A���Z�b�g�𑗂��ăZ�O�����g��j������B
	 */
	if ((tcph->flags & TCP_FLG_ACK) &&
	    (SEQ_LE(tcph->ack, cep->iss) || SEQ_GT(tcph->ack, cep->snd_max)))
		return RET_RST_DROP;

	/*
	 *  RST/ACK �t���O�̉���������΁A�|�[�g���J���Ă��Ȃ�
	 *  ���Ƃ��Ӗ����Ă���B
	 */
	if (tcph->flags & TCP_FLG_RST) {
		if (tcph->flags & TCP_FLG_ACK) {
			cep->net_error = EV_CNNRF;
			cep = tcp_drop(cep, E_CLS);
			}
		return RET_DROP;
		}

	/*
	 *  SYN �t���O���Ȃ���΃Z�O�����g��j������B
	 */
	if ((tcph->flags & TCP_FLG_SYN) == 0)
		return RET_DROP;

	cep->snd_wnd = tcph->win;	/* snd_wnd: ����̎�M�\�E�B���h�T�C�Y	*/
	cep->irs     = tcph->seq;	/* irs:     ����̃V�[�P���X�ԍ��̏����l	*/
	init_receive_seq(cep);		/* ����M�V�[�P���X�ԍ�������������B		*/

	if (tcph->flags & TCP_FLG_ACK) {
		/*
		 *  ACK �t���O������Ƃ��̏���
		 *
		 *  ��M�����҂��Ă���ő�� SEQ (rcv_adv) ��
		 *  ��M�\�ȃE�B���h�T�C�Y (rcv_wnd) ���i�߂�B
		 */
		cep->rcv_adv += cep->rcv_wnd;	/* rcv_adv: ��M�����҂��Ă���ő�� SEQ	*/
						/* rcv_wnd: ��M�\�ȃE�B���h�T�C�Y		*/

		/* ���m�F�̍ŏ����M SEQ (snd_una) �� SYN �� (1 �I�N�e�b�g) �i�߂�B*/
		cep->snd_una ++;

#ifdef TCP_CFG_DELAY_ACK

		if (tcph->sum != 0)		/* tcph->sum �� SDU �� */
			cep->flags |= TCP_CEP_FLG_DEL_ACK;
		else
			cep->flags |= TCP_CEP_FLG_ACK_NOW;

#else/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->flags |= TCP_CEP_FLG_ACK_NOW;

#endif/* of #ifdef TCP_CFG_DELAY_ACK */

		if (cep->flags & TCP_CEP_FLG_NEED_FIN) {
			/*
			 *  CEP �� FIN ���M���v������Ă���΁A
			 *  �ؒf�������J�n���A
			 *  CEP �̏�Ԃ� FIN Wait 1 �ɂ���B
			 */
			cep->fsm_state = TCP_FSM_FIN_WAIT_1;
			cep->flags  &= ~TCP_CEP_FLG_NEED_FIN;
			tcph->flags &= ~TCP_FLG_SYN;
			}
		else {
			/*
			 *  ���肩�� ACK ���������ꂽ�̂ŁA
			 *  CEP �̏�Ԃ� �R�l�N�V�����J�݊�����Ԃɂ���B
			 */
			cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;
			cep->fsm_state  = TCP_FSM_ESTABLISHED;
			NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_ESTABLISHED));

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->snd_nblk_tfn == TFN_TCP_CON_CEP) {

				/* ����̃A�h���X���R�s�[����B*/
				*cep->p_dstaddr = cep->dstaddr;

				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, E_OK);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_OK;

					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					}
				else {
					syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
					error = RET_RST_DROP;
					}
				cep->p_dstaddr = NULL;
				cep->snd_tskid = TA_NULL;
				cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
				}
			else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

				NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
			}
		}
	else {
		/* ACK �t���O���Ȃ��Ƃ��́AACK �𑗂��āACEP �̏�Ԃ� SYN ��M�ς݂ɂ���B*/
		cep->flags |= TCP_CEP_FLG_ACK_NOW;
		cep->timer[TCP_TIM_REXMT] = 0;
		cep->fsm_state  = TCP_FSM_SYN_RECVD;
		}

	return error;
	}

/*
 *  trim_length -- ��M���� SDU ���𒲐�����B
 */

static void
trim_length (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	tcph->seq ++;
	if (tcph->sum > cep->rcv_wnd) {		/* ����: tcph->sum �� SDU �� */
		/*
		 *  SDU ������M�E�B���h�T�C�Y���傫���Ƃ��́A��M�E�B���h�T�C�Y�ȍ~��
		 *  �j�����AFIN �ɉ������Ȃ����ƂŁA�j�������f�[�^���đ�������B
		 */
		tcph->sum    = (uint16_t)cep->rcv_wnd;
		tcph->flags &= ~TCP_FLG_FIN;
		}
	cep->snd_wl1 = tcph->seq - 1;		/* cep->snd_wl1: �E�B���h�X�V SEQ �ԍ�	*/

#ifdef TCP_CFG_EXTENTIONS
	cep->rcv_up  = tcph->seq;		/* cep->rcv_up : ��M�����ً}�|�C���^	*/
#endif
	}

/*
 *  proc_ack2 -- ACK �̏��� (2)
 *
 *    �߂�l
 *
 *      RET_OK		����
 *      RET_RETURN	����A���^�[������B
 *	RET_DROP	�G���[�A�Z�O�����g��j������B
 *	RET_RST_DROP	�G���[�ARST �𑗐M���A�Z�O�����g��j������B
 */

static ER
proc_ack2 (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput)
{
	T_TCP_HDR	*tcph;
	ER		ret = RET_OK;
	uint32_t	acked;
	bool_t		ourfinisacked = false;

	tcph = GET_TCP_HDR(input, thoff);

	/*
	 *  ����Ɏ�M�m�F���ꂽ ACK ����A�܂��m�F����Ă��Ȃ�
	 *  �ŏ����M SEQ (snd_una) �������ƁA���M�E�B���h�o�b�t�@����
	 *  �폜���Ă悢�I�N�e�b�g�� (acked) �ɂȂ�B
	 */
	acked = tcph->ack - cep->snd_una;
	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_ACKS], 1);

	/*
	 *  �������Ԍv�� (rtt) ���ݒ肳��Ă��āA�v���J�n SEQ ���
	 *  ��� ACK ����M������A�^�C�}�o�b�N�I�t���L�����Z�����A
	 *  �đ��^�C�}���Đݒ肷��B
	 */
	if (cep->rtt && SEQ_GT(tcph->ack, cep->rtseq)) {
		set_rexmt_timer(cep, cep->rtt);
		}

	/*
	 *  �S�Ă̖��m�F�f�[�^�� ACK ���ꂽ��A�đ��^�C�}���~���A
	 *  �ĊJ���L������ (����ɏo�͂�����)�B
	 *  �����AACK ���ׂ��A����ɑ����̃f�[�^������Ȃ�A�đ��^�C�}��
	 *  ���݂̍đ��^�C���A�E�g��ݒ肷��B
	 */
	if (tcph->ack == cep->snd_max) {	/* cep->snd_max: ���M�����ő� SEQ */

#ifdef TCP_CFG_SWBUF_CSAVE

		/*
		 * ���M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���L���̏ꍇ�́A
		 * ���M�ς݂ŁAACK����������܂ōđ��^�C�}��ύX���Ȃ��B
		 */
		if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_ACKED)
			cep->timer[TCP_TIM_REXMT] = 0;

#else	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		cep->timer[TCP_TIM_REXMT] = 0;

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		*needoutput = true;
		}
	else if (cep->timer[TCP_TIM_PERSIST] == 0) {
	 	cep->timer[TCP_TIM_REXMT] = cep->rxtcur;	/* cep->rxtcur: ���݂̍đ��^�C���A�E�g */
		}

	/* ���肪��M�m�F�����f�[�^������Ƃ��̏��� */
	if (acked) {
		uint32_t cw   = cep->snd_cwnd;	/* cep->snd_cwnd: �t�s�E�B���h�T�C�Y	*/
		uint32_t incr = cep->maxseg;		/* cep->maxseg:   �ő�Z�O�����g�T�C�Y	*/

		/*
		 *  �V���ɑ��肪��M�m�F�����f�[�^���������Ƃ��́A
		 *  �t�s�E�B���h�T�C�Y��傫������B
		 *  �t�s�E�B���h�T�C�Y (snd_cwnd) ��
		 *  �t�s�E�B���h�T�C�Y�̂������l (snd_ssthresh) ���傫���Ƃ���
		 *  �t�s��𐧌���s���B
		 *
		 *    snd_cwnd = snd_cwnd + maxseg * maxseg / snd_cwnd;
		 *
		 *  ���������������Ƃ��́A�X���[�X�^�[�g������s���B
		 *
		 *    snd_cwnd = snd_cwnd + maxseg
		 *
		 */
		if (cw > cep->snd_ssthresh)
			/* �t�s��𐧌� */
			incr = incr * incr / cw;

		if (cw + incr < MAX_TCP_WIN_SIZE)
			cep->snd_cwnd = (uint16_t)(cw + incr);
		else
			cep->snd_cwnd = MAX_TCP_WIN_SIZE;

		/*
		 *  ���M�E�B���h�o�b�t�@����A���肪��M�m�F�����f�[�^�� (acked) �̃f�[�^���폜����B
		 */
		if (acked > cep->swbuf_count) {
			cep->snd_wnd -= cep->swbuf_count;
			TCP_DROP_SWBUF(cep, (uint_t)cep->swbuf_count);
			ourfinisacked = true;
			}
		else {
			cep->snd_wnd -= (uint16_t)acked;
			TCP_DROP_SWBUF(cep, (uint_t)acked);
			ourfinisacked = false;
			}

		/* ���M�E�B���h�o�b�t�@�ɋ󂫂��ł������Ƃ�m�点��B*/
		syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

		/*
		 *  ���B�m�F����Ă��Ȃ��ŏ����M SEQ (snd_una) ��
		 *  ���񑗒B�m�F���ꂽ ACK �܂Ői�߁A
		 *  ���̑��M�f�[�^�� SEQ (snd_nxt) ���A�V����
		 *  ���B�m�F����Ă��Ȃ��ŏ����M SEQ (snd_una)
		 *  �܂Ői�߂�B
		 */
		cep->snd_una += acked;
		if (SEQ_LT(cep->snd_nxt, cep->snd_una))
			cep->snd_nxt = cep->snd_una;

		/*
		 *  ��Ԃɂ�蕪��
		 */
		switch (cep->fsm_state) {
		case TCP_FSM_FIN_WAIT_1:	/* APP ���I���AFIN ���M�ς݁AACK �҂� */
			if (ourfinisacked) {
				cep->fsm_state = TCP_FSM_FIN_WAIT_2;
				cep->timer[TCP_TIM_2MSL] = TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL;
				}
			break;
		case TCP_FSM_CLOSING:		/* �����N���[�Y�AFIN �����ς݁AACK �҂� */
			if (ourfinisacked) {
				/*
				 *  ���M���� FIN ���m�F����Ă���Ώ�Ԃ�ύX���A
				 *  ���ׂẴ^�C�}�����Z�b�g������A2MSL �^�C�}��ݒ肷��B
				 */
				cep->fsm_state = TCP_FSM_TIME_WAIT;
				tcp_cancel_timers(cep);
				cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;
				}
			break;
		case TCP_FSM_LAST_ACK:		/* APP ���I���AACK �҂� */
			if (ourfinisacked) {
				/*
				 *  ���M���� FIN ���m�F����Ă���΁Acep ���N���[�Y���A
				 *  �Z�O�����g��j������B
				 */
				cep = tcp_close(cep);
				ret = RET_DROP;
				}
			break;
		case TCP_FSM_TIME_WAIT:		/* ���肩��� FIN ��M�ς݁A���ԑ҂� */
			/*
			 *  ���肩�� FIN ���đ����ꂽ�B������x2MSL �^�C�}��ݒ肵�A
			 *  ACK ���M��A�Z�O�����g��j������B
			 */
			cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;
			return drop_after_ack(input, cep, thoff);
			}
		}

	return ret;
	}

/*
 *  proc_ack1 -- ACK �̏��� (1)
 *
 *    �߂�l:
 *      RET_OK		����
 *      RET_RETURN	����A���^�[������B
 *	RET_DROP	�G���[�A�Z�O�����g��j������B
 *	RET_RST_DROP	�G���[�ARST �𑗐M���A�Z�O�����g��j������B
 *
 */

static ER
proc_ack1 (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, bool_t *needoutput)
{
	T_TCP_HDR *tcph = GET_TCP_HDR(input, thoff);

	switch (cep->fsm_state) {
	case TCP_FSM_SYN_RECVD:		/* SYN ����M���ASYN ���M�ς�	*/

		/* ��Ԃ�ύX����B*/
		if (cep->flags & TCP_CEP_FLG_NEED_FIN) {
			cep->fsm_state  = TCP_FSM_FIN_WAIT_1;
			cep->flags &= ~TCP_CEP_FLG_NEED_FIN;
			}
		else {
			cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;
			cep->fsm_state  = TCP_FSM_ESTABLISHED;

			/* TCP �ʐM�[�_����TCP ��t�����������B*/
			cep->rep = NULL;

			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_ESTABLISHED));

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->rcv_nblk_tfn == TFN_TCP_ACP_CEP) {

				/* ����̃A�h���X���R�s�[����B*/
				*cep->p_dstaddr = cep->dstaddr;

				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					NET_COUNT_MIB(tcp_stats.tcpPassiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_ACCEPTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, E_OK);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_OK;

					NET_COUNT_MIB(tcp_stats.tcpPassiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_ACCEPTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					cep->p_dstaddr = NULL;
					cep->rcv_tskid = TA_NULL;
					cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
					}
				else {
					syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
					cep->p_dstaddr = NULL;
					cep->rcv_tskid = TA_NULL;
					cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
					return RET_RST_DROP;
					}
				}

			if (cep->snd_nblk_tfn == TFN_TCP_CON_CEP) {

				/* ����̃A�h���X���R�s�[����B*/
				*cep->p_dstaddr = cep->dstaddr;

				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, E_OK);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_OK;

					NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
					NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
					(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					cep->p_dstaddr = NULL;
					cep->snd_tskid = TA_NULL;
					cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
					}
				else {
					syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
					cep->p_dstaddr = NULL;
					cep->snd_tskid = TA_NULL;
					cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
					return RET_RST_DROP;
					}
				}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			if (cep->rcv_tfn == TFN_TCP_ACP_CEP) {
				NET_COUNT_MIB(tcp_stats.tcpPassiveOpens, 1);
				NET_COUNT_TCP(net_count_tcp[NC_TCP_ACCEPTS], 1);
				}

			if (cep->snd_tfn == TFN_TCP_CON_CEP) {
				NET_COUNT_MIB(tcp_stats.tcpActiveOpens, 1);
				NET_COUNT_TCP(net_count_tcp[NC_TCP_CONNECTS], 1);
				}
			}

		/*
		 *  SDU ���Ȃ� FIN �����Ă��Ȃ���΁Atcp_move_ra2rw() ���ďo���B
		 */
		if (tcph->sum == 0 && (tcph->flags & TCP_FLG_FIN) == 0)		/* tcph->sum �� SDU �� */
			tcph->flags = tcp_move_ra2rw(cep, tcph->flags);
		
		cep->snd_wl1 = tcph->seq - 1;	/* snd_wl1: �E�B���h�X�V SEQ */

		/* break; ���ɗ�����B*/
	
	case TCP_FSM_ESTABLISHED:	/* �R�l�N�V�����J�݊���		*/
	case TCP_FSM_FIN_WAIT_1:	/* �I�����āAFIN ���M�ς�		*/
	case TCP_FSM_FIN_WAIT_2:	/* �I���AFIN �`�B�m�F��M�AFIN�҂�*/
	case TCP_FSM_CLOSE_WAIT:	/* FIN ��M�A�N���[�Y�҂�		*/
	case TCP_FSM_CLOSING:		/* �I���AFIN �����ς݁AACK �҂�	*/
	case TCP_FSM_LAST_ACK:		/* FIN ��M�A�I���AACK �҂�	*/
	case TCP_FSM_TIME_WAIT:		/* �I���A���ԑ҂�		*/

		if (SEQ_LE(tcph->ack, cep->snd_una)) {

			/*
			 *  ��M�m�F ACK �� ���m�F�̍ŏ����M SEQ (snd_una) �Ɠ������ȑO�̂Ƃ��̏���
			 *  �܂�A���d�� ACK ����M�������Ƃ��Ӗ����Ă���B
			 */

			if (tcph->sum == 0 && tcph->win == cep->snd_wnd) {	/* tcph->sum �� SDU �� */

				/*
				 *  SDU ���Ȃ��A����̃E�B���h�T�C�Y���ύX����Ă��Ȃ���΁A
				 *  ���łɑ��M�����Z�O�����g�̒��ŁAACK (tcph->ack) ��
				 *  ���� SEQ ����n�܂�Z�O�����g���A�r���ŏ��������\��������B
				 *  ���̏ꍇ�́A�����ē]���ƍ������J�o�����s���B
				 */
				NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DUP_ACKS], 1);

				if (cep->timer[TCP_TIM_REXMT] == 0 || tcph->ack != cep->snd_una) {

					/*
					 *  �đ��^�C�}���Z�b�g����Ă��Ȃ��Ƃ��A
					 *  �܂��́AACK (tcph->ack) �Ɩ��m�F�̍ŏ����M SEQ��
					 *  ��v���Ȃ��Ƃ��́A���d ACK ���� 0 �ɂ���B
					 */
					cep->dupacks = 0;
					}

				else if (++ cep->dupacks == MAX_TCP_REXMT_THRESH) {

					/*
					 *  ���d ACK �����������l (�W�� 3) �ɂȂ�����
					 *  �����ē]���������J�n����B
					 */
					uint_t		win;

					/*
					 *  �t�s�E�B���h�T�C�Y(snd_cwnd)�̂������l��ݒ肷��B
					 *
					 *    ����̎�M�\�E�B���h�T�C�Y (snd_wnd) ��
					 *    �t�s�E�B���h�T�C�Y (snd_cwnd) �� 1/2�B
					 *    �������A2 * maxseg �ȏ�B
					 *
					 */
					if (cep->snd_wnd < cep->snd_cwnd)
						win = cep->snd_wnd / 2 / cep->maxseg;
					else
						win = cep->snd_cwnd / 2 / cep->maxseg;
					if (win < 2)
						win = 2;
					cep->snd_ssthresh = win * cep->maxseg;

					/* �đ��^�C�}�Ɖ������Ԃ����Z�b�g����B*/
					cep->timer[TCP_TIM_REXMT] = 0;
					cep->rtt = 0;

					/* ���������Z�O�����g�𑗐M����B*/
					cep->snd_old_nxt = cep->snd_nxt;
					cep->snd_nxt     = tcph->ack;
					cep->snd_cwnd    = cep->maxseg;

					/*
					 *  snd_nxt �����ɖ߂��悤�ɐݒ肵��
					 *  ���M���w������B
					 */
					cep->flags |=  TCP_CEP_FLG_POST_OUTPUT |
					               TCP_CEP_FLG_FORCE       |
					               TCP_CEP_FLG_FORCE_CLEAR |
					               TCP_CEP_FLG_RESTORE_NEXT_OUTPUT;
					sig_sem(SEM_TCP_POST_OUTPUT);

					/* �t�s�E�B���h�T�C�Y���X�V����B*/
					cep->snd_cwnd = (uint16_t)(cep->snd_ssthresh
					                   + cep->maxseg * cep->dupacks);
					
					return RET_DROP;
					}

				else if (cep->dupacks > MAX_TCP_REXMT_THRESH) {

					/*
					 *  ���d ACK �����������l (�W�� 3) �𒴂�����
					 *  �t�s�E�B���h�T�C�Y�𑝉����Ȃ���đ�����B
					 */
					cep->snd_cwnd += cep->maxseg;

					/* ���M���w������B*/
					cep->flags |=  TCP_CEP_FLG_POST_OUTPUT;
					sig_sem(SEM_TCP_POST_OUTPUT);

					return RET_DROP;
					}
				} 
			else
				cep->dupacks = 0;
			break;
			}

		/*
		 *  ��M�m�F ACK �� ���m�F�̍ŏ����M SEQ (snd_una) �ȍ~�̂Ƃ��̏���
		 */
		if (cep->dupacks >= MAX_TCP_REXMT_THRESH && cep->snd_cwnd > cep->snd_ssthresh)
		 	/*
			 *  �����ē]�����s���Ă����Ƃ��́A�t�s�E�B���h�T�C�Y���������l�܂Ŗ߂��B
			 */
			cep->snd_cwnd = (uint16_t)cep->snd_ssthresh;
	
		cep->dupacks = 0;

		if (SEQ_GT(tcph->ack, cep->snd_max))
			/*
			 *  ��M���� ACK �����M�����ő� SEQ �𒴂��Ă����Ƃ��̏���
			 */
			return drop_after_ack(input, cep, thoff);

		if (cep->flags & TCP_CEP_FLG_NEED_SYN) {
			/*
			 *  SYN ���M�v�����������āA���m�F�̍ŏ����M SEQ ��i�߂�B
			 */
			cep->flags &= ~TCP_CEP_FLG_NEED_SYN;
			cep->snd_una ++;
			}
		
		return proc_ack2(input, cep, thoff, needoutput);
		break;
		}
	return RET_OK;
	}

/*
 *  update_wnd -- �E�B���h�T�C�Y���X�V����B
 *
 *    �߂�l: ���M���K�v�Ȃ� true ��Ԃ��B
 */

static bool_t
update_wnd (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{

	/*
	 *  �X�V����
	 *
	 *    ACK �t���O���Z�b�g����Ă��� &&
	 *    (�O��E�B���h���X�V���� SEQ (snd_wl1) �� SEQ ���O ||
	 *     �O��E�B���h���X�V���� SEQ (snd_wl1) �� SEQ �Ɠ��� &&
	 *     (�O��E�B���h���X�V���� ACK (snd_wl2) �� ACK ���O ||
	 *      (�O��E�B���h���X�V���� ACK (snd_wl2) �� ACK �Ɠ��� &&
	 *       WIN ������̎�M�\�E�B���h�T�C�Y (snd_wnd) ���傫��
	 *       )
	 *      )
	 *     )
	 */
	if ((tcph->flags & TCP_FLG_ACK) &&
	    (SEQ_LT(cep->snd_wl1, tcph->seq) ||
	     (cep->snd_wl1 == tcph->seq &&
	      (SEQ_LT(cep->snd_wl2, tcph->ack) ||
	       (cep->snd_wl2 == tcph->ack && tcph->win > cep->snd_wnd))))) {

		cep->snd_wnd = tcph->win;
		cep->snd_wl1 = tcph->seq;
		cep->snd_wl2 = tcph->ack;

		if (cep->snd_wnd > cep->max_sndwnd)
			/* ���܂ł̍ő呗�M�E�B���h�T�C�Y���X�V����B*/
			cep->max_sndwnd = cep->snd_wnd;

#ifdef TCP_CFG_SWBUF_CSAVE

		if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_WOPEN_PEND) {

			/*
			 *  ���M�E�B���h�o�b�t�@�p�̃l�b�g���[�N�o�b�t�@���蓖�Ē��ŁA
			 *  ����̎�M�E�B���h���󂭂̂�҂��Ă���Ƃ��̏���
			 */
			if (cep->snd_wnd > 0) {

				/*
				 *  ����̎�M�E�B���h���󂢂��Ƃ��́A
				 *  ���M�E�B���h�o�b�t�@�p�̃l�b�g���[�N�o�b�t�@���蓖�Ă��ĊJ����B
				 */
				cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK)
				                         |  TCP_CEP_FLG_WBCS_FREE |  TCP_CEP_FLG_POST_OUTPUT;
				sig_sem(SEM_TCP_POST_OUTPUT);
				}
			}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

		return true;
		}
	else
		return false;
	}

/*
 *  proc_urg -- �ً}�f�[�^���̃Z�O�����g�̏���
 */

#ifdef TCP_CFG_EXTENTIONS

static void
proc_urg (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	if ((tcph->flags & TCP_FLG_URG) && VALID_URG_POINTER(tcph->urp) &&
	    TCP_FSM_HAVE_RCVD_FIN(cep->fsm_state) == 0) {

		/* �ً}�f�[�^���̃Z�O�����g�̏��� */

		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_URG_SEGS], 1);
		if (tcph->urp + cep->rwbuf_count > cep->rbufsz) {

			/*
			 *  �ً}�|�C���^�̈ʒu����M�E�B���h�o�b�t�@��
			 *  �͈͂𒴂���Ƃ��͉������Ȃ��B
			 */
			tcph->urp    = 0;
			tcph->flags &= ~TCP_FLG_URG;
			}

		if (SEQ_GT(tcph->seq + tcph->urp, cep->rcv_up))
			/* �ً}�|�C���^���X�V���ꂽ�Ƃ��̏��� */
			cep->rcv_up = tcph->seq + tcph->urp;

		if ((tcph->flags & TCP_FLG_URG) && (tcph->urp + TCP_CFG_URG_OFFSET) < tcph->sum) {	/* tcph->sum �� TCP �� SDU �� */

			/*
			 *  �ً}�|�C���^�̈ʒu���A�����M�����Z�O�����g���̏ꍇ�́A
			 *  �R�[���o�b�N�֐����Ăяo���B
			 */
			cep->urg_tcph = tcph;
			if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), TEV_TCP_RCV_OOB, (void*)(uint32_t)1);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				uint32_t	len = 1;

				(*cep->callback)(GET_TCP_CEPID(cep), TEV_TCP_RCV_OOB, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				}
			else {
				syslog(LOG_WARNING, "[TCP] no call back for OOB, CEP: %d.", GET_TCP_CEPID(cep));
				}

			if (cep->urg_tcph != NULL) {
				/* �R�[���o�b�N�֐����� tcp_rcv_oob() ���ďo���Ȃ������B*/
				cep->urg_tcph = NULL;
				tcph->urp = 0;
				}
			else {
				/* 
				 *  �R�[���o�b�N�֐����� tcp_rcv_oob() ���ďo�������́A
				 *  SDU ���̕␳�l��ݒ肷��B
				 */
				tcph->urp = 1;
				}
			}
		else if (tcph->urp > 0) {
			tcph->urp = 0;
			}

		}
	else if (SEQ_GT(cep->rcv_nxt, cep->rcv_up)) {
		cep->rcv_up = cep->rcv_nxt;
		tcph->urp = 0;
		}
	}

#else	/* of #ifdef TCP_CFG_EXTENTIONS */

static void
proc_urg (T_TCP_HDR *tcph, T_TCP_CEP *cep)
{
	tcph->urp = 0;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

/*
 *  drop_after_ack -- ��M�Z�O�����g��j��������AACK ��Ԃ� (����: ���O�Ƃ͍����Ă��Ȃ�)�B
 *
 *    �߂�l:
 *      RET_RETURN	����A���^�[������B
 *	RET_RST_DROP	�G���[�ARST �𑗐M���A�Z�O�����g��j������B
 */

static ER
drop_after_ack (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff)
{
	T_TCP_HDR *tcph = GET_TCP_HDR(input, thoff);

	/*
	 *    SYN ��M��ԂŁAACK �����B�m�F����Ă��Ȃ��ŏ����M SEQ (snd_una) ���
	 *    �O�̒l���A���M���ꂽ�ő� SEQ (snd_max) ����̒l�̏ꍇ�́A����� RST ��
	 *    �����ďI������B����́A"LAND" DoS �U���ւ̖h��ł���A�U�����ꂽ SYN
	 *    �Z�O�����g�𑗐M���Â���|�[�g�Ԃł� ACK �X�g�[����h���B
	 */
	if (cep->fsm_state == TCP_FSM_SYN_RECVD && (tcph->flags & TCP_FLG_ACK) &&
	    (SEQ_GT(cep->snd_una, tcph->ack) ||
	     SEQ_GT(tcph->ack, cep->snd_max)))
		return RET_RST_DROP;

	syscall(rel_net_buf(input));

	/* ���M���w������B*/
	cep->flags |=  TCP_CEP_FLG_ACK_NOW | TCP_CEP_FLG_POST_OUTPUT;
	sig_sem(SEM_TCP_POST_OUTPUT);
	return RET_RETURN;
	}

/*
 *  close_connection -- �R�l�N�V�����J�������A���肩�� FIN ����M�����B
 */

static void
close_connection (T_TCP_CEP *cep, bool_t *needoutput)
{
	if (TCP_FSM_HAVE_RCVD_FIN(cep->fsm_state) == 0) {

#ifdef TCP_CFG_DELAY_ACK

		if (cep->flags & TCP_CEP_FLG_NEED_SYN)
			cep->flags |= TCP_CEP_FLG_DEL_ACK;
		else
			cep->flags |= TCP_CEP_FLG_ACK_NOW;

#else/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->flags |= TCP_CEP_FLG_ACK_NOW;

#endif/* of #ifdef TCP_CFG_DELAY_ACK */

		cep->rcv_nxt ++;
		}

	switch (cep->fsm_state) {
	case TCP_FSM_SYN_RECVD:		/* SYN ����M���ASYN ���M�ς�	*/
	case TCP_FSM_ESTABLISHED:	/* �R�l�N�V�����J�݊���		*/
		cep->fsm_state = TCP_FSM_CLOSE_WAIT;
		break;

	case TCP_FSM_FIN_WAIT_1:	/* APP ���I���AFIN ���M�ς݁AACK �҂� */
		cep->fsm_state = TCP_FSM_CLOSING;
		break;

	case TCP_FSM_FIN_WAIT_2:	/* ���肩��� FIN �҂� */
		cep->fsm_state = TCP_FSM_TIME_WAIT;
		tcp_cancel_timers(cep);
		cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;

		/*
		 *  FIN WAIT 2 ��Ԃł́A
		 *  ��M�͉\�ł��邪�A���łɑ��M�͏I�����Ă���B
		 *  ����̑��M���I�������̂ŁA���̓^�X�N�̂݋N������B
		 */
		syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

		/* ���肩��� FIN �ɑ΂��ĉ�����Ԃ��B*/
		tcp_respond(NULL, cep, cep->rcv_nxt, cep->snd_una,
		            cep->rbufsz - cep->rwbuf_count, TCP_FLG_ACK);
		cep->flags &= ~TCP_CEP_FLG_ACK_NOW;
		*needoutput = false;

		/*
		 *  �K�v�ȏ��� Time Wait �p TCP �ʐM�[�_�Ɉڂ��āA
		 *  �W���� TCP �ʐM�[�_���J������B
		 */
		tcp_move_twcep(cep);

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

		break;

	case TCP_FSM_TIME_WAIT:		/* ���肩��� FIN ��M�ς݁A���ԑ҂� */
		cep->timer[TCP_TIM_2MSL] = 2 * TCP_TVAL_MSL;
		break;
		}
	}

/*
 *  tcp_input -- TCP �̓��͊֐�
 *
 *	����: input �ɂ� IF �w�b�_�� IP �w�b�_���擪�ɂ���B
 */

uint_t
tcp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_IP_HDR	*iph;
	T_TCP_HDR	*tcph;
	T_TCP_CEP	*cep = NULL;
	T_TCP_SEQ	iss = 0;
	ER		ret;
	bool_t		needoutput = false;
	int_t		rbfree;
	int32_t		todrop, win;
	uint16_t	seglen;
	uint8_t		flags;

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0
	T_TCP_TWCEP	*twcep;
#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_OCTETS],
	              input->len - GET_IF_IP_HDR_SIZE(input));
	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_SEGS], 1);
	NET_COUNT_MIB(tcp_stats.tcpInSegs, 1);

	/* �w�b�_�����`�F�b�N����B*/
	if (input->len < IF_IP_TCP_HDR_SIZE) {
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_BAD_HEADERS], 1);
		goto drop;
		}

	iph  = GET_IP_HDR(input);
	tcph = GET_TCP_HDR(input, *offp);

	seglen  = input->len - *offp;				/* TCP �̃Z�O�����g�� */

	if (IN_CKSUM(input, IPPROTO_TCP, *offp, (uint_t)seglen) != 0) {
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_BAD_CKSUMS], 1);
		goto drop;
		}

	/* TCP �w�b�_�����`�F�b�N����B*/
	if (TCP_HDR_LEN(tcph->doff) < TCP_HDR_SIZE || TCP_HDR_LEN(tcph->doff) > seglen) {
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_BAD_HEADERS], 1);
		goto drop;
		}
	tcph->sum = seglen - TCP_HDR_LEN(tcph->doff);		/* �������� tcph->sum �� TCP �� SDU �� */

	/*
	 *  SYN �� FIN �̗��r�b�g���Z�b�g����Ă���Δj������Bnmap ���̑΍�
	 *  �������ARFC1644 T/TCP �g���@�\�Ƌ�������B
	 */
	if ((tcph->flags & (TCP_FLG_SYN | TCP_FLG_FIN)) == (TCP_FLG_SYN | TCP_FLG_FIN))
		goto drop;

	/* �l�b�g���[�N�I�[�_�[����z�X�g�I�[�_�[�ɕϊ�����B*/

	NTOHL(tcph->seq);
	NTOHL(tcph->ack);
	NTOHS(tcph->win);
	NTOHS(tcph->urp);
	NTOHS(tcph->sport);
	NTOHS(tcph->dport);

find_cep:

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

	/*
	 *  ��Ԃ� Time Wait ���� CEP ��T������B
	 */
	twcep = tcp_find_twcep(&iph->dst, tcph->dport, &iph->src, tcph->sport);
	if (twcep != NULL) {

		if (tcph->flags & TCP_FLG_RST)		/* RST �t���O����M�����Ƃ��͖�������B*/
			goto drop;
		else {

			/*
			 *    TCP �ʐM�[�_�� Time Wait �̎��A����z�X�g����Z�O�����g�������Ƃ��́A
			 *    ����z�X�g�� FIN �ɑ΂��鎩�z�X�g�� ACK �Z�O�����g���r����
			 *    �����������Ƃ��Ӗ����Ă���̂ŁAACK �Z�O�����g���đ�����B
			 */

			/* �z�X�g�I�[�_�[����l�b�g���[�N�I�[�_�[�ɖ߂��B*/
			HTONS(tcph->sport);
			HTONS(tcph->dport);

			tcp_respond(input, NULL, twcep->rcv_nxt, twcep->snd_una, twcep->rbufsz - twcep->rwbuf_count, TCP_FLG_ACK);
			}
		return IPPROTO_DONE;
		}
	else
		/* �W���� TCP �ʐM�[�_�𓾂�B*/
		cep = tcp_find_cep(&iph->dst, tcph->dport, &iph->src, tcph->sport);

#else	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

	/* TCP �ʐM�[�_�𓾂�B*/
	cep = tcp_find_cep(&iph->dst, tcph->dport, &iph->src, tcph->sport);

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

	/*
	 *  TCP �ʐM�[�_���Ȃ��ꍇ�� CEP �̏�Ԃ��N���[�Y�Ȃ�j������B
	 */
	if (cep == NULL) {
		syslog(LOG_INFO, "[TCP] unexp port: %d.", tcph->dport);
		goto reset_drop;
		}

#ifdef TCP_CFG_TRACE

	tcp_input_trace(input, cep);

#endif	/* of #ifdef TCP_CFG_TRACE */


	if (cep->fsm_state == TCP_FSM_CLOSED)
		goto drop;

	/*
	 *  �R�l�N�V�����J�ݍς݂ŃZ�O�����g����M�����Ƃ��́A
	 *  �A�C�h�����ԂƐ����m�F�^�C�}�����Z�b�g����B
	 */
	cep->idle = 0;
	if (TCP_FSM_HAVE_ESTABLISHED(cep->fsm_state)) {
		cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;
		}

	/* CEP �̏�Ԃ� LISTEN �ȊO�̎��́A�I�v�V��������������B*/
	if (cep->fsm_state != TCP_FSM_LISTEN)
		parse_option(tcph, cep);

	/*
	 *  ��M�\�E�B���h�T�C�Y���v�Z����B
	 *
	 *  rcv_nxt:     ��M�����҂��Ă���ŏ��� SEQ�i����ȑO�͎�M�ς݁j
	 *  rcv_adv:     ��M�����҂��Ă���ő�� SEQ
	 *  rbufsz:      ��M�E�B���h�o�b�t�@�T�C�Y
	 *  rwbuf_count:  ��M�E�B���h�o�b�t�@�ɂ���f�[�^��
	 *  tcph->sum:   �����M���� SDU �T�C�Y
	 *
	 *  �����M�����Z�O�����g����������L���[�ɘA������
	 *  �\��������̂� tcph->sum ���l������B
	 *
	 */
	win = cep->rbufsz - (cep->rwbuf_count + tcph->sum);
	if (win < 0)
		win = 0;
	if (win > (int32_t)(cep->rcv_adv - cep->rcv_nxt))
		cep->rcv_wnd = win;
	else
		cep->rcv_wnd = cep->rcv_adv - cep->rcv_nxt;

	/* CEP �̏�Ԃɂ�菈�����s���B*/

	if (cep->fsm_state == TCP_FSM_LISTEN) {		/* �󓮃I�[�v�� (LISTEN) �̏����B*/
		if ((ret = listening(input, cep, *offp, iss)) == RET_RST_DROP)
			goto reset_drop;
		else if (ret == RET_DROP)
			goto drop;
		trim_length(tcph, cep);			/* ��M���� SDU ���𒲐�����B*/

		if (tcph->flags & TCP_FLG_ACK) {	/* ACK �t���O�̏��� */
			if ((ret = proc_ack2(input, cep, *offp, &needoutput)) == RET_DROP)
				goto drop;
			else if (ret == RET_RST_DROP)
				goto reset_drop;
			else if (ret == RET_RETURN)
				return IPPROTO_DONE;
			}
		}
	else if (cep->fsm_state == TCP_FSM_SYN_SENT) {	/* �\���I�[�v���ASYN ���M�ς�	*/
		if ((ret = syn_sent(tcph, cep)) == RET_RST_DROP)
			goto reset_drop;
		else if (ret == RET_DROP)
			goto drop;
		trim_length(tcph, cep);			/* ��M���� SDU ���𒲐�����B*/

		if (tcph->flags & TCP_FLG_ACK) {	/* ACK �t���O�̏��� */
			if ((ret = proc_ack2(input, cep, *offp, &needoutput)) == RET_DROP)
				goto drop;
			else if (ret == RET_RST_DROP)
				goto reset_drop;
			else if (ret == RET_RETURN)
				return IPPROTO_DONE;
			}
		}
	else {
		if (cep->fsm_state == TCP_FSM_SYN_RECVD) {	/* SYN ����M�ASYN ���M�ς�	*/
			/*
			 *  ���肩���M�m�F�������ė��Ă��A
			 *
			 *    ACK <= ���m�F�̍ŏ����M SEQ (snd_una) &&
			 *           ���M�����ő�     SEQ (snd_max) < ACK
			 *
			 *  �Ȃ�A���Z�b�g�𑗂��ăZ�O�����g��j������B
			 */
			if ((tcph->flags & TCP_FLG_ACK) &&
			    (SEQ_LE(tcph->ack, cep->snd_una) ||
			     SEQ_GT(tcph->ack, cep->snd_max)))
			     	goto reset_drop;
			}

		/* 
		 *  RST �t���O����M�����Ƃ��̏��� (�ُ�ؒf)
		 */
		if (tcph->flags & TCP_FLG_RST) {
			if (SEQ_GE(tcph->seq, cep->last_ack_sent) &&
			    SEQ_LT(tcph->seq, cep->last_ack_sent + cep->rcv_wnd)) {
				/*
				 *  ��M�����Z�O�����g�� SEQ ���A�Ō�ɑ��M���� ACK (last_ack_sent)
				 *  ����A��M�E�C���h�E�T�C�Y�܂ł̊Ԃ̏���
				 */
				switch (cep->fsm_state) {
				case TCP_FSM_SYN_RECVD:		/* SYN ����M���ASYN ���M�ς�		*/

					cep->net_error = EV_CNNRF;	/* �ڑ��s�\ */
					cep->error     = E_CLS;
					NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_RSTS], 1);
					NET_COUNT_MIB(tcp_stats.tcpAttemptFails, 1);
					cep = tcp_close(cep);
					break;

				case TCP_FSM_ESTABLISHED:	/* �R�l�N�V�����J�݊���			*/
				case TCP_FSM_CLOSE_WAIT:	/* FIN ��M�A�N���[�Y�҂�		*/
					NET_COUNT_MIB(tcp_stats.tcpEstabResets, 1);
					/* fallthrough */

				case TCP_FSM_FIN_WAIT_1:	/* �I�����āAFIN ���M�ς�		*/
				case TCP_FSM_FIN_WAIT_2:	/* �I���AFIN �`�B�m�F��M�AFIN�҂�	*/

					cep->net_error = EV_CNRST;	/* �ڑ����Z�b�g */
					cep->error     = E_CLS;
					NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_RSTS], 1);
					/* no break; */

				case TCP_FSM_CLOSING:		/* �I���AFIN �����ς݁AACK �҂�	*/
				case TCP_FSM_LAST_ACK:		/* FIN ��M�A�I���AACK �҂�	*/

					cep = tcp_close(cep);
					break;
					}
				}
			goto drop;
			}

		/*
		 *  CEP �̏�Ԃ� SYN ����M���ASYN ���M�ς݂̏ꍇ�́A
		 *  ��M�E�B���h�Ɏ��܂�悤�Ƀf�[�^��
		 *  ��������O�ɁA���̐ڑ��ɂ��p�P�b�g���ǂ��������؂���B
		 *
		 *    ��M��������� SEQ < ����� SEQ �̏����l (irs)
		 *
		 *  ����́A"LAND" DoS �U���̖h��ł���B
		 */
		if (cep->fsm_state == TCP_FSM_SYN_RECVD && SEQ_LT(tcph->seq, cep->irs)) {
			goto reset_drop;
			}

		/*
		 *  ��M�����҂��Ă���ŏ��� SEQ (rcv_nxt) - ��M��������� SEQ ��
		 *  ���Ȃ�Arcv_nxt �ȑO�̃f�[�^�͂��łɎ�M���Ă���̂ŁA���̕�����
		 *  �폜����B
		 *                           <---------- rcv_wnd --------->
		 *                           rcv_nxt                      rcv_nxt + rcv_wnd
		 *                           v                            v
		 *                      -----+----------------------------+-----
		 *                           |                            |
		 *                      -----+----------------------------+-----
		 *           +----------------------+
		 *           |***************|      |
		 *           +----------------------+
		 *           ^                      ^
		 *           seq                    seq + len
		 *           <---------------> �폜����B
		 */
		todrop = cep->rcv_nxt - tcph->seq;
		if (todrop > 0) {

			/*
			 *  SYN �t���O�����Ă���Ƃ��́A���̕� (1 �I�N�e�b�g)
			 *  SEQ ��i�߁A�ً}�|�C���^�ƍ폜���钷���𒲐�����B
			 */
			if (tcph->flags & TCP_FLG_SYN) {
				tcph->flags &= ~TCP_FLG_SYN;
				tcph->seq ++;
				if (tcph->urp > 1)
					tcph->urp --;
				else
					tcph->flags &= ~TCP_FLG_URG;
				todrop --;
				}

			/*
			 *  �폜���钷���� SDU ��蒷���A�܂�A��M�����҂��Ă���
			 *  �ŏ��� SEQ (rcv_nxt) �ɒB���Ă��Ȃ����A
			 *  �폜���钷���� SDU �Ɠ����ŁAFIN �t���O�����ĂȂ����
			 *  �S�č폜����B
			 */
			if ( todrop >  tcph->sum ||		/* tcph->sum �� TCP �� SDU �� */
			    (todrop == tcph->sum && (tcph->flags & TCP_FLG_FIN) == 0)) {
				tcph->flags &= ~TCP_FLG_FIN;
				cep->flags |= TCP_CEP_FLG_ACK_NOW;
				todrop = tcph->sum;		/* tcph->sum �� TCP �� SDU �� */
				}

			/*
			 *  SDU ��O�ɋl�߂�B
			 */
			if (todrop < tcph->sum) {		/* tcph->sum �� TCP �� SDU �� */
				memcpy(GET_TCP_SDU(input, *offp),
				       GET_TCP_SDU(input, *offp) + todrop, (size_t)(tcph->sum - todrop));
				}

			/*
			 *  SEQ �� SDU ���𒲐�����B
			 */
			tcph->seq +=     todrop;
			tcph->sum -= (uint16_t)todrop;	/* tcph->sum �� TCP �� SDU �� */

			/*
			 *  �ً}�|�C���^�𒲐�����B
			 */
			if (tcph->urp > todrop)
				tcph->urp -= (uint16_t)todrop;
			else {
				tcph->flags &= ~TCP_FLG_URG;
				tcph->urp = 0;
				}

			NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DUP_SEGS], 1);
			}

		/*  
		 *  �������[�U�^�X�N���I��������ɁA�f�[�^����M����
		 *  �ꍇ�́ARST �𑗂�B
		 */
		if (cep->fsm_state == TCP_FSM_LAST_ACK && tcph->sum > 0) {	/* tcph->sum �� TCP �� SDU �� */
			cep = tcp_close(cep);
			goto reset_drop;
			}

		/*
		 *  ��M�Z�O�����g����M�E�B���h�𒴂���ꍇ�́A
		 *  �������������B
		 *
		 *       <---------- rcv_wnd --------->
		 *       rcv_nxt                      (rcv_nxt + rcv_wnd)
		 *       v                            v
		 *  -----+----------------------------+-----
		 *       |                            |
		 *  -----+----------------------------+-----
		 *                    +----------------------+
		 *                    |               |******|
		 *                    +----------------------+
		 *                    ^                      ^
		 *                    seq                    seq + len
		 *                                     <-----> �폜����B
		 */
		todrop = (tcph->seq + tcph->sum) - (cep->rcv_nxt + cep->rcv_wnd);	/* tcph->sum �� TCP �� SDU �� */
		if (todrop > 0) {
			if (todrop > tcph->sum) {					/* tcph->sum �� TCP �� SDU �� */
				/*
				 *  ��M���� SDU �̑S�Ă���M�E�B���h�𒴂���ꍇ�B
				 *
				 *  TIME_WAIT ���ɁA�V���Ȑڑ��v������M������
				 *  �Â��ڑ���j�����A�V���Ȑڑ����J�n����B
				 *  �������ASEQ �͑O���i��ł��Ȃ���΂Ȃ�Ȃ��B
				 */
				if ((tcph->flags & TCP_FLG_SYN) &&
				    cep->fsm_state == TCP_FSM_TIME_WAIT &&
				    SEQ_GT(tcph->seq, cep->rcv_nxt)) {
					iss = cep->snd_nxt + TCP_ISS_INCR();
					tcp_close(cep);
					syscall(dly_tsk(0));
					goto find_cep;
				    	}

				/*
				 *  ��M�E�B���h�� 0 �ŁA��M���� SEQ ��
				 *  ��M�����҂��Ă���ŏ��� SEQ ����v�����Ƃ���
				 *  ACK ��Ԃ��B����ȊO�̓f�[�^��j�����AACK ��Ԃ��B
				 */
				if (cep->rcv_wnd == 0 && (tcph->seq == cep->rcv_nxt || tcph->sum == 0)) {
					cep->flags |= TCP_CEP_FLG_ACK_NOW;
					}
				else if (drop_after_ack(input, cep, *offp) == RET_RST_DROP)
					goto reset_drop;
				else {
					return IPPROTO_DONE;
					}
				}
			tcph->sum -= (uint16_t)todrop;	/* tcph->sum �� TCP �� SDU �� */
			tcph->flags &= ~(TCP_FLG_PUSH | TCP_FLG_FIN);
			}

		/*
		 *  �����ASYN ���Z�b�g����Ă���΁A
		 *  �G���[�Ȃ̂� RST �𑗂�A�ڑ���j������B
		 */
		if (tcph->flags & TCP_FLG_SYN) {
			cep->net_error = EV_CNRST;
			cep = tcp_drop(cep, E_CLS);
			goto reset_drop;
			}

		/*
		 *  �����AACK ���Z�b�g����Ă��Ȃ��ꍇ�́A
		 *  ��Ԃ� SYN ��M�ς݂�
		 *  SYN �𑗐M���悤�Ƃ��Ă���΁A�����𑱂��邪�A
		 *  ����ȊO�̓Z�O�����g��j�����ďI������B
		 */
		if ((tcph->flags & TCP_FLG_ACK) == 0) {
			if (!(cep->fsm_state == TCP_FSM_SYN_RECVD || (cep->flags & TCP_CEP_FLG_NEED_SYN)))
				goto drop;
			}
		else {
			/*
			 * ACK �̏���
			 */
			ret = proc_ack1(input, cep, *offp, &needoutput);
			if (ret == RET_DROP)
				goto drop;
			else if (ret == RET_RST_DROP)
				goto reset_drop;
			else if (ret == RET_RETURN)
				return IPPROTO_DONE;
			}
		}

/* step 6 */

	/* ���M�E�B���h���X�V����B*/
	if (update_wnd(tcph, cep) == true)
		needoutput = true;

	/* �ً}�f�[�^����������B*/
	proc_urg(tcph, cep);

/* do data */

	/*
	 *  SDU �����邩�AFIN �𖢎�M�̏�ԂŁA�ŏ��� FIN ����M�����Ƃ��A
	 *  ��M�Z�O�����g�L���[�� net_buf ��ǉ�����B
	 *  ����ȊO�̏ꍇ�́A�Z�O�����g��j������B
	 */
	flags = tcph->flags;
	if ((tcph->sum > 0 || (flags & TCP_FLG_FIN)) &&		/* tcph->sum �� TCP �� SDU �� */
	    TCP_FSM_HAVE_RCVD_FIN(cep->fsm_state) == 0) {
		flags = reassemble(input, cep, *offp, flags);
		}
	else {
		syscall(rel_net_buf(input));
		flags &= ~TCP_FLG_FIN;
		}

	/*
	 *  FIN ����M������R�l�N�V�������N���[�Y����B
	 */
	if (flags & TCP_FLG_FIN)
		close_connection(cep, &needoutput);

	/* �o�͂��s������I������B*/
	if (needoutput == true || (cep->flags & TCP_CEP_FLG_ACK_NOW)) {
		/* ���M���w������B*/
		cep->flags |=  TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}

	return IPPROTO_DONE;

reset_drop:
	/*
	 *  RST ���M����
	 */

	if ((tcph->flags & TCP_FLG_RST) || IN_IS_NET_ADDR_MULTICAST(&iph->dst))
		goto drop;

	/* �z�X�g�I�[�_�[����l�b�g���[�N�I�[�_�[�ɖ߂��B*/

	HTONS(tcph->sport);
	HTONS(tcph->dport);

	if (cep == NULL)
		rbfree = 0;
	else
		rbfree = cep->rbufsz - cep->rwbuf_count;

	if (tcph->flags & TCP_FLG_ACK) {
		tcp_respond(input, cep, 0, tcph->ack, rbfree, TCP_FLG_RST);
		}
	else {
		if (tcph->flags & TCP_FLG_SYN)
			tcph->sum ++;		/* tcph->sum �� SDU �� */
		tcp_respond(input, cep, tcph->seq + tcph->sum, 0, rbfree, TCP_FLG_RST | TCP_FLG_ACK);
		}

	/* input �� tcp_respoond �ŕԋp�����B*/
	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_RSTS], 1);
	NET_COUNT_MIB(tcp_stats.tcpOutRsts, 1);
	return IPPROTO_DONE;

drop:
	NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DROP_SEGS], 1);
	NET_COUNT_MIB(tcp_stats.tcpInErrs, 1);
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

#endif	/* of #ifdef SUPPORT_TCP */
