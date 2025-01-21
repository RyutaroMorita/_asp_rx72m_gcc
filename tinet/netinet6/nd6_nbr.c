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
 *  @(#) $Id: nd6_nbr.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/nd6_nbr.c,v 1.13 2002/10/16 01:54:45 sam Exp $	*/
/*	$KAME: nd6_nbr.c,v 1.86 2002/01/21 02:33:04 jinmei Exp $	*/

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

#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#include <netinet6/ip6_var.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

/*
 *  �Ǐ��֐�
 */

static void nd6_dad_timer (T_IN6_IFADDR *ifa);
static void nd6_dad_duplicated (T_IFNET *ifp, T_IN6_IFADDR *ifa);
static void nd6_dad_ns_output (T_IFNET *ifp, T_IN6_IFADDR *ifa);
static void nd6_dad_ns_input (T_IFNET *ifp, T_IN6_IFADDR *ifa);
static void nd6_dad_na_input (T_IFNET *ifp, T_IN6_IFADDR *ifa);

/*
 *  nd6_dad_duplicated -- �d���A�h���X�����o�������̏���
 */

static void
nd6_dad_duplicated (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	if ((ifa->flags & IN6_IFF_TENTATIVE) == 0)
		syslog(LOG_ERROR, "[ND6 DAD DUP] no pending.");
	else {
		syslog(LOG_ERROR, "[ND6 DAD DUP] dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		ifa->flags &= ~IN6_IFF_TENTATIVE;
		ifa->flags |=  IN6_IFF_DUPLICATED;

		/* �^�C�}�[���~����B*/
		untimeout((callout_func)nd6_dad_timer, ifa);

		/*
		 *  ���� IPv6 �A�h���X���A���j�[�N�Ɋ��蓖�Ă炽
		 * �i�C�[�T�l�b�g�p�� EUI-64�j�n�[�h�E�F�A�A�h���X���x�[�X�Ƃ���
		 *  �C���^�t�F�[�X ID �Ő������ꂽ�̂ł���΁A
		 *  ���̃C���^�t�F�[�X�ł� IPv6 �̓���͖����ɂ��ׂ��ł���
		 * �iRFC2462bis-03 �Z�N�V���� 5.4.5�j�B
		 */
		if (IN6_IS_ADDR_LINKLOCAL(&ifa->addr))
			ifp->flags |= ND6_IFF_IFDISABLED;
		}
	}

/*
 *  nd6_dad_ns_output -- �d���A�h���X���o (DAD) �v�����o�͂���B
 */

static void
nd6_dad_ns_output (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_DAD_OUT_PACKETS], 1);

	ifa->ns_ocount ++;
	nd6_ns_output(ifp, &in6_addr_unspecified, &ifa->addr, NULL, true);
	}

/*
 *  nd6_dad_ns_input -- �d���A�h���X���o (DAD) �v������
 */

static void
nd6_dad_ns_input (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_IN_PACKETS], 1);

	/*
	 *  �܂��A�d���A�h���X���o�v�����o�͂��Ă��Ȃ��ꍇ
	 */
	if (ifa->ns_ocount == 0)
		nd6_dad_duplicated(ifp, ifa);
	else
		ifa->ns_icount ++;
	}

/*
 *  nd6_dad_na_input -- �d���A�h���X���o (DAD) �ʒm����
 */

static void
nd6_dad_na_input (T_IFNET *ifp, T_IN6_IFADDR *ifa)
{
	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NA_IN_PACKETS], 1);
	ifa->na_icount ++;
	nd6_dad_duplicated(ifp, ifa);
	}

/*
 *  nd6_dad_timer -- �d���A�h���X���o (DAD) �^�C�}�[
 */

