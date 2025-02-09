/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2025 by Aeterlink Corp.
 *
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 *
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 *
 */

#include <kernel.h>

#include "platform.h"


//static bsp_int_err_t bsp_fit_interrupts_control(bool enable, bsp_int_ctrl_t * pdata);


void R_BSP_InterruptRequestEnable(uint32_t vector)
{
	ena_int((INTNO)vector);
}


void R_BSP_InterruptRequestDisable(uint32_t vector)
{
	dis_int((INTNO)vector);
}


bsp_int_err_t R_BSP_InterruptWrite(bsp_int_src_t vector,  bsp_int_cb_t callback)
{
	return BSP_INT_SUCCESS;
}


bsp_int_err_t R_BSP_InterruptControl(bsp_int_src_t vector, bsp_int_cmd_t cmd, void * pdata)
{
    bsp_int_err_t       err;
    bsp_int_cb_args_t   cb_args;

    err = BSP_INT_SUCCESS;

#ifdef BSP_MCU_GROUP_INTERRUPT
    /* nothing */
#else
    /* This code is only used to remove compiler info messages about these parameters not being used. */
    INTERNAL_NOT_USED(pdata);
#endif

    switch (cmd)
    {
#if 0
        case (BSP_INT_CMD_CALL_CALLBACK):

            /* �L���X�g�́A�^���E���܂��͈����ƈ�v���邽�ߗL���ł� */
            if (((uint32_t)g_bsp_vectors[vector] != (uint32_t)NULL) && ((uint32_t)g_bsp_vectors[vector] != (uint32_t)FIT_NO_FUNC))
            {
                /* Fill in callback info. */
                cb_args.vector = vector;

                g_bsp_vectors[vector](&cb_args);
            }
            else
            {
                err = BSP_INT_ERR_NO_REGISTERED_CALLBACK;
            }
            break;
#endif

        case (BSP_INT_CMD_INTERRUPT_ENABLE):
            //err = bsp_interrupt_enable_disable(vector, true);
        	ena_int((INTNO)vector);
            break;

        case (BSP_INT_CMD_INTERRUPT_DISABLE):
            //err = bsp_interrupt_enable_disable(vector, false);
        	dis_int((INTNO)vector);
            break;

#ifdef BSP_MCU_GROUP_INTERRUPT
        case (BSP_INT_CMD_GROUP_INTERRUPT_ENABLE):

            /* �L���X�g�́A�^���E���܂��͈����ƈ�v���邽�ߗL���ł� */
            if(((uint32_t)NULL != (uint32_t)pdata) && ((uint32_t)FIT_NO_FUNC != (uint32_t)pdata))
            {
                /* �L���X�g�́A�^���E���܂��͈����ƈ�v���邽�ߗL���ł� */
                //err = bsp_gr_int_enable_disable(vector, true, ((bsp_int_ctrl_t *)pdata)->ipl);
                //ena_int((INTNO)vector);	// ������
            }
            else
            {
                err = BSP_INT_ERR_INVALID_ARG;
            }
            break;

        case (BSP_INT_CMD_GROUP_INTERRUPT_DISABLE):
            //err = bsp_gr_int_enable_disable(vector, false, 0);
        	dis_int((INTNO)vector);	// ������
            break;
#endif

        case (BSP_INT_CMD_FIT_INTERRUPT_ENABLE):

            /* �L���X�g�́A�^���E���܂��͈����ƈ�v���邽�ߗL���ł� */
            //err = bsp_fit_interrupts_control(true, (bsp_int_ctrl_t *)pdata);
			//dis_int((INTNO)vector);	// ������
            break;

        case (BSP_INT_CMD_FIT_INTERRUPT_DISABLE):

            /* �L���X�g�́A�^���E���܂��͈����ƈ�v���邽�ߗL���ł� */
            //err = bsp_fit_interrupts_control(false, (bsp_int_ctrl_t *)pdata);
        	//dis_int((INTNO)vector);	// ������
            break;

        default:
            err = BSP_INT_ERR_INVALID_ARG;
            break;
    }

    return err;
}
