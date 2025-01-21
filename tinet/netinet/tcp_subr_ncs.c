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
 *  @(#) $Id: tcp_subr_ncs.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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

#ifndef TCP_CFG_SWBUF_CSAVE_ONLY

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\������
 */

/*
 *  tcp_read_swbuf -- ���M�E�B���h�o�b�t�@����f�[�^��ǂݏo���B
 */

void
tcp_read_swbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff)
{
	uint8_t	*wptr, *rptr;

	/* SDU �̑傫�����`�F�b�N����B*/
	if (GET_IP_SDU_SIZE(GET_IP_HDR(output)) < GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET) + len) {
		syslog(LOG_INFO, "[TCP] shrink SUD len: %d -> %d",
		       (uint16_t)len, (uint16_t)(GET_IP_SDU_SIZE(GET_IP_HDR(output)) - GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET)));
		len = GET_IP_SDU_SIZE(GET_IP_HDR(output)) - GET_TCP_HDR_SIZE2(output, IF_IP_TCP_HDR_OFFSET);
		}

	wptr = GET_TCP_SDU(output, IF_IP_TCP_HDR_OFFSET);

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	rptr = cep->sbuf_rptr + doff;
	if (rptr - (uint8_t*)cep->sbuf > cep->sbufsz) {

		/* �]���J�n�����M�E�B���h�o�b�t�@�̏I���𒴂���Ƃ��̏����@*/
		rptr = (uint8_t*)cep->sbuf_rptr - (cep->sbufsz - doff);
		}
	else if (len + (rptr - (uint8_t*)cep->sbuf) > cep->sbufsz) {
		uint_t sub;

		/* �]���͈͂����E���h����Ƃ��̏��� */
		sub = (uint_t)(cep->sbufsz - (rptr - (uint8_t*)cep->sbuf));
		memcpy((void*)wptr, rptr, (size_t)sub);
		len  -= sub;
		wptr += sub;
		rptr  = (uint8_t*)cep->sbuf;
		}
	memcpy((void*)wptr, rptr, (size_t)len);

	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_DATA_SEGS],   1);
	NET_COUNT_TCP(net_count_tcp[NC_TCP_SEND_DATA_OCTETS], len);

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));
	}

/*
 *  tcp_drop_swbuf -- ���M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���폜����B
 */

void
tcp_drop_swbuf_ncs (T_TCP_CEP *cep, uint_t len)
{
	uint_t	last;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	last = cep->swbuf_count;

	if (cep->sbuf_rptr + len > (uint8_t*)cep->sbuf + cep->sbufsz)
		/* ���E���h����Ƃ��̌v�Z */
		cep->sbuf_rptr -= cep->sbufsz - len;
	else
		cep->sbuf_rptr += len;
	cep->swbuf_count -= (uint16_t)len;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

#ifdef TCP_CFG_NON_BLOCKING

	if (cep->snd_nblk_tfn == TFN_TCP_GET_BUF) {	/* �m���u���b�L���O�R�[�� */

		/* �ʐM�[�_�����b�N����B*/
		syscall(wai_sem(cep->semid_lock));

		/* ���M�f�[�^�����v�Z����B*/
		if (cep->sbufsz - cep->swbuf_count > cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf))
			/* �����݃|�C���^�����E���h����Ƃ��́A�����݃|�C���^���瑗�M�E�B���h�o�b�t�@�̏I���܂� */
			len = (uint_t)(cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf));
		else
			len = cep->sbufsz - cep->swbuf_count;

		/* �ʐM�[�_�̃��b�N����������B*/
		syscall(sig_sem(cep->semid_lock));

		if (len > 0) {

			/* tcp_get_buf �̊����Ē���ݒ肷��B*/
			cep->get_buf_len = len;

			/* ���M�E�B���h�o�b�t�@�̃A�h���X��Ԃ��B*/
			*cep->snd_p_buf = cep->sbuf_wptr;

			if (IS_PTR_DEFINED(cep->callback))
#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			else
				syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

			/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
			cep->snd_tskid = TA_NULL;
			cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
			}
		}

