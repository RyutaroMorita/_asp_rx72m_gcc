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
 *  @(#) $Id: ppp_lcp.c,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * lcp.c - PPP Link Control Protocol.
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
 *	      PPP Link Control Protocol (LCP) Module
 *
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
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
 * $FreeBSD: src/usr.sbin/ppp/lcp.c,v 1.81.2.3 2000/08/19 09:30:04 brian Exp $
 *
 */

#include <string.h>

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_hdlc.h>
#include <net/ppp_auth.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>

#ifdef SUPPORT_PPP

/*
 *  �֐�
 */

static void lcp_init    (void);
static void lcp_protrej (void);
static void lcp_input   (T_NET_BUF *input);

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

static void send_echo_req  (T_PPP_FSM *fsm);
static void recv_echo_rep  (T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input);
static void echo_timeout   (void *arg);
static void echo_lowerup   (void);
static void echo_lowerdown (void);

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

/*
 * FSM ����ďo�����R�[���o�b�N�֐�
 */

static void  lcp_resetci(T_PPP_FSM *fsm);	/* ���\���������Z�b�g����B	*/
static int_t lcp_cilen	(T_PPP_FSM *fsm);	/* �\�����̒�����Ԃ��B		*/
static void  lcp_addci	(T_PPP_FSM *fsm, T_NET_BUF *output);
						/* ���\������ǉ�����B		*/
static bool_t lcp_ackci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* ACK ����M�����Ƃ��̏���	*/
static bool_t lcp_nakci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* NAK ����M�����Ƃ��̏���	*/
static bool_t lcp_rejci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* REJ ����M�����Ƃ��̏���	*/
static int_t lcp_reqci	(T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output);
						/* ����̍\�������m�F����B	*/
static void lcp_up	(T_PPP_FSM *fsm);	/* �����N�ڑ����m������B		*/
static void lcp_starting(T_PPP_FSM *fsm);	/* ���ʑw���J�n����B		*/
static bool_t lcp_extcode	(T_PPP_FSM *fsm, uint8_t code, uint8_t id, T_NET_BUF *input);
						/* �s���� CP ����M�����Ƃ��̏���	*/
static void lcp_rprotrej(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* Proto-REJ ����M�����Ƃ��̏���	*/
/*
 *  �ϐ�
 */

static T_LCP_CONFIGS lcp_def_cfg = {		/* �\�����̏����ݒ�l		*/
	DEF_REMOTE_ACCM,			/* ACCM				*/

#ifdef LCP_CFG_MAGIC

	ULONG_C(0),				/* �}�W�b�N�ԍ�			*/

#endif	/* of #ifdef LCP_CFG_MAGIC */

	DEF_PPP_MTU,				/* MRU				*/
	UINT_C(0),				/* �I�v�V�����t���O		*/
	};

static T_LCP_CONFIGS lcp_local_def_cfg = {	/* ���\�����̋K��l		*/
	DEF_LOCAL_ACCM,				/* ACCM				*/

#ifdef LCP_CFG_MAGIC

	ULONG_C(0),				/* �}�W�b�N�ԍ�			*/

#endif	/* of #ifdef LCP_CFG_MAGIC */

	DEF_PPP_MTU,				/* MRU				*/
	DEF_LCP_LOCAL_CFGS,			/* �I�v�V�����t���O		*/
	};

static T_LCP_CONFIGS lcp_local_neg_cfg;		/* �l�S���̎��\�����		*/

static T_LCP_CONFIGS lcp_remote_neg_cfg;	/* �l�S���̑���̍\�����		*/

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

static uint8_t echo_pending  = UINT_C(0);
static uint8_t echo_number   = UINT_C(0);
static uint8_t timer_running = false;

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

/*
 *  �S��ϐ�
 */

T_PPP_FSM_CALLBACKS lcp_callbacks = {
	lcp_resetci,			/* ���\���������Z�b�g����B	*/
	lcp_cilen,			/* �\�����̒�����Ԃ��B		*/
	lcp_addci,			/* ���\������ǉ�����B		*/
	lcp_ackci,			/* ACK ����M�����Ƃ��̏���	*/
	lcp_nakci,			/* NAK ����M�����Ƃ��̏���	*/
	lcp_rejci,			/* REJ ����M�����Ƃ��̏���	*/
	lcp_reqci,			/* ����̍\�������m�F����B	*/
	lcp_up,				/* �����N�ڑ����m������B		*/
	lcp_down,			/* �����N�ڑ����������B		*/
	lcp_starting,			/* ���ʑw���J�n����B		*/
	lcp_finished,			/* ���ʑw���I������B		*/
	NULL,				/* �đ�����B			*/
	lcp_extcode,			/* �s���� CP ����M�����Ƃ��̏���	*/
	};

T_PPP_FSM lcp_fsm = {
	&lcp_callbacks,			/* �R�[���o�b�N�֐�		*/
	PPP_LCP,			/* �v���g�R��			*/
	};

T_PPP_PROTENT lcp_protent = {
	PPP_LCP,
	lcp_init,			/* ������			*/
	lcp_input,			/* ����				*/
	lcp_protrej,			/* Proto-REJ ��M����		*/
	NULL,				/* ���ʑw���N������		*/
	lcp_lowerdown,			/* ���ʑw���~����		*/
	NULL,				/* �I�[�v������			*/
	lcp_close,			/* �N���[�Y����			*/
	NULL,				/* �f�[�^����			*/
	};

T_LCP_CONFIGS lcp_local_ack_cfg;	/* ����ɋ����ꂽ�̎��\�����	*/
T_LCP_CONFIGS lcp_remote_ack_cfg;	/* ����ɋ������\�����		*/

/*
 *  lcp_init -- LCP ���W���[���̏�����
 */

static void
lcp_init (void)
{
	fsm_init(&lcp_fsm);
	}

/*
 *  lcp_input -- LCP ����
 */

static void
lcp_input (T_NET_BUF *input)
{
	NET_COUNT_PPP_LCP(net_count_ppp_lcp_in_octets,  input->len);
	NET_COUNT_PPP_LCP(net_count_ppp_lcp_in_packets, 1);
	fsm_input(&lcp_fsm, input);
	}

/*
 *  lcp_resetci -- LCP�̍\���������Z�b�g����B
 */

static void
lcp_resetci (T_PPP_FSM *fsm)
{
#ifdef LCP_CFG_MAGIC

	SYSTIM	time;

#endif	/* of #ifdef LCP_CFG_MAGIC */

	/* ���\�����̏����ݒ� */
	lcp_local_neg_cfg	= lcp_local_def_cfg;
	lcp_local_ack_cfg	= lcp_def_cfg;

	/* ����̍\�����̏����ݒ� */
	lcp_remote_neg_cfg	= lcp_def_cfg;
	lcp_remote_ack_cfg	= lcp_def_cfg;

#ifdef LCP_CFG_MAGIC

	syscall(get_tim(&time));
	net_srand((unsigned int)time);
	lcp_local_neg_cfg.magic = net_rand();

#endif	/* of #ifdef LCP_CFG_MAGIC */

	auth_reset();
	}

/*
 *  lcp_cilen -- �\�����̒�����Ԃ��B
 */

static int_t
lcp_cilen (T_PPP_FSM *fsm)
{
	int_t cilen = 0;

	if (lcp_local_neg_cfg.options & LCP_CFG_MRU)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);	/* MRU   */

	if (lcp_local_neg_cfg.options & LCP_CFG_ACCM)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);	/* ACCM  */

#ifdef LCP_CFG_MAGIC

	if (lcp_local_neg_cfg.options & LCP_CFG_MAGIC)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);	/* Magic */

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	if (lcp_local_neg_cfg.options & LCP_CFG_PAP)
		cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);	/* PAP   */

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	if (lcp_local_neg_cfg.options & LCP_CFG_PCOMP)
		cilen += sizeof(T_PPP_CI_HDR);			/* �v���g�R�����k */

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	if (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP)
		cilen += sizeof(T_PPP_CI_HDR);			/* �A�h���X�E���䈳�k */

