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
 *  @(#) $Id: tcp_subr_cs.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 *	@(#)tcp_subr.c	8.2 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_subr.c,v 1.49.2.4 1999/08/29 16:29:55 peter Exp $
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
#include <net/if_arp.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/nd6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>
#include <netinet/in_itron.h>

#ifdef SUPPORT_TCP

#ifdef TCP_CFG_SWBUF_CSAVE

#ifndef TCP_CFG_SWBUF_CSAVE_ONLY

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���L���ȏꍇ
 *  �������A�ʐM�[�_�̑��M�E�B���h�o�b�t�@�icep->sbuf�j�̒l�ɂ��A
 *  TCP �ʐM�[�_���ɑ��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���g�p���邩�A
 *  �g�p���Ȃ�����؂�ւ���B
 */

/*
 *  tcp_drop_swbuf -- ���M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���폜����i�I���j�B
 */

void
tcp_drop_swbuf (T_TCP_CEP *cep, uint_t len)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		tcp_drop_swbuf_ncs(cep, len);
	else
		tcp_drop_swbuf_cs(cep, len);
	}

/*
 *  tcp_write_swbuf -- ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށi�I���j�B
 */

ER_UINT
tcp_write_swbuf (T_TCP_CEP *cep, void *data, uint_t len)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_write_swbuf_ncs(cep, data, len);
	else
		return tcp_write_swbuf_cs(cep, data, len);
	}

/*
 *  tcp_read_swbuf -- ���M�E�B���h�o�b�t�@����f�[�^��ǂݏo���i�I���j�B
 */

void
tcp_read_swbuf (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		tcp_read_swbuf_ncs(cep, output, len, doff);
	}

/*
 *  tcp_wait_swbuf -- ���M�E�B���h�o�b�t�@�Ƒ���̎�M�E�B���h���J���̂�҂i�I���j�B
 */

ER
tcp_wait_swbuf (T_TCP_CEP *cep, TMO tmout)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_wait_swbuf_ncs(cep, tmout);
	else
		return tcp_wait_swbuf_cs(cep, tmout);
	}

/*
 *  tcp_get_swbuf_addr -- ���M�E�B���h�o�b�t�@�̋󂫃A�h���X���l������i�I���j�B
 */

ER_UINT
tcp_get_swbuf_addr (T_TCP_CEP *cep, void **p_buf)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_get_swbuf_addr_ncs(cep, p_buf);
	else
		return tcp_get_swbuf_addr_cs(cep, p_buf);
	}

/*
 *  tcp_send_swbuf -- ���M�E�B���h�o�b�t�@�̃f�[�^�𑗐M�\�ɂ���i�I���j�B
 */

void
tcp_send_swbuf (T_TCP_CEP *cep, uint_t len)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		tcp_send_swbuf_ncs(cep, len);
	else
		tcp_send_swbuf_cs(cep, len);
	}

/*
 *  tcp_free_swbufq -- ���M�E�B���h�o�b�t�@�L���[�̉�����w������i�I���j�B
 */

void
tcp_free_swbufq (T_TCP_CEP *cep)
{
	if (!IS_PTR_DEFINED(cep->sbuf))
		tcp_free_swbufq_cs(cep);
	}

/*
 *  tcp_alloc_swbuf -- ���M�E�B���h�o�b�t�@�p�̃l�b�g���[�N�o�b�t�@�̊��蓖�Ă��w������i�I���j�B
 */

void
tcp_alloc_swbuf (T_TCP_CEP *cep)
{
	if (!IS_PTR_DEFINED(cep->sbuf))
		tcp_alloc_swbuf_cs(cep);
	}

/*
 *  tcp_is_swbuf_full -- ���M�E�B���h�o�b�t�@�����t���`�F�b�N����i�I���j�B
 */

bool_t
tcp_is_swbuf_full (T_TCP_CEP *cep)
{
	if (IS_PTR_DEFINED(cep->sbuf))
		return tcp_is_swbuf_full_ncs(cep);
	else
		return tcp_is_swbuf_full_cs(cep);
	}

#endif	/* of #ifndef TCP_CFG_SWBUF_CSAVE_ONLY */

/*
 *  tcp_drop_swbuf_cs -- ���M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���폜����i��p�j�B
 */

