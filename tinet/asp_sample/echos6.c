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
 *  @(#) $Id: echos6.c,v 1.5 2009/12/24 06:20:39 abe Exp $
 */

/* 
 *  IPv6�ATCP ECHO �T�[�o�A����M�^�X�N����^
 */

#include <string.h>

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "echos6.h"

/*
 *  �O���֐��̒�`
 */

extern const char *itron_strerror (ER ercd);

/*
 *  ����:
 *
 *    BUF_SIZE �� TCP ��
 *    ���M�E�C���h�E�o�b�t�@�T�C�Y + ��M�E�C���h�E�o�b�t�@�T�C�Y�� 
 *    3/2 �{�ȏ�̑傫�����Ȃ���΁A�f�b�h���b�N����\��������B
 */

#define BUF_SIZE	((TCP_ECHO_SRV_SWBUF_SIZE + \
                          TCP_ECHO_SRV_RWBUF_SIZE) * 3 / 2)

static T_IPV6EP		dst;

#ifdef USE_TCP_NON_BLOCKING

static ER		nblk_error = E_OK;
static ER_UINT		nblk_slen  = 0;
static ER_UINT		nblk_rlen  = 0;

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifndef USE_COPYSAVE_API

static uint8_t 		buffer[BUF_SIZE];

#endif	/* of #ifndef USE_COPYSAVE_API */

/*
 *  TCP ����M�o�b�t�@
 */

uint8_t tcp_echo_srv_swbuf[TCP_ECHO_SRV_SWBUF_SIZE];
uint8_t tcp_echo_srv_rwbuf[TCP_ECHO_SRV_RWBUF_SIZE];

#ifdef USE_TCP_NON_BLOCKING

/*
 *  �m���u���b�L���O�R�[���̃R�[���o�b�N�֐�
 */

