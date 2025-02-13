/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 */

#include <string.h>
#include <errno.h>

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "kernel_cfg.h"
#include "main.h"
#include "target_board.h"
#include "r_smc_entry.h"

#include "tinet_cfg.h"
#include <tinet_config.h>
#include <tinet_defs.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>


/*
 *  メインタスク
 */
void main_task(intptr_t exinf)
{
	/*
	 *  PHY(KSZ8081MNX/RNB)のリセット
	 */
	PIN_WRITE(A,6) = 0;
	dly_tsk(10);
	PIN_WRITE(A,6) = 1;

	wup_tsk(ETHER_INPUT_TASK);

	act_tsk(UDP_TASK);

	while (1) {
		syslog(LOG_NOTICE, "main_task is running.");
		dly_tsk(1000);
	}
}


/*
 * UDPテストタスク
 */
#define UDP_MAX_DATA_SIZE	1024
static uint_t		buffer[2][UDP_MAX_DATA_SIZE/sizeof(uint_t)];
void udp_task(intptr_t exinf)
{
	int_t tskno = (int_t) exinf;
	int8_t *buf_snd = (int8_t *)buffer[0];
	int8_t *buf_rcv = (int8_t *)buffer[1];
	T_IPV4EP dst;			// 通信相手ＩＰ情報
	ID id = 0;
	int_t len = 0;
	int i;
	ER er;			// サービスコール戻り値

	dst.ipaddr = MAKE_IPV4_ADDR(192,168,0,1);
	dst.portno = 1001;
	id = ID_UDP0;
	len = UDP_MAX_DATA_SIZE;

	for ( i = 0; i < len; i++ )
		buf_snd[i] = (int8_t)i;

	while (true) {
		// UDP送信
		er = udp_snd_dat(id, &dst, (void *)buf_snd, len, 1000);
		if ( er <= 0 ) {	// エラーの場合
			syslog(LOG_NOTICE, "Error in udp_snd_dat() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
		er = udp_rcv_dat(id, &dst, (void *)buf_rcv, len, 1000);
		if ( er <= 0 ) {	// エラーの場合
			syslog(LOG_NOTICE, "Error in udp_rcv_dat() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
		if ( memcmp(buf_snd, buf_rcv, len) != 0 ) {
			syslog(LOG_NOTICE, "Error in memcmp() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
	}
}


/*
 *  以下、 syscalls のダミー.
 */
int getpid(void)
{
	return 1;
}

int kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	kill(status, -1);
	while (1) {}		/* Make sure we hang here */
}

extern int errno;
caddr_t sbrk(int incr)
{
	errno = ENOMEM;
	return (caddr_t) -1;
}
