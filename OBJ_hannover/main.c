/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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

#include <string.h>
#include <errno.h>

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "kernel_cfg.h"
#include "main.h"
#include "target_board.h"

#include "tinet_cfg.h"
#include <tinet_config.h>
#include <tinet_defs.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

/*
 *  smc_gen �f�B���N�g�����̓��e�Ɉˑ����邽�� r_smc_entry.h �̓C���N���[�h���Ȃ�.
 */
//#include "r_cg_macrodriver.h"
#include "platform.h"
#include "r_cg_port.h"
#include "r_cg_icu.h"
#include "r_cg_rspi.h"
#include "Pin.h"
//#include "Config_ICU/Config_ICU.h"
//#include "Config_PORT/Config_PORT.h"
//#include "Config_RSPI0/Config_RSPI0.h"


volatile uint8_t * gp_rspi0_tx_address;             /* RSPI0 transmit buffer address */
volatile uint16_t g_rspi0_tx_count;                 /* RSPI0 transmit data number */
volatile uint8_t * gp_rspi0_rx_address;             /* RSPI0 receive buffer address */
volatile uint16_t g_rspi0_rx_count;                 /* RSPI0 receive data number */
volatile uint16_t g_rspi0_rx_length;                /* RSPI0 receive data length */


void rspi_tx_handler(void)
{
    uint16_t frame_cnt;

    /* WAIT_LOOP */
    for (frame_cnt = 0U; frame_cnt < (_00_RSPI_FRAMES_1 + 1U); frame_cnt++)
    {
        if (g_rspi0_tx_count > 0U)
        {
            /* Write data for transmission */
            RSPI0.SPDR.BYTE.HH = (*(uint8_t*)gp_rspi0_tx_address);
            gp_rspi0_tx_address++;
            g_rspi0_tx_count--;
        }
        else
        {
            /* Disable transmit interrupt */
            RSPI0.SPCR.BIT.SPTIE = 0U;
            break;
        }
    }
}


void rspi_rx_handler(void)
{
    uint16_t frame_cnt;

    /* WAIT_LOOP */
    for (frame_cnt = 0U; frame_cnt < (_00_RSPI_FRAMES_1 + 1U); frame_cnt++)
    {
        if (g_rspi0_rx_length > g_rspi0_rx_count)
        {
            *(uint8_t *)gp_rspi0_rx_address = RSPI0.SPDR.BYTE.HH;
            gp_rspi0_rx_address++;
            g_rspi0_rx_count++;

            if (g_rspi0_rx_length == g_rspi0_rx_count)
            {
                /* Disable receive interrupt */
                RSPI0.SPCR.BIT.SPRIE = 0U;
                iwup_tsk(MAIN_TASK);
                break;
            }
        }
    }
}


