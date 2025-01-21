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
 *  @(#) $Id: tcp_usrreq.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	From: @(#)tcp_usrreq.c	8.2 (Berkeley) 1/3/94
 * $FreeBSD: src/sys/netinet/tcp_usrreq.c,v 1.40.2.3 1999/08/29 16:29:57 peter Exp $
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
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>

#include <net/if_var.h>

#ifdef SUPPORT_TCP

/*
 *  IPv4 �� IPv6 �̐؂�ւ��}�N��
 */

#if defined(SUPPORT_INET4)

#define TCP_CRE_REP	tcp_cre_rep
#define TCP_ACP_CEP	tcp_acp_cep
#define TCP_CON_CEP	tcp_con_cep

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_CRE_REP	tcp6_cre_rep
#define TCP_ACP_CEP	tcp6_acp_cep
#define TCP_CON_CEP	tcp6_con_cep

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  TINET �����C�u���������Ȃ��ꍇ�́A�S�Ă̋@�\��
 *  �I�u�W�F�N�g�t�@�C���ɏo�͂��邽�߁A�}�N����L���ɂ���B
 */

#ifndef TCP_CFG_LIBRARY

#define __tcp_cre_rep
#define __tcp_del_rep
#define __tcp_cre_cep
#define __tcp_del_cep
#define __tcp_acp_cep
#define __tcp_con_cep
#define __tcp_sht_cep
#define __tcp_cls_cep
#define __tcp_snd_dat
#define __tcp_rcv_dat
#define __tcp_snd_oob
#define __tcp_rcv_oob
#define __tcp_get_buf
#define __tcp_snd_buf
#define __tcp_rcv_buf
#define __tcp_rel_buf
#define __tcp_can_cep
#define __tcp_set_opt
#define __tcp_get_opt

#endif	/* of #ifndef TCP_CFG_LIBRARY */

/*
 *  tcp_cre_rep -- TCP ��t���̐����y�g���@�\�z
 */

#ifdef __tcp_cre_rep

#ifdef TCP_CFG_EXTENTIONS

