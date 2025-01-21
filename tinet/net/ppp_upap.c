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
 *  @(#) $Id: ppp_upap.c,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * upap.c - User/Password Authentication Protocol.
 *
 * Copyright (c) 1989 Carnegie Mellon University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Carnegie Mellon University.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 *			PPP PAP Module
 *
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993-94, Internet Initiative Japan, Inc.
 *		     All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan, Inc.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/pap.c,v 1.42.2.1 2000/08/19 09:30:05 brian Exp $
 *
 *	TODO:
 */

#include <string.h>

#include <s_services.h>
#include <t_services.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_hdlc.h>
#include <net/ppp_auth.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>
#include <net/ppp_upap.h>

#ifdef SUPPORT_PPP

/*
 *  �֐�
 */

static void upap_init (void);
static void upap_input (T_NET_BUF *input);
static void upap_protrej (void);
static void upap_lowerup (void);
static void upap_lowerdown (void);
static bool_t compare (uint8_t *rstr, uint8_t *lstr, uint8_t rlen);

#ifdef AUTH_CFG_CLIENT

static void upap_sauthreq (void);
static void upap_rauthack (void);
static void upap_rauthnak (void);

#if defined(DEF_PAP_TIMEOUT)

static void upap_timeout(void *arg);

#endif	/* of #if defined(DEF_PAP_TIMEOUT) */

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

static void upap_rauthreq (T_NET_BUF *input);
static void upap_sresp    (uint8_t code, uint8_t id);

#if defined(DEF_PAP_REQTIME)

static void upap_reqtimeout(void *arg);

#endif	/* of #if defined(DEF_PAP_REQTIME) */

#endif	/* of #ifdef AUTH_CFG_SERVER */

/*
 *  �S��ϐ�
 */

T_PPP_PROTENT pap_protent = {
	PPP_PAP,
	upap_init,			/* ������			*/
	upap_input,			/* ����				*/
	upap_protrej,			/* Proto-REJ ��M����		*/
	upap_lowerup,			/* ���ʑw���N������		*/
	upap_lowerdown,			/* ���ʑw���~����		*/
	NULL,				/* �I�[�v������			*/
	NULL,				/* �N���[�Y����			*/
	NULL,				/* �f�[�^����			*/
	};

/*
 *  �ϐ�
 */

#ifdef AUTH_CFG_CLIENT

static uint8_t client_state;
static uint8_t client_cp_id;

#if defined(DEF_PAP_TIMEOUT)

static uint8_t client_rexmt = 0;

#endif	/* of #if defined(DEF_PAP_TIMEOUT) */

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

static uint8_t server_state;

#endif	/* of #ifdef AUTH_CFG_SERVER */

/*
 *  upap_init -- UPAP ���W���[���̏�����
 */

static void
upap_init (void)
{
#ifdef AUTH_CFG_CLIENT

	client_cp_id = 0;
	client_state = PAP_CS_INIT;

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

	server_state = PAP_SS_INIT;

#endif	/* of #ifdef AUTH_CFG_SERVER */
	}

/*
 *  upap_input -- UPAP ����
 */

static void
upap_input (T_NET_BUF *input)
{
	T_PPP_CP_HDR	*hdr;

	NET_COUNT_PPP_PAP(net_count_ppp_upap_in_octets,  input->len);
	NET_COUNT_PPP_PAP(net_count_ppp_upap_in_packets, 1);

 	/* PPP �����N���� (CP) �w�b�_���Z����΃G���[ */
 	if (input->len < (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR))) {
 		syslog(LOG_WARNING, "[PPP/PAP] short hdr: %d.", input->len);
 		return;
 		}

 	hdr = GET_PPP_CP_HDR(input);

 	/* �w�b�_�̒����Ɠ��̓f�[�^�T�C�Y����v���Ȃ���΃G���[ */
 	if (hdr->len != input->len - sizeof(T_PPP_HDR)) {
 		syslog(LOG_WARNING, "[PPP/PAP] bad len: %d.", hdr->len);
 		return;
 		}
 
 	/*
 	 *  ����R�[�h�ɂ��K���Ȋ֐����ďo��
 	 */

	switch (hdr->code) {

#ifdef AUTH_CFG_CLIENT

	case PAP_AUTHACK:
		upap_rauthack();
		break;

	case PAP_AUTHNAK:
		upap_rauthnak();
		break;

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

	case PAP_AUTHREQ:
		upap_rauthreq(input);
		break;

#endif	/* of #ifdef AUTH_CFG_SERVER */

		}
	}

/*
 *  upap_protrej -- Proto-REJ ����M�����Ƃ��̏���
 */

