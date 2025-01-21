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
 *  @(#) $Id: nd6_rtr.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/nd6_rtr.c,v 1.11 2002/04/19 04:46:23 suz Exp $	*/
/*	$KAME: nd6_rtr.c,v 1.111 2001/04/27 01:37:15 jinmei Exp $	*/

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

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet6/in6_ifattach.h>
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#include <netinet6/ip6_var.h>

#include <net/if6_var.h>

/*
 *  �O���֐��̒�`
 */

extern const char *itron_strerror (ER ercd);

#ifdef SUPPORT_INET6

#if NUM_ND6_DEF_RTR_ENTRY > 0

/*
 *  �S��ϐ�
 */

SYSTIM	nd6_base_reachable_time		= ND6_DEF_REACHABLE_TIME;	/* ���[�^����ʒm���ꂽ�l		*/
SYSTIM	nd6_reachable_time		= ND6_DEF_REACHABLE_TIME;	/* ���[�^����ʒm���ꂽ�l�̕␳�l	*/
SYSTIM	nd6_recalc_reachtm_interval	= ND6_RECALC_REACHTM_INTERVAL;	/* ���B�\��Ԃ̗L�����ԍČv�Z�Ԋu	*/
SYSTIM	nd6_retrans_time		= ND6_DEF_RETRANS_TIME;		/* �ߗגT���̑��M�Ԋu			*/
uint8_t	ip6_defhlim			= IPV6_DEFHLIM;			/* �z�b�v���~�b�g�̋K��l		*/

/*
 *  �Ǐ��ϐ�
 */

/*
 *  �v���t�B�b�N�X�E���X�g
 */

static T_ND6_PREFIX nd6_prefix[NUM_ND6_PREFIX_ENTRY];

/*
 *  �f�B�t�H���g���[�^�E���X�g
 */

static T_DEF_ROUTER	nd6_def_router[NUM_ND6_DEF_RTR_ENTRY];
static uint_t		def_router_count = 0;				/* ���X�g�ɂ��郋�[�^�� */

/*
 *  make_mask -- �}�b�v�p�̃}�X�N�𐶐�����B
 */

static uint_t
make_mask (int_t index)
{
	uint_t	mask;
	int_t	ix;

	/* �}�X�N�𐶐�����B*/
	mask = 1;
	for (ix = index; ix -- > 0; )
		mask <<= 1;

	return mask;
	}

/*
 *  find_pfxlist_reachable_router --
 *      �w�肵���v���t�B�b�N�X��ʒm�������[�^�������N��ɑ��݂��邩�`�F�b�N����B
 */

static T_DEF_ROUTER *
find_pfxlist_reachable_router (T_ND6_PREFIX *pr)
{
	T_DEF_ROUTER	*dr = NULL;
	T_LLINFO_ND6	*ln;
	uint_t		mask;
	int_t		ix;

	mask = 1;
	for (ix = 0; ix < def_router_count; ix ++) {
		if ((pr->routermap & mask) != 0) {
			if ((ln = nd6_lookup(&nd6_def_router[ix].addr, false)) != NULL &&
			    ND6_IS_LLINFO_PROBREACH(ln))
				return dr;
			}
		mask <<= 1;
		}
	return NULL;
	}

/*
 *  pfxlist_onlink_check -- �v���t�B�b�N�X�E���X�g�̃I�������N��Ԃ��`�F�b�N����B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

static void
pfxlist_onlink_check (void)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_ND6_PREFIX	*pr = NULL;
	T_IN6_IFADDR	*ia;
	ER		error;
	int_t		ix;

	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) != 0 &&
		    find_pfxlist_reachable_router(pr))
			break;
		}

	if (ix >= 0) {
		/*
		 *  �I�������N��Ԃ̃v���t�B�b�N�X���Œ����݂���Ƃ��̏����B
		 *  �e�v���t�B�b�N�X�̃I�������N��Ԃ��A������ʒm���Ă������[�^��
		 *  ��Ԃɏ]���Đݒ肷��B
		 */

		
		for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
			pr = &nd6_prefix[ix];

			if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0)
				continue;

			if ((pr->flags & ND6_PREFIX_STATE_DETACHED) == 0 &&
			    find_pfxlist_reachable_router(pr) == NULL)
				pr->flags |= ND6_PREFIX_STATE_DETACHED;

			if ((pr->flags & ND6_PREFIX_STATE_DETACHED) != 0 &&
			    find_pfxlist_reachable_router(pr) != NULL)
				pr->flags &= ~ND6_PREFIX_STATE_DETACHED;
			}
		}
	else {
		/*
		 *  �ǂ̃v���t�B�b�N�X���I�������N�ł͂Ȃ��A
		 *  �f�B�t�H���g���[�^�����݂��Ȃ��Ƃ��̏����B
		 *  ���ׂẴv���t�B�b�N�X���g�p�\��Ԃɐݒ肷��B
		 */

		
		for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
			pr = &nd6_prefix[ix];

			if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0)
				continue;

			if ((pr->flags & ND6_PREFIX_STATE_DETACHED) != 0)
				pr->flags &= ~ND6_PREFIX_STATE_DETACHED;
			}
		}

	/*
	 *  �e�v���t�B�b�N�X���ɁA�ʒm���Ă������[�^�̏�Ԃ�
	 *  �I�������N�̏�Ԃ���v���Ȃ���΁A�I�������N��Ԃ��X�V����B
	 */
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];

		if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0)
			continue;

		if ((pr->flags & ND6_PREFIX_STATE_DETACHED) != 0 &&
		    (pr->flags & ND6_PREFIX_STATE_ONLINK  ) != 0) {
			if ((error = nd6_prefix_offlink(pr)) != E_OK)
				syslog(LOG_ERROR, "[ND6 RTR] prefix offlink failed: %s", itron_strerror(error));
			}

		if ((pr->flags & ND6_PREFIX_STATE_DETACHED) == 0 &&
		    (pr->flags & ND6_PREFIX_STATE_ONLINK  ) == 0 &&
		    (pr->flags & ND6_PREFIX_FLAG_ONLINK   ) == 0) {
			if ((error = nd6_prefix_onlink(pr)) != E_OK)
				syslog(LOG_ERROR, "[ND6 RTR] prefix onlink failed: %s", itron_strerror(error));
			}
		}

	/*
	 *  �����N��Ƀv���t�B�b�N�X��ʒm���Ă��郋�[�^��
	 *  ���Ȃ��Ƃ� 1 �䑶�݂��邩�m�F����B
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
		ia = &ifp->in_ifaddrs[ix];
		if ((ia->flags & (IN6_IFF_DEFINED | IN6_IFF_AUTOCONF)) != 0 &&
		     ia->prefix_index != ND6_PREFIX_IX_INVALID) {
			pr = &nd6_prefix[ia->prefix_index];
			if (find_pfxlist_reachable_router(pr) != NULL)
				break;
			}
		}

	if (ix >= 0) {
		/*
		 *  �����N��Ƀv���t�B�b�N�X��ʒm���Ă��郋�[�^��
		 *  ���Ȃ��Ƃ� 1 �䑶�݂��鎞�̏����B
		 */
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if ((ia->flags & (IN6_IFF_DEFINED | IN6_IFF_AUTOCONF)) != 0 &&
			     ia->prefix_index != ND6_PREFIX_IX_INVALID) {
				pr = &nd6_prefix[ia->prefix_index];
				if (find_pfxlist_reachable_router(pr) != NULL)
					ia->flags &= ~IN6_IFF_DETACHED;
				else
					ia->flags |= IN6_IFF_DETACHED;
				}
			}
		}
	else {
		/*
		 *  �����N��Ƀv���t�B�b�N�X��ʒm���Ă��郋�[�^��
		 *  1 �䑶�݂��Ȃ����͑S�ẴA�h���X�𗘗p�ł���悤�ɂ���B
		 */
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if ((ia->flags & (IN6_IFF_DEFINED | IN6_IFF_AUTOCONF)) != 0)
				ia->flags &= ~IN6_IFF_DETACHED;
			}
		}
	}