#ifdef TCP_CFG_EXTENTIONS

	else if (cep->snd_nblk_tfn == TFN_TCP_SND_DAT ||
	         cep->snd_nblk_tfn == TFN_TCP_SND_OOB) {	/* �m���u���b�L���O�R�[�� */

#else	/* of #ifdef TCP_CFG_EXTENTIONS */

	else if (cep->snd_nblk_tfn == TFN_TCP_SND_DAT) {	/* �m���u���b�L���O�R�[�� */

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		ER_UINT	error;

	 	/* ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB*/
		error = TCP_WRITE_SWBUF(cep, cep->snd_data, (uint_t)cep->snd_len);

#ifdef TCP_CFG_EXTENTIONS

		/* ���M�ً}�|�C���^��ݒ肷��B*/
	        if (cep->snd_nblk_tfn == TFN_TCP_SND_OOB)
			cep->snd_up = cep->snd_una + error;

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

		if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		else
			syslog(LOG_WARNING, "[TCP] no call back, CEP: %d.", GET_TCP_CEPID(cep));

		/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
		cep->snd_tskid = TA_NULL;
		cep->snd_tfn   = cep->snd_nblk_tfn = TFN_TCP_UNDEF;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* ���M�E�B���h�o�b�t�@�ɋ󂫂��o������o�̓^�X�N���N������B*/
		if (last == cep->sbufsz && cep->swbuf_count < cep->sbufsz)
			syscall(set_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY));

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	if (cep->swbuf_count > 0) {
		/* ���M�E�B���h�o�b�t�@�Ƀf�[�^������Ώo�͂��|�X�g����B*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}
	}

/*
 *  tcp_write_swbuf -- ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB
 */

ER_UINT
tcp_write_swbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len)
{
	uint_t	offset;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/* len �Ƒ��M�E�B���h�o�b�t�@�̋󂫂̏����������ڂ��f�[�^���ɂ���B*/
	if (len > (cep->sbufsz - cep->swbuf_count))
		len = cep->sbufsz - cep->swbuf_count;

	/* �������݃|�C���^�����E���h����Ƃ��̏��� */
	if (len > cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf)) {
		offset = (uint_t)(cep->sbufsz - (cep->sbuf_wptr -(uint8_t*)cep->sbuf));
		memcpy(cep->sbuf_wptr, data, (size_t)offset);
		cep->sbuf_wptr  = (uint8_t*)cep->sbuf;
		cep->swbuf_count += offset;
		}
	else
		offset = 0;

	memcpy(cep->sbuf_wptr, (void*)((uint8_t*)data + offset), (size_t)(len - offset));
	cep->sbuf_wptr  += len - offset;
	cep->swbuf_count += len - offset;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return (ER_UINT)len;
	}

/*
 *  tcp_wait_swbuf -- ���M�E�B���h�o�b�t�@���󂭂̂�҂B
 */

ER
tcp_wait_swbuf_ncs (T_TCP_CEP *cep, TMO tmout)
{
	ER	error;
	FLGPTN	flag;

	while (cep->swbuf_count >= cep->sbufsz) {
		/*
		 *  ���M�E�B���h�o�b�t�@�̋󂫂��Ȃ���΁A�o�͂��|�X�g���āA
		 *  ���M�E�B���h�o�b�t�@���󂭂܂ő҂B
		 */
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);

		if ((error = twai_flg(cep->snd_flgid, TCP_CEP_EVT_SWBUF_READY, TWF_ORW, &flag, tmout)) != E_OK) {
			return error;
			}
		syscall(clr_flg(cep->snd_flgid, (FLGPTN)(~TCP_CEP_EVT_SWBUF_READY)));

		/*
		 *  ���M�ł��邩�ACEP �� FSM ��Ԃ�����B
		 *  ���M�E�B���h�o�b�t�@���󂭂܂ő҂ԂɁA���M�s�\�ɂȂ����ꍇ�́A
		 *  �R�l�N�V�������ؒf���ꂽ���Ƃ��Ӗ����Ă���B
		 */
		if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state)) {
			return E_CLS;
			}
		}

	return E_OK;
	}
