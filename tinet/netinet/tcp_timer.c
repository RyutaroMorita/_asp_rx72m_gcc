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
 *  @(#) $Id: tcp_timer.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 *	@(#)tcp_timer.c	8.2 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_timer.c,v 1.28.2.1 1999/08/29 16:29:56 peter Exp $
 */

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
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>

#ifdef SUPPORT_TCP

/*
 *  �Ǐ��֐�
 */

static T_TCP_CEP *tcp_timers (T_TCP_CEP *cep, int_t tix);

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

static void tcp_tw_timo (void);

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

/*
 *  �o�b�N�I�t����
 *
 *  �đ����s�����тɁA�^�C���A�E�g�̎��Ԃ���������B
 */

const static uint8_t tcp_back_off[] = {
	UINT_C(1), 	UINT_C(2), 	UINT_C(4), 	UINT_C(8),
	UINT_C(16), 	UINT_C(32), 	UINT_C(64), 	UINT_C(64),
	UINT_C(64), 	UINT_C(64), 	UINT_C(64), 	UINT_C(64), 
	UINT_C(64)
	};

#define TCP_TOTAL_BACK_OFF	511	/* �o�b�N�I�t���Ԃ̍��v */

/*
 *  tcp_timers -- �^�C���A�E�g����
 */

static T_TCP_CEP *
tcp_timers (T_TCP_CEP *cep, int_t tix)
{
	uint16_t	win;


	switch (tix) {

	/*
	 *  �đ��^�C�}
	 */
	case TCP_TIM_REXMT:
	
		/*
		 *  �ő�đ��� (TCP_MAX_REXMT_SHIFT�A�W�� 12 ��) �ɂȂ����Ƃ��́A
		 *  �R�l�N�V������ؒf����B
		 */
		if (++ cep->rxtshift > TCP_MAX_REXMT_SHIFT) {
			cep->rxtshift  = TCP_MAX_REXMT_SHIFT;
			cep->net_error = EV_REXMTMO;
			cep = tcp_drop(cep, E_CLS);
			break;
			}

		/*
		 *  �đ��^�C���A�E�g���v�Z����B
		 */
		cep->rxtcur = tcp_range_set((T_TCP_TIME)(tcp_rexmt_val(cep) * tcp_back_off[cep->rxtshift]),
		                            (T_TCP_TIME)TCP_TVAL_MIN, 
		                            (T_TCP_TIME)TCP_TVAL_MAX_REXMT);
		cep->timer[TCP_TIM_REXMT] = cep->rxtcur;

		/*
		 *  srtt:   ���������ꂽ RTT
		 *  rttvar: ���������ꂽ���U
		 *
		 *  �đ��񐔂��ő�đ��񐔂� 1/4 �ɂȂ����Ƃ��́A
		 *  ���������ꂽ���U (rttvar) �� srtt �����Z���A
		 *  ���������ꂽ RTT �� 0 �ɂ���B
		 *  
		 */
		if (cep->rxtshift > TCP_MAX_REXMT_SHIFT / 4) {
			cep->rttvar += (cep->srtt >> TCP_SRTT_SHIFT);
			cep->srtt    = 0;
			}

		/*
		 *  snd_nxt: ���ɑ��M���� SEQ�A���̎��_�ł́A�O�񑗐M���� SEQ
		 *  snd_una: ���m�F�̍ŏ����M SEQ	 �܂��́A�m�F���ꂽ�ő呗�M SEQ
		 *
		 *  �O�񑗐M���� SEQ (snd_nxt) �� 
		 *  �m�F���ꂽ�ő呗�M SEQ (snd_una) �܂Ŗ߂��B
		 */
		cep->snd_nxt = cep->snd_una;
		cep->flags  |= TCP_CEP_FLG_ACK_NOW;

		/*
		 *  rtt: �������Ԃ̌v���𒆎~����B
		 */
		cep->rtt     = 0;

		/*
		 *  ���M�E�C���h�̐ݒ�
		 *
		 *  snd_wnd:  ����̎�M�\�E�B���h�T�C�Y
		 *  snd_cwnd: �t�s�E�B���h�T�C�Y
		 *  maxseg  : ����̍ő��M�Z�O�����g�T�C�Y
		 *
		 *  ����̎�M�\�E�B���h�T�C�Y (snd_wnd) ���A
		 *  �t�s�E�B���h�T�C�Y (snd_cwnd) ��
		 *  �ǂ��炩�������T�C�Y�� 1/2 ���A�X��
		 *  ����̍ő��M�Z�O�����g�T�C�Y (maxseg) �Ŋ������l�B
		 *  �������A2 �ȏ�
		 */
		if (cep->snd_wnd < cep->snd_cwnd)
			win = cep->snd_wnd / 2 / cep->maxseg;
		else
			win = cep->snd_cwnd / 2 / cep->maxseg;

		if (win < 2)
			win = 2;

		/*
		 *  �t�s�E�B���h�T�C�Y (snd_cwnd) ��
		 *  ����̎�M�\�E�B���h�T�C�Y (snd_wnd) �ɁA
		 *  �t�s�E�B���h�T�C�Y�̂������l (snd_ssthresh) ��
		 *  ����̎�M�\�E�B���h�T�C�Y (snd_wnd) �� win �{��
		 *  �ݒ肷��B
		 */
		cep->snd_cwnd     = cep->maxseg;
		cep->snd_ssthresh = win * cep->maxseg;
		cep->dupacks      = 0;

		/* �o�͂��|�X�g����B*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		break;

	/*
	 *  �����^�C�}	
	 */
	case TCP_TIM_PERSIST:

		/*
		 *  �ő�đ��� (TCP_MAX_REXMT_SHIFT�A�W�� 12 ��) �𒴂��Ă��āA
		 *  �A�C�h�����Ԃ��A�ۗ��^�C�}�̕W���l (TCP_TVAL_KEEP_IDLE�A
		 *  �W�� 2 * 60 * 60 �b) �ȏォ�A
		 *  �đ��^�C���A�E�g�l * �o�b�N�I�t���Ԃ̍��v�ȏ�Ȃ�
		 *  �R�l�N�V������ؒf����B
		 */
		if (cep->rxtshift > TCP_MAX_REXMT_SHIFT &&
		    (cep->idle >= TCP_TVAL_KEEP_IDLE ||
		     cep->idle >= tcp_rexmt_val(cep) * TCP_TOTAL_BACK_OFF)) {
			cep->net_error = EV_REXMTMO;
			cep = tcp_drop(cep, E_CLS);
			break;
			}

		/* �����^�C�}���Đݒ肵�A�o�͂��|�X�g����B*/
		tcp_set_persist_timer(cep);

		cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR | TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		break;

	/*
	 *  �ۗ� (keep alive) �^�C�}
	 */
	case TCP_TIM_KEEP:

		/*
		 *  �R�l�N�V�������J�݂����܂łɃ^�C���A�E�g������
		 *  �R�l�N�V�����̊J�݂𒆎~����B
		 */
		if (cep->fsm_state < TCP_FSM_ESTABLISHED) {
			cep->net_error = EV_REXMTMO;
			cep = tcp_drop(cep, E_CLS);
			break;
			}

#ifdef TCP_CFG_ALWAYS_KEEP

		else if (cep->fsm_state < TCP_FSM_CLOSING) {
			if (cep->idle >= TCP_TVAL_KEEP_IDLE + 
			                 TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL) {
				cep->net_error = EV_REXMTMO;
				cep = tcp_drop(cep, E_CLS);
				break;
				}
			else
				tcp_respond(NULL, cep, cep->rcv_nxt, cep->snd_una - 1,
				                       cep->rbufsz - cep->rwbuf_count, 0);
			cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_INTERVAL;
			}
		else
			cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;

#else	/* of #ifdef TCP_CFG_ALWAYS_KEEP */

		cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_IDLE;

#endif	/* of #ifdef TCP_CFG_ALWAYS_KEEP */

		break;

	/*
	 *  2MSL �^�C�}		
	 */
	case TCP_TIM_2MSL:

		if (cep->fsm_state != TCP_FSM_TIME_WAIT &&
		    cep->idle  <= TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL)
			cep->timer[TCP_TIM_2MSL] = TCP_TVAL_KEEP_INTERVAL;
		else
			cep = tcp_close(cep);
		break;
		}

	return cep;
	}

/*
 *  tcp_cancel_timers -- �S�Ẵ^�C�}���L�����Z������B
 */

void
tcp_cancel_timers (T_TCP_CEP *cep)
{
	int_t ix;

	for (ix = NUM_TCP_TIMERS; ix -- > 0; )
		cep->timer[ix] = 0;
	}

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

/*
 *  tcp_tw_timo -- Time Wait �p TCP �ʐM�[�_�̃^�C���A�E�g����
 */

void
tcp_tw_timo (void)
{
	T_TCP_CEP	*cep, *lcep;
	T_TCP_TWCEP*	twcep;
	T_TCP_TIME	longer;
	int_t		frees, waits;

	/*
	 *  Time Wait �p TCP �ʐM�[�_�Ń^�C���A�E�g�̃G���g����T�����A
	 *  �T�������G���g�����󂫂ɂ���B
	 */
	frees = 0;
	for (twcep = &tcp_twcep[NUM_TCP_TW_CEP_ENTRY]; twcep -- != tcp_twcep; )
		if (twcep->fsm_state == TCP_FSM_TIME_WAIT && -- twcep->timer_2msl == 0) {
			twcep->fsm_state = TCP_FSM_CLOSED;
			frees ++;
			}

	/*
	 *  Time Wait �p TCP �ʐM�[�_�̋󂫃G���g��������������
	 *  �W�� TCP �ʐM�[�_�� Time Wait ���� TCP �ʐM�[�_��T�����A
	 *  �K�v�ȏ��� Time Wait �p TCP �ʐM�[�_�Ɉڂ��āA
	 *  �W���� TCP �ʐM�[�_���J������B
	 */
	if (frees > 0) {
		waits = 0;
		for (cep = &tcp_cep[tmax_tcp_cepid]; cep -- != tcp_cep; )
			if (cep->fsm_state == TCP_FSM_TIME_WAIT)
				waits ++;
		if (waits > frees)
			waits = frees;

		/*
		 *  �����Ƃ������� Time Wait ���Ă��� TCP �ʐM�[�_���J������B
		 */
		while (waits > 0) {
			longer = TCP_TVAL_MSL * 2;
			lcep   = NULL;
			for (cep = &tcp_cep[tmax_tcp_cepid]; cep -- != tcp_cep; )
				if (cep->fsm_state == TCP_FSM_TIME_WAIT && cep->timer[TCP_TIM_2MSL] < longer) {
					longer = cep->timer[TCP_TIM_2MSL];
					lcep   = cep;
					}
			if (lcep != NULL) {
				tcp_move_twcep(lcep);
				waits --;
				}
			else
				break;
			}
		}
	}

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

/*
 *  tcp_slow_timo -- 500 [ms] ���Ɍďo����� TCP �^�C���A�E�g�֐�
 */

void
tcp_slow_timo (void *ignore)
{
	T_TCP_CEP	*cep;
	int_t		cix, tix;

	for (cix = tmax_tcp_cepid; cix -- > 0; ) {
		cep = &tcp_cep[cix];
		if (!(cep->fsm_state == TCP_FSM_CLOSED || cep->fsm_state == TCP_FSM_LISTEN)) {
			for (tix = NUM_TCP_TIMERS; cep != NULL && tix -- > 0; ) {
				if (cep->timer[tix] != 0 && -- cep->timer[tix] == 0) {
					cep = tcp_timers(cep, tix);
					}
				}
			if (cep != NULL) {
				cep->idle ++;
				if (cep->rtt) {
					cep->rtt ++;
					}
				}
			}
		}

#if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0

	tcp_tw_timo();

#endif	/* of #if defined(NUM_TCP_TW_CEP_ENTRY) && NUM_TCP_TW_CEP_ENTRY > 0 */

	if (tcp_iss != 0) {
		tcp_iss += TCP_ISS_INCR() / TCP_SLOW_HZ;
		}

	timeout(tcp_slow_timo, NULL, TCP_SLOW_TMO);
	}

#ifdef TCP_CFG_DELAY_ACK

/*
 *  tcp_fast_timo -- 200 [ms] ���Ɍďo����� TCP �^�C���A�E�g�֐�
 */

void
tcp_fast_timo (void *ignore)
{
	T_TCP_CEP	*cep;
	int_t		cix;

	for (cix = tmax_tcp_cepid; cix -- > 0; ) {
		cep = &tcp_cep[cix];
		if (cep->flags & TCP_CEP_FLG_DEL_ACK) {
			cep->flags &= ~TCP_CEP_FLG_DEL_ACK;
			cep->flags |=  TCP_CEP_FLG_ACK_NOW | TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}
		}

	timeout(tcp_fast_timo, NULL, TCP_FAST_TMO);
	}

#endif/* of #ifdef TCP_CFG_DELAY_ACK */

/*
 *  tcp_range_set -- ���Ԃ��w�肵���͈͂ɐݒ肷��B
 */

T_TCP_TIME
tcp_range_set (T_TCP_TIME value, T_TCP_TIME tvmin, T_TCP_TIME tvmax)
{
	if ((uint32_t)value < (uint32_t)tvmin)
		return tvmin;
	else if ((uint32_t)value > (uint32_t)tvmax)
		return tvmax;
	else
		return value;
	}

/*
 *  tcp_set_persist_timer -- �����^�C�}�̐ݒ�
 */

void
tcp_set_persist_timer (T_TCP_CEP *cep)
{
	T_TCP_TIME time;

	/*
	 *  srtt:   ���������ꂽ RTT
	 *  rttvar: ���������ꂽ���U
	 */
	time = ((cep->srtt >> 2) + cep->rttvar) >> 1;

	/*
	 *  �đ��^�C�}���ݒ肳��Ă���Ή񕜕s�\�G���[
	 */
	if (cep->timer[TCP_TIM_REXMT])
		/* %%% panic("tcp_output REXMT"); %%% */;

	/*
	 *  �����^�C�}��ݒ肷��B
	 */
	cep->timer[TCP_TIM_PERSIST] = tcp_range_set((T_TCP_TIME)(time * tcp_back_off[cep->rxtshift]),
	                                            (T_TCP_TIME)TCP_TVAL_MIN_PERSIST,
	                                            (T_TCP_TIME)TCP_TVAL_MAX_PERSIST);

	/*
	 *  �đ��񐔂��X�V����B
	 */
	if (cep->rxtshift < TCP_MAX_REXMT_SHIFT)
		cep->rxtshift ++;
	}

#endif	/* of #ifdef SUPPORT_TCP */
