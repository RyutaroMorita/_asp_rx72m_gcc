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
 *  @(#) $Id: tcp_discard_srv.c,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

/* 
 *  DISCARD �T�[�o
 *
 *    �E�ȃR�s�[ API
 *    �EIPv4
 *    �EIPv6
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "tinet_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <t_services.h>
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/discard.h>

#ifdef USE_TCP_DISCARD_SRV

/*
 *  �\��
 */

//#define SHOW_RCV_RANGE
//#define SHOW_RCV_DATA

/*
 *  �S��ϐ�
 */

/* TCP ����M�E�B���h�o�b�t�@ */

#ifndef TCP_CFG_RWBUF_CSAVE_ONLY
uint8_t tcp_discard_srv_rwbuf[TCP_DISCARD_SRV_RWBUF_SIZE];
#endif

/*
 *  TCP DISCARD �T�[�o�^�X�N
 */

#define BUF_SIZE	TCP_DISCARD_SRV_RWBUF_SIZE

#ifdef USE_COPYSAVE_API

static ER
tcp_discard_srv (ID cepid, ID repid)
{
	T_IPEP		dst;
	ER_UINT		rlen;
	ER		error;
	SYSTIM		time;
	uint32_t	total;
	uint16_t	count;
	uint8_t		*buf;

#ifdef SHOW_RCV_DATA
	uint_t	ix;
#endif	/* of #ifdef SHOW_RCV_DATA */

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d ACP] accept error: %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	count = total = 0;
	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] connected:  %6ld, from: %s.%d",
	                   cepid, time / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	while ((rlen = tcp_rcv_buf(cepid, (void*)&buf, TMO_FEVR)) > 0) {
		count ++;

#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TDS:%02d RCV] count: %4d, len: %4d, data: %02x -> %02x",
		       cepid, count, (uint16_t)rlen, *buf, *(buf + rlen - 1));
#endif	/* of #ifdef SHOW_RCV_RANGE */

#ifdef SHOW_RCV_DATA
		for (ix = 0; ix < rlen; ix ++)
			cons_putchar(CONSOLE_PORTID,  *(buf + ix));
#endif	/* of #ifdef SHOW_RCV_DATA */

		if ((error = tcp_rel_buf(cepid, rlen)) != E_OK) {
			syslog(LOG_NOTICE, "[TDS:%02d RCV] rel buf error: %s",
			                    cepid, itron_strerror(error));
			rlen = 0;
			break;
			}
		total += rlen;
		}

	if (rlen != 0)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] recv buf error: %s", cepid, itron_strerror(rlen));

	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] shutdown error: %s", cepid, itron_strerror(error));

	if ((error = tcp_cls_cep(cepid, TMO_FEVR)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] close error: %s", cepid, itron_strerror(error));

	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] finished:   %6ld,            rcv: %4d, len: %ld",
	                   cepid, time / SYSTIM_HZ, count, total);

	return error;
	}

#else	/* of #ifdef USE_COPYSAVE_API */

