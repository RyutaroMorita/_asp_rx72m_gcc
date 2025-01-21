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
 *  @(#) $Id: in.h,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1990, 1993
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
 *	@(#)in.h	8.3 (Berkeley) 1/3/94
 * $FreeBSD: src/sys/netinet/in.h,v 1.38.2.3 1999/08/29 16:29:34 peter Exp $
 */
 
#ifndef _IN_H_
#define _IN_H_

#include <tinet_kernel_defs.h>

#include <netinet6/in6.h>

/*
 *  TINET �̃o�[�W�������
 */

#define TINET_PRVER		UINT_C(0x1053)	/* TINET �̃o�[�W�����ԍ� */

/*
 *  �C���^�[�l�b�g�V�X�e���̒�`�ARFC790 �Q��
 */

/*
 *  �v���g�R�� (RFC1700)
 */

#define IPPROTO_IP		UINT_C(0)	/* IP �̃_�~�[				*/
#define IPPROTO_HOPOPTS		UINT_C(0)	/* IPv6 ���p�_ (Hop-by-Hop) �I�v�V����	*/
#define IPPROTO_ICMP		UINT_C(1)	/* ICMP					*/
#define IPPROTO_TCP		UINT_C(6)	/* TCP					*/
#define IPPROTO_UDP		UINT_C(17)	/* UDP					*/
#define IPPROTO_IPV6		UINT_C(41)	/* IPv6					*/
#define IPPROTO_ROUTING		UINT_C(43)	/* �o�H����I�v�V����			*/
#define IPPROTO_FRAGMENT	UINT_C(44)	/* �f�Љ��I�v�V����			*/
#define IPPROTO_RSVP		UINT_C(46)	/* RSVP					*/
#define IPPROTO_ESP		UINT_C(50)	/* IPv6 �Í����I�v�V����		*/
#define IPPROTO_AH		UINT_C(51)	/* IPv6 �F�؃I�v�V����			*/
#define IPPROTO_ICMPV6		UINT_C(58)	/* ICMPv6				*/
#define IPPROTO_NONE		UINT_C(59)	/* IPv6 ���w�b�_����			*/
#define IPPROTO_DSTOPTS		UINT_C(60)	/* IPv6 �I�_�I�v�V����			*/
#define IPPROTO_IPCOMP		UINT_C(108)	/* �y�C���[�h���k			*/
#define IPPROTO_DONE		UINT_C(257)	/* IPv6 �ŏ�ʃv���g�R�����͏I��	*/

/*
 *  IPv4 �A�h���X
 */

/* �O���Q�� */

#ifndef T_IN4_ADDR_DEFINED

typedef uint32_t T_IN4_ADDR;

#define T_IN4_ADDR_DEFINED

#endif	/* of #ifndef T_IN4_ADDR_DEFINED */

/*
 *  ITRON TCP/IPv4 �A�h���X/�|�[�g�ԍ��̒�`
 */

typedef struct t_ipv4ep {
	uint32_t	ipaddr;		/* IPv4 �A�h���X	*/
	uint16_t	portno;		/* �|�[�g�ԍ�		*/
	} T_IPV4EP;

/*
 *  �A�h���X/�|�[�g�̒���
 */

#define IPV4_ADDR_LEN		4
#define PORT_NUM_LEN		2

/*
 *  �|�[�g�ԍ��̒�`
 */

#define TCP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP �W��	*/
#define UDP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP �W��	*/

#define TCP_PORT_LAST_WELL_KNOWN	UINT_C(1023)	/* Well Known �I���ԍ�	*/
#define TCP_PORT_FIRST_AUTO		UINT_C(1024)	/* �������蓖�ĊJ�n�ԍ�	*/
#define TCP_PORT_LAST_AUTO		UINT_C(4999)	/* �������蓖�ďI���ԍ�	*/

#define UDP_PORT_LAST_WELL_KNOWN	UINT_C(1023)	/* Well Known �I���ԍ�	*/
#define UDP_PORT_FIRST_AUTO		UINT_C(1024)	/* �������蓖�ĊJ�n�ԍ�	*/
#define UDP_PORT_LAST_AUTO		UINT_C(4999)	/* �������蓖�ďI���ԍ�	*/

/*
 *  IP �A�h���X�̒�`
 */

#define IPV4_ADDRANY		ULONG_C(0x00000000)	/* ITRON TCP/IP �W��	*/

#define IPV4_ADDR_LOOPBACK	ULONG_C(0x7f000001)
#define IPV4_ADDR_LOOPBACK_MASK	IPV4_CLASS_A_MASK
#define IPV4_ADDR_BROADCAST	ULONG_C(0xffffffff)

#define IPV4_CLASS_A(i)		(((i) & ULONG_C(0x80000000)) == 0)
#define IPV4_CLASS_A_NET	ULONG_C(0xff000000)
#define IPV4_CLASS_A_MASK	ULONG_C(0xff000000)
#define IPV4_CLASS_A_HOST	ULONG_C(0x00ffffff)

#define IPV4_CLASS_B(i)		(((i) & ULONG_C(0xc0000000)) == ULONG_C(0x80000000))
#define IPV4_CLASS_B_NET	ULONG_C(0xffff0000)
#define IPV4_CLASS_B_MASK	ULONG_C(0xffff0000)
#define IPV4_CLASS_B_HOST	ULONG_C(0x0000ffff)

#define IPV4_CLASS_C(i)		(((i) & ULONG_C(0xe0000000)) == ULONG_C(0xc0000000))
#define IPV4_CLASS_C_NET	ULONG_C(0xffffff00)
#define IPV4_CLASS_C_MASK	ULONG_C(0xffffff00)
#define IPV4_CLASS_C_HOST	ULONG_C(0x000000ff)

#define IPV4_CLASS_D(i)		(((i) & ULONG_C(0xf0000000)) == ULONG_C(0xe0000000))

#define IN4_IS_ADDR_MULTICAST(i)	IPV4_CLASS_D(i)

#define MAKE_IPV4_LOCAL_BROADCAST(i)	(IPV4_CLASS_A(i)?((i)|IPV4_CLASS_A_HOST):\
					 IPV4_CLASS_B(i)?((i)|IPV4_CLASS_B_HOST):\
					 IPV4_CLASS_C(i)?((i)|IPV4_CLASS_C_HOST):\
					 IPV4_ADDR_BROADCAST)

#define MAKE_IPV4_LOCAL_MASK(i)		(IPV4_CLASS_A(i)?IPV4_CLASS_A_MASK:\
					 IPV4_CLASS_B(i)?IPV4_CLASS_B_MASK:\
					 IPV4_CLASS_C(i)?IPV4_CLASS_C_MASK:\
					 IPV4_ADDRANY)

