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
 *  @(#) $Id: ip_icmp.h,v 1.5 2009/12/24 05:47:21 abe Exp $
 */

/*
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)ip_icmp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/ip_icmp.h,v 1.12.2.2 1999/11/18 08:51:44 peter Exp $
 */
 
#ifndef _IP_ICMP_H_
#define _IP_ICMP_H_

/*
 *  ICMP �w�b�_�̒�`�ARFC 792
 */

typedef struct t_icmp_hdr {
	uint8_t		type;		/* ���b�Z�[�W�̌^	*/
	uint8_t		code;		/* �T�u�^		*/
	uint16_t	sum;		/* �`�F�b�N�T��		*/
	union {
		struct id_seq {
			uint16_t	id;
			uint16_t	seq;
			} id_seq;
		T_IN4_ADDR	addr;
		} data;
	} T_ICMP4_HDR;

#define ICMP4_HDR_SIZE			(sizeof(T_ICMP4_HDR))
#define IP4_ICMP4_HDR_SIZE		(IP4_HDR_SIZE + ICMP4_HDR_SIZE)
#define IF_IP4_ICMP4_HDR_SIZE		(IF_IP4_HDR_SIZE + ICMP4_HDR_SIZE)
#define IF_IP4_ICMP4_HDR_OFFSET		(IF_IP4_HDR_SIZE)

#define GET_ICMP4_HDR(nbuf,ihoff)	((T_ICMP4_HDR*)((uint8_t*)((nbuf)->buf) + ihoff))
#define GET_ICMP4_SDU(nbuf,ihoff)	((uint8_t*)((nbuf)->buf) + ihoff + ICMP4_HDR_SIZE)

#define GET_ICMP4_HDR_OFFSET(nbuf)	(GET_IF_IP_HDR_SIZE(nbuf))

#define GET_IP4_ICMP4_HDR_SIZE(nbuf)	(GET_IP4_HDR_SIZE(GET_IP4_HDR(nbuf)) + ICMP4_HDR_SIZE)
#define GET_IF_IP4_ICMP4_HDR_SIZE(nbuf)	(IF_HDR_SIZE + GET_IP4_ICMP4_HDR_SIZE(nbuf))

/*
 *  ���b�Z�[�W�̌^
 */

#define ICMP4_ECHO_REPLY	UINT_C(0)	/* �G�R�[����		*/
#define ICMP4_UNREACH		UINT_C(3)	/* �G���[		*/
#define ICMP4_SOURCE_QUENCH	UINT_C(4)	/* ���M����		*/
#define ICMP4_REDIRECT		UINT_C(5)	/* �����ύX		*/
#define ICMP4_ECHO_REQUEST	UINT_C(8)	/* �G�R�[�v��		*/
#define ICMP4_TIME_EXCEEDED	UINT_C(11)	/* ���M����		*/
#define ICMP4_PARAMETER		UINT_C(12)	/* �p�����[�^�ُ�	*/
#define ICMP4_TIME_REQUEST	UINT_C(13)	/* �^�C���X�^���v�v��	*/
#define ICMP4_TIME_REPLY	UINT_C(14)	/* �^�C���X�^���v����	*/
#define ICMP4_MASK_REQUEST	UINT_C(17)	/* �A�h���X�}�X�N�v��	*/
#define ICMP4_MASK_REPLY	UINT_C(18)	/* �A�h���X�}�X�N����	*/

/*
 *  �T�u�^
 */

/* ICMP4_UNREACH (3)	*/

#define ICMP4_UNREACH_NET		UINT_C(0)	/* �l�b�g���[�N		*/
#define ICMP4_UNREACH_HOST		UINT_C(1)	/* �z�X�g		*/
#define ICMP4_UNREACH_PROTOCOL		UINT_C(2)	/* �v���g�R��		*/
#define ICMP4_UNREACH_PORT		UINT_C(3)	/* �|�[�g		*/
#define ICMP4_UNREACH_FLAG		UINT_C(4)	/* ����			*/
#define ICMP4_UNREACH_SRC_FAIL		UINT_C(5)	/* �\�[�X�o�H		*/
#define ICMP4_UNREACH_NET_UNKNOWN	UINT_C(6)	/* �l�b�g���[�N�s��	*/
#define ICMP4_UNREACH_HOST_UNKNOWN	UINT_C(7)	/* �z�X�g�s��		*/
#define ICMP4_UNREACH_ISOLATED		UINT_C(8)	/* ����			*/
#define ICMP4_UNREACH_NET_PROHIB	UINT_C(9)	/* 			*/
#define ICMP4_UNREACH_HOST_PROHIB	UINT_C(10)	/* 			*/
#define ICMP4_UNREACH_TOS_NET		UINT_C(11)	/* �l�b�g���[�N�ւ̕s��TOS*/
#define ICMP4_UNREACH_TOS_HOST		UINT_C(12)	/* �z�X�g�ւ̕s��TOS	*/
#define ICMP4_UNREACH_FILTER_PROHIB	UINT_C(13)	/* 			*/
#define ICMP4_UNREACH_HOST_PRECEDENCE	UINT_C(14)	/* 			*/
#define ICMP4_UNREACH_PRECEDENCE_CUTOFF	UINT_C(15)	/* 			*/

/* ICMP4_REDIRECT (5)	*/

#define ICMP4_REDIRECT_NET		UINT_C(0)	/* �l�b�g���[�N		*/
#define ICMP4_REDIRECT_HOST		UINT_C(1)	/* �z�X�g		*/
#define ICMP4_REDIRECT_PORT_AND_NET	UINT_C(2)	/* �|�[�g�ԍ��ƃl�b�g	*/
#define ICMP4_REDIRECT_PORT_AND_HOST	UINT_C(3)	/* �|�[�g�ԍ��ƃz�X�g	*/

/*
 *  �S��ϐ�
 */

/*
 *  �֐��V�~�����[�V�����}�N��
 */

#ifndef ICMP_REPLY_ERROR

#define _tinet_icmp_error(code,data)

#endif	/* of #ifdef ICMP_REPLY_ERROR */

/*
 *  �֐�
 */

extern uint_t icmp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);

#ifdef ICMP_REPLY_ERROR

extern void icmp_error (uint8_t code, T_NET_BUF *data);

#endif	/* of #ifdef ICMP_REPLY_ERROR */

/*
 *  TINET �Ǝ� API
 */

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

extern void icmp_echo_reply (T_NET_BUF *input, uint_t ihoff);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

#endif	/* of #ifndef _IP_ICMP_H_ */
