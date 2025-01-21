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
 *  @(#) $Id: ppp.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
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
 */

#ifndef _PPP_H_
#define _PPP_H_

/*
 *  PPP �w�b�_�̃v���g�R���t�B�[���h�̒l
 */

#define PPP_IP		UINT_C(0x0021)		/* IP   */

#define PPP_IPCP	UINT_C(0x8021)		/* IPCP */
#define PPP_CCP		UINT_C(0x80fd)		/* CCP */

#define PPP_LCP		UINT_C(0xc021)		/* LCP  */
#define PPP_PAP		UINT_C(0xc023)		/* PAP  */
#define PPP_LQR		UINT_C(0xc025)		/* LQR  */
#define PPP_CHAP	UINT_C(0xc223)		/* CHAP */

#define GET_PPP_HDR(nbuf)	((T_PPP_HDR*)((nbuf)->buf))

/*
 *  �����N�̏��
 */

#define PPP_PHASE_DEAD		0
#define PPP_PHASE_INITIALIZE	1
#define PPP_PHASE_DORMANT	2
#define PPP_PHASE_ESTABLISH	3
#define PPP_PHASE_AUTHENTICATE	4
#define PPP_PHASE_CALLBACK	5
#define PPP_PHASE_NETWORK	6
#define PPP_PHASE_TERMINATE	7
#define PPP_PHASE_HOLDOFF	8

/*
 *  PPP �����N���� (CP) �w�b�_�\����
 */

typedef struct t_ppp_cp_hdr {
	uint8_t		code;		/* ����R�[�h	*/
	uint8_t		id;		/* ���ʎq	*/
	uint16_t	len;		/* ����		*/
	} T_PPP_CP_HDR;

#define GET_PPP_CP_HDR(nbuf)	((T_PPP_CP_HDR*)((nbuf)->buf + sizeof(T_PPP_HDR)))

/*
 *  PPP �����N���� (CP) �̐���R�[�h
 */

#define PPP_VENDER		UINT_C(0)	/* Vender Specific		*/
#define PPP_CONFREQ		UINT_C(1)	/* Configuration Request	*/
#define PPP_CONFACK		UINT_C(2)	/* Configuration ACK		*/
#define PPP_CONFNAK		UINT_C(3)	/* Configuration NAK		*/
#define PPP_CONFREJ		UINT_C(4)	/* Configuration Reject		*/
#define PPP_TERMREQ		UINT_C(5)	/* Termination Request		*/
#define PPP_TERMACK		UINT_C(6)	/* Termination ACK		*/
#define PPP_CODEREJ		UINT_C(7)	/* Code Reject			*/

/*
 * �\����� (CI) �w�b�_
 */

typedef struct t_ppp_ci_hdr {
	uint8_t		type;		/* CI �̌^	*/
	uint8_t		len;		/* ����		*/
	} T_PPP_CI_HDR;

#endif	/* of #ifndef _PPP_H_ */