#endif	/* of #ifdef LCP_CFG_ACCOMP */

	return cilen;
	}

/*
 *  lcp_addci -- LCP�̍\������ǉ�����B
 */

static void
lcp_addci (T_PPP_FSM *fsm, T_NET_BUF *output)
{
	uint8_t *buf;

	buf = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);

	/* MRU �I�v�V������ǉ�����B */
	if (lcp_local_neg_cfg.options & LCP_CFG_MRU) {
		*buf ++ = LCP_CIT_MRU;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		*((uint16_t*)buf) = htons(lcp_local_neg_cfg.MRU);
		buf += sizeof(uint16_t);
		}

	/* ACCM �I�v�V������ǉ�����B */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCM) {
		*buf ++ = LCP_CIT_ACCM;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		ahtonl(buf, lcp_local_neg_cfg.ACCM);
		buf += sizeof(uint32_t);
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number �I�v�V������ǉ�����B */
	if (lcp_local_neg_cfg.options & LCP_CFG_MAGIC) {
		*buf ++ = LCP_CIT_MAGIC;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		ahtonl(buf, lcp_local_neg_cfg.magic);
		buf += sizeof(uint32_t);
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* �F�؃v���g�R���I�v�V������ǉ�����B */
	if (lcp_local_neg_cfg.options & LCP_CFG_PAP) {
		*buf ++ = LCP_CIT_AUTH;
		*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		*((uint16_t*)buf) = htons(PPP_PAP);
		buf += sizeof(uint16_t);
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �v���g�R�����k�I�v�V������ǉ�����B */
	if (lcp_local_neg_cfg.options & LCP_CFG_PCOMP) {
		*buf ++ = LCP_CIT_PCOMP;
		*buf ++ = sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* �A�h���X�E���䈳�k�I�v�V������ǉ�����B */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP) {
		*buf ++ = LCP_CIT_ACCOMP;
		*buf ++ = sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */
	}

/*
 *  lcp_ackci -- ACK ����M�����Ƃ��̏���
 *
 *	�߂�l:	TURE  ACK �͐���
 *		false ACK �ُ͈�
 */

static bool_t
lcp_ackci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	uint8_t		*buf;
	uint16_t	len;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	/*
	 *  �\�����͑��M�������Ɋ��S�Ɉ�v���Ȃ���΂Ȃ�Ȃ��B
	 *  �]���āAlcp_addci �ō쐬�������ɉ�͂���B
	 */

	/* MRU �I�v�V��������͂���B */
	if (lcp_local_neg_cfg.options & LCP_CFG_MRU) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	||
		    *buf ++ != LCP_CIT_MRU			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)||
		    *((uint16_t*)buf) != htons(lcp_local_neg_cfg.MRU)	)
			return false;
		buf += sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		}

	/* ACCM �I�v�V��������͂���B */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCM) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	||
		    *buf ++ != LCP_CIT_ACCM			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)||
		    nahcmpl(buf, lcp_local_neg_cfg.ACCM)        )
			return false;
		buf += sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number �I�v�V��������͂���B */
	if (lcp_local_neg_cfg.options & LCP_CFG_MAGIC) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	||
		    *buf ++ != LCP_CIT_MAGIC			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)||
		    nahcmpl(buf, lcp_local_neg_cfg.magic)       )
			return false;
		buf += sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* �F�؃v���g�R���I�v�V��������͂���B */
	if (lcp_local_neg_cfg.options & LCP_CFG_PAP) {
		if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	||
		    *buf ++ != LCP_CIT_AUTH			||
		    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)||
		    *((uint16_t*)buf) != htons(PPP_PAP)		)
			return false;
		buf += sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �v���g�R�����k�I�v�V��������͂���B */
	if (lcp_local_neg_cfg.options & LCP_CFG_PCOMP) {
		if (len < sizeof(T_PPP_CI_HDR)			||
		    *buf ++ != LCP_CIT_PCOMP			||
		    *buf ++ != sizeof(T_PPP_CI_HDR))
			return false;
		len -= sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* �A�h���X�E���䈳�k�I�v�V��������͂���B */
	if (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP) {
		if (len < sizeof(T_PPP_CI_HDR)			||
		    *buf ++ != LCP_CIT_ACCOMP			||
		    *buf ++ != sizeof(T_PPP_CI_HDR))
			return false;
		len -= sizeof(T_PPP_CI_HDR);
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */
	return true;
	}

/*
 *  lcp_nakci -- NAK ����M�����Ƃ��̏���
 *
 *	�߂�l:	1  NAK �͐���
 *		0  NAK �ُ͈�
 */

static int_t
lcp_nakci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_LCP_CONFIGS	new_cfg;
	bool_t		loop = false;	/* ���[�v�o�b�N���`�F�b�N */
	uint32_t	cilong;
	uint16_t	cishort, len;
	uint8_t		*buf, cilen;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = lcp_local_neg_cfg;

	/* MRU �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_MRU				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MRU)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort <= lcp_local_neg_cfg.MRU || cishort <= DEF_PPP_MTU)
			new_cfg.MRU = cishort;
		}

	/* ACCM �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_ACCM				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCM)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.ACCM |= cilong;
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_MAGIC				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MAGIC)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.magic = cilong;
		loop = true;
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* �F�؃v���g�R���I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_AUTH				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PAP)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort == PPP_PAP)
			new_cfg.options &= ~LCP_CFG_PAP;
		else
			return 0;
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �v���g�R�����k�I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_PCOMP				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_PCOMP;
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* �A�h���X�E���䈳�k�I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_ACCOMP			&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_ACCOMP;
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */

	/* ��͖�������B*/
	while (len > sizeof(T_PPP_CI_HDR)) {
		cilen = *(buf + 1);
		if (len < cilen)
			return 0;
		buf += cilen;
		len -= cilen;
		}

	/* ������ 0 �łȂ���΃G���[ */
	if (len != 0)
		return 0;

	/* �V�����I�v�V������ݒ肷��B*/
	if (fsm->state != PPP_FSM_OPENED) {
		if (loop) {
			syslog(LOG_WARNING, "[PPP/LCP] line looped.");
			lcp_close();
			}
		lcp_local_neg_cfg = new_cfg;
		}
	return 1;
	}

