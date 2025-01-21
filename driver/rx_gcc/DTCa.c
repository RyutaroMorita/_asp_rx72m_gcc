/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <kernel_impl.h>
#include <driver/rx_gcc/DTCa.h>

//DTC register define
//#define DID_DTCA     //defined in target_device_id.h
#define DTC_DTCCR (DTCA_BASE_ADDR+0x0)
#define DTC_DTCVBR (DTCA_BASE_ADDR+0x4)
#define DTC_DTCADMOD (DTCA_BASE_ADDR+0x8)
#define DTC_DTCST (DTCA_BASE_ADDR+0xC)
#define DTC_DTCSTS (DTCA_BASE_ADDR+0xE)

void set_vecter_table(uint8_t intno, dtca_descriptor *vecter){
  dtca_table[intno] = vecter;
}

//
// DTCA Macro Controll
//
#define DTCA_MODE_ENABLE 0x1
#define DTCA_MODE_DISABLE 0x0

void dtca_enable(){
  sil_wrb_mem((uint8_t*)DTC_DTCST, DTCA_MODE_ENABLE);
}
  
void dtca_disable(){
  sil_wrb_mem((uint8_t*)DTC_DTCST, DTCA_MODE_DISABLE);
}

//Set DTCER to accept irq.
void dtcer_irq_enable(uint8_t intno){
  ENABLE_ICU_DTCER(intno);
}

void dtcer_irq_disable(uint8_t intno){
  DISABLE_ICU_DTCER(intno);
}
