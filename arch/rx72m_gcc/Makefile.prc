#
#		Makefile のchip依存部（rx用）
#

# 
#  チップ依存部ディレクトリ名の定義 
# 
ARCHDIR = $(SRCDIR)/arch/$(PRC)_$(TOOL)

#
#  コンパイルオプション
#
INCLUDES := $(INCLUDES) -I$(ARCHDIR)
CDEFS := $(CDEFS)
COPTS := $(COPTS)

#
#  カーネルに関する定義
#
KERNEL_DIR := $(KERNEL_DIR) $(ARCHDIR)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_test.o
KERNEL_COBJS := $(KERNEL_COBJS) rx72m_config.o

#
#  システムサービスに関する定義
#
SYSSVC_DIR := $(SYSSVC_DIR)
SYSSVC_COBJS := $(SYSSVC_COBJS)

#
#  トレースログに関する設定
#
ifeq ($(ENABLE_TRACE),true)
	COPTS := $(COPTS) -DTOPPERS_ENABLE_TRACE
	KERNEL_DIR := $(KERNEL_DIR) $(SRCDIR)/arch/logtrace
	KERNEL_COBJS := $(KERNEL_COBJS) trace_config.o trace_dump.o
endif

#
#  依存関係の定義
#
kernel_cfg.timestamp: $(ARCHDIR)/rx72m.tf
$(OBJFILE): $(ARCHDIR)/prc_check.tf

# 
#  オフセットファイル生成のための定義 
# 
#OFFSET_TF := $(ARCHDIR)/core_offset.tf
OFFSET_TF = $(TARGETDIR)/target_offset.tf

#
#		Makefile のプロセッサ依存部（RX用）
#

#
#  ツール依存部ディレクトリ名の定義 
#
TOOLDIR = $(SRCDIR)/arch/$(TOOL)

#
#  コンパイルオプション
#
COPTS := $(COPTS) -misa=v3 -mlittle-endian-data -std=gnu99
INCLUDES := $(INCLUDES) -I$(TOOLDIR)
LDFLAGS := -nostdlib $(LDFLAGS)
CDEFS := $(CDEFS)
LIBS := $(LIBS)

#
#  カーネルに関する定義
#
KERNEL_DIR := $(KERNEL_DIR) $(COREDIR)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_support.o
KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o

#
#  依存関係の定義
#
cfg1_out.c: $(ARCHDIR)/prc_def.csv
kernel_cfg.timestamp: $(ARCHDIR)/prc.tf

#
#  コンフィギュレータ関係の変数の定義
#
CFG_TABS := $(CFG_TABS) --cfg1-def-table $(ARCHDIR)/prc_def.csv
