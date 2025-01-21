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
 *  @(#) $Id: nd6.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/nd6.c,v 1.20 2002/08/02 20:49:14 rwatson Exp $	*/
/*	$KAME: nd6.c,v 1.144 2001/05/24 07:44:00 itojun Exp $	*/

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

/*
 * XXX
 * KAME 970409 note:
 * BSD/OS version heavily modifies this code, related to llinfo.
 * Since we don't have BSD/OS version of net/route.c in our hand,
 * I left the code mostly as it was in 970310.  -- itojun
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
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
#include <net/if_loop.h>
#include <net/if_ppp.h>
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

#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#include <netinet6/ip6_var.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 *  �ߗ׃L���b�V��
 */

static T_LLINFO_ND6 nd6_cache[NUM_ND6_CACHE_ENTRY];

/*
 *  nd6_free -- ���[�^���폜����B
 */

static void
nd6_free (T_LLINFO_ND6	*ln)
{
	T_DEF_ROUTER	*dr;

	dr = nd6_defrtrlist_lookup(&ln->addr);
	if (dr != NULL) {
		ln->state = ND6_LLINFO_INCOMPLETE;

		/* �v���t�B�b�N�X�E���X�g���烋�[�^���폜����B*/
		nd6_defrtrlist_del(dr);
		}
	}

/*
 *  nd6_timer -- �ߗגT���Ǘ��^�C�}�[
 */

void
nd6_timer (void)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_LLINFO_ND6	*ln;
	SYSTIM		now;
	int_t		ix;

	/* �ߗ׃L���b�V���̏��� */
	syscall(wai_sem(SEM_ND6_CACHE));
	syscall(get_tim(&now));
	for (ix = NUM_ND6_CACHE_ENTRY; ix -- > 0; ) {
		ln = &nd6_cache[ix];
		if (ln->state >= ND6_LLINFO_NO_STATE && (int32_t)(ln->expire - now) < 0) {
		                                               /* ln->expire < now */

			switch (ln->state) {

			case ND6_LLINFO_INCOMPLETE:	/* ������		*/
				if (ln->asked < ND6_MAX_MCAST_QUERY) {
					/*
					 *  �}���`�L���X�g�A�h���X�v���̍đ��񐔈ȉ��̏ꍇ�̏���
					 */
					ln->asked ++;
					ln->expire = now + ND6_RETRANS_TIME;	/* �ߗגT�����M�Ԋu */
					nd6_ns_output(ifp, &in6_addr_unspecified, &ln->addr, ln, false);
					}
				else  {
					if (ln->hold != NULL) {
						/*
						 *  �ŏI�I�ɂ́A�ۗ�����Ă���l�b�g���[�N�o�b�t�@��
						 *  ����΁AICMP6 ERROR ���������g�ɕԂ������ƁA
						 *  �l�b�g���[�N�o�b�t�@���J������B
						 *  �������A���݁Aicmp6_error �̎������s���S�̂��߁A
						 *  �l�b�g���[�N�o�b�t�@�̊J���̂ݍs���B
						 */
#if 0	/* �ۗ� */
						icmp6_error(ln->hold, ICMP6_DST_UNREACH,
						                      ICMP6_DST_UNREACH_ADDR, 0);
#endif	/* #if 0 */
						syscall(rel_net_buf(ln->hold));
						ln->hold = NULL;
						}
					nd6_free(ln);
					memset((void*)ln, 0, sizeof(*ln));
					}
				break;

			case ND6_LLINFO_REACHABLE:	/* ���B�\		*/
				if (ln->expire) {
					ln->expire = now + ND6_GCOLLECTION_TIME;
					ln->state = ND6_LLINFO_STALE;
					}
				break;

			case ND6_LLINFO_STALE:		/* ���B�\���͖��m�F	*/
				if (ln->expire) {
					if (ln->hold != NULL) {
						syscall(rel_net_buf(ln->hold));
						ln->hold = NULL;
						}
					nd6_free(ln);
					memset((void*)ln, 0, sizeof(*ln));
					}
				break;

			case ND6_LLINFO_DELAY:		/* ���B�\���̊m�F�ҋ@	*/
				ln->asked = 1;
				ln->expire = now + ND6_RETRANS_TIME;		/* �ߗגT�����M�Ԋu */
				ln->state = ND6_LLINFO_PROBE;
				nd6_ns_output(ifp, &ln->addr, &ln->addr, ln, false);
				break;

			case ND6_LLINFO_PROBE:		/* ���B�\�����m�F��	*/
				if (ln->asked < ND6_MAX_UCAST_QUERY) {
					/*
					 *  ���j�L���X�g�A�h���X�v���̍đ��񐔈ȉ��̏ꍇ�̏���
					 */
					ln->asked ++;
					ln->expire += ND6_RETRANS_TIME;	/* �ߗגT�����M�Ԋu */
					nd6_ns_output(ifp, &ln->addr, &ln->addr, ln, false);
					}
				else {
					if (ln->hold != NULL) {
						syscall(rel_net_buf(ln->hold));
						ln->hold = NULL;
						}
					nd6_free(ln);
					memset((void*)ln, 0, sizeof(*ln));
					}
				break;

				}
			}
		}
	syscall(sig_sem(SEM_ND6_CACHE));

	/* �f�B�t�H���g���[�^�E���X�g�̏��� */
	nd6_defrtrlist_timer();

	/* �v���t�B�b�N�X�E���X�g�̏��� */
	nd6_prelist_timer();

	/* �l�b�g���[�N�C���^�t�F�[�X�̃A�h���X�̏��� */
	in6_ifaddr_timer(ifp);

	/*
	 *  ���B�\��Ԃ̗L�����Ԃ̍X�V
	 */
	if ((int32_t)(nd6_recalc_reachtm_interval - now) < 0) {
	           /* nd6_recalc_reachtm_interval < now */
		nd6_recalc_reachtm_interval	= now + ND6_RECALC_REACHTM_INTERVAL;
		nd6_reachable_time		= ND6_CALC_REACH_TIME(nd6_base_reachable_time);
		}
	timeout((callout_func)nd6_timer, NULL, ND6_TIMER_TMO);
	}

