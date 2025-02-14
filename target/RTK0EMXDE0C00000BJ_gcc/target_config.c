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
 *  ��L���쌠�҂́CFree Software Foundation �ɂ���Č��\����Ă���
 *  GNU General Public License �� Version 2 �ɋL�q����Ă���������C��
 *  ����(1)?(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F
 *  �A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���ė��p�\�ȃo�C�i���R�[�h�i�����P�[�^�u���I�u
 *      �W�F�N�g�t�@�C���⃉�C�u�����Ȃǁj�̌`�ŗ��p����ꍇ�ɂ́C���p
 *      �ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C
 *      ���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���ė��p�s�\�ȃo�C�i���R�[�h�̌`�܂��͋@��ɑg
 *      �ݍ��񂾌`�ŗ��p����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
 *    (a) ���p�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
 *        ���\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) ���p�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āC��L���쌠�҂ɕ񍐂���
 *        ���ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂�Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂́C
 *  �{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\�����܂߂āC�����Ȃ�ۏ؂��s��
 *  �Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ�������
 *  ���Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *	�^�[�Q�b�g�V�X�e���ˑ����W���[���iRTK0EMXDE0C00000BJ�p�j
 */

#include "kernel_impl.h"
#include <stdbool.h>
#include <sil.h>
#include "target_board.h"
#include "rx72m/rx72m_uart.h"
#include "mcu_clocks.h"
#include "r_bsp_cpu.h"
#include "Pin.h"


static void usart_early_init( void )
{
	/*
	 *  �^�[�Q�b�g�̃|�[�g�ݒ�
	 */
	R_Pins_Create();

	/*
	 *  �J�[�l���N�����̃o�i�[�o�͗p�̏�����
	 */
	scic_uart_init(TARGET_PUTC_PORTID, UART_BAUDRATE, UART_CLKSRC);

	/* unlock PFS write protection */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSWE_BIT);

	// PORTB.PMR.BIT.B1 = 1U; // Please set the PMR bit after TE bit is set to 1.
	sil_wrb_mem((void *)(PORTB_PMR_ADDR), (uint8_t)(sil_reb_mem((void *)PORTB_PMR_ADDR) | PORT_PMR_B1_BIT));

	/* lock PFS write */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_B0WI_BIT);
}

/*
 *  �^�[�Q�b�g�V�X�e���ˑ� ���������[�`��
 */
void target_initialize( void )
{
	/*
	 *  �v���Z�b�T�ˑ��̏�����
	 */
	prc_initialize();

	//target_clock_config();
	mcu_clock_setup();

    /* Initialize RAM */
    bsp_ram_initialize();

	/*
	 *  �|�[�g�̐ݒ�
	 */
    usart_early_init();
}

/*
 *  �^�[�Q�b�g�V�X�e���̏I�����[�`��
 */
void
target_exit( void )
{
	/*
	 *	�v���Z�b�T�ˑ��̏I������
	 */
	prc_terminate();
	while ( 1 );
}

/*
 *  �V�X�e�����O�̒჌�x���o�͂̂��߂̕����o��
 */
void target_fput_log( char c )
{
	if (c == '\n'){
	   scic_uart_pol_putc('\r', TARGET_PUTC_PORTID);
	}
    scic_uart_pol_putc(c, TARGET_PUTC_PORTID);
}