void
tcp_drop_swbuf_cs (T_TCP_CEP *cep, uint_t len)
{

	/*���M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���폜����B*/
	cep->swbuf_count -= (uint16_t)len;

	/* ���M�ς݂ŁAACK�҂��̎��́AACK�����ɕύX����B*/
	if (len > 0 && (cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_SENT) {
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_ACKED;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

/*
 *  tcp_write_swbuf_cs -- ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށi��p�j�B
 */

ER_UINT
tcp_write_swbuf_cs (T_TCP_CEP *cep, void *data, uint_t len)
{
	ER_UINT	error;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	if ((error = net_buf_siz(cep->swbufq)) > 0 && error >= IF_IP_TCP_HDR_SIZE) {


		/*
		 *  +-----------+--------+---------+---------+
		 *  | Ehter HDR | IP HDR | TCP HDR | TCP SDU |
		 *  +-----------+--------+---------+---------+
		 *        14        20        20        n
		 *   <---------------- error --------------->
		 *              ^
		 *              net_buf �� 4 �I�N�e�b�g���E�ɃA���C������Ă���B
		 *
		 *  tcp_output �� ip_output �ŁA�`�F�b�N�T�����v�Z����Ƃ��A
		 *  n �� 4 �I�N�e�b�g���E�ɂȂ�悤�� SDU �̌��� 0 ��
		 *  �p�b�f�B���O����B���̕����l�����đ��M�E�B���h�o�b�t�@��
		 *  �󂫃T�C�Y�� 4 �I�N�e�b�g���E�ɒ�������B
		 */
		error = (uint_t)(((error - IF_IP_TCP_HDR_SIZE) >> 2 << 2) + IF_IP_TCP_HDR_SIZE);

		if (len > cep->sbufsz - cep->swbuf_count)
			len = (uint_t)(cep->sbufsz - cep->swbuf_count);
		if (len > (error - IF_IP_TCP_HDR_SIZE))
			len = (uint_t)(error - IF_IP_TCP_HDR_SIZE);

		/* ���M�E�C���h�T�C�Y�ɂ��T�C�Y�𒲐�����B*/
		if (len > cep->snd_wnd) 
			len = cep->snd_wnd;
		if (len > cep->snd_cwnd)
			len = cep->snd_cwnd;

		/* ����̍ő��M�Z�O�����g�T�C�Y (maxseg) �𒴂��Ȃ��悤�ɂ���B*/
		if (len > cep->maxseg) 
			len = cep->maxseg;

		/* �f�[�^���ڂ��B*/
		memcpy(cep->sbuf_wptr, (void*)((uint8_t*)data), (size_t)len);
		cep->sbuf_wptr   += len;
		cep->swbuf_count += len;
		error             = len;

		/* �l�b�g���[�N�o�b�t�@���� IP �f�[�^�O��������ݒ肷��B*/
		cep->swbufq->len = (uint16_t)(cep->swbuf_count + IF_IP_TCP_HDR_SIZE);
		SET_IP_SDU_SIZE(GET_IP_HDR(cep->swbufq), cep->swbuf_count + TCP_HDR_SIZE);

		/* �t���O���A���M�\�ɐݒ肷��B*/
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_SEND_READY;
		}

	else {	/* ���M�E�C���h�o�b�t�@���s�� */
		syslog(LOG_WARNING, "[TCP] illegal window buff for send, CEP: %d, %4d < %4d.",
		                    GET_TCP_CEPID(cep), error, IF_IP_TCP_HDR_SIZE);

		/* ���M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		tcp_free_swbufq_cs(cep);
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_wait_swbuf_cs -- ���M�E�B���h�o�b�t�@�Ƒ���̎�M�E�B���h���J���̂�҂i��p�j�B
 */

ER
tcp_wait_swbuf_cs (T_TCP_CEP *cep, TMO tmout)
{
	FLGPTN	flag;
	SYSTIM	before, after;
	ER	error;
	int_t	win;


	/* ���M�E�B���h�o�b�t�@�������čς݂ŁA�󂫂�����ΏI������B*/
	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_READY &&
	    (cep->swbuf_count + IF_IP_TCP_HDR_SIZE) < net_buf_siz(cep->swbufq))
		return E_OK;

	/* ���M���ł���΁A�I������܂őҋ@����B*/
	while ((cep->flags & TCP_CEP_FLG_WBCS_MASK) != TCP_CEP_FLG_WBCS_FREE) {

		/* ���M�҂��̎��Ԃ� tmout ���猸����B*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR))
			syscall(get_tim(&before));

		if ((error = twai_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY,
		                      TWF_ORW, &flag, tmout)) != E_OK)
			return error;
		syscall(clr_flg(cep->snd_flgid, (FLGPTN)(~TCP_CEP_EVT_SWBUF_READY)));

		/* ���M�҂��̎��Ԃ� tmout ���猸����B*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR)) {
			syscall(get_tim(&after));
			if (after - before > tmout)
				return E_TMOUT;
			tmout -= (TMO)(after - before);
			}

		/*
		 *  ���M�ł��邩�ACEP �� FSM ��Ԃ�����B
		 *  ���M�E�C���h�o�b�t�@���󂭂܂ő҂ԂɁA���M�s�\�ɂȂ����ꍇ�́A
		 *  �R�l�N�V�������ؒf���ꂽ���Ƃ��Ӗ����Ă���B
		 */
		if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state))
			return E_CLS;
		}

	/* ����̎�M�E�B���h�����Ă���ꍇ�́A�J���܂őҋ@����B*/
	while (true) {

		/*
		 *  snd_wnd:  ����̎�M�\�E�B���h�T�C�Y
		 *  snd_cwnd: �t�s�E�B���h�T�C�Y
		 *
		 *  win: �ǂ��炩�������E�B���h�T�C�Y�ɐݒ肷��B
		 */
		win = cep->snd_wnd < cep->snd_cwnd ? cep->snd_wnd : cep->snd_cwnd;
		if (win > 0)
			break;

		/* �J���҂��̎��Ԃ� tmout ���猸����B*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR))
			syscall(get_tim(&before));

		if ((error = twai_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY,
		                      TWF_ORW, &flag, tmout)) != E_OK)
			return error;
		syscall(clr_flg(cep->snd_flgid, (FLGPTN)(~TCP_CEP_EVT_SWBUF_READY)));

		/* �J���҂��̎��Ԃ� tmout ���猸����B*/
		if (!(tmout == TMO_POL || tmout == TMO_FEVR)) {
			syscall(get_tim(&after));
			if (after - before > tmout)
				return E_TMOUT;
			tmout -= (TMO)(after - before);
			}

		/*
		 *  ���M�ł��邩�ACEP �� FSM ��Ԃ�����B
		 *  ���M�E�C���h�o�b�t�@���󂭂܂ő҂ԂɁA���M�s�\�ɂȂ����ꍇ�́A
		 *  �R�l�N�V�������ؒf���ꂽ���Ƃ��Ӗ����Ă���B
		 */
		if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state))
			return E_CLS;
		}

	/* �l�b�g���[�N�o�b�t�@���l������B*/
	if ((error = tcp_get_segment(&cep->swbufq, cep, 0,
	                             TCP_CFG_SWBUF_CSAVE_MIN_SIZE,
	                             TCP_CFG_SWBUF_CSAVE_MAX_SIZE - IF_IP_TCP_HDR_SIZE,
	                             NBA_SEARCH_DESCENT, tmout)) != E_OK)
		return error;

	/* ���M�E�B���h�o�b�t�@������������B*/
	tcp_init_swbuf(cep);

	return E_OK;
	}

