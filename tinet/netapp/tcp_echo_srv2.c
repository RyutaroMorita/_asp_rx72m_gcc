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
 *  @(#) $Id: tcp_echo_srv2.c,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

/* 
 *  TCP ECHO �T�[�o #2
 *
 *    �E����M�^�X�N�����^
 *    �E�m���u���b�L���O�R�[��
 *    �EIPv4/IPv6
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/echo.h>

#ifdef USE_TCP_ECHO_SRV2

/*
 *  �\��
 */

/*#define SHOW_RCV_RANGE*/

/*
 *  �R�l�N�V�����ؒf���@�̎w��
 */

/*#define USE_TCP_SHT_CEP*/

/*
 *  �S��ϐ�
 */

/* TCP ����M�E�B���h�o�b�t�@ */

#ifndef TCP_CFG_SWBUF_CSAVE
uint8_t tcp_echo_srv_swbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_SWBUF_SIZE];
#endif

#ifndef TCP_CFG_RWBUF_CSAVE
uint8_t tcp_echo_srv_rwbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_RWBUF_SIZE];
#endif

/*
 *  �ϐ�
 */

/*
 *  ����:
 *
 *    BUF_SIZE �� TCP ��
 *    ���M�E�C���h�E�o�b�t�@�T�C�Y + ��M�E�C���h�E�o�b�t�@�T�C�Y�� 
 *    3/2 �{�ȏ�̑傫�����Ȃ���΁A�f�b�h���b�N����\��������B
 */

#define BUF_SIZE	((TCP_ECHO_SRV_SWBUF_SIZE + \
                          TCP_ECHO_SRV_RWBUF_SIZE) * 3 / 2)

static char	buffer[BUF_SIZE];	/* �o�b�t�@		*/

static T_IPEP	dst;			/* �ڑ�����		*/
static bool_t	ena_rcv;		/* ��M�\�t���O	*/
static char	*rptr = buffer;		/* ��M�|�C���^		*/
static char	*sptr = buffer;		/* ���M�|�C���^		*/
static uint32_t	rcv_total;		/* ��M������		*/
static uint32_t	snd_total;		/* ���M������		*/
static uint16_t	chars;			/* �o�b�t�@���̕�����	*/
static uint16_t	rcv_count;		/* ��M��		*/
static uint16_t	snd_count;		/* ���M��		*/

#ifdef USE_TCP_NON_BLOCKING

static ER	rcv_error = E_OK;	/* ��M�A�m���u���b�L���O�R�[���G���[ */
static ER	snd_error = 1;		/* ���M�A�m���u���b�L���O�R�[���G���[ */

/*
 *  �m���u���b�L���O�R�[���̃R�[���o�b�N�֐�
 */

