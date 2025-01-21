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
 *  @(#) $Id: icmp6.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*	$FreeBSD: src/sys/netinet6/icmp66.c,v 1.6.2.6 2001/07/10 09:44:16 ume Exp $	*/
/*	$KAME: icmp66.c,v 1.211 2001/04/04 05:56:20 itojun Exp $	*/

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
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	@(#)ip_icmp6.c	8.2 (Berkeley) 1/4/94
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>

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
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>
#include <netinet6/nd6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>

#ifdef SUPPORT_INET6

/*
 *  �ϐ�
 */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

T_ICMP6_IFSTAT icmp6_ifstat;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  icmp6_output -- ICMP6 �p�P�b�g�𑗐M����B
 */

static void
icmp6_output (T_NET_BUF *output, uint_t off)
{
	T_IN6_IFADDR	*ia;
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;

	/*
	 *  ����A�h���X�ɂӂ��킵�����M���A�h���X���A
	 *  �l�b�g���[�N�C���^�t�F�[�X����T�����ė��p����B
	 */
	ip6h = GET_IP6_HDR(output);
	if ((ia = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutErrors, 1);
		syscall(rel_net_buf(output));
		return;
		}
	ip6h->src = ia->addr;

	icmp6h = GET_ICMP6_HDR(output, off);

	/* �`�F�b�N�T�����v�Z����B*/
	icmp6h->sum = 0;
	icmp6h->sum = in6_cksum(output, IPPROTO_ICMPV6, (uint8_t*)icmp6h - output->buf, 
	                        ntohs(ip6h->plen) - (off - IF_IP6_HDR_SIZE));

	/* ���M����B*/
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_OCTETS],
	               output->len - GET_IF_IP6_HDR_SIZE(output));
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	ip6_output(output, 0, TMO_ICMP_OUTPUT);
	}

/*
 *  icmp6_echo_request -- �G�R�[�v������M�����Ƃ��̏���
 */

static void
icmp6_echo_request (T_NET_BUF *input, uint_t off)
{
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN6_IFADDR	*ia;
	T_IN6_ADDR	dst;
	uint_t		diff;

	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInEchos, 1);

	ip6h       = GET_IP6_HDR(input);

	/*
	 *  IPv6 �w�b�_�� ICMPv6 �w�b�_�Ԃ̊g���w�b�_����������B
	 */
	diff = off - IF_IP6_HDR_SIZE;
	if (diff > 0) {
		/* ICMPv6 �w�b�_��O�ɋl�߂�B*/
		memmove(input->buf + IF_IP6_HDR_SIZE, input->buf + off, input->len - off);
		off = IF_IP6_HDR_SIZE;

		/* �y�C���[�h���𒲐�����B*/
		ip6h->plen  = htons(ntohs(ip6h->plen) - diff);
		input->len -= diff;
		}

	icmp6h = GET_ICMP6_HDR(input, off);
	if (icmp6h->code != 0) {
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		syscall(rel_net_buf(input));
		return;
		}

	/*
	 *  ���b�Z�[�W�̌^���G�R�[�v�� (128) ����
	 *  �G�R�[���� (129) �ɕύX���đ���Ԃ��B
	 */
	icmp6h->type = ICMP6_ECHO_REPLY;

	/* IPv6 �w�b�_�̔��M���A�h���X�ƈ���A�h���X����ւ���B*/
	dst 	  = ip6h->dst;
	ip6h->dst = ip6h->src;
	ip6h->src = dst;

	/*
	 *  ���̈���A�h���X���}���`�L���X�g�̏ꍇ�́A
	 *  ����A�h���X�ɂӂ��킵�����M���A�h���X���A
	 *  �l�b�g���[�N�C���^�t�F�[�X����T�����ė��p����B
	 */
	if (IN6_IS_ADDR_MULTICAST(&dst)) {
		if ((ia = in6_ifawithifp(ifp, &ip6h->dst)) == NULL) {
			syscall(rel_net_buf(input));
			return;
			}
		else
			ip6h->src = ia->addr;
		}

	/* ���w�b�_�ƃz�b�v���~�b�g��ݒ肷��B*/
	ip6h->next = IPPROTO_ICMPV6;
	ip6h->hlim = IP_DEFTTL;

	/* �`�F�b�N�T�����v�Z����B*/
	icmp6h->sum = 0;
	icmp6h->sum = in6_cksum(input, IPPROTO_ICMPV6, (uint8_t*)icmp6h - input->buf, 
	                        ntohs(ip6h->plen) - (off - IF_IP6_HDR_SIZE));

	/* ���M����B*/
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_OCTETS],
	               input->len - GET_IF_IP6_HDR_SIZE(input));
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_OUT_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutEchoReplies, 1);
	ip6_output(input, 0, TMO_ICMP_OUTPUT);
	}

