/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id$
 */

/*
 *  ターゲット依存モジュール（RX72M用）
 */

#include <kernel.h>
#include <sil.h>
#include <tinet_defs.h>
#include <tinet_config.h>
#include "target_board.h"


/*
 * MACアドレスの設定
*/
uint8_t mac_addr[6] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };


/*
 *  rx72m_bus_init -- ターゲット依存部のバスの初期化
 */
void rx72m_bus_init(void)
{
	/*
	 *  イーサネットチャネル0をMIIモードに設定
	 */
	sil_wrb_mem(
			(void *)(MPC_PFENET_ADDR),
			(uint32_t)(sil_reb_mem((void *)MPC_PFENET_ADDR) | MPC_PFENET_PHYMODE0_BIT)
	);

	//unlock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

	/*
	 *  モジュールストップ機能の設定
	 */
	sil_wrw_mem(
			(void *)(SYSTEM_MSTPCRB_ADDR),
			(uint32_t)(sil_rew_mem((void *)SYSTEM_MSTPCRB_ADDR) & ~SYSTEM_MSTPCRB_MSTPB15_BIT)
	);

	//lock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY);

	slp_tsk();	// 後で main.c から wup_tsk(ETHER_INPUT_TASK) される
}


/*
 *  rx72m_inter_init -- ターゲット依存部の割込みの初期化
 */
void
rx72m_inter_init(void)
{
	/*
	 *  ---- KSZ8081MNX/RNBからの割り込み(IRQ0:P10) ----
	 *
	 *  INTRP (ピン 21) は、KSZ8081MNX/RNB PHY レジスタのステータスが更新されたことを外部コントローラに通知するために使用されるオプションの割り込み信号です。
	 *  レジスタ 1Bh のビット [15:8] は、INTRP 信号をアサートする条件を有効または無効にする割り込み制御ビットです。
	 *  レジスタ 1Bh のビット [7:0] は、どの割り込み条件が発生したかを示す割り込みステータス ビットです。
	 *  割り込みステータス ビットは、レジスタ 1Bh の読み取り後にクリアされます。レジスタ 1Fh のビット [9] は、割り込みレベルをアクティブ ハイまたはアクティブ ローに設定します。
	 *  デフォルトはアクティブ ローです。MII 管理バス オプションにより、MAC プロセッサは KSZ8081MNX/RNB 制御レジスタとステータス レジスタに完全にアクセスできます。
	 *  さらに、割り込みピンにより、プロセッサがステータス変更のために PHY をポーリングする必要がなくなります。
	 */
}


/*
 *  戻り値に TRUE を指定すると、TINET で重複相手の MAC アドレスを syslog に出力し、
 *  重複相手にも重複したことを伝える。
 *  FALSE を指定すると何もしない。
*/
bool_t arp_callback_duplicated(uint8_t *shost)
{
	/*
	 *  IPアドレスの重複を検知した時の処理
	 */
	return false;
}
