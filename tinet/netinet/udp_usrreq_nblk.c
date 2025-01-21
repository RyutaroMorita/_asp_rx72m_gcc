/*
 *  TINET (UDP/IP Protocol Stack)
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
 *  @(#) $Id: udp_usrreq_nblk.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 * 2. Redistributions in binary form must ceproduce the above copyright
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
 *	@(#)udp_usrreq.c	8.6 (Berkeley) 5/23/95
 * $FreeBSD: src/sys/netinet/udp_usrreq.c,v 1.49.2.2 1999/08/29 16:29:58 peter Exp $
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
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp_ipcp.h>

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

/*
 *  IPv4 �� IPv6 �̐؂�ւ��}�N��
 */

#if defined(SUPPORT_INET4)

#define UDP_SND_DAT	udp_snd_dat
#define UDP_RCV_DAT	udp_rcv_dat

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define UDP_SND_DAT	udp6_snd_dat
#define UDP_RCV_DAT	udp6_rcv_dat

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  TINET �����C�u���������Ȃ��ꍇ�́A�S�Ă̋@�\��
 *  �I�u�W�F�N�g�t�@�C���ɏo�͂��邽�߁A�}�N����L���ɂ���B
 */

#ifndef UDP_CFG_LIBRARY

#define __udp_can_snd
#define __udp_can_rcv
#define __udp_snd_dat
#define __udp_rcv_dat

#endif	/* of #ifndef UDP_CFG_LIBRARY */

#ifdef UDP_CFG_NON_BLOCKING

#ifdef __udp_can_snd

/*
 *  udp_can_snd -- �y���f�B���O���Ă��鑗�M�̃L�����Z��
 */

ER
udp_can_snd (T_UDP_CEP *cep, ER error)
{
	if (cep->snd_p_dstaddr != NULL) {	/* �m���u���b�L���O�R�[���Ńy���f�B���O�� */
		if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		else
			error = E_OBJ;
		cep->snd_p_dstaddr = NULL;
		}
	else if (cep->snd_tskid != TA_NULL) {	/* ��m���u���b�L���O�R�[���Ńy���f�B���O�� */

#ifdef UDP_CFG_EXTENTIONS

		/* �҂����ɔ��������G���[����ݒ肷��B*/
		cep->error = error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		error = rel_wai(cep->snd_tskid);
		cep->snd_tskid = TA_NULL;
		}
	else					/* �ǂ���ł��Ȃ��Ȃ�y���f�B���O���Ă��Ȃ� */
		error = EV_NOPND;

	return error;
	}

#endif	/* of #ifdef __udp_can_snd */

#ifdef __udp_can_rcv

/*
 *  udp_can_rcv -- �y���f�B���O���Ă����M�̃L�����Z��
 */

ER
udp_can_rcv (T_UDP_CEP *cep, ER error)
{
	if (cep->rcv_p_dstaddr != NULL) {	/* �m���u���b�L���O�R�[���Ńy���f�B���O�� */
		if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_RCV_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_RCV_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		else
			error = E_OBJ;
		cep->rcv_p_dstaddr = NULL;
		}
	else if (cep->rcv_tskid != TA_NULL) {	/* ��m���u���b�L���O�R�[���Ńy���f�B���O�� */

#ifdef UDP_CFG_EXTENTIONS

		/* �҂����ɔ��������G���[����ݒ肷��B*/
		cep->error = error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		error = rel_wai(cep->rcv_tskid);
		cep->rcv_tskid = TA_NULL;
		}
	else					/* �ǂ���ł��Ȃ��Ȃ�y���f�B���O���Ă��Ȃ� */
		error = EV_NOPND;

	return error;
	}

#endif	/* of #ifdef __udp_can_rcv */

#ifdef __udp_snd_dat

/*
 *  udp_snd_dat -- �p�P�b�g�̑��M�y�W���@�\�z
 */

ER_UINT
UDP_SND_DAT (ID cepid, T_IPEP *p_dstaddr, void *data, int_t len, TMO tmout)
{
	T_UDP_CEP	*cep;
	ER		error;

	/* p_dstaddr �܂��� data �� NULL �Ȃ�G���[ */
	if (p_dstaddr == NULL || data == NULL)
		return E_PAR;

	/* �f�[�^�����`�F�b�N����B*/
	if (len < 0 || len + IP_HDR_SIZE + UDP_HDR_SIZE > IF_MTU)
		return E_PAR;

	/* UDP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �ʐM�[�_�𓾂�B*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �ʐM�[�_���`�F�b�N����B*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/*
	 *  ���|�[�g�ԍ��� UDP_PORTANY �Ȃ�A�����Ŋ��蓖�Ă�B
	 */
	if (cep->myaddr.portno == UDP_PORTANY) {
		if ((error = udp_alloc_auto_port(cep)) != E_OK)
			return error;
		}

	/*
	 * �^�C���A�E�g���`�F�b�N����B
	 */

	if (tmout == TMO_NBLK) {	/* �m���u���b�L���O�R�[�� */

		/* �ʐM�[�_�����b�N����B*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->snd_p_dstaddr != NULL) {

			/* �m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_QOVR;

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));
			}
		else if (cep->snd_tskid != TA_NULL) {

			/* ��m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_OBJ;

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));
			}
		else {

			cep->snd_p_dstaddr = p_dstaddr;
			cep->snd_data	= data;
			cep->snd_len	= len;

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));

			cep->flags |= UDP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_UDP_POST_OUTPUT);
			error = E_WBLK;
			}
		}
	else {				/* ��m���u���b�L���O�R�[�� */
	
		/* �ʐM�[�_�����b�N����B*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->snd_p_dstaddr != NULL) {

			/* �m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_OBJ;

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));
			}
		else if (cep->snd_tskid != TA_NULL) {

			/* ��m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_QOVR;

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));
			}
		else {

			/* ���݂̃^�X�N���ʎq���L�^����B*/
			get_tid(&(cep->snd_tskid));

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));

			/* �p�P�b�g�𑗐M����B*/
			error = udp_send_data(cep, p_dstaddr, data, len, tmout);
			}
		}

	return error;
	}

