/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2004 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2003-2004 by Platform Development Center
 *                                          RICOH COMPANY,LTD. JAPAN
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
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

/*
 *	RX72M UART�p�V���A��I/O���W���[��
 */
#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "target_board.h"
#include "target_serial.h"
#include "r_sci_rx_if.h"
#include "r_sci_rx_pinset.h"
#include "r_sci_rx_private.h"

ID g_siopid;
//sci_hdl_t g_uart_ctrl[TNUM_SIOP];

/*
 *  �V���A��I/O�|�[�g�������u���b�N�̒�`
 */
typedef struct sio_port_initialization_block {
	sci_hdl_t	hdl;
	uint8_t		chan;
} SIOPINIB;

/*
 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̒�`
 */
struct sio_port_control_block {
	const SIOPINIB*	p_siopinib; 	/* �V���A��I/O�|�[�g�������u���b�N */
	intptr_t		exinf;			/* �g����� */
	bool_t			openflag;		/* �I�[�v���ς݃t���O */
	bool_t			sendflag;		/* ���M�����݃C�l�[�u���t���O */
	bool_t			getready;		/* ��������M������� */
	bool_t			putready;		/* �����𑗐M�ł����� */
	bool_t			is_initialized; /* �f�o�C�X�������ς݃t���O */
};

/*
 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̃G���A
 */
static SIOPCB	siopcb_table[TNUM_SIOP];

/*  ���W�X�^�e�[�u�� */
static SIOPINIB siopinib_table[TNUM_SIOP];

/*
 *  �V���A��I/O�|�[�gID����Ǘ��u���b�N�����o�����߂̃}�N��
 */
#define INDEX_SIOP(siopid)	 ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	 (&(siopcb_table[INDEX_SIOP(siopid)]))
#define get_siopinib(siopid) (&(siopinib_table[INDEX_SIOP(siopid)]))

/*
 *  SIO�̃R�[���o�b�N�֐�
 */
void sio_callback(void *p_args)
{
	SIOPCB	*p_siopcb = get_siopcb(g_siopid);
	sci_cb_args_t *args;
	args = (sci_cb_args_t *)p_args;
	if (args->event == SCI_EVT_RX_CHAR)
	{
		/*
		 *  ��M�ʒm�R�[���o�b�N���[�`�����Ăяo���D
		 */
		sio_irdy_rcv(p_siopcb->exinf);
	}
	else
	if (args->event == SCI_EVT_TEI)
	{
		/*
		 *  ���M�\�R�[���o�b�N���[�`�����Ăяo���D
		 */
		sio_irdy_snd(p_siopcb->exinf);
	}
}

/*
 *  SIO�h���C�o�̏�����
 */
void sio_initialize(intptr_t exinf)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̏�����
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++){
		//siopinib_table[i].hdl = &g_uart_ctrl[i];
		siopinib_table[i].chan = (6 + i);	// SCI6��1�Ԗڂ̃|�[�g�Ƃ���
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
		p_siopcb->sendflag = false;
	}
}

/*
 *  �V���A��I/O�|�[�g�̃I�[�v��
 */