/*
 *  tcp_get_swbuf_addr -- ���M�E�B���h�o�b�t�@�̋󂫃A�h���X���l������B
 */

ER_UINT
tcp_get_swbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf)
{
	uint_t	len;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/* ���M�E�B���h�o�b�t�@�̋󂫃A�h���X�̐擪��ݒ肷��B*/
	*p_buf = cep->sbuf_wptr;

	/* ���M�E�B���h�o�b�t�@�̋󂫃T�C�Y���v�Z����B*/
	if (cep->sbufsz - cep->swbuf_count > cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf))
		/* �����݃|�C���^�����E���h����Ƃ��́A�����݃|�C���^���瑗�M�E�B���h�o�b�t�@�̏I���܂� */
		len = (uint_t)(cep->sbufsz - (cep->sbuf_wptr - (uint8_t*)cep->sbuf));
	else
		len = cep->sbufsz - cep->swbuf_count;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	/* ���M�E�B���h�o�b�t�@�̋󂫃f�[�^����ݒ肵�A���̒l��Ԃ��B*/
	cep->get_buf_len = len;
	return (ER_UINT)len;
	}

/*
 *  tcp_send_swbuf -- ���M�E�B���h�o�b�t�@�̃f�[�^�𑗐M�\�ɂ���B
 */

void
tcp_send_swbuf_ncs (T_TCP_CEP *cep, uint_t len)
{
	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	cep->sbuf_wptr  += len;
	cep->swbuf_count += len;

	/* �����݃|�C���^�����E���h����Ƃ��̏��� */
	if (cep->sbuf_wptr >= (uint8_t*)cep->sbuf + cep->sbufsz)
		cep->sbuf_wptr  = (uint8_t*)cep->sbuf;

	/* tcp_get_buf �̊����Ē������Z�b�g����B*/
	cep->get_buf_len = 0;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	/* ���M�E�B���h�o�b�t�@���t���̂Ƃ��͋����I�ɑ��M����B*/
	if (cep->swbuf_count >= cep->sbufsz)
		cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR;
	}

/*
 *  tcp_is_swbuf_full -- ���M�E�B���h�o�b�t�@�����t���`�F�b�N����B
 */

bool_t
tcp_is_swbuf_full_ncs (T_TCP_CEP *cep)
{
	return cep->swbuf_count >= cep->sbufsz;
	}

#endif	/* of #ifndef TCP_CFG_SWBUF_CSAVE_ONLY */

#ifndef TCP_CFG_RWBUF_CSAVE_ONLY

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\������
 */

/*
 *  tcp_drop_rwbuf -- ��M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���폜����B
 */

void
tcp_drop_rwbuf_ncs (T_TCP_CEP *cep, uint_t len)
{
	cep->rwbuf_count -= len;
	cep->rbuf_rptr  += len;

	/* �ǂݏo���|�C���^�����E���h����Ƃ��̏��� */
	if (cep->rbuf_rptr >= (uint8_t*)cep->rbuf + cep->rbufsz)
		cep->rbuf_rptr  = (uint8_t*)cep->rbuf;
	}

/*
 *  tcp_read_rwbuf -- ��M�E�B���h�o�b�t�@����w�肳�ꂽ�I�N�e�b�g���ǂݏo���B
 */

