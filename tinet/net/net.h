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
 *  @(#) $Id: net.h,v 1.5.4.1 2015/02/05 02:09:13 abe Exp abe $
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
 */

#ifndef _NET_H_
#define _NET_H_

/*
 *  �o�C�g�I�[�_�̒�`
 */

#define _NET_CFG_LITTLE_ENDIAN	1234
#define _NET_CFG_BIG_ENDIAN	4321

#ifdef TARGET_KERNEL_ASP

#if defined(SIL_ENDIAN_LITTLE)

#define _NET_CFG_BYTE_ORDER	_NET_CFG_LITTLE_ENDIAN

#elif defined(SIL_ENDIAN_BIG)

#define _NET_CFG_BYTE_ORDER	_NET_CFG_BIG_ENDIAN

#else	/* of #if defined(SIL_ENDIAN_BIG) */

#error "SIL_ENDIAN expected."

#endif	/* of #if defined(SIL_ENDIAN_BIG) */

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#if SIL_ENDIAN == SIL_ENDIAN_LITTLE

#define _NET_CFG_BYTE_ORDER	_NET_CFG_LITTLE_ENDIAN

#elif SIL_ENDIAN == SIL_ENDIAN_BIG	/* of #if SIL_ENDIAN == SIL_ENDIAN_LITTLE */

#define _NET_CFG_BYTE_ORDER	_NET_CFG_BIG_ENDIAN

#else	/* of #if SIL_ENDIAN == SIL_ENDIAN_LITTLE */

#error "SIL_ENDIAN expected."

#endif	/* of #if SIL_ENDIAN == SIL_ENDIAN_LITTLE */

#endif	/* of #ifdef TARGET_KERNEL_JSP */

/*
 *  �o�C�g�I�[�_�ϊ��̒�`
 */

#if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN

#define ntohs(n)		((uint16_t)n)
#define htons(h)		((uint16_t)h)
#define ntohl(n)		((uint32_t)n)
#define htonl(h)		((uint32_t)h)

#define NTOHS(n)
#define HTONS(h)
#define NTOHL(n)
#define HTONL(h)

/*
 *  ����: IP�w�b�_�ȍ~�́A4 �o�C�g���E�ɃA���C������Ă��鎖��
 *        �O��Ƃ��Ă��邪�A4 �o�C�g���E�ŃA�N�Z�X����
 *        �v���Z�b�T�ŁA�l�b�g���[�N���̃f�[�^���A4 �o�C�g���E�ɃA���C��
 *        ����Ă��Ȃ��ꍇ�́Antoahl�Aahtonl�Anahcmpl ���g�p���邱�ƁB
 */

#define ntoahl(h,n)		memcpy((uint8_t*)&(h),(n),4)
#define ahtonl(n,h)		memcpy((n),(uint8_t*)&(h),4)

#define nahcmpl(n,h)		memcmp((n),(uint8_t*)&(h),4)

#elif _NET_CFG_BYTE_ORDER == _NET_CFG_LITTLE_ENDIAN

#ifndef NET_REV_ENDIAN_HWORD

#define NET_REV_ENDIAN_HWORD(d)	((uint16_t)((((uint16_t)(d)&0xff)<<8)|(((uint16_t)(d)>>8)&0xff)))

#endif	/* of #ifndef NET_REV_ENDIAN_HWORD */

#ifndef NET_REV_ENDIAN_WORD

#define NET_REV_ENDIAN_WORD(d)	((uint32_t)((((uint32_t)(d)&0xff)<<24)|(((uint32_t)(d)&0xff00)<<8)| \
				            (((uint32_t)(d)>>8)&0xff00)|(((uint32_t)(d)>>24)&0xff)))

#endif	/* of #ifndef NET_REV_ENDIAN_WORD */

#define ntohs(n)		NET_REV_ENDIAN_HWORD(n)
#define htons(h)		NET_REV_ENDIAN_HWORD(h)
#define ntohl(n)		NET_REV_ENDIAN_WORD(n)
#define htonl(h)		NET_REV_ENDIAN_WORD(h)

#define NTOHS(n)		((n)=NET_REV_ENDIAN_HWORD(n))
#define HTONS(h)		((h)=NET_REV_ENDIAN_HWORD(h))
#define NTOHL(n)		((n)=NET_REV_ENDIAN_WORD(n))
#define HTONL(h)		((h)=NET_REV_ENDIAN_WORD(h))

