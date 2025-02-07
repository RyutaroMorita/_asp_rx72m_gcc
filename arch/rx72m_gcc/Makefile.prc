#
#		Makefile ��chip�ˑ����irx�p�j
#

# 
#  �`�b�v�ˑ����f�B���N�g�����̒�` 
# 
ARCHDIR = $(SRCDIR)/arch/$(PRC)_$(TOOL)

#
#  �R���p�C���I�v�V����
#
INCLUDES := $(INCLUDES) -I$(ARCHDIR)
CDEFS := $(CDEFS)
COPTS := $(COPTS)

#
#  �J�[�l���Ɋւ����`
#
KERNEL_DIR := $(KERNEL_DIR) $(ARCHDIR)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_test.o
KERNEL_COBJS := $(KERNEL_COBJS) rx72m_config.o

#
#  �V�X�e���T�[�r�X�Ɋւ����`
#
SYSSVC_DIR := $(SYSSVC_DIR)
SYSSVC_COBJS := $(SYSSVC_COBJS)

#
#  �g���[�X���O�Ɋւ���ݒ�
#
ifeq ($(ENABLE_TRACE),true)
	COPTS := $(COPTS) -DTOPPERS_ENABLE_TRACE
	KERNEL_DIR := $(KERNEL_DIR) $(SRCDIR)/arch/logtrace
	KERNEL_COBJS := $(KERNEL_COBJS) trace_config.o trace_dump.o
endif

#
#  �ˑ��֌W�̒�`
#
kernel_cfg.timestamp: $(ARCHDIR)/rx72m.tf
$(OBJFILE): $(ARCHDIR)/prc_check.tf

# 
#  �I�t�Z�b�g�t�@�C�������̂��߂̒�` 
# 
#OFFSET_TF := $(ARCHDIR)/core_offset.tf
OFFSET_TF = $(TARGETDIR)/target_offset.tf

#
#		Makefile �̃v���Z�b�T�ˑ����iRX�p�j
#

#
#  �c�[���ˑ����f�B���N�g�����̒�` 
#
TOOLDIR = $(SRCDIR)/arch/$(TOOL)

#
#  �R���p�C���I�v�V����
#
COPTS := $(COPTS) -misa=v3 -mlittle-endian-data -std=gnu99
INCLUDES := $(INCLUDES) -I$(TOOLDIR)
LDFLAGS := -nostdlib $(LDFLAGS)
CDEFS := $(CDEFS)
LIBS := $(LIBS)

#
#  �J�[�l���Ɋւ����`
#
KERNEL_DIR := $(KERNEL_DIR) $(COREDIR)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_support.o
KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o

#
#  �ˑ��֌W�̒�`
#
cfg1_out.c: $(ARCHDIR)/prc_def.csv
kernel_cfg.timestamp: $(ARCHDIR)/prc.tf

#
#  �R���t�B�M�����[�^�֌W�̕ϐ��̒�`
#
CFG_TABS := $(CFG_TABS) --cfg1-def-table $(ARCHDIR)/prc_def.csv
