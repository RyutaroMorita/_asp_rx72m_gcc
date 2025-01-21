/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
 * 
 *  上記著作権者は，Free Software Foundation によって公表されている 
 *  GNU General Public License の Version 2 に記述されている条件か，以
 *  下の(1)～(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
 *  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
 *      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
 *      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
 *      この利用条件および下記の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
 *      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
 *    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
 *        こと．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者を免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
 *  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
 *  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
 *  かなる損害に関しても，その責任を負わない．
 * 
 */

/*
 *	ターゲットシステム依存モジュール（Starter Kit用）
 */

#include "kernel_impl.h"
#include <sil.h>
#include "starter_kit.h"
#include "rx600/rx600_uart.h"

/*
 *  ターゲットシステム依存 初期化ルーチン
 */
void
target_initialize( void )
{
	/*
	 *  プロセッサ依存の初期化
	 */
	prc_initialize();

	/*
	 *  ポートの設定
	 */
	rx600_uart_init( TARGET_PUTC_PORTID, UART_BAUDRATE, UART_CLKSRC );

	/* ポートP26をTxD1, ポートP25をRxD1に */
	/* 入力コントロールレジスタ(ICR)の設定 P25(RxD1)を入力バッファ有効にする */
	sil_wrb_mem((void *)(PORT2_ICR_ADDR) , 
					sil_reb_mem((void *)(PORT2_ICR_ADDR)) | PORT_ICR_B5_BIT);

	/* 入力コントロールレジスタ(ICR)の設定 P26(TxD1)を入力バッファ無効にする */
	sil_wrb_mem((void *)(PORT2_ICR_ADDR) , 
					sil_reb_mem((void *)(PORT2_ICR_ADDR)) & ~PORT_ICR_B6_BIT);

	/* データディレクションレジスタ(DDR)の設定 P25(RxD1)を入力ポートにする */
	sil_wrb_mem((void *)(PORT2_DDR_ADDR) , 
					sil_reb_mem((void *)(PORT2_DDR_ADDR)) & ~PORT_DDR_B5_BIT);

	/* データディレクションレジスタ(DDR)の設定 P26(TxD1)を出力ポートにする */
	sil_wrb_mem((void *)(PORT2_DDR_ADDR) , 
					sil_reb_mem((void *)(PORT2_DDR_ADDR)) | PORT_DDR_B6_BIT);
}


/*
 *  ターゲットシステムの終了ルーチン
 */
void
target_exit( void )
{
	/*
	 *	プロセッサ依存の終了処理
	 */
	prc_terminate();

	while ( 1 );
}


/*
 *  システムログの低レベル出力のための文字出力
 */
void
target_fput_log( char c )
{
	if( c == '\n' ){
	   rx600_uart_pol_putc( '\r' , TARGET_PUTC_PORTID );
	}

    rx600_uart_pol_putc( c , TARGET_PUTC_PORTID );
}