ER
callback_nblk_tcp_echo_srv (ID cepid, FN fncd, void *p_parblk)
{
	ER	error = E_OK;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		nblk_error = *(ER*)p_parblk;
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_DAT:
		if ((nblk_rlen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] recv err: %s", itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_SND_DAT:
		if ((nblk_slen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] send err: %s", itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_CLS_CEP:
		if ((nblk_error = *(ER*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] clse err: %s", itron_strerror(nblk_error));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_RCV_BUF:
		if ((nblk_rlen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] rbuf err: %s", itron_strerror(nblk_rlen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_GET_BUF:
		if ((nblk_slen = *(ER_UINT*)p_parblk) < 0)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CBN] sbuf err: %s", itron_strerror(nblk_slen));
		syscall(sig_sem(SEM_TCP_ECHO_SRV_NBLK_READY));
		break;

	case TFN_TCP_CON_CEP:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		break;
		}
	return error;
	}

#ifdef USE_COPYSAVE_API

void
tcp_echo_srv_task(intptr_t exinf)
{
	ID		tskid;
	ER		error = E_OK;
	uint32_t	total;
	uint16_t	rblen, sblen, rlen, slen, soff, count;
	char		*rbuf, *sbuf, head, tail;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK):%d,%d] (copy save API) started.", tskid, (int_t)exinf);
	while (true) {
		if ((error = tcp6_acp_cep((int_t)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(error));
			continue;
			}

		/* ���肩��ڑ������܂ő҂B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		if (nblk_error == E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] connected from %s:%d", ipv62str(NULL, &dst.ipaddr), dst.portno);
		else {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(nblk_error));
			continue;
			}

		total = rlen = count = 0;
		while (true) {
			if ((error = tcp_rcv_buf((int_t)exinf, (void **)&rbuf, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s", itron_strerror(error));
				break;
				}

			/* ��M����܂ő҂B*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

			if (nblk_rlen < 0) {		/* �G���[ */
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s", itron_strerror(nblk_rlen));
				break;
				}
			else if (nblk_rlen == 0)	/* ��M�I�� */
				break;

			rblen = (uint16_t)nblk_rlen;

			/* �o�b�t�@�̎c��ɂ��A��M���𒲐�����B*/
			if (rblen > BUF_SIZE - rlen)
				rblen = BUF_SIZE - rlen;
			total += rblen;
			rlen   = rblen;

			head = *rbuf;
			tail = *(rbuf + rblen - 1);
			count ++;
			/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] "
			                   "count: %4d, len: %4d, data %02x -> %02x",
			                   ++ count, rblen, head, tail);*/
			memcpy(buffer, rbuf, rblen);

			if ((error = tcp_rel_buf((int_t)exinf, rlen)) < 0) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) REL] error: %s",
				                   itron_strerror(error));
				break;
				}

			soff = 0;
			while (rlen > 0) {

				if ((error = tcp_get_buf((int_t)exinf, (void **)&sbuf, TMO_NBLK)) != E_WBLK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) GET] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}

				/* ���M�o�b�t�@�̊l������������܂ő҂B*/
				syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

				if (nblk_slen < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) GET] error: %s",
					                   itron_strerror(nblk_slen));
					goto err_fin;
					}
				else
					/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) GET] len: %d", nblk_slen)*/;

				sblen = (uint16_t)nblk_slen;
				slen = sblen < rlen ? sblen : rlen;
				memcpy(sbuf, buffer + soff, slen);

				if ((error = tcp_snd_buf((int_t)exinf, slen)) != E_OK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] len: %d", slen);*/

				rlen -= slen;
				soff += slen;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((int_t)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((int_t)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CLS] error: %s", itron_strerror(error));

		/* �J������������܂ő҂B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) FIN] finished, total count: %d, len: %d", count, total);
		}
	}

#else	/* of #ifdef USE_COPYSAVE_API */

void
tcp_echo_srv_task(intptr_t exinf)
{
	ID		tskid;
	ER		error;
	uint32_t	total;
	uint16_t	rlen, slen, soff, count;
	char		head, tail;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK):%d,%d] started.", tskid, (int_t)exinf);
	while (true) {
		if ((error = tcp6_acp_cep((int_t)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_NBLK)) != E_WBLK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(error));
			continue;
			}

		/* ���肩��ڑ������܂ő҂B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		if (nblk_error == E_OK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] connected from %s:%d",
			                   ipv62str(NULL, &dst.ipaddr), dst.portno);
			}
		else {
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) ACP] error: %s", itron_strerror(nblk_error));
			continue;
			}

		count = total = 0;
		while (true) {
			if ((error = tcp_rcv_dat((int_t)exinf, buffer, BUF_SIZE - 1, TMO_NBLK)) != E_WBLK) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s",
				                   itron_strerror(error));
				break;
				}

			/* ��M�����܂ő҂B*/
			syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

			if (nblk_rlen < 0) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] error: %s",
				                   itron_strerror(nblk_rlen));
				break;
				}
			else if (nblk_rlen == 0)
				break;

			rlen   = (uint16_t)nblk_rlen;
			total += (uint32_t)nblk_rlen;
			head = *buffer;
			tail = *(buffer + rlen - 1);
			count ++;
			/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) RCV] count: %4d, len: %4d, data %02x -> %02x",
			                   ++ count, rlen, head, tail);*/
			soff = 0;
			while (rlen > 0) {
				if ((error = tcp_snd_dat((int_t)exinf, &buffer[soff], rlen, TMO_NBLK)) != E_WBLK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}

				/* ���M�����܂ő҂B*/
				syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

				if (nblk_slen < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] error: %s",
					                   itron_strerror(nblk_slen));
					goto err_fin;
					}
				else
					/*syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SND] len: %4d", nblk_slen)*/;

				slen = (uint16_t)nblk_slen;
				rlen -= slen;
				soff += slen;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((int_t)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((int_t)exinf, TMO_NBLK)) != E_WBLK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) CLS] error: %s", itron_strerror(error));

		/* �J������������܂ő҂B*/
		syscall(wai_sem(SEM_TCP_ECHO_SRV_NBLK_READY));

		syslog(LOG_NOTICE, "[TCP ECHO SRV (NBLK) FIN] finished, total cnt: %d, len: %d", count, total);
		}
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

#else	/* of #ifdef USE_TCP_NON_BLOCKING */

#ifdef USE_COPYSAVE_API

