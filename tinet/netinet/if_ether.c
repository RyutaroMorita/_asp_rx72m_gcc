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
 *  @(#) $Id: if_ether.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 *	@(#)if_ether.c	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/if_ether.c,v 1.52.2.6 1999/10/18 11:59:31 sheldonh Exp $
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
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_var.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

#include <net/if_var.h>

#if defined(SUPPORT_INET4) && defined(SUPPORT_ETHER)

/*
 *  ARP �L���b�V���G���g��
 */

static T_ARP_ENTRY arp_cache[NUM_ARP_ENTRY];

/*
 *  �֐�
 */

static T_ARP_ENTRY *arp_lookup (T_IN4_ADDR addr, bool_t create);
static void in_arpinput (T_IF_ADDR *ifaddr, T_NET_BUF *input);
static void arp_timer (void *ignore);

/*
 *  arp_lookup -- ARP �L���b�V���̒T���Ɠo�^
 *
 *    ����: SEM_ARP_CACHE_LOCK ���l��������ԂŌďo������
 */

static T_ARP_ENTRY *
arp_lookup (T_IN4_ADDR addr, bool_t create)
{
	int_t		ix, six;
	uint16_t	min;

	for (ix = NUM_ARP_ENTRY; ix -- > 0; ) {
		if (arp_cache[ix].expire && arp_cache[ix].ip_addr == addr)
			return &arp_cache[ix];
		}

	/* create ���^�Ȃ�A�V���ȃG���g����o�^����B*/
	if (create) {

		/* �܂��A�󂫂�����΁A���̋󂫂𗘗p����B*/
		for (ix = NUM_ARP_ENTRY; ix -- > 0; ) {
			if (arp_cache[ix].expire == 0) {
				arp_cache[ix].ip_addr = addr;
				return &arp_cache[ix];
				}
			}

		/*
		 *  �󂫂��Ȃ���΁A�^�C���A�E�g�܂Ŏ��Ԃ��ŒZ��
		 *  �G���g���[��j�����ė��p����B
		 */
		syslog(LOG_NOTICE, "[ARP] cache busy, size=%d", NUM_ARP_ENTRY);
		min = 0xffff;
		for (six = ix = NUM_ARP_ENTRY; ix -- > 0; )
			if (arp_cache[ix].expire < min) {
				six = ix;
				min = arp_cache[ix].expire;
				}
		arp_cache[six].expire  = 0;
		arp_cache[six].ip_addr = addr;
		return &arp_cache[six];
		}
	else
		return NULL;
	}

/*
 *  in_arpinput -- TCP/IP �p ARP �̓��͊֐�
 */

static void
in_arpinput (T_IF_ADDR *ifaddr, T_NET_BUF *input)
{
	T_NET_BUF	*pending;
	T_ETHER_HDR	*eth;
	T_ARP_HDR	*arph;
	T_ETHER_ARP_HDR	*et_arph;
	T_ARP_ENTRY	*ent;
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IN4_ADDR	saddr, taddr;

	et_arph = GET_ETHER_ARP_HDR(input);

	ntoahl(saddr, et_arph->sproto);		/* ���M�� IP �A�h���X	*/
	ntoahl(taddr, et_arph->tproto);		/* �����Ώ� IP �A�h���X	*/

	/*
	 *  �ȉ��̏ꍇ�̓G���[
	 *    �E���M�z�X�g�̕����A�h���X������
	 *    �E���M�z�X�g�̕����A�h���X���u���[�h�L���X�g
	 */
	if (memcmp(et_arph->shost, ifaddr->lladdr,        ETHER_ADDR_LEN) == 0 ||
	    memcmp(et_arph->shost, ether_broad_cast_addr, ETHER_ADDR_LEN) == 0)
		goto err_ret;

	/*
	 *  ���M�z�X�g�� IP �A�h���X�������̏ꍇ�́A�d�����Ă���̂�
	 *  ����ɂ��m�点��B
	 */
	if (saddr == ifp->in_ifaddr.addr) {

#ifdef ARP_CFG_CALLBACK_DUPLICATED

		if (arp_callback_duplicated(et_arph->shost)) {
			syslog(LOG_ERROR, "[ARP] IP address duplicated: %s", mac2str(NULL, et_arph->shost));
			taddr = saddr;
			goto reply;
			}
		else
			goto buf_rel;

#else	/* of #ifdef ARP_CFG_CALLBACK_DUPLICATED */

		syslog(LOG_ERROR, "[ARP] IP address duplicated: %s", mac2str(NULL, et_arph->shost));
		taddr = saddr;
		goto reply;

#endif	/* of #ifdef ARP_CFG_CALLBACK_DUPLICATED */

		}

	/*
	 *  �ȉ��̏ꍇ�͉������Ȃ��B
	 *    �E�����Ώ� IP �A�h���X�������ł͂Ȃ��A��: ���� FreeBSD ��
	 *      �����ł́AARP PROXY ���̂��߁A�����ȊO�� IP �A�h���X��
	 *      �������s���Ă��邪�A�{�����ł́A�����ȊO�� IP
	 *      �A�h���X�̉����͍s��Ȃ��B
	 */
	if (taddr != ifp->in_ifaddr.addr)
		goto buf_rel;

	/*
	 *  ���M�� IP �A�h���X�� ARP �L���b�V���ɂ��邩���ׂ�B
	 *  �L���b�V���ɂȂ���΁A�V���ɃG���g����o�^����B
	 */
	syscall(wai_sem(SEM_ARP_CACHE_LOCK));
	ent = arp_lookup(saddr, true);

	memcpy(ent->mac_addr, et_arph->shost, ETHER_ADDR_LEN);
	ent->expire = ARP_CACHE_KEEP;

	/*
	 *  ���M���y���f���O����Ă���t���[��������Α��M����B
	 */
	if (ent->hold) {

		/* �t���[���� Ethernet �w�b�_��ݒ肷��B*/
		memcpy(GET_ETHER_HDR(ent->hold)->dhost, ent->mac_addr, ETHER_ADDR_LEN);

		pending = ent->hold;
		ent->hold = NULL;
		syscall(sig_sem(SEM_ARP_CACHE_LOCK));

		/* �y���f�B���O����Ă���t���[���𑗐M����B*/
		IF_RAW_OUTPUT(pending, TMO_FEVR);

		}
	else
		syscall(sig_sem(SEM_ARP_CACHE_LOCK));

reply:

	arph = GET_ARP_HDR(input);

	/* �A�h���X�����v���łȂ���ΏI�� */
	if (ntohs(arph->opcode) != ARPOP_REQUEST)
		goto buf_rel;

	/* Ethernet ARP �w�b�_��ݒ肷��B*/
	memcpy(et_arph->thost, et_arph->shost, ETHER_ADDR_LEN);
	memcpy(et_arph->shost, ifaddr->lladdr, ETHER_ADDR_LEN);
	memcpy(et_arph->tproto, (uint8_t*)&et_arph->sproto, sizeof(T_IN_ADDR));
	ahtonl(et_arph->sproto, taddr);

	/* Ethernet ARP �w�b�_��ݒ肷��B*/
	arph->opcode = htons(ARPOP_REPLY);

	/* Ethernet �w�b�_��ݒ肷��B*/
	eth = GET_ETHER_HDR(input);
	memcpy(eth->dhost, eth->shost,     ETHER_ADDR_LEN);
	memcpy(eth->shost, ifaddr->lladdr, ETHER_ADDR_LEN);

	/* ARP �����𑗐M����B*/
	IF_RAW_OUTPUT(input, TMO_FEVR);
	return;

err_ret:
	NET_COUNT_ARP(net_count_arp.in_err_packets, 1);
buf_rel:
	syscall(rel_net_buf(input));
	}

/*
 *  arp_timer -- ARP �L���b�V���̍X�V
 */

static void
arp_timer (void *ignore)
{
	int_t	ix;

	syscall(wai_sem(SEM_ARP_CACHE_LOCK));

	for (ix = NUM_ARP_ENTRY; ix -- > 0; ) {
		if (arp_cache[ix].expire) {
			arp_cache[ix].expire -= ARP_TIMER_TMO;
			if (arp_cache[ix].expire == 0) {
				/* ���M���y���f���O����Ă���t���[��������Ύ̂Ă�B*/
				if (arp_cache[ix].hold) {
					NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
					syscall(rel_net_buf(arp_cache[ix].hold));
					}
				memset(&arp_cache[ix], 0, sizeof(T_ARP_ENTRY));
				}
			}
		}

	syscall(sig_sem(SEM_ARP_CACHE_LOCK));
	timeout(arp_timer, NULL, ARP_TIMER_TMO);
	}

/*
 *  arp_request -- MAC �A�h���X�����v��
 */

ER
arp_request (T_IF_ADDR *ifaddr, T_IN4_ADDR dst)
{
	ER		error;
	T_IN4_ADDR	src;
	T_ETHER_HDR	*eth;
	T_ARP_HDR	*arph;
	T_ETHER_ARP_HDR	*et_arph;
	T_NET_BUF	*arp_req;

	NET_COUNT_ARP(net_count_arp.out_octets , IF_ARP_ETHER_HDR_SIZE - IF_HDR_SIZE);
	NET_COUNT_ARP(net_count_arp.out_packets, 1);

	if ((error = tget_net_buf(&arp_req, IF_ARP_ETHER_HDR_SIZE, TMO_ARP_GET_NET_BUF)) == E_OK) {

		/* �C�[�T�l�b�g�w�b�_��ݒ肷��B*/
		eth     = GET_ETHER_HDR(arp_req);
		memcpy(eth->dhost, ether_broad_cast_addr, ETHER_ADDR_LEN);
		memcpy(eth->shost, ifaddr->lladdr,        ETHER_ADDR_LEN);
		eth->type = htons(ETHER_TYPE_ARP);

		/* ARP �w�b�_��ݒ肷��B*/
		arph    = GET_ARP_HDR(arp_req);
		arph->hrd_addr  = htons(ARPHRD_ETHER);
		arph->proto     = htons(ETHER_TYPE_IP);
		arph->hdr_len   = sizeof(et_arph->shost);
		arph->proto_len = sizeof(et_arph->sproto);
		arph->opcode    = htons(ARPOP_REQUEST);

		/* �C�[�T�l�b�g ARP �w�b�_��ݒ肷��B*/
		et_arph = GET_ETHER_ARP_HDR(arp_req);
		src     = IF_GET_IFNET()->in_ifaddr.addr;
		memcpy(et_arph->shost, ifaddr->lladdr, ETHER_ADDR_LEN);
		memset(et_arph->thost, 0,              ETHER_ADDR_LEN);
		ahtonl(et_arph->sproto, src);
		ahtonl(et_arph->tproto, dst);

		/* ���M����B*/
		error = IF_RAW_OUTPUT(arp_req, TMO_ARP_OUTPUT);
		}
	if (error != E_OK)
		NET_COUNT_ARP(net_count_arp.out_err_packets, 1);
	return error;
	}

/*
 *  arp_get_cache -- ARP �L���b�V�����l������B
 */

const T_ARP_ENTRY *
arp_get_cache (void)
{
	return arp_cache;
	}

/*
 *  arp_input -- ARP �̓��͊֐�
 */

void
arp_input (T_IF_ADDR *ifaddr, T_NET_BUF *input)
{
	T_ARP_HDR	*arph;

	NET_COUNT_ARP(net_count_arp.in_octets , input->len - IF_HDR_SIZE);
	NET_COUNT_ARP(net_count_arp.in_packets, 1);

	/* ARP �w�b�_�̒������`�F�b�N����B*/
	if (input->len < IF_ARP_HDR_SIZE)
		goto buf_rel;

	arph = GET_ARP_HDR(input);

	/*
	 *  �����A�h���X�t�H�[�}�b�g�� Ehternet �ȊO
	 *  �܂��́A�v���g�R���� IP �ȊO�̓G���[�B
	 */
	if (ntohs(arph->hrd_addr) != ARPHRD_ETHER ||
	    ntohs(arph->proto)    != ETHER_TYPE_IP)
		goto buf_rel;

	/* ARP �w�b�_ + Ether ARP �w�b�_�̒������`�F�b�N����B*/
	if (input->len < IF_ARP_ETHER_HDR_SIZE)
		goto buf_rel;

	in_arpinput(ifaddr, input);
	return;

buf_rel:
	NET_COUNT_ARP(net_count_arp.in_err_packets, 1);
	syscall(rel_net_buf(input));
	}

/*
 *  arp_resolve -- MAC �A�h���X����
 *
 *    �A�h���X�������ł���΁A�߂�l�� true ��Ԃ��A�ł��Ȃ����
 *    ���M���y���f�B���O���āA�߂�l�� false ��Ԃ��B
 */

bool_t
arp_resolve (T_IF_ADDR *ifaddr, T_NET_BUF *output, T_IN4_ADDR gw)
{
	T_ARP_ENTRY	*ent;
	T_ETHER_HDR	*eth;
	T_IFNET		*ifp = IF_GET_IFNET();

	eth = GET_ETHER_HDR(output);

	/*
	 *  ���̏ꍇ�́A�C�[�T�l�b�g�̃u���[�h�L���X�g�A�h���X��Ԃ��B
	 *
	 *    �E�S�r�b�g�� 1
	 *    �E�z�X�g���̑S�r�b�g�� 1 �ŁA�l�b�g���[�N�������[�J���A�h���X
	 */
	if (gw == IPV4_ADDR_BROADCAST ||
	    gw == ((ifp->in_ifaddr.addr & ifp->in_ifaddr.mask) | ~ifp->in_ifaddr.mask)) {
		memcpy(eth->dhost, ether_broad_cast_addr, ETHER_ADDR_LEN);
		return true;
		}

	/* ���M�� GW �� IP �A�h���X�� ARP �L���b�V���ɂ��邩���ׂ�B*/
	syscall(wai_sem(SEM_ARP_CACHE_LOCK));
	ent = arp_lookup(gw, true);
	if (ent->expire) {
		memcpy(eth->dhost, ent->mac_addr, ETHER_ADDR_LEN);
		syscall(sig_sem(SEM_ARP_CACHE_LOCK));
		return true;
		}
	else {
	 	/* ���M���y���f���O����Ă���t���[��������Ύ̂Ă�B*/
		if (ent->hold) {
			NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
			syscall(rel_net_buf(ent->hold));
			}

		/*
		 *  ���M���y���f�B���O����B
		 *  IF �Ńl�b�g���[�N�o�b�t�@���J�����Ȃ��t���O���ݒ肳��Ă���Ƃ��́A
		 *  ���M���y���f�B���O���Ȃ��B
		 */
		if ((output->flags & NB_FLG_NOREL_IFOUT) == 0)
			ent->hold = output;
		else {
			output->flags &= (uint8_t)~NB_FLG_NOREL_IFOUT;
			ent->hold = NULL;
			}
		syscall(sig_sem(SEM_ARP_CACHE_LOCK));

		/* �A�h���X�����v���𑗐M����B*/
		arp_request(ifaddr, gw);
		return false;
		}
	}

/*
 *  arp_init -- ARP ������
 */

void
arp_init (void)
{
	timeout(arp_timer, NULL, ARP_TIMER_TMO);
	}

#endif	/* of #if defined(SUPPORT_INET4) && defined(SUPPORT_ETHER) */