static void
upap_protrej (void)
{
#ifdef AUTH_CFG_CLIENT

	if (client_state == PAP_CS_AUTHREQ)
	 	syslog(LOG_WARNING, "[PPP/PAP] proto-rej recved.");

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

	if (server_state == PAP_SS_LISTEN) {
	 	syslog(LOG_WARNING, "[PPP/PAP] proto-rej recved.");
		lcp_close();
		}

#endif	/* of #ifdef AUTH_CFG_SERVER */

	upap_lowerdown();
	}

/*
 *  upap_lowerup -- UPAP ���ʑw���N������B
 */

static void
upap_lowerup (void)
{
#ifdef AUTH_CFG_CLIENT

	if (client_state == PAP_CS_INIT)
		client_state = PAP_CS_CLOSED;
	else if (client_state == PAP_CS_PENDING)
		upap_sauthreq();

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

	if (server_state == PAP_SS_INIT)
		server_state = PAP_SS_CLOSED;
	else if (server_state == PAP_SS_PENDING) {
		server_state = PAP_SS_LISTEN;

#if defined(DEF_PAP_REQTIME)

		timeout((FP)upap_reqtimeout, NULL, DEF_PAP_REQTIME);

#endif	/* of #if defined(DEF_PAP_REQTIME) */

		}

#endif	/* of #ifdef AUTH_CFG_SERVER */
	}

/*
 *  upap_lowerdown -- UPAP ���ʑw���~����B
 */

static void
upap_lowerdown (void)
{
#ifdef AUTH_CFG_CLIENT

#if defined(DEF_PAP_TIMEOUT)

	if (client_state == PAP_CS_AUTHREQ)
		untimeout((FP)upap_timeout, NULL);

#endif	/* of #if defined(DEF_PAP_TIMEOUT) */

	client_state = PAP_CS_INIT;

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

#if defined(DEF_PAP_REQTIME)

	if (server_state == PAP_SS_LISTEN)
		untimeout((FP)upap_reqtimeout, NULL);

#endif	/* of #if defined(DEF_PAP_REQTIME) */

	server_state = PAP_SS_INIT;

#endif	/* of #ifdef AUTH_CFG_SERVER */
	}
#ifdef AUTH_CFG_CLIENT

/*
 *  �N���C�A���g���[�h�� PAP �F�؂��J�n����B
 */

void
upap_auth_client (void)
{
#if defined(DEF_PAP_TIMEOUT)

	client_rexmt = 0;

#endif	/* of #if defined(DEF_PAP_TIMEOUT) */

	if (client_state == PAP_CS_INIT || client_state == PAP_CS_PENDING) {
		client_state = PAP_CS_PENDING;
		return;
		}

	upap_sauthreq();
	}

/*
 *  upap_rauthack -- �F�� ACK ����
 */

static void
upap_rauthack (void)
{
	if (client_state == PAP_CS_AUTHREQ) {
		client_state = PAP_CS_OPEN;
		network_phase();
		}
	}

/*
 *  upap_rauthnak -- �F�� NAK ����
 */

static void
upap_rauthnak (void)
{
 	syslog(LOG_WARNING, "[PPP/PAP] auth-req NAKed.");
	client_state = PAP_CS_BADAUTH;
	}

/*
 *  upap_sauthreq -- �F�ؗv������
 */

static void
upap_sauthreq (void)
{
	T_NET_BUF	*output;
	uint8_t		*data;

	syscall(get_net_buf(&output, sizeof(T_PPP_HDR)        + sizeof(T_PPP_CP_HDR)
	                           + sizeof(AUTH_REMOTE_USER) + sizeof(AUTH_REMOTE_PASSWD)));

	data = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);

	/* ���[�U����ݒ肷��B*/
	*data = sizeof(AUTH_REMOTE_USER) - 1;
	strcpy(data + 1, AUTH_REMOTE_USER);

	/* �p�X���[�h��ݒ肷��B*/
	*(data + sizeof(AUTH_REMOTE_USER)) = sizeof(AUTH_REMOTE_PASSWD) - 1;
	strcpy(data + sizeof(AUTH_REMOTE_USER) + 1, AUTH_REMOTE_PASSWD);

	/* ���M���� */
	IF_SET_PROTO(output, PPP_PAP);
	ppp_cp_output(PAP_AUTHREQ, ++ client_cp_id, output);

#if defined(DEF_PAP_TIMEOUT)

	timeout((FP)upap_timeout, NULL, DEF_PAP_TIMEOUT);
	client_rexmt ++;

#endif	/* of #if defined(DEF_PAP_TIMEOUT) */

	client_state = PAP_CS_AUTHREQ;
	}

#if defined(DEF_PAP_TIMEOUT)

