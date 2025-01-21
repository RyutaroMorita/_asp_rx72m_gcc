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
 *  @(#) $Id: if_ether.h,v 1.5 2009/12/24 05:47:21 abe Exp $
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
 *	@(#)if_ether.h	8.3 (Berkeley) 5/2/95
 * $FreeBSD: src/sys/netinet/if_ether.h,v 1.21.2.1 1999/08/29 16:29:31 peter Exp $
 */

#ifndef _IF_ETHER_H_
#define _IF_ETHER_H_

#ifdef SUPPORT_ETHER

/*
 *  Ethernet Address Resolution Protocol.
 *
 *  RFC 826 �Q��
 */

typedef struct t_ether_arp_hdr {
	uint8_t		shost[ETHER_ADDR_LEN];	/* ���M�z�X�g�̕����A�h���X	*/
	uint8_t		sproto[IPV4_ADDR_LEN];	/* ���M�z�X�g�� IP �A�h���X	*/
	uint8_t		thost[ETHER_ADDR_LEN];	/* �����Ώە����A�h���X		*/
	uint8_t		tproto[IPV4_ADDR_LEN];	/* �����Ώ� IP �A�h���X		*/
	} T_ETHER_ARP_HDR;

#define ETHER_ARP_HDR_SIZE		(sizeof(T_ETHER_ARP_HDR))
#define IF_ARP_ETHER_HDR_SIZE		(IF_HDR_SIZE + ARP_HDR_SIZE + ETHER_ARP_HDR_SIZE)

#define GET_ETHER_ARP_HDR(nbuf)		((T_ETHER_ARP_HDR*)((nbuf)->buf + GET_IF_ARP_HDR_SIZE(nbuf)))

/*
 *  ARP �L���b�V���G���g��
 */

typedef struct arp_entry {
	T_NET_BUF	*hold;		/* ARP �̉����҂��o�̓t���[��	*/
	T_IN4_ADDR	ip_addr;	/* IP �A�h���X			*/
	uint16_t	expire;		/* �j���܂ł̎��ԁA0 �Ȃ疢�g�p	*/
	uint8_t		mac_addr[ETHER_ADDR_LEN];	/* MAC �A�h���X	*/
	} T_ARP_ENTRY;

/*
 *  �֐�
 */

extern ER arp_request (T_IF_ADDR *ifaddr, T_IN4_ADDR dst);
extern void arp_input (T_IF_ADDR *ifaddr, T_NET_BUF *input);
extern bool_t arp_resolve (T_IF_ADDR *ifaddr, T_NET_BUF *output, T_IN4_ADDR gw);
extern void arp_init (void);
extern const T_ARP_ENTRY *arp_get_cache (void);

/*
 *  TINET �Ǝ� API
 */

#ifdef ARP_CFG_CALLBACK_DUPLICATED

extern bool_t arp_callback_duplicated(uint8_t *shost);

#endif	/* of #ifdef ARP_CFG_CALLBACK_DUPLICATED */

#endif	/* of #ifdef SUPPORT_ETHER */

#endif	/* of #ifndef _IF_ETHER_H_ */
