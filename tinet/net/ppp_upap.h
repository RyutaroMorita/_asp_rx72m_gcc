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
 *  @(#) $Id: ppp_upap.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * upap.h - User/Password Authentication Protocol definitions.
 *
 * Copyright (c) 1989 Carnegie Mellon University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Carnegie Mellon University.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/pppd/upap.h,v 1.6.2.1 1999/08/29 15:47:10 peter Exp $
 */

/*
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/pap.h,v 1.11 1999/08/28 01:18:37 peter Exp $
 *
 *	TODO:
 */

#ifndef _PPP_UPAP_H_
#define _PPP_UPAP_H_

#ifdef SUPPORT_PPP

/*
 *  PAP の制御コード
 */

#define PAP_AUTHREQ		UINT_C(1)	/* 認証要求	*/
#define PAP_AUTHACK		UINT_C(2)	/* 認証 ACK	*/
#define PAP_AUTHNAK		UINT_C(3)	/* 認証 NAK	*/

/*
 *  クライアントの状態
 */

#define PAP_CS_INIT		UINT_C(0)	/* 未接続		*/
#define PAP_CS_CLOSED		UINT_C(1)	/* 接続、未認証		*/
#define PAP_CS_PENDING		UINT_C(2)	/* 未接続、認証		*/
#define PAP_CS_AUTHREQ		UINT_C(3)	/* 認証要求送信済み	*/
#define PAP_CS_OPEN		UINT_C(4)	/* ACK 受信		*/
#define PAP_CS_BADAUTH		UINT_C(5)	/* NAK 受信		*/

/*
 *  サーバの状態
 */

#define PAP_SS_INIT		UINT_C(0)	/* 未接続		*/
#define PAP_SS_CLOSED		UINT_C(1)	/* 接続、未認証		*/
#define PAP_SS_PENDING		UINT_C(2)	/* 未接続、認証		*/
#define PAP_SS_LISTEN		UINT_C(3)	/* 認証要求受信待ち	*/
#define PAP_SS_OPEN		UINT_C(4)	/* ACK 送信		*/
#define PAP_SS_BADAUTH		UINT_C(5)	/* NAK 送信		*/

/*
 *  変数
 */

extern T_PPP_PROTENT	pap_protent;

/*
 *  関数
 */

extern void upap_auth_client (void);
extern void upap_auth_server (void);

#endif	/* of #ifdef SUPPORT_PPP */

#endif	/* of #ifndef _PPP_UPAP_H_ */