static void main_init(void)
{
    volatile uint8_t spcr_dummy;

	//unlock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

	/*
	 *  R_Config_PORT_Create
	 */
    /* Set PORTA registers */
    PORTA.PODR.BYTE = _00_Pm6_OUTPUT_0;
    PORTA.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTA.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORTA.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF |
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF | _00_Pm7_HIDRV_OFF;
    PORTA.DSCR2.BYTE = _00_Pm0_HISPEED_OFF | _00_Pm1_HISPEED_OFF | _00_Pm2_HISPEED_OFF | _00_Pm3_HISPEED_OFF |
                       _00_Pm4_HISPEED_OFF | _00_Pm5_HISPEED_OFF | _00_Pm6_HISPEED_OFF | _00_Pm7_HISPEED_OFF;
    PORTA.PMR.BYTE = _00_Pm6_PIN_GPIO;
    PORTA.PDR.BYTE = _40_Pm6_MODE_OUTPUT;

    /*
     *  R_Config_ICU_Create
     */
    /* Disable IRQ interrupts */
    ICU.IER[0x08].BYTE = 0x00U;
    ICU.IER[0x09].BYTE = 0x00U;

    /* Disable software interrupt */
    IEN(ICU,SWINT) = 0U;
    IEN(ICU,SWINT2) = 0U;

    /* Disable IRQ digital filter */
    ICU.IRQFLTE0.BYTE &= ~(_01_ICU_IRQ0_FILTER_ENABLE);

    /* Set IRQ0 pin */
    MPC.P10PFS.BYTE = 0x40U;
    PORT1.PDR.BYTE &= 0xFEU;
    PORT1.PMR.BYTE &= 0xFEU;

    /* Set IRQ detection type */
    ICU.IRQCR[0].BYTE = _00_ICU_IRQ_EDGE_LOW_LEVEL;

    /* Set IRQ priority level */
    IPR(ICU,IRQ0) = _06_ICU_PRIORITY_LEVEL6;

    /*
     *  R_Config_RSPI0_Create
     */
    /* Disable RSPI interrupts */
    IEN(RSPI0,SPTI0) = 0U;
    IEN(RSPI0,SPRI0) = 0U;

    /* Cancel RSPI0 module stop state */
    MSTP(RSPI0) = 0U;

    /* Disable RSPI function */
    RSPI0.SPCR.BIT.SPE = 0U;

    /* Set control registers */
    RSPI0.SSLP.BYTE = _00_RSPI_SSL0_POLARITY_LOW;
    RSPI0.SPPCR.BYTE = _00_RSPI_LOOPBACK_DISABLED | _00_RSPI_LOOPBACK2_DISABLED;
    RSPI0.SPDCR.BYTE = _40_RSPI_ACCESS_BYTE | _00_RSPI_FRAMES_1;
    RSPI0.SPCR2.BYTE = _00_RSPI_PARITY_DISABLE;
    RSPI0.SPCMD0.WORD = _0001_RSPI_RSPCK_SAMPLING_EVEN | _0000_RSPI_RSPCK_POLARITY_LOW |
                        _0400_RSPI_DATA_LENGTH_BITS_8 | _0000_RSPI_MSB_FIRST;
    RSPI0.SPDCR2.BYTE = _00_RSPI_BYTESWAP_DISABLED;

    /* Set SPTI0 priority level */
    IPR(RSPI0,SPTI0) = _03_RSPI_PRIORITY_LEVEL3;

    /* Set SPRI0 priority level */
    IPR(RSPI0,SPRI0) = _03_RSPI_PRIORITY_LEVEL3;

    /* Set RSPCKA pin */
    MPC.PC5PFS.BYTE = 0x0DU;
    PORTC.ODR1.BYTE &= 0xFBU;
    PORTC.PMR.BYTE |= 0x20U;

    /* Set MOSIA pin */
    MPC.PC6PFS.BYTE = 0x0DU;
    PORTC.ODR1.BYTE &= 0xEFU;
    PORTC.PMR.BYTE |= 0x40U;

    /* Set MISOA pin */
    MPC.PC7PFS.BYTE = 0x0DU;
    PORTC.ODR1.BYTE &= 0xBFU;
    PORTC.PMR.BYTE |= 0x80U;

    /* Set SSLA0 pin */
    MPC.PC4PFS.BYTE = 0x0DU;
    PORTC.ODR1.BYTE &= 0xFEU;
    PORTC.PMR.BYTE |= 0x10U;

    RSPI0.SPCR.BYTE = _00_RSPI_MODE_SPI | _00_RSPI_FULL_DUPLEX_SYNCHRONOUS | _00_RSPI_SLAVE_MODE;
    spcr_dummy = RSPI0.SPCR.BYTE;

	//lock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY);
}


static void RSPI0_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf)
{
    if (tx_num < 1U)
    {
        return;
    }
    else
    {
        /* Initialize the global counters */
        gp_rspi0_tx_address = tx_buf;
        g_rspi0_tx_count = tx_num;
        gp_rspi0_rx_address = rx_buf;
        g_rspi0_rx_length = tx_num;
        g_rspi0_rx_count = 0U;

        /* Clear SPE bit to ensure transmit buffer empty interrupt be generated
           when state of SPE bit changing from 0 to 1 is satisfied later        */
        if(1U == RSPI0.SPCR.BIT.SPE)
        {
            RSPI0.SPCR.BIT.SPE = 0U;
        }

        /* Enable transmit interrupt */
        RSPI0.SPCR.BIT.SPTIE = 1U;

        /* Enable receive interrupt */
        RSPI0.SPCR.BIT.SPRIE = 1U;

        /* Enable RSPI function */
        RSPI0.SPCR.BIT.SPE = 1U;
    }
}