SIOPCB* sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;
	sci_cfg_t		cfg;

	/*
	 *  �V���A��I/O�����݂��}�X�N����D
	 *  (dis_int�֐��́A"\kernel\interrupt.c"�ɋL�q)
	 */
	dis_int(INTNO_SIO_TX);
	dis_int(INTNO_SIO_RX);
	dis_int(INTNO_SIO_TE);
	
	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;

	/*
	 *  �n�[�h�E�F�A�̏�����
	 *
	 *  ���ɏ��������Ă���ꍇ��, ��d�ɏ��������Ȃ�.
	 */
	if (!(p_siopcb->is_initialized)) {
		cfg.async.baud_rate = 9600;
		cfg.async.clk_src = SCI_CLK_INT;
		cfg.async.data_size = SCI_DATA_8BIT;
		cfg.async.parity_en = SCI_PARITY_OFF;
		cfg.async.parity_type = SCI_EVEN_PARITY;
		cfg.async.stop_bits = SCI_STOPBITS_1;
		cfg.async.int_priority = 3;

		R_SCI_Open(
				p_siopinib->chan,
				SCI_MODE_ASYNC,
				&cfg,
				sio_callback,
				(sci_hdl_t * const)&p_siopinib->hdl
		);
		// PORTB.PMR.BIT.B1 = 1U; // Please set the PMR bit after TE bit is set to 1.
		R_SCI_PinSet_SCI();

		p_siopcb->is_initialized = true;
	}

	p_siopcb->exinf = exinf;
	p_siopcb->getready = p_siopcb->putready = false;
	p_siopcb->openflag = true;

	/*
	 *  �V���A��I/O�����݂��}�X�N��������D
	 *  (ena_int�֐��́A"\kernel\interrupt.c"�ɋL�q)
	 */
	ena_int(INTNO_SIO_TX);
	ena_int(INTNO_SIO_RX);
	ena_int(INTNO_SIO_TE);

	return(p_siopcb);
}

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
void sio_cls_por(SIOPCB *p_siopcb)
{
	/*
	 *  �f�o�C�X�ˑ��̃N���[�Y�����D
	 */
	R_SCI_Close(p_siopcb->p_siopinib->hdl);

	p_siopcb->openflag = false;
	p_siopcb->is_initialized = false;

	/*
	 *  �V���A��I/O�����݂��}�X�N����D
	 */
	dis_int(INTNO_SIO_TX);
	dis_int(INTNO_SIO_RX);
	dis_int(INTNO_SIO_TE);
}

/*
 *  SIO�̊����݃n���h��
 */
void sio_tx_isr(intptr_t exinf)
{
	ID siopid = (ID)exinf;
	SIOPCB	*p_siopcb = get_siopcb(siopid);
	g_siopid = siopid;
	txi_handler(p_siopcb->p_siopinib->hdl);
}

/*
 *  SIO�̊����݃n���h��
 */
void sio_rx_isr(intptr_t exinf)
{
	ID siopid = (ID)exinf;
	SIOPCB	*p_siopcb = get_siopcb(siopid);
	g_siopid = siopid;
	rxi_handler(p_siopcb->p_siopinib->hdl);
}

/*
 *  SIO�̊����݃n���h��
 */
void sio_te_isr(intptr_t exinf)
{
	ID siopid = (ID)exinf;
	SIOPCB	*p_siopcb = get_siopcb(siopid);
	g_siopid = siopid;
	tei_handler(p_siopcb->p_siopinib->hdl);
}


/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
bool_t sio_snd_chr(SIOPCB *p_siopcb, char c)
{
	if (R_SCI_Send(p_siopcb->p_siopinib->hdl, (uint8_t*)&c, 1) != SCI_SUCCESS)
		return false;
	return true;
}

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
int_t sio_rcv_chr(SIOPCB *p_siopcb)
{
	int_t	c;
	R_SCI_Receive(p_siopcb->p_siopinib->hdl, (uint8_t*)&c, 1);
	return c;
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
void
sio_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		//*(uint8_t*)SCI_SCR_ADDR |= SCI_SCR_TEIE_BIT;
		*(uint8_t*)SCI_SCR_ADDR |= SCI_SCR_TIE_BIT;
		break;
	case SIO_RDY_RCV:
		*(uint8_t*)SCI_SCR_ADDR |= SCI_SCR_RIE_BIT;
		break;
	}
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
void
sio_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		//*(uint8_t*)SCI_SCR_ADDR &= ~SCI_SCR_TEIE_BIT;
		*(uint8_t*)SCI_SCR_ADDR &= ~SCI_SCR_TIE_BIT;
		break;
	case SIO_RDY_RCV:
		*(uint8_t*)SCI_SCR_ADDR &= ~SCI_SCR_RIE_BIT;
		break;
	}
}