/*
 *  tcp_get_swbuf_addr_cs -- ���M�E�B���h�o�b�t�@�̋󂫃A�h���X���l������i��p�j�B
 */

ER_UINT
tcp_get_swbuf_addr_cs (T_TCP_CEP *cep, void **p_buf)
{
	ER_UINT	error;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	if ((error = net_buf_siz(cep->swbufq)) > 0) {

		/*
		 *  +-----------+--------+---------+---------+
		 *  | Ehter HDR | IP HDR | TCP HDR | TCP SDU |
		 *  +-----------+--------+---------+---------+
		 *        14        20        20        n
		 *   <---------------- error --------------->
		 *              ^
		 *              net_buf �� 4 �I�N�e�b�g���E�ɃA���C������Ă���B
		 *
		 *  tcp_output �� ip_output �ŁA�`�F�b�N�T�����v�Z����Ƃ��A
		 *  n �� 4 �I�N�e�b�g���E�ɂȂ�悤�� SDU �̌��� 0 ��
		 *  �p�b�f�B���O����B���̕����l�����đ��M�E�B���h�o�b�t�@��
		 *  �󂫃T�C�Y�� 4 �I�N�e�b�g���E�ɒ�������B
		 */
		error = (uint_t)(((error - IF_IP_TCP_HDR_SIZE) >> 2 << 2) - cep->swbuf_count);

		/* ���M�E�C���h�T�C�Y�ɂ��T�C�Y�𒲐�����B*/
		if (error > cep->snd_wnd) 
			error = cep->snd_wnd;
		if (error > cep->snd_cwnd)
			error = cep->snd_cwnd;

		/* ����̍ő��M�Z�O�����g�T�C�Y (maxseg) �𒴂��Ȃ��悤�ɂ���B*/
		if (error > cep->maxseg) 
			error = cep->maxseg;

		/* ���M�E�B���h�o�b�t�@�̋󂫃f�[�^����ݒ肵�A���̒l��Ԃ��B*/
		cep->get_buf_len = error;

		/* ���M�E�B���h�o�b�t�@�̋󂫃A�h���X�̐擪��ݒ肷��B*/
		*p_buf = cep->sbuf_wptr;
		}

	else {	/* �l�b�g���[�N�o�b�t�@���s�� */

		/* ���M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		tcp_free_swbufq_cs(cep);
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_send_swbuf_cs -- ���M�E�B���h�o�b�t�@�̃f�[�^�𑗐M�\�ɂ���i��p�j�B
 */

void
tcp_send_swbuf_cs (T_TCP_CEP *cep, uint_t len)
{
	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	cep->sbuf_wptr  += len;
	cep->swbuf_count += len;

	/* �l�b�g���[�N�o�b�t�@���� IP �f�[�^�O��������ݒ肷��B*/
	cep->swbufq->len = (uint16_t)(cep->swbuf_count + IF_IP_TCP_HDR_SIZE);
	SET_IP_SDU_SIZE(GET_IP_HDR(cep->swbufq), len + TCP_HDR_SIZE);

	/* tcp_get_buf �̊����Ē������Z�b�g����B*/
	cep->get_buf_len = 0;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	/* �t���O���A���M�\�ɐݒ肵�A�����I�ɑ��M����B*/
	cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_SEND_READY
	                                               | TCP_CEP_FLG_FORCE
	                                               | TCP_CEP_FLG_FORCE_CLEAR
	                                               | TCP_CEP_FLG_POST_OUTPUT;
	}

/*
 *  tcp_free_swbufq_cs -- ���M�E�B���h�o�b�t�@�L���[�̉�����w������i��p�j�B
 *
 *    ����:
 *      �K�v�ł���΁A���̊֐����Ăяo���O�ɁA�ʐM�[�_�����b�N���A
 *      �߂�����A��������K�v������B
 */

void
tcp_free_swbufq_cs (T_TCP_CEP *cep)
{
	/* ���M�E�B���h�o�b�t�@�̋󂫑҂����������B*/
	cep->flags &= ~TCP_CEP_FLG_WBCS_NBUF_REQ;

	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) != TCP_CEP_FLG_WBCS_FREE) {
		/*
		 *  ���M�E�B���h�o�b�t�@���폜���邽�߂ɁA�t���O�� ACK �����ɐݒ肵�A
		 *  TCP �o�̓^�X�N���N������B
		 */
		cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_ACKED;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

/*
 *  tcp_alloc_swbuf_cs -- ���M�E�B���h�o�b�t�@�p�̃l�b�g���[�N�o�b�t�@�̊��蓖�Ă��w������i��p�j�B
 */

void
tcp_alloc_swbuf_cs (T_TCP_CEP *cep)
{
	cep->flags |= TCP_CEP_FLG_WBCS_NBUF_REQ;

	/*
	 *  ���M�E�B���h�o�b�t�@�����g�p�̏ꍇ�̂݁A
	 *  ���M�E�B���h�o�b�t�@�p�̃l�b�g���[�N�o�b�t�@�̊��蓖�Ă��w������B
	 */
	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_FREE)
		sig_sem(SEM_TCP_POST_OUTPUT);
	}

/*
 *  tcp_is_swbuf_full_cs -- ���M�E�B���h�o�b�t�@�����t���`�F�b�N����i��p�j�B
 */

bool_t
tcp_is_swbuf_full_cs (T_TCP_CEP *cep)
{
	return (cep->flags & TCP_CEP_FLG_WBCS_MASK) != TCP_CEP_FLG_WBCS_NBUF_READY ||
	        cep->swbuf_count >= cep->swbufq->len - IF_IP_TCP_HDR_SIZE;
	}

/*
 *  tcp_init_swbuf -- ���M�E�B���h�o�b�t�@������������i��p�j�B
 *
 *    ����: tcp_get_segment �Ńl�b�g���[�N�o�b�t�@���l������
 *          ����ɌĂяo�����ƁB
 */

void
tcp_init_swbuf (T_TCP_CEP *cep)
{
	/* ���M�E�C���h�o�b�t�@�̎g�p���T�C�Y�����Z�b�g����B*/
	cep->swbuf_count = 0;

	/* ���M�E�C���h�o�b�t�@�̃A�h���X��ݒ肷��B*/
	cep->sbuf_wptr = cep->sbuf_rptr = GET_TCP_SDU(cep->swbufq, IF_IP_TCP_HDR_OFFSET);

	/* �t���O���A�l�b�g���[�N�o�b�t�@�����čς݂ɐݒ肷��B*/
	cep->flags = (cep->flags & ~(TCP_CEP_FLG_WBCS_NBUF_REQ | TCP_CEP_FLG_WBCS_MASK))
	                         |   TCP_CEP_FLG_WBCS_NBUF_READY;
	}

/*
 *  tcp_push_res_nbuf -- �l�b�g���[�N�o�b�t�@��\�񂷂�i��p�j�B
 */

T_NET_BUF *
tcp_push_res_nbuf (T_NET_BUF *nbuf)
{
	static int_t last_ix = 0;

	T_TCP_CEP	*cep;
 	int_t		ix, sel_ix;

	if (++ last_ix == tmax_tcp_cepid)
		last_ix = 0;
	sel_ix = ix = last_ix;
	do {
		cep = &tcp_cep[ix];
		if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_PEND) {

			/* �l�b�g���[�N�o�b�t�@��\�񂷂�B*/
			cep->swbufq = nbuf;
			nbuf = NULL;

			/* �t���O��\��ɐݒ肷��B*/
			cep->flags = (cep->flags & ~TCP_CEP_FLG_WBCS_MASK) | TCP_CEP_FLG_WBCS_NBUF_RSVD;
			sel_ix = ix;
			break;
			}
		if (++ ix == tmax_tcp_cepid)
			ix = 0;
		} while (ix != last_ix);

	last_ix = sel_ix;

	return nbuf;
	}