/*
 *  lcp_rejci -- REJ ����M�����Ƃ��̏���
 *
 *	�߂�l:	1  REJ �͐���
 *		0  REJ �ُ͈�
 */

static int_t
lcp_rejci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_LCP_CONFIGS	new_cfg;
	uint32_t	cilong;
	uint16_t	cishort, len;
	uint8_t		*buf;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = lcp_local_neg_cfg;

	/* MRU �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_MRU					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MRU)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort != lcp_local_neg_cfg.MRU)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_MRU;
		}
		
	/* ACCM �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_ACCM					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCM)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		if (cilong != lcp_local_neg_cfg.ACCM)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_ACCM;
		}

#ifdef LCP_CFG_MAGIC

	/* Magic Number �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == LCP_CIT_MAGIC					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_MAGIC)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		if (cilong != lcp_local_neg_cfg.magic)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_MAGIC;
		}

#endif	/* of #ifdef LCP_CFG_MAGIC */

#ifdef LCP_CFG_PAP

	/* �F�؃v���g�R���I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)		&&
	    * buf      == LCP_CIT_AUTH					&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t)	&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PAP)) {
	    	cishort = ntohs(*((uint16_t*)(buf + 2)));
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
		if (cishort != PPP_PAP)
			return 0;
		else
			new_cfg.options &= ~LCP_CFG_PAP;
		}

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

	/* �v���g�R�����k�I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_PCOMP				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_PCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_PCOMP;
		}

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

	/* �A�h���X�E���䈳�k�I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR)				&&
	    * buf      == LCP_CIT_ACCOMP			&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR)			&&
	    (lcp_local_neg_cfg.options & LCP_CFG_ACCOMP)) {
		buf += sizeof(T_PPP_CI_HDR);
		len -= sizeof(T_PPP_CI_HDR);
		new_cfg.options &= ~LCP_CFG_ACCOMP;
		}

#endif	/* of #ifdef LCP_CFG_ACCOMP */

	/* ������ 0 �łȂ���΃G���[ */
	if (len != 0)
		return 0;

	/* �V�����I�v�V������ݒ肷��B*/
	if (fsm->state != PPP_FSM_OPENED)
		lcp_local_neg_cfg = new_cfg;

	return 1;
	}

