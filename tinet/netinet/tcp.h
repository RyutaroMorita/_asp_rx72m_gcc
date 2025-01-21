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
 *  @(#) $Id: tcp.h,v 1.5 2009/12/24 05:47:21 abe Exp $
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
 *	@(#)tcp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/tcp.h,v 1.10.2.1 1999/08/29 16:29:52 peter Exp $
 */
 
#ifndef _TCP_H_
#define _TCP_H_

/*
 *  TCP �w�b�_�ARFC 793 �Q��
 */

typedef struct t_tcp_hdr {
	uint16_t	sport;		/* ���M���|�[�g�ԍ�			*/
	uint16_t	dport;		/* ����|�[�g�ԍ�			*/

	uint32_t	seq;		/* SEQ �ԍ�				*/

	uint32_t	ack;		/* ACK �ԍ�				*/

	uint8_t		doff;		/* �f�[�^�I�t�Z�b�g(���4�r�b�g)	*/
	uint8_t		flags;		/* �t���O(����6�r�b�g)			*/
	uint16_t	win;		/* �E�B���h�T�C�Y			*/

	uint16_t	sum;		/* �`�F�b�N�T��				*/
	uint16_t	urp;		/* �ً}�|�C���^				*/
	} T_TCP_HDR;

#define TCP_HDR_SIZE			(sizeof(T_TCP_HDR))

/*
 *  TCP �w�b�_�\���̃����o�A�N�Z�X�}�N��
 */

#define TCP_MAKE_DATA_OFF(o)	((uint8_t)(((uint8_t)(o) << 2) & 0xf0))
#define TCP_DATA_OFF(o)		(((uint8_t)(o) & UINT_C(0xf0)) >> 2)
#define TCP_HDR_LEN(o)		(TCP_DATA_OFF(o))

/*
 *  TCP �w�b�_�̃t���O�t�B�[���h�̒l�̒�`
 */

#define TCP_FLG_FIN		UINT_C(0x01)	/* FIN:	�ŏI			*/
#define TCP_FLG_SYN		UINT_C(0x02)	/* SYN:	����			*/
#define TCP_FLG_RST		UINT_C(0x04)	/* RST:	�R�l�N�V�����̃��Z�b�g	*/
#define TCP_FLG_PUSH		UINT_C(0x08)	/* PUSH:�v�b�V���@�\		*/
#define TCP_FLG_ACK		UINT_C(0x10)	/* ACK:	�m�艞��		*/
#define TCP_FLG_URG		UINT_C(0x20)	/* URG:	�ً}���		*/

/*
 *  TCP �I�v�V�����̒�`
 */

/* �I�v�V�����̌^ */

#define TCP_OPT_EOL		UINT_C(0)	/* �ŏI				*/
#define TCP_OPT_NOP		UINT_C(1)	/* �������Ȃ�			*/
#define TCP_OPT_MAXSEG		UINT_C(2)	/* �ő�Z�O�����g��		*/
#define TCP_OPT_WINDOW		UINT_C(3)	/* �E�B���h�X�P�[�����O		*/
#define TCP_OPT_SACK_PERM	UINT_C(4)	/* �I�� ACK ����		*/
#define TCP_OPT_SACK		UINT_C(5)	/* �I�� ACK			*/
#define TCP_OPT_TIMESTAMP	UINT_C(8)	/* �^�C���X�^���v		*/
#define TCP_OPT_CC		UINT_C(11)	/* �ڑ��J�E���g			*/
#define TCP_OPT_CCNEW		UINT_C(12)	/* �ڑ��J�E���g			*/
#define TCP_OPT_CCECHO		UINT_C(13)	/* �ڑ��J�E���g			*/

/* �I�v�V�����̒��� */

#define TCP_OPT_LEN_MAXSEG	4		/* �ő�Z�O�����g��		*/
#define TCP_OPT_LEN_WINDOW	3		/* �E�B���h�X�P�[�����O		*/
#define TCP_OPT_LEN_SACK_PERM	4		/* �I�� ACK ����		*/
#define TCP_OPT_LEN_SACK	5		/* �I�� ACK			*/
#define TCP_OPT_LEN_TIMESTAMP	10		/* �^�C���X�^���v		*/
#define TCP_OPT_LEN_CC		6		/* �ڑ��J�E���g			*/
#define TCP_OPT_LEN_CCNEW	6		/* �ڑ��J�E���g			*/
#define TCP_OPT_LEN_CCECHO	6		/* �ڑ��J�E���g			*/

/*
 *  TCP �ő�Z�O�����g�T�C�Y
 */

/*
 *  IPv4 �� TCP �ő�Z�O�����g�T�C�Y
 *  IP4_MSS �� 576 �ŁA�W���� IPv4 �w�b�_�� (20) ��
 *  TCP �w�b�_�� (20) ���������l 536 �ł��邪�A512 ��W���Ƃ���B
 */

#define TCP_MSS			UINT_C(512)

/*
 *  IPv6 �� TCP �ő�Z�O�����g�T�C�Y
 *  IPV6_MMTU �� 1280 �ŁA�W���� IPv6 �w�b�_�� (40) ��
 *  TCP �w�b�_�� (20) ���������l 1220 �ł��邪�A1024 ��W���Ƃ���B
 */

#define TCP6_MSS		UINT_C(1024)

/*
 *  TCP �ŏ��Z�O�����g�T�C�Y
 *
 *  256�i�ŏ������N MTU�j- 40 = 216
 */

#define TCP_MINMSS		UINT_C(216)

/*
 *  TCP �ő�E�B���h�E�T�C�Y
 */

#define MAX_TCP_WIN_SIZE	UINT_C(65535)

#endif	/* of #ifndef _TCP_H_ */