/*
 *  pfxrtr_add -- �v���t�B�b�N�X�G���g���ƃf�B�t�H���g���[�^�E�G���g���������N����B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

static void
pfxrtr_add (int_t prefix_index, int_t rtr_index)
{
	/*  �v���t�B�b�N�X�G���g���ƃf�B�t�H���g���[�^�E�G���g���������N����B*/
	nd6_prefix[prefix_index].routermap |= make_mask(rtr_index);
	nd6_def_router[rtr_index].plistmap |= make_mask(prefix_index);

	pfxlist_onlink_check();
	}

/*
 *  nd6_pfxrtr_lookup -- �v���t�B�b�N�X�G���g�����烋�[�^��T������B
 */

static uint_t
pfxrtr_lookup (const T_ND6_PREFIX *pr, int_t rtr_index)
{
	return (pr->routermap & make_mask(rtr_index)) == 0 ? IN6_RTR_IX_UNREACH : rtr_index;
	}

/*
 *  defrouter_select -- �D��f�B�t�H���g�E���[�^��I�����Ȃ����B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

static void
defrouter_select (void)
{
	T_DEF_ROUTER	*dr = NULL, router;
	T_LLINFO_ND6	*ln;
	int_t		ix, tix;

	for (ix = 0; ix < def_router_count; ix ++) {
		dr = &nd6_def_router[ix];
		if ((ln = nd6_lookup(&dr->addr, false)) != NULL && ND6_IS_LLINFO_PROBREACH(ln)) {
		
			/* �I���������[�^��擪�Ɉڂ��B*/
			router = *dr;
			for (tix = ix; tix > 0; tix --)
				nd6_def_router[tix] = nd6_def_router[tix - 1];
			nd6_def_router[0] = router;
			break;
			}
		}
	}

/*
 *  defrtrlist_update -- �f�B�t�H���g���[�^�E���X�g���X�V����B
 *
 *  	�߂�l�́A���[�^�̃C���f�b�N�X�B
 *      �������A�l�� -1 �Ȃ�A�v���t�B�b�N�X�E���X�g�͍X�V���Ȃ��B
 */

static int_t
defrtrlist_update (T_IN6_ADDR *src, uint32_t lifetime, uint8_t flags)
{
	T_DEF_ROUTER	*dr, *fdr = NULL;
	SYSTIM		now;
	int_t		ix;

	syscall(get_tim(&now));
	syscall(wai_sem(SEM_ND6_DEFRTRLIST));

	/* �o�^�ς����ׂ�B*/
	if ((fdr = nd6_defrtrlist_lookup(src)) != NULL) {
		/* �o�^�ς݂̏ꍇ�̏��� */
		if (lifetime == 0) {
			nd6_defrtrlist_del(fdr);
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return -1;
			}
		else {
			fdr->lifetime = lifetime * SYSTIM_HZ;		/* lifetime �̒P�ʂ͕b */
			fdr->flags    = flags;
			fdr->expire   = now + fdr->lifetime;
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return fdr - nd6_def_router;
			}
		}
	else if (lifetime == 0) {
		syscall(sig_sem(SEM_ND6_DEFRTRLIST));
		return -1;
		}

	if (fdr == NULL && def_router_count < NUM_ND6_DEF_RTR_ENTRY) {
		/*
		 *  def_router_count < NUM_ND6_DEF_RTR_ENTRY �ł���΁A
		 *  nd6_def_router[def_router_count]; ���󂫃G���g��
		 */
		fdr = &nd6_def_router[def_router_count];
		}

	/* �󂫃G���g�����Ȃ���΁A�L�����Ԃ��Z���G���g�����폜����B*/
	if (fdr == NULL) {
		T_DEF_ROUTER	*sdr = NULL;
		int32_t		diff, sdiff = 0xffffffff;

		for (ix = def_router_count; ix -- > 0; ) {
			dr = &nd6_def_router[ix];
			diff = (int32_t)(dr->expire - now);
			if (diff <= 0) {	/* dr->expire <= now */
				/* ���ɁA�L�����Ԃ��߂��Ă���B*/
				sdr = dr;
				break;
				}
			else if (diff < sdiff)
				sdr = dr;
			}
		if (sdr != NULL) {
			fdr = sdr;
			nd6_defrtrlist_del(fdr);
			}
		}

	/* �e�����o�ɒl��ݒ肷��B*/
	fdr->plistmap = 0;
	fdr->addr     = *src;
	fdr->lifetime = lifetime * SYSTIM_HZ;		/* lifetime �̒P�ʂ͕b */
	fdr->flags    = flags;
	fdr->expire   = now + fdr->lifetime;
	fdr->state    = ND6_DEF_RTR_BUSY;
	def_router_count ++;

	/*
	 *  �f�B�t�H���g���[�^�Ƃ��ēo�^���邪�A
	 *  ���Ƀf�B�t�H���g���[�^������ΑI�����Ȃ����Ȃ��B
	 */
	if (fdr - nd6_def_router != 0)
		defrouter_select();

	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	return fdr - nd6_def_router;
	}

