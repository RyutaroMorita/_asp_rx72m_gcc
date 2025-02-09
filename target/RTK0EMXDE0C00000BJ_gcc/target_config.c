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
 *  下の(1)?(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
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
 *	ターゲットシステム依存モジュール（RTK0EMXDE0C00000BJ用）
 */

#include <stdbool.h>
#include <sil.h>
#include "kernel_impl.h"
//#include "renesas/scic_uart.h"
//#include <target_device/target_device.h>
#include "mcu_clocks.h"
#include "platform.h"
#include "r_bsp_cpu.h"
#include "r_sci_rx72m_private.h"

//#include "target_board.h"


static void usart_early_init()
{
	//
	MSTP(SCI6) = 0;
	ch6_rom.regs->SCR.BYTE = 0;
    /* Configure SMR */
	ch6_rom.regs->SMR.BYTE = (uint8_t)((SCI_DATA_8BIT | SCI_STOPBITS_1) | (SCI_PARITY_OFF | SCI_EVEN_PARITY));
	//sci_init_bit_rate();
}

/*
 *  ターゲットシステム依存 初期化ルーチン
 */
void target_initialize( void )
{
	prc_initialize();

	//target_clock_config();
	mcu_clock_setup();

    /* Initialize RAM */
    bsp_ram_initialize();

    //usart_early_init();
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
void target_fput_log( char c )
{
	(void)c;
}