ER
TCP_CRE_REP (ID repid, T_TCP_CREP *pk_crep)
{
	T_TCP_REP	*rep;
	ER		error;

	/* TCP ��t�� ID ���`�F�b�N����B*/
	if (!VAID_TCP_REPID(repid))
		return E_ID;

	/* pk_crep �� NULL �Ȃ�G���[ */
	if (pk_crep == NULL)
		return E_PAR;

	/* TCP ��t���𓾂�B*/
	rep = GET_TCP_REP(repid);

	/* TCP ��t�����A���I�����p�łȂ���΃G���[ */
	if (!DYNAMIC_TCP_REP(rep))
		return E_ID;

	/* ��t�������b�N����B*/
	syscall(wai_sem(rep->semid_lock));

	/*
	 * TCP ��t�����`�F�b�N����B�����ς݂ł���΃G���[
	 */
	if (VALID_TCP_REP(rep))
		error = E_OBJ;
	else {

		/* TCP ��t�����������R�s�[����B*/
		rep->repatr = pk_crep->repatr;		/* ��t������		*/
		rep->myaddr = pk_crep->myaddr;		/* �����̃A�h���X	*/

		/* TCP ��t���𐶐��ς݂ɂ���B*/
		rep->flags |= TCP_REP_FLG_VALID;
		error = E_OK;
		}

	/* ��t���̃��b�N����������B*/
	syscall(sig_sem(rep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_cre_cep */

#ifdef __tcp_del_rep

#ifdef TCP_CFG_EXTENTIONS

/*
 *  tcp_find_cep_rep -- TCP ��t���������N���Ă��� TCP �ʐM�[�_�𓾂�B
 */

static T_TCP_CEP*
tcp_find_cep_rep (T_TCP_REP* rep)
{
	T_TCP_CEP*	cep;

	for (cep = &tcp_cep[tmax_tcp_cepid]; cep -- != tcp_cep; ) {
		if (cep->rep == rep)
			return cep;
		}

	return NULL;
	}

/*
 *  tcp_del_rep -- TCP ��t���̍폜�y�g���@�\�z
 */


ER
tcp_del_rep (ID repid)
{
	T_TCP_CEP	*cep;
	T_TCP_REP	*rep;
	ER		error = E_OK;

	/* TCP ��t�� ID ���`�F�b�N����B*/
	if (!VAID_TCP_REPID(repid))
		return E_ID;

	/* TCP ��t���𓾂�B*/
	rep = GET_TCP_REP(repid);

	/* TCP ��t�����A���I�����p�łȂ���΃G���[ */
	if (!DYNAMIC_TCP_REP(rep))
		return E_ID;

	/* ��t�������b�N����B*/
	syscall(wai_sem(rep->semid_lock));

	/* TCP ��t�����`�F�b�N����B�������̏ꍇ�̓G���[ */
	if (!VALID_TCP_REP(rep))
		error = E_NOEXS;
	else {
		if ((cep = tcp_find_cep_rep(rep)) != NULL) {
			/*
			 * ���łɎ󓮃I�[�v�����Ă���Ƃ�
			 *�itcp_acp_cep ���Ă΂�Ă���Ƃ��j�́A
			 * tcp_acp_cep ���I��������B
			 */

			/* �ʐM�[�_�����b�N����B*/
			syscall(wai_sem(cep->semid_lock));

			/*
			 *  �ʐM�[�_�����t����������A
			 *  �C�x���g�t���O���N���[�Y�ɐݒ肷��B
			 */
			cep->rep = NULL;
			cep->fsm_state = TCP_FSM_CLOSED;
			cep->error = E_DLT;
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));

#ifdef TCP_CFG_NON_BLOCKING

			if (cep->rcv_nblk_tfn != TFN_TCP_UNDEF) {
				if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)E_DLT);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					ER	error = E_DLT;

					(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

					}
				else
					error = E_OBJ;
				cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
				}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			cep->rcv_tskid = TA_NULL;
			cep->rcv_tfn   = TFN_TCP_UNDEF;

			/* �ʐM�[�_�̃��b�N����������B*/
			syscall(sig_sem(cep->semid_lock));

			}
		else
			error = E_OK;

		/* TCP ��t���𖢐����ɂ���B*/
		rep->flags &= ~TCP_REP_FLG_VALID;
		}

	/* ��t���̃��b�N����������B*/
	syscall(sig_sem(rep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_del_rep */

/*
 *  tcp_cre_cep -- TCP �ʐM�[�_�̐����y�g���@�\�z
 */

#ifdef __tcp_cre_cep

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_cre_cep (ID cepid, T_TCP_CCEP *pk_ccep)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* TCP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* pk_ccep �� NULL �Ȃ�G���[ */
	if (pk_ccep == NULL)
		return E_PAR;

	/* TCP �ʐM�[�_�𓾂�B*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �ʐM�[�_���A���I�����p�łȂ���΃G���[ */
	if (!DYNAMIC_TCP_CEP(cep))
		return E_ID;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 * TCP �ʐM�[�_���`�F�b�N����B�����ς݂ł���΃G���[
	 */
	if (VALID_TCP_CEP(cep))
		error = E_OBJ;
	else {

		/* TCP �ʐM�[�_���������R�s�[����B*/
		cep->cepatr   = pk_ccep->cepatr;		/* �ʐM�[�_����			*/
		cep->sbuf     = pk_ccep->sbuf;			/* ���M�p�E�B���h�o�b�t�@	*/
		cep->sbufsz   = pk_ccep->sbufsz;		/* ���M�p�E�B���h�o�b�t�@�T�C�Y	*/
		cep->rbuf     = pk_ccep->rbuf;			/* ��M�p�E�B���h�o�b�t�@	*/
		cep->rbufsz   = pk_ccep->rbufsz;		/* ��M�p�E�B���h�o�b�t�@�T�C�Y	*/
		cep->callback = (void*)pk_ccep->callback;	/* �R�[���o�b�N			*/

		/* TCP �ʐM�[�_�𐶐��ς݂ɂ���B*/
		cep->flags |= TCP_CEP_FLG_VALID;
		error = E_OK;
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_cre_cep */

/*
 *  tcp_del_cep -- TCP �ʐM�[�_�̍폜�y�g���@�\�z
 */

#ifdef __tcp_del_cep

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_del_cep (ID cepid)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* TCP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �ʐM�[�_�𓾂�B*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �ʐM�[�_���A���I�����p�łȂ���΃G���[ */
	if (!DYNAMIC_TCP_CEP(cep))
		return E_ID;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 * TCP �ʐM�[�_���`�F�b�N����B�ȉ��̏ꍇ�̓G���[
	 * �E�������B
	 * �E�g�p���B
	 */
	if (!VALID_TCP_CEP(cep))
		error = E_NOEXS;
	else if (cep->fsm_state != TCP_FSM_CLOSED)
		error = E_OBJ;
	else {

		/* TCP �ʐM�[�_�𖢐����ɂ���B*/
		cep->flags &= ~TCP_CEP_FLG_VALID;
		error = E_OK;
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_del_cep */

#ifdef TCP_CFG_PASSIVE_OPEN

/*
 *  tcp_acp_cep -- �ڑ��v���҂� (�󓮃I�[�v��)�y�W���@�\�z
 */

#ifdef __tcp_acp_cep

ER
TCP_ACP_CEP (ID cepid, ID repid, T_IPEP *p_dstaddr, TMO tmout)
{
	T_TCP_REP	*rep;
	T_TCP_CEP	*cep;
	ER		error;
	FLGPTN		flag;

	/* TCP ��t�����`�F�b�N����B*/
	if (!VAID_TCP_REPID(repid))
		return E_ID;

#ifdef TCP_CFG_NON_BLOCKING

	/* p_dstaddr �� NULL �Ȃ�G���[ */
	if (p_dstaddr == NULL)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* p_dstaddr �� NULL ���Atmout �� TMO_NBLK �Ȃ�G���[ */
	if (p_dstaddr == NULL || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_ACP_CEP)) != E_OK)
		return error;

	/* CEP �� FSM ���N���[�Y��ԂłȂ���΃G���[�B*/
	if (cep->fsm_state != TCP_FSM_CLOSED) {
		error = E_OBJ;
		goto err_ret;
		}
	syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_CLOSED)));

	/* TCP �ʐM�[�_������������B*/
	tcp_init_cep(cep);

	/* TCP ��t���𓾂�B*/
	rep = GET_TCP_REP(repid);

#ifdef TCP_CFG_EXTENTIONS

	/* TCP ��t�������b�N����B*/
	syscall(wai_sem(rep->semid_lock));

	/* TCP ��t�����`�F�b�N����B*/
	if (!VALID_TCP_REP(rep)) {
		syscall(sig_sem(rep->semid_lock));
		error = E_NOEXS;
		goto err_ret;
		}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	/* TCP �ʐM�[�_��TCP��t�����L�^����B*/
	cep->rep = rep;

#ifdef TCP_CFG_EXTENTIONS

	/* TCP ��t���̃��b�N����������B*/
	syscall(sig_sem(rep->semid_lock));

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	/* TCP ��t���̃A�h���X���R�s�[����B*/
	cep->myaddr = rep->myaddr;

	/* �ʐM�[�_��ݒ肷��B*/
	cep->fsm_state = TCP_FSM_LISTEN;

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {
		/* �m���u���b�L���O�R�[�� */
		cep->p_dstaddr    = p_dstaddr;
		cep->rcv_nblk_tfn = TFN_TCP_ACP_CEP;
		return E_WBLK;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/*
		 *  FSM �� ESTABLISHED �ɂȂ�܂ő҂B
		 *  FSM �� CLOSED �ɂȂ����ꍇ�́A�G���[�������������Ƃ��Ӗ����Ă���B
		 */
		error = twai_flg(cep->est_flgid, (TCP_CEP_EVT_CLOSED |
		                                  TCP_CEP_EVT_ESTABLISHED), TWF_ORW, &flag, tmout);
		if (error == E_OK) {
			if (cep->error != E_OK)
				error = cep->error;
			else if (cep->fsm_state == TCP_FSM_CLOSED)
				error = E_TMOUT;
			}

		syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_ESTABLISHED)));

		if (error == E_OK) {
			/* ����̃A�h���X���R�s�[����B*/
			*p_dstaddr = cep->dstaddr;
			}
		else {
			/*
			 *  �ʐM�[�_�����t����������A
			 *  �C�x���g�t���O���N���[�Y�ɐݒ肷��B
			 */
			cep->rep = NULL;
			cep->fsm_state = TCP_FSM_CLOSED;
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_acp_cep */

#endif	/* of #ifdef TCP_CFG_PASSIVE_OPEN */

/*
 *  tcp_con_cep -- �ڑ��v�� (�\���I�[�v��)�y�W���@�\�z
 */

#ifdef __tcp_con_cep

ER
TCP_CON_CEP (ID cepid, T_IPEP *p_myaddr, T_IPEP *p_dstaddr, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER		error;
	FLGPTN		flag;

#ifdef TCP_CFG_NON_BLOCKING

	/*
	 *  p_dstaddr �܂��� p_myaddr �� NULL ���A
	 *  ���Đ悪�}���`�L���X�g�A�h���X�Ȃ�G���[
	 */
	if (p_myaddr == NULL || p_dstaddr == NULL || IN_IS_ADDR_MULTICAST(&p_dstaddr->ipaddr))
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  p_dstaddr �܂��� p_myaddr �� NULL �A
	 *  ���Đ悪�}���`�L���X�g�A�h���X���A
	 *  tmout �� TMO_NBLK �Ȃ�G���[
	 */
	if (p_myaddr == NULL || p_dstaddr == NULL ||
	    IN_IS_ADDR_MULTICAST(&p_dstaddr->ipaddr) || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_CON_CEP)) != E_OK)
		return error;

	/* CEP �� FSM ���N���[�Y��ԂłȂ���΃G���[�B*/
	if (cep->fsm_state != TCP_FSM_CLOSED) {
		error = E_OBJ;
		goto err_ret;
		}
	syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_CLOSED)));

	/* �V�[�P���X�ԍ�������������B*/
	if (tcp_iss == 0)
		tcp_init_iss();

	/* �ʐM�[�_������������B*/
	tcp_init_cep(cep);

	/*
	 *  p_myaddr �� NADR (-1) �ł͂Ȃ��A�� IP �A�h���X�� ANY �łȂ���΁A
	 *  �w�肳�ꂽ IP �A�h���X�����蓖�Ă�B
	 */
	if (p_myaddr != NADR && !IN_IS_ADDR_ANY(&p_myaddr->ipaddr))
		cep->myaddr.ipaddr = p_myaddr->ipaddr;
	else {
		T_IN_IFADDR	*ia;

		if ((ia = IN_IFAWITHIFP(IF_GET_IFNET(), &p_dstaddr->ipaddr)) == NULL) {
			error = E_PAR;
			goto err_ret;
			}
		cep->myaddr.ipaddr = ia->addr;
		}

	/* �ʐM�[�_��ݒ肷��B*/
	cep->fsm_state = TCP_FSM_SYN_SENT;
	cep->dstaddr   = *p_dstaddr;
	cep->iss       = tcp_iss;
	cep->timer[TCP_TIM_KEEP] = TCP_TVAL_KEEP_INIT;
	tcp_iss += TCP_ISS_INCR() / 2;
	init_send_seq(cep);

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {
		/* �m���u���b�L���O�R�[�� */
		cep->p_dstaddr    = p_dstaddr;
		cep->p_myaddr     = p_myaddr;
		cep->snd_nblk_tfn = TFN_TCP_CON_CEP;

		/* �R�l�N�V�����̊J�݂��|�X�g����B*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		return E_WBLK;
		}
	else {

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/*
		 *  p_myaddr �� NADR (-1) ���A
		 *  ���|�[�g�ԍ��� TCP_PORTANY �Ȃ�A�����Ŋ��蓖�Ă�B
		 */
		if (p_myaddr == NADR || p_myaddr->portno == TCP_PORTANY)
			tcp_alloc_auto_port(cep);
		else if ((error = tcp_alloc_port(cep, p_myaddr->portno)) != E_OK)
			goto err_ret;

		/* �R�l�N�V�����̊J�݂��|�X�g����B*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);

		/*
		 *  �C�x���g�� ESTABLISHED �ɂȂ�܂ő҂B
		 *  �C�x���g�� CLOSED �ɂȂ����ꍇ�́A���炩�̃G���[�������������A
		 *  �ڑ��v�������ۂ��ꂽ���Ƃ��Ӗ����Ă���B
		 */
		error = twai_flg(cep->est_flgid, (TCP_CEP_EVT_CLOSED |
		                                  TCP_CEP_EVT_ESTABLISHED), TWF_ORW, &flag, tmout);
		if (error == E_OK) {
			if (cep->error != E_OK)
				error = cep->error;
			else if (cep->fsm_state == TCP_FSM_CLOSED)
				error = E_CLS;
			}

		syscall(clr_flg(cep->est_flgid, (FLGPTN)(~TCP_CEP_EVT_ESTABLISHED)));

		if (error != E_OK) {
			/*
			 *  �ʐM�[�_�����t����������A
			 *  �C�x���g�t���O���N���[�Y�ɐݒ肷��B
			 */
			cep->rep = NULL;
			cep->fsm_state = TCP_FSM_CLOSED;
			syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_con_cep */

#ifdef __tcp_cls_cep

/*
 *  tcp_user_closed -- ���[�U����̃R�l�N�V�����̊J��
 */

T_TCP_CEP *
tcp_user_closed (T_TCP_CEP *cep)
{
	switch (cep->fsm_state) {

	case TCP_FSM_CLOSED:		/* �N���[�Y	*/
	case TCP_FSM_LISTEN:		/* �󓮃I�[�v��	*/
		cep->fsm_state = TCP_FSM_CLOSED;
		cep = tcp_close(cep);
		break;

	case TCP_FSM_SYN_SENT:		/* �\���I�[�v���ASYN ���M�ς�	*/
	case TCP_FSM_SYN_RECVD:		/* SYN ����M���ASYN ���M�ς�	*/
		cep->flags |= TCP_CEP_FLG_NEED_FIN;
		break;

	case TCP_FSM_ESTABLISHED:	/* �R�l�N�V�����J�݊���	*/
		cep->fsm_state = TCP_FSM_FIN_WAIT_1;
		break;

	case TCP_FSM_CLOSE_WAIT:	/* ���肩�� FIN ��M�AAPP �̏I���҂� */
		cep->fsm_state = TCP_FSM_LAST_ACK;
		break;
		}

	if (cep != NULL && cep->fsm_state == TCP_FSM_FIN_WAIT_2)
		cep->timer[TCP_TIM_2MSL] = TCP_TVAL_KEEP_COUNT * TCP_TVAL_KEEP_INTERVAL;
	return cep;
	}

/*
 *  tcp_cls_cep -- �ʐM�[�_�̃N���[�Y�y�W���@�\�z
 */

ER
tcp_cls_cep (ID cepid, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER		error = E_OK;
	FLGPTN		flag;

#ifndef TCP_CFG_NON_BLOCKING

	/* tmout �� TMO_NBLK �Ȃ�G���[ */
	if (tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifndef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_CLS_CEP)) != E_OK)
		return error;

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {				/* �m���u���b�L���O�R�[�� */

		if (!IS_PTR_DEFINED(cep->callback))
			error = E_OBJ;
		else if (cep->fsm_state == TCP_FSM_CLOSED) {	/* ���łɃN���[�Y����Ă���Ƃ� */

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_CLS_CEP, E_OK);
			error = E_WBLK;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			ER	error = E_OK;

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_CLS_CEP, (void*)&error);
			error = E_WBLK;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			}
		else {
			/* NBLK ��API �@�\�R�[�h��ݒ肷��B*/
			cep->rcv_nblk_tfn = TFN_TCP_CLS_CEP;

			if ((cep = tcp_user_closed(cep)) != NULL) {	/* �R�l�N�V������ؒf����B*/
				/* �ؒf�Z�O�����g�o�͂��|�X�g����B*/
				cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
				sig_sem(SEM_TCP_POST_OUTPUT);
				}

			/*  cep �� NULL �Ŗ߂��Ă����ꍇ�́A
			 *  ���ɃR�l�N�V�������ؒf����Ă��邱�Ƃ��Ӗ����Ă���B
			 *  �܂��A���̏ꍇ�R�[���o�b�N�֐����Ăяo����Ă���B
			 */
			return E_WBLK;
			}
		}
	else {							/* ��m���u���b�L���O�R�[�� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		if ((cep = tcp_user_closed(cep)) == NULL) {	/* �R�l�N�V������ؒf����B*/

			/*  cep �� NULL �Ŗ߂��Ă����ꍇ�́A
			 *  ���ɃR�l�N�V�������ؒf����Ă��邱�Ƃ��Ӗ����Ă���B
			 */
			return error;
			}
		else {
			/* �ؒf�Z�O�����g�o�͂��|�X�g����B*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);

			/* �C�x���g�t���O�� CLOSED �ɂȂ�܂ő҂B*/
			error = twai_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED, TWF_ORW, &flag, tmout);
			if (error == E_OK && cep->error != E_OK)
				error = cep->error;

			if (error != E_OK) {
				if (error == E_RLWAI) {
					/* tcp_cls_cep ���L�����Z�����ꂽ�Ƃ��́ARST �𑗐M����B*/
					tcp_respond(NULL, cep, cep->rcv_nxt, cep->snd_una - 1, 
					            cep->rbufsz - cep->rwbuf_count, TCP_FLG_RST);
					}

				/* �^�C�}�[���~����B*/
				tcp_cancel_timers(cep);

				/* 
				 *  �ʐM�[�_�����b�N���A
				 *  ��M�č\���L���[�̃l�b�g���[�N�o�b�t�@���������B
				 */
				syscall(wai_sem(cep->semid_lock));
				tcp_free_reassq(cep);
				syscall(sig_sem(cep->semid_lock));

				/* ��Ԃ𖢎g�p�ɂ���B*/
				cep->fsm_state = TCP_FSM_CLOSED;

				/*
				 * �ȉ��Ɋ֌W���Ȃ��t���O���N���A�[����B
				 * �E����M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\
				 * �E���I�ȒʐM�[�_�̐����E�폜�@�\
				 */
				cep->flags &= (TCP_CEP_FLG_WBCS_NBUF_REQ | TCP_CEP_FLG_WBCS_MASK | 
				               TCP_CEP_FLG_DYNAMIC       | TCP_CEP_FLG_VALID);

				/* 
				 *  �ʐM�[�_�����b�N���A
				 *  ����M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B
				 */
				cep->rwbuf_count = 0;
				syscall(wai_sem(cep->semid_lock));
				TCP_FREE_RWBUFQ(cep);
				TCP_FREE_SWBUFQ(cep);
				syscall(sig_sem(cep->semid_lock));

				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				}
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_cls_cep */

#ifdef __tcp_sht_cep

/*
 *  tcp_sht_cep  -- �f�[�^���M�̏I���y�W���@�\�z
 */

ER
tcp_sht_cep (ID cepid)
{
	T_TCP_CEP	*cep;
	ER		error = E_OK;

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SHT_CEP)) != E_OK)
		return error;

	/* TCP �ʐM�[�_�̃R�l�N�V�������m����ԂłȂ���΃G���[ */
	if (!TCP_FSM_HAVE_ESTABLISHED(cep->fsm_state)) {
		if ((error = cep->error) == E_OK)
			error = E_OBJ;
		}

	else if ((cep = tcp_user_closed(cep)) != NULL) {		/* �R�l�N�V������ؒf����B*/

		/* �ؒf�Z�O�����g�o�͂��|�X�g����B*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);
		}

	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_sht_cep */

#ifdef __tcp_snd_dat

/*
 *  tcp_snd_dat -- �p�P�b�g�̑��M�y�W���@�\�z
 */

ER_UINT
tcp_snd_dat (ID cepid, void *data, int_t len, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* data �� NULL ���Alen < 0 �Ȃ�G���[ */
	if (data == NULL || len < 0)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* data �� NULL�Alen < 0 ���Atmout �� TMO_NBLK �Ȃ�G���[ */
	if (data == NULL || len < 0 || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SND_DAT)) != E_OK)
		return error;

	/* ���M�ł��邩�A�ʐM�[�_�̏�Ԃ�����B*/
	if ((error = tcp_can_send_more(cep, TFN_TCP_SND_DAT, tmout)) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {		/* �m���u���b�L���O�R�[�� */

		/* ���M�E�B���h�o�b�t�@�ɋ󂫂�����΃R�[���o�b�N�֐����Ăяo���B*/
		if (!TCP_IS_SWBUF_FULL(cep)) {

		 	/* ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB*/
			error = TCP_WRITE_SWBUF(cep, data, (uint_t)len);

			/* �o�͂��|�X�g����B*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->snd_data     = data;
			cep->snd_len      = len;
			cep->snd_nblk_tfn = TFN_TCP_SND_DAT;
			TCP_ALLOC_SWBUF(cep);

			return E_WBLK;
			}
		}
	else {		/* ��m���u���b�L���O�R�[�� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	 	/* ���M�E�B���h�o�b�t�@���󂭂̂�҂B*/
		if ((error = TCP_WAIT_SWBUF(cep, tmout)) != E_OK)
			goto err_ret;

	 	/* ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB*/
		if ((error = TCP_WRITE_SWBUF(cep, data, (uint_t)len)) > 0) {

			/* �f�[�^�𑗐M����B���M�E�B���h�o�b�t�@���t���̂Ƃ��͋����I�ɑ��M����B*/
			if (TCP_IS_SWBUF_FULL(cep))
				cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR;

			/* �o�͂��|�X�g����B*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_snd_dat */

#ifdef __tcp_snd_oob

#ifdef TCP_CFG_EXTENTIONS

/*
 *  tcp_snd_oob -- �ً}�f�[�^�̑��M�y�g���@�\�z
 */

ER_UINT
tcp_snd_oob (ID cepid, void *data, int_t len, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* data �� NULL ���Alen < 0 �Ȃ�G���[ */
	if (data == NULL || len < 0)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* data �� NULL�Alen < 0 ���Atmout �� TMO_NBLK �Ȃ�G���[ */
	if (data == NULL || len < 0 || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SND_OOB)) != E_OK)
		return error;

	/* ���M�ł��邩�A�ʐM�[�_�̏�Ԃ�����B*/
	if ((error = tcp_can_send_more(cep, TFN_TCP_SND_OOB, tmout)) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {		/* �m���u���b�L���O�R�[�� */

		/* ���M�E�B���h�o�b�t�@�ɋ󂫂�����΃R�[���o�b�N�֐����Ăяo���B*/
		if (!TCP_IS_SWBUF_FULL(cep)) {

		 	/* ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB*/
			error = TCP_WRITE_SWBUF(cep, data, (uint_t)len);

			/* ���M�ً}�|�C���^��ݒ肷��B*/
			cep->snd_up = cep->snd_una + cep->swbuf_count;

			/* �o�͂��|�X�g����B*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_OOB, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_SND_OOB, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->snd_data     = data;
			cep->snd_len      = len;
			cep->snd_nblk_tfn = TFN_TCP_SND_OOB;
			TCP_ALLOC_SWBUF(cep);

			return E_WBLK;
			}
		}
	else {		/* ��m���u���b�L���O�R�[�� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	 	/* ���M�E�B���h�o�b�t�@���󂭂̂�҂B*/
		if ((error = TCP_WAIT_SWBUF(cep, tmout)) != E_OK)
			goto err_ret;

	 	/* ���M�E�B���h�o�b�t�@�Ƀf�[�^���������ށB*/
		if ((error = TCP_WRITE_SWBUF(cep, data, (uint_t)len)) > 0) {

			/* ���M�ً}�|�C���^��ݒ肷��B*/
			cep->snd_up = cep->snd_una + cep->swbuf_count;

			/* �f�[�^�𑗐M����B���M�E�B���h�o�b�t�@���t���̂Ƃ��͋����I�ɑ��M����B*/
			if (TCP_IS_SWBUF_FULL(cep))
				cep->flags |= TCP_CEP_FLG_FORCE | TCP_CEP_FLG_FORCE_CLEAR;

			/* �o�͂��|�X�g����B*/
			cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_TCP_POST_OUTPUT);
			}

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_snd_oob */

#ifdef __tcp_get_buf

/*
 *  tcp_get_buf -- ���M�p�o�b�t�@�̊l���y�W���@�\�z
 */

ER_UINT
tcp_get_buf (ID cepid, void **p_buf, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* p_buf �� NULL �Ȃ�G���[ */
	if (p_buf == NULL)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* p_buf �� NULL ���Atmout �� TMO_NBLK �Ȃ�G���[ */
	if (p_buf == NULL || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_GET_BUF)) != E_OK)
		return error;

	/* ���M�ł��邩�A�ʐM�[�_�̏�Ԃ�����B*/
	if ((error = tcp_can_send_more(cep, TFN_TCP_GET_BUF, tmout)) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {		/* �m���u���b�L���O�R�[�� */

		if (!TCP_IS_SWBUF_FULL(cep)) {

			/* ���M�E�B���h�o�b�t�@�ɋ󂫂�����΃R�[���o�b�N�֐����Ăяo���B*/
			error = TCP_GET_SWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_GET_BUF, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_GET_BUF, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->snd_p_buf    = p_buf;
			cep->snd_nblk_tfn = TFN_TCP_GET_BUF;
			TCP_ALLOC_SWBUF(cep);
			return E_WBLK;
			}
		}

	else {		/* ��m���u���b�L���O�R�[�� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	 	/* ���M�E�B���h�o�b�t�@���󂭂̂�҂B*/
		if ((error = TCP_WAIT_SWBUF(cep, tmout)) != E_OK)
			goto err_ret;

	 	/* ���M�E�B���h�o�b�t�@�̋�A�h���X���l������B*/
		error = TCP_GET_SWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_get_buf */

#ifdef __tcp_snd_buf

/*
 *  tcp_snd_buf -- �o�b�t�@���̃f�[�^�̑��M�y�W���@�\�z
 */

ER
tcp_snd_buf (ID cepid, int_t len)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* ���M���钷�� len ���`�F�b�N����B*/
	if (len < 0)
		return E_PAR;

	/* ���M���钷��len �� 0 �ł���΁A�������Ȃ��Ŗ߂�B*/
	if (len == 0)
		return E_OK;

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_SND_BUF)) != E_OK)
		return error;

	/* ���M���钷�� len ���`�F�b�N����B*/
	if (len > cep->get_buf_len) {
		error = E_OBJ;
		goto err_ret;
		}

	/* ���M�ł��邩�ACEP �� FSM ��Ԃ�����B*/
	if (!TCP_FSM_CAN_SEND_MORE(cep->fsm_state)) {
		if ((error = cep->error) == E_OK)
			error = E_OBJ;
		goto err_ret;
		}

	/* ���M�E�B���h�o�b�t�@�̃f�[�^�𑗐M�\�ɂ���B*/
	TCP_SEND_SWBUF(cep, (uint_t)len);

	/* �o�͂��|�X�g����B*/
	cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
	sig_sem(SEM_TCP_POST_OUTPUT);

