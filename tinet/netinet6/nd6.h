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
 *  @(#) $Id: nd6.h,v 1.5 2009/12/24 05:48:16 abe Exp $
 */

/*	$FreeBSD: src/sys/netinet6/nd6.h,v 1.10 2002/04/19 04:46:23 suz Exp $	*/
/*	$KAME: nd6.h,v 1.76 2001/12/18 02:10:31 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
#ifndef _ND6_H_
#define _ND6_H_

#ifdef SUPPORT_INET6

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�\���́iT_IFNET�j�̃t���O
 */

#define ND6_IFF_IFDISABLED	UINT_C(0x01)	/* �C���^�t�F�[�X�𖳌��ɂ���B*/

/*
 *  �ߗ׃L���b�V�� 
 */

typedef struct t_llinfo_nd6 {
	T_IN6_ADDR	addr;
	T_NET_BUF	*hold;
	TMO		tmout;
	SYSTIM		expire;		/* [ms] �L�����Ԃ��؂�鎞��	*/
	T_IF_ADDR	ifaddr;
	uint8_t		state;
	uint8_t		asked;
	uint8_t		flags;
	} T_LLINFO_ND6;

/* �ߗ׃L���b�V���̏�� */

#define ND6_LLINFO_FREE			0	/* ���g�p		*/
#define ND6_LLINFO_NO_STATE		1	/* ��Ԗ���`		*/
#define ND6_LLINFO_INCOMPLETE		2	/* ������		*/
#define ND6_LLINFO_REACHABLE		3	/* ���B�\		*/
#define ND6_LLINFO_STALE		4	/* ���B�\���͖��m�F	*/
#define ND6_LLINFO_DELAY		5	/* ���B�\���̊m�F�ҋ@	*/
#define ND6_LLINFO_PROBE		6	/* ���B�\�����m�F��	*/

#define ND6_IS_LLINFO_PROBREACH(n)	((n)->state > ND6_LLINFO_INCOMPLETE)

/* �ߗ׃L���b�V���̐���r�b�g */

#define ND6_LLIF_ROUTER			UINT_C(0x80)	/* ���[�^		*/
#define ND6_LLIF_ASKED			UINT_C(0x40)	/* �ʒm�ς�		*/
#define ND6_LLIF_STATE_MASK		UINT_C(0x07)	/* ��ԃ}�X�N		*/

/* �ߗגT���L���b�V���A�L�����Ԃ̒�` */

#define ND6_SLOW_TMO			((60*60)/NET_TIMER_HZ)
							/* 1 [����]				*/
							/* �ߗגT���L���b�V���X�V�^�C���A�E�g	*/

#define ND6_MAX_DAD_TRY			15		/* �d���A�h���X���o�̍đ���		*/
#define ND6_MAX_MCAST_QUERY		3		/* �}���`�L���X�g�A�h���X�v���̍đ���	*/
#define ND6_MAX_UCAST_QUERY		3		/* ���j�L���X�g�A�h���X�v���̍đ���	*/

#define ND6_INFINITE_LIFETIME		0xffffffff

#define ND6_GCOLLECTION_TIME		(60*60*24*SYSTIM_HZ)
							/* �S�~�E�������A1 ��			*/
#define	ND6_DELAY_TIME			(5*SYSTIM_HZ)	/* �m�F�ҋ@�x��				*/
#define ND6_FIRST_DAD_DELAY_TIME	(1*SYSTIM_HZ)	/* �ŏ��̏d���A�h���X���o���M�x��	*/
#define ND6_DAD_DELAY_TIME		(5*SYSTIM_HZ/10)
							/* �d���A�h���X���o���M�x��		*/

/* �ߗגT���p�^�C�}�̐ݒ� */

#define ND6_TIMER_TMO			((SYSTIM_HZ/NET_TIMER_CYCLE)/5)	/* 0.2[s] �Ԋu		*/

/*
 *  ���B�\��Ԃ̗L������
 */

#define	ND6_DEF_REACHABLE_TIME		(30*SYSTIM_HZ)	/* ���B�\��Ԃ̗L�����Ԃ̊���l		*/
#define	ND6_MAX_REACHABLE_TIME		(60*60*SYSTIM_HZ)
							/* ���B�\��Ԃ̗L�����Ԃ̊���l		*/
#define	ND6_RECALC_REACHTM_INTERVAL	(60*60*2*SYSTIM_HZ)
							/* ���B�\��Ԃ̗L�����ԍČv�Z�Ԋu	*/

#define	ND6_MIN_REACHTM_RAND_FACTOR	512		/* �ŏ������␳�l�A1,024 * 0.5		*/

#if 1							/* �^�C�}�[�̋N���Ԋu���l�����A�K����Z���ݒ�	*/
#define	ND6_MAX_REACHTM_RAND_FACTOR	1484		/* �ŏ������␳�l�A1,024 * 1.45			*/
#else
#define	ND6_MAX_REACHTM_RAND_FACTOR	1536		/* �ŏ������␳�l�A1,024 * 1.5			*/
#endif

/* ���B�\��Ԃ̗L�����Ԃ̌v�Z�}�N�� */

#define ND6_CALC_REACH_TIME(b)		\
	 ((ND6_MIN_REACHTM_RAND_FACTOR * ((uint32_t)(b) >> 10)) + \
	  (net_rand() & ((ND6_MAX_REACHTM_RAND_FACTOR - ND6_MIN_REACHTM_RAND_FACTOR) * ((uint32_t)(b) >> 10))))

/*
 *  �ߗגT���̑��M�Ԋu
 */

#define ND6_DEF_RETRANS_TIME		(1*SYSTIM_HZ)

/*
 *  ���[�^�ʒm�ɂ��ύX����邱�Ƃ�����l
 */

#if NUM_ND6_DEF_RTR_ENTRY > 0

/* ���[�^�ʒm����M����ꍇ�́A�ʒm���ꂽ�l */

#define	ND6_REACHABLE_TIME		nd6_reachable_time
#define ND6_RETRANS_TIME		nd6_retrans_time

#else	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/* ���[�^�ʒm����M���Ȃ��ꍇ�̒l�͊���l */

#define	ND6_REACHABLE_TIME		ND6_DEF_REACHABLE_TIME
#define ND6_RETRANS_TIME		ND6_DEF_RETRANS_TIME

#endif	/* #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/*
 *  �f�B�t�H���g���[�^�E���X�g
 */

typedef struct t_def_router {
	T_IN6_ADDR	addr;
	SYSTIM		expire;		/* [ms] �L�����Ԃ��؂�鎞��	*/
	uint32_t	lifetime;	/* [ms] �L������			*/
	uint16_t	plistmap;	/* �v���t�B�b�N�X�}�b�v		*/
	uint8_t		flags;		/* ���[�^�ʒm�̃t���O		*/
	uint8_t		state;
	} T_DEF_ROUTER;

/* �f�B�t�H���g���[�^�E���X�g�̏�� */

#define ND6_DEF_RTR_BUSY		0xff	/* �g�p��		*/

/* �v���t�B�b�N�X�̃C���f�b�N�X */

#define ND6_PREFIX_IX_INVALID		0xff

/*
 *  �v���t�B�b�N�X�E���X�g
 */

typedef struct t_nd6_prefix {
	T_IN6_ADDR	prefix;		/* �v���t�B�b�N�X		*/
	uint32_t	expire;		/* [s] �L�����Ԃ��؂�鎞��	*/
	uint32_t	preferred;	/* [s] �����L�����Ԃ��؂�鎞��	*/
	uint32_t	vltime;		/* [s] �L������			*/
	uint32_t	pltime;		/* [s] �����L������		*/
	uint16_t	routermap;	/* ���[�^�}�b�v			*/
	uint8_t		flags;		/* �t���O			*/
	uint8_t		prefix_len;	/* �v���t�B�b�N�X��		*/
	} T_ND6_PREFIX;

/* �t���O */

#define ND6_PREFIX_FLAG_ONLINK		UINT_C(0x80)	/* �I�������N�v���t�B�b�N�X	*/
#define ND6_PREFIX_FLAG_AUTO		UINT_C(0x40)	/* �X�e�[�g���X�E�A�h���X�����ݒ�*/

#define ND6_PREFIX_STATE_BUSY		UINT_C(0x01)	/* �g�p��		*/
#define ND6_PREFIX_STATE_ONLINK		UINT_C(0x02)	/* �I�������N���	*/
#define ND6_PREFIX_STATE_DETACHED	UINT_C(0x04)	/* ��g�p���	*/

/*
 *  �ϐ�
 */

extern SYSTIM	nd6_base_reachable_time;
extern SYSTIM	nd6_reachable_time;
extern SYSTIM	nd6_recalc_reachtm_interval;
extern SYSTIM	nd6_retrans_time;
extern uint8_t	ip6_defhlim;

/*
 *  �֐�
 */

extern void nd6_ifattach (T_IFNET *ifp);
extern void nd6_ns_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
                           T_IN6_ADDR *taddr, T_LLINFO_ND6 *ln, bool_t dad);
extern void nd6_na_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
                           T_IN6_ADDR *taddr, uint32_t flags, bool_t tlladdr);