/*
 *  lcp_reqci -- ����̍\��������͂���B
 */

static int_t
lcp_reqci (T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output)
{
#if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC

	uint32_t	cilong;

#endif	/* of #if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC */

	uint16_t	code, final, len, cilen, cishort;
	uint8_t		*np, *rp, *ap, *cp, type = 0;

	rp = ap = input->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
				/* rp: REJ�Aap: ACK ���� CI �̃|�C���^		*/
				/* ���ۂ���ꍇ�́A���� input �ɏ㏑������B	*/
	len   = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
	np    = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	final = PPP_CONFACK;	/* �ŏI�I�ɑ��M����R�[�h */
	while (len > 0) {
		code = PPP_CONFACK;
		cp   = ap;	/* cp: ���ݏ������� CI	*/

		if (len < sizeof(T_PPP_CI_HDR)) {

			/* �c�肪 CI �w�b�_���Z�� */
			syslog(LOG_WARNING, "[PPP/LCP] bad CI len: %d.", len);
			cilen = len;	/* �f�[�^�����ُ�̏ꍇ�̏��u	*/
			len   = 0;	/* ���[�v���甲����B		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}

		type  = *ap ++;	/* CI �̌^		*/
		cilen = *ap ++;	/* CI �̒���		*/
		if (len < cilen) {

			/* �c�肪 CI �����Z�� */
			syslog(LOG_WARNING, "[PPP/LCP] bad CI len: %d.", cilen);
			cilen = len;	/* �f�[�^�����ُ�̏ꍇ�̏��u	*/
			len   = 0;	/* ���[�v���甲����B		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}
		len -= sizeof(T_PPP_CI_HDR);

		/* CI �̌^�ɂ�蕪�򂷂�B*/
		switch (type) {

		case LCP_CIT_MRU:	/* �ő��M�� (Maximum Receive Unit) */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MRU) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MRU) == 0 */

		 	/* CI �����A�w�b�_ + 2 �I�N�e�b�g�łȂ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint16_t))
				code = PPP_CONFREJ;
			{
				cishort = ntohs(*(uint16_t*)ap);

				/* �ŏ���M�ʂ�菬������� NAK */
				if (cishort < MIN_PPP_MTU) {
					*np ++ = LCP_CIT_MRU;
					*np ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint16_t);
					*((uint16_t*)np) = htons(MIN_PPP_MTU);
					np  += sizeof(uint16_t);
					code = PPP_CONFNAK;
					}
				else {
					lcp_remote_neg_cfg.MRU = cishort;
					lcp_remote_neg_cfg.options |= LCP_CFG_MRU;
					}
				}

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MRU) == 0 */

			break;

		case LCP_CIT_ACCM:	/* Async Control Character Map */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCM) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCM) == 0 */

		 	/* CI �����A�w�b�_ + 4 �I�N�e�b�g�łȂ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t))
				code = PPP_CONFREJ;
			else {
				ntoahl(lcp_remote_neg_cfg.ACCM, ap);
				lcp_remote_neg_cfg.options |= LCP_CFG_ACCM;
				}

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCM) == 0 */

			break;

		case LCP_CIT_MAGIC:	/* �}�W�b�N�ԍ� */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC) == 0 */

		 	/* CI �����A�w�b�_ + 4 �I�N�e�b�g�łȂ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t))
				code = PPP_CONFREJ;
			else {
				ntoahl(cilong, ap);

				/* �ԍ��������Ɠ����Ȃ� NAK */
				if (cilong == lcp_local_neg_cfg.magic) {
					cilong = net_rand();
					*np ++ = LCP_CIT_MAGIC;
					*np ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
					ahtonl(np, cilong);
					np  += sizeof(uint32_t);
					code = PPP_CONFNAK;
					}
				else {
					lcp_remote_neg_cfg.magic = cilong;
					lcp_remote_neg_cfg.options |= LCP_CFG_MAGIC;
					}
				}

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC) == 0 */

			break;

