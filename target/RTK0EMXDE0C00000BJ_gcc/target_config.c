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
 *	ターゲットシステム依存モジュール（Starter Kit用）
 */

#include "kernel_impl.h"
#include <sil.h>
#include "target_board.h"
#include "renesas/scic_uart.h"
#include <target_device/target_device.h>

/*
 *  ターゲットシステム依存 初期化ルーチン
 */
void
sakura_clock_waitcount_config(void){
  //unlock lopwermode register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

  //clock wait count set
  sil_wrb_mem((void *)(SYSTEM_MOSCWTR_ADDR),SYSTEM_CLKWAIT_HE );
  sil_wrb_mem((void *)(SYSTEM_PLLWTCR_ADDR), SYSTEM_CLKWAIT_HA);
  
  //lock lopwermode register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
}


void 
sakura_clock_config( void ){
  const uint16_t wait_count = 1250; //pll lock wait count
  uint16_t i;
  sakura_clock_waitcount_config();

  //unlock access of clock setting register
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC0);
  //GR-SAKURA Bord OSC is 12MHz
  //set clock freq(PLL 196MHz, PCKB 48MHz PCKA 98MHz ICK 98MHz)
  //pll set div 1, mul 16
  sil_wrh_mem((void *)(CKG_PLLCR_ADDR), CKG_PLLCR_PLIDIV1 | CKG_PLLCR_STC16);
  //set bus clock rate
  sil_wrw_mem((void *)(CKG_SCKCR_ADDR),   CKG_SCKCR_PB_DIV04 
                                        | CKG_SCKCR_PA_DIV02   
                                        | CKG_SCKCR_BCK_DIV04
                                        | CKG_SCKCR_PSTOP0
                                        | CKG_SCKCR_PSTOP1
                                        | CKG_SCKCR_FCK_DIV04
                                        | CKG_SCKCR_ICK_DIV02
                                        | CKG_SCKCR_RESERVE);

  sil_wrh_mem((void *)(CKG_SCKCR2_ADDR), CKG_SCKCR2_IEBCK_DIV4 | CKG_SCKCR2_UCK_NOT_USE);

  //Main clock enable
   sil_wrb_mem((void *)(CKG_MOSCCR_ADDR), CKG_CLOCK_ENABLE);
   //Wait Main clock lock
   while(sil_reb_mem((void *)(CKG_MOSCCR_ADDR)) != CKG_CLOCK_ENABLE);
   
  //pll enable
   sil_wrb_mem((void *)(CKG_PLLCR2_ADDR), CKG_CLOCK_ENABLE);
   while(sil_reb_mem((void *)(CKG_PLLCR2_ADDR)) != CKG_CLOCK_ENABLE);
   //PLL lock wait
   //wait over 10ms, LOCO freq 125Khz, wait count is 125*10 = 1250;                               
   //switch clock(PLL select)
   sil_wrh_mem((void *)(CKG_SCKCR3_ADDR),   CKG_SCKCR3_PLL);                        
  //lock access of clock setting register
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );


}
void
sakura_port_config( void )
{
	/*
	 *  ?|?[?g????
	 */
	scic_uart_init( TARGET_PUTC_PORTID, UART_BAUDRATE, UART_CLKSRC );

	/* ?|?[?gP50??TxD2, ?|?[?gP52??RxD2?? */
	/* MPC setting */
	/* unlock PFS write protection */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSWE_BIT);
	/* p50 is set as TxD2 mode */
	sil_wrb_mem((void *)(MPC_P50PFS_ADDR), MPC_PFS_PSELA);
	/* p52 is set as RxD2 mode*/
	sil_wrb_mem((void *)(MPC_P52PFS_ADDR), MPC_PFS_PSELA);
	/* lock PFS write */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_B0WI_BIT);

	/* port mode setting */
	/* Port Mode Register(PMR) config. P50 and P52(RxD2) are setted to IP use */
	sil_wrb_mem((void *)(PORT5_PMR_ADDR) , 
					sil_reb_mem((void *)(PORT2_PMR_ADDR)) | PORT_PMR_B0_BIT | PORT_PMR_B2_BIT);
}

void
sakura_ip_wakeup( void )
{
  //unlock register access 
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);
  /*
   * ???W???[???X?g?b?v?@?\????(SCI2)
   */
  *SYSTEM_MSTPCRB_ADDR &= ~(SYSTEM_MSTPCRB_MSTPB29_BIT); /* CMT0 */
  //lock register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
}
void
target_initialize( void )
{
	/*
	 *  ?v???Z?b?T??????????
	 */

  prc_initialize();
  sakura_clock_config();
  //set port direction
  sakura_port_config();
  sakura_ip_wakeup();
  target_device_init();

}


/*
 *  ?^?[?Q?b?g?V?X?e????I?????[?`??
 */
void
target_exit( void )
{
	/*
	 *	?v???Z?b?T?????I??????
	 */
	prc_terminate();

	while ( 1 );
}


/*
 *  ?V?X?e?????O????x???o???????????o??
 */
void
target_fput_log( char c )
{
	if( c == '\n' ){
	   scic_uart_pol_putc( '\r' , TARGET_PUTC_PORTID );
	}

    scic_uart_pol_putc( c , TARGET_PUTC_PORTID );
}


