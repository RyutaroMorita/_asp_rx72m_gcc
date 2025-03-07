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
 *  @(#) $Id: usrv6.c,v 1.5 2009/12/24 06:20:39 abe Exp $
 */

/* 
 *  UDP ECHO サーバ
 *
 *    ・送受信タスク同一型
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include "usrv6.h"

/*
 *  外部関数の定義
 */

extern const char *itron_strerror (ER ercd);

/*
 *  変数
 */

#define BUF_SIZE	2048

/*
 *  UDP ECHO サーバタスク
 */

void
usrv_task(intptr_t exinf)
{
	static uint8_t buffer[BUF_SIZE];

	T_IPV6EP	dst;
	T_IN6_ADDR	addr;
	ER_UINT		len;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		if ((len = udp6_rcv_dat((ID)exinf, &dst, buffer, sizeof(buffer), 20 * 1000)) >= 0) {
			buffer[len] = '\0';
			syslog(LOG_NOTICE, "[UDP ECHO SRV] recv, addr: %s:%d,\n"
			                   "                     len: %d, msg: '%s'",
			                   ipv62str(NULL, &dst.ipaddr), dst.portno, len, buffer);
			if ((int)len > 0) {
				if ((len = udp6_snd_dat((ID)exinf, &dst, buffer, len, TMO_FEVR)) < 0)
					syslog(LOG_NOTICE, "[UDP ECHO SRV] send, error: %s", itron_strerror(len));
				}
			}
		else
			syslog(LOG_NOTICE, "[UDP ECHO SRV] recv, error: %s", itron_strerror(len));
		}
	}