/*
 *  ����: IP�w�b�_�ȍ~�́A4 �o�C�g���E�ɃA���C������Ă��鎖��
 *        �O��Ƃ��Ă��邪�A4 �o�C�g���E�ŃA�N�Z�X����
 *        �v���Z�b�T�ŁA�l�b�g���[�N���̃f�[�^���A4 �o�C�g���E�ɃA���C��
 *        ����Ă��Ȃ��ꍇ�́Antoahl�Aahtonl�Anahcmpl ���g�p���邱�ƁB
 */

#ifndef _MACRO_ONLY

extern void rev_memcpy_word (uint8_t *dst, uint8_t *src);
extern int  rev_memcmp_word (uint8_t *data1, uint8_t *data2);

#endif	/* of #ifndef _MACRO_ONLY */

#define ntoahl(h,n)		rev_memcpy_word((uint8_t*)&(h),(n))
#define ahtonl(n,h)		rev_memcpy_word((n),(uint8_t*)&(h))
#define nahcmpl(n,h)		rev_memcmp_word((n),(uint8_t*)&(h))

#else	/* #if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN */

#error "_NET_CFG_BYTE_ORDER expected."

#endif	/* #if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN */

/*
 *  �v���g�R�������ʂ���t���O�Ɋւ����`
 *
 *    �E���v���
 */

#define PROTO_FLG_PPP_HDLC	ULONG_C(0x00000001)	/* ppp_hdlc.c	*/
#define PROTO_FLG_PPP_FSM	ULONG_C(0x00000002)	/* ppp_fsm.c	*/
#define PROTO_FLG_PPP_AUTH	ULONG_C(0x00000004)	/* ppp_auth.c	*/
#define PROTO_FLG_PPP_LCP	ULONG_C(0x00000008)	/* ppp_lcp.c	*/
#define PROTO_FLG_PPP_IPCP	ULONG_C(0x00000010)	/* ppp_ipcp.c	*/
#define PROTO_FLG_PPP_CCP	ULONG_C(0x00000020)	/* ppp_ccp.c	*/
#define PROTO_FLG_PPP_PAP	ULONG_C(0x00000040)	/* ppp_upap.c	*/
#define PROTO_FLG_PPP_MODEM	ULONG_C(0x00000080)	/* ppp_modem.c	*/
#define PROTO_FLG_PPP		ULONG_C(0x00000100)	/* ppp.c	*/

#define PROTO_FLG_ETHER_NIC	ULONG_C(0x00000001)	/* if_??.c	*/

#define PROTO_FLG_LOOP		ULONG_C(0x00000100)	/* if_loop.c	*/

#define PROTO_FLG_ETHER		ULONG_C(0x00000100)	/* ethernet.c	*/

#define PROTO_FLG_IF		ULONG_C(0x00000800)	/* if.c		*/

#define PROTO_FLG_ARP		ULONG_C(0x00008000)	/* if_ether.c	*/

#define PROTO_FLG_IP4		ULONG_C(0x00010000)	/* ip_*.c	*/
#define PROTO_FLG_ICMP4		ULONG_C(0x00040000)	/* ip_icmp.c	*/

#define PROTO_FLG_IP6		ULONG_C(0x00100000)	/* ip6_*.c	*/
#define PROTO_FLG_ICMP6		ULONG_C(0x00400000)	/* icmp6.c	*/
#define PROTO_FLG_ND6		ULONG_C(0x00800000)	/* nd6_*.c	*/

#define PROTO_FLG_UDP		ULONG_C(0x08000000)	/* udp_*.c	*/

#define PROTO_FLG_TCP		ULONG_C(0x01000000)	/* tcp_*.c	*/

#define PROTO_FLG_NET_BUF	ULONG_C(0x10000000)	/* net_buf.c	*/
#define PROTO_FLG_NET		ULONG_C(0x80000000)	/* route.c, net*.c	*/

/*
 *  �A�h���X�`���̒�`
 */

#define AT_ETHER		UINT_C(0x01)		/* �C�[�T�l�b�g		*/
#define AT_INET4		UINT_C(0x10)		/* IPv4 �A�h���X	*/
#define AT_INET6		UINT_C(0x20)		/* IPv6 �A�h���X	*/

#if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY)

/*
 *  TINET �Ǝ��֐�
 */

extern char *mac2str (char *buf, uint8_t *macaddr);

#endif /* #if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY) */

#endif	/* of #ifndef _NET_H_ */