/*
 *  icmp6_notify_error -- �G���[��ʒm����B
 */

static void
icmp6_notify_error(T_NET_BUF *input, uint_t poff)
{
	T_ICMP6_HDR	*icmp6h;
	ER_UINT		loff;
	uint_t		len, next;

	len  = input->len - poff;

	/* �f�[�^�O�������� ICMP6 �w�b�_�� + IP6 �w�b�_���ȉ��Ȃ牽�����Ȃ��B*/
	if (len < ICMP6_HDR_SIZE + IP6_HDR_SIZE)
		return;

	icmp6h = GET_ICMP6_HDR(input, poff);

	/* �ŏI�w�b�_��T������B*/
	loff = ip6_lasthdr(input, poff + ICMP6_HDR_SIZE, IPPROTO_IPV6, &next);

	/* �ŏI�w�b�_�� TCP �̂ݑΉ�����B*/
	if (loff >= 0 && next == IPPROTO_TCP) {

#ifdef SUPPORT_TCP

		memcpy(GET_IP6_HDR(input), input->buf + (loff + ICMP6_HDR_SIZE),
		                           input->len - (loff + ICMP6_HDR_SIZE));
		input->len -= loff + ICMP6_HDR_SIZE;
		tcp_notify(input, icmp6h->code == ICMP6_DST_UNREACH_NOPORT ? EV_CNNRF : EV_HURCH);

#endif	/* of #ifdef SUPPORT_TCP */

		}
	else
		syslog(LOG_NOTICE, "[ICMP6] error code: %d.", icmp6h->code);
	}

#if NUM_IN6_HOSTCACHE_ENTRY > 0

/*
 *  icmp6_mtudisc_update -- Path MTU ���X�V����B
 */