static void
nd6_dad_timer (T_IN6_IFADDR *ifa)
{
	T_IFNET *ifp = IF_GET_IFNET();

	if (ifa->flags & IN6_IFF_DUPLICATED) {
		syslog(LOG_ERROR, "[ND6 DAD] dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		return;
		}

	if ((ifa->flags & IN6_IFF_TENTATIVE) == 0) {
		syslog(LOG_ERROR, "[ND6 DAD] no tentative IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		return;
		}

	if (ifa->ns_ocount < NUM_IP6_DAD_COUNT) {
		nd6_dad_ns_output(ifp, ifa);

		/* �^�C���A�E�g���ߗגT���̑��M�Ԋu�ɐݒ肷��B*/
		timeout((callout_func)nd6_dad_timer, ifa, ND6_RETRANS_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		}
	else if (ifa->na_icount || ifa->ns_icount)
		nd6_dad_duplicated(ifp, ifa);
	else {
		ifa->flags &= ~IN6_IFF_TENTATIVE;
		syslog(LOG_NOTICE, "[ND6 DAD] no dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		}
	}

/*
 *  nd6_ns_input -- �ߗחv���̓��͏����B
 */

void
nd6_ns_input (T_NET_BUF *input, uint_t off)
{
	T_IFNET			*ifp = IF_GET_IFNET();
	T_IP6_HDR		*ip6h;
	T_NEIGHBOR_SOLICIT_HDR	*nsh;
	T_ND_OPT_HDR		*opth;
	T_IN6_IFADDR		*ifa;
	bool_t			tlladdr;
	uint_t			lladdr_len = 0;
	uint32_t		flags;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_IN_PACKETS], 1);

	ip6h = GET_IP6_HDR(input);

	/*
	 *  �w�b�_�̃`�F�b�N�A�ȉ��̏ꍇ�͔j������B
	 *    �E�z�b�v���~�b�g�� IPV6_MAXHLIM (255) �ȊO
	 *    �E�w�b�_�����Z��
	 */
	if (ip6h->hlim != IPV6_MAXHLIM || input->len - off < NEIGHBOR_SOLICIT_HDR_SIZE)
		goto err_ret;

	nsh  = (T_NEIGHBOR_SOLICIT_HDR *)(input->buf + off);

	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src)) {
		/*
		 *  �n�_�A�h���X�����w��Ȃ�A�d���A�h���X���o
		 *  ���Đ�A�h���X�́A�v���}���`�L���X�g�łȂ���΂Ȃ�Ȃ��B
		 */
		if (!IN6_IS_ADDR_NS_MULTICAST(&ip6h->dst))
			goto err_ret;
		}

	/* �ړI�A�h���X���}���`�L���X�g�Ȃ�G���[ */
	if (IN6_IS_ADDR_MULTICAST(&nsh->target))
		goto err_ret;

	/* �ߗגT���I�v�V�����̃I�t�Z�b�g���L�^����B*/
	if (nd6_options(nd_opt_off, input->buf + (off + NEIGHBOR_SOLICIT_HDR_SIZE),
	                            input->len - (off + NEIGHBOR_SOLICIT_HDR_SIZE)) != E_OK)
		goto err_ret;

	/* �ߗגT���I�v�V���� (�n�_�����N�A�h���X) */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + NEIGHBOR_SOLICIT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_SOURCE_LINKADDR)] - 8);
	 	/* ����: �I�v�V�����I�t�Z�b�g�z��ɂ́A�I�t�Z�b�g + 8 ���ݒ肳��Ă���B*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src) && lladdr != NULL)
		goto err_ret;

	/* ����A�h���X���}���`�L���X�g�Ȃ�ߗגʒm�Ƀf�[�^�����N�w�̃A�h���X��t����B*/
	if (IN6_IS_ADDR_MULTICAST(&ip6h->dst))
		tlladdr = true;
	else
		tlladdr = false;

	/*
	 *  �ړI�A�h���X���A�����̃l�b�g���[�N�C���^�t�F�[�X��
	 *  ���蓖�Ă��Ă���A�h���X�����ׂ�B
	 *  �Ȃ��A�㗝�T�[�r�X�͎������Ă��Ȃ��B
	 */
	ifa = in6_lookup_ifaddr(ifp, &nsh->target);

	if (ifa == NULL)
		goto free_ret;

	/* �T�����ʃA�h���X���d�����Ă���Ή������Ȃ��ŏI������B*/
	if (ifa->flags & IN6_IFF_DUPLICATED)
		goto err_ret;

	/*
	 *  �l�b�g���[�N�C���^�t�F�[�X�̃A�h���X������v���Ȃ���΃G���[
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/*
	 *  �n�_�A�h���X�������̃A�h���X�ƈ�v����Ώd�����Ă���B
	 */
	if (IN6_ARE_ADDR_EQUAL(&ifa->addr, &ip6h->src))
		goto free_ret;

	/* �d�����o���ɁA�ߗחv������M�����Ƃ��̏��� */
	if (ifa->flags & IN6_IFF_TENTATIVE) {
		if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src))
			nd6_dad_ns_input(ifp, ifa);
		goto free_ret;
		}

	if ((ifa->flags & IN6_IFF_ANYCAST) || !tlladdr)
		flags = 0;
	else
		flags = ND_NA_FLG_OVERRIDE;

	/*
	 *  �n�_�A�h���X�����w��Ȃ�A���M����͏d���A�h���X���o���ŁA
	 *  ���ڑ��M���邱�Ƃ͂ł��Ȃ��̂ŁA�S�m�[�h�}���`�L���X�g
	 *  �A�h���X�ɑ��M����B
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src)) {
		nd6_na_output(ifp, &in6_addr_linklocal_allnodes, &nsh->target, flags, tlladdr);
		goto free_ret;
		}

	/* �ߗ׃L���b�V���ɓo�^����B*/
	nd6_cache_lladdr(ifp, &ip6h->src, (T_IF_ADDR *)lladdr, ND_NEIGHBOR_SOLICIT, 0);

	nd6_na_output(ifp, &ip6h->src, &nsh->target, flags | ND_NA_FLG_SOLICITED, tlladdr);

