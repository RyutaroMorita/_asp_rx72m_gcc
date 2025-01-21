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
 *  @(#) $Id: ppp_auth.c,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * auth.c - PPP authentication and phase control.
 *
 * Copyright (c) 1993 The Australian National University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Australian National University.  The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
 *			PPP Secret Key Module
 *
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1994, Internet Initiative Japan, Inc. All rights reserverd.
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
 * $FreeBSD: src/usr.sbin/ppp/auth.c,v 1.50 1999/12/27 11:43:30 brian Exp $
 *
 *	TODO:
 *		o Implement check against with registered IP addresses.
 */

#include <s_services.h>
#include <t_services.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_auth.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>
#include <net/ppp_upap.h>

#ifdef SUPPORT_PPP

/*
 *  �萔
 */

#define PAP_PEND_SERVER		UINT_C(0x01)
#define PAP_PEND_CLIENT		UINT_C(0x02)
#define CHAP_PEND_SERVER	UINT_C(0x04)
#define CHAP_PEND_CLIENT	UINT_C(0x08)

/*
 *  network_phase -- �R�l�N�V�����m��
 */

void
network_phase (void)
{
	int_t		num, ix;
	T_PPP_PROTENT	*proto;

	ppp_phase = PPP_PHASE_NETWORK;

	/* ��ʃv���g�R�����I�[�v������ */
	num = 0;
	for (ix = 0; (proto = protocols[ix]) != NULL; ix ++)
#if 0	/* �ۗ��A�폜�֎~ */
		if (proto->proto < 0xc000 && proto->open != NULL) {
#else	/* of #if 0 */
		if (proto->open != NULL) {
#endif	/* of #if 0 */
			(*proto->open)();
			if (proto->proto != PPP_CCP)
				num ++;
			}

	if (num == 0)
		/* ��ʃv���g�R�����Ȃ� */
		lcp_close();
	else
		syslog(LOG_NOTICE, "[PPP] up.");
	}

/*
 *  link_required -- �����N���J�݂���B
 */

void
link_required (void)
{
	}

/*
 *  link_terminated -- ���O�A�E�g���āA�����N��ؒf����B
 */

void
link_terminated (void)
{
	ppp_phase     = PPP_PHASE_DEAD;
	ppp_open_mode = PPP_OPEN_PASSIVE;
	syslog(LOG_NOTICE, "[PPP] down.");
	}

/*
 *  link_down -- �����N���������B
 */

void
link_down (void)
{
	int_t		ix;
	T_PPP_PROTENT	*proto;

	/* ��ʃv���g�R����������� */
	for (ix = 0; (proto = protocols[ix]) != NULL; ix ++) {
		if (proto->proto != PPP_LCP && proto->lowerdown != NULL)
			(*proto->lowerdown)();
		if (proto->proto < 0xc000 && proto->close != NULL)
			(*proto->close)();
		}

	if (ppp_phase != PPP_PHASE_DEAD)
		ppp_phase = PPP_PHASE_TERMINATE;
	}

/*
 *  link_established -- �����N�̐ڑ����m�������B
 */

void
link_established (void)
{
	int_t		ix;
	T_PPP_PROTENT	*proto;

#if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP)

	int		auth;

#endif	/* of #if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP) */

	/* ��ʃv���g�R�����N������ */
	for (ix = 0; (proto = protocols[ix]) != NULL; ix ++)
		if (proto->lowerup != NULL)
			(*proto->lowerup)();

	/* �F�؃I�v�V�������m�F����B�y�������z*/

	ppp_phase = PPP_PHASE_AUTHENTICATE;

#if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP)

	auth = 0;

#ifdef AUTH_CFG_SERVER

#if defined(LCP_CFG_CHAP)

	if (lcp_local_ack_cfg.options & LCP_CFG_CHAP) {
		chap_auth_server();
		auth |= CHAP_PEND_SERVER;
		}

#endif	/* of #if defined(LCP_CFG_CHAP) */

#if defined(LCP_CFG_PAP)
	
	if (lcp_local_ack_cfg.options & LCP_CFG_PAP) {
		upap_auth_server();
		auth |= PAP_PEND_SERVER;
		}

#endif	/* of #if defined(LCP_CFG_PAP) */

#endif	/* of #ifdef AUTH_CFG_SERVER */

#ifdef AUTH_CFG_CLIENT

#if defined(LCP_CFG_PAP)
	
	if (lcp_remote_ack_cfg.options & LCP_CFG_PAP) {
		upap_auth_client();
		auth |= PAP_PEND_CLIENT;
		}

#endif	/* of #if defined(LCP_CFG_PAP) */

#endif	/* of #ifdef AUTH_CFG_CLIENT */

	if (auth == 0)
		network_phase();

#else	/* of #if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP) */

	network_phase();

#endif	/* of #if defined(LCP_CFG_CHAP) || defined(LCP_CFG_PAP) */

	}

/*
 *  auth_reset -- �F�؃I�v�V�������Ċm�F����B
 */

void
auth_reset (void)
{
	}

#endif	/* fo #ifdef SUPPORT_PPP */