static void
icmp6_mtudisc_update(T_NET_BUF *input, uint_t off, uint32_t mtu)
{
	T_IP6_HDR	*pip6h;

	pip6h = (T_IP6_HDR*)GET_ICMP6_SDU(input, off);

	if (mtu < IP6_HDR_SIZE + sizeof(T_IP6_FRAG_HDR) + 8)
		return;

	if (mtu > IF_MTU)
		return;

	in6_hostcache_update(&pip6h->dst, mtu);
	}

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  icmp6_redirect_input -- �����������b�Z�[�W�̏���
 */

static void
icmp6_redirect_input (T_NET_BUF *input, uint_t off)
{
	T_IP6_HDR		*ip6h;
	T_IN6_ADDR		*gw;
	T_ND_REDIRECT_HDR	*rdh;
	T_ND_OPT_HDR		*opth;
	T_IFNET			*ifp = IF_GET_IFNET();
	bool_t			router, onlink;
	uint_t			lladdr_len = 0;
	uint8_t			*lladdr = NULL;
	uint8_t			nd_opt_off[ND_OPT_OFF_ARRAY_SIZE];

	ip6h = GET_IP6_HDR(input);

	/*
	 *  IP �w�b�_�̃`�F�b�N�A�ȉ��̏ꍇ�͔j������B
	 *    �E�����N���[�J���ȊO���瑗���Ă������b�Z�[�W
	 *    �E�z�b�v���~�b�g�� IPV6_MAXHLIM (255) �ȊO
	 */
	if (!IN6_IS_ADDR_LINKLOCAL(&ip6h->src) || ip6h->hlim != IPV6_MAXHLIM)
		goto err_ret;

	rdh  = (T_ND_REDIRECT_HDR *)(input->buf + off);

	/* ���������̏I�_�A�h���X���}���`�L���X�g�A�h���X�̏ꍇ�͔j������B*/
	if (IN6_IS_ADDR_MULTICAST(&rdh->dst))
		goto err_ret;

	/* �^�[�Q�b�g�A�h���X���o�H�\�ɓo�^����Ă��邩�`�F�b�N����B*/
	if ((gw = in6_rtalloc(ifp, &rdh->dst)) != NULL) {
		/* GW �A�h���X�Ƒ��M���A�h���X���قȂ��Ă���Δj������B*/
		if (!IN6_ARE_ADDR_EQUAL(gw, &ip6h->src))
			goto err_ret;
		}
	else	/* �o�H�\�ɂȂ���Δj������B*/
		goto err_ret;

	router = onlink = false;

	/*
	 *  �^�[�Q�b�g�A�h���X�������N���[�J���A�h���X�ł���΁A
	 *  �^�[�Q�b�g�̓��[�^
	 */
	if (IN6_IS_ADDR_LINKLOCAL(&rdh->target))
		router = true;

	/*
	 *  �^�[�Q�b�g�A�h���X�ƏI�_�A�h���X������ł���΁A�I�������N
	 */
	if (IN6_ARE_ADDR_EQUAL(&rdh->target, &rdh->dst))
		onlink = true;
		
	/*
	 *  ���[�^�ł��A�I�������N�ł��Ȃ���΃G���[
	 */
	if (!router && !onlink)
		goto err_ret;

	/* �ߗגT���I�v�V�����̃I�t�Z�b�g���L�^����B*/
	if (nd6_options(nd_opt_off, input->buf +  off + ND_REDIRECT_HDR_SIZE,
	                            input->len - (off + ND_REDIRECT_HDR_SIZE)) != E_OK)
		goto err_ret;

	/* �ߗגT���I�v�V���� (���������̃��[�^�̃����N�A�h���X) */
	if (nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)]) {
		opth = (T_ND_OPT_HDR *)((uint8_t *)(input->buf + off + ND_REDIRECT_HDR_SIZE) +
		                        nd_opt_off[ND_OPT_OFF_ARRAY_IX(ND_OPT_TARGET_LINKADDR)] - 8);
	 	/* ����: �I�v�V�����I�t�Z�b�g�z��ɂ́A�I�t�Z�b�g + 8 ���ݒ肳��Ă���B*/
		lladdr     = (uint8_t *)(opth + 1);
		lladdr_len = (opth->len << 3);
		}

	/*
	 *  �l�b�g���[�N�C���^�t�F�[�X�̃A�h���X������v���Ȃ���΃G���[
	 */
	if (lladdr && lladdr_len != ((sizeof(T_IF_ADDR) + sizeof(T_ND_OPT_HDR) + 7) & ~7))
		goto err_ret;

	/* ���������̃��[�^�̃����N�A�h���X���ߗ׃L���b�V���ɓo�^����B*/
	nd6_cache_lladdr(ifp, &rdh->target, (T_IF_ADDR *)lladdr, ND_REDIRECT, 
	                 onlink ? ND_REDIRECT_ONLINK : ND_REDIRECT_ROUTER);

	/* ���[�e�B���O�\�ɓo�^����B*/
	in6_rtredirect(&rdh->target, &rdh->dst, 128, IN_RTF_REDIRECT, TMO_IN_REDIRECT);

	syscall(rel_net_buf(input));
	return;

