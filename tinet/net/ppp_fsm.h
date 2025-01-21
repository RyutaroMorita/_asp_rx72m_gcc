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
 *  @(#) $Id: ppp_fsm.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * fsm.h - {Link, IP} Control Protocol Finite State Machine definitions.
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
 * $FreeBSD: src/usr.sbin/pppd/fsm.h,v 1.6.2.1 1999/08/29 15:47:00 peter Exp $
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
 * $FreeBSD: src/usr.sbin/ppp/fsm.h,v 1.23 1999/12/27 11:54:53 brian Exp $
 *
 *	TODO:
 */

#ifndef _PPP_FSM_H_
#define _PPP_FSM_H_

#ifdef SUPPORT_PPP

/*
 *  ��ԊǗ��\����
 */

struct t_ppp_fsm_callbacks;

typedef struct t_fsm {
	struct t_ppp_fsm_callbacks	*callbacks;	/* �R�[���o�b�N�֐�*/
	uint16_t	proto;		/* �v���g�R��				*/
	uint8_t		state;		/* FSM �̏��				*/
	uint8_t		id;		/* ���݂� ID				*/
	uint8_t		reqid;		/* �v�� ID				*/
	uint8_t		seen_ack;	/* �v���ɑ΂������ ACK/NAK/REJ ����M	*/
	int8_t		failures;	/* �ٔF���� NAK ��			*/
	int8_t		retrans;	/* Configure-Request �܂��́A		*/
					/* Terminate-Request �̍đ���		*/
	} T_PPP_FSM;

#define T_PPP_FSM_DEFINED

/*
 *  �R�[���o�b�N�֐��\����
 */

typedef struct t_ppp_fsm_callbacks {
	void (*resetci)	(T_PPP_FSM *);	/* ���\���������Z�b�g����B	*/
	int_t  (*cilen)	(T_PPP_FSM *);	/* �\�����̒�����Ԃ��B		*/
	void (*addci)	(T_PPP_FSM *, T_NET_BUF *);
					/* ���\������ǉ�����B		*/
	bool_t (*ackci)	(T_PPP_FSM *, T_NET_BUF *);
					/* ACK ����M�����Ƃ��̏���	*/
	int_t  (*nakci)	(T_PPP_FSM *, T_NET_BUF *);
					/* NAK ����M�����Ƃ��̏���	*/
	int_t  (*rejci)	(T_PPP_FSM *, T_NET_BUF *);
					/* REJ ����M�����Ƃ��̏���	*/
	int_t  (*reqci)	(T_PPP_FSM *, T_NET_BUF *, T_NET_BUF *);
					/* ����̍\�������m�F����B	*/
	void (*up)	(T_PPP_FSM *);	/* �����N�̐ڑ����m������B	*/
	void (*down)	(T_PPP_FSM *);	/* �����N�̐ڑ����������B	*/
	void (*starting)(T_PPP_FSM *);	/* ���ʑw���J�n����B		*/
	void (*finished)(T_PPP_FSM *);	/* ���ʑw���I������B		*/
	void (*retrans)	(T_PPP_FSM *);	/* �đ�����B			*/
					/* �s���� CP ����M�����Ƃ��̏���	*/
	bool_t  (*extcode)(T_PPP_FSM *, uint8_t, uint8_t, T_NET_BUF *);
	} T_PPP_FSM_CALLBACKS;

/*
 *  FSM �̏��
 */

#define PPP_FSM_INITIAL		0	/* ���ڑ��A���I�[�v��	*/
#define PPP_FSM_STARTING	1	/* ���ڑ��A�I�[�v��	*/
#define PPP_FSM_CLOSED		2	/* �ڑ��A  ���I�[�v��	*/
#define PPP_FSM_STOPPED		3	/* �I�[�v���A�ؒf�҂�	*/
#define PPP_FSM_CLOSING		4	/* �ؒf���A���I�[�v��	*/
#define PPP_FSM_STOPPING	5	/* �ؒf���A�I�[�v��	*/
#define PPP_FSM_REQSENT		6	/* Config REQ ���M�ς�	*/
#define PPP_FSM_ACKRCVD		7	/* Config ACK ��M�ς�	*/
#define PPP_FSM_ACKSENT		8	/* Config ACK ���M�ς�	*/
#define PPP_FSM_OPENED		9	/* �ڑ��A�ʐM�\	*/

/*
 *  �I�[�v�����̓��샂�[�h
 */

#define PPP_OPEN_PASSIVE	false	/* �󓮃I�[�v��		*/
#define PPP_OPEN_ACTIVE		true	/* �\���I�[�v��		*/

/*
 *  �đ��A�^�C���A�E�g�̊���l
 */

#define DEF_PPP_TIMEOUT		(3*NET_TIMER_HZ)
					/* RFC1661 �ł�  3 �b			*/
#define MAX_PPP_TERMINATES	2	/* Terminate-Requests �̍ő�đ���	*/
					/* RFC1661 �ł�  2 ��			*/
#define MAX_PPP_CONFIGURES	10	/* Configure-Requests �̍ő�đ���	*/
					/* RFC1661 �ł� 10 ��			*/
#define MAX_PPP_FAILURES	5	/* Configure-NAK �̍ő�ٔF��		*/
					/* RFC1661 �ł�  5 ��			*/

/*
 *  �֐�
 */

extern void fsm_init    (T_PPP_FSM *fsm);
extern void fsm_lowerup (T_PPP_FSM *fsm);
extern void fsm_lowerdown(T_PPP_FSM *fsm);
extern void fsm_open    (T_PPP_FSM *fsm);
extern void fsm_close	(T_PPP_FSM *fsm);
extern void fsm_input	(T_PPP_FSM *fsm, T_NET_BUF *data);
extern void fsm_protreject(T_PPP_FSM *fsm);

/*
 *  �ϐ�
 */

extern uint8_t ppp_open_mode;

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _PPP_FSM_H_ */