#ifdef LCP_CFG_PAP
		/* CHAP �͎����\��	*/

		case LCP_CIT_AUTH:	/* �F�؃v���g�R�� */

		 	/* CI �����A�w�b�_ + 2 �I�N�e�b�g���Z���Ƃ��̓G���[ */
		 	if (cilen < sizeof(T_PPP_CI_HDR) + sizeof(uint16_t))
				code = PPP_CONFREJ;
			else {
				cishort = ntohs(*(uint16_t*)ap);

				/* �F�؃v���g�R���ɂ�蕪�򂷂�	*/
				if (cishort == PPP_PAP &&
				    cilen   == sizeof(T_PPP_CI_HDR) + sizeof(uint16_t) &&
			 	    (DEF_LCP_REMOTE_CFGS & LCP_CFG_PAP) != 0)
					lcp_remote_neg_cfg.options |= LCP_CFG_PAP;
				else
					code = PPP_CONFREJ;
				}
			break;

#endif	/* of #ifdef LCP_CFG_PAP */

#ifdef LCP_CFG_PCOMP

		case LCP_CIT_PCOMP:	/* �v���g�R�������k�͎����\�� */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_PCOMP) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_PCOMP) == 0 */

		 	/* CI �����A�w�b�_�������łȂ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR))
				code = PPP_CONFREJ;
			else
				lcp_remote_neg_cfg.options |= LCP_CFG_PCOMP;

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_PCOMP) == 0 */

			break;

