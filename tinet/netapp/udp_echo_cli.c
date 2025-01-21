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
 *  @(#) $Id: udp_echo_cli.c,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

/* 
 *  UDP ECHO �N���C�A���g
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
#include <net/net_var.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/echo.h>

#ifdef USE_UDP_ECHO_CLI

/* echo �T�[�o�̃|�[�g�ԍ� */

#define ECHO_SRV_PORTNO		UINT_C(7)

/*
 *  �S��ϐ�
 */

bool_t udp_echo_cli_valid;

/*
 * �ϐ�
 */

#define BUF_SIZE	2048

static char		udp_buf[BUF_SIZE];
static T_IPEP		dst;

#ifdef USE_UDP_NON_BLOCKING

static ER_UINT		nblk_len;

/*
 *  �m���u���b�L���O�R�[���̃R�[���o�b�N�֐�
 */

ER
callback_nblk_udp_echo_cli (ID cepid, FN fncd, void *p_parblk)
{
	nblk_len = *(ER_UINT*)p_parblk;
	syscall(wup_tsk(UDP_ECHO_CLI_TASK));
	return E_OK;
	}

/*
 *  send_udp_echo -- ECHO/UDP �T�[�o�Ƀ��b�Z�[�W�𑗐M���� (�m���u���b�L���O�R�[���g�p)�B
 */

static ER
send_udp_echo (ID cepid, T_IN_ADDR *ipaddr, uint16_t portno, char *line)
{
	ER_UINT	error;
	uint_t	len;

	dst.ipaddr = *ipaddr;
	dst.portno = portno;
	len         = strlen(line);
	if ((error = UDP_SND_DAT(cepid, &dst, line, len, TMO_NBLK)) != E_WBLK) {
		syslog(LOG_NOTICE, "[UEC:%02d SND] error: %s", cepid, itron_strerror(error));
		return error;
		}
	else
		syslog(LOG_NOTICE, "[UEC:%02d SND] sending:            to:   %s.%d: %s",
		                   cepid, IP2STR(NULL, &dst.ipaddr), dst.portno, line);

	syscall(slp_tsk());
	if (nblk_len < 0) {	/* 0 �ȉ��̏ꍇ�́A�G���[�R�[�h */
		syslog(LOG_NOTICE, "[UEC:%02d CBR] error: %s", cepid, itron_strerror(nblk_len));
		return nblk_len;
		}

	if ((error = UDP_RCV_DAT(cepid, &dst, udp_buf, sizeof(udp_buf), TMO_NBLK)) != E_WBLK) {
		syslog(LOG_NOTICE, "[UEC:%02d RCV] error: %s", cepid, itron_strerror(error));
		return error;
		}

	syscall(slp_tsk());
	if (nblk_len < 0) {	/* 0 �ȉ��̏ꍇ�́A�G���[�R�[�h */
		syslog(LOG_NOTICE, "[UEC:%02d RCV] error: %s", cepid, itron_strerror(nblk_len));
		return nblk_len;
		}
	else {
		udp_buf[nblk_len] = '\0';
		syslog(LOG_NOTICE, "[UEC:%02d RCV] received:           from: %s.%d: %s",
		                   cepid, IP2STR(NULL, &dst.ipaddr), dst.portno, udp_buf);
		nblk_len = E_OK;
		}

	return nblk_len;
	}

#else	/* of #ifdef USE_UDP_NON_BLOCKING */

#ifdef USE_UDP_CALL_BACK

/*
 *  �R�[���o�b�N�֐�
 */

ER
callback_udp_echo_cli (ID cepid, FN fncd, void *p_parblk)
{
	ER_UINT	len;

	if ((len = UDP_RCV_DAT(cepid, &dst, udp_buf, sizeof(udp_buf), TMO_FEVR)) >= 0) {
		*(udp_buf + len) = '\0';
		syslog(LOG_NOTICE, "[UEC:%02d RCV] recv: addr: %s.%d: %s",
		                   cepid, IP2STR(NULL, &dst.ipaddr), dst.portno, udp_buf);
		}
	else
		syslog(LOG_NOTICE, "[UEC:%02d RCV] recv: error: %s", cepid, itron_strerror(len));

	return E_OK;
	}

/*
 *  send_udp_echo -- ECHO/UDP �T�[�o�Ƀ��b�Z�[�W�𑗐M���� (�R�[���o�b�N�֐��g�p)�B
 */

static ER
send_udp_echo (ID cepid, T_IN_ADDR *ipaddr, uint16_t portno, char *line)
{
	ER_UINT	len;

	dst.ipaddr = *ipaddr;
	dst.portno = portno;
	len        = strlen(line);
	syslog(LOG_NOTICE, "[UEC:%02d SND] sending:            to:   %s.%d: %s",
	                   cepid, IP2STR(NULL, &dst.ipaddr), dst.portno, line);
	if ((len = UDP_SND_DAT(cepid, &dst, line, len, TMO_FEVR)) < 0)
		syslog(LOG_NOTICE, "[UEC:%02d SND] error: %s", cepid, itron_strerror(len));

	return E_OK;
	}

#else	/* of #ifdef USE_UDP_CALL_BACK */

/*
 *  send_udp_echo -- ECHO/UDP �T�[�o�Ƀ��b�Z�[�W�𑗐M���� (�R�[���o�b�N�֐����g�p)�B
 */

static ER
send_udp_echo (ID cepid, T_IN_ADDR *ipaddr, uint16_t portno, char *line)
{
	ER_UINT	len;

	dst.ipaddr = *ipaddr;
	dst.portno = portno;
	len         = strlen(line);
	syslog(LOG_NOTICE, "[UEC:%02d SND] sending:            to:   %s.%d: %s",
	                   cepid, IP2STR(NULL, &dst.ipaddr), dst.portno, line);
	if ((len = UDP_SND_DAT(cepid, &dst, line, len, TMO_FEVR)) < 0) {
		syslog(LOG_NOTICE, "[UEC:%02d SND] error: %s", cepid, itron_strerror(len));
		return len;
		}

	if ((len = UDP_RCV_DAT(cepid, &dst, udp_buf, sizeof(udp_buf), 10*1000)) >= 0) {
		*(udp_buf + len) = '\0';
		syslog(LOG_NOTICE, "[UEC:%02d RCV] received:           from: %s.%d: %s",
		                   cepid, IP2STR(NULL, &dst.ipaddr), dst.portno, line);
		return E_OK;
		}
	else {
		syslog(LOG_NOTICE, "[UEC:%02d RCV] error: %s", cepid, itron_strerror(len));
		return len;
		}
	}

#endif	/* of #ifdef USE_UDP_CALL_BACK */

#endif	/* of #ifdef USE_UDP_NON_BLOCKING */

#define MESSAGE_FORMAT	"MSG 1000000"

/*
 *  UDP ECHO �N���C�A���g���M�^�X�N
 */

void
udp_echo_cli_task (intptr_t exinf)
{
	static char msg[sizeof(MESSAGE_FORMAT)] = MESSAGE_FORMAT;

	T_IN_ADDR	addr;
	ID		tskid, cepid;
	ER		error = E_OK;
	char		*line, *p;
	int_t		rep;
	uint32_t	count, msgno;
	uint16_t	portno;

#ifdef USE_UDP_EXTENTIONS

	T_UDP_CCEP	ccep;

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO CLI:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		if (rcv_dtq(DTQ_UDP_ECHO_CLI, (intptr_t*)&line) == E_OK) {

#ifdef USE_UDP_EXTENTIONS

			ccep.cepatr = UINT_C(0);
			ccep.myaddr.portno = UDP_PORTANY;

#if defined(SUPPORT_INET4)
			ccep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
			memcpy(&ccep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

#ifdef USE_UDP_NON_BLOCKING
			ccep.callback = (FP)callback_nblk_udp_echo_cli;
#else
			ccep.callback = NULL;
#endif

			if ((error = alloc_udp_cep(&cepid, tskid, &ccep)) != E_OK) {
				syslog(LOG_NOTICE, "[UEC:%02d TSK] CEP create error: %s", cepid, itron_strerror(error));
				continue;
				}

#else	/* of #ifdef USE_UDP_EXTENTIONS */

			cepid = (ID)exinf;

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

			line = skip_blanks(GET_IPADDR(&addr, skip_blanks(line)));	/* IP Address */

			if ('0' <= *line && *line <= '9') {				/* Port No */
				line = get_int(&rep, line);
				portno = (uint16_t)rep;
				}
			else {
				line ++;
				portno = ECHO_SRV_PORTNO;
				}

			line = skip_blanks(line);
			if ('0' <= *line && *line <= '9') {				/* Repeat */
				line = get_int(&rep, line);
				if (rep > 1000000)
					rep = 1000000;
				udp_echo_cli_valid = true;
				for (count = 0;  count ++ < rep; ) {
					if (!udp_echo_cli_valid) {
						syslog(LOG_NOTICE, "[UEC:%02d TSK] canceled.", cepid);
						break;
						}
						
					p = &msg[sizeof(MESSAGE_FORMAT)] - 1;
					for (msgno = count; msgno > 0; msgno /= 10)
						*(-- p) = msgno % 10 + '0';
					while (*(p - 2) != 'G')
						*(-- p) = ' ';

					if ((error = send_udp_echo(cepid, &addr, portno, msg)) != E_OK)
						break;

					dly_tsk(10 * SYSTIM_HZ + net_rand() % (10 * SYSTIM_HZ));
					}
				}

			else								/* Single Message */
				error = send_udp_echo(cepid, &addr, portno, line);

			if (error != E_OK)
				syslog(LOG_NOTICE, "[UEC:%02d TSK] error: %s", cepid, itron_strerror(error));

#ifdef USE_UDP_EXTENTIONS

			if ((error = free_udp_cep(cepid, !(error == E_NOEXS || error == E_DLT))) != E_OK)
				syslog(LOG_NOTICE, "[UEC:%02d TSK] CEP delete error: %s", cepid, itron_strerror(error));

#endif	/* of #ifdef USE_UDP_EXTENTIONS */

			}
		}
	}

#endif	/* of #ifdef USE_UDP_ECHO_CLI */
