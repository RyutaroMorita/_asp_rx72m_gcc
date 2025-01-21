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
 *  @(#) $Id: ppp_lcp.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * lcp.h - Link Control Protocol definitions.
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
 *
 * $FreeBSD: src/usr.sbin/pppd/lcp.h,v 1.6.2.1 1999/08/29 15:47:03 peter Exp $
 */

/*
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/lcp.h,v 1.23.2.1 2000/08/19 09:30:04 brian Exp $
 *
 *	TODO:
 */

#ifndef _PPP_LCP_H_
#define _PPP_LCP_H_

#ifdef SUPPORT_PPP

/*
 *  LCP ���L�� PPP �����N���� (CP) �̐���R�[�h
 */

#define PPP_PROTREJ		UINT_C(8)	/* Protocol Reject	*/
#define PPP_ECHOREQ		UINT_C(9)	/* Echo Request		*/
#define PPP_ECHOREP		UINT_C(10)	/* Echo Reply		*/
#define PPP_DISCREQ		UINT_C(11)	/* Discard Request	*/

/*
 *  LCP �̍\����� (CI)
 */

/*
 *  CI �̌^
 */

#define LCP_CIT_MRU		UINT_C(1)	/* �ő��M�� (Maximum Receive Unit)	*/
#define LCP_CIT_ACCM		UINT_C(2)	/* Async Control Character Map		*/
#define LCP_CIT_AUTH		UINT_C(3)	/* �F�؃v���g�R��			*/
#define LCP_CIT_QUALITY		UINT_C(4)	/* �i���v���g�R���͖�����			*/
#define LCP_CIT_MAGIC		UINT_C(5)	/* �}�W�b�N�ԍ�				*/
#define LCP_CIT_PCOMP		UINT_C(7)	/* �v���g�R�������k�͎����\��		*/
#define LCP_CIT_ACCOMP		UINT_C(8)	/* �A�h���X�E���䕔���k�͎����\��		*/
#define LCP_CIT_FCS_ALTER	UINT_C(9)	/* FCS-Alternatives �͖�����		*/
#define LCP_CIT_SELF_PAD	UINT_C(10)	/* Self-Describing-Padding �͖�����	*/
#define LCP_CIT_CALLBACK	UINT_C(13)	/* Callback �͖�����			*/
#define LCP_CIT_CFRAMES		UINT_C(15)	/* Compound-Frames �͖�����		*/

/*
 *  LCP �̍\�����I�v�V����
 */

typedef struct t_lcp_configs {
	uint32_t	ACCM;		/* ACCM			*/

#ifdef LCP_CFG_MAGIC

	uint32_t	magic;		/* �}�W�b�N�ԍ�		*/

#endif	/* of #ifdef LCP_CFG_MAGIC */

	uint16_t	MRU;		/* MRU			*/
	uint16_t	options;	/* �I�v�V�����t���O	*/
	} T_LCP_CONFIGS;

/*
 *  �ϐ�
 */

extern T_PPP_FSM	lcp_fsm;
extern T_PPP_PROTENT	lcp_protent;
extern T_LCP_CONFIGS	lcp_local_ack_cfg;	/* ����ɋ����ꂽ�̎��\�����	*/
extern T_LCP_CONFIGS	lcp_remote_ack_cfg;	/* ����ɋ������\�����		*/

/*
 *  �֐�
 */

extern void lcp_lowerup (void);
extern void lcp_lowerdown (void);
extern void lcp_down (T_PPP_FSM *fsm);
extern void lcp_finished (T_PPP_FSM *fsm);
extern void lcp_open (uint8_t open_mode);
extern void lcp_close (void);
extern void lcp_sprotrej (T_NET_BUF *data);

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _PPP_LCP_H_ */