err_ret:
	cep->snd_tskid = TA_NULL;
	cep->snd_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_snd_buf */

#ifdef __tcp_rcv_dat

/*
 *  tcp_rcv_dat -- �p�P�b�g�̎�M�y�W���@�\�z
 */

ER_UINT
tcp_rcv_dat (ID cepid, void *data, int_t len, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* data �� NULL ���Alen < 0 �Ȃ�G���[ */
	if (data == NULL || len < 0)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* data �� NULL�Alen < 0 ���Atmout �� TMO_NBLK �Ȃ�G���[ */
	if (data == NULL || len < 0 || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_RCV_DAT)) != E_OK)
		return error;

	/* ��M�ł��邩�A�ʐM�[�_�̏�Ԃ�����B*/
	if (tcp_can_recv_more(&error, cep, TFN_TCP_RCV_DAT, tmout) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {		/* �m���u���b�L���O�R�[�� */

		/* ��M�E�B���h�o�b�t�@�Ƀf�[�^������΃R�[���o�b�N�֐����Ăяo���B*/
		if (cep->rwbuf_count > 0) {

			/* ��M�E�B���h�o�b�t�@����f�[�^�����o���B*/
			len = TCP_READ_RWBUF(cep, data, (uint_t)len);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_DAT, (void*)(uint32_t)len);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_DAT, (void*)&len);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->rcv_data     = data;
			cep->rcv_len      = len;
			cep->rcv_nblk_tfn = TFN_TCP_RCV_DAT;
			return E_WBLK;
			}
		}
	else {		/* ��m���u���b�L���O�R�[�� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* ��M�E�B���h�o�b�t�@�Ƀf�[�^���Ȃ���΁A���͂�����܂ő҂B*/
		if ((error = tcp_wait_rwbuf(cep, tmout)) != E_OK)
			goto err_ret;

		/* ��M�E�B���h�o�b�t�@����f�[�^�����o���B*/
		error = TCP_READ_RWBUF(cep, data, (uint_t)len);

		/* ����ɃE�B���h�E�T�C�Y���ς�������Ƃ�m�点�邽�ߏo�͂��|�X�g����B*/
		cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
		sig_sem(SEM_TCP_POST_OUTPUT);

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_rcv_dat */

#ifdef __tcp_rcv_oob

#ifdef TCP_CFG_EXTENTIONS

/*
 *  tcp_rcv_oob -- �ً}�f�[�^�̎�M�y�g���@�\�z
 *
 *    ����: ���M���������I�N�e�b�g�̃f�[�^�𑗐M���Ă��A
 *          �ً}�|�C���^���w�� 1 �I�N�e�b�g�̃f�[�^�̂ݎ�M����B
 */

ER_UINT
tcp_rcv_oob (ID cepid, void *data, int_t len)
{
	T_TCP_CEP	*cep;
	uint8_t		*urg;

	/* TCP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* data �� NULL ���Alen < 0 �Ȃ�G���[ */
	if (data == NULL || len < 0)
		return E_PAR;

	/* TCP �ʐM�[�_�𓾂�B*/
	cep = GET_TCP_CEP(cepid);

	/* ��M�ł��邩�A�ʐM�[�_�̏�Ԃ�����B*/
	/* ��M�ł��邩�Afsm_state ������B*/
	if (!TCP_FSM_CAN_RECV_MORE(cep->fsm_state))
		return E_OBJ;

	/*
	 *  �ً}�f�[�^����̃Z�O�����g�� TCP �w�b�_��
	 *  �ݒ肳��Ă��Ȃ���΁A�ً}�f�[�^����M���Ă��Ȃ��B
	 */
	if (cep->urg_tcph == NULL)
		return E_OBJ;

	/* len == 0 �Ȃ�o�b�t�@�I�[�o�[�t���[ */
	if (len == 0)
		return E_BOVR;

	/* �ً}�|�C���^���w�� 1 �I�N�e�b�g�̃f�[�^��ǂݎ��B*/
	urg = (uint8_t*)cep->urg_tcph + TCP_DATA_OFF(cep->urg_tcph->doff) + cep->urg_tcph->urp + TCP_CFG_URG_OFFSET;
	*(uint8_t*)data = *urg;

	/* �ǂݎ�����f�[�^������� SDU ��O�ɋl�߂�B*/
	memcpy(urg, urg + 1, cep->urg_tcph->sum - (cep->urg_tcph->urp + TCP_CFG_URG_OFFSET) - 1);

	/* tcp_rcv_oob() ���ďo���ꂽ���ƒm�点�邽�߂ɁANULL ��ݒ肷��B*/
	cep->urg_tcph = NULL;

	return 1;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_rcv_oob */

#ifdef __tcp_rcv_buf

/*
 *  tcp_rcv_buf -- ��M�����f�[�^�̓������o�b�t�@�̊l���y�W���@�\�z
 */

ER_UINT
tcp_rcv_buf (ID cepid, void **p_buf, TMO tmout)
{
	T_TCP_CEP	*cep;
	ER_UINT		error;

#ifdef TCP_CFG_NON_BLOCKING

	/* p_buf �� NULL �Ȃ�G���[ */
	if (p_buf == NULL)
		return E_PAR;

#else	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/* p_buf �� NULL ���Atmout �� TMO_NBLK �Ȃ�G���[ */
	if (p_buf == NULL || tmout == TMO_NBLK)
		return E_PAR;

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_RCV_BUF)) != E_OK)
		return error;

	/* ��M�ł��邩�A�ʐM�[�_�̏�Ԃ�����B*/
	if (tcp_can_recv_more(&error, cep, TFN_TCP_RCV_DAT, tmout) != E_OK)
		goto err_ret;

