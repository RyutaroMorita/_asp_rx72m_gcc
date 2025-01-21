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
 *  @(#) $Id: if_arp.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * Copyright (c) 1986, 1993
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
 *	@(#)if_arp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if_arp.h,v 1.10.2.3 1999/11/19 09:30:31 julian Exp $
 */

#ifndef _IF_ARP_H_
#define _IF_ARP_H_

#ifdef SUPPORT_ETHER

/*
 *  Address Resolution Protocol.
 *
 *  RFC 826 �Q��
 */

/*
 *  �\����
 */

/* ARP �w�b�_ */

typedef struct t_arp_hdr {
	uint16_t	hrd_addr;	/* �����A�h���X�t�H�[�}�b�g	*/
	uint16_t	proto;		/* �v���g�R��			*/
	uint8_t		hdr_len;	/* �����A�h���X��		*/
	uint8_t		proto_len;	/* �v���g�R����			*/
	uint16_t	opcode;		/* ���߃R�[�h			*/
	} T_ARP_HDR;

#define ARP_HDR_SIZE			(sizeof(T_ARP_HDR))
#define IF_ARP_HDR_SIZE			(IF_HDR_SIZE + ARP_HDR_SIZE)

#define GET_ARP_HDR(nbuf)		((T_ARP_HDR*)((nbuf)->buf + IF_HDR_SIZE))

#define GET_IF_ARP_HDR_SIZE(nbuf)	(IF_HDR_SIZE + ARP_HDR_SIZE)

/* hrd_addr�A�����A�h���X�t�H�[�}�b�g�̒l */

#define ARPHRD_ETHER	1	/* Ethernet	*/

/* opcode, ���߃R�[�h�̒l */

#define ARPOP_REQUEST		UINT_C(1)	/* �A�h���X�����v��		*/
#define ARPOP_REPLY		UINT_C(2)	/* �A�h���X��������		*/
#define ARPOP_REV_REQUEST	UINT_C(3)	/* �v���g�R���E�A�h���X�����v��	*/
#define ARPOP_REV_REPLY		UINT_C(4)	/* �v���g�R���E�A�h���X�����v��	*/
#define ARPOP_INV_REQUEST	UINT_C(8)	/* �I�[���ʗv��			*/
#define ARPOP_INV_REPLY		UINT_C(9)	/* �I�[���ʗv��			*/

/*
 *  �C�[�T�l�b�g�h���C�o���W���[���Ŏg�p����� ARP ���
 */

typedef struct arpcom {
	uint8_t		mac_addr[ETHER_ADDR_LEN];
	} T_ARPCOM;

/*
 *  ARP �L���b�V���X�V�^�C�}�̒�`
 */

#define ARP_TIMER_TMO		(60*NET_TIMER_HZ)	/* �^�C���A�E�g�A60 [s]	*/

/*
 *  �ϐ�
 */

extern const uint8_t	ether_broad_cast_addr[ETHER_ADDR_LEN];

#endif	/* of #ifdef SUPPORT_ETHER */

#endif	/* of #ifndef _IF_ARP_H_ */