/*
 *  nd6_get_cache -- �ߗ׃L���b�V�����l������B
 */

const T_LLINFO_ND6 *
nd6_get_cache (void)
{
	return nd6_cache;
	}

/*
 *  nd6_ifattach -- �ߗגT���̏����ݒ���s���B
 */

void
nd6_ifattach (T_IFNET *ifp)
{
	}

/*
 *  nd6_output_hold -- �ߗגT���L���b�V���ɕۗ�����Ă���
 *                     �A�h���X�����҂��̃f�[�^�O����������Α��M����B
 *
 *    ����: �Z�}�t�H SEM_ND6_CACHE �ɂ�胍�b�N��ԂŌďo�����ƁB
 */

ER
nd6_output_hold (T_IFNET *ifp, T_LLINFO_ND6 *ln)
{
	SYSTIM now;

	/* �A�h���X�����҂��̃f�[�^�O����������Α��M����B*/
	if (ln->hold) {

		/* �^�C���A�E�g�̏��� */
		if (ln->tmout != TMO_FEVR) {

			/*
			 *  �^�C���A�E�g�̎w�肪�i�v�łȂ��A���Ԃ��߂��Ă���΁A
			 *  �o�͂��Ȃ��ŏI������B
			 */
			syscall(get_tim(&now));
			if ((int32_t)(ln->tmout - now) < 0) {
			           /* ln->tmout < now */
				syscall(rel_net_buf(ln->hold));
				ln->hold = NULL;
				return E_TMOUT;
				}
			}
				
		nd6_output(ifp, ln->hold, &ln->addr, ln, TMO_FEVR);
		ln->hold = NULL;
		}
	return E_OK;
	}

/*
 *  nd6_lookup -- �ߗגT���L���b�V����T������B
 *
 *    ����: �Z�}�t�H SEM_ND6_CACHE �ɂ�胍�b�N��ԂŌďo�����ƁB
 *
 */

T_LLINFO_ND6 *
nd6_lookup (T_IN6_ADDR *addr, bool_t create)
{
	SYSTIM	min = 0xffffffff;
	int_t	ix, fix = -1, mix = -1;

	for (ix = NUM_ND6_CACHE_ENTRY; ix -- > 0; ) {
		if (nd6_cache[ix].state == 0) {
			/* ���g�p�G���g���̃C���f�b�N�X���L�^����B*/
			if (fix == -1)
				fix = ix;
			}
		else if (IN6_ARE_ADDR_EQUAL(addr, &nd6_cache[ix].addr)) {
			return &nd6_cache[ix];
			}
		else if ((int32_t)(nd6_cache[ix].expire - min) < 0) {	/* nd6_cache[ix].expire < min */
			/* �L���������ŒZ�G���g���̃C���f�b�N�X���L�^����B*/
			min = nd6_cache[ix].expire;
			mix = ix;
			}
		}

	if (create) {
		if (fix == -1)  {
			if (nd6_cache[mix].hold != NULL) {
				syscall(rel_net_buf(nd6_cache[mix].hold));
				}
			fix = mix;
			}
		syscall(get_tim(&nd6_cache[fix].expire));
		nd6_cache[fix].addr   = *addr;
		nd6_cache[fix].state  = ND6_LLINFO_NO_STATE;
		return &nd6_cache[fix];
		}
	else
		return NULL;
	}