free_ret:
	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}

/*
 *  nd6_ns_output -- �ߗחv�����o�͂���B
 */

void
nd6_ns_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
               T_IN6_ADDR *taddr, T_LLINFO_ND6 *ln, bool_t dad)
{
	T_NEIGHBOR_SOLICIT_HDR	*nsh;
	T_NET_BUF		*output;
	T_IP6_HDR		*ip6h;
	T_IF_ADDR		*mac = NULL;
	uint_t			len;
	uint16_t		ipflags = 0;

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_OUT_PACKETS], 1);

	if (IN6_IS_ADDR_MULTICAST(taddr))
		return;

	/* �ߗחv���y�C���[�h�����v�Z����B*/
	if (!dad && IF_SOFTC_TO_IFADDR(ifp->ic))
		len = (NEIGHBOR_SOLICIT_HDR_SIZE + ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
	else
		len = (NEIGHBOR_SOLICIT_HDR_SIZE + 7) >> 3 << 3;

	/*
	 *  �v���}���`�L���X�g�E�A�h���X���̋ߗגT���ł́A
	 *  ���̃����N����̋U�����ꂽ�f�[�^�O������
	 *  �r�����邽�߁A�z�b�v���~�b�g�� IPV6_MAXHLIM (255) ��ݒ肷��B
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(daddr) || IN6_IS_ADDR_MULTICAST(daddr))
		ipflags = IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_MAXHLIM);

	/* �l�b�g���[�N�o�b�t�@���l�����AIPv6 �w�b�_��ݒ肷��B*/
	if (in6_get_datagram(&output, len, 0, daddr, NULL,
	                     IPPROTO_ICMPV6, IPV6_MAXHLIM,
	                     NBA_SEARCH_ASCENT, TMO_ND6_NS_OUTPUT) != E_OK)
		return;

	ip6h = GET_IP6_HDR(output);

	if (IN6_IS_ADDR_UNSPECIFIED(daddr)) {

		/* ����A�h���X�����w��̏ꍇ�́A�v���}���`�L���X�g�A�h���X��ݒ肷��B*/
		ip6h->dst.s6_addr32[0] = IPV6_ADDR_INT32_MLL;
		ip6h->dst.s6_addr32[2] = IPV6_ADDR_INT32_ONE;
		ip6h->dst.s6_addr32[3] = taddr->s6_addr32[3];
		ip6h->dst.s6_addr8[12] = 0xff;
		}

	/* ���M���A�h���X�̐ݒ� */
	if (!dad) {

		/* �d���A�h���X���o�ł͂Ȃ����̑��M���A�h���X���菈���B*/
		T_IN6_ADDR *saddr;

		if (ln && ln->hold) {
			/*
			 * ���M���y���f�B���O����Ă���f�[�^�O������
			 * ���M���A�h���X�𗘗p����B
			 */
			if (ln->hold->len > IF_IP6_HDR_SIZE)
				saddr = &GET_IP6_HDR(ln->hold)->src;
			else
				saddr = NULL;
			}
		else
			saddr = NULL;

		if (saddr && in6_lookup_ifaddr(ifp, saddr))
			ip6h->src = *saddr;
		else {
			/*
			 *  ����A�h���X�ɂӂ��킵�����M���A�h���X���A
			 *  �l�b�g���[�N�C���^�t�F�[�X����T�����ė��p����B
			 */
			T_IN6_IFADDR *ifa;

			if ((ifa = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
				syscall(rel_net_buf(output));
				return;
				}
			ip6h->src = ifa->addr;
			}
		}
	else {

		/* �d���A�h���X���o���̑��M���A�h���X�͖��w��B*/
		memset(&ip6h->src, 0, sizeof(T_IN6_ADDR));
		}

 	/* �ߗחv���w�b�_��ݒ肷��B*/
 	nsh = GET_NEIGHBOR_SOLICIT_HDR(output, IF_IP6_NEIGHBOR_SOLICIT_HDR_OFFSET);
 	nsh->hdr.type        = ND_NEIGHBOR_SOLICIT;
 	nsh->hdr.code        = 0;
 	nsh->hdr.data.data32 = 0;
 	nsh->target          = *taddr;

	if (!dad && (mac = IF_SOFTC_TO_IFADDR(ifp->ic)) != NULL) {

		/* �ߗגT���I�v�V�����Ƃ��āA�T���ڕW�� MAC �A�h���X��ݒ肷��B*/
		T_ND_OPT_HDR	*opth;
		uint_t		optlen;

		opth   = (T_ND_OPT_HDR *)GET_NEIGHBOR_SOLICIT_SDU(output, IF_IP6_NEIGHBOR_SOLICIT_HDR_OFFSET);
		optlen = (ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
		memset(opth, 0, optlen);
		opth->type = ND_OPT_SOURCE_LINKADDR;
		opth->len  = optlen >> 3;
		memcpy((uint8_t *)opth + sizeof(T_ND_OPT_HDR), mac, sizeof(T_IF_ADDR));
		}

	/* �`�F�b�N�T�����v�Z����B*/
	nsh->hdr.sum = 0;
	nsh->hdr.sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)nsh - output->buf, len);

	/* ���M����B*/
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutNeighborSolicits, 1);
	ip6_output(output, ipflags | IPV6_OUT_FLG_DAD, TMO_ND6_NS_OUTPUT);
	}

