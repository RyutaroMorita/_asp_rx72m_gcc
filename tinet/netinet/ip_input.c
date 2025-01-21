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
 *  @(#) $Id: ip_input.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 *	@(#)input.c	8.2 (Berkeley) 1/4/94
 * $FreeBSD: src/sys/netinet/input.c,v 1.111.2.4 1999/11/01 22:23:53 des Exp $
 *	$ANA: input.c,v 1.5 1996/09/18 14:34:59 wollman Exp $
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
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

#if defined(SUPPORT_IPSEC)
//#include <stdio.h>
#include <sys/types.h>
#include <netinet6/ipsec.h>
#include <netinet6/esp.h>
#include <netkey/key.h>
#include <netkey/key_debug.h>
#endif /* of defined(SUPPORT_IPSEC) */

#include <net/if_var.h>

/*
 *  �ϐ�
 */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

T_IP_STATS ip_stats;

#endif	/* of #ifdef SUPPORT_MIB */

#ifdef IP4_CFG_FRAGMENT

/*
 *  �f�[�^�O�����č\���L���[
 */

static T_NET_BUF	*ip_frag_queue[NUM_IP4_FRAG_QUEUE];
static T_IN4_ADDR	    frag_dst  [NUM_IP4_FRAG_QUEUE];

/*
 *  �֐�
 */

static void ip_freef (int_t ix);
static T_NET_BUF *ip_reass (T_IP4_HDR *ip4h, T_NET_BUF *input);

/*
 *  ip_get_frag_queue -- �f�[�^�O�����č\���L���[���l������B
 */

const T_NET_BUF **
ip_get_frag_queue (void)
{
	return (const T_NET_BUF **)ip_frag_queue;
	}

/*
 *  ip_freef -- �f�[�^�O�����č\���L���[���������B
 */

static void
ip_freef (int_t ix)
{
	T_NET_BUF	*frag, *next;

	frag = ip_frag_queue[ix];
	while (frag != NULL) {
		next = GET_QIP4_HDR(frag)->next;
		syscall(rel_net_buf(frag));
		frag = next;
		}
	ip_frag_queue[ix] = NULL;
	}

/*
 *  ip_frag_timer -- �f�[�^�O�����č\���Ǘ��^�C�}
 */

void
ip_frag_timer (void)
{
	T_NET_BUF	*frag;
	int_t		ix;

	syscall(wai_sem(SEM_IP4_FRAG_QUEUE));
	for (ix = NUM_IP4_FRAG_QUEUE; ix -- > 0; ) {
		frag = ip_frag_queue[ix];
		if (frag != NULL && GET_QIP4_HDR(frag)->ttl > 0 &&
		    -- GET_QIP4_HDR(frag)->ttl == 0) {
			NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_TMOUT], 1);
			NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_DROP], 1);
			ip_freef(ix);
			}
		}
	syscall(sig_sem(SEM_IP4_FRAG_QUEUE));
	}

/*
 *  ip_reass -- �f�[�^�O�������č\������B
 */