#endif	/* of #ifdef LCP_CFG_PCOMP */

#ifdef LCP_CFG_ACCOMP

		case LCP_CIT_ACCOMP:	/* �A�h���X�E���䕔���k */

#if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCOMP) == 0

			code = PPP_CONFREJ;

#else	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCOMP) == 0 */

		 	/* CI �����A�w�b�_�������łȂ���� REJ */
		 	if (cilen != sizeof(T_PPP_CI_HDR))
				code = PPP_CONFREJ;
			else
				lcp_remote_neg_cfg.options |= LCP_CFG_ACCOMP;

#endif	/* of #if (DEF_LCP_REMOTE_CFGS & LCP_CFG_ACCOMP) == 0 */

			break;

#endif	/* of #ifdef LCP_CFG_ACCOMP */

		default:
			syslog(LOG_WARNING, "[PPP/LCP] unexp opt: %d.", type);
			code  = PPP_CONFREJ;
			break;
			}
endswitch:
		if (code == PPP_CONFNAK) {
			/* CI �̌^�� Magic Number �̏ꍇ�������āANAK �̉񐔂�	*/
			/* �ő�l MAX_PPP_FAILURES  �𒴂����狑�ۂ���B	*/
			if (fsm->failures >= MAX_PPP_FAILURES && type != LCP_CIT_MAGIC)
				code = PPP_CONFREJ;
			else if (final != PPP_CONFREJ)
				final = PPP_CONFNAK;
			}

		/* ���� CI �����ۂ��� */
		if (code == PPP_CONFREJ) {
			if (rp < cp)		/* �O�ɋl�߂�B*/
				memcpy(rp, cp, cilen);
			rp += cilen;
			final = PPP_CONFREJ;
			}

		ap   += cilen - sizeof(T_PPP_CI_HDR);
		len  -= cilen - sizeof(T_PPP_CI_HDR);
		}

	/* �ŏI�I�Ȓ����𒲐�����B*/
	switch (final) {
	case PPP_CONFNAK:
		output->len = np - output->buf;
		memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
		break;
	case PPP_CONFREJ:
		memcpy(output->buf, input->buf, output->len = rp - input->buf);
		break;
	case PPP_CONFACK:
		memcpy(output->buf, input->buf, input->len);
		break;
		}
	return final;
	}

/*
 *  lcp_up -- �����N�ڑ����m������ (Phase: Establish �Ɉڍs����)�B
 */