/*
 *  in6_ifadd -- �C���^�t�F�[�X�ɃA�h���X��ǉ�����B
 */

static ER
in6_ifadd (T_ND6_PREFIX *pr, T_IN6_IFADDR *ia, int_t router_index)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_ADDR	mask, addr;
	T_IN6_IFADDR	*lla;
	int_t		ix;

	lla = &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL];

	/*
	 *  �����N���[�J���A�h���X�����o�^�ł���Ή������Ȃ��B
	 */
	if ((lla->flags & IN6_IFF_DEFINED) == 0)
		return E_OBJ;

	/*
	 *  ���[�^����ʒm���ꂽ�v���t�B�b�N�X�����A
	 *  �����N���[�J���A�h���X�̃v���t�B�b�N�X����
	 *  �قȂ��Ă���΃G���[
	 */
	if (lla->prefix_len != pr->prefix_len)
		return E_PAR;

	/* �v���t�B�b�N�X�}�X�N�𐶐�����B*/
	in6_plen2pmask(&mask, pr->prefix_len);

	/* �A�h���X�𐶐�����B*/
	for (ix = 0; ix < 4; ix ++)
		addr.s6_addr32[ix] = (pr->prefix.s6_addr32[ix] &  mask.s6_addr32[ix])
		                   | ( lla->addr.s6_addr32[ix] & ~mask.s6_addr32[ix]);

	/* �t���O������������B*/
	ia->flags = 0;

	return in6_update_ifa(ifp, ia, &addr,
	                      pr->prefix_len, pr->vltime, pr->pltime,
	                      router_index, pr - nd6_prefix, IN6_IFF_AUTOCONF);
	}

/*
 *  nd6_prefix_lookup -- �v���t�B�b�N�X��T������B
 */

static T_ND6_PREFIX *
nd6_prefix_lookup (const T_IN6_ADDR *prefix, uint_t plen)
{
	T_ND6_PREFIX	*pr;
	int_t		ix;

	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY) &&
		     pr->prefix_len == plen && IN6_ARE_ADDR_EQUAL(&pr->prefix, prefix))
			return pr;
		}

	return NULL;
	}

/*
 *  prelist_remove -- �v���t�B�b�N�X���X�g����v���t�B�b�N�X���폜����B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

static void
prelist_remove (T_ND6_PREFIX *pr)
{
	ER	error = E_OK;
	uint_t	mask;
	int_t	rix;

	/* �L�����Ԑ؂�ɂ���B*/
	pr->vltime = 0;
	pr->pltime = 0;

	if ((pr->flags & ND6_PREFIX_STATE_ONLINK) != 0 &&
	    (error = nd6_prefix_offlink(pr)) != E_OK) {
		syslog(LOG_ERROR, "[ND6 RTR] prefix remove failed: %s", itron_strerror(error));
		return;
		}

	/*  �v���t�B�b�N�X�G���g���ƃf�B�t�H���g���[�^�E�G���g���̃����N����������B*/
	pr->routermap = 0;
	mask = make_mask(pr - nd6_prefix);
	for (rix = def_router_count; rix --; )
		nd6_def_router[rix].plistmap &= ~mask;

	/* �v���t�B�b�N�X�𖳌��ɂ���B*/
	pr->flags &= ~ND6_PREFIX_STATE_BUSY;

	pfxlist_onlink_check();
	}

/*
 *  nd6_prefix_onlink -- �v���t�B�b�N�X���I�������N�ɐݒ肵�A�A�h���X���g�p�\�ɂ���B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

ER
nd6_prefix_onlink (T_ND6_PREFIX *pr)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*lla, *ia = NULL;
	int_t		ix;

	/* ���ɃI�������N��ԂɂȂ��Ă���ꍇ�̓G���[�B*/
	if ((pr->flags & ND6_PREFIX_STATE_ONLINK) != 0)
		return E_OBJ;

	/* �����N���[�J���A�h���X�����o�^�ł���Ή������Ȃ��B*/
	lla = &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL];
	if ((lla->flags & IN6_IFF_DEFINED) == 0)
		return E_OK;

	/*
	 *  �w�肳�ꂽ�v���t�B�b�N�X�����蓖�Ă��Ă���C���^�t�F�[�X��
	 *  �A�h���X����T���B
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
		ia = &ifp->in_ifaddrs[ix];
		if (ia->prefix_index == (pr - nd6_prefix))
			break;
		}

	if (ix >= 0) {

		/* �A�h���X�����g�p�\�ɂ���B*/
		ia->flags &= ~IN6_IFF_DETACHED;

		/* �v���t�B�b�N�X���I�������N�ɐݒ肷��B*/
		pr->flags |= ND6_PREFIX_STATE_ONLINK;
		}

	return E_OK;
	}

/*
 *  nd6_prefix_offlink -- �v���t�B�b�N�X���I�t�����N�ɐݒ肵�A�A�h���X���g�p�s�ɂ���B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

ER
nd6_prefix_offlink (T_ND6_PREFIX *pr)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*ia = NULL;
	int_t		ix;

	/* ���ɃI�t�����N��ԂɂȂ��Ă���ꍇ�̓G���[�B*/
	if ((pr->flags & ND6_PREFIX_STATE_ONLINK) == 0)
		return E_OBJ;

	/*
	 *  �w�肳�ꂽ�v���t�B�b�N�X�����蓖�Ă��Ă���C���^�t�F�[�X��
	 *  �A�h���X����T���B
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
		ia = &ifp->in_ifaddrs[ix];
		if (ia->prefix_index == (pr - nd6_prefix))
			break;
		}

	if (ix >= 0) {

		/* �A�h���X�����g�p�s�ɂ���B*/
		ia->flags |= IN6_IFF_DETACHED;

		/* �v���t�B�b�N�X���I�t�����N�ɐݒ肷��B*/
		pr->flags &= ~ND6_PREFIX_STATE_ONLINK;
		}

	return E_OK;
	}

