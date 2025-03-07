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
 *  @(#) $Id: wwws.h,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

#ifndef _WWWS_H_
#define _WWWS_H_

/* 
 *  WWW サーバ
 */

#include <tinet_defs.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>

#include <netinet6/in6.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#ifdef TOPPERS_S810_CLG3_85
#define	WWW_SRV_STACK_SIZE		768		/* タスクのスタックサイズ	*/
#else	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define	WWW_SRV_STACK_SIZE		1024		/* タスクのスタックサイズ	*/
#endif	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define WWW_SRV_MAIN_PRIORITY		5		/* タスクの優先度		*/

/*
 *  TCP 送受信ウインドバッファサイズ
 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#define WWW_SRV_SWBUF_SIZE	((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)

#else	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)
#define WWW_SRV_SWBUF_SIZE	(TCP_MSS)
#endif

#if defined(SUPPORT_INET6)
#define WWW_SRV_SWBUF_SIZE	(TCP6_MSS)
#endif

#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)
#define WWW_SRV_RWBUF_SIZE	(TCP_MSS)
#endif

#if defined(SUPPORT_INET6)
#define WWW_SRV_RWBUF_SIZE	(TCP6_MSS)
#endif

#define WWW_RBUFF_SIZE		(WWW_SRV_RWBUF_SIZE)
#define WWW_LINE_SIZE		80
#define WWW_NUM_FIELDS		4

#ifndef _MACRO_ONLY

typedef struct line {
	uint8_t		len;
	uint8_t		num;
	uint8_t		off[WWW_NUM_FIELDS];
	char		buf[WWW_LINE_SIZE + 1];
	} T_WWW_LINE;

#ifdef USE_COPYSAVE_API

typedef struct www_buffer {
	char		*buf;
	uint16_t	len;
	uint16_t	index;
	} T_WWW_BUFFER;

#else	/* of #ifdef USE_COPYSAVE_API */

typedef struct www_buffer {
	uint16_t	len;
	uint16_t	index;
	char		buf[WWW_RBUFF_SIZE];
	} T_WWW_BUFFER;

#endif	/* of #ifdef USE_COPYSAVE_API */

typedef struct www_rwbuf {
	T_WWW_BUFFER	sbuf;
	T_WWW_BUFFER	rbuf;
	char		unget;
	} T_WWW_RWBUF;

/* タスク */

extern void	www_srv_task (intptr_t exinf);

/*
 *  TCP 送受信バッファ
 */

extern uint8_t www_srv_swbuf[NUM_WWW_SRV_TASKS][WWW_SRV_SWBUF_SIZE];
extern uint8_t www_srv_rwbuf[NUM_WWW_SRV_TASKS][WWW_SRV_RWBUF_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #ifndef _WWWS_H_ */