#define MAKE_IPV4_ADDR(a,b,c,d)		((T_IN4_ADDR)(((uint32_t)(a)<<24)|((uint32_t)(b)<<16)|((uint32_t)(c)<<8)|(d)))

/*
 *  ���I�����p TCP �ʐM�[�_
 */

typedef struct t_tcp_ccep {
	/* �W�� */
	ATR		cepatr;		/* �ʐM�[�_����			*/
	void		*sbuf;		/* ���M�p�E�B���h�o�b�t�@	*/
	int_t		sbufsz;		/* ���M�p�E�B���h�o�b�t�@�T�C�Y	*/
	void		*rbuf;		/* ��M�p�E�B���h�o�b�t�@	*/
	int_t		rbufsz;		/* ��M�p�E�B���h�o�b�t�@�T�C�Y	*/
	FP		callback;	/* �R�[���o�b�N			*/
	/* �����ˑ� */
	} T_TCP_CCEP;

/*
 *  ���I�����p TCP ��t��
 */

#if defined(SUPPORT_INET4)

typedef struct t_tcp_crep {
	/* �W�� */
	ATR		repatr;		/* ��t������		*/
	T_IPV4EP	myaddr;		/* �����̃A�h���X	*/
	/* �����ˑ� */
	} T_TCP_CREP;

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  ���I�����p UDP �ʐM�[�_
 */

#if defined(SUPPORT_INET4)

typedef struct t_udp_ccep {
	/* �W�� */
	ATR		cepatr;		/* UDP �ʐM�[�_����		*/
	T_IPV4EP	myaddr;		/* �����̃A�h���X		*/
	FP		callback;	/* �R�[���o�b�N�֐�		*/
	/* �����ˑ� */
	} T_UDP_CCEP;

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  IPv4 �� IPv6 ���R���p�C�����ɑI�����邽�߂̃}�N��
 */

#if defined(SUPPORT_INET4)

#define T_IN_ADDR			T_IN4_ADDR
#define T_IPEP				T_IPV4EP
#define IP_ADDRANY			IPV4_ADDRANY

#define IN_ARE_ADDR_EQUAL(n,h)		(*(n)==*(h))
#define IN_ARE_NET_ADDR_EQUAL(n,h)	(ntohl(*(n))==*(h))
#define IN_COPY_TO_NET(d,s)		(*(d)=htonl(*(s)))
#define IN_COPY_TO_HOST(d,s)		(*(d)=ntohl(*(s)))
#define IN_IS_ADDR_MULTICAST(a)		IN4_IS_ADDR_MULTICAST(*(a))
#define IN_IS_NET_ADDR_MULTICAST(a)	IN4_IS_ADDR_MULTICAST(ntohl(*(a)))
#define IN_IS_ADDR_ANY(a)		(*(a)==IPV4_ADDRANY)

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  TINET �Ǝ� API
 */

extern const char *in_strtfn (FN fncd);

#if defined(SUPPORT_INET4)

extern ER in4_add_ifaddr (T_IN4_ADDR addr, T_IN4_ADDR mask);
extern ER in4_add_route (int_t index, T_IN4_ADDR target,
                                      T_IN4_ADDR mask, T_IN4_ADDR gateway);
extern char *ip2str (char *buf, const T_IN4_ADDR *p_ipaddr);
#ifdef SUPPORT_E1
extern ER in4_arp_request (void);
extern ER in4_set_lladdr (uint8_t *p);
extern const uint8_t *in4_get_lladdr (int_t index);
#endif
extern const T_IN4_ADDR *in4_get_ifaddr (int_t index);

#endif	/* of #if defined(SUPPORT_INET4) */

#endif	/* of #ifndef _IN_H_ */