/*
 *  nd6_cache_lladdr -- �ߗגT���L���b�V���ɓo�^����B
 */

T_LLINFO_ND6 *
nd6_cache_lladdr (T_IFNET *ifp, T_IN6_ADDR *from,
                  T_IF_ADDR *lladdr, uint8_t type, uint8_t code)
{
	T_LLINFO_ND6	*ln;
	SYSTIM		now;
	bool_t		newentry, olladdr, llchange, doupdate;
	int_t		newstate = ND6_LLINFO_INCOMPLETE;

	/* �A�h���X�����w��Ȃ牽�����Ȃ��B*/
	if (IN6_IS_ADDR_UNSPECIFIED(from))
		return NULL;

	/* �ߗ׃L���b�V���ɓo�^����B*/
	syscall(wai_sem(SEM_ND6_CACHE));
	if ((ln = nd6_lookup(from, false)) == NULL) {
		ln = nd6_lookup(from, true);
		newentry = true;
		}
	else
		newentry = false;

	olladdr = ln->state > ND6_LLINFO_INCOMPLETE;
	if (!olladdr || lladdr == NULL)
		llchange = false;
	else if (memcmp(lladdr, &ln->ifaddr, sizeof(T_IF_ADDR)))
		llchange = true;
	else
		llchange = false;

	/*
	 *  ��ԑJ�ڕ\
	 *
	 *  nd_na_flags
	 *  newnetry olladdr lladdr llchange ���� (L: lladdr ��o�^����)
	 *
	 *      F       F       N       -    (1)
	 *      F       T       N       -    (2)
	 *      F       F       Y       -    (3) L * -> STALE
	 *      F       T       Y       F    (4) L
	 *      F       T       Y       T    (5) L * -> STALE
	 *      T       -       N       -    (6)   * -> NO_STATE
	 *      T       -       Y       -    (7) L * -> STALE
	 */

	/* �f�[�^�����N�w�̃A�h���X���ʒm����Ă���΍X�V����B*/
	if (lladdr != NULL) {
		ln->ifaddr = *(T_IF_ADDR *)lladdr;
		}

	if (newentry) {
		if (lladdr != NULL)					/* (7) */
			newstate = ND6_LLINFO_STALE;
		else							/* (6) */
			newstate = ND6_LLINFO_NO_STATE;
		doupdate = true;
		}
	else {
		if ((!olladdr && lladdr != NULL) ||			/* (3) */
		    ( olladdr && lladdr != NULL && llchange)) {		/* (5) */
			newstate = ND6_LLINFO_STALE;
			doupdate = true;
			}
		else							/* (1),(2),(4) */
			doupdate = false;
		}

	/* �ߗ׃L���b�V���G���g�����X�V����B*/
	if (doupdate) {
		ln->state = newstate;

		syscall(get_tim(&now));
		if (ln->state == ND6_LLINFO_STALE) {
			ln->expire = now + ND6_GCOLLECTION_TIME;

			/* �A�h���X�����҂��̃f�[�^�O����������Α��M����B*/
			nd6_output_hold(ifp, ln);
			}
		else if (ln->state == ND6_LLINFO_INCOMPLETE)
			ln->expire = now;
		}
	syscall(sig_sem(SEM_ND6_CACHE));


	/* ���[�^�ʒm�̏��� */
	switch (type) {

	case ND_NEIGHBOR_SOLICIT:
		if (newentry)
			ln->flags &= ~ND6_LLIF_ROUTER;
		break;

	case ND_REDIRECT:
		if (code == ND_REDIRECT_ROUTER)
			ln->flags |=  ND6_LLIF_ROUTER;
		else if (newentry)
			ln->flags &= ~ND6_LLIF_ROUTER;
		break;

	case ND_ROUTER_SOLICIT:
		ln->flags &= ~ND6_LLIF_ROUTER;
		break;

	case ND_ROUTER_ADVERT:
		if ((!newentry && (olladdr || lladdr != NULL)) ||
		    ( newentry && lladdr))
			ln->flags |=  ND6_LLIF_ROUTER;
		break;
		}

	return ln;
	}

