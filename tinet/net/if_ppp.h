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
 *  @(#) $Id: if_ppp.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * if_ppp.h - Point-to-Point Protocol definitions.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/sys/net/if_ppp.h,v 1.13.2.1 1999/08/29 16:28:21 peter Exp $
 */

#ifndef _IF_PPP_H_
#define _IF_PPP_H_

#ifdef SUPPORT_PPP

/*
 *  �C���^�t�F�[�X�̑I���}�N��
 */

#define T_IF_HDR		T_PPP_HDR	/* �C���^�t�F�[�X�̃w�b�_			*/
#define IF_HDR_ALIGN		2		/* �w�b�_�̃A���C���P��			*/
#define IF_MTU			DEF_PPP_MTU	/* �C���^�t�F�[�X�� MTU			*/
						/* �C���^�t�F�[�X�� IPv4 �A�h���X		*/
#define IF_PROTO_IP		PPP_IP		/* �C���^�t�F�[�X�� IP �v���g�R���w��	*/

#define IF_OUTPUT(o,d,g,t)	ppp_output(o,t)		/* �C���^�t�F�[�X�̏o�͊֐�		*/
#define IF_RAW_OUTPUT(o,t)	ppp_output(o,t)		/* �C���^�t�F�[�X�̏o�͊֐��A�A�h���X��������*/
							/* �C���^�t�F�[�X�̃v���g�R���ݒ�֐�	*/
#define IF_SET_PROTO(b,p)	(*GET_PPP_HDR(b) = htons(p))
#define IF_GET_IFNET()		ppp_get_ifnet()		/* �l�b�g���[�N�C���^�t�F�[�X�\���̂�Ԃ��B		*/

/*
 *  MTU (MRU) �Ɋւ����`
 */

#define DEF_PPP_MTU		1500	/* PPP �� �W�� MTU	*/
#define MAX_PPP_MTU		16384	/* PPP �� �ő� MTU	*/
#define MIN_PPP_MTU		128	/* PPP �� �ŏ� MTU	*/

/*
 *  PPP �w�b�_
 */

typedef uint16_t T_PPP_HDR;				/* ��ʃv���g�R��		*/

/*
 *  �O���Q��
 */

#ifndef T_IFNET_DEFINED

typedef struct t_ifnet T_IFNET;

#define T_IFNET_DEFINED

#endif	/* of #ifndef T_IFNET_DEFINED */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�Ɉˑ����Ȃ��\�t�g�E�F�A���
 */

struct t_if_softc { };

/*
 *  �֐�
 */

extern T_IFNET *ppp_get_ifnet (void);
ER ppp_output (T_NET_BUF *data, TMO tmout);

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _IF_PPP_H_ */