/*
 *  nd6_na_input -- �ߗגʒm�̓��͏����B
 */

void
nd6_na_input (T_NET_BUF *input, uint_t off)
{
	T_IFNET			*ifp = IF_GET_IFNET();
	T_IP6_HDR		*ip6h;
	T_NEIGHBOR_ADVERT_HDR	*nah;
	T_ND_OPT_HDR		*opth;
	T_IN6_IFADDR		*ifa;
	T_LLINFO_ND6		*ln;
	SYSTIM			now;
	bool_t			llchange;
	uint_t			lladdr_len = 0;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NS_IN_PACKETS], 1);

	ip6h = GET_IP6_HDR(input);

	/*
	 *  �w�b�_�̃`�F�b�N�A�ȉ��̏ꍇ�͔j������B
	 *    �E�z�b�v���~�b�g�� IPV6_MAXHLIM (255) �ȊO
	 *    �E�w�b�_�����Z��
	 */
	if (ip6h->hlim != IPV6_MAXHLIM || input->len - off < NEIGHBOR_ADVERT_HDR_SIZE)
		goto err_ret;

	nah  = (T_NEIGHBOR_ADVERT_HDR *)(input->buf + off);

	/* �ړI�A�h���X���}���`�L���X�g�Ȃ�G���[ */
	if (IN6_IS_ADDR_MULTICAST(&nah->target))
		goto err_ret;

	/* �ߗחv���ւ̉����ŁA����A�h���X���}���`�L���X�g�Ȃ�G���[ */
	if ((nah->nd_na_flags_reserved & ND_NA_FLG_SOLICITED) &&
	    IN6_IS_ADDR_MULTICAST(&ip6h->dst))
		goto err_ret;

	/* �ߗגT���I�v�V�����̃I�t�Z�b�g���L�^����B*/
	if (nd6_options(nd_opt_off, input->buf + (off + NEIGHBOR_ADVERT_HDR_SIZE), 
	                            input->len - (off + NEIGHBOR_ADVERT_HDR_SIZE)) != E_OK)
		goto err_ret;

	/* �ߗגT���I�v�V���� (�ړI�����N�A�h���X) */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + NEIGHBOR_ADVERT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)] - 8);
	 	/* ����: �I�v�V�����I�t�Z�b�g�z��ɂ́A�I�t�Z�b�g + 8 ���ݒ肳��Ă���B*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	ifa = in6_lookup_ifaddr(ifp, &nah->target);

	/*
	 *  �ړI�A�h���X�������̃l�b�g���[�N�C���^�t�F�[�X�Ɋ��蓖�Ă��Ă���A�h���X��
	 *  �����ꂩ�Ɉ�v�����Ƃ��́A�d�����Ă��邱�Ƃ��Ӗ����Ă���B
	 */
	if (ifa) {
		if (ifa->flags & IN6_IFF_TENTATIVE)
			nd6_dad_na_input(ifp, ifa);
		else
			syslog(LOG_ERROR, "[ND6 NA INPUT] dup IPv6 addr: %s.", ipv62str(NULL, &ifa->addr));
		goto err_ret;
		}

	/*
	 *  �l�b�g���[�N�C���^�t�F�[�X�̃A�h���X������v���Ȃ���΃G���[
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/* �ߗ׃L���b�V����T������B*/
	syscall(wai_sem(SEM_ND6_CACHE));
	if ((ln = nd6_lookup(&nah->target, false)) == NULL)
		goto free_ret;

	/* �ߗ׃L���b�V���̏�Ԃ��A�f�[�^�����N�w�̃A�h���X�������̏ꍇ */
	if (ln->state == ND6_LLINFO_INCOMPLETE) {
		/* �ʒm���ꂽ�f�[�^�����N�w�̃A�h���X�̒����� 0 �̏ꍇ */
		if (lladdr == NULL)
			goto free_ret;

		ln->ifaddr = *(T_IF_ADDR *)lladdr;
		if (nah->nd_na_flags_reserved & ND_NA_FLG_SOLICITED) {
			ln->state = ND6_LLINFO_REACHABLE;
			/*ln->byhint = 0*/;
			if (ln->expire) {
				syscall(get_tim(&now));
				ln->expire = now + ND6_REACHABLE_TIME;
				}
			}
		else {
			syscall(get_tim(&now));
			ln->expire = now + ND6_GCOLLECTION_TIME;
			ln->state  = ND6_LLINFO_STALE;
			}

		if ((nah->nd_na_flags_reserved & ND_NA_FLG_ROUTER) != 0)
			ln->flags |=  ND6_LLIF_ROUTER;
		else
			ln->flags &= ~ND6_LLIF_ROUTER;
		if ((ln->flags & ND6_LLIF_ROUTER) != 0)
			/*pfxlist_onlink_check()*/;
		}
	else {
		if (lladdr == NULL)
			llchange = false;
		else if (memcmp(lladdr, &ln->ifaddr, sizeof(T_IF_ADDR)))
			llchange = true;
		else
			llchange = false;

		/*
		 *  ��ԑJ�ڕ\
		 *
		 *  nd_na_flags_reserved
		 *  OVERRIDE    SOLICTED lladdr llchange ���� (L: lladdr ��o�^����)
		 *
		 *      F           F       N      -    (2c)
		 *      F           F       Y      F    (2b) L
		 *      F           F       Y      T    (1)    REACHABLE -> STALE
		 *      F           T       N      -    (2c)           * -> REACHABLE
		 *      F           T       Y      F    (2b) L         * -> REACHABLE
		 *      F           T       Y      T    (1)    REACHABLE -> STALE
		 *      T           F       N      -    (2a)
		 *      T           F       Y      F    (2a) L
		 *      T           F       Y      T    (2a) L         *-> STALE
		 *      T           T       N      -    (2a)           * -> REACHABLE
		 *      T           T       Y      F    (2a) L         * -> REACHABLE
		 *      T           T       Y      T    (2a) L         * -> REACHABLE
		 */
		if ((nah->nd_na_flags_reserved & ND_NA_FLG_OVERRIDE) == 0 && (lladdr != NULL && llchange)) {	/* (1) */
			/* ��Ԃ� REACHABLE �Ȃ� STALE �ɑJ�ڂ���B*/
			if (ln->state == ND6_LLINFO_REACHABLE) {
				syscall(get_tim(&now));
				ln->expire = now + ND6_GCOLLECTION_TIME;
				ln->state  = ND6_LLINFO_STALE;
				}
			goto free_ret;
			}
		else if ((nah->nd_na_flags_reserved & ND_NA_FLG_OVERRIDE) ||						/* (2a) */
		         ((nah->nd_na_flags_reserved & ND_NA_FLG_OVERRIDE) == 0 && (lladdr != NULL && !llchange)) ||	/* (2b) */
		         lladdr == NULL) {										/* (2c) */

			/* �f�[�^�����N�w�̃A�h���X���ʒm����Ă���΍X�V����B*/
			if (lladdr != NULL)
				ln->ifaddr = *(T_IF_ADDR *)lladdr;

			/* �ߗחv���ւ̉����Ȃ� REACHABLE �ɑJ�ڂ���B*/
			if (nah->nd_na_flags_reserved & ND_NA_FLG_SOLICITED) {
				ln->state = ND6_LLINFO_REACHABLE;
				/*ln->byhint = 0*/;
				if (ln->expire) {
					syscall(get_tim(&now));
					ln->expire = now + ND6_REACHABLE_TIME;
					}
				}
			/*
			 *  �f�[�^�����N�w�̃A�h���X���ʒm����A
			 *  �قȂ�A�h���X�Ȃ�X�V����B
			 */
			else if (lladdr != NULL && llchange) {
				syscall(get_tim(&now));
				ln->expire = now + ND6_GCOLLECTION_TIME;
				ln->state  = ND6_LLINFO_STALE;
				}
			}

		/* ���[�^�ʒm�t���O�̏��� */
		if ((ln->flags        & ND6_LLIF_ROUTER ) != 0 &&
		    (nah->nd_na_flags_reserved & ND_NA_FLG_ROUTER) == 0) {
			/*
			 *  ���M���肪���[�^�ʒm�t���O�𖳌��ɂ����ꍇ�B
			 *  �f�B�t�H���g�E���[�^���X�g����Ώۂ̃��[�^���폜���A
			 *  �ߗגT���L���b�V�����X�V����B
			 */
			T_DEF_ROUTER	*dr = NULL;

			syscall(wai_sem(SEM_ND6_DEFRTRLIST));
			if ((dr = nd6_defrtrlist_lookup(&ln->addr)) != NULL) {
				nd6_defrtrlist_del(dr);
				}
			syscall(sig_sem(SEM_ND6_DEFRTRLIST));
			}
		if ((nah->nd_na_flags_reserved & ND_NA_FLG_ROUTER) != 0)
			ln->flags |=  ND6_LLIF_ROUTER;
		else
			ln->flags &= ~ND6_LLIF_ROUTER;
		}

	ln->asked = 0;

	/* �A�h���X�����҂��̃f�[�^�O����������Α��M����B*/
	nd6_output_hold(ifp, ln);