err_ret:
	NET_COUNT_ICMP6(net_count_nd6[NC_ICMP6_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

/*
 *  icmp6_input -- ICMP6 �̓��͊֐�
 */

uint_t
icmp6_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp)
{
	T_NET_BUF	*input = *inputp;
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;
	uint_t		len, off = *offp;
	uint8_t		code;

	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_OCTETS],
	               input->len - GET_IF_IP6_HDR_SIZE(input));
	NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_PACKETS], 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInMsgs, 1);

	/* ICMP6 �w�b�_�̒������`�F�b�N����B*/
	len  = input->len - off;
	if (len < ICMP6_HDR_SIZE) {
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInErrors, 1);
		goto buf_rel;
		}

	ip6h   = GET_IP6_HDR(input);
	icmp6h = GET_ICMP6_HDR(input, off);

	/* �`�F�b�N�T�����v�Z����B*/
	if ((in6_cksum(input, IPPROTO_ICMPV6, off, ntohs(ip6h->plen) - (off - IF_IP_HDR_SIZE)) & 0xffff) != 0) {
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInErrors, 1);
		goto buf_rel;
		}

	code = icmp6h->code;

	/* ���b�Z�[�W�̌^�ɂ�蕪�򂷂�B*/
	switch (icmp6h->type) {

	case ICMP6_DST_UNREACH:			/* ���擞�B�s�\		*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInDestUnreachs, 1);
		icmp6_notify_error(input, off);
		break;

	case ICMP6_ECHO_REQUEST:		/* �G�R�[�v��			*/
		icmp6_echo_request(input, off);
		return IPPROTO_DONE;
		break;

	case ICMP6_ECHO_REPLY:			/* �G�R�[����			*/

#ifdef ICMP_CFG_CALLBACK_ECHO_REPLY

		icmp6_echo_reply(input, off);

#endif	/* of #ifdef ICMP_CFG_CALLBACK_ECHO_REPLY */

		break;

	case ND_ROUTER_ADVERT:			/* ���[�^�ʒm			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInRouterAdvertisements, 1);
		if (code != 0 || len < ROUTER_ADVERT_HDR_SIZE)
			goto buf_rel;
		nd6_ra_input(input, off);
		return IPPROTO_DONE;
		break;

	case ND_NEIGHBOR_SOLICIT:		/* �ߗחv��			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInNeighborSolicits, 1);
		if (code != 0 || len < NEIGHBOR_SOLICIT_HDR_SIZE)
			goto buf_rel;
		nd6_ns_input(input, off);
		return IPPROTO_DONE;
		break;

	case ND_NEIGHBOR_ADVERT:		/* �ߗגʒm			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInNeighborAdvertisements, 1);
		if (code != 0 || len < NEIGHBOR_ADVERT_HDR_SIZE)
			goto buf_rel;
		nd6_na_input(input, off);
		return IPPROTO_DONE;
		break;

	case ND_REDIRECT:			/* ��������			*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInRedirects, 1);

#if NUM_REDIRECT_ROUTE_ENTRY > 0

		if (code != 0 || len < ND_REDIRECT_HDR_SIZE)
			goto buf_rel;
		icmp6_redirect_input(input, off);
		return IPPROTO_DONE;

#else	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		syslog(LOG_WARNING, "[ICMP6] redirect ignored.");

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

		break;

	case ICMP6_PACKET_TOO_BIG:		/* �p�P�b�g���傫������B	*/

#if NUM_IN6_HOSTCACHE_ENTRY > 0

		icmp6_mtudisc_update(input, off, ntohl(icmp6h->icmp6_mtu));

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInPktTooBigs, 1);
		break;

	case ICMP6_TIME_EXCEEDED:		/* TTL �𒴉߂����B		*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInTimeExcds, 1);
		break;

	case ICMP6_PARAM_PROB:			/* IPv6 �w�b�_���s���B		*/
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInParmProblems, 1);
		break;

	case MLD_LISTENER_QUERY:		/* �}���`�L���X�g��M�ҏƉ�	*/
	case MLD_LISTENER_REPORT:		/* �}���`�L���X�g��M�ҕ�	*/
	case MLD_LISTENER_DONE:			/* �}���`�L���X�g��M�ҏI��	*/
	case ND_ROUTER_SOLICIT:			/* ���[�^�v��			*/
	case ICMP6_ROUTER_RENUMBERING:		/* ���[�^�ԍ��Đݒ�		*/
	case ICMP6_FQDN_QUERY:			/* FQDN �Ɖ�			*/
	case ICMP6_FQDN_REPLY:			/* FQDN ����			*/
		syslog(LOG_WARNING, "[ICMP6] unsupported type: %d.", icmp6h->type);
		break;

	default:
		syslog(LOG_WARNING, "[ICMP6] unknown type: %d.", icmp6h->type);
		NET_COUNT_ICMP6(net_count_icmp6[NC_ICMP6_IN_ERR_PACKETS], 1);
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpInErrors, 1);
		break;
		}

buf_rel:
	syscall(rel_net_buf(input));
	return IPPROTO_DONE;
	}