/*
 *  tcp_pull_res_nbuf -- �\�񂵂Ă���l�b�g���[�N�o�b�t�@�Ԃ��i��p�j�B
 */

T_NET_BUF *
tcp_pull_res_nbuf (ATR nbatr)
{
	T_NET_BUF	*nbuf;
	T_TCP_CEP	*cep;

	cep = GET_TCP_CEP(nbatr & NBA_ID_MASK);
	if ((cep->flags & TCP_CEP_FLG_WBCS_MASK) == TCP_CEP_FLG_WBCS_NBUF_RSVD) {

		/* �\�񂵂Ă���l�b�g���[�N�o�b�t�@��Ԃ��B*/
		nbuf = cep->swbufq;
		cep->swbufq = NULL;

		/* TCP �o�̓^�X�N���N������B*/
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	else
		nbuf = NULL;

	return nbuf;
	}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

#ifdef TCP_CFG_RWBUF_CSAVE 

#ifndef TCP_CFG_RWBUF_CSAVE_ONLY

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���L���ȏꍇ
 *  �������A�ʐM�[�_�̎�M�E�B���h�o�b�t�@�icep->rbuf�j�̒l�ɂ��A
 *  TCP �ʐM�[�_���Ɏ�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���g�p���邩�A
 *  �g�p���Ȃ�����؂�ւ���B
 */

/*
 *  tcp_drop_rwbuf -- ��M�E�B���h�o�b�t�@�L���[�̍ŏ��̃l�b�g���[�N�o�b�t�@���������B
 */

void
tcp_drop_rwbuf (T_TCP_CEP *cep, uint_t len)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		tcp_drop_rwbuf_ncs(cep, len);
	else
		tcp_drop_rwbuf_cs(cep, len);
	}

/*
 *  tcp_read_rwbuf -- ��M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���ǂݏo���B
 */

uint_t
tcp_read_rwbuf (T_TCP_CEP *cep, void *data, uint_t len)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		return tcp_read_rwbuf_ncs(cep, data, len);
	else
		return tcp_read_rwbuf_cs(cep, data, len);
	}

/*
 *  tcp_get_rwbuf_addr -- ��M�E�B���h�o�b�t�@�̋󂫃A�h���X���l������B
 */

uint_t
tcp_get_rwbuf_addr (T_TCP_CEP *cep, void **p_buf)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		return tcp_get_rwbuf_addr_ncs(cep, p_buf);
	else
		return tcp_get_rwbuf_addr_cs(cep, p_buf);
	}