static T_NET_BUF *
ip_reass (T_IP4_HDR *ip4h, T_NET_BUF *input)
{
	T_NET_BUF	*frag, *prev;
	T_IN4_ADDR	dst, src;
	int_t		ix;
	uint_t		id, off, len;

	NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_FRAGS], 1);
	NET_COUNT_MIB(ip_stats.ipReasmReqds, 1);

	src = ntohl(ip4h->src);
	dst = ntohl(ip4h->dst);
	NTOHS(ip4h->id);
	NTOHS(ip4h->flg_off);
	id = ip4h->id;
	ix = id % NUM_IP4_FRAG_QUEUE;

	syscall(wai_sem(SEM_IP4_FRAG_QUEUE));

	/*
	 *  ID�AIP�A�h���X�A��ʃv���g�R�����قȂ�t���O�����g���L���[�ɗL��Δj������B
	 */
	frag = ip_frag_queue[ix];
	if (frag != NULL &&
	    (id  != GET_IP4_HDR(frag)->id  ||
	     dst != frag_dst[ix] ||
	     src != ntohl(GET_IP4_HDR(frag)->src) ||
	     ip4h->proto != GET_IP4_HDR(frag)->proto)) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_DROP], 1);
		NET_COUNT_MIB(ip_stats.ipReasmFails, 1);
		ip_freef(ix);
		}

	frag = ip_frag_queue[ix];
	if (frag == NULL) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN], 1);

		/* �V�K�� ID �Ȃ�A����A�h���X��ۑ����āA�L���[�ɂȂ��B*/
		frag_dst  [ix] = dst;
		ip_frag_queue[ix] = input;
		((T_QIP4_HDR *)ip4h)->next = NULL;
		input = NULL;

		/* �č\���^�C���A�E�g��ݒ肷��B*/
		ip4h->ttl = IP4_FRAGTTL;
		}
	else {

		/* �������ʒu�ɑ}������B*/
		prev = NULL;
		while (frag != NULL &&
		       IP4_FLGOFF_OFF(ip4h->flg_off) >
		       IP4_FLGOFF_OFF(GET_QIP4_HDR(frag)->flg_off)) {
			prev = frag;
			frag = GET_QIP4_HDR(frag)->next;
			}
		((T_QIP4_HDR *)ip4h)->next = frag;
		if (prev == NULL) {
			ip4h->ttl      = GET_QIP4_HDR(frag)->ttl;
			ip_frag_queue[ix] = input;
			}
		else
			GET_QIP4_HDR(prev)->next = input;
		input = NULL;

		/* �S�Ẵt���O�����g�������Ă��邩���ׂ�B*/
		off = 0;
		for (frag = ip_frag_queue[ix]; frag != NULL; frag = GET_QIP4_HDR(frag)->next) {
			if ((IP4_FLGOFF_OFF(GET_QIP4_HDR(frag)->flg_off) << 3) != off) {
				/* �r���������Ă�����I������B*/
				syscall(sig_sem(SEM_IP4_FRAG_QUEUE));
				return NULL;
				}
			off += ntohs(GET_QIP4_HDR(frag)->len) - (IP4_VHL_HL(GET_QIP4_HDR(frag)->vhl) << 2);
			prev = frag;				
			}

		/* �S�Ẵt���O�����g����������č\������B*/
		if ((GET_QIP4_HDR(prev)->flg_off & IP4_MF) == 0) {

			/* �l�b�g���[�N�o�b�t�@���l������B*/
			if (tget_net_buf(&input, IF_IP4_HDR_SIZE + off, TMO_IP4_FRAG_GET_NET_BUF) == E_OK) {
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_OK], 1);
				NET_COUNT_MIB(ip_stats.ipReasmOKs, 1);

				/* IPv4 �w�b�_��ݒ肷��B*/
				frag  = ip_frag_queue[ix];
				ip4h  = GET_IP4_HDR(input);
				*ip4h = *GET_IP4_HDR(frag);
				ip4h->dst     = htonl(frag_dst[ix]);
				ip4h->len     = htons(IP4_HDR_SIZE + off);
				ip4h->vhl     = IP4_MAKE_VHL(IPV4_VERSION, IP4_HDR_SIZE >> 2);
				ip4h->ttl     = GET_QIP4_HDR(prev)->ttl;
				ip4h->flg_off = ip4h->id = 0;

				/* �f�[�^�O�������č\������B*/
				off = IP4_HDR_SIZE;
				while (frag != NULL) {
					len = ntohs(GET_QIP4_HDR(frag)->len) - (IP4_VHL_HL(GET_QIP4_HDR(frag)->vhl) << 2);
					memcpy((uint8_t *)ip4h + off, GET_QIP4_SDU(frag), len);
					off += len;
					frag = GET_QIP4_HDR(frag)->next;
					}
				}
			else {
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_NO_BUF], 1);
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_IN_DROP], 1);
				NET_COUNT_MIB(ip_stats.ipReasmFails, 1);
				}
			/* �L���[����ɂ���B*/
			ip_freef(ix);
			}
		}
	syscall(sig_sem(SEM_IP4_FRAG_QUEUE));
	return input;
	}

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

/*
 *  ip_init -- IP �̏�����
 */

void
ip_init (void)
{
	in4_init();
	}