extern void nd6_dad_start (T_IFNET *ifp, T_IN6_IFADDR *ia, int_t *tick);
extern ER nd6_output (T_IFNET *ifp, T_NET_BUF *output,
                      T_IN6_ADDR *dst, T_LLINFO_ND6 *ln, TMO tmout);
extern void nd6_na_input (T_NET_BUF *input, uint_t off);
extern void nd6_ns_input (T_NET_BUF *input, uint_t off);
extern void nd6_ra_input (T_NET_BUF *input, uint_t off);
extern ER nd6_storelladdr (T_IF_ADDR *out, T_IN6_ADDR *dst, T_IF_ADDR *ifa);
extern ER nd6_options (uint8_t *opt, void *nh, uint_t len);
extern T_LLINFO_ND6 *nd6_lookup (T_IN6_ADDR *addr, bool_t create);
extern ER nd6_output_hold (T_IFNET *ifp, T_LLINFO_ND6 *ln);
extern T_LLINFO_ND6 *nd6_cache_lladdr (T_IFNET *ifp, T_IN6_ADDR *from, 
                                       T_IF_ADDR *lladdr, uint8_t type, uint8_t code);
extern void nd6_defrtrlist_timer (void);
extern void nd6_prelist_timer (void);
extern void nd6_rtrsol_ctl (void);
extern T_IN6_ADDR *nd6_router_lookup (void);
extern T_DEF_ROUTER *nd6_defrtrlist_lookup (T_IN6_ADDR *src);
extern void nd6_defrtrlist_del (T_DEF_ROUTER *dr);
extern void nd6_timer (void);
extern const T_DEF_ROUTER *nd6_get_drl (uint_t *count);
extern const T_ND6_PREFIX *nd6_get_prl (void);
extern const T_LLINFO_ND6 *nd6_get_cache (void);
extern ER nd6_prefix_onlink (T_ND6_PREFIX *pr);
extern ER nd6_prefix_offlink (T_ND6_PREFIX *pr);
extern T_ND6_PREFIX *nd6_onlink_prefix_lookup (T_IN6_ADDR *dst);

#endif	/* of #ifdef SUPPORT_INET6 */

#endif	/* of #ifndef _ND6_H_ */