static void
lcp_up (T_PPP_FSM *fsm)
{
	/* ���\�����̐ݒ� */
	lcp_local_ack_cfg = lcp_local_neg_cfg;

	/* ����̍\�����̐ݒ� */
	lcp_remote_ack_cfg = lcp_remote_neg_cfg;

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

	echo_lowerup();

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

	link_established();
	}

/*
 *  lcp_starting -- ���ʑw���J�n����B
 */

static void
lcp_starting (T_PPP_FSM *fsm)
{
	link_required();
	}

/*
 *  lcp_extcode -- LCP ���L�� CP ����M�����Ƃ��̏���
 */

static bool_t
lcp_extcode (T_PPP_FSM *fsm, uint8_t code, uint8_t id, T_NET_BUF *input)
{
#if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC

	T_NET_BUF *output;

#endif	/* of #if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC */

	switch (code) {
	case PPP_PROTREJ:
		lcp_rprotrej(fsm, input);
		break;

	case PPP_ECHOREQ:

#if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC

		if (fsm->state == PPP_FSM_OPENED) {
			syscall(get_net_buf(&output, sizeof(T_PPP_HDR)
			                           + sizeof(T_PPP_CP_HDR)
			                           + sizeof(uint32_t)));
			*(uint32_t*)(output->buf + sizeof(T_PPP_HDR)
			                   + sizeof(T_PPP_CP_HDR)) = lcp_local_ack_cfg.magic;
			IF_SET_PROTO(output, PPP_LCP);
			ppp_cp_output(PPP_ECHOREP, id, output);
			}

#endif	/* of #if DEF_LCP_REMOTE_CFGS & LCP_CFG_MAGIC */

		break;

	case PPP_ECHOREP:

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

		recv_echo_rep(fsm, id, input);

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

		break;

	case PPP_DISCREQ:
		break;

	default:
		return false;
		break;

		}
	return true;
	}

/*
 *  lcp_rprotrej -- Proto-REJ ����M�����Ƃ��̏���
 */

static void
lcp_rprotrej (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_PPP_PROTENT	*entry;
	int_t		ix;
	uint16_t	proto;

	if (input->len < sizeof(uint16_t)) {
		syslog(LOG_WARNING, "[PPP/LCP] bad len: %d in recv Proto-REJ.");
		return;
		}

	proto = ntohs(*GET_PPP_HDR(input));

	if (fsm->state != PPP_FSM_OPENED) {
		return;
		}

	/* ��ʃv���g�R�������������� */
	for (ix = 0; (entry = protocols[ix]) != NULL; ix ++)
		if (entry->proto == proto) {
			(*entry->protrej)();
			return;
			}

	syslog(LOG_WARNING, "[PPP/LCP] unexp proto: %d in recv Proto-REJ.", proto);
	}

/*
 *  lcp_protrej -- Proto-REJ ����M�����Ƃ��̏���
 */

static void
lcp_protrej (void)
{
	fsm_protreject(&lcp_fsm);
	}

/*
 *  lcp_lowerup -- LCP ���ʑw���N������B
 */

void
lcp_lowerup (void)
{
	fsm_lowerup(&lcp_fsm);
	}

/*
 *  lcp_lowerdown -- LCP ���ʑw���~����B
 */

void
lcp_lowerdown (void)
{
	fsm_lowerdown(&lcp_fsm);
	}

/*
 *  lcp_open -- LCP �̃I�[�v
 */

void
lcp_open (uint8_t open_mode)
{
	ppp_open_mode = open_mode;	/* �I�[�v�����̓��샂�[�h	*/
	fsm_open(&lcp_fsm);
	}

/*
 *  lcp_close -- LCP �̃N���[�Y
 */

void
lcp_close (void)
{
	if (ppp_phase != PPP_PHASE_DEAD)
		ppp_phase = PPP_PHASE_TERMINATE;

	if (ppp_open_mode == PPP_OPEN_PASSIVE && lcp_fsm.state == PPP_FSM_STOPPED) {
		lcp_fsm.state = PPP_FSM_CLOSED;
		lcp_finished(&lcp_fsm);
		}
	else
		fsm_close(&lcp_fsm);
	}

/*
 *  lcp_sprotrej -- �F���ł��Ȃ��v���g�R���������Ă����Ƃ��̏���
 */