/*
 *  nd6_is_addr_neighbor -- �w�肳�ꂽ�A�h���X�̃m�[�h�����ꃊ���N�ɂ��邩�`�F�b�N����B
 */

bool_t
nd6_is_addr_neighbor (T_IFNET *ifp, T_IN6_ADDR *addr)
{
	if (IN6_IS_ADDR_LINKLOCAL(addr))
		return true;

	if (nd6_onlink_prefix_lookup(addr) != NULL)
		return true;

	if (nd6_lookup(addr, false) != NULL)
		return true;

	return false;
	}

/*
 *  nd6_output -- �ߗגT���̏o�͊֐�
 *
 *    ����: �Z�}�t�H SEM_ND6_CACHE �ɂ�胍�b�N��ԂŌďo�����ƁB
 */

ER
nd6_output (T_IFNET *ifp, T_NET_BUF *output, T_IN6_ADDR *dst, T_LLINFO_ND6 *ln, TMO tmout)
{
	ER	error = E_OK;
	SYSTIM	now;

	/*
	 *  ���Đ�A�h���X���}���`�L���X�g���A�ߗ׃L���b�V����
	 *  �s�v�̏ꍇ�͒����ɑ��M����B
	 */
	if (!(IN6_IS_ADDR_MULTICAST(dst) || !IF_IN6_NEED_CACHE(ifp))) {
		if (ln == NULL) {
			/* �ߗ׃L���b�V��������`�̏ꍇ */
			if (nd6_is_addr_neighbor(ifp, dst)) {
				/*
				 *  �w�肳�ꂽ�A�h���X�̃m�[�h�����ꃊ���N�ɂ��鎞�́A
				 *  �ߗ׃L���b�V����T�����A����`�̏ꍇ�͓o�^����B
				 */
				ln = nd6_lookup(dst, true);
				}
			else {
				error = E_CLS;
				goto err_ret;
				}
			}

		/*
		 *  �ߗ׃L���b�V���̏�Ԃ��A�f�[�^�����N�w�̃A�h���X���������Ă��Ă��A
		 *  ���B�\�����m�F����Ă��Ȃ��Ƃ��́A���B�s�\�ʒm���J�n����B
		 */
		if (ln->state == ND6_LLINFO_STALE) {
			syscall(get_tim(&now));
			ln->expire = now + ND6_DELAY_TIME;
			ln->asked = 0;
			ln->state = ND6_LLINFO_DELAY;
			}

		/*
		 *  �ߗ׃L���b�V���̏�Ԃ��A�f�[�^�����N�w�̃A�h���X�������̏ꍇ��
		 *  �ߗגT�����s���B
		 */
		if (ln->state <= ND6_LLINFO_INCOMPLETE) {

			/* �^�C���A�E�g�̎w�肪�|�[�����O�Ȃ�^�C���A�E�g�ŏI������B*/
			if (tmout == TMO_POL) {
				error = E_TMOUT;
				goto err_ret;
				}

			if (ln->state == ND6_LLINFO_NO_STATE)
				ln->state = ND6_LLINFO_INCOMPLETE;

			/* ���łɁA�������̃l�b�g���[�N�o�b�t�@������΁A�J������B*/
			if (ln->hold != NULL) {
				syscall(rel_net_buf(ln->hold));
				}

			/*
			 *  ���M���y���f�B���O����B
			 *  IF �Ńl�b�g���[�N�o�b�t�@���J�����Ȃ��t���O���ݒ肳��Ă���Ƃ��́A
			 *  ���M���y���f�B���O���Ȃ��B
			 */
			if ((output->flags & NB_FLG_NOREL_IFOUT) == 0) {
				ln->hold = output;

				/* �^�C���A�E�g�̐ݒ� */
				if (tmout == TMO_FEVR)
					ln->tmout = tmout;
				else {
					syscall(get_tim(&now));
					ln->tmout = now + tmout;
					}
				}
			else {
				output->flags &= ~NB_FLG_NOREL_IFOUT;
				syscall(get_tim(&now));
				ln->tmout = now + tmout;
				}

			if (ln->expire) {
				if (ln->asked < ND6_MAX_MCAST_QUERY) {
					syscall(get_tim(&now));
					if ((int32_t)(ln->expire - now) < 0) {
					           /* ln->expire < now */
						ln->expire += ND6_RETRANS_TIME;	/* �ߗגT�����M�Ԋu */
						ln->asked ++;
						nd6_ns_output(ifp, &in6_addr_unspecified, dst, ln, false);
						}
					}
				}
			return error;
			}
		}

	/*
	 *  �d�������o���ꂽ�C���^�t�F�[�X�ɂ͏o�͂��Ȃ��B
	 */
	if ((ifp->flags & ND6_IFF_IFDISABLED) != 0) {
		return E_OK;
		}

	IF_SET_PROTO(output, IF_PROTO_IPV6);
	error = IF_OUTPUT(output, dst, ln ? & ln->ifaddr : NULL, tmout);
	return error;

err_ret:
	syscall(rel_net_buf(output));
	return error;
	}

