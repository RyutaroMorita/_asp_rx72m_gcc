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
 *  @(#) $Id: tcp_timer.h,v 1.5 2009/12/24 05:47:21 abe Exp $
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
 *	@(#)tcp_timer.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/tcp_timer.h,v 1.13.2.1 1999/08/29 16:29:56 peter Exp $
 */
 
#ifndef _TCP_TIMER_H_
#define _TCP_TIMER_H_

/* TCP �^�C�}�ϐ� */

#define NUM_TCP_TIMERS		4	/* TCP �̃^�C�}��	*/

#define TCP_TIM_REXMT		0	/* �đ��^�C�}		*/
#define TCP_TIM_PERSIST		1	/* �����^�C�}		*/
#define TCP_TIM_KEEP		2	/* �ۗ� (keep alive) �^�C�}*/
#define TCP_TIM_2MSL		3	/* 2MSL �^�C�}		*/

/* MSL: Maximum Segment Lifetime, �ő�Z�O�����g�������� 		*/

/*
 *  TCP/IP �̃^�C�}�̒�`
 */

#define TCP_SLOW_TMO		(ULONG_C(500)/NET_TIMER_CYCLE)	/* 500 [ms]	*/
#define TCP_FAST_TMO		(ULONG_C(200)/NET_TIMER_CYCLE)	/* 200 [ms]	*/

#define TCP_SLOW_HZ		(ULONG_C(1000)/TCP_SLOW_TMO/NET_TIMER_CYCLE)	/* Hz	*/

/* TCP �^�C�}�l */

#define TCP_TVAL_MSL		(TCP_SLOW_HZ * 30)
					/* �ő�Z�O�����g��������	*/

#define TCP_TVAL_SRTT_BASE	0	/* ���炩�ȉ������Ԃ̊�l*/

#define TCP_TVAL_RTO_BASE	(TCP_SLOW_HZ * 3)
		/* ��񂪓����Ȃ��ꍇ�̍đ��^�C���A�E�g�̊�l	*/

#define TCP_TVAL_MIN_PERSIST	(TCP_SLOW_HZ * 5)
				/* �����^�C���A�E�g�̍ŏ��l	*/
#define TCP_TVAL_MAX_PERSIST	(TCP_SLOW_HZ * 60)
				/* �����^�C���A�E�g�̍ő�l	*/

#define TCP_TVAL_KEEP_INIT	(TCP_SLOW_HZ * 75)
					/* �ۗ��^�C�}�̏����l	*/
#define TCP_TVAL_KEEP_IDLE	(TCP_SLOW_HZ * 2 * 60 * 60)
					/* �ۗ��^�C�}�N���܂ł̕W���l*/
#define TCP_TVAL_KEEP_INTERVAL	(TCP_SLOW_HZ * 75)
					/* �ۗ��^�C�}�C���^�[�o���̕W���l*/
#define TCP_TVAL_KEEP_COUNT	8	/* �ۗ��^�C���A�E�g�̍ő�l*/

#define TCP_TVAL_MIN		(TCP_SLOW_HZ * 3)
					/* ���Ԃ̍ŏ��P��	*/
#define TCP_TVAL_MAX_REXMT	(TCP_SLOW_HZ * 64)
					/* �ő�đ�����		*/

/*
 *  �ȉ��̕ϐ��̒l�̓}�N���Őݒ肷��B
 *
 *  tcp_maixidle   = tcp_keepcnt * tcp_keepintvl
 *                 = TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL
 *  tcp_keepcnt    = TCP_TVAL_KEEP_COUNT
 *  tcp_keepintval = TCP_TVAL_KEEP_INTERVAL
 *
 */

/*
 *  ���̑��̒萔
 */

#define TCP_MAX_REXMT_SHIFT	12	/* �ő�đ���		*/

/* TCP �^�C�}�l�̌^ */

typedef int16_t T_TCP_TIME;

/*
 *  �֐�
 */

extern void tcp_slow_timo (void *ignore);
extern void tcp_fast_timo (void *ignore);

extern T_TCP_TIME tcp_range_set (T_TCP_TIME value, T_TCP_TIME tvmin, T_TCP_TIME tvmax);

#endif	/* of #ifndef _TCP_TIMER_H_ */