/*
 *  tcp_free_rwbufq -- ��M�E�B���h�o�b�t�@�L���[���������B
 */

void
tcp_free_rwbufq (T_TCP_CEP *cep)
{
	if (!IS_PTR_DEFINED(cep->rbuf))
		tcp_free_rwbufq_cs(cep);
	}

/*
 *  tcp_write_rwbuf -- ��M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB
 */

void
tcp_write_rwbuf (T_TCP_CEP *cep, T_NET_BUF *input, uint_t thoff)
{
	if (IS_PTR_DEFINED(cep->rbuf))
		tcp_write_rwbuf_ncs(cep, input, thoff);
	else
		tcp_write_rwbuf_cs(cep, input, thoff);
	}

#endif	/* of #ifndef TCP_CFG_RWBUF_CSAVE_ONLY */

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���L��
 */

/*
 *  tcp_drop_rwbuf -- ��M�E�B���h�o�b�t�@�L���[�̍ŏ��̃l�b�g���[�N�o�b�t�@���������B
 */

void
tcp_drop_rwbuf_cs (T_TCP_CEP *cep, uint_t len)
{
	T_TCP_Q_HDR	*qhdr;

	if (cep->rwbufq != NULL) {

		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);
		cep->rwbuf_count -= len;

		/* �l�b�g���[�N�o�b�t�@�Ƀf�[�^�������Ȃ�����������B*/
		if (len == qhdr->slen) {
			T_NET_BUF *next;

#ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES

			cep->rwbufq_entries --;

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES */

			next = qhdr->next;
			syscall(rel_net_buf(cep->rwbufq));
			cep->rwbufq = next;
			}
		else {
			qhdr->slen -= len;
			qhdr->soff += len;
			}
		}
	}