#endif	/* of #ifdef __udp_snd_dat */

#ifdef __udp_rcv_dat

/*
 *  udp_rcv_dat -- �p�P�b�g�̎�M�y�W���@�\�z
 */

ER_UINT
UDP_RCV_DAT (ID cepid, T_IPEP *p_dstaddr, void *data, int_t len, TMO tmout)
{
	T_NET_BUF	*input;
	T_UDP_CEP	*cep;
	T_UDP_HDR	*udph;
	ER_UINT		error;
	uint_t		ulen, uhoff;

	/* p_dstaddr �܂��� data �� NULL ���Alen < 0 �Ȃ�G���[ */
	if (p_dstaddr == NULL || data == NULL || len < 0)
		return E_PAR;

	/* UDP �ʐM�[�_ ID ���`�F�b�N����B*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP �ʐM�[�_�𓾂�B*/
	cep = GET_UDP_CEP(cepid);

	/* UDP �ʐM�[�_���`�F�b�N����B*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/*
	 * �^�C���A�E�g���`�F�b�N����B
	 */

	if (tmout == TMO_NBLK) {	/* �m���u���b�L���O�R�[�� */

		/* �ʐM�[�_�����b�N����B*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->rcv_p_dstaddr != NULL)

			/* �m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_QOVR;

		else if (cep->rcv_tskid != TA_NULL)

			/* ��m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_OBJ;
		else {
			cep->rcv_p_dstaddr = p_dstaddr;
			cep->rcv_data	= data;
			cep->rcv_len	= len;
			error = E_WBLK;
			}

		/* �ʐM�[�_�����b�N����������B*/
		syscall(sig_sem(cep->semid_lock));
		return error;
		}
	else {				/* ��m���u���b�L���O�R�[�� */

		/* �ʐM�[�_�����b�N����B*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->rcv_p_dstaddr != NULL) {

			/* �m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_OBJ;

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));
			}
		else if (cep->rcv_tskid != TA_NULL) {

			/* ��m���u���b�L���O�R�[���Ńy���f�B���O�� */
			error = E_QOVR;

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));
			}
		else {

			/* ���݂̃^�X�N���ʎq���L�^����B*/
			get_tid(&(cep->rcv_tskid));

			/* �ʐM�[�_�����b�N����������B*/
			syscall(sig_sem(cep->semid_lock));

			/* ���͂�����܂ő҂B*/
			if (cep->cb_netbuf != NULL) {

				/*
				 *  �����ɂ���ꍇ�́A�R�[���o�b�N�֐��̒�����
				 *  udp_rcv_dat ���Ăяo���Ă��邱�ƂɂȂ�A
				 *  ���łɓ��͍ς݂ł���B
				 */
				input = cep->cb_netbuf;
				cep->cb_netbuf = NULL;
				}
			else if ((error = trcv_dtq(cep->rcvqid, (intptr_t*)&input, tmout)) != E_OK) {
				cep->rcv_tskid = TA_NULL;
				return error;
				}

			/* p_dstaddr ��ݒ肷��B*/
			uhoff = (uint_t)GET_UDP_HDR_OFFSET(input);
			udph = GET_UDP_HDR(input, uhoff);
			p_dstaddr->portno = ntohs(udph->sport);
			IN_COPY_TO_HOST(&p_dstaddr->ipaddr, &GET_IP_HDR(input)->src);

			/* �f�[�^���o�b�t�@�Ɉڂ��B*/
			ulen = ntohs(udph->ulen);
			if (ulen - UDP_HDR_SIZE > len)
				error = E_BOVR;
			else {
				len   =     (int_t)(ulen - UDP_HDR_SIZE);
				error = (ER_UINT)(ulen - UDP_HDR_SIZE);
				}

			memcpy(data, GET_UDP_SDU(input, uhoff), (size_t)len);

			syscall(rel_net_buf(input));

			cep->rcv_tskid = TA_NULL;
			}
		return error;
		}
	}

#endif	/* of #ifdef __udp_rcv_dat */

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#endif	/* of #ifdef SUPPORT_UDP */
