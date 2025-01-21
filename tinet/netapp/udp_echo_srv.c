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
 *  @(#) $Id: udp_echo_srv.c,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

/* 
 *  UDP ECHO �T�[�o
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/net.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/echo.h>

#ifdef USE_UDP_ECHO_SRV

/*
 *  ��M�^�C���A�E�g
 */

#define RCV_TMOUT	TMO_FEVR
//#define RCV_TMOUT	(30*ULONG_C(1000))

#define BUF_SIZE	2048

static char	echo_rcv_buf[BUF_SIZE];
static T_IPEP	dst;

#ifdef USE_UDP_CALL_BACK

/*
 *  �R�[���o�b�N�֐�
 */

ER
callback_udp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	ER_UINT	len;
	SYSTIM	now;

	if ((len = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), TMO_FEVR)) >= 0) {
		echo_rcv_buf[len] = '\0';
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d UCB] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		if (len > 0) {
			len = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, len, TMO_FEVR);
			get_tim(&now);
			if (len >= 0)
				syslog(LOG_NOTICE, "[UES:%02d UCB] sent,       %6ld, len: %d",
				                   cepid, now / SYSTIM_HZ, len);
			else
				syslog(LOG_NOTICE, "[UES:%02d UCB] send error, %6ld: %s",
				                   cepid, now / SYSTIM_HZ, itron_strerror(len));
			}
		len = E_OK;
		}
	else {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d UCB] recv error, %6ld: %s",
		                   cepid, now / SYSTIM_HZ, itron_strerror(len));
		}

	return len;
	}

#else	/* of #ifdef USE_UDP_CALL_BACK */

#ifdef USE_UDP_NON_BLOCKING

/*
 *  �ϐ�
 */

static ER_UINT		nblk_len;

/*
 *  �m���u���b�L���O�R�[���̃R�[���o�b�N�֐�
 */

ER
callback_nblk_udp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	SYSTIM	now;

	get_tim(&now);
	nblk_len = *(ER_UINT*)p_parblk;
	if (nblk_len < 0) {	/* 0 �ȉ��̏ꍇ�́A�G���[�R�[�h */
		syslog(LOG_NOTICE, "[UES:%02d CBR] error,      %6ld: %s, fncd: %s",
		                   cepid, now / SYSTIM_HZ, itron_strerror(nblk_len), in_strtfn(fncd));
		}
	else if (fncd == TFN_UDP_RCV_DAT) {
		echo_rcv_buf[nblk_len] = '\0';
		syslog(LOG_NOTICE, "[UES:%02d CBR] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		}
	syscall(wup_tsk(UDP_ECHO_SRV_TASK));
	return E_OK;
	}

/*
 *  UDP ECHO �T�[�o
 */

ER
udp_echo_srv (ID cepid)
{
	ER	error;
	SYSTIM	now;

	if ((error = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), TMO_NBLK)) != E_WBLK) {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d RCV] recv error, %6ld: %s", cepid, now / SYSTIM_HZ, itron_strerror(error));
		return error;
		}

	syscall(slp_tsk());
	if (nblk_len < 0)
		error = nblk_len;
	else {
		if ((error = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, nblk_len, TMO_NBLK)) != E_WBLK) {
			get_tim(&now);
			syslog(LOG_NOTICE, "[UES:%02d SND] send error, %6ld: %s",
			                   cepid, now / SYSTIM_HZ, itron_strerror(error));
			return error;
			}

		syscall(slp_tsk());
		if (nblk_len < 0)
			error = nblk_len;
		else {
			get_tim(&now);
			syslog(LOG_NOTICE, "[UES:%02d SND] sent,       %6ld, len: %d", cepid, now / SYSTIM_HZ, nblk_len);
			error = E_OK;
			}
		}

	return error;
	}

#else	/* of #ifdef USE_UDP_NON_BLOCKING */

/*
 *  UDP ECHO �T�[�o
 */

ER
udp_echo_srv (ID cepid)
{
	ER_UINT	len;
	SYSTIM	now;

	if ((len = UDP_RCV_DAT(cepid, &dst, echo_rcv_buf, sizeof(echo_rcv_buf), RCV_TMOUT)) >= 0) {
		get_tim(&now);
		echo_rcv_buf[len] = '\0';
		syslog(LOG_NOTICE, "[UES:%02d RCV] received,   %6ld, from: %s.%d,\n"
		                   "                                 msg: '%s'",
		                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno, echo_rcv_buf);
		if (len > 0) {
			len = UDP_SND_DAT(cepid, &dst, echo_rcv_buf, len, TMO_FEVR);
			get_tim(&now);
			if (len >= 0)
				syslog(LOG_NOTICE, "[UES:%02d SND] sent,       %6ld, len: %d",
				                   cepid, now / SYSTIM_HZ, (uint16_t)len);
			else
				syslog(LOG_NOTICE, "[UES:%02d SND] send error, %6ld: %s",
				                   cepid, now / SYSTIM_HZ, itron_strerror(len));
			}
		}
	else {
		get_tim(&now);
		syslog(LOG_NOTICE, "[UES:%02d RCV] recv error, %6ld: %s", cepid, now / SYSTIM_HZ, itron_strerror(len));
		}

	return len >= 0 || len == E_TMOUT ? E_OK : len;
	}

#endif	/* of #ifdef USE_UDP_NON_BLOCKING */

/*
 *  UDP ECHO �T�[�o�^�X�N
 */

#ifdef USE_UDP_EXTENTIONS

void
udp_echo_srv_task (intptr_t exinf)
{
	ID		tskid, cepid;
	ER		error;
	T_UDP_CCEP	ccep;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {

		syscall(slp_tsk());

		ccep.cepatr = UINT_C(0);
		ccep.myaddr.portno = UINT_C(7);

#if defined(SUPPORT_INET4)
		ccep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
		memcpy(&ccep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

#ifdef USE_UDP_NON_BLOCKING
		ccep.callback = (FP)callback_nblk_udp_echo_srv;
#else
		ccep.callback = NULL;
#endif

		if ((error = alloc_udp_cep(&cepid, tskid, &ccep)) != E_OK) {
			syslog(LOG_NOTICE, "[UES:%02d TSK] CEP create error: %s", cepid, itron_strerror(error));
			continue;
			}

		while (error == E_OK) {
			if ((error = udp_echo_srv(cepid)) != E_OK) {
				if ((error = free_udp_cep(cepid, !(error == E_NOEXS || error == E_DLT))) != E_OK)
					syslog(LOG_NOTICE, "[UEC:%02d TSK] CEP delete error: %s", cepid, itron_strerror(error));
				break;
				}
			}

		}
	slp_tsk();
	}

#else	/* of #ifdef USE_UDP_EXTENTIONS */

void
udp_echo_srv_task (intptr_t exinf)
{
	ID	tskid;
	ER	error = E_OK;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (error == E_OK) {
		error = udp_echo_srv((ID)exinf);
		}
	slp_tsk();
	}

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

#endif	/* of #ifdef USE_UDP_CALL_BACK */

#endif	/* of #ifdef USE_UDP_ECHO_SRV */
