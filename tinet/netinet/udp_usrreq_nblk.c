/*
 *  TINET (UDP/IP Protocol Stack)
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
 *  @(#) $Id: udp_usrreq_nblk.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
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
 * 2. Redistributions in binary form must ceproduce the above copyright
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
 *	@(#)udp_usrreq.c	8.6 (Berkeley) 5/23/95
 * $FreeBSD: src/sys/netinet/udp_usrreq.c,v 1.49.2.2 1999/08/29 16:29:58 peter Exp $
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
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp_ipcp.h>

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

/*
 *  IPv4 と IPv6 の切り替えマクロ
 */

#if defined(SUPPORT_INET4)

#define UDP_SND_DAT	udp_snd_dat
#define UDP_RCV_DAT	udp_rcv_dat

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define UDP_SND_DAT	udp6_snd_dat
#define UDP_RCV_DAT	udp6_rcv_dat

#endif	/* of #if defined(SUPPORT_INET6) */

/*
 *  TINET をライブラリ化しない場合は、全ての機能を
 *  オブジェクトファイルに出力するため、マクロを有効にする。
 */

#ifndef UDP_CFG_LIBRARY

#define __udp_can_snd
#define __udp_can_rcv
#define __udp_snd_dat
#define __udp_rcv_dat

#endif	/* of #ifndef UDP_CFG_LIBRARY */

#ifdef UDP_CFG_NON_BLOCKING

#ifdef __udp_can_snd

/*
 *  udp_can_snd -- ペンディングしている送信のキャンセル
 */

ER
udp_can_snd (T_UDP_CEP *cep, ER error)
{
	if (cep->snd_p_dstaddr != NULL) {	/* ノンブロッキングコールでペンディング中 */
		if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_SND_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		else
			error = E_OBJ;
		cep->snd_p_dstaddr = NULL;
		}
	else if (cep->snd_tskid != TA_NULL) {	/* 非ノンブロッキングコールでペンディング中 */

#ifdef UDP_CFG_EXTENTIONS

		/* 待ち中に発生したエラー情報を設定する。*/
		cep->error = error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		error = rel_wai(cep->snd_tskid);
		cep->snd_tskid = TA_NULL;
		}
	else					/* どちらでもないならペンディングしていない */
		error = EV_NOPND;

	return error;
	}

#endif	/* of #ifdef __udp_can_snd */

#ifdef __udp_can_rcv

/*
 *  udp_can_rcv -- ペンディングしている受信のキャンセル
 */

ER
udp_can_rcv (T_UDP_CEP *cep, ER error)
{
	if (cep->rcv_p_dstaddr != NULL) {	/* ノンブロッキングコールでペンディング中 */
		if (IS_PTR_DEFINED(cep->callback))

#ifdef TCP_CFG_NON_BLOCKING_COMPAT14

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_RCV_DAT, (void*)error);

#else	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

			(*cep->callback)(GET_UDP_CEPID(cep), TFN_UDP_RCV_DAT, (void*)&error);

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING_COMPAT14 */

		else
			error = E_OBJ;
		cep->rcv_p_dstaddr = NULL;
		}
	else if (cep->rcv_tskid != TA_NULL) {	/* 非ノンブロッキングコールでペンディング中 */

#ifdef UDP_CFG_EXTENTIONS

		/* 待ち中に発生したエラー情報を設定する。*/
		cep->error = error;

#endif	/* of #ifdef UDP_CFG_EXTENTIONS */

		error = rel_wai(cep->rcv_tskid);
		cep->rcv_tskid = TA_NULL;
		}
	else					/* どちらでもないならペンディングしていない */
		error = EV_NOPND;

	return error;
	}

#endif	/* of #ifdef __udp_can_rcv */

#ifdef __udp_snd_dat

/*
 *  udp_snd_dat -- パケットの送信【標準機能】
 */

ER_UINT
UDP_SND_DAT (ID cepid, T_IPEP *p_dstaddr, void *data, int_t len, TMO tmout)
{
	T_UDP_CEP	*cep;
	ER		error;

	/* p_dstaddr または data が NULL ならエラー */
	if (p_dstaddr == NULL || data == NULL)
		return E_PAR;

	/* データ長をチェックする。*/
	if (len < 0 || len + IP_HDR_SIZE + UDP_HDR_SIZE > IF_MTU)
		return E_PAR;

	/* UDP 通信端点 ID をチェックする。*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP 通信端点を得る。*/
	cep = GET_UDP_CEP(cepid);

	/* UDP 通信端点をチェックする。*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/*
	 *  自ポート番号が UDP_PORTANY なら、自動で割り当てる。
	 */
	if (cep->myaddr.portno == UDP_PORTANY) {
		if ((error = udp_alloc_auto_port(cep)) != E_OK)
			return error;
		}

	/*
	 * タイムアウトをチェックする。
	 */

	if (tmout == TMO_NBLK) {	/* ノンブロッキングコール */

		/* 通信端点をロックする。*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->snd_p_dstaddr != NULL) {

			/* ノンブロッキングコールでペンディング中 */
			error = E_QOVR;

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));
			}
		else if (cep->snd_tskid != TA_NULL) {

			/* 非ノンブロッキングコールでペンディング中 */
			error = E_OBJ;

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));
			}
		else {

			cep->snd_p_dstaddr = p_dstaddr;
			cep->snd_data	= data;
			cep->snd_len	= len;

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));

			cep->flags |= UDP_CEP_FLG_POST_OUTPUT;
			sig_sem(SEM_UDP_POST_OUTPUT);
			error = E_WBLK;
			}
		}
	else {				/* 非ノンブロッキングコール */
	
		/* 通信端点をロックする。*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->snd_p_dstaddr != NULL) {

			/* ノンブロッキングコールでペンディング中 */
			error = E_OBJ;

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));
			}
		else if (cep->snd_tskid != TA_NULL) {

			/* 非ノンブロッキングコールでペンディング中 */
			error = E_QOVR;

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));
			}
		else {

			/* 現在のタスク識別子を記録する。*/
			get_tid(&(cep->snd_tskid));

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));

			/* パケットを送信する。*/
			error = udp_send_data(cep, p_dstaddr, data, len, tmout);
			}
		}

	return error;
	}

