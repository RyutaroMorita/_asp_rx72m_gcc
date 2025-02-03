$ 
$     asm_config.inc 生成用
$     パス2のアーキテクチャ依存テンプレート（rx用）
$ 

$FILE "asm_config.inc"$


.equ TIPM_LOCK $TAB$$TAB$ $TAB$ $+TIPM_LOCK$ $NL$
.equ IPL_LOCK $TAB$$TAB$ $TAB$ $+IPL_LOCK$ $NL$
.equ PSW_I_MASK $TAB$$TAB$ $TAB$ $+PSW_I_MASK$ $NL$
.equ PSW_IPL_MASK $TAB$$TAB$ $TAB$ $+PSW_IPL_MASK$ $NL$
.equ EXC_GET_PSW_OFFSET $TAB$$TAB$ $TAB$ $+EXC_GET_PSW_OFFSET$ $NL$