void
lcp_sprotrej (T_NET_BUF *input)
{
	T_NET_BUF	*output;
	/*
	 *  Protocol-Reject �𑗂�Ԃ��B
	 */

	syscall(get_net_buf(&output, input->len + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)));

	memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
	memcpy(output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR), input->buf, input->len);

	IF_SET_PROTO(output, PPP_LCP);
	ppp_cp_output(PPP_PROTREJ, ++ lcp_fsm.id, output);
	}

/*
 *  lcp_down -- �����N�ڑ���������� (Phase: Dead �Ɉڍs����)�B
 */

void
lcp_down (T_PPP_FSM *fsm)
{

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

	echo_lowerdown();

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

	link_down();
	}

/*
 *  lcp_finished -- ���ʑw���I������B
 */

void
lcp_finished (T_PPP_FSM *fsm)
{
	link_terminated();
	}

#if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC

/*
 *  recv_echo_rep -- ECHOREP ����M�����Ƃ��̏���
 */

static void
recv_echo_rep(T_PPP_FSM *fsm, uint8_t id, T_NET_BUF *input)
{
	T_PPP_CP_HDR	*hdr;
	uint32_t	magic;

 	hdr = GET_PPP_CP_HDR(input);

 	/* Magic Number �̒����ȉ��Ȃ�G���[ */
 	if (hdr->len < sizeof(T_PPP_CP_HDR) + sizeof(uint32_t)) {
		syslog(LOG_WARNING, "[PPP/LCP] bad ECHOREP len: %d.", hdr->len);
		return;
		}

	ntoahl(magic, input->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

 	/* ��M���� Magic Number �������Ɠ����Ȃ烋�[�v���Ă���B*/
	if ((lcp_local_ack_cfg.options & LCP_CFG_MAGIC) && magic == lcp_local_ack_cfg.magic) {
		syslog(LOG_WARNING, "[PPP/LCP] ECHOREP looped.");
		return;
		}

	echo_pending = 0;
	}

/*
 *  echo_timeout -- ECHO REQ/REP �̃^�C���A�E�g����
 */

static void
echo_timeout (void *arg)
{
	if (timer_running) {
		timer_running = false;
		send_echo_req((T_PPP_FSM *)arg);
		}
	}

/*
 *  send_echo_req -- ECHO REQ �𑗐M����B
 */

static void
send_echo_req (T_PPP_FSM *fsm)
{
	T_NET_BUF	*input;

#if LCP_ECHO_FAILS > 0

	if (echo_pending >= LCP_ECHO_FAILS) {
		syslog(LOG_WARNING, "[PPP/LCP] no reply to ECHOREQ.");
		lcp_close();
		echo_pending = 0;
		}

#endif	/* of #if LCP_ECHO_FAILS > 0 */

	if (fsm->state == PPP_FSM_OPENED) {

		/* ECHOREQ �𑗐M����B*/
		syscall(get_net_buf(&input, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR) + sizeof(uint32_t)));
		*(uint32_t*)(input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)) = lcp_local_ack_cfg.magic;
		IF_SET_PROTO(input, PPP_LCP);
		ppp_cp_output(PPP_ECHOREQ, echo_number ++, input);
		echo_pending ++;

		/* �^�C�}�[���X�^�[�g����B*/
		timeout((FP)echo_timeout, fsm, LCP_ECHO_INTERVAL);
		timer_running = true;
		}
	}

/*
 *  echo_lowerup -- ECHO REQ/REP �̋N��
 */

static void
echo_lowerup (void)
{
	echo_pending  = 0;
	echo_number   = 0;
	timer_running = false;

	send_echo_req(&lcp_fsm);
	}

/*
 *  echo_lowerdown -- ECHO REQ/REP �̒�~
 */

static void
echo_lowerdown (void)
{
	if (timer_running) {
		untimeout((FP)echo_timeout, &lcp_fsm);
		timer_running = false;
		}
	}

#endif	/* of #if DEF_LCP_LOCAL_CFGS & LCP_CFG_MAGIC */

#endif	/* fo #ifdef SUPPORT_PPP */