/*
 *  icmp6_error -- ICMP6 �G���[���M�֐�
 */

void
icmp6_error (T_NET_BUF *input, uint8_t type, uint8_t code, uint32_t param)
{
	T_NET_BUF	*output;
	T_IP6_HDR	*ip6h;
	T_ICMP6_HDR	*icmp6h;
	ER_UINT		off;
	uint_t		next, len;

	ip6h = GET_IP6_HDR(input);

	/*
	 *  ����A�h���X���A�}���`�L���X�g�̏ꍇ�́A
	 *  �ȉ��̏����ȊO�̂Ƃ��͏������s��Ȃ��B
	 *
	 *    �E�f�[�^�O�������傫������B
	 *    �EIPv6 �w�b�_�̕s���ŁA�I�v�V�������F���ł��Ȃ��B
	 */
	if (IN6_IS_ADDR_MULTICAST(&ip6h->dst) &&
	    !((type == ICMP6_PACKET_TOO_BIG) ||
	      (type == ICMP6_PARAM_PROB && code == ICMP6_PARAMPROB_OPTION)))
		goto buf_rel;

	/*
	 *  �n�_�A�h���X���A�ȉ��̏ꍇ�͏������s��Ȃ��B
	 *
	 *    �E���w��
	 *    �E�}���`�L���X�g
	 */
	if (IN6_IS_ADDR_UNSPECIFIED(&ip6h->src) ||
	    IN6_IS_ADDR_MULTICAST  (&ip6h->src))
		goto buf_rel;

	/* �Ō�̃w�b�_��T������B*/
	off = ip6_lasthdr(input, 0, IPPROTO_IPV6, &next);

	/*
	 *  �^�C�v���A�G���[������������ ICMP6 �p�P�b�g�̃G���[�ɂ͕ԓ����Ȃ��B
	 */
	if (off >= 0 && next == IPPROTO_ICMPV6) {
		T_ICMP6_HDR	*icmp6h;

		if (input->len - off < ICMP6_HDR_SIZE)
			goto buf_rel;

		icmp6h = GET_ICMP6_HDR(input, off);
		if (icmp6h->type <  ICMP6_ECHO_REQUEST ||
		    icmp6h->type == ND_REDIRECT)
			goto buf_rel;
		}

	/* DoS �U���ɑ΂���h��͖����� */

	/*
	 *  ����Ԃ����b�Z�[�W�����AICMPv6 �̍ő�y�C���[�h���ɒ�������B
	 *  IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE)
	 */
	if (input->len - IF_HDR_SIZE > IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE))
		len = IPV6_MMTU - (IP6_HDR_SIZE + ICMP6_HDR_SIZE);
	else
		len = input->len - IF_HDR_SIZE;

	/* ���M�p�̃l�b�g���[�N�o�b�t�@���l������B*/
	if (in6_get_datagram(&output, len + ICMP6_HDR_SIZE, 0,
	                     &ip6h->src, &in6_addr_unspecified,
	                     IPPROTO_ICMPV6, IPV6_MAXHLIM,
	                     NBA_SEARCH_ASCENT, TMO_ICMP_OUTPUT) != E_OK)
		goto buf_rel;

	/* ICMP6 �w�b�_��ݒ肷��B*/
 	icmp6h = GET_ICMP6_HDR(output, IF_IP6_ICMP6_HDR_OFFSET);
 	icmp6h->type       = type;
 	icmp6h->code       = code;
 	icmp6h->icmp6_pptr = htonl(param);
 
 	/* �G���[�f�[�^��ݒ肷��B*/
 	memcpy(GET_ICMP6_SDU(output, IF_IP6_ICMP6_HDR_OFFSET), (uint8_t *)ip6h, len);

#ifdef SUPPORT_MIB

	switch (type) {
	case ICMP6_DST_UNREACH:
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutDestUnreachs, 1);
		break;

	case ICMP6_PARAM_PROB:
		NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutParmProblems, 1);
		break;

	default:
		break;

		}

#endif	/* of #ifdef SUPPORT_MIB */

	/* ���M����B*/
	icmp6_output(output, IF_IP6_HDR_SIZE);

buf_rel:
	syscall(rel_net_buf(input));
	}

#endif /* of #ifdef SUPPORT_INET6 */