#ifdef TCP_CFG_NON_BLOCKING

	/* �^�C���A�E�g���`�F�b�N����B*/
	if (tmout == TMO_NBLK) {		/* �m���u���b�L���O�R�[�� */

		/* ��M�E�B���h�o�b�t�@�Ƀf�[�^������΃R�[���o�b�N�֐����Ăяo���B*/
		if (cep->rwbuf_count > 0) {

		 	/* ��M�E�B���h�o�b�t�@�̋�A�h���X���l������B*/
			error = TCP_GET_RWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_BUF, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			/* �R�[���o�b�N�֐����Ăяo���B*/
			(*cep->callback)(GET_TCP_CEPID(cep), TFN_TCP_RCV_BUF, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			error = E_WBLK;
			goto err_ret;
			}
		else {
			cep->rcv_p_buf    = p_buf;
			cep->rcv_nblk_tfn = TFN_TCP_RCV_BUF;
			return E_WBLK;
			}
		}
	else {		/* ��m���u���b�L���O�R�[�� */

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

		/* ��M�E�B���h�o�b�t�@�Ƀf�[�^���Ȃ���΁A���͂�����܂ő҂B*/
		if ((error = tcp_wait_rwbuf(cep, tmout)) != E_OK) {
			cep->rwbuf_count = 0;
			goto err_ret;
			}

	 	/* ��M�E�B���h�o�b�t�@�̃A�h���X���l������B*/
		error = TCP_GET_RWBUF_ADDR(cep, p_buf);

#ifdef TCP_CFG_NON_BLOCKING

		}

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_rcv_buf */

#ifdef __tcp_rel_buf

/*
 *  tcp_rel_buf -- ��M�p�o�b�t�@�̉���y�W���@�\�z
 */

ER
tcp_rel_buf (ID cepid, int_t len)
{
	T_TCP_CEP	*cep;
	ER		error;

	/* ������钷�� len ���`�F�b�N����B*/
	if (len < 0)
		return E_PAR;

	/*
	 *  CEP �����b�N���AAPI �@�\�R�[�h�ƃ^�X�N���ʎq���L�^����B
	 *  ���łɋL�^����Ă���΁A�y���f�B���O���Ȃ̂ŃG���[
	 */
	if ((error = tcp_lock_cep(cepid, &cep, TFN_TCP_REL_BUF)) != E_OK)
		return error;

	/* ������钷�� len ���`�F�b�N����B*/
	if (len > cep->rcv_buf_len) {
		error = E_OBJ;
		goto err_ret;
		}

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/* ��M�E�B���h�o�b�t�@�����M�����I�N�e�b�g���폜����B*/
	TCP_DROP_RWBUF(cep, (uint_t)len);

	/* tcp_rcv_buf �̊����Ē������Z�b�g����B*/
	cep->rcv_buf_len = 0;

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	/* ����ɃE�B���h�E�T�C�Y���ς�������Ƃ�m�点�邽�ߏo�͂��|�X�g����B*/
	cep->flags |= TCP_CEP_FLG_POST_OUTPUT;
	sig_sem(SEM_TCP_POST_OUTPUT);

err_ret:
	cep->rcv_tskid = TA_NULL;
	cep->rcv_tfn   = TFN_TCP_UNDEF;
	return error;
	}

#endif	/* of #ifdef __tcp_rel_buf */

#ifdef __tcp_can_cep

/*
 *  tcp_can_snd -- �y���f�B���O���Ă��鑗�M�̃L�����Z��
 */

static ER
tcp_can_snd (T_TCP_CEP *cep, FN fncd)
{
	ER	error = E_OK;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 *  snd_tskid �� TA_NULL �Ȃ�A
	 *  �y���f�B���O���Ă��Ȃ��̂ŃG���[
	 */
	if (cep->snd_tskid == TA_NULL)
		error = EV_NOPND;

	/* �y���f�B���O���� API �@�\�R�[�h�ƈ�v���Ȃ���΃G���[ */
	else if (fncd != TFN_TCP_ALL && fncd != cep->snd_tfn)
		error = E_OBJ;

	/* �������L�����Z������B*/
	else {

		/* ��M�č\���L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		tcp_free_reassq(cep);

		/* ��M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		cep->rwbuf_count = 0;
		TCP_FREE_RWBUFQ(cep);

		/* ���M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		TCP_FREE_SWBUFQ(cep);

#ifdef TCP_CFG_NON_BLOCKING

		if (cep->snd_nblk_tfn != TFN_TCP_UNDEF) {	/* �m���u���b�L���O�R�[�� */

			switch (cep->snd_nblk_tfn) {

			case TFN_TCP_CON_CEP:
				/*  �ʐM�[�_�����t�����������B*/
				cep->rep = NULL;
				cep->fsm_state = TCP_FSM_CLOSED;
				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				break;

			case TFN_TCP_SND_DAT:
			case TFN_TCP_GET_BUF:
			case TFN_TCP_SND_OOB:
				break;
				}

			if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)E_RLWAI);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				ER	error = E_RLWAI;

				(*cep->callback)(GET_TCP_CEPID(cep), cep->snd_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				}
			else
				error = E_OBJ;
			cep->snd_nblk_tfn = TFN_TCP_UNDEF;
			}
		else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			error = rel_wai(cep->snd_tskid);

		cep->snd_tskid = TA_NULL;
		cep->snd_tfn   = TFN_TCP_UNDEF;
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_can_rcv -- �y���f�B���O���Ă����M�̃L�����Z��
 */

static ER
tcp_can_rcv (T_TCP_CEP *cep, FN fncd)
{
	ER	error = E_OK;

	/* �ʐM�[�_�����b�N����B*/
	syscall(wai_sem(cep->semid_lock));

	/*
	 *  rcv_tskid �� TA_NULL �Ȃ�A
	 *  �y���f�B���O���Ă��Ȃ��̂ŃG���[
	 */
	if (cep->rcv_tskid == TA_NULL)
		error = EV_NOPND;

	/* �y���f�B���O���� API �@�\�R�[�h�ƈ�v���Ȃ���΃G���[ */
	else if (fncd != TFN_TCP_ALL && fncd != cep->rcv_tfn)
		error = E_OBJ;

	/* �������L�����Z������B*/
	else {

		/* ��M�č\���L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		tcp_free_reassq(cep);

		/* ��M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		cep->rwbuf_count = 0;
		TCP_FREE_RWBUFQ(cep);

		/* ���M�E�B���h�o�b�t�@�L���[�̃l�b�g���[�N�o�b�t�@���������B*/
		TCP_FREE_SWBUFQ(cep);

#ifdef TCP_CFG_NON_BLOCKING

		if (cep->rcv_nblk_tfn != TFN_TCP_UNDEF) {	/* �m���u���b�L���O�R�[�� */

			switch (cep->rcv_nblk_tfn) {

			case TFN_TCP_ACP_CEP:
				/*
				 *  �ʐM�[�_�����t����������A
				 *  �C�x���g�t���O���N���[�Y�ɐݒ肷��B
				 */
				cep->rep = NULL;
				cep->fsm_state = TCP_FSM_CLOSED;
				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				break;

			case TFN_TCP_RCV_DAT:
			case TFN_TCP_RCV_BUF:
				break;

			case TFN_TCP_CLS_CEP:
				cep->fsm_state = TCP_FSM_CLOSED;
				tcp_respond(NULL, cep, cep->rcv_nxt, cep->snd_una - 1,
				            cep->rbufsz - cep->rwbuf_count, TCP_FLG_RST);
				syscall(set_flg(cep->est_flgid, TCP_CEP_EVT_CLOSED));
				break;
				}

			if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)E_RLWAI);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				ER	error = E_RLWAI;

				(*cep->callback)(GET_TCP_CEPID(cep), cep->rcv_nblk_tfn, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

				}
			else
				error = E_OBJ;
			cep->rcv_nblk_tfn = TFN_TCP_UNDEF;
			}
		else

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

			error = rel_wai(cep->rcv_tskid);

		cep->rcv_tskid = TA_NULL;
		cep->rcv_tfn   = TFN_TCP_UNDEF;
		}

	/* �ʐM�[�_�̃��b�N����������B*/
	syscall(sig_sem(cep->semid_lock));

	return error;
	}