/*
 *  in6_init_prefix_ltimes -- �v���t�B�b�N�X�̗L�����Ԃ�ݒ肷��B
 */

static ER
in6_init_prefix_ltimes (T_ND6_PREFIX *pr)
{
	SYSTIM		now;

	/* �����L�����Ԃ��L�����Ԃ�蒷���Ƃ��̓G���[ */
	if (pr->pltime > pr->vltime)
		return E_PAR;

	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

	if (pr->pltime == ND6_INFINITE_LIFETIME)
		pr->preferred = 0;
	else
		pr->preferred = pr->pltime + now;

	if (pr->vltime == ND6_INFINITE_LIFETIME)
		pr->expire = 0;
	else
		pr->expire = pr->vltime + now;

	return E_OK;
	}

/*
 *  nd6_prelist_add -- �v���t�B�b�N�X���X�g�Ƀv���t�B�b�N�X��ǉ�����B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

static T_ND6_PREFIX *
nd6_prelist_add (T_ND_OPT_PREFIX_INFO *pi, int_t rtr_index)
{
	T_ND6_PREFIX	*pr = NULL;
	int_t		ix;
	ER		error;

	/* �v���t�B�b�N�X���X�g����󂫂̃v���t�B�b�N�X�G���g����T������B*/
	for (ix = NUM_ND6_PREFIX_ENTRY; ix --; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY) == 0)
			break;
		}

	/* �v���t�B�b�N�X���X�g�ɋ󂫂��Ȃ���΃G���[ */
	if (ix < 0)
		return NULL;

	pr->flags |= ND6_PREFIX_STATE_BUSY;

	/* �v���t�B�b�N�X��ǉ�����B*/
	pr->prefix     = pi->prefix;
	pr->prefix_len = pi->prefix_len;

	/* �t���O��ݒ肷��B*/
	if ((pi->flags & ND_OPT_PI_FLAG_ONLINK) != 0)
		pr->flags |= ND6_PREFIX_FLAG_ONLINK;
	if ((pi->flags & ND_OPT_PI_FLAG_AUTO) != 0)
		pr->flags |= ND6_PREFIX_FLAG_AUTO;

	/* �v���t�B�b�N�X�̗L�����Ԃ�ݒ肷��B*/
	pr->vltime = ntohl(pi->valid);
	pr->pltime = ntohl(pi->preferred);
	in6_init_prefix_ltimes(pr);

	if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) != 0) {
		if ((error = nd6_prefix_onlink(pr)) != E_OK)
			return NULL;
		}

	/* ���[�^�}�b�v������������B*/
	pr->routermap = 0;

	/* ���[�^��ǉ�����B*/
	pfxrtr_add(pr - nd6_prefix, rtr_index);

	return pr;
	}

/*
 *  prelist_update -- �v���t�B�b�N�X�E���X�g���X�V����B
 */

