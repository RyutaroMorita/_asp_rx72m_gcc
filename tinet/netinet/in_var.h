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
 *  @(#) $Id: in_var.h,v 1.5 2009/12/24 05:47:21 abe Exp $
 */

/*
 * Copyright (c) 1985, 1986, 1993
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
 *	@(#)in_var.h	8.2 (Berkeley) 1/9/95
 * $FreeBSD: src/sys/netinet/in_var.h,v 1.29.2.1 1999/08/29 16:29:38 peter Exp $
 */
 
#ifndef _IN_VAR_H_
#define _IN_VAR_H_

#if defined(SUPPORT_INET6)

#include <netinet6/in6_var.h>

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  �Ǝ��̃G���[�R�[�h
 */

#define EV_NOPND		(-97)		/* �y���f�B���O���Ă��Ȃ� */

/*
 *  �l�b�g���[�N�G���[�R�[�h
 */

#define EV_MSIZE		(-98)		/* �f�[�^�O����������	*/
#define EV_NURCH		(-99)		/* �l�b�g���[�N���B�s�\	*/
#define EV_HDOWN		(-100)		/* �z�X�g�_�E��		*/
#define EV_HURCH		(-101)		/* �z�X�g���B�s�\	*/
#define EV_CNNRF		(-102)		/* �ڑ��s�\		*/
#define EV_CNRST		(-103)		/* �ڑ����Z�b�g		*/
#define EV_REXMTMO		(-104)		/* �đ��^�C���A�E�g	*/

/*
 *  ���ʃ^�C�}�̋N�������̒�`
 */

#define IN_TIMER_TMO		(SYSTIM_HZ/NET_TIMER_CYCLE)

/*
 *  �C���^�t�F�[�X�A�h���X�\����
 */

typedef struct t_in4_ifaddr {
	T_IN4_ADDR		addr;		/* IPv4 �A�h���X	*/
	T_IN4_ADDR		mask;		/* �T�u�l�b�g�}�X�N	*/
	} T_IN4_IFADDR;

/*
 *  ���[�e�B���O�\�G���g���\����
 */

typedef struct t_in4_rtentry {
	T_IN4_ADDR	target;		/* �ڕW�l�b�g���[�N�A�h���X			*/
	T_IN4_ADDR	mask;		/* �ڕW�l�b�g���[�N�A�h���X�̃T�u�l�b�g�}�X�N	*/
	T_IN4_ADDR	gateway;	/* �Q�[�g�E�F�C�� IP �A�h���X			*/
	uint32_t	expire;		/* �L�����Ԃ��؂�鎞�� [s]			*/
	uint8_t		flags;		/* �t���O					*/
	} T_IN4_RTENTRY;

/*
 *  TINET 1.1 �Ƃ̌݊����̂��߂̒�`
 */

#ifdef NUM_ROUTE_ENTRY

#define NUM_STATIC_ROUTE_ENTRY		NUM_ROUTE_ENTRY
#define NUM_REDIRECT_ROUTE_ENTRY	0
#define T_RT_ENTRY			T_IN_RTENTRY

#else	/* of #ifdef NUM_ROUTE_ENTRY */

#define NUM_ROUTE_ENTRY			\
	(NUM_STATIC_ROUTE_ENTRY + NUM_REDIRECT_ROUTE_ENTRY)
					/* ���[�e�B���O�\�̃G���g����	*/

#endif	/* of #ifdef NUM_ROUTE_ENTRY */

/*
 *  ���[�e�B���O�G���g����ԃt���O
 */

#define IN_RTF_DEFINED		UINT_C(0x01)	/* ��`�ς�			*/
#define IN_RTF_REDIRECT		UINT_C(0x10)	/* ���������ɂ�莩���ݒ肳�ꂽ	*/

/*
 *  IPv4 �� IPv6 ���R���p�C�����ɑI�����邽�߂̃}�N��
 */

#if defined(SUPPORT_INET4)

#define IN_SET_HEADER(nbuf,len,dst,src,proto,ttl)	\
					in4_set_header(nbuf,len,dst,src,proto,ttl)
#define IN_GET_DATAGRAM(nbuf,len,maxlen, dst,src,proto,ttl,nbatr,tmout)	\
					in4_get_datagram(nbuf,len,maxlen, dst,src,proto,ttl,nbatr,tmout)
#define IN_CKSUM(nbuf,proto,off,len)	in4_cksum(nbuf,proto,off,len)
#define IN_IS_DSTADDR_ACCEPT(myaddr,dstaddr)			\
					in4_is_dstaddr_accept(myaddr,dstaddr)
#define IN_IFAWITHIFP(ifp,dst)		in4_ifawithifp(ifp,dst)
#define T_IN_IFADDR			T_IN4_IFADDR
#define T_IN_RTENTRY			T_IN4_RTENTRY

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  ���[�e�B���O�\
 */

extern T_IN_RTENTRY routing_tbl[];

/*
 *  �O���Q��
 */

#ifndef T_NET_BUF_DEFINED
typedef struct t_net_buf T_NET_BUF;
#define T_NET_BUF_DEFINED
#endif

#ifndef T_IFNET_DEFINED
typedef struct t_ifnet T_IFNET;
#define T_IFNET_DEFINED
#endif

/*
 *  �֐�
 */

extern void ip_input (T_NET_BUF *data);
extern ER in4_set_header (T_NET_BUF *nbuf, uint_t len,
                          T_IN4_ADDR *dstaddr, T_IN4_ADDR *srcaddr, uint8_t proto, uint8_t ttl);
extern ER in4_get_datagram (T_NET_BUF **nbuf, uint_t len, uint_t maxlen,
                            T_IN4_ADDR *dstaddr, T_IN4_ADDR *srcaddr,
                            uint8_t proto, uint8_t ttl, ATR nbatr, TMO tmout);
extern uint16_t in4_cksum (T_NET_BUF *nbuf, uint8_t proto, uint_t off, uint_t len);
extern T_IN4_ADDR in4_rtalloc (T_IN4_ADDR dst);
extern void in4_rtredirect (T_IN4_ADDR gateway, T_IN4_ADDR target, uint8_t flags, uint32_t tmo);
extern void in4_init (void);
extern T_IN4_IFADDR *in4_ifawithifp (T_IFNET *ifp, T_IN4_ADDR *dst);
extern T_IN_RTENTRY *in_rtnewentry (uint8_t flags, uint32_t tmo);
extern void in_rttimer (void);
extern void in_rtinit (void);
extern const T_NET_BUF**ip_get_frag_queue (void);

/*
 *  in4_is_dstaddr_accept -- ����A�h���X�Ƃ��Đ��������`�F�b�N����B
 *
 *    ����: dstaddr �́A
 *          TINET-1.2 ����l�b�g���[�N�o�C�g�I�[�_�A
 *          TINET-1.1 �܂ł́A�z�X�g�o�C�g�I�[�_
 */
extern bool_t in4_is_dstaddr_accept (T_IN4_ADDR *myaddr, T_IN4_ADDR *dstaddr);

/*
 *  in_cksum -- �`�F�b�N�T���v�Z�֐��AIPv4�AICMPv4 �p
 *
 *  ����: data �� 4 �I�N�e�b�g�P�ʂŃp�f�B���O���邱�ƁB
 *        data �� 2 �I�N�e�b�g�P�ʂɃA���C������Ă��Ȃ���
 *        ��O����������\��������B
 *        len  �� 4 �I�N�e�b�g�P�ʂɃA���C������Ă��邱�ƁB
 */
extern uint16_t in_cksum(void *data, uint_t len /*�I�N�e�b�g�P��*/);

/*
 *  in_cksum_sum -- �`�F�b�N�T���̍��v�v�Z�֐�
 *
 *  ����: data �� 4 �I�N�e�b�g�P�ʂŃp�f�B���O���邱�ƁB
 *        data �� 2 �I�N�e�b�g�P�ʂɃA���C������Ă��Ȃ���
 *        ��O����������\��������B
 *        len  �� 4 �I�N�e�b�g�P�ʂɃA���C������Ă��邱�ƁB
 */
extern uint32_t in_cksum_sum (void *data, uint_t len /*�I�N�e�b�g�P��*/);

/*
 *  in_cksum_carry -- �`�F�b�N�T���̌��グ�v�Z�֐�
 *
 *  ����: data �� 4 �I�N�e�b�g�P�ʂŃp�f�B���O���邱�ƁB
 *        data �� 2 �I�N�e�b�g�P�ʂɃA���C������Ă��Ȃ���
 *        ��O����������\��������B
 *        len  �� 4 �I�N�e�b�g�P�ʂɃA���C������Ă��邱�ƁB
 */
extern uint32_t in_cksum_carry (uint32_t sum);

#endif	/* of #ifndef _IN_VAR_H_ */
