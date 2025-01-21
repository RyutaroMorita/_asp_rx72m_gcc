/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <target_board.h>
#include <driver/rx_gcc/mmc_rspi.h>
#include <target_device/target_device.h>

#ifdef USE_MMC_RSPI_0

const dnode_id pdrv_to_dev[1] = {
  DEV_MMC_RSPI0
};

mmc_rspi_stat_t mmc_sdcard_rspi0_stat={
  DEV_RSPI0, //Drive ID of MMC disk io
  DEV_MMC_GPIO0, //Driver ID of Card detect io
  SSLP_SSL1P,
  STA_NOINIT, //Status
  0,       //CardType
  0       //time out flag
};

dev_node_t mmc_sdcard_rspi_node_0 = {
  &mmc_rspi_func,
  &mmc_sdcard_rspi0_stat
};
  
void target_dev_ini_mmc_sdcard_rspi_0(){
}

#endif