/*
 *  ip_remove_options -- IPv4 �w�b�_�̃I�v�V�������폜���A�ȍ~��O�ɋl�߂�B
 */

ER
ip_remove_options (T_NET_BUF *nbuf)
{
	T_IP_HDR	*iph;

	iph  = GET_IP_HDR(nbuf);

	if (GET_IP_HDR_SIZE(iph) > IP4_HDR_SIZE) {
		memmove((char *)iph + IP4_HDR_SIZE, GET_IP_SDU(nbuf),
		        (size_t)(iph->len - GET_IP_HDR_SIZE(iph)));
		iph->vhl   = IP4_MAKE_VHL(IPV4_VERSION, IP4_HDR_SIZE >> 2);
		iph->len  -= (uint16_t)(GET_IP_HDR_SIZE(iph) - IP4_HDR_SIZE);
		nbuf->len -= (uint16_t)(GET_IP_HDR_SIZE(iph) - IP4_HDR_SIZE);
		}

	return E_OK;
	}

/*
 *  ip_input -- IP �̓��͊֐�
 */

#if defined(SUPPORT_IPSEC)
/*
 * TODO: IPsec SP���������A�p�P�b�g�����W�F�N�g���邩�ǂ������肷�鏈������������
 */
#endif /* of defined(SUPPORT_IPSEC) */

void
ip_input (T_NET_BUF *input)
{
	T_IP4_HDR	*ip4h;
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN4_ADDR	dst, src, bc;
	uint_t		hlen, off;

	NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_OCTETS], input->len - IF_HDR_SIZE);
	NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_PACKETS], 1);
	NET_COUNT_MIB(ip_stats.ipInReceives, 1);

	/* IP �w�b�_�̒������`�F�b�N����B*/
	if (input->len < IF_IP4_HDR_SIZE) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_SHORT], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	ip4h  = GET_IP4_HDR(input);
	hlen = GET_IP4_HDR_SIZE(ip4h);

	/* �o�[�W�������`�F�b�N����B*/
	if (IP4_VHL_V(ip4h->vhl) != IPV4_VERSION) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_VER], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	/* IP �w�b�_�̒������`�F�b�N���A�I�v�V��������͂���B*/
	if (hlen > IP4_HDR_SIZE) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_OPTS], 1);
		/* %%% �I�v�V�����̉�� %%% */
		}

	/* �f�[�^�O���������`�F�b�N����B*/
	if (ntohs(ip4h->len) > input->len - IF_HDR_SIZE) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_SHORT], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	/* �l�b�g���[�N�o�b�t�@�̒������f�[�^�O�������ɒ�������B*/
	input->len = (uint16_t)(ntohs(ip4h->len) + IF_HDR_SIZE);

	/* �`�F�b�N�T�����`�F�b�N����B*/
	if (in_cksum(ip4h, hlen) != 0) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_CKSUM], 1);
		NET_COUNT_MIB(ip_stats.ipInHdrErrors, 1);
		goto buf_rel;
		}

	/* IP �w�b�_�̒������`�F�b�N���A��ʂ� ICMP �ȊO�̓I�v�V��������������B*/
	if (hlen > IP4_HDR_SIZE && ip4h->proto != IPPROTO_ICMP) {
		memset((uint8_t*)ip4h + IP4_HDR_SIZE, 0, hlen - IP4_HDR_SIZE);
		}

	/* ���M���A�h���X���`�F�b�N����B*/
	src = ntohl(ip4h->src);
	bc  = (ifp->in_ifaddr.addr & ifp->in_ifaddr.mask) | ~ifp->in_ifaddr.mask;

#ifdef SUPPORT_LOOP

	if (src == bc || src == IPV4_ADDR_BROADCAST || src == IPV4_ADDRANY) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#else	/* of #ifdef SUPPORT_LOOP */

	if (src == ifp->in_ifaddr.addr || src == bc || src == IPV4_ADDR_BROADCAST || src == IPV4_ADDRANY) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#endif	/* of #ifdef SUPPORT_LOOP */

	/* ���Đ�A�h���X���`�F�b�N����B*/
	dst = ntohl(ip4h->dst);

