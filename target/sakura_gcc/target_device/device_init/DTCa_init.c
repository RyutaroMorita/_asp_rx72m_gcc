/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include "target_board.h"
#include "driver/rx/DTCa.h"

#define DTCA_BASE 0x00082400

#ifdef USE_DTCA_0

//device info define
dev_node_t dtca_node_0 = x{
  DTCA_BASE,
  NULL  //DTCA don't have irq
};

void target_dev_init_dtca_0(){
  //unlock register access 
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);
  /*
   * モジュールストップ機能の設定(DTCa)
   */
  *SYSTEM_MSTPCRA_ADDR &= ~(SYSTEM_MSTPCRA_MSTPA28_BIT); /* CMT0 */
  //lock register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );

  //set dtc vecter base
  sil_wrw_lem((uint32_t *)(DTCA_BASE+DTC_DTCCR_OFFSET), dtca_vector);
}


#endif