ER
callback_nblk_tcp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	ER		error = E_OK;
	ER_UINT		slen, rlen;
	SYSTIM		now;
	uint16_t	last;
	char		head, tail;

	get_tim(&now);

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		rcv_error = *(ER*)p_parblk;
		if (rcv_error == E_OK) {
			sptr = rptr = buffer;
			snd_count = snd_total = rcv_count = rcv_total = chars = 0;
			snd_error = 1;
			ena_rcv   = true;
			syslog(LOG_NOTICE, "[TES:%02d CBN] connected:  %6ld, from: %s.%d",
			                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
			}
		else
			syslog(LOG_NOTICE, "[TES:%02d CBN] accept error: %s\n", cepid, itron_strerror(rcv_error));

		syscall(sig_sem(SEM_TCP_ECHO_SRV_RCV_READY));
		break;

	case TFN_TCP_SND_DAT:
		slen = snd_error = *(ER*)p_parblk;
		if (slen > 0) {
			head = *sptr;
			tail = *(sptr + slen - 1);
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d CBN] send len: %4d, data %02x -> %02x",
			                   cepid, (uint16_t)slen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
			snd_count ++;
			snd_total += slen;

			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* ���M�|�C���^��i�߂�B*/
			if (sptr - buffer + slen >= sizeof(buffer))
				sptr -= sizeof(buffer) - slen;
			else
				sptr += slen;

			/* �o�b�t�@���̕����������炷�B*/
			last   = chars;
			chars -= slen;

 			/* �o�b�t�@���ɕ���������΁A���M�^�X�N���N������B*/
			if (chars > 0 || (!ena_rcv && chars == 0))
				sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 			/* ��M�\�ŁA�o�b�t�@���ɋ󂫂��ł���΁A��M�^�X�N���N������B*/
			if (ena_rcv && last == sizeof(buffer) && sizeof(buffer) - chars > 0)
				syscall(sig_sem(SEM_TCP_ECHO_SRV_RCV_READY));

			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
			}
		else {
			syslog(LOG_NOTICE, "[TES:%02d CBN] send error = %s", cepid, itron_strerror(snd_error));
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);
			}
		break;

	case TFN_TCP_RCV_DAT:
		rlen = rcv_error = *(ER*)p_parblk;
		if (rlen > 0) {
			head = *rptr;
			tail = *(rptr + rlen - 1);
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d CBN] recv len: %4d, data %02x -> %02x",
			                   cepid, (uint16_t)rlen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
			rcv_count ++;
			rcv_total += rlen;

			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* ��M�|�C���^��i�߂�B*/
			if (rptr - buffer + rlen >= sizeof(buffer))
				rptr -= sizeof(buffer) - rlen;
			else
				rptr += rlen;

			/* �o�b�t�@���̕������𑝂₷�B*/
			last   = chars;
			chars += rlen;

 			/* �o�b�t�@���ɕ���������΁A���M�^�X�N���N������B*/
			if (last == 0 && chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 			/* �o�b�t�@���ɋ󂫂�����΁A��M�^�X�N���N������B*/
			if (sizeof(buffer) - chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);

			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
			}
		else {
			if (rlen < 0)
				syslog(LOG_NOTICE, "[TES:%02d CBN] recv error = %s", cepid, itron_strerror(rcv_error));
			sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);
			}
		break;

	case TFN_TCP_CLS_CEP:
		snd_error = *(ER*)p_parblk;
		if (snd_error != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d CBN] close error = %s", cepid, itron_strerror(snd_error));

		syslog(LOG_NOTICE, "[TES:%02d CBN] finished:   %6ld, snd: %4d, rcv: %4d, len: %ld",
		                   cepid, now / SYSTIM_HZ, snd_count, rcv_count, snd_total);

		sig_sem(SEM_TCP_ECHO_SRV_CLS_READY);
		break;

	case TFN_TCP_CON_CEP:
	case TFN_TCP_GET_BUF:
	case TFN_TCP_RCV_BUF:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		}
	return error;
	}

/*
 *  TCP ECHO �T�[�o��M���[�`�� (�m���u���b�L���O�R�[���g�p)
 */

