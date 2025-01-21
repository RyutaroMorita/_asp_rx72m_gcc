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
 *  @(#) $Id: in6_ifattach.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/in6_ifattach.c,v 1.2.2.5 2001/08/13 16:26:17 ume Exp $	*/
/*	$KAME: in6_ifattach.c,v 1.118 2001/05/24 07:44:00 itojun Exp $	*/

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

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>
#include <netinet6/in6_ifattach.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 * EUI64 �̒�`
 */

#define EUI64_UBIT		0x02

#ifdef SUPPORT_ETHER

/*
 * get_mac6_ifid -- MAC (6 �I�N�e�b�g) �A�h���X�ŁA�C���^�t�F�[�X���ʎq��ݒ肷��B
 */

static ER
get_mac6_ifid (T_IFNET *ifp, T_IN6_ADDR *ifra_addr)
{
	ifra_addr->s6_addr[ 8] = ifp->ic->ifaddr.lladdr[0] ^ EUI64_UBIT;
	ifra_addr->s6_addr[ 9] = ifp->ic->ifaddr.lladdr[1];
	ifra_addr->s6_addr[10] = ifp->ic->ifaddr.lladdr[2];
	ifra_addr->s6_addr[11] = UINT_C(0xff);
	ifra_addr->s6_addr[12] = UINT_C(0xfe);
	ifra_addr->s6_addr[13] = ifp->ic->ifaddr.lladdr[3];
	ifra_addr->s6_addr[14] = ifp->ic->ifaddr.lladdr[4];
	ifra_addr->s6_addr[15] = ifp->ic->ifaddr.lladdr[5];

	return E_OK;
	}

#endif	/* of #ifdef SUPPORT_ETHER */

#ifdef IP6_CFG_AUTO_LINKLOCAL

/*
 *  in6_ifattach_linklocal -- �C���^�t�F�[�X�Ƀ����N���[�J���E�A�h���X�����蓖�Ă�B
 */

static ER
in6_ifattach_linklocal (T_IFNET *ifp)
{
	T_IN6_ADDR	addr;
	ER		error = E_OK;

	/*
	 *  �����N���[�J���E�v���t�B�b�N�X fe80::/64 ��ݒ肷��B
	 */
	addr.s6_addr32[0] = IPV6_ADDR_INT32_ULL;
	addr.s6_addr32[1] = ULONG_C(0);

	/* �C���^�t�F�[�X���ʎq��ݒ肷��B*/
	if ((error = IF_IN6_IFID(ifp, &addr)) != E_OK)
		return error;

	/* �C���^�t�F�[�X�̃A�h���X�����X�V����B*/
	if ((error = in6_update_ifa(ifp, &ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL],
	                            &addr, 64, ND6_INFINITE_LIFETIME,
	                                       ND6_INFINITE_LIFETIME, 
	                                       IN6_RTR_IX_UNREACH, ND6_PREFIX_IX_INVALID, 0)) != E_OK)
		return error;

	return error;
	}

#endif	/* of #ifdef IP6_CFG_AUTO_LINKLOCAL */

/*
 *  in6_ifattach -- �C���^�t�F�[�X�ɃA�h���X�����蓖�Ă�B
 */

ER
in6_ifattach (T_IFNET *ifp)
{
	ER error = E_OK;

#ifdef IP6_CFG_AUTO_LINKLOCAL

	if ((ifp->in_ifaddrs[IPV6_IFADDR_IX_LINKLOCAL].flags & IN6_IFF_DEFINED) == 0)
		if ((error = in6_ifattach_linklocal(ifp)) != E_OK)
			return error;

#endif	/* of #ifdef IP6_CFG_AUTO_LINKLOCAL */

	return error;
	}

#endif /* of #ifdef SUPPORT_INET6 */
