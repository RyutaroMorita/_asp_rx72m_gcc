/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次の条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: udp_output.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993, 1995
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
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet6/in6.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/nd6.h>
#include <netinet/icmp6.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

#ifdef SUPPORT_UDP

#ifdef UDP_CFG_NON_BLOCKING

/*
 *  関数
 */

static void udp_output (T_UDP_CEP *cep);

/*
 *  UDP 出力タスク
 *  ノンブロッキングコールを組み込んだとき使用する。
 */

static void
udp_output (T_UDP_CEP *cep)
{
	T_NET_BUF	*output;
	T_UDP_HDR	*udph;
	ER_UINT		error;

#ifdef UDP_CFG_OUT_CHECKSUM
	uint16_t	sum;
#endif	/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	/* IP データグラムを割り当てる。*/
	if ((error = IN_GET_DATAGRAM(&output, (uint_t)(UDP_HDR_SIZE + cep->snd_len), 0,
	                             &cep->snd_p_dstaddr->ipaddr,
	                             &cep->myaddr.ipaddr,
	                             IPPROTO_UDP, IP_DEFTTL, 
	                             NBA_SEARCH_ASCENT, TMO_UDP_OUTPUT)) != E_OK) {
		goto err_ret;
		}

	/* UDP ヘッダに情報を設定する。*/
	udph		= GET_UDP_HDR(output, IF_IP_UDP_HDR_OFFSET);
	udph->sport	= htons(cep->myaddr.portno);
	udph->dport	= htons(cep->snd_p_dstaddr->portno);
	udph->ulen	= htons(UDP_HDR_SIZE + cep->snd_len);
	udph->sum	= 0;

	/* データをコピーする。*/
	memcpy((void*)GET_UDP_SDU(output, IF_IP_UDP_HDR_OFFSET),
	       cep->snd_data, (size_t)cep->snd_len);

#ifdef UDP_CFG_OUT_CHECKSUM

	sum = IN_CKSUM(output, IPPROTO_UDP, IF_IP_UDP_HDR_OFFSET,
	               (uint_t)(UDP_HDR_SIZE + cep->snd_len));

	/* 計算したチェックサムの値が 0 なら 0xffff を入れる。*/
	if (sum == 0)
		sum = UINT_C(0xffff);
	udph->sum = sum;

#endif/* of #ifdef UDP_CFG_OUT_CHECKSUM */

	/* ネットワークバッファ長を調整する。*/
	output->len = (uint16_t)(IF_IP_UDP_HDR_SIZE + cep->snd_len);

	/* ネットワーク層 (IP) の出力関数を呼び出す。*/
	if ((error = IP_OUTPUT(output, TMO_UDP_OUTPUT)) != E_OK)
		goto err_ret;


	NET_COUNT_MIB(udp_stats.udpOutDatagrams, 1);

	if (IS_PTR_DEFINED(cep->callback)) {

		if (error == E_OK)
			error = cep->snd_len;

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		}
	else
		syslog(LOG_WARNING, "[UDP] no call back, CEP: %d.", GET_UDP_CEPID(cep));
	cep->snd_p_dstaddr = NULL;
	return;

err_ret:
	NET_COUNT_UDP(net_count_udp.out_err_packets, 1);
	if (IS_PTR_DEFINED(cep->callback)) {

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)E_NOMEM);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		error = E_NOMEM;
		(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		}
	else
		syslog(LOG_WARNING, "[UDP] no call back, CEP: %d.", GET_UDP_CEPID(cep));
	cep->snd_p_dstaddr = NULL;
	return;
	}

/*
 *  UDP 出力タスク
 *  ノンブロッキングコールを組み込んだとき使用する。
 */

void
udp_output_task (intptr_t exinf)
{
	ID	tskid;
	int_t	ix;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP OUTPUT:%d] started.", tskid);


#if defined(SUPPORT_INET6) && !defined(SUPPORT_TCP)

	/* IPv6 のステートレス・アドレス自動設定を実行する。*/
	in6_if_up(IF_GET_IFNET());

#endif	/* of #if defined(SUPPORT_INET6) && !defined(SUPPORT_TCP) */

	while (true) {

		/* 出力がポストされるまで待つ。*/
		syscall(wai_sem(SEM_UDP_POST_OUTPUT));

		for (ix = tmax_udp_ccepid; ix -- > 0; ) {

			if (udp_cep[ix].flags & UDP_CEP_FLG_POST_OUTPUT) {
				udp_cep[ix].flags &= ~UDP_CEP_FLG_POST_OUTPUT;
				udp_output(&udp_cep[ix]);
				}
			}
		}
	}

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#endif	/* of #ifdef SUPPORT_UDP */