ER
tcp_echo_srv_rcv (ID cepid, ID repid)
{
	ER		error;
	uint16_t	blen;

	if ((error = psnd_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t)cepid)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d RCV] sync error: %s", cepid, itron_strerror(error));
		return error;
		}

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_NBLK)) != E_WBLK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] accept error = %s", cepid, itron_strerror(error));
		return error;
		}

	/* �R�l�N�V�����J�݊����܂ő҂B*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_RCV_READY));

	/* �҂��Ă���ԂɃG���[�ɂȂ�����A�R�l�N�V�����̊J�ݑ҂��ɖ߂�B*/
	if (rcv_error != E_OK)
		return rcv_error;

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	while (true) {

		/* ��M�T�C�Y���v�Z����B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
		if (sptr > rptr)
			blen = sptr - rptr;
		else
			blen = sizeof(buffer) - (rptr - buffer);
		syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* ��M����B*/
		if ((error = tcp_rcv_dat(cepid, rptr, blen, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TES:%02d RCV] recv error = %s", cepid, itron_strerror(error));
			break;
			}

		/* ��M�o�b�t�@�ɋ󂪂ł���܂ő҂B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_RCV_READY));

		/* �҂��Ă���ԂɁA��M�������� 0 �ɂȂ邩�A�G���[�ɂȂ�����I������B*/
		if (rcv_error <= 0)
			break;

		}

	/* ��M���� */
	ena_rcv = false;

	/* ��M�o�b�t�@�ɕ���������̂�҂��Ă��鑗�M�^�X�N���N������B*/
	if (chars == 0)
		sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

	/* �R�l�N�V�����ؒf�����܂ő҂B*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_CLS_READY));

	return error == E_WBLK ? E_OK : error;
	}

/*
 *  TCP ECHO �T�[�o���M�^�X�N (�m���u���b�L���O�R�[���g�p)
 */

void
tcp_echo_srv_snd_task(intptr_t exinf)
{
	ER		error;
	ID		tskid, cepid;
	uint16_t	blen;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND:%d] started.", tskid);
	while (true) {
		if ((error = rcv_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t*)&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TES:%02d SND] sync error: %s",
			                   cepid, itron_strerror(error));
			continue;
			}

		while (true) {

			/* �o�b�t�@�ɕ���������܂ő҂B*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_SND_READY));

			/* �҂��Ă���ԂɃG���[�ɂȂ�����I������B*/
			if (snd_error <= 0)
				break;

			/* ��M�����ŁA�o�b�t�@�ɕ������Ȃ���ΏI������B*/
			if (!ena_rcv && chars == 0)
				break;

			/* ���M�T�C�Y���v�Z����B*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
			if (rptr > sptr)
				blen = rptr - sptr;
			else
				blen = sizeof(buffer) - (sptr - buffer);
			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* ���M����B*/
			if ((error = tcp_snd_dat(cepid, sptr, blen, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TES:%02d SND] send error = %s", cepid, itron_strerror(error));
				break;
				}
			}

		/* ��M�o�b�t�@�ɋ󂪂ł����҂��Ă����M�^�X�N���N������B*/
		if (chars == sizeof(buffer))
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

#ifdef USE_TCP_SHT_CEP
		if ((error = tcp_sht_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d SND] shutdown error = %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

		if ((error = tcp_cls_cep(cepid, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TES:%02d SND] close error = %s", cepid, itron_strerror(error));
			}

		pol_sem(SEM_TCP_ECHO_SRV_SND_READY);
		pol_sem(SEM_TCP_ECHO_SRV_RCV_READY);
		}
	}

#else	/* of #ifdef USE_TCP_NON_BLOCKING */

/*
 *  TCP ECHO �T�[�o��M���[�`��
 */

ER
tcp_echo_srv_rcv (ID cepid, ID repid)
{
	ER_UINT		rlen;
	ER		error;
	SYSTIM		now;
	uint16_t	blen, last;
	char		head, tail;

	if ((error = psnd_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t)cepid)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d RCV] sync error: %s", cepid, itron_strerror(error));
		return error;
		}

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d ACP] accept error = %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TES:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	syscall(get_tim(&now));
	syslog(LOG_NOTICE, "[TES:%02d ACP] connected:  %6ld, from: %s.%d",
	                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	sptr = rptr = buffer;
	snd_count = snd_total = rcv_count = rcv_total = chars = 0;
	ena_rcv   = true;
	while (true) {

		/* ��M�T�C�Y���v�Z����B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
		if (sptr > rptr)
			blen = sptr - rptr;
		else
			blen = sizeof(buffer) - (rptr - buffer);
		syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* ��M����B*/
		if ((rlen = tcp_rcv_dat(cepid, rptr, blen, TMO_FEVR)) <= 0) {
			if (rlen < 0)
				syslog(LOG_NOTICE, "[TES:%02d RCV] recv error = %s",
				                   cepid, itron_strerror(rlen));
			break;
			}
		head = *rptr;
		tail = *(rptr + rlen - 1);
#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TES:%02d RCV] len: %4d, data %02x -> %02x",
		                   cepid, (uint16_t)rlen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
		rcv_count ++;
		rcv_total += rlen;

		syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* ��M�|�C���^��i�߂�B*/
		if (rptr - buffer + rlen >= sizeof(buffer))
			rptr -= sizeof(buffer) - rlen;
		else
			rptr += rlen;

		/* �o�b�t�@���̕������𑝂₷�B*/
		last   =     chars;
		chars += (uint16_t)rlen;

 				/* �o�b�t�@���ɕ���������΁A���M�^�X�N���N������B*/
		if (last == 0 && chars > 0)
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 				/* �o�b�t�@���ɋ󂫂�����΁A��M�^�X�N���N������B*/
		if (sizeof(buffer) - chars > 0)
			sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);

		syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

		/* �o�b�t�@�ɋ󂫂��ł���܂ő҂B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_RCV_READY));
		}

	/* ��M���� */
	ena_rcv = false;

	/* ��M�o�b�t�@�ɕ���������̂�҂��Ă��鑗�M�^�X�N���N������B*/
	if (chars == 0)
		sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

	/* �R�l�N�V�����̐ؒf����������܂ő҂B*/
	syscall(wai_sem(SEM_TCP_ECHO_SRV_CLS_READY));

	return error;
	}