uint_t
tcp_read_rwbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len)
{
	uint_t	offset;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/* len �Ǝ�M�E�B���h�o�b�t�@�̃f�[�^���̏������������o���f�[�^���ɂ���B*/
	if (len > cep->rwbuf_count)
		len = cep->rwbuf_count;

	/* �ǂݏo���|�C���^�����E���h����Ƃ��̏��� */
	if (len > cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf)) {
		offset = (uint_t)(cep->rbufsz - (cep->rbuf_rptr -(uint8_t*)cep->rbuf));
		memcpy(data, cep->rbuf_rptr, (size_t)offset);
		cep->rwbuf_count -= offset;
		cep->rbuf_rptr   = (uint8_t*)cep->rbuf;
		}
	else
		offset = 0;

	memcpy((void*)((uint8_t*)data + offset), cep->rbuf_rptr, (size_t)(len - offset));
	cep->rwbuf_count -= len - offset;
	cep->rbuf_rptr  += len - offset;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return len;
	}

/*
 *  tcp_get_rwbuf_addr -- ��M�E�B���h�o�b�t�@�̋󂫃A�h���X���l������B
 */

uint_t
tcp_get_rwbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf)
{
	uint_t	len;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/* ��M�E�B���h�o�b�t�@�̃f�[�^�����v�Z����B*/
	if (cep->rwbuf_count > cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf))
		/* �|�C���^�����E���h����Ƃ��͎�M�E�B���h�o�b�t�@�̏I���܂� */
		len = (uint_t)(cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf));
	else
		len = cep->rwbuf_count;

	/* ��M�E�B���h�o�b�t�@�̃f�[�^�̃A�h���X�̐擪��ݒ肷��B*/
	*p_buf = cep->rbuf_rptr;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	/* ��M�E�B���h�o�b�t�@�̃f�[�^����ݒ肵�A���̒l��Ԃ��B*/
	cep->rcv_buf_len = len;
	return len;
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
tcp_write_rwbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t thoff)
{
	T_TCP_Q_HDR	*qhdr;
	uint_t		offset, inlen, last;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	qhdr  = (T_TCP_Q_HDR*)GET_TCP_HDR(input, thoff);

	/* ��M�ς݃V�[�P���X�ԍ����X�V����B*/
	cep->rcv_nxt += qhdr->slen;

	last  = cep->rwbuf_count;
	inlen = qhdr->slen;

	/* �ً}�f�[�^�� SDU �␳���s���B*/
	if (qhdr->urp > 0 && inlen > 0) {
		inlen      -= qhdr->urp;
		qhdr->slen -= qhdr->urp;
		qhdr->urp   = 0;
		}

	/*
	 *  FIN �t���O���t�����Z�O�����g�� inlen == 0 �ɂȂ邱�Ƃ�����B
	 *  ����́A�A�v���P�[�V�����ɁA���肩�炱��ȏ�f�[�^��������
	 *  ���Ȃ����Ƃ�m�点�邽�߂ł���B
	 */
	if (inlen > 0) {

		/* �������݃|�C���^�����E���h����Ƃ��̏��� */
		if (inlen > cep->rbufsz - (cep->rbuf_wptr - (uint8_t*)cep->rbuf)) {
			offset = (uint_t)(cep->rbufsz - (cep->rbuf_wptr - (uint8_t*)cep->rbuf));
			memcpy(cep->rbuf_wptr, (void*)(GET_TCP_SDU(input, thoff) + qhdr->soff), (size_t)offset);
			cep->rbuf_wptr   = (uint8_t*)cep->rbuf;
			cep->rwbuf_count += offset;
			inlen           -= offset;
			}
		else
			offset	= 0;

		memcpy(cep->rbuf_wptr, (void*)(GET_TCP_SDU(input, thoff) + qhdr->soff + offset), (size_t)inlen);
		cep->rbuf_wptr  += inlen;
		cep->rwbuf_count += inlen;

		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_SEGS],   1);
		NET_COUNT_TCP(net_count_tcp[NC_TCP_RECV_DATA_OCTETS], inlen);
		}

	syscall(rel_net_buf(input));