static void
prelist_update (T_ND_OPT_PREFIX_INFO *pi, uint_t router_index)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_ND6_PREFIX	*pr;
	T_IN6_IFADDR	*ia = NULL;
	int_t		ix, ifidlen;

	syscall(wai_sem(SEM_ND6_DEFRTRLIST));
	if ((pr = nd6_prefix_lookup(&pi->prefix, pi->prefix_len)) != NULL) {
		/*
		 *  �o�^�ς݂̏ꍇ�́A�v���t�B�b�N�X���X�g���X�V����B
		 */

		/*
		 *  �t���O�̍X�V�̒���:
		 *    on-link �r�b�g�� autonomous �r�b�g��
		 *    1 ���� 0 �ɕύX���Ă͂Ȃ�Ȃ��B
		 */

		if ((pi->flags & ND_OPT_PI_FLAG_ONLINK) != 0)
			pr->flags |= ND6_PREFIX_FLAG_ONLINK;
		if ((pi->flags & ND_OPT_PI_FLAG_AUTO) != 0)
			pr->flags |= ND6_PREFIX_FLAG_AUTO;

		if ((pi->flags & ND_OPT_PI_FLAG_ONLINK) != 0) {
			/*
			 *  �ʒm���ꂽ�v���t�B�b�N�X���I�������N�̎��́A
			 *  �L�����Ԃ��X�V����B
			 */
			pr->vltime = ntohl(pi->valid);
			pr->pltime = ntohl(pi->preferred);
			in6_init_prefix_ltimes(pr);
			}

		if ((pi->flags & ND_OPT_PI_FLAG_ONLINK  ) != 0 &&
		    (pr->flags & ND6_PREFIX_STATE_ONLINK) == 0) {
			/*
			 *  �I�t�����N�̃v���t�B�b�N�X���I�������N�ɂȂ������̏��������s����B
			 */
			if (nd6_prefix_onlink(pr) != E_OK) {
				syscall(sig_sem(SEM_ND6_DEFRTRLIST));
				syslog(LOG_ERROR, "[ND6 RTR] prefix update failed.");
				return;
				}
			}

		if (router_index != IN6_RTR_IX_UNREACH && pfxrtr_lookup(pr, router_index) == IN6_RTR_IX_UNREACH)
			pfxrtr_add(pr - nd6_prefix, router_index);
		}
	else {	/* ���o�^�̏ꍇ */

		/* �L������ 0 �̃v���t�B�b�N�X�͒ǉ����Ȃ��B*/
		if (pi->valid == 0) {
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return;
			}

		/* �I�t�����N�ŃA�h���X�����ݒ�Ɏg�p���Ȃ���Βǉ����Ȃ��B*/
		if ((pi->flags & (ND_OPT_PI_FLAG_ONLINK | ND_OPT_PI_FLAG_AUTO)) !=
		                 (ND_OPT_PI_FLAG_ONLINK | ND_OPT_PI_FLAG_AUTO)) {
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return;
			}

		/* �v���t�B�b�N�X��ǉ�����B*/
		if ((pr = nd6_prelist_add(pi, router_index)) == NULL) {
			syslog(LOG_ERROR, "[ND6 RTR] prefix add failed.");
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			return;
			}

		if ((pr->flags & ND6_PREFIX_FLAG_ONLINK) == 0) {
			/*
			 *  �I�t�����N�E�v���t�B�b�N�X�̏ꍇ�́A�L�����Ԃ� 0 �ɐݒ肷��B
			 *  ���ƂŗL�������؂�ƂȂ�A���X�g����폜�����B
			 */
			pr->vltime = 0;
			pr->pltime = 0;
			in6_init_prefix_ltimes(pr);
			}
		}

	/*
	 *  �X�e�[�g���X�E�A�h���X�����ݒ���s���B
	 */
	if ((pr->flags & ND6_PREFIX_FLAG_AUTO) == 0) {
		syscall(sig_sem(SEM_ND6_DEFRTRLIST));
		return;
		}

	/*
	 *  �ʒm���ꂽ�v���t�B�b�N�X�����蓖�Ă��Ă���C���^�t�F�[�X��
	 *  �A�h���X����T���B
	 */
	for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
		ia = &ifp->in_ifaddrs[ix];
		if ((ia->flags & IN6_IFF_DEFINED) != 0 &&
		    ia->prefix_len == pr->prefix_len &&
		    in6_are_prefix_equal(&ia->addr, &pr->prefix, pr->prefix_len))
			break;
		}

	if (ix >= 0) {	/* �o�^�ς݂̂Ƃ� */
		if ((ia->flags & IN6_IFF_AUTOCONF) == 0) {
			/*
			 *  �X�e�[�g���X�E�A�h���X�����ݒ�ɂ��
			 *  �ݒ肳��Ă��Ȃ���΍X�V���Ȃ��B
			 */
			;
			}
		else if (ia->flags & IN6_IFF_TENTATIVE) {
			/*
			 *  �d�����o���Ȃ�X�V���Ȃ��B
			 */
			;
			}
		else {
			T_IN6_ADDR	mask, addr;
			T_IN6_IFADDR	*lla;
			uint32_t		vltime;
			SYSTIM		now;
			int_t		ix;

			/* �L�����Ԃ�ݒ肷��B*/
			syscall(get_tim(&now));

			if (ia->lifetime.vltime == ND6_INFINITE_LIFETIME)
				vltime = ND6_INFINITE_LIFETIME;
			else if (IFA6_IS_INVALID(ia, now))
				vltime = 0;
			else
				vltime = ia->lifetime.expire - now / SYSTIM_HZ;

			if (pr->vltime > (2 * 60 * 60) || pr->vltime > vltime) {
				/*
				 *  lifetime.expire�Api->valid (�L������) ��
				 *  pi->preferred (�����L������) �̒P�ʂ� [s]�B
				 *  �ʒm���ꂽ�L�����Ԃ� 2 ���Ԉȏォ�A���݂̎c�莞�Ԃ��
				 *  ������΁A�V�����L�����Ԃɂ́A�ʒm���ꂽ�L�����Ԃ�ݒ肷��B
				 */
				vltime = pr->vltime;
				}
			else if (vltime <= (2 * 60 * 60))
				;
			else {
				/*
				 *  IPsec �͖������̂��߁A2 ���Ԃ�ݒ肷��B
				 */
				vltime = 2 * 60 * 60;
				}

			lla = &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL];

			/* �v���t�B�b�N�X�}�X�N�𐶐�����B*/
			in6_plen2pmask(&mask, pr->prefix_len);

			/* �A�h���X�𐶐�����B*/
			for (ix = 0; ix < 4; ix ++)
				addr.s6_addr32[ix] = (pr->prefix.s6_addr32[ix] &  mask.s6_addr32[ix])
				                   | ( lla->addr.s6_addr32[ix] & ~mask.s6_addr32[ix]);

			in6_update_ifa(ifp, ia, &addr, pr->prefix_len, vltime,
			               pr->pltime, router_index, pr - nd6_prefix,
			               IN6_IFF_AUTOCONF | IN6_IFF_NODAD);
			}
		}

	else { /* ���o�^�̂Ƃ� */

		/*
		 *  �v���t�B�b�N�X�����`�F�b�N����B
		 *  �����A�v���t�B�b�N�X���ƃC���^�t�F�[�X ID �̍��v��
		 *  128 �r�b�g�Ɉ�v���Ȃ����́A�v���t�B�b�N�X���𖳎�����B
		 */
		if ((ifidlen = in6_if2idlen(ifp)) < 0)
			syslog(LOG_ERROR, "[ND6 RTR] IFID undefined.");
		else if (ifidlen + pr->prefix_len != 128)
			syslog(LOG_NOTICE, "[ND6 RTR] invalid prefix len: %d.", pr->prefix_len);
		else {

			for (ix = NUM_IN6_IFADDR_ENTRY; ix --; ) {
				ia = &ifp->in_ifaddrs[ix];
				if ((ia->flags & IN6_IFF_DEFINED) == 0) {
					in6_ifadd(pr, ia, router_index);
					pfxlist_onlink_check();
					break;
					}
				}

			if (ix < 0)
				syslog(LOG_ERROR, "[ND6 RTR] prefix update failed.");
			}
		}
	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	}

/*
 *  nd6_prelist_timer -- �v���t�B�b�N�X�E���X�g�̊Ǘ��^�C�}�[
 */

void
nd6_prelist_timer (void)
{
	T_ND6_PREFIX	*pr;
	SYSTIM		now;
	int_t		ix;

	syscall(get_tim(&now));
	now /= SYSTIM_HZ;		/* �L�����Ԃ̒P�ʂ� [s] */

	syscall(wai_sem(SEM_ND6_DEFRTRLIST));
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY) != 0 && (int32_t)(pr->expire - now) <= 0)
		                                                       /* pr->expire <= now */
			prelist_remove(pr);
		}
	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	}

/*
 *  nd6_rs_output -- ���[�^�v�����o�͂���B
 */