/*
 *  tcp_can_cep -- �y���f�B���O���Ă��鏈���̃L�����Z���y�W���@�\�z
 */

ER
tcp_can_cep (ID cepid, FN fncd)
{
	T_TCP_CEP	*cep;
	ER		error = E_OK, snd_err, rcv_err;

	/* API �@�\�R�[�h���`�F�b�N����B*/
	if (!VALID_TFN_TCP_CAN(fncd))
		return E_PAR;

	/* TCP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �ʐM�[�_�𓾂�B*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �ʐM�[�_���`�F�b�N����B*/
	if (!VALID_TCP_CEP(cep))
		return E_NOEXS;

	if (fncd == TFN_TCP_ALL) {		/* TFN_TCP_ALL �̏��� */
		snd_err = tcp_can_snd(cep, fncd);
		rcv_err = tcp_can_rcv(cep, fncd);

		/*
		 *  snd_err �� rcv_err �̂ǂ���� EV_NOPND
		 *  �Ȃ�A�y���f�B���O���Ă��Ȃ��̂ŃG���[
		 */
		if (snd_err == EV_NOPND && rcv_err == EV_NOPND)
			error = E_OBJ;
		else {
			if (snd_err == EV_NOPND)
				snd_err = E_OK;
			if (rcv_err == EV_NOPND)
				rcv_err = E_OK;

			if (snd_err != E_OK)
				error = snd_err;
			else if (rcv_err != E_OK)
				error = rcv_err;
			}
		}

	else if (IS_TFN_TCP_RCV(fncd)) {	/* ��M�����̃L�����Z�� */
		if ((error = tcp_can_rcv(cep, fncd)) == EV_NOPND)
			error = E_OBJ;
		}

	else {					/* ���M�����̃L�����Z�� */
		if ((error = tcp_can_snd(cep, fncd)) == EV_NOPND)
			error = E_OBJ;
		}

	return error;
	}

