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
 *  @(#) $Id: if_loop.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _IF_LOOP_H_
#define _IF_LOOP_H_

#ifdef SUPPORT_LOOP

/*
 *  ���[�J�����[�v�o�b�N�C���^�t�F�[�X�E�w�b�_�ƃA�h���X
 */

typedef struct t_loop_hdr  { } T_LOOP_HDR;
typedef struct t_loop_addr { } T_LOOP_ADDR;

/*
 *  �C���^�t�F�[�X�̑I���}�N��
 */

#define T_IF_HDR		T_LOOP_HDR		/* �C���^�t�F�[�X�̃w�b�_	*/
#define T_IF_ADDR		T_LOOP_ADDR		/* �C���^�t�F�[�X�̃A�h���X	*/
#define IF_HDR_ALIGN		4			/* �w�b�_�̃A���C���P��		*/
#define IF_MTU			LOMTU			/* �C���^�t�F�[�X�� MTU		*/

#define IF_OUTPUT(o,d,g,t)	looutput(o,t)		/* �C���^�t�F�[�X�̏o�͊֐�	*/
#define IF_RAW_OUTPUT(o,t)	looutput(o,t)		/* �C���^�t�F�[�X�̏o�͊֐��A�A�h���X��������*/
#define IF_SET_PROTO(b,p)				/* �C���^�t�F�[�X�̃v���g�R���ݒ�֐�	*/
#define IF_GET_IFNET()		loop_get_ifnet()	/* �l�b�g���[�N�C���^�t�F�[�X�\���̂�Ԃ��B		*/

/* IPv4 �֌W */

#define IF_PROTO_IP		0			/* �C���^�t�F�[�X�� IP �v���g�R���w��		*/

/* IPv6 �֌W */

#define MAX_IF_MADDR_CNT	0			/* �C���^�t�F�[�X�̃}���`�L���X�g�A�h���X�z��̍ő�T�C�Y	*/
#define IF_IN6_NEED_CACHE(i)	(false)			/* �ߗגT���L���b�V�����g�p����B				*/

/*
 *  �O���Q��
 */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_IFNET_DEFINED

typedef struct t_ifnet T_IFNET;

#define T_IFNET_DEFINED

#endif	/* of #ifndef T_IFNET_DEFINED */

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�Ɉˑ����Ȃ��\�t�g�E�F�A���
 */

struct t_if_softc { };

/*
 *  �֐�
 */

extern T_IFNET *loop_get_ifnet (void);
ER looutput (T_NET_BUF *output, TMO tmout);

/*
 *  ���[�J�����[�v�o�b�N�C���^�t�F�[�X�E�����^�X�N
 */

extern void	if_loop_output_task(intptr_t exinf);
extern void	if_loop_input_task(intptr_t exinf);

#endif	/* of #ifdef SUPPORT_LOOP */

#endif	/* of #ifndef _IF_LOOP_H_ */