static void
nd6_rs_output (void)
{
	T_ROUTER_SOLICIT_HDR	*rsh;
	T_NET_BUF		*output;
	T_IN6_IFADDR		*ifa;
	T_IN6_ADDR		*saddr;
	uint16_t		len;

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_RS_OUT_PACKETS], 1);

	/*
	 *  ���M���A�h���X�ɂ́A�����N���[�J���A�h���X��ݒ肷�邪�A
	 *  �܂��ݒ肳�ꂢ�Ȃ���΁A���w���ݒ肷��B
	 */
	if ((ifa = in6ifa_ifpwithix(IF_GET_IFNET(), IPV6_IFADDR_IX_LINKLOCAL)) != NULL && !IFA6_IS_NOTREADY(ifa))
		saddr = &ifa->addr;
	else
		saddr = &in6_addr_unspecified;

	len = (ROUTER_SOLICIT_HDR_SIZE + 7) >> 3 << 3;

	/* �l�b�g���[�N�o�b�t�@���l�����AIPv6 �w�b�_��ݒ肷��B*/
	if (in6_get_datagram(&output, len, 0, &in6_addr_linklocal_allrouters,
	                     saddr, IPPROTO_ICMPV6,
	                     IPV6_MAXHLIM, NBA_SEARCH_ASCENT, TMO_ND6_RS_OUTPUT) != E_OK)
		return;

 	/* ���[�^�v���w�b�_��ݒ肷��B*/
 	rsh = GET_ROUTER_SOLICIT_HDR(output, IF_IP6_ROUTER_SOLICIT_HDR_OFFSET);
 	rsh->hdr.type       = ND_ROUTER_SOLICIT;
 	rsh->hdr.code       = 0;
 	rsh->nd_rs_reserved = 0;

	/* �`�F�b�N�T�����v�Z����B*/
	rsh->hdr.sum = 0;
	rsh->hdr.sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)rsh - output->buf, len);

	/* ���M����B*/
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutRouterSolicits, 1);
	ip6_output(output, IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_MAXHLIM), TMO_ND6_RS_OUTPUT);
	}

/*
 *  nd6_defrtrlist_lookup -- �f�B�t�H���g���[�^�E���X�g��T������B
 */

T_DEF_ROUTER *
nd6_defrtrlist_lookup (T_IN6_ADDR *src)
{
	T_DEF_ROUTER	*dr = NULL;
	int_t		ix;

	for (ix = def_router_count; ix -- > 0; ) {
		dr = &nd6_def_router[ix];
		if (IN6_ARE_ADDR_EQUAL(&dr->addr, src)) {
			return dr;
			}
		}
	return NULL;
	}

/*
 *  nd6_router_lookup -- ���[�^�̃A�h���X��Ԃ��B
 *
 */

T_IN6_ADDR *
nd6_router_lookup (void)
{
	if (def_router_count > 0)
		return &nd6_def_router[0].addr;
	else
		return NULL;
	}

/*
 *  nd6_defrtrlist_del -- �f�B�t�H���g���[�^�E���X�g���烋�[�^���폜����B
 *
 *    ����: ���̊֐����Ăяo���Ƃ��́ASEM_ND6_DEFRTRLIST �ŁA
 *          ���b�N���Ă���Ăяo�����ƁB
 */

void
nd6_defrtrlist_del (T_DEF_ROUTER *dr)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*ia;
	T_ND6_PREFIX	*pr;
	uint_t		mask;
	int_t		ix, rix, pix, rtrix = dr - nd6_def_router;

	if ((ia = in6ifa_ifpwithrtrix(ifp, rtrix)) != NULL) {
		/*
		 *  �l�b�g���[�N�C���^�t�F�[�X�̃v���t�B�b�N�X��ʒm����
		 *  ���[�^�𓞒B�s�\�ɂ���B
		 */
		ia->router_index = IN6_RTR_IX_UNREACH;
		}

	/* �v���t�B�b�N�X���X�g���烋�[�^���폜����B*/
	mask = make_mask(rtrix);
	for (pix = NUM_ND6_PREFIX_ENTRY; pix --; )
		nd6_prefix[pix].routermap &= ~mask;

	/* �폜�������[�^�ȍ~��O�ɋl�߂�B*/
	for (rix = rtrix + 1; rix < def_router_count; rix ++)
		nd6_def_router[rix - 1] = nd6_def_router[rix];

	/* �v���t�B�b�N�X���X�g�̃��[�^���X�V����B*/
	if (dr != nd6_def_router) {

		/* �}�X�N�𐶐�����B*/
		mask = 1;
		for (ix = rtrix - 1; ix -- > 0; )
			mask = (mask << 1) | 1;

		for (pix = NUM_ND6_PREFIX_ENTRY; pix --; ) {
			pr = &nd6_prefix[pix];
			pr->routermap = (pr->routermap & mask) | (((pr->routermap & ~mask) >> 1) & ~mask);
			}
		}
	def_router_count --;

	/* �v���t�B�b�N�X�̃I�������N��Ԃ��m�F����B*/
	pfxlist_onlink_check();

	/*
	 *  �폜���郋�[�^���D��f�B�t�H���g���[�^�̏ꍇ�́A
	 *  �D��f�B�t�H���g���[�^��I�����Ȃ����B
	 */
	if (rtrix == 0)
		defrouter_select();
	}

/*
 *  nd6_defrtrlist_timer -- �f�B�t�H���g���[�^�E���X�g�̊Ǘ��^�C�}�[
 */

void
nd6_defrtrlist_timer (void)
{
	T_DEF_ROUTER	*dr;
	SYSTIM		now;
	int_t		ix;

	syscall(get_tim(&now));

	syscall(wai_sem(SEM_ND6_DEFRTRLIST));
	for (ix = def_router_count; ix -- > 0; ) {
		dr = &nd6_def_router[ix];
		if ((int32_t)(dr->expire - now) <= 0) {
		           /* dr->expire <= now */
			nd6_defrtrlist_del(dr);
			}
		}
	syscall(sig_sem(SEM_ND6_DEFRTRLIST));
	}

/*
 *  nd6_get_drl -- �f�B�t�H���g���[�^�E���X�g���l������B
 */

const T_DEF_ROUTER *
nd6_get_drl (uint_t *count)
{
	*count = def_router_count;
	return nd6_def_router;
	}

