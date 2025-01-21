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
 *  @(#) $Id: net_timer.c,v 1.5.4.1 2015/02/05 02:09:13 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
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

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp_timer.h>

/*
 *  �ϐ�
 */

static T_NET_CALLOUT callout[NUM_NET_CALLOUT];

/*
 *  �ďo���G���g���o�^
 */

void
timeout (callout_func func, void *arg, RELTIM timeout)
{
	int_t ix;

	/* �ďo���G���g�����l������ */
	syscall(wai_sem(SEM_CALL_OUT_LOCK));
	for (ix = NUM_NET_CALLOUT; callout[-- ix].func != NULL; )
		if (ix == 0) {
			syslog(LOG_WARNING, "[NET] callout busy, size=%d.", NUM_NET_CALLOUT);
			syscall(sig_sem(SEM_CALL_OUT_LOCK));
			return;
			}

	/* �ďo���G���g����ݒ肷�� */
	callout[ix].func	= func;
	callout[ix].arg		= arg;
	callout[ix].timeout	= timeout;
	syscall(sig_sem(SEM_CALL_OUT_LOCK));
	}

/*
 *  �ďo���G���g���폜
 */

void
untimeout (callout_func func, void *arg)
{
	int_t ix;

	/* �G���g����T�� */
	for (ix = NUM_NET_CALLOUT; ix -- > 0; ) {
		syscall(wai_sem(SEM_CALL_OUT_LOCK));
		if (callout[ix].func == func && callout[ix].arg == arg && callout[ix].timeout > 0) {
			callout[ix].func = NULL;
			syscall(sig_sem(SEM_CALL_OUT_LOCK));
			break;
			}
		syscall(sig_sem(SEM_CALL_OUT_LOCK));
		}
	}

/*
 *  �l�b�g���[�N�^�C�}�^�X�N
 *
 *    ����: �^�X�N�R���e�L�X�g�Ŏ��s����K�v�����邽�߁C
 *          �����n���h���͎g�p�ł��Ȃ��B
 */

static char const tinet_banner[] =
"\n"
"TINET %d.%d.%d (" __DATE__ ", " __TIME__ ")\n"
"Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering\n"
"                    Tomakomai National College of Technology, JAPAN\n";

void
net_timer_task(intptr_t exinf)
{
	ID		tskid;
	int_t		ix;
	callout_func	func;
	void 		*arg;

	get_tid(&tskid);
	syslog(LOG_NOTICE, tinet_banner,
	       (TINET_PRVER   >> 12) & UINT_C(0x0f),
	       (TINET_PRVER   >>  4) & UINT_C(0x0f),
	        TINET_PRVER          & UINT_C(0x0f));
	syslog(LOG_NOTICE, "[NET/TIMER:%d] started.", tskid);

	/* IP ������������B*/
	IP_INIT();

#ifdef SUPPORT_TCP

	/* TCP �o�̓^�X�N���N������ */
	syscall(act_tsk(TCP_OUTPUT_TASK));

#endif	/* of #ifdef SUPPORT_TCP */

#if defined(SUPPORT_UDP) && defined(UDP_CFG_NON_BLOCKING)

	/* UDP �o�̓^�X�N���N������ */
	syscall(act_tsk(UDP_OUTPUT_TASK));

#endif	/* of #if defined(SUPPORT_UDP) && defined(UDP_CFG_NON_BLOCKING) */

	while (true) {
		/* �^�C���A�E�g�����G���g�����ďo���B*/
		syscall(wai_sem(SEM_CALL_OUT_TIMEOUT));
		for (ix = NUM_NET_CALLOUT; ix -- > 0; ) {
			syscall(wai_sem(SEM_CALL_OUT_LOCK));
			if (callout[ix].func != NULL && callout[ix].timeout == 0) {
				func = callout[ix].func;
				arg  = callout[ix].arg;
				callout[ix].func = NULL;
				syscall(sig_sem(SEM_CALL_OUT_LOCK));
				(func)(arg);
				}
			else
				syscall(sig_sem(SEM_CALL_OUT_LOCK));
			}
		}
	}

/*
 *  �l�b�g���[�N�^�C�}�n���h��
 *
 *    NET_TIMER_CYCLE (100ms) ���Ɍďo�����B
 */

void
net_timer_handler(intptr_t exinf)
{
	int_t	ix, count = 0;

	for (ix = NUM_NET_CALLOUT; ix -- > 0; ) {
		if (callout[ix].func != NULL && callout[ix].timeout > 0) {
			callout[ix].timeout --;
			if (callout[ix].timeout == 0)
				count ++;
			}
		}

	if (count)
		syscall(isig_sem(SEM_CALL_OUT_TIMEOUT));
	}