free_ret:
	syscall(sig_sem(SEM_ND6_CACHE));
	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}

/*
 *  nd6_na_output -- �ߗגʒm���o�͂���B
 */

void
nd6_na_output (T_IFNET *ifp, T_IN6_ADDR *daddr,
               T_IN6_ADDR *taddr, uint32_t flags, bool_t tlladdr)
{
	T_NEIGHBOR_ADVERT_HDR	*nah;
	T_NET_BUF		*output;
	T_IP6_HDR		*ip6h;
	T_IN6_IFADDR		*ifa;
	T_IF_ADDR		*mac = NULL;
	uint_t			len;
	uint16_t		ipflags = 0;

	NET_COUNT_ICMP6(net_count_nd6[NC_ND6_NA_OUT_PACKETS], 1);

	/*
	 *  �ߗגʒm�y�C���[�h�����v�Z����B
	 *  tlladdr ���^�Ȃ�l�b�g���[�N�C���^�t�F�[�X�̃A�h���X��ǉ�����B
	 */
	if (tlladdr && IF_SOFTC_TO_IFADDR(ifp->ic))
		len = (NEIGHBOR_ADVERT_HDR_SIZE + ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
	else
		len = (NEIGHBOR_ADVERT_HDR_SIZE + 7) >> 3 << 3;

	/*
	 *  ���̃����N����̋U�����ꂽ�f�[�^�O������
	 *  �r�����邽�߁A�z�b�v���~�b�g�� IPV6_MAXHLIM (255) ��ݒ肷��B
	 */
	ipflags = IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_MAXHLIM);

	/* �l�b�g���[�N�o�b�t�@���l�����AIPv6 �w�b�_��ݒ肷��B*/
	if (in6_get_datagram(&output, len, 0, daddr, NULL,
	                     IPPROTO_ICMPV6, IPV6_MAXHLIM,
	                     NBA_SEARCH_ASCENT, TMO_ND6_NA_OUTPUT) != E_OK)
		return;

	ip6h = GET_IP6_HDR(output);

	if (IN6_IS_ADDR_UNSPECIFIED(daddr)) {
		/*
		 *  ����A�h���X�����w��̏ꍇ�́A
		 *  �����N���[�J���S�m�[�h�E�}���`�L���X�g�A�h���X��ݒ肷��B
		 */
		ip6h->dst.s6_addr32[0] = IPV6_ADDR_INT32_MLL;
		ip6h->dst.s6_addr32[1] = 0;
		ip6h->dst.s6_addr32[2] = 0;
		ip6h->dst.s6_addr32[3] = IPV6_ADDR_INT32_ONE;
		flags &= ~ND_NA_FLG_SOLICITED;
		}
	else
		ip6h->dst = *daddr;

	/*
	 *  ����A�h���X�ɂӂ��킵�����M���A�h���X���A
	 *  �l�b�g���[�N�C���^�t�F�[�X����T�����ė��p����B
	 */
	if ((ifa = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
		syscall(rel_net_buf(output));
		return;
		}
	ip6h->src = ifa->addr;

 	/* �ߗגʒm�w�b�_��ݒ肷��B*/
 	nah = GET_NEIGHBOR_ADVERT_HDR(output, IF_IP6_NEIGHBOR_ADVERT_HDR_OFFSET);
 	nah->hdr.type        = ND_NEIGHBOR_ADVERT;
 	nah->hdr.code        = 0;
 	nah->target          = *taddr;

	/* tlladdr ���^�Ȃ�l�b�g���[�N�C���^�t�F�[�X�̃A�h���X��ǉ�����B*/
	if (tlladdr && (mac = IF_SOFTC_TO_IFADDR(ifp->ic)) != NULL) {

		T_ND_OPT_HDR	*opth;
		uint_t		optlen;

		opth   = (T_ND_OPT_HDR *)GET_NEIGHBOR_ADVERT_SDU(output, IF_IP6_NEIGHBOR_ADVERT_HDR_OFFSET);
		optlen = (ND_OPT_HDR_SIZE + sizeof(T_IF_ADDR) + 7) >> 3 << 3;
		memset(opth, 0, optlen);
		opth->type = ND_OPT_TARGET_LINKADDR;
		opth->len  = optlen >> 3;
		memcpy((uint8_t *)opth + sizeof(T_ND_OPT_HDR), mac, sizeof(T_IF_ADDR));
		}
	else
		flags &= ~ND_NA_FLG_OVERRIDE;

	nah->nd_na_flags_reserved = flags;

	/* �`�F�b�N�T�����v�Z����B*/
	nah->hdr.sum = 0;
	nah->hdr.sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)nah - output->buf, len);

	/* ���M����B*/
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutNeighborAdvertisements, 1);
	ip6_output(output, ipflags, TMO_ND6_NS_OUTPUT);
	}