static ER
tcp_discard_srv (ID cepid, ID repid)
{
	static char buffer[BUF_SIZE];

	T_IPEP		dst;
	ER_UINT		rlen;
	ER		error;
	SYSTIM		time;
	uint32_t	total;
	uint16_t	count;
	uint8_t		*buf = buffer;

	if ((error = TCP_ACP_CEP(cepid, repid, &dst, TMO_FEVR)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d RCV] accept error: %s", cepid, itron_strerror(error));
		return error;
		}

#ifdef USE_TCP_EXTENTIONS
	if ((error = free_tcp_rep(repid, true)) != E_OK) {
		syslog(LOG_NOTICE, "[TDS:%02d DEL] REP delete error: %s", cepid, itron_strerror(error));
		return error;
		}
#endif	/* of #ifdef USE_TCP_EXTENTIONS */

	count = total = 0;
	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] connected:  %6ld, from: %s.%d",
	                   cepid, time / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
	while ((rlen = tcp_rcv_dat(cepid, buf, BUF_SIZE - 1, TMO_FEVR)) > 0) {
		count ++;

#ifdef SHOW_RCV_RANGE
		syslog(LOG_NOTICE, "[TDS:%02d RCV] count: %4d, len: %4d, data: %02x -> %02x",
		       cepid, count, (uint16_t)rlen, *buf, *(buf + rlen - 1));
#endif	/* of #ifdef SHOW_RCV_RANGE */

		total += rlen;
		}
	if (rlen != 0)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] recv error: %s", cepid, itron_strerror(rlen));

	if ((error = tcp_sht_cep(cepid)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] shutdown error: %s", cepid, itron_strerror(error));

	if ((error = tcp_cls_cep(cepid, TMO_FEVR)) != E_OK)
		syslog(LOG_NOTICE, "[TDS:%02d RCV] close error: %s", cepid, itron_strerror(error));

	get_tim(&time);
	syslog(LOG_NOTICE, "[TDS:%02d RCV] finished:   %6ld,            rcv: %4d, len: %ld",
	                   cepid, time / SYSTIM_HZ, count, total);

	return error;
	}

#endif	/* of #ifdef USE_COPYSAVE_API */

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
	crep.myaddr.portno = UINT_C(9);

#if defined(SUPPORT_INET4)
	crep.myaddr.ipaddr = IPV4_ADDRANY;
#endif

#if defined(SUPPORT_INET6)
	memcpy(&crep.myaddr.ipaddr, &ipv6_addrany, sizeof(T_IN6_ADDR));
#endif

	return alloc_tcp_rep(repid, tskid, &crep);
	}

/*
 *  get_tcp_cep -- TCP �ʐM�[�_�Ƃ��l������B
 */

static ER
get_tcp_cep (ID *cepid)
{
	ID		tskid;
	T_TCP_CCEP	ccep;

	get_tid(&tskid);

	ccep.cepatr = UINT_C(0);
	ccep.sbuf = NADR;
	ccep.sbufsz = 0;
	ccep.rbufsz = TCP_DISCARD_SRV_RWBUF_SIZE;
	ccep.callback = NULL;

#ifdef TCP_CFG_RWBUF_CSAVE
	ccep.rbuf = NADR;
#else
	ccep.rbuf = tcp_discard_srv_rwbuf;
#endif

	return alloc_tcp_cep(cepid, tskid, &ccep);
	}

/*
 *  tcp_discard_srv_task -- TCP �G�R�[�T�[�o�^�X�N
 */

void
tcp_discard_srv_task (intptr_t exinf)
{
	ID	tskid, cepid, repid;
	ER	error = E_OK;

	syscall(get_tid(&tskid));
	syslog(LOG_NOTICE, "[TCP ECHO SRV:%d] started.", tskid);
	while (true) {

		syscall(slp_tsk());
		if ((error = get_tcp_cep (&cepid)) != E_OK) {
			syslog(LOG_NOTICE, "[TDS:00 EXT] CEP create error: %s", itron_strerror(error));
			continue;
			}

		while (true) {

			if ((error = get_tcp_rep (&repid)) != E_OK) {
				syslog(LOG_NOTICE, "[TDS:00 EXT] REP create error: %s", itron_strerror(error));
				break;
				}
			else if ((error = tcp_discard_srv(cepid, repid)) != E_OK) {
				error = free_tcp_rep(repid, error != E_DLT);
				break;
				}
			}

		if ((error = free_tcp_cep(cepid)) != E_OK)
			syslog(LOG_NOTICE, "[TDS:%02d EXT] CEP delete error: %s", cepid, itron_strerror(error));

		}
	}

#else	/* of #ifdef USE_TCP_EXTENTIONS */

void
tcp_discard_srv_task(intptr_t exinf)
{
	ID	tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[TCP DISCARD SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		while (tcp_discard_srv((ID)exinf, TCP_DISCARD_SRV_REPID) == E_OK)
			;
		}
	}

#endif	/* of #ifdef USE_TCP_EXTENTIONS */

#endif	/* of #ifdef USE_TCP_DISCARD_SRV */