/*
 *  nd6_storelladdr -- �o�͂���l�b�g���[�N�C���^�t�F�[�X�̃A�h���X��Ԃ��B
 */

ER
nd6_storelladdr (T_IF_ADDR *out, T_IN6_ADDR *dst, T_IF_ADDR *ifa)
{
	if (IN6_IS_ADDR_MULTICAST(dst)) {
		IF_IN6_RESOLVE_MULTICAST(out, dst);
		}
	else {
		*out = *ifa;
		}

	return E_OK;
	}

/*
 *  nd6_option -- �ߗגT���I�v�V�����̏���
 *
 *    ����: �I�v�V�����I�t�Z�b�g�z��ɂ́A�I�t�Z�b�g + 8 ���ݒ肳��Ă���B
 */

ER
nd6_options (uint8_t *opt, void *nh, uint_t len)
{
	T_ND_OPT_HDR	*opth;
	ER		error = E_OK;
	int_t		pi_count = 0;	/* �v���t�B�b�N�X���̌� */

	opth = (T_ND_OPT_HDR *)nh;
	memset(opt, 0, ND_OPT_OFF_ARRAY_SIZE);

	while (error == E_OK && ((uint8_t *)opth - (uint8_t *)nh) < (256 - 8) && len > 0) {

		/* �I�v�V�������� 0 �̎��́A�s���ȃI�v�V�����Ƃ��ď�������B*/
		if (opth->len == 0) {
			error = E_PAR;
			break;
			}

		/* �I�v�V�����̃^�C�v�ɂ�蕪�򂷂�B*/
		switch (opth->type) {
		case ND_OPT_SOURCE_LINKADDR:		/* ���M��l�b�g���[�N�C���^�t�F�[�X�̃A�h���X	*/
		case ND_OPT_TARGET_LINKADDR:		/* �Ώۃl�b�g���[�N�C���^�t�F�[�X�̃A�h���X	*/
		case ND_OPT_REDIRECTED_HEADER:		/* ���_�C���N�g�E�w�b�_				*/
		case ND_OPT_MTU:			/* MTU						*/
			if (opt[ND_OPT_OFF_ARRAY_IX(opth->type)]) {
				/* �v���t�B�b�N�X���ȊO�̓����I�v�V�����������w�肳��Ă���B*/
				error = E_PAR;
				}
			else {
				opt[ND_OPT_OFF_ARRAY_IX(opth->type)] = (uint8_t *)opth - (uint8_t *)nh + 8;
				}
			break;
		case ND_OPT_PREFIX_INFORMATION:		/* �v���t�B�b�N�X���				*/
			if (!opt[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFORMATION)]) {
				/*
				 *  �v���t�B�b�N�X���͍ŏ��Ɍ��ꂽ�I�t�Z�b�g�̂݋L�^����B
				 */
				opt[ND_OPT_OFF_ARRAY_IX(opth->type)] = (uint8_t *)opth - (uint8_t *)nh + 8;
				}
			pi_count ++;
			break;
		default:
			/*
			 *  ������`�����v���g�R���ւ̊g���ɑΉ����邽�߁A
			 *  �F���ł��Ȃ��I�v�V�����͒P�ɖ������A�����𑱍s����B
			 */
			break;
			}
		len -= opth->len << 3;		/* �I�v�V�������̒P�ʂ� 8 �o�C�g */
		opth = (T_ND_OPT_HDR *)((uint8_t *)opth + (opth->len << 3));
		}

	opt[ND_OPT_OFF_ARRAY_IX(ND_OPT_PREFIX_INFO_COUNT)] = pi_count;
	return error;
	}

#endif /* of #ifdef SUPPORT_INET6 */