/*
 *  nd6_get_prl -- �v���t�B�b�N�X�E���X�g���l������B
 */

const T_ND6_PREFIX *
nd6_get_prl (void)
{
	return nd6_prefix;
	}

#endif	/* of #if NUM_ND6_DEF_RTR_ENTRY > 0 */

/*
 *  nd6_ra_input -- ���[�^�ʒm�̓��͏����B
 */

void
nd6_ra_input (T_NET_BUF *input, uint_t off)
{
#if NUM_ND6_DEF_RTR_ENTRY > 0

	T_IFNET			*ifp = IF_GET_IFNET();
	T_IP6_HDR		*ip6h;
	T_ROUTER_ADVERT_HDR	*rah;
	T_ND_OPT_HDR		*opth;
	SYSTIM			now;
	int_t			rix;
	uint_t			lladdr_len = 0;
	uint32_t		advrea;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_RA_IN_PACKETS], 1);

	ip6h = GET_IP6_HDR(input);

	/*
	 *  �w�b�_�̃`�F�b�N�A�ȉ��̏ꍇ�͔j������B
	 *    �E�z�b�v���~�b�g�� IPV6_MAXHLIM (255) �ȊO
	 *    �E�w�b�_�����Z��
	 *    �E�n�_�A�h���X���A�����N���[�J���ł͂Ȃ� (RFC2461)
	 */
	if (ip6h->hlim != IPV6_MAXHLIM                ||
	    input->len - off < ROUTER_ADVERT_HDR_SIZE ||
	    !IN6_IS_ADDR_LINKLOCAL(&ip6h->src))
		goto err_ret;

	rah  = GET_ROUTER_ADVERT_HDR(input, off);

	/* �ߗגT���I�v�V�����̃I�t�Z�b�g���L�^����B*/
	if (nd6_options(nd_opt_off, input->buf + (off + ROUTER_ADVERT_HDR_SIZE),
	                            input->len - (off + ROUTER_ADVERT_HDR_SIZE)) != E_OK)
		goto err_ret;
	/*
	 *  ���B�\��Ԃ̗L�����Ԃ̍X�V

	 */
	if (rah->reachable) {
		advrea = ntohl(rah->reachable) * SYSTIM_HZ / 1000;	/* rah->reachable �̒P�ʂ� ms */
		if (advrea <= ND6_MAX_REACHABLE_TIME &&
		    advrea != nd6_base_reachable_time) {
			syscall(get_tim(&now));
			nd6_recalc_reachtm_interval
				= now + ND6_RECALC_REACHTM_INTERVAL;
			nd6_base_reachable_time	= advrea;
			nd6_reachable_time
				= ND6_CALC_REACH_TIME(nd6_base_reachable_time);
			}
		}

	/* �ߗגT���̑��M�Ԋu�̍X�V */
	if (rah->retransmit) {
		nd6_retrans_time = ntohl(rah->retransmit) * SYSTIM_HZ / 1000;
									/* rah->retransmit �̒P�ʂ� ms */
		}

	/* �z�b�v���~�b�g�̋K��l�̍X�V */
	if (rah->nd_ra_current_hoplimit) {
		ip6_defhlim = rah->nd_ra_current_hoplimit;
		}

	/* �f�B�t�H���g���[�^���X�g�̍X�V */
	rix = defrtrlist_update(&ip6h->src,
	                       ntohs(rah->nd_ra_router_lifetime),
	                       rah->nd_ra_flags);		/* rah->nd_ra_router_lifetime �̒P�ʂ͕b */

	/* �v���t�B�b�N�X���X�g�̍X�V */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFO_COUNT)]) {
		T_ND_OPT_PREFIX_INFO	*pi;
		uint_t			pi_off, pi_count;

		pi_count = nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFO_COUNT)];
		pi_off   = off + ROUTER_ADVERT_HDR_SIZE
		               + nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFORMATION)] - 8;
	 	/* ����: �I�v�V�����I�t�Z�b�g�z��ɂ́A�I�t�Z�b�g + 8 ���ݒ肳��Ă���B*/
		while (pi_count -- > 0) {
			pi = (T_ND_OPT_PREFIX_INFO*)(input->buf + pi_off);
			if (pi->type != ND_OPT_PREFIX_INFORMATION)
				/* �I�v�V�����^�C�v���v���t�B�b�N�X���łȂ���Ή������Ȃ��B*/
				;
			else if (pi->len != 4)
			    	/* �v���t�B�b�N�X���̒����� 32 (8�~4) �łȂ���Εs�� */
				syslog(LOG_NOTICE, "[ND6 RTR] prefix opt len: %d.", pi->len);
			else if (pi->prefix_len > 128)
				/* �v���t�B�b�N�X���� 128 �r�b�g�ȉ� */
				syslog(LOG_NOTICE, "[ND6 RTR] prefix len: %d.", pi->prefix_len);
			else if (IN6_IS_ADDR_MULTICAST(&pi->prefix) ||
			         IN6_IS_ADDR_LINKLOCAL(&pi->prefix))
				/* �}���`�L���X�g�ƃ����N���[�J���͕s�� */
				syslog(LOG_NOTICE, "[ND6 RTR] invalid addr: %s from %s.",
				                   ipv62str(NULL, &pi->prefix), ipv62str(NULL, &ip6h->src));
#if 0	/* FreeBSD 6.3 �ō폜����Ă���B*/
			else if (IN6_IS_ADDR_AGGREGATE_UNICAST(&pi->prefix) &&		
			         (pi->prefix_len != 64)                       )
				/* �W��\���j�L���X�g�ŁA�v���t�B�b�N�X���� 64 �r�b�g�ȊO�͕s�� */
				syslog(LOG_NOTICE, "[ND6 RTR] invalid prefix len for global: %d.", pi->prefix_len);
#endif
			else if (ntohl(pi->preferred) > ntohl(pi->valid))
				/* �����L�����Ԃ��L�����Ԃ�蒷����Εs�� */
				syslog(LOG_NOTICE, "[ND6 RTR] preferred(%d) > valid time(%d).", ntohl(pi->preferred), ntohl(pi->valid));
			else {
				syslog(LOG_NOTICE, "[ND6 RTR] update prefix: %s from %s.",
				                   ipv62str(NULL, &pi->prefix), ipv62str(NULL, &ip6h->src));
				if (rix >= 0) {
					/*
					 *  defrtrlist_update �̖߂�l�́A���[�^�̃C���f�b�N�X�B
					 *  �������A�l�� -1 �Ȃ�A�v���t�B�b�N�X�E���X�g�͍X�V���Ȃ��B
					 */
					prelist_update(pi, rix);	/* �v���t�B�b�N�X�E���X�g���X�V����B*/
					}
				}
			pi_off += pi->len << 3;		/* �I�v�V�������̒P�ʂ� 8 �o�C�g */
			}
		}

	/* MTU �̍X�V */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_MTU)]) {
		T_ND_OPT_MTU_HDR	*optmtuh;
		uint32_t			mtu;

		optmtuh = (T_ND_OPT_MTU_HDR *)((uint8_t *)(input->buf + off + ROUTER_ADVERT_HDR_SIZE) +
		                               nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_MTU)] - 8);

		/*
		 *  �l�̃`�F�b�N
		 *
		 *    �I�v�V������: 1
		 *    �\��:         0
		 */
		if (optmtuh->len != 1 || optmtuh->reserved != 0)
			goto err_ret;

		/* MTU �� IPv6 MMTU�i1280 �I�N�e�b�g�j�ȉ��Ȃ疳������B*/
		mtu = ntohl(optmtuh->mtu);
		if (mtu >= IPV6_MMTU) {
			if (mtu <= (linkmtu > IF_MTU ? linkmtu : IF_MTU))
				linkmtu = mtu;
			}
		}

	/*
	 *  ���[�^�̎n�_�����N�A�h���X���ߗ׃L���b�V���ɓo�^����B
	 */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + ROUTER_ADVERT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)] - 8);
	 	/* ����: �I�v�V�����I�t�Z�b�g�z��ɂ́A�I�t�Z�b�g + 8 ���ݒ肳��Ă���B*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	/*
	 *  �l�b�g���[�N�C���^�t�F�[�X�̃A�h���X������v���Ȃ���΃G���[
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/* �ߗ׃L���b�V���ɓo�^����B*/
	nd6_cache_lladdr(ifp, &ip6h->src, (T_IF_ADDR *)lladdr, ND_ROUTER_ADVERT, 0);

	/*
	 *  ���[�^�̎n�_�����N�A�h���X���ߗ׃L���b�V���ɓo�^�����̂ŁA
	 *  �I�������N��Ԃ��ω�����\�������邽�߁A������`�F�b�N����B
	 */
	pfxlist_onlink_check();

	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));

