/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2025 by Aeterlink Corp.
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
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

            /* キャストは、型が右側または引数と一致するため有効です */
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

            /* キャストは、型が右側または引数と一致するため有効です */
            if(((uint32_t)NULL != (uint32_t)pdata) && ((uint32_t)FIT_NO_FUNC != (uint32_t)pdata))
            {
                /* キャストは、型が右側または引数と一致するため有効です */
                //err = bsp_gr_int_enable_disable(vector, true, ((bsp_int_ctrl_t *)pdata)->ipl);
                //ena_int((INTNO)vector);	// 仮実装
            }
            else
            {
                err = BSP_INT_ERR_INVALID_ARG;
            }
            break;

        case (BSP_INT_CMD_GROUP_INTERRUPT_DISABLE):
            //err = bsp_gr_int_enable_disable(vector, false, 0);
        	dis_int((INTNO)vector);	// 仮実装
            break;
#endif

        case (BSP_INT_CMD_FIT_INTERRUPT_ENABLE):

            /* キャストは、型が右側または引数と一致するため有効です */
            //err = bsp_fit_interrupts_control(true, (bsp_int_ctrl_t *)pdata);
			//dis_int((INTNO)vector);	// 仮実装
            break;

        case (BSP_INT_CMD_FIT_INTERRUPT_DISABLE):

            /* キャストは、型が右側または引数と一致するため有効です */
            //err = bsp_fit_interrupts_control(false, (bsp_int_ctrl_t *)pdata);
        	//dis_int((INTNO)vector);	// 仮実装
            break;

        default:
            err = BSP_INT_ERR_INVALID_ARG;
            break;
    }

    return err;
}