#ifdef DHCP_CFG

	/*
	 *  DHCP_CFG ����`����Ă���Ƃ��́A���[�J���A�h���X������`��
	 *  �ꍇ���f�[�^�O��������M����B
	 */

	if ((ifp->in_ifaddr.addr != IPV4_ADDRANY) &&
	    (!(dst == ifp->in_ifaddr.addr || dst == bc ||
	       dst == IPV4_ADDR_BROADCAST || dst == IPV4_ADDRANY))) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#else	/* of #ifdef DHCP_CFG */

	if (!(dst == ifp->in_ifaddr.addr || dst == bc ||
	      dst == IPV4_ADDR_BROADCAST || dst == IPV4_ADDRANY)) {
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_ADDR], 1);
		NET_COUNT_MIB(ip_stats.ipInAddrErrors, 1);
		goto buf_rel;
		}

#endif	/* of #ifdef DHCP_CFG */

#ifdef IP4_CFG_FRAGMENT

	/* ��������Ă��邩�`�F�b�N����B*/
	if (ntohs(ip4h->flg_off) & (IP4_MF | IP4_OFFMASK)) {
		if ((input = ip_reass(ip4h, input)) == NULL)
			return;
		}

#else	/* of #ifdef IP4_CFG_FRAGMENT */

	/* ��������Ă��邩�`�F�b�N����B*/
	if (ntohs(ip4h->flg_off) & (IP4_MF | IP4_OFFMASK)) {
		T_IN4_ADDR	src;

		NET_COUNT_MIB(ip_stats.ipReasmReqds, 1);
		if ((ntohs(ip4h->flg_off) & IP4_OFFMASK) == 0) {
			NET_COUNT_MIB(ip_stats.ipReasmFails, 1);
			}
		src = ntohl(ip4h->src);
		syslog(LOG_WARNING, "[IP] flaged src: %s.", ip2str(NULL, &src));
		goto buf_rel;
		}

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

	off  = (uint_t)(GET_IP4_SDU(input) - input->buf);

#if defined(SUPPORT_IPSEC)
	/* ������ipsec4_in_reject�����s���� */
	if ((ip4h->proto != IPPROTO_ESP) && ipsec4_in_reject (input)) {
		goto buf_rel;
	}
#endif /* of #if defined(SUPPORT_IPSEC) */

	/* �v���g�R����I������ */
	switch (ip4h->proto) {

#ifdef SUPPORT_UDP
	case IPPROTO_UDP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		udp_input(&input, &off, NULL);
		return;
		break;
#endif	/* of #ifdef SUPPORT_UDP */

#ifdef SUPPORT_TCP
	case IPPROTO_TCP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		tcp_input(&input, &off, NULL);
		return;
		break;
#endif	/* of #ifdef SUPPORT_UDP */

	case IPPROTO_ICMP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		icmp_input(&input, &off, NULL);
		return;
		break;

#if defined(SUPPORT_IPSEC)
	case IPPROTO_ESP:
		NET_COUNT_MIB(ip_stats.ipInDelivers, 1);
		esp4_input(input, &off);
		return;
		break;
#endif /* of #if defined(SUPPORT_IPSEC) */

	default:
		NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_PROTO], 1);
		NET_COUNT_MIB(ip_stats.ipInUnknownProtos, 1);

		/* ���[�J�� IP �A�h���X�ɓ͂����f�[�^�O�����̂� ICMP �G���[��ʒm����B*/
		if (dst == ifp->in_ifaddr.addr) {
			T_IN4_ADDR	src;

			src = ntohl(ip4h->src);
			syslog(LOG_INFO, "[IP] unexp proto: %d, src=%s.", ip4h->proto, ip2str(NULL, &src));
			icmp_error(ICMP4_UNREACH_PROTOCOL, input);
			}
		/*
		 *  icmp_error �ł́A�l�b�g���[�N�o�b�t�@ input ��ԋp���Ȃ��̂�
		 *  �J�����Ă���I������B
		 */
		break;
		}

buf_rel:
	NET_COUNT_IP4(net_count_ip4[NC_IP4_IN_ERR_PACKETS], 1);
	syscall(rel_net_buf(input));
	}