/*
 *  ���C���^�X�N
 */
#define LENGTH	11
uint8_t tx_buf[32];
uint8_t rx_buf[32];
volatile bool rspi_recieved = false;
void main_task(intptr_t exinf)
{
	volatile uint8_t dummy;
	int count;
	int i;
	uint8_t msg[80];

#if 0
	//unlock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

	R_Config_PORT_Create();
	R_Config_ICU_Create();
	R_Config_RSPI0_Create();

	//lock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY);
#endif

	main_init();

	/*
	 *  PHY(KSZ8081MNX/RNB)�̃��Z�b�g
	 */
	PIN_WRITE(A,6) = 0;
	dly_tsk(10);
	PIN_WRITE(A,6) = 1;

	wup_tsk(ETHER_INPUT_TASK);

	//act_tsk(UDP_TASK);

	/*
	 *  R_Config_RSPI0_Start();
	 */
	ena_int(INTNO_RSPI_TX);
	ena_int(INTNO_RSPI_RX);
    /* Clear error sources */
    dummy = RSPI0.SPSR.BYTE;
    RSPI0.SPSR.BYTE = 0xA0U;

    /* Disable idle interrupt */
    RSPI0.SPCR2.BIT.SPIIE = 0U;

	while (1) {
		/*
		 *  R_Config_RSPI0_Send_Receive(tx_buf, LENGTH, rx_buf);
		 */
		RSPI0_Send_Receive(tx_buf, LENGTH, rx_buf);
		slp_tsk();
		count = 0;
		for (i = 0; i < LENGTH; i++) {
			msg[count] = '0' + ((rx_buf[i] / 100) % 10);
			count++;
			msg[count] = '0' + ((rx_buf[i] / 10) % 10);
			count++;
			msg[count] = '0' + ((rx_buf[i] / 1) % 10);
			count++;
			if (i < (LENGTH - 1)) {
				msg[count] = ',';
				count++;
			} else {
				msg[count] = 0;
			}
		}
		syslog(LOG_NOTICE, (const char *)msg);
	}
}


/*
 * UDP�e�X�g�^�X�N
 */
#define UDP_MAX_DATA_SIZE	1024
static uint_t		buffer[2][UDP_MAX_DATA_SIZE/sizeof(uint_t)];
void udp_task(intptr_t exinf)
{
	int_t tskno = (int_t) exinf;
	int8_t *buf_snd = (int8_t *)buffer[0];
	int8_t *buf_rcv = (int8_t *)buffer[1];
	T_IPV4EP dst;			// �ʐM����h�o���
	ID id = 0;
	int_t len = 0;
	int i;
	ER er;			// �T�[�r�X�R�[���߂�l

	dst.ipaddr = MAKE_IPV4_ADDR(192,168,0,1);
	dst.portno = 1001;
	id = ID_UDP0;
	len = UDP_MAX_DATA_SIZE;

	for ( i = 0; i < len; i++ )
		buf_snd[i] = (int8_t)i;

	while (true) {
		// UDP���M
		er = udp_snd_dat(id, &dst, (void *)buf_snd, len, 1000);
		if ( er <= 0 ) {	// �G���[�̏ꍇ
			syslog(LOG_NOTICE, "Error in udp_snd_dat() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
		er = udp_rcv_dat(id, &dst, (void *)buf_rcv, len, 1000);
		if ( er <= 0 ) {	// �G���[�̏ꍇ
			syslog(LOG_NOTICE, "Error in udp_rcv_dat() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
		if ( memcmp(buf_snd, buf_rcv, len) != 0 ) {
			syslog(LOG_NOTICE, "Error in memcmp() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
	}
}


/*
 *  �ȉ��A syscalls �̃_�~�[.
 */
int getpid(void)
{
	return 1;
}

int kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	kill(status, -1);
	while (1) {}		/* Make sure we hang here */
}

extern int errno;
caddr_t sbrk(int incr)
{
	errno = ENOMEM;
	return (caddr_t) -1;
}