/*
 *  tcp_read_rwbuf -- ��M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���ǂݏo���B
 */

uint_t
tcp_read_rwbuf_cs (T_TCP_CEP *cep, void *data, uint_t len)
{
	T_TCP_Q_HDR	*qhdr;
	uint_t		blen, rlen = 0;
	uint8_t		*buf = (uint8_t*)data;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 *  ��M�E�B���h�o�b�t�@�L���[�Ƀl�b�g���[�N�o�b�t�@�������Ȃ邩
	 *  len �� 0 �ɂȂ�܂ő�����B
	 */
	while (cep->rwbufq != NULL && len > 0) {
		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);

		/*
		 *  len �Ǝ�M�E�B���h�o�b�t�@�L���[�̐擪�l�b�g���[�N�o�b�t�@��
		 *  �f�[�^���̏����������ڂ��f�[�^���ɂ���B
		 */
		if (len > qhdr->slen)
			blen = qhdr->slen;
		else
			blen = len;

		memcpy(buf,
		       GET_TCP_SDU(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff) + qhdr->soff,
		       (size_t)blen);

		/*
		 *  ��M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@��
		 *  �f�[�^�������Ȃ�����������B
		 */
		tcp_drop_rwbuf_cs(cep, blen);

		buf  += blen;
		rlen += blen;
		len  -= blen;
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return rlen;
	}

/*
 *  tcp_get_rwbuf_addr -- ��M�E�B���h�o�b�t�@�̋󂫃A�h���X���l������B
 */

uint_t
tcp_get_rwbuf_addr_cs (T_TCP_CEP *cep, void **p_buf)
{
	T_TCP_Q_HDR	*qhdr;
	uint_t		len;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	if (cep->rwbufq == NULL) {

		/* ��M�E�B���h�o�b�t�@���S�ĊJ������Ă���Ƃ��B*/
		*p_buf = NULL;
		len = 0;
		}
	else {

		/* ��M�E�B���h�o�b�t�@�̃f�[�^�̃A�h���X�̐擪��ݒ肷��B*/
		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);
		*p_buf = GET_TCP_SDU(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff) + qhdr->soff;

		/* ��M�E�B���h�o�b�t�@�̃f�[�^�����v�Z����B*/
		len = qhdr->slen;
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	/* ��M�E�B���h�o�b�t�@�̃f�[�^����ݒ肵�A���̒l��Ԃ��B*/
	cep->rcv_buf_len = len;
	return len;
	}

/*
 *  tcp_free_rwbufq -- ��M�E�B���h�o�b�t�@�L���[���������B
 *
 *    ����:
 *      �K�v�ł���΁A���̊֐����Ăяo���O�ɁA�ʐM�[�_�����b�N���A
 *      �߂�����A��������K�v������B
 */

void
tcp_free_rwbufq_cs (T_TCP_CEP *cep)
{
	T_NET_BUF *next;

	if (cep->rwbuf_count == 0 && cep->reassq == NULL) {
		while (cep->rwbufq != NULL) {
			next = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff)->next;

#ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES

			cep->rwbufq_entries --;

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES */

			syscall(rel_net_buf(cep->rwbufq));
			cep->rwbufq = next;
			}

		/* ��M�E�B���h�o�b�t�@�̎g�p���T�C�Y�����Z�b�g����B*/
		cep->rwbuf_count = 0;
		}
	}

/*
 *  tcp_write_rwbuf -- ��M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB
 *
 *    ����:
 *	���� input �́AT_TCP_Q_HDR �ɂ�胊���N����A
 *	���בւ����I�����Ă��Ȃ���΂Ȃ�Ȃ��B�܂��A
 *	�ǉ�����f�[�^�́A��M�E�B���h�o�b�t�@�Ɏ��܂邱�ƁB
 */

void
tcp_write_rwbuf_cs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t thoff)
{
	T_TCP_Q_HDR	*qhdr;
	T_NET_BUF	**nextp;
	uint_t		inlen, last;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	qhdr  = (T_TCP_Q_HDR*)GET_TCP_HDR(input, thoff);

	inlen = qhdr->slen;

#ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES

	if (cep->rwbufq_entries >= TCP_CFG_RWBUF_CSAVE_MAX_QUEUES &&
	    inlen > 0 && (qhdr->flags & TCP_FLG_FIN) == 0) {

		/*
		 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\�́A
		 *  ��M�E�B���h�o�b�t�@�L���[�̍ő�G���g�����𒴂���Ƃ��́A
		 *  ��M�����Z�O�����g��j������B
		 *  �������ASDU ���� 0 �̃Z�O�����g�� FIN �Z�O�����g�͔j�����Ȃ��B
		 *  �Ȃ��A����Ɏ�M�����Z�O�����g���j�����邽�߁A�đ��񐔂���������B
		 */
		syscall(rel_net_buf(input));

		/* �ʐM�[�_�̃��b�N����������B*/
		syscall(sig_sem(cep->semid_lock));
		return;
		}

	cep->rwbufq_entries ++;

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_MAX_QUEUES */

	qhdr  = (T_TCP_Q_HDR*)GET_TCP_HDR(input, thoff);

	/* ��M�ς݃V�[�P���X�ԍ����X�V����B*/
	cep->rcv_nxt += inlen;

	/* �ً}�f�[�^�� SDU �␳���s���B*/
	if (qhdr->urp > 0 && inlen > 0) {
		inlen      -= qhdr->urp;
		qhdr->slen -= qhdr->urp;
		qhdr->urp   = 0;
		}

	last  = cep->rwbuf_count;

	/* �l�b�g���[�N�o�b�t�@����M�E�B���h�o�b�t�@�L���[�̍Ō�ɘA������B*/
	qhdr->next = NULL;
	nextp = &cep->rwbufq;
	while (*nextp)
		nextp = &GET_TCP_Q_HDR(*nextp, GET_TCP_IP_Q_HDR(*nextp)->thoff)->next;
	*nextp = input;

	/*
	 *  FIN �t���O���t�����Z�O�����g�� inlen == 0 �ɂȂ邱�Ƃ�����B
	 *  ����́A�A�v���P�[�V�����ɁA���肩�炱��ȏ�f�[�^��������
	 *  ���Ȃ����Ƃ�m�点�邽�߂ł���B
	 */
	if (inlen > 0) {
		cep->rwbuf_count += inlen;
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_SEGS],   1);
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_OCTETS], inlen);
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

