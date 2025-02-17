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
#include "target_board.h"

#include "tinet_cfg.h"
#include <tinet_config.h>
#include <tinet_defs.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "main.h"

/*
 *  smc_gen �f�B���N�g�����̓��e�Ɉˑ����邽�� r_smc_entry.h �̓C���N���[�h���Ȃ�.
 */
#include "r_cg_macrodriver.h"
#include "Pin.h"
#include "Config_ICU/Config_ICU.h"
#include "Config_PORT/Config_PORT.h"
#include "Config_RSPI0/Config_RSPI0.h"


extern void r_Config_RSPI0_transmit_interrupt(void);
extern void r_Config_RSPI0_receive_interrupt(void);


uint8_t			TCP_SWBUFT[(TCP_MSS * 4)];
uint8_t			TCP_RWBUFT[(TCP_MSS * 4)];


void rspi_tx_handler(void)
{
	r_Config_RSPI0_transmit_interrupt();
}


void rspi_rx_handler(void)
{
	r_Config_RSPI0_receive_interrupt();
}


/*
 *  ���C���^�X�N
 */
#define LENGTH	11
uint8_t tx_buf[32];
uint8_t rx_buf[32];
uint8_t snd_buf[] = {0x01, 0x66, 0x00, 0x00, 0x00, 0x06, 0x01, 0x03, 0x00, 0x00, 0x00, 0x0A};
uint8_t rcv_buf[TCP_MSS];
volatile bool rspi_recieved = false;
void main_task(intptr_t exinf)
{
	ER ercd;
	T_IPV4EP src;
	T_IPV4EP dst;
	int count;
	int i;
	uint8_t msg[80];

	//unlock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

	R_Config_PORT_Create();
	R_Config_ICU_Create();
	R_Config_RSPI0_Create();

	//lock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY);

#if 0
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
#endif
    sil_wrb_mem(
    		(void *)(PORTC_PCR_ADDR),
			(uint8_t)(sil_reb_mem((void *)PORTC_PCR_ADDR) | PORT_PCR_B4_BIT)
	);
    sil_wrb_mem(
    		(void *)(PORTC_PCR_ADDR),
			(uint8_t)(sil_reb_mem((void *)PORTC_PCR_ADDR) | PORT_PCR_B5_BIT)
	);
    sil_wrb_mem(
    		(void *)(PORTC_PCR_ADDR),
			(uint8_t)(sil_reb_mem((void *)PORTC_PCR_ADDR) | PORT_PCR_B6_BIT)
	);
    sil_wrb_mem(
    		(void *)(PORTC_PCR_ADDR),
			(uint8_t)(sil_reb_mem((void *)PORTC_PCR_ADDR) | PORT_PCR_B7_BIT)
	);

	/*
	 *  PHY(KSZ8081MNX/RNB)�̃��Z�b�g
	 */
	PIN_WRITE(A,6) = 0;
	dly_tsk(10);
	PIN_WRITE(A,6) = 1;

	wup_tsk(ETHER_INPUT_TASK);

	//act_tsk(UDP_TASK);
	src.ipaddr = IPV4_ADDR_LOCAL;
	src.portno = 0xC010;
	dst.ipaddr = MAKE_IPV4_ADDR(192,168,0,1);
	dst.portno = 502;
	ercd = tcp_con_cep(ID_CEP0, &src, &dst, TMO_FEVR);
	if (ercd != E_OK) {
		syslog(LOG_NOTICE, "Error <- tcp_con_cep()");
	}

	/*
	 *  R_Config_RSPI0_Start();
	 */
	ena_int(INTNO_RSPI_TX);
	ena_int(INTNO_RSPI_RX);
	R_Config_RSPI0_Start();

	while (1) {
		/*
		 *  R_Config_RSPI0_Send_Receive(tx_buf, LENGTH, rx_buf);
		 */
		R_Config_RSPI0_Send_Receive(tx_buf, LENGTH, rx_buf);
		if (tslp_tsk(5000) == E_TMOUT) {
			syslog(LOG_NOTICE, "Timeout <- R_Config_RSPI0_Send_Receive()");
			continue;
		}
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
		ercd = tcp_snd_dat(ID_CEP0, (void *)snd_buf, sizeof(snd_buf), TMO_FEVR);
		if (ercd <= 0) {
			syslog(LOG_NOTICE, "Error <- tcp_snd_dat()");
			continue;
		}
		ercd = tcp_rcv_dat(ID_CEP0, (void *)rcv_buf, TCP_MSS, TMO_FEVR);
		if (ercd <= 0) {
			syslog(LOG_NOTICE, "Error <- tcp_rcv_dat()");
			continue;
		}
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