/*
 *  nd6_dad_start -- �d���A�h���X���o (DAD) ���J�n����B
 *
 *    ��3������tick �́A�C���^�t�F�[�X���N������Ă���A�d�����o��
 *    ���M����܂ł̍ŏ��x���l�ł���B
 */

void
nd6_dad_start (T_IFNET *ifp, T_IN6_IFADDR *ifa, int_t *tick)
{
	/* �t���O���`�F�b�N����B*/
	if (!(ifa->flags & IN6_IFF_TENTATIVE))
		return;

#if NUM_IP6_DAD_COUNT == 0

	ifa->flags &= ~IN6_IFF_TENTATIVE;

#else	/* of #if NUM_IP6_DAD_COUNT == 0 */

	if (ifa->flags & IN6_IFF_ANYCAST) {
		ifa->flags &= ~IN6_IFF_TENTATIVE;
		return;
		}
	else if ((ifa->flags & IN6_IFF_TENTATIVE) == 0)
		return;

	/* �d���A�h���X���o�J�E���^�����Z�b�g����B*/
	ifa->ns_icount = ifa->na_icount = ifa->ns_ocount = 0;

	/*
	 *  �d���A�h���X���o�v���𑗐M����B�������A�C���^�t�F�[�X��
	 *  ��������������ɁA�ŏ��ɑ��M����ꍇ�́A�����_���Ȓx�����s���B
	 */
	if (tick == NULL) {
		nd6_dad_ns_output(ifp, ifa);

		/* �^�C���A�E�g���ߗגT���̑��M�Ԋu�ɐݒ肷��B*/
		timeout((callout_func)nd6_dad_timer, ifa, ND6_RETRANS_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		}
	else {
		int_t ntick;

		if (*tick == 0)	/* �ŏ��̑��M */
			ntick = net_rand() % (ND6_FIRST_DAD_DELAY_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		else
			ntick = *tick + net_rand() % (ND6_DAD_DELAY_TIME * NET_TIMER_HZ / SYSTIM_HZ);
		*tick = ntick;
		timeout((callout_func)nd6_dad_timer, ifa, ntick);
		}

#endif	/* of #if NUM_IP6_DAD_COUNT == 0 */

	}

#endif /* of #ifdef SUPPORT_INET6 */