#ifdef TCP_CFG_NON_BLOCKING

	if (cep->rcv_nblk_tfn == TFN_TCP_RCV_BUF) {	/* �m���u���b�L���O�R�[�� */

		int_t	len;

		/* ��M�E�B���h�o�b�t�@�̋󂫃f�[�^�����v�Z����B*/
		if (cep->rwbuf_count > cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf)) {
			/* �|�C���^�����E���h����Ƃ��͎�M�E�B���h�o�b�t�@�̏I���܂� */
			len = (uint_t)(cep->rbufsz - (cep->rbuf_rptr - (uint8_t*)cep->rbuf));
			}
		else
			len = cep->rwbuf_count;

		/* �ʐM�[�_�̃��b�N����������B*/
		syscall(sig_sem(cep->semid_lock));

		/*
		 *  FIN �t���O���t�����Z�O�����g�� inlen == 0 �ɂȂ邱�Ƃ�����B
		 *  ����́A�A�v���P�[�V�����ɁA���肩�炱��ȏ�f�[�^��������
		 *  ���Ȃ����Ƃ�m�点�邽�߂ł���B
		 */
		if (len > 0 || inlen == 0) {

			/* tcp_rcv_buf �̊����Ē���ݒ肷��B*/
			cep->rcv_buf_len = len;

			/* ��M�E�B���h�o�b�t�@�̃A�h���X��Ԃ��B*/
			*cep->rcv_p_buf = cep->rbuf_rptr;


			if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)(uint32_t)len);

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
				TCP_FREE_RWBUFQ(cep);
				syscall(sig_sem(cep->semid_lock));
				}
			}

		/* �L������Ă���^�X�N ID �� API �@�\�R�[�h���N���A�[����B*/
		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
		}

	else if (cep->rcv_nblk_tfn == TFN_TCP_RCV_DAT) {	/* �m���u���b�L���O�R�[�� */
		ER_UINT	len;

		/* �ʐM�[�_�̃��b�N����������B*/
		syscall(sig_sem(cep->semid_lock));

		/* ��M�E�B���h�o�b�t�@����f�[�^�����o���B*/
		if ((len = TCP_READ_RWBUF(cep, cep->rcv_data, (uint_t)cep->rcv_len)) > 0) {
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

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)(uint32_t)len);

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

		/* �ʐM�[�_�̃��b�N����������B*/
		syscall(sig_sem(cep->semid_lock));

		if (inlen == 0 && cep->rwbuf_count == 0) {
			/*
			 *  ��M�E�B���h�o�b�t�@���̃f�[�^���� 0 �ŁA
			 *  ���肩�� FIN �t���O���t�����Z�O�����g����M�����Ƃ��́A
			 *  �ʐM�[�_�����b�N���āA
			 *  ��M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B
			 */
			syscall(wai_sem(cep->semid_lock));
			TCP_FREE_RWBUFQ(cep);
			syscall(sig_sem(cep->semid_lock));
			}

		/*
		 *  ��M�E�B���h�o�b�t�@�Ƀf�[�^�����邩�A inlen == 0 �̎��A���̓^�X�N���N������B
		 *  FIN �t���O���t�����Z�O�����g�� inlen == 0 �ɂȂ邱�Ƃ�����B
		 *  ����́A�A�v���P�[�V�����ɁA���肩�炱��ȏ�f�[�^��������
		 *  ���Ȃ����Ƃ�m�点�邽�߂ł���B
		 */
		if ((last == 0 && cep->rwbuf_count > 0) || inlen == 0)
			syscall(set_flg(cep->rcv_flgid, TCP_CEP_EVT_RWBUF_READY));

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	}

#endif	/* of #ifndef TCP_CFG_RWBUF_CSAVE_ONLY */

#endif	/* of #ifdef SUPPORT_TCP */
