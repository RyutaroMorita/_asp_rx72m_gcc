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
 *  @(#) $Id: ppp_ccp.c,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * ccp.c - PPP Compression Control Protocol.
 *
 * Copyright (c) 1994 The Australian National University.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, provided that the above copyright
 * notice appears in all copies.  This software is provided without any
 * warranty, express or implied. The Australian National University
 * makes no representations about the suitability of this software for
 * any purpose.
 *
 * IN NO EVENT SHALL THE AUSTRALIAN NATIONAL UNIVERSITY BE LIABLE TO ANY
 * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
 * THE AUSTRALIAN NATIONAL UNIVERSITY HAVE BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * THE AUSTRALIAN NATIONAL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE AUSTRALIAN NATIONAL UNIVERSITY HAS NO
 * OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 */

/*
 *	   PPP Compression Control Protocol (CCP) Module
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
 * $FreeBSD: src/usr.sbin/ppp/ccp.c,v 1.54.2.2 2000/08/19 09:29:59 brian Exp $
 *
 *	TODO:
 *		o Support other compression protocols
 */

/*
 *  �����\��A���݂͂��ׂċ���
 */

#include <t_services.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net_buf.h>
#include <net/net_debug.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_fsm.h>
#include <net/ppp_ccp.h>

/*
 *  �֐�
 */

static void ccp_init (void);
static void ccp_input (T_NET_BUF *nbuf);
static void ccp_protrej (void);
static void ccp_lowerup (void);
static void ccp_lowerdown (void);
static void ccp_open (void);
static void ccp_close (void);

/*
 * FSM ����ďo�����R�[���o�b�N��
 */

static int_t  ccp_reqci	(T_PPP_FSM *fsm, T_NET_BUF *nbuf);
					/* ����̍\�������m�F����B	*/

/*
 *  �S��ϐ�
 */

T_PPP_FSM_CALLBACKS ccp_callbacks = {
	NULL,				/* ���\���������Z�b�g����B	*/
	NULL,				/* �\�����̒�����Ԃ��B		*/
	NULL,				/* ���\������ǉ�����B		*/
	NULL,				/* ACK ����M�����Ƃ��̏���	*/
	NULL,				/* NAK ����M�����Ƃ��̏���	*/
	NULL,				/* REJ ����M�����Ƃ��̏���	*/
	ccp_reqci,			/* ����̍\�������m�F����B	*/
	NULL,				/* �����N�ڑ����m������B		*/
	NULL,				/* �����N�ڑ����������B		*/
	NULL,				/* ���ʑw���J�n����B		*/
	NULL,				/* ���ʑw���I������B		*/
	NULL,				/* �đ�����B			*/
	NULL,				/* �s���� CP ����M�����Ƃ��̏���	*/
	};

T_PPP_FSM ccp_fsm = {
	&ccp_callbacks,			/* �R�[���o�b�N�֐�		*/
	PPP_CCP,			/* �v���g�R��			*/
	};

T_PPP_PROTENT ccp_protent = {
	PPP_CCP,
	ccp_init,			/* ������			*/
	ccp_input,			/* ����				*/
	ccp_protrej,			/* Proto-REJ ��M����		*/
	ccp_lowerup,			/* ���ʑw���N������		*/
	ccp_lowerdown,			/* ���ʑw���~����		*/
	ccp_open,			/* �I�[�v������			*/
	ccp_close,			/* �N���[�Y����			*/
	NULL,				/* �f�[�^����			*/
	};

/*
 *  ccp_init -- CCP ���W���[���̏�����
 */

static void
ccp_init (void)
{
	fsm_init(&ccp_fsm);
	}

/*
 *  ccp_input -- CCP ����
 */

static void
ccp_input (T_NET_BUF *nbuf)
{
	NET_COUNT_PPP_CCP(net_count_ppp_ccp_in_octets,  nbuf->len);
	NET_COUNT_PPP_CCP(net_count_ppp_ccp_in_packets, 1);
	fsm_input(&ccp_fsm, nbuf);
	}

/*
 *  ccp_reqci -- ����̍\��������͂���B
 */

static int_t
ccp_reqci (T_PPP_FSM *fsm, T_NET_BUF *nbuf)
{
/*
 *  �����\��A���݂͂��ׂẴI�v�V���������ۂ���B
 */
	return nbuf->len > (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR)) ? PPP_CONFREJ : PPP_CONFACK;
	}

/*
 *  ccp_protrej -- Proto-REJ ����M�����Ƃ��̏���
 */

static void
ccp_protrej (void)
{
	fsm_lowerdown(&ccp_fsm);
	}

/*
 *  ccp_lowerup -- CCP ���ʑw���N������B
 */

static void
ccp_lowerup (void)
{
	fsm_lowerup(&ccp_fsm);
	}

/*
 *  ccp_lowerdown -- CCP ���ʑw���~����B
 */

static void
ccp_lowerdown (void)
{
	fsm_lowerdown(&ccp_fsm);
	}

/*
 *  ccp_open -- CCP �̃I�[�v
 */

static void
ccp_open (void)
{
	fsm_open(&ccp_fsm);
	}

/*
 *  ccp_close -- CCP �̃N���[�Y
 */

static void
ccp_close (void)
{
	fsm_close(&ccp_fsm);
	}