#endif	/* of #ifdef __tcp_can_cep */

/*
 *  tcp_set_opt -- TCP �ʐM�[�_�I�v�V�����̐ݒ�y�g���@�\�z
 *
 *  ����: �ݒ�\�� TCP �ʐM�[�_�I�v�V�����͖������߁AE_PAR ���Ԃ����B
 */

#ifdef __tcp_set_opt

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_set_opt (ID cepid, int_t optname, void *optval, int_t optlen)
{
	T_TCP_CEP	*cep;

	/* TCP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �ʐM�[�_�𓾂�B*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �ʐM�[�_���`�F�b�N����B*/
	if (!VALID_TCP_CEP(cep))
		return E_NOEXS;

	return E_PAR;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_set_opt */

/*
 *  tcp_get_opt -- TCP �ʐM�[�_�I�v�V�����̐ݒ�y�g���@�\�z
 *
 *  ����: �ݒ�\�� TCP �ʐM�[�_�I�v�V�����͖������߁AE_PAR ���Ԃ����B
 */

#ifdef __tcp_get_opt

#ifdef TCP_CFG_EXTENTIONS

ER
tcp_get_opt (ID cepid, int_t optname, void *optval, int_t optlen)
{
	T_TCP_CEP	*cep;

	/* TCP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VAID_TCP_CEPID(cepid))
		return E_ID;

	/* TCP �ʐM�[�_�𓾂�B*/
	cep = GET_TCP_CEP(cepid);

	/* TCP �ʐM�[�_���`�F�b�N����B*/
	if (!VALID_TCP_CEP(cep))
		return E_NOEXS;

	return E_PAR;
	}

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

#endif	/* of #ifdef __tcp_get_opt */

#endif	/* of #ifdef SUPPORT_TCP */