void
tcp_echo_srv_task(intptr_t exinf)
{
	ID		tskid;
	ER_UINT		rblen, sblen;
	ER		error = E_OK;
	uint32_t	total;
	uint16_t	rlen, slen, soff, count;
	char		*rbuf, *sbuf, head, tail;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d,%d] (copy save API) started.", tskid, (int_t)exinf);
	while (true) {
		if (tcp6_acp_cep((int_t)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_FEVR) != E_OK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] error: %s", itron_strerror(error));
			continue;
			}

		total = count = 0;
		syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] connected from %s:%d", ipv62str(NULL, &dst.ipaddr), dst.portno);
		while (true) {
			if ((rblen = tcp_rcv_buf((int_t)exinf, (void **)&rbuf, TMO_FEVR)) <= 0) {
				if (rblen != E_OK)
					syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] error: %s", itron_strerror(rblen));
				break;
				}

			rlen   = (uint16_t)rblen;
			total += (uint32_t)rblen;
			head = *rbuf;
			tail = *(rbuf + rlen - 1);
			count ++;
			/*syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] count: %4d, len: %4d, data %02x -> %02x",
			       ++ count, rlen, head, tail);*/

			soff = 0;
			while (rlen > 0) {

				if ((sblen = tcp_get_buf((int_t)exinf, (void **)&sbuf, TMO_FEVR)) < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV GET] error: %s",
					                   itron_strerror(sblen));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV GET] len: %d", sblen);*/
			
				slen = rlen < (uint16_t)sblen ? rlen : (uint16_t)sblen;
				memcpy(sbuf, rbuf + soff, slen);
				if ((error = tcp_snd_buf((int_t)exinf, slen)) != E_OK) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV SND] error: %s",
					                   itron_strerror(error));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV SND] len: %d", slen);*/

				rlen -= slen;
				soff += slen;
				}

			if ((error = tcp_rel_buf((int_t)exinf, rblen)) < 0) {
				syslog(LOG_NOTICE, "[TCP ECHO SRV REL] error: %s", itron_strerror(error));
				break;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((int_t)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((int_t)exinf, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV CLS] error: %s", itron_strerror(error));

		syslog(LOG_NOTICE, "[TCP ECHO SRV FIN] finished, total cnt: %d, len: %d", count, total);
		}
	}

#else	/* of #ifdef USE_COPYSAVE_API */

void
tcp_echo_srv_task(intptr_t exinf)
{
	ID		tskid;
	ER_UINT		rlen, slen;
	ER		error = E_OK;
	uint16_t	soff, count, total;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d,%d] started.", tskid, (int_t)exinf);
	while (true) {
		if (tcp6_acp_cep((int_t)exinf, TCP_ECHO_SRV_REPID, &dst, TMO_FEVR) != E_OK) {
			syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] error: %s", itron_strerror(error));
			continue;
			}

		total = count = 0;
		syslog(LOG_NOTICE, "[TCP ECHO SRV ACP] connected from %s:%d",
		                   ipv62str(NULL, &dst.ipaddr), dst.portno);
		while (true) {
			if ((rlen = tcp_rcv_dat((int_t)exinf, buffer, BUF_SIZE - 1, TMO_FEVR)) <= 0) {
				if (rlen != E_OK)
					syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] error: %s",
					                   itron_strerror(rlen));
				break;
				}

			/*syslog(LOG_NOTICE, "[TCP ECHO SRV RCV] count: %4d, len: %4d, data %02x -> %02x",
			       ++ count, (uint16_t)rlen, *buffer, *(buffer + rlen - 1));*/
			count ++;
			total += (uint16_t)rlen;
			soff = 0;
			while (rlen > 0) {
				if ((slen = tcp_snd_dat((int_t)exinf, &buffer[soff], rlen, TMO_FEVR)) < 0) {
					syslog(LOG_NOTICE, "[TCP ECHO SRV SND] error: %s",
					                   itron_strerror(slen));
					goto err_fin;
					}
				/*syslog(LOG_NOTICE, "[TCP ECHO SRV SND] len: %d", slen);*/
				rlen -=     slen;
				soff += (uint16_t)slen;
				}
			}
	err_fin:

		if ((error = tcp_sht_cep((int_t)exinf)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV SHT] error: %s", itron_strerror(error));

		if ((error = tcp_cls_cep((int_t)exinf, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[TCP ECHO SRV CLS] error: %s", itron_strerror(error));

		syslog(LOG_NOTICE, "[TCP ECHO SRV FIN] finished, total cnt: %d, len: %d", count, total);
		}
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

#endif	/* of #ifdef USE_TCP_NON_BLOCKING */