#else	/* of #if NUM_ND6_DEF_RTR_ENTRY > 0 */

	/*
	 *  ���[�^�ʒm����M���Ȃ��ꍇ�́A�j�����ďI������B
	 */
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_RA_IN_PACKETS], 1);
	syscall(rel_net_buf(input));

#endif	/* of #if NUM_ND6_DEF_RTR_ENTRY > 0 */
	}

#if NUM_ND6_RTR_SOL_RETRY > 0

/*
 *  nd6_rtrsol_ctl -- ���[�^�v���o�͂̐���
 */

void
nd6_rtrsol_ctl (void)
{
	T_IN6_IFADDR	*ifa;
	int_t		try;

	/* �����N���[�J���A�h���X�̃A�h���X���𓾂�B*/
	if ((ifa = in6ifa_ifpwithix(IF_GET_IFNET(), IPV6_IFADDR_IX_LINKLOCAL)) == NULL)
		return;

	/* �����N���[�J���A�h���X�̏d�����o�I����҂B*/
	do {
		/* �����N���[�J���A�h���X�̏d�����o�I���҂����Ԃ�ݒ肷��B*/
		syscall(dly_tsk(net_rand() % TMO_ND6_RTR_SOL_DELAY));

		/* �҂��Ă���Ԃɏd�������o���ꂽ��I������B*/
		if (ifa->flags & IN6_IFF_DUPLICATED)
			return;

		} while (!((ifa->flags & IN6_IFF_DEFINED) && (ifa->flags & IN6_IFF_TENTATIVE) == 0));

	for (try = 0; try < NUM_ND6_RTR_SOL_RETRY; try ++) {

		/* �f�B�t�H���g���[�^�E���X�g�ɃG���g��������ΏI�� */
		if (def_router_count > 0)
			return;

		/* ���[�^�v�����o�͂���B*/
		nd6_rs_output();

		/* �o�͂� 2 ��ڈȍ~�̒x�����Ԃ�ݒ肷��B*/
		syscall(dly_tsk(TMO_ND6_RTR_SOL_INTERVAL));
		}
	}

#endif	/* of #if NUM_ND6_RTR_SOL_RETRY > 0 */

/*
 *  nd6_onlink_prefix_lookup -- �v���t�B�b�N�X��T������B
 */

T_ND6_PREFIX *
nd6_onlink_prefix_lookup (T_IN6_ADDR *dst)
{
	SYSTIM		now;
	T_ND6_PREFIX	*pr;
	int_t		ix;

	syscall(get_tim(&now));
	now /= SYSTIM_HZ;

	/* �����L�����ԓ��̃v���t�B�b�N�X��T������B*/
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY)  &&
		    (pr->flags & ND6_PREFIX_FLAG_ONLINK) &&
		    in6_are_prefix_equal(dst, &pr->prefix, pr->prefix_len) &&
		    (int32_t)(pr->preferred - now) > 0) {
		           /* pr->preferred > now */
			return pr;
			}
		}

	/* �L�����ԓ��̃v���t�B�b�N�X��T������B*/
	for (ix = NUM_ND6_PREFIX_ENTRY; ix -- > 0; ) {
		pr = &nd6_prefix[ix];
		if ((pr->flags & ND6_PREFIX_STATE_BUSY)  &&
		    (pr->flags & ND6_PREFIX_FLAG_ONLINK) &&
		    in6_are_prefix_equal(dst, &pr->prefix, pr->prefix_len) &&
		    (int32_t)(pr->expire - now) > 0) {
		           /* pr->expire > now */
			return pr;
			}
		}

	return NULL;
	}

#endif /* of #ifdef SUPPORT_INET6 */