/*
 *  TCP ECHO �T�[�o���M�^�X�N
 */

void
tcp_echo_srv_snd_task(intptr_t exinf)
{
	ID		tskid, cepid;
	ER		error;
	ER_UINT		slen;
	SYSTIM		now;
	uint16_t	blen, last;
	char		head, tail;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV SND:%d] started.", tskid);
	while (true) {
		if ((error = rcv_dtq(DTQ_TCP_ECHO_SRV_SND, (intptr_t*)&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TES:%02d SND] sync error: %s",
			                   cepid, itron_strerror(error));
			continue;
			}

		while (true) {

			/* �o�b�t�@�ɕ���������܂ő҂B*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_SND_READY));

			/* ��M�����ŁA�o�b�t�@�ɕ������Ȃ���ΏI������B*/
			if (!ena_rcv && chars == 0)
				break;

			/* ���M�T�C�Y���v�Z����B*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));
			if (rptr > sptr)
				blen = rptr - sptr;
			else
				blen = sizeof(buffer) - (sptr - buffer);
			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));

			if ((slen = tcp_snd_dat(cepid, sptr, blen, TMO_FEVR)) <= 0) {
				syslog(LOG_NOTICE, "[TES:%02d SND] send error = %s", cepid, itron_strerror(slen));
				break;
				}

			head = *sptr;
			tail = *(sptr + slen - 1);
#ifdef SHOW_RCV_RANGE
			syslog(LOG_NOTICE, "[TES:%02d SND] len: %4d, data %02x -> %02x",
			                   cepid, (uint16_t)slen, head, tail);
#endif	/* of #ifdef SHOW_RCV_RANGE */
			snd_count ++;
			snd_total += slen;

			syscall(wai_sem(SEM_TCP_ECHO_SRV_LOCK));

			/* ���M�|�C���^��i�߂�B*/
			if (sptr - buffer + slen >= sizeof(buffer))
				sptr -= sizeof(buffer) - slen;
			else
				sptr += slen;

			/* �o�b�t�@���̕����������炷�B*/
			last   =     chars;
			chars -= (uint16_t)slen;

			/* ��M�����ŁA�o�b�t�@�ɕ������Ȃ���ΏI������B*/
			if (!ena_rcv && chars == 0) {
				syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
				break;
				}

 			/* �o�b�t�@���ɕ���������΁A���M�^�X�N���N������B*/
			if (chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

 			/* ��M�\�ŁA�o�b�t�@���ɋ󂫂��ł���΁A��M�^�X�N���N������B*/
			if (ena_rcv && last == sizeof(buffer) && sizeof(buffer) - chars > 0)
				sig_sem(SEM_TCP_ECHO_SRV_RCV_READY);

			syscall(sig_sem(SEM_TCP_ECHO_SRV_LOCK));
			}

		/* ��M�o�b�t�@�ɋ󂪂ł����҂��Ă����M�^�X�N���N������B*/
		if (chars == sizeof(buffer))
			sig_sem(SEM_TCP_ECHO_SRV_SND_READY);

#ifdef USE_TCP_SHT_CEP
		if ((error = tcp_sht_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d SND] shtudown error = %s", cepid, itron_strerror(error));
#endif	/* of #ifdef USE_TCP_SHT_CEP */

		if ((error = tcp_cls_cep(cepid, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d SND] close error = %s", cepid, itron_strerror(error));

		get_tim(&now);
		syslog(LOG_NOTICE, "[TES:%02d SND] finished:   %6ld, snd: %4d, rcv: %4d, len: %ld",
		                   cepid, now / SYSTIM_HZ, snd_count, rcv_count, snd_total);

		sig_sem(SEM_TCP_ECHO_SRV_CLS_READY);

		pol_sem(SEM_TCP_ECHO_SRV_SND_READY);
		pol_sem(SEM_TCP_ECHO_SRV_RCV_READY);
		}
	}

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifdef USE_TCP_EXTENTIONS

/*
 *  get_tcp_rep -- TCP ��t�����l������B
 */

static ER
get_tcp_rep (ID *repid)
{
	ID		tskid;
	T_TCP_CREP	crep;

	get_tid(&tskid);

	crep.repatr = UINT_C(0);
	crep.myaddr.portno = UINT_C(7);

#if defined(SUPPORT_INET4)
	crep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
	memcpy(&crep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

	return alloc_tcp_rep(repid, tskid, &crep);
	}

/*
 *  get_tcp_cep -- TCP �ʐM�[�_���l������B
 */

static ER
get_tcp_cep (ID *cepid)
{
	ID		tskid;
	T_TCP_CCEP	ccep;

	get_tid(&tskid);

	ccep.cepatr = UINT_C(0);
	ccep.sbufsz = TCP_ECHO_SRV_SWBUF_SIZE;
	ccep.rbufsz = TCP_ECHO_SRV_RWBUF_SIZE;

#ifdef TCP_CFG_SWBUF_CSAVE
	ccep.sbuf = NADR;
#else
	ccep.sbuf = tcp_echo_srv_swbuf;
#endif
#ifdef TCP_CFG_RWBUF_CSAVE
	ccep.rbuf = NADR;
#else
	ccep.rbuf = tcp_echo_srv_rwbuf;
#endif
#ifdef USE_TCP_NON_BLOCKING
	ccep.callback = (FP)callback_nblk_tcp_echo_srv;
#else
	ccep.callback = NULL;
#endif

	return alloc_tcp_cep(cepid, tskid, &ccep);
	}

/*
 *  TCP ECHO �T�[�o��M�^�X�N
 */

void
tcp_echo_srv_rcv_task (intptr_t exinf)
{
	ID	tskid, cepid, repid;
	ER	error = E_OK;

	syscall(get_tid(&tskid));
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d] started.", tskid);
	while (true) {

		syscall(slp_tsk());
		if ((error = get_tcp_cep (&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TES:00 EXT] CEP create error: %s", itron_strerror(error));
			continue;
			}

		while (true) {

			if ((error = get_tcp_rep (&repid)) != E_OK) {
				syslog(LOG_NOTICE, "[TES:00 EXT] REP create error: %s", itron_strerror(error));
				break;
				}
			else if ((error = tcp_echo_srv_rcv(cepid, repid)) != E_OK) {
				error = free_tcp_rep(repid, error != E_DLT);
				break;
				}
			}

		if ((error = free_tcp_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TES:%02d EXT] CEP delete error: %s", cepid, itron_strerror(error));

		}
	}

#else	/* of #ifdef USE_TCP_EXTENTIONS */

void
tcp_echo_srv_rcv_task(intptr_t exinf)
{
	ID	tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV RCV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		while (tcp_echo_srv_rcv((ID)exinf, TCP_ECHO_SRV_REPID) == E_OK)
			;
		}
	}

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

#endif	/* of #ifdef USE_TCP_ECHO_SRV2 */