#ifdef TCP_CFG_NON_BLOCKING

	if (cep->rcv_nblk_tfn == TFN_TCP_RCV_BUF) {	/* �m���u���b�L���O�R�[�� */

		int_t	len;

		qhdr = GET_TCP_Q_HDR(cep->rwbufq, GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff);
		len = qhdr->slen;

		/*
		 *  FIN �t���O���t�����Z�O�����g�� inlen == 0 �ɂȂ邱�Ƃ�����B
		 *  ����́A�A�v���P�[�V�����ɁA���肩�炱��ȏ�f�[�^��������
		 *  ���Ȃ����Ƃ�m�点�邽�߂ł���B
		 */
		if (len > 0 || inlen == 0) {

			/* tcp_rcv_buf �̊����Ē���ݒ肷��B*/
			cep->rcv_buf_len = len;

			/* ��M�E�B���h�o�b�t�@�̃A�h���X��Ԃ��B*/
			*cep->rcv_p_buf = GET_TCP_SDU(cep->rwbufq,
			                  GET_TCP_IP_Q_HDR(cep->rwbufq)->thoff) + qhdr->soff;

			if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

			if (len == 0) {

				/*
				 *  �ʐM�[�_�����b�N���āA
				 *  ��M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B
				 */
				syscall(wai_sem(cep->semid_lock));
				tcp_free_rwbufq_cs(cep);
				syscall(sig_sem(cep->semid_lock));
				}
			}

		/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
		}

	else if (cep->rcv_nblk_tfn == TFN_TCP_RCV_DAT) {	/* �m���u���b�L���O�R�[�� */
		int_t	len;

		/* ��M�E�B���h�o�b�t�@����f�[�^�����o���B*/
		if ((len = tcp_read_rwbuf_cs(cep, cep->rcv_data, (uint_t)cep->rcv_len)) > 0) {
			/* ����ɃE�B���h�E�T�C�Y���ς�������Ƃ�m�点�邽�ߏo�͂��|�X�g����B*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}

		/*
		 *  FIN �t���O���t�����Z�O�����g�� inlen == 0 �ɂȂ邱�Ƃ�����B
		 *  ����́A�A�v���P�[�V�����ɁA���肩�炱��ȏ�f�[�^��������
		 *  ���Ȃ����Ƃ�m�点�邽�߂ł���B
		 */
		if (len > 0 || inlen == 0) {

			if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));
			}

		/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		if (inlen == 0 && cep->rwbuf_count == 0) {
			/*
			 *  ��M�E�B���h�o�b�t�@���̃f�[�^���� 0 �ŁA
			 *  ���肩�� FIN �t���O���t�����Z�O�����g����M�����Ƃ��́A
			 *  �ʐM�[�_�����b�N���āA
			 *  ��M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B
			 */
			syscall(wai_sem(cep->semid_lock));
			tcp_free_rwbufq_cs(cep);
			syscall(sig_sem(cep->semid_lock));
			}

		/*
		 *  ��M�E�B���h�o�b�t�@�Ƀf�[�^�����邩�A inlen == 0 �̎��A���̓^�X�N���N������B
		 *  FIN �t���O���t�����Z�O�����g�� inlen == 0 �ɂȂ邱�Ƃ�����B
		 *  ����́A�A�v���P�[�V�����ɁA���肩�炱��ȏ�f�[�^��������
		 *  ���Ȃ����Ƃ�m�点�邽�߂ł���B
		 */
		if ((last == 0 && cep->rwbuf_count > 0) || inlen == 0) {
			syscall(set_flg(cep->rcv_flgid, TCP_CEP_EVT_RWBUF_READY));
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	}

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#endif	/* of #ifdef SUPPORT_TCP */
