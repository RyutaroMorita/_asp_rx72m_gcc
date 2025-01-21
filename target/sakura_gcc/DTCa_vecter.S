/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#include "target_device/use_device.h"
    
.section DTCA_VECTOR_SEC
.glb _dtca_vector
    
_dtca_vector:
#ifdef USE_DTCA_0
	.blkb		0400H
#endif
	.glb _dtca_vector_end
_dtca_vector_end:
