$ 
$     asm_config.inc 生成用
$     パス2のターゲット依存テンプレート（rsk_rx_hew用）
$ 
$     Copyright (C) 2010 by Witz Corporation, JAPAN

$ 

$ 
$  プロセッサ依存のテンプレートファイルのインクルード
$ 
$INCLUDE"prc_asm_config.tf"$

$FILE "asm_config.inc"$

$NL$

.equ LOG_INH_ENTER $TAB$ $TAB$ $+LOG_INH_ENTER$ $NL$
.equ LOG_INH_LEAVE $TAB$ $TAB$ $+LOG_INH_LEAVE$ $NL$
.equ LOG_EXC_ENTER $TAB$ $TAB$ $+LOG_EXC_ENTER$ $NL$
.equ LOG_EXC_LEAVE $TAB$ $TAB$ $+LOG_EXC_LEAVE$ $NL$
.equ LOG_DSP_ENTER $TAB$ $TAB$ $+LOG_DSP_ENTER$ $NL$
.equ LOG_DSP_LEAVE $TAB$ $TAB$ $+LOG_DSP_LEAVE$ $NL$
.equ SIL_DLY_TIM1 $TAB$ $TAB$ $+SIL_DLY_TIM1$ $NL$
.equ SIL_DLY_TIM2 $TAB$ $TAB$ $+SIL_DLY_TIM2$ $NL$