/*
 *  upap_timeout -- �^�C���A�E�g����
 */

static void
upap_timeout (void *arg)
{
	if (client_state != PAP_CS_AUTHREQ)
		return;

	if (client_rexmt >= MAX_PAP_REXMT) {
 		syslog(LOG_WARNING, "[PPP/PAP] no reply auth-req.");
		client_state = PAP_CS_BADAUTH;
		return;
		}

	upap_sauthreq();
	}

#endif	/* of #if defined(DEF_PAP_TIMEOUT) */

#endif	/* of #ifdef AUTH_CFG_CLIENT */

#ifdef AUTH_CFG_SERVER

/*
 *  �T�[�o���[�h�� PAP �F�؂��J�n����B
 */

void
upap_auth_server (void)
{
	if (server_state == PAP_SS_INIT || server_state == PAP_SS_PENDING) {
		server_state = PAP_SS_PENDING;
		return;
		}

	server_state = PAP_SS_LISTEN;

#if defined(DEF_PAP_REQTIME)

	timeout((FP)upap_reqtimeout, NULL, DEF_PAP_REQTIME);

#endif	/* of #if defined(DEF_PAP_REQTIME) */
	}

/*
 *  upap_rauthreq -- �F�ؗv����������
 */

static void
upap_rauthreq (T_NET_BUF *input)
{
	int16_t	cplen;
	uint8_t	*data, *user, ulen, plen, code, id;

	if (server_state < PAP_SS_LISTEN)
		return;

	/*
	 *  �ėv�����������Ƃ��̏���
	 */
	id = GET_PPP_CP_HDR(input)->id;
	if (server_state == PAP_SS_OPEN) {
		upap_sresp(PAP_AUTHACK, id);
		return;
		}

	if (server_state == PAP_SS_BADAUTH) {
		upap_sresp(PAP_AUTHNAK, id);
		return;
		}

	cplen = GET_PPP_CP_HDR(input)->len;
	data  = input->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);

	/*
	 *  ���[�U������肷��B
	 */
	ulen  = *data;
	if (cplen < sizeof(T_PPP_CP_HDR) + ulen + sizeof(uint8_t)) {
 		syslog(LOG_WARNING, "[PPP/PAP] bad req len: %d.", cplen);
 		return;
		}
	user = ++ data;
	data += ulen;

	/*
	 *  �p�X���[�h����肷��B
	 */
	plen  = *data;
	if (cplen < sizeof(T_PPP_CP_HDR) + ulen + plen + sizeof(uint8_t) * 2) {
 		syslog(LOG_WARNING, "[PPP/PAP] bad req len: %d.", cplen);
 		return;
		}

	/*
	 *  ���[�U���ƃp�X���[�h���`�F�b�N����B
	 */
	if (compare(user,     AUTH_LOCAL_USER,   ulen) &&
	    compare(data + 1, AUTH_LOCAL_PASSWD, plen))
		code = PAP_AUTHACK;
	else
		code = PAP_AUTHNAK;

	upap_sresp(code, id);

	if (code == PAP_AUTHACK) {
		network_phase();
		server_state = PAP_SS_OPEN;
		}
	else {
		lcp_close();
		server_state = PAP_SS_BADAUTH;
		}

#if defined(DEF_PAP_REQTIME)

	untimeout((FP)upap_reqtimeout, NULL);

#endif	/* of #if defined(DEF_PAP_REQTIME) */
	}

/*
 *  upap_sresp -- ������Ԃ��B
 */

static void
upap_sresp (uint8_t code, uint8_t id)
{
	T_NET_BUF *output;

	/* ���M���� */
	syscall(get_net_buf(&output, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));
	IF_SET_PROTO(output, PPP_PAP);
	ppp_cp_output(code, id, output);
	}

/*
 *  compare -- ���[�U���ƃp�X���[�h�̔�r
 */

static bool_t
compare (uint8_t *rstr, uint8_t *lstr, uint8_t rlen)
{
	while (rlen -- > 0) {
		if (*rstr != *lstr)
			return false;
		rstr ++;
		lstr ++;
		}
	return *lstr ? false : true;
	}

#if defined(DEF_PAP_REQTIME)

/*
 *  upap_reqtimeout -- �v���^�C���A�E�g����
 */

static void
upap_reqtimeout (void *arg)
{
	if (server_state == PAP_SS_LISTEN) {
		lcp_close();
		server_state = PAP_SS_BADAUTH;
		}
	}

#endif	/* of #if defined(DEF_PAP_REQTIME) */

#endif	/* of #ifdef AUTH_CFG_SERVER */

#endif	/* fo #ifdef SUPPORT_PPP */