#endif	/* of #ifdef __udp_snd_dat */

#ifdef __udp_rcv_dat

/*
 *  udp_rcv_dat -- パケットの受信【標準機能】
 */

ER_UINT
UDP_RCV_DAT (ID cepid, T_IPEP *p_dstaddr, void *data, int_t len, TMO tmout)
{
	T_NET_BUF	*input;
	T_UDP_CEP	*cep;
	T_UDP_HDR	*udph;
	ER_UINT		error;
	uint_t		ulen, uhoff;

	/* p_dstaddr または data が NULL か、len < 0 ならエラー */
	if (p_dstaddr == NULL || data == NULL || len < 0)
		return E_PAR;

	/* UDP 通信端点 ID をチェックする。*/
	if (!VALID_UDP_CEPID(cepid))
		return E_ID;

	/* UDP 通信端点を得る。*/
	cep = GET_UDP_CEP(cepid);

	/* UDP 通信端点をチェックする。*/
	if (!VALID_UDP_CEP(cep))
		return E_NOEXS;

	/*
	 * タイムアウトをチェックする。
	 */

	if (tmout == TMO_NBLK) {	/* ノンブロッキングコール */

		/* 通信端点をロックする。*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->rcv_p_dstaddr != NULL)

			/* ノンブロッキングコールでペンディング中 */
			error = E_QOVR;

		else if (cep->rcv_tskid != TA_NULL)

			/* 非ノンブロッキングコールでペンディング中 */
			error = E_OBJ;
		else {
			cep->rcv_p_dstaddr = p_dstaddr;
			cep->rcv_data	= data;
			cep->rcv_len	= len;
			error = E_WBLK;
			}

		/* 通信端点をロックを解除する。*/
		syscall(sig_sem(cep->semid_lock));
		return error;
		}
	else {				/* 非ノンブロッキングコール */

		/* 通信端点をロックする。*/
		syscall(wai_sem(cep->semid_lock));

		if (cep->rcv_p_dstaddr != NULL) {

			/* ノンブロッキングコールでペンディング中 */
			error = E_OBJ;

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));
			}
		else if (cep->rcv_tskid != TA_NULL) {

			/* 非ノンブロッキングコールでペンディング中 */
			error = E_QOVR;

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));
			}
		else {

			/* 現在のタスク識別子を記録する。*/
			get_tid(&(cep->rcv_tskid));

			/* 通信端点をロックを解除する。*/
			syscall(sig_sem(cep->semid_lock));

			/* 入力があるまで待つ。*/
			if (cep->cb_netbuf != NULL) {

				/*
				 *  ここにくる場合は、コールバック関数の中から
				 *  udp_rcv_dat を呼び出していることになり、
				 *  すでに入力済みである。
				 */
				input = cep->cb_netbuf;
				cep->cb_netbuf = NULL;
				}
			else if ((error = trcv_dtq(cep->rcvqid, (intptr_t*)&input, tmout)) != E_OK) {
				cep->rcv_tskid = TA_NULL;
				return error;
				}

			/* p_dstaddr を設定する。*/
			uhoff = (uint_t)GET_UDP_HDR_OFFSET(input);
			udph = GET_UDP_HDR(input, uhoff);
			p_dstaddr->portno = ntohs(udph->sport);
			IN_COPY_TO_HOST(&p_dstaddr->ipaddr, &GET_IP_HDR(input)->src);

			/* データをバッファに移す。*/
			ulen = ntohs(udph->ulen);
			if (ulen - UDP_HDR_SIZE > len)
				error = E_BOVR;
			else {
				len   =     (int_t)(ulen - UDP_HDR_SIZE);
				error = (ER_UINT)(ulen - UDP_HDR_SIZE);
				}

			memcpy(data, GET_UDP_SDU(input, uhoff), (size_t)len);

			syscall(rel_net_buf(input));

			cep->rcv_tskid = TA_NULL;
			}
		return error;
		}
	}

#endif	/* of #ifdef __udp_rcv_dat */

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#endif	/* of #ifdef SUPPORT_UDP */
