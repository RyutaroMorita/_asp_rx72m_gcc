/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̏����𖞂������ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 *  @(#) $Id: if_ed.c,v 1.5.4.1 2015/02/05 02:12:02 abe Exp abe $
 */

/*
 * Copyright (c) 1995, David Greenman
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/i386/isa/if_ed.c,v 1.148.2.4 1999/09/25 13:08:18 nyan Exp $
 */

/*
 * Device driver for National Semiconductor DS8390/WD83C690 based ethernet
 *   adapters. By David Greenman, 29-April-1993
 *
 * Currently supports the Western Digital/SMC 8003 and 8013 series,
 *   the SMC Elite Ultra (8216), the 3Com 3c503, the NE1000 and NE2000,
 *   and a variety of similar clones.
 *
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "target_config.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_timer.h>
#include <net/net_count.h>
#include <net/net_buf.h>

#include "if_edreg.h"

/*
 *  ���� RAM �̃y�[�W�w��
 */

#define ED_INT_TXBUF_START	(ED_INT_RAM_BASE / ED_PAGE_SIZE)
#define ED_INT_TXBUF_STOP	(ED_INT_RAM_BASE / ED_PAGE_SIZE + IF_ED_TXBUF_PAGE_SIZE)
#define ED_INT_RXBUF_START	 ED_INT_TXBUF_STOP
#define ED_INT_RXBUF_STOP	((ED_INT_RAM_BASE + ED_INT_RAM_SIZE) / ED_PAGE_SIZE)

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�Ɉˑ�����\�t�g�E�F�A��� 
 */

typedef struct t_ed_softc {
	uint32_t	nic_addr;			/* NIC �̃x�[�X�A�h���X		*/
	uint32_t	asic_addr;			/* ASIC �̃x�[�X�A�h��		*/
	uint16_t	txb_len[NUM_IF_ED_TXBUF];	/* ���M�o�b�t�@�̃I�N�e�b�g��	*/
	uint8_t		txb_inuse;			/* �g�p���̑��M�o�b�t�@		*/
	uint8_t		txb_insend;			/* ���M���̑��M�o�b�t�@		*/
	uint8_t		txb_write;			/* �������ޑ��M�o�b�t�@		*/
	uint8_t		txb_send;			/* ���M���鑗�M�o�b�t�@		*/
	uint8_t		rxb_read;			/* �ǂݍ��ގ�M�y�[�W		*/
	} T_ED_SOFTC;

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�̃\�t�g�E�F�A���
 */

/* �l�b�g���[�N�C���^�t�F�[�X�Ɉˑ�����\�t�g�E�F�A��� */

static T_ED_SOFTC ed_softc = {
	ED_BASE_ADDRESS + ED_NIC_OFFSET,	/* NIC �̃x�[�X�A�h���X		*/
	ED_BASE_ADDRESS + ED_ASIC_OFFSET,	/* ASIC �̃x�[�X�A�h���X		*/
	};

/* �l�b�g���[�N�C���^�t�F�[�X�Ɉˑ����Ȃ��\�t�g�E�F�A��� */


T_IF_SOFTC if_softc = {
	{},					/* �l�b�g���[�N�C���^�t�F�[�X�̃A�h���X	*/
	0,					/* ���M�^�C���A�E�g			*/
	&ed_softc,				/* �f�B�o�C�X�ˑ��̃\�t�g�E�F�A���	*/
	SEM_IF_ED_SBUF_READY,			/* ���M�Z�}�t�H			*/
	SEM_IF_ED_RBUF_READY,			/* ��M�Z�}�t�H			*/

#ifdef SUPPORT_INET6

	IF_MADDR_INIT,				/* �}���`�L���X�g�A�h���X���X�g	*/

#endif	/* of #ifdef SUPPORT_INET6 */
	};

/*
 *  �Ǐ��ϐ�
 */

static void ed_pio_readmem (T_ED_SOFTC *sc, uint32_t src, uint8_t *dst, uint16_t amount);
static T_NET_BUF *ed_get_frame (T_ED_SOFTC *sc, uint32_t ring, uint16_t len);
static void ed_xmit (T_IF_SOFTC *ic);
static void ed_stop (T_ED_SOFTC *sc);
static void ed_init_sub (T_IF_SOFTC *ic);
static void ed_setrcr (T_IF_SOFTC *ic);

#ifdef SUPPORT_INET6

static uint32_t ds_crc (uint8_t *addr);
static void ds_getmcaf (T_IF_SOFTC *ic, uint32_t *mcaf);

/*
 *  ds_crc -- �C�[�T�l�b�g�A�h���X�� CRC ���v�Z����B
 */

#define POLYNOMIAL	0x04c11db6

static uint32_t
ds_crc (uint8_t *addr)
{
	uint32_t	crc = ULONG_C(0xffffffff);
	int_t		carry, len, bit;
	uint8_t		byte;

	for (len = ETHER_ADDR_LEN; len -- > 0; ) {
		byte = *addr ++;
		for (bit = 8; bit -- > 0; ) {
			carry   = ((crc & ULONG_C(0x80000000)) ? 1 : 0) ^ (byte & UINT_C(0x01));
			crc   <<= 1;
			byte   >>= 1;
			if (carry)
				crc = (crc ^ POLYNOMIAL) | carry;
			}
		}
	return crc;
	}

#undef POLYNOMIAL

/*
 *  ds_getmcaf -- �}���`�L���X�g�A�h���X�̃��X�g����}���`�L���X�g�A�h���X
 *                �t�B���^���v�Z����B
 */

static void
ds_getmcaf (T_IF_SOFTC *ic, uint32_t *mcaf)
{
	uint32_t	count, index;
	uint8_t		*af = (uint8_t*)mcaf;

	mcaf[0] = mcaf[1] = 0;

	for (count = MAX_IF_MADDR_CNT; count -- > 0; ) {
		index = ds_crc(ic->maddrs[count].lladdr) >> 26;
		af[index >> 3] |= 1 << (index & 7);
		}
	}

/*
 * ed_setrcr -- ��M�\�����W�X�^ (RCR) ��ݒ肷��B
 */

static void
ed_setrcr (T_IF_SOFTC *ic)
{
	T_ED_SOFTC	*sc = ic->sc;
	int_t		ix;
	uint32_t	mcaf[2];

	/* ���W�X�^�y�[�W 1 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	                 ED_CR_RD2 | ED_CR_PAGE1 | ED_CR_STP);

	/* �}���`�L���X�g�t�B���^���v�Z����B*/
	ds_getmcaf(ic, mcaf);

	/* �}���`�L���X�g�̎�M�ݒ� */
	for (ix = 0; ix < 8; ix ++)
		sil_wrb_mem((void*)(sc->nic_addr + ED_P1_MAR(ix)), ((uint8_t *)mcaf)[ix]);

	/* ���W�X�^�y�[�W 0 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STP);

	/* �}���`�L���X�g�ƃ��j�L���X�g�A�h���X�̂ݎ�M����悤�ɐݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RCR), ED_RCR_AM);

	/* NIC ���N������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);
	}

/*
 * ed_addmulti -- �}���`�L���X�g�A�h���X��ǉ�����B
 */

ER
ed_addmulti (T_IF_SOFTC *ic)
{
	ed_setrcr(ic);
	return E_OK;
	}

#endif	/* of #ifdef SUPPORT_INET6 */

/*
 * ed_pio_readmem -- �v���O���� I/O ���g���� NIC �̃f�[�^��ǂݍ���
 */

static void
ed_pio_readmem (T_ED_SOFTC *sc, uint32_t src, uint8_t *dst, uint16_t amount)
{
	/* ���W�X�^�y�[�W 0 ��I�����ADMA ���~����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);

	/* DMA �]������ݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RBCR0), amount);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RBCR1), amount >> 8);

	/* NIC �������̓]�����A�h���X��ݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RSAR0), src);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RSAR1), src >> 8);

	/* DMA �ǂݍ��݂�I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD0 | ED_CR_PAGE0 | ED_CR_STA);

	/* NIC ����������ǂݍ��� */
	while (amount -- > 0)
		*dst ++ = sil_reb_mem((void*)(sc->asic_addr + ED_DATA_OFFSET));
	}

/*
 * ed_pio_writemem -- �v���O���� I/O ���g���� NIC �Ƀf�[�^����������
 */

static void
ed_pio_writemem (T_ED_SOFTC *sc, uint8_t *src, uint32_t dst, uint16_t amount)
{
	/* ���W�X�^�y�[�W 0 ��I�����ADMA ���~����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);

	/* DMA �]������ݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RBCR0), amount);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RBCR1), amount >> 8);

	/* NIC �������̓]����A�h���X��ݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RSAR0), dst);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RSAR1), dst >> 8);

	/* DMA �����݂�I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	                 ED_CR_RD1 | ED_CR_PAGE0 | ED_CR_STA);

	/* NIC �������ɏ������� */
	while (amount -- > 0)
		sil_wrb_mem((void*)(sc->asic_addr + ED_DATA_OFFSET), *src ++);
	}

/*
 * ed_get_frame -- Ethernet �t���[������͂���B
 */

static T_NET_BUF *
ed_get_frame (T_ED_SOFTC *sc, uint32_t ring, uint16_t len)
{
	T_NET_BUF	*input = NULL;
	uint16_t	sublen, align;
	uint8_t		*dst;
	ER		error;

	/*
	 *  +-----------+--------+---------+---------+
	 *  | Ehter HDR | IP HDR | TCP HDR | TCP SDU |
	 *  +-----------+--------+---------+---------+
	 *        14        20        20        n
	 *   <----------------- len ---------------->
	 *              ^
	 *              t_net_buf �� 4 �I�N�e�b�g���E�ɃA���C������Ă���B
	 *
	 *  tcp_input �� udp_input �ł́A�[���w�b�_�� SDU �Ń`�F�b�N�T����
	 *  �v�Z���邪�An �� 4 �I�N�e�b�g���E�ɂȂ�悤�� SDU �̌��� 0 ��
	 *  �p�b�f�B���O����B���̕����l������ net_buf ���l�����Ȃ���΂Ȃ�Ȃ��B
	 */
	align = ((((len - sizeof(T_IF_HDR)) + 3) >> 2) << 2) + sizeof(T_IF_HDR);

	if ((error = tget_net_buf(&input, align, TMO_IF_ED_GET_NET_BUF)) == E_OK && input != NULL) {
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_PACKETS], 1);
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_OCTETS],  len);
		dst = input->buf + IF_ETHER_NIC_HDR_ALIGN;
		if (ring + len > ED_INT_RAM_BASE + ED_INT_RAM_SIZE) {
			sublen = (ED_INT_RAM_BASE + ED_INT_RAM_SIZE) - ring;
			ed_pio_readmem(sc, ring, dst, sublen);
			len -= sublen;
			dst += sublen;
			ring = ED_INT_RXBUF_START * ED_PAGE_SIZE;
			}
		ed_pio_readmem(sc, ring, dst, len);
		}
	else {
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
		NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_NO_BUFS], 1);
		}
	return input;
	}

/*
 *  ed_xmit -- �t���[���𑗐M����B
 *
 *    ����: NIC ���荞�݋֎~��ԂŌĂяo�����ƁB
 */

static void
ed_xmit (T_IF_SOFTC *ic)
{
	T_ED_SOFTC *sc = ic->sc;

	/* ���W�X�^�y�[�W 0 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);

	/* ���M����y�[�W��ݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_TPSR),
	            ED_INT_TXBUF_START + sc->txb_send * NUM_IF_ED_TXBUF_PAGE);

	/* ���M����I�N�e�b�g����ݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_TBCR0), sc->txb_len[sc->txb_send]);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_TBCR1), sc->txb_len[sc->txb_send] >> 8);

	/* ���M����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_TXP | ED_CR_STA);

	/* ���M�o�b�t�@��؂�ւ���B*/
	sc->txb_send ++;
	if (sc->txb_send == NUM_IF_ED_TXBUF)
		sc->txb_send = 0;

	sc->txb_insend ++;

	/* ���M�^�C���A�E�g��ݒ肷��B*/
	ic->timer = TMO_IF_ED_XMIT;
	}

/*
 *  ed_stop -- ed �l�b�g���[�N�C���^�t�F�[�X���~����B
 *
 *    ����: NIC ���荞�݋֎~��ԂŌĂяo�����ƁB
 */

static void
ed_stop (T_ED_SOFTC *sc)
{
	int_t wait;

	/* DMA ���~����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STP);

	/* NIC ����~��ԂɂȂ�܂ő҂B�������A5[ms]������ɂ��Ă���B*/
	for (wait = 5; ((sil_reb_mem((void*)(sc->nic_addr + ED_P0_ISR)) & ED_ISR_RST) == 0) && wait -- > 0; )
		syscall(dly_tsk(1));
	}

/*
 *  ed_init_sub -- ed �l�b�g���[�N�C���^�t�F�[�X�̏�����
 *
 *    ����: NIC ���荞�݋֎~��ԂŌĂяo�����ƁB
 */

static void
ed_init_sub (T_IF_SOFTC *ic)
{
	T_ED_SOFTC	*sc = ic->sc;
	int_t		ix;

	/* ��M�y�[�W�̐ݒ� */
	sc->rxb_read = ED_INT_RXBUF_START + 1;

	/* ���M�o�b�t�@�̐ݒ� */
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_ERR_PACKETS], sc->txb_inuse);
	sc->txb_inuse  = 0;
	sc->txb_insend = 0;
	sc->txb_write  = 0;
	sc->txb_send   = 0;
	
	/* ���M�^�C���A�E�g�����Z�b�g����B*/
	ic->timer = 0;

	/* �C���^�t�F�[�X���~����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR), ED_CR_PAGE0 | ED_CR_STP);

	/*
	 *  DCR ��ݒ肷��B
	 *    �EFIFO �̂������l�� 8
	 *    �E���[�v�o�b�N���[�h
	 */
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_DCR), ED_DCR_FT1 | ED_DCR_LS);

	/* RBCR ���N���A�[����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RBCR0), 0);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RBCR1), 0);

	/* ���̓t���[����ۑ����Ȃ��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RCR), ED_RCR_MON);

	/* �������[�v�o�b�N���[�h�ɐݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_TCR), ED_TCR_LB0);

	/* ����M�����O�o�b�t�@�̐ݒ� */
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_TPSR),   ED_INT_TXBUF_START);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_PSTART), ED_INT_RXBUF_START);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_PSTOP),  ED_INT_RXBUF_STOP);
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_BNRY),   ED_INT_RXBUF_START);

	/* �S�Ă̊��荞�݃t���O�����Z�b�g����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_ISR), 0xff);

	/*
	 *  ���荞�݂�������B
	 *    �E����M����
	 *    �E����M�G���[
	 *    �E��M�I�[�o�[���C�g
	 */
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_IMR),
	            ED_IMR_PRX | ED_IMR_PTX | ED_IMR_RXE | ED_IMR_TXE | ED_IMR_OVW);

	/* ���W�X�^�y�[�W 1 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE1 | ED_CR_STP);

	/* MAC �A�h���X��ݒ肷��B*/
	for (ix = 0; ix < ETHER_ADDR_LEN; ix ++)
		sil_wrb_mem((void*)(sc->nic_addr + ED_P1_PAR(ix)), ic->ifaddr.lladdr[ix]);

	/* �t���[�����������ރy�[�W��ݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P1_CURR), sc->rxb_read);

 	/* ��M�\�����W�X�^ (RCR) ��ݒ肷��B*/
 	ed_setrcr(ic);

	/* �������[�v�o�b�N���[�h����ʂ���B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_TCR), 0);
	
	/* ���M�\�Z�}�t�H������������B*/
	for (ix = NUM_IF_ED_TXBUF; ix --; )
		sig_sem(ic->semid_txb_ready);

#if defined(TARGET_KERNEL_ASP)

	/* �^�[�Q�b�g�ˑ����̊����ݏ����� */
	ed_inter_init();

#endif	/* of #if defined(TARGET_KERNEL_ASP) */

#if defined(TARGET_KERNEL_JSP) && TKERNEL_PRVER >= 0x1042u	/* JSP-1.4.2 �ȍ~ */

	/* �^�[�Q�b�g�ˑ����̊����ݏ����� */
	ed_inter_init();

#endif	/* of #if defined(TARGET_KERNEL_JSP) && TKERNEL_PRVER >= 0x1042u */

	}

#ifndef SUPPORT_INET6

/*
 * ed_setrcr -- ��M�\�����W�X�^ (RCR) ��ݒ肷��B
 */

static void
ed_setrcr (T_IF_SOFTC *ic)
{
	T_ED_SOFTC	*sc = ic->sc;
	int_t		ix;

	/* ���W�X�^�y�[�W 1 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE1 | ED_CR_STP);

#ifdef IF_ED_CFG_ACCEPT_ALL

	/* �}���`�L���X�g�̎�M�ݒ� */
	for (ix = 0; ix < 8; ix ++)

		/* �}���`�L���X�g��S�Ď�M����B*/
		sil_wrb_mem((void*)(sc->nic_addr + ED_P1_MAR(ix)), 0xff);

	/* ���W�X�^�y�[�W 0 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	                 ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STP);

	/* �}���`�L���X�g�ƃG���[�t���[������M����悤�ɐݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RCR),
	            ED_RCR_PRO | ED_RCR_AM | ED_RCR_AB |ED_RCR_SEP);

#else	/* of #ifdef IF_ED_CFG_ACCEPT_ALL */

	/* �}���`�L���X�g�̎�M�ݒ� */
	for (ix = 0; ix < 8; ix ++)

		/* �}���`�L���X�g��S�Ď�M���Ȃ��B*/
		sil_wrb_mem((void*)(sc->nic_addr + ED_P1_MAR(ix)), 0x00);

	/* ���W�X�^�y�[�W 0 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STP);

	/* �����ƃu���[�h�L���X�g�̂ݎ�M����悤�ɐݒ肷��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RCR), ED_RCR_AB);

#endif	/* of #ifdef IF_ED_CFG_ACCEPT_ALL */

	/* NIC ���N������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);
	}

#endif	/* of #ifndef SUPPORT_INET6 */

/*
 * ed_reset -- ed �l�b�g���[�N�C���^�t�F�[�X�����Z�b�g����B
 */

void
ed_reset (T_IF_SOFTC *ic)
{
#ifdef TARGET_KERNEL_JSP
	IPM	ipm;
#endif

	/* NIC ����̊��荞�݂��֎~����B*/
#ifdef TARGET_KERNEL_JSP
	ipm = ed_dis_inter();
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(dis_int(INTNO_IF_ED));
#endif

	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_RESETS], 1);
	ed_stop(ic->sc);
	ed_init_sub(ic);

	/* NIC ����̊��荞�݂�������B*/
#ifdef TARGET_KERNEL_JSP
	ed_ena_inter(ipm);
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(ena_int(INTNO_IF_ED));
#endif
	}

/*
 *  get_ed_softc -- �l�b�g���[�N�C���^�t�F�[�X�̃\�t�g�E�F�A����Ԃ��B
 */

T_IF_SOFTC *
ed_get_softc (void)
{
	return &if_softc;
	}

/*
 * ed_watchdog -- ed �l�b�g���[�N�C���^�t�F�[�X�̃��b�`�h�b�O�^�C���A�E�g
 */

void
ed_watchdog (T_IF_SOFTC *ic)
{
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_ERR_PACKETS], 1);
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_TIMEOUTS], 1);
	ed_reset(ic);
	}

/*
 * ed_probe -- ed �l�b�g���[�N�C���^�t�F�[�X�̌��o
 */

void
ed_probe (T_IF_SOFTC *ic)
{
#ifdef ED_CFG_HSB8S2638
	static const uint8_t mac_order[] = { 3, 1, 7, 5, 11, 9 };
#else	/* #ifdef ED_CFG_HSB8S2638 */
	static const uint8_t mac_order[] = { 1, 3, 5, 7, 9, 11 };
#endif	/* #ifdef ED_CFG_HSB8S2638 */

	uint8_t		romdata[ETHER_ADDR_LEN * 2], tmp;
	T_ED_SOFTC	*sc = ic->sc;
	int_t		ix;

#if defined(TARGET_KERNEL_ASP)

	/* �^�[�Q�b�g�ˑ����̃o�X�̏����� */
	ed_bus_init();

#endif	/* of #if defined(TARGET_KERNEL_ASP) */

#if defined(TARGET_KERNEL_JSP) && TKERNEL_PRVER >= 0x1042u	/* JSP-1.4.2 �ȍ~ */

	/* �^�[�Q�b�g�ˑ����̃o�X�̏����� */
	ed_bus_init();

#endif	/* of #if defined(TARGET_KERNEL_JSP) && TKERNEL_PRVER >= 0x1042u */

	/* ���Z�b�g����B*/
	tmp = sil_reb_mem((void*)(sc->asic_addr + ED_RESET_OFFSET));
	sil_wrb_mem((void*)(sc->asic_addr + ED_RESET_OFFSET), tmp);
	dly_tsk(5);

	/* DMA ���~����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STP);
	dly_tsk(5);

	/* ���̓t���[����ۑ����Ȃ��B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_RCR), ED_RCR_MON);

	/*
	 *  DCR ��ݒ肷��B
	 *    �EFIFO �̂������l�� 8
	 *    �E���[�v�o�b�N���[�h
	 */
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_DCR), ED_DCR_FT1 | ED_DCR_LS);

	/* MAC �A�h���X��ǂݍ��ށB*/
	ed_pio_readmem(sc, 0, romdata, ETHER_ADDR_LEN * 2);
	for (ix = 0; ix < ETHER_ADDR_LEN; ix ++)
		ic->ifaddr.lladdr[ix] = romdata[mac_order[ix]];

	/* �S�Ă̊��荞�݃t���O�����Z�b�g����B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_ISR), 0xff);
	}

/*
 * ed_init -- ed �l�b�g���[�N�C���^�t�F�[�X�̏�����
 */

void
ed_init (T_IF_SOFTC *ic)
{
#ifdef TARGET_KERNEL_JSP
	IPM	ipm;
#endif

	/* NIC ����̊��荞�݂��֎~����B*/
#ifdef TARGET_KERNEL_JSP
	ipm = ed_dis_inter();
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(dis_int(INTNO_IF_ED));
#endif

	/* ed_init �{�̂��Ăяo���B*/
	ed_init_sub(ic);

	/* NIC ����̊��荞�݂�������B*/
#ifdef TARGET_KERNEL_JSP
	ed_ena_inter(ipm);
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(ena_int(INTNO_IF_ED));
#endif
	}

/*
 * ed_read -- �t���[���̓ǂݍ���
 */

T_NET_BUF *
ed_read (T_IF_SOFTC *ic)
{
	T_ED_FRAME_HDR	frame_hdr;
	T_ED_SOFTC	*sc = ic->sc;
	T_NET_BUF	*input = NULL;
	uint32_t	frame_ptr;
	int_t		len;
	uint8_t		boundry;
	uint8_t		curr;
#ifdef TARGET_KERNEL_JSP
	IPM	ipm;
#endif

	/* NIC ����̊��荞�݂��֎~����B*/
#ifdef TARGET_KERNEL_JSP
	ipm = ed_dis_inter();
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(dis_int(INTNO_IF_ED));
#endif

	/* ���W�X�^�y�[�W 1 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE1 | ED_CR_STA);

	curr = sil_reb_mem((void*)(sc->nic_addr + ED_P1_CURR));
	if (sc->rxb_read != curr) {

		/* ��M�t���[���̐擪�𓾂�B*/
		frame_ptr = sc->rxb_read * ED_PAGE_SIZE;

		/* ��M�t���[���w�b�_�\���̂����o���B*/
		ed_pio_readmem(sc, frame_ptr, (char *)&frame_hdr, sizeof(frame_hdr));

#if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN

		frame_hdr.count = (frame_hdr.count << 8) | (frame_hdr.count >> 8);

#endif	/* of #if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN */

		len = frame_hdr.count;
		if (len >  sizeof(T_ED_FRAME_HDR) &&
		    len <= IF_MTU + sizeof(T_ETHER_HDR) + sizeof(T_ED_FRAME_HDR) &&
		    frame_hdr.next >= ED_INT_RXBUF_START &&
		    frame_hdr.next <  ED_INT_RXBUF_STOP) {
			input = ed_get_frame(sc, frame_ptr + sizeof(T_ED_FRAME_HDR),
			                               len - sizeof(T_ED_FRAME_HDR));
			}
		else {
			/* ��M�G���[�ƃ��Z�b�g���L�^����B*/
			NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
			NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_RESETS], 1);
			ed_stop(sc);
			ed_init_sub(ic);

			/* NIC ����̊��荞�݂�������B*/
#ifdef TARGET_KERNEL_JSP
			ed_ena_inter(ipm);
#endif
#ifdef TARGET_KERNEL_ASP
			syscall(ena_int(INTNO_IF_ED));
#endif
			return NULL;
			}

		/* �t���[���|�C���^���X�V����B*/
		sc->rxb_read = frame_hdr.next;

		/* ���W�X�^�y�[�W 0 ��I������B*/
		sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
		            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);

		/* NIC �̋��E�|�C���^���X�V����B*/
		boundry = sc->rxb_read - 1;
		if (boundry < ED_INT_RXBUF_START)
			boundry = ED_INT_RXBUF_STOP - 1;
		sil_wrb_mem((void*)(sc->nic_addr + ED_P0_BNRY), boundry);

		/* ���W�X�^�y�[�W 1 ��I������B*/
		sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
		            ED_CR_RD2 | ED_CR_PAGE1 | ED_CR_STA);
		}

	/* ��M�����O�o�b�t�@�Ƀf�[�^���c���Ă���΁A��M�������p������B*/
	curr = sil_reb_mem((void*)(sc->nic_addr + ED_P1_CURR));
	if (sc->rxb_read != curr)
		sig_sem(ic->semid_rxb_ready);

	/* NIC ����̊��荞�݂�������B*/
#ifdef TARGET_KERNEL_JSP
	ed_ena_inter(ipm);
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(ena_int(INTNO_IF_ED));
#endif

	return input;
	}

/*
 * ed_start -- ���M�t���[�����o�b�t�@�����O����B
 */

void
ed_start (T_IF_SOFTC *ic, T_NET_BUF *output)
{
	T_ED_SOFTC	*sc = ic->sc;
#ifdef TARGET_KERNEL_JSP
	IPM	ipm;
#endif

	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_PACKETS], 1);
	NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_OCTETS],  output->len);

	/* NIC ����̊��荞�݂��֎~����B*/
#ifdef TARGET_KERNEL_JSP
	ipm = ed_dis_inter();
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(dis_int(INTNO_IF_ED));
#endif

	/* ���M�o�b�t�@�ɏ������ށB*/
	ed_pio_writemem(sc, output->buf + IF_ETHER_NIC_HDR_ALIGN,
	                ED_INT_RAM_BASE + sc->txb_write * NUM_IF_ED_TXBUF_PAGE * ED_PAGE_SIZE,
	                output->len);

	/* ���M�o�b�t�@�ɏ������񂾃I�N�e�b�g�����L�^����B*/
	if (output->len > ETHER_MIN_LEN - ETHER_CRC_LEN)
		sc->txb_len[sc->txb_write] = output->len;
	else
		sc->txb_len[sc->txb_write] = ETHER_MIN_LEN - ETHER_CRC_LEN;

	/* ���M�o�b�t�@��؂�ւ���B*/
	sc->txb_write ++;
	if (sc->txb_write == NUM_IF_ED_TXBUF)
		sc->txb_write = 0;

	sc->txb_inuse ++;

	/* �������M���łȂ���΁A���M���J�n����B*/
	if (sc->txb_insend == 0)
		ed_xmit(ic);

	/* NIC ����̊��荞�݂�������B*/
#ifdef TARGET_KERNEL_JSP
	ed_ena_inter(ipm);
#endif
#ifdef TARGET_KERNEL_ASP
	syscall(ena_int(INTNO_IF_ED));
#endif
	}

/*
 *  NIC ���荞�݃n���h��
 */

void
if_ed_handler (void)
{
	T_ED_SOFTC	*sc;
	T_IF_SOFTC	*ic;
	uint8_t		isr, tsr;
	uint16_t	collisions;

	ic = &if_softc;
	sc = ic->sc;

	/* ���W�X�^�y�[�W 0 ��I������B*/
	sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
	            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);

	isr = sil_reb_mem((void*)(sc->nic_addr + ED_P0_ISR));

	if (isr != 0) {

		/* �S�Ă̊��荞�݃t���O�����Z�b�g����B*/
		sil_wrb_mem((void*)(sc->nic_addr + ED_P0_ISR), isr);

		if (isr & (ED_ISR_PTX | ED_ISR_TXE)) {
			collisions = sil_reb_mem((void*)(sc->nic_addr + ED_P0_NCR)) & 0x0f;

			/* ���M���� */
			tsr = sil_reb_mem((void*)(sc->nic_addr + ED_P0_TSR));
			if (isr & ED_ISR_TXE) {

				/* ���M�G���[���L�^����B*/
				if ((tsr & ED_TSR_ABT) && (collisions == 0)) {
					/*
					 * �R���W������ 16 �̂Ƃ��AP_NCR �� 0�A
					 * TSR_ABT �� 1 �ɂȂ�B
					 */
					collisions = 16;
					}
				NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_OUT_ERR_PACKETS], 1);
				}

			if (sc->txb_insend)
				sc->txb_insend --;
			if (sc->txb_inuse)
				sc->txb_inuse  --;

			/* ���M�^�C���A�E�g�����Z�b�g����B*/
			ic->timer = 0;

			/* �܂����M�o�b�t�@�Ɏc���Ă���Α��M����B*/
			if (sc->txb_inuse)
				ed_xmit(ic);

			if (isig_sem(ic->semid_txb_ready) != E_OK)
				NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_TXB_QOVRS], 1);

			/* �R���W�������L�^����B*/
			NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_COLS], collisions);
			}

		if (isr & (ED_ISR_PRX | ED_ISR_RXE | ED_ISR_OVW)) {
			if (isr & ED_ISR_OVW) {

				/* �㏑���G���[�ƃ��Z�b�g���L�^����B*/
				NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
				NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_RESETS], 1);

				/* DMA ���~����B*/
				sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
				            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STP);
				ed_init_sub(ic);
				}
			else {
				if (isr & ED_ISR_RXE) {

					/* ��M�G���[���L�^����B*/
					NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_IN_ERR_PACKETS], 1);
					}
				/* ��M���荞�ݏ��� */
				if (isig_sem(ic->semid_rxb_ready) != E_OK)
					NET_COUNT_ETHER_NIC(net_count_ether_nic[NC_ETHER_NIC_RXB_QOVRS], 1);
				}
			}

		/* ���W�X�^�y�[�W 0 ��I������B*/
		sil_wrb_mem((void*)(sc->nic_addr + ED_P0_CR),
		            ED_CR_RD2 | ED_CR_PAGE0 | ED_CR_STA);

		/* �l�b�g���[�N�L�^�J�E���^���I�[�o�t���[�����烊�Z�b�g����B*/
		if (isr & ED_ISR_CNT) {
			(void)sil_reb_mem((void*)(sc->nic_addr + ED_P0_CNTR0));
			(void)sil_reb_mem((void*)(sc->nic_addr + ED_P0_CNTR1));
			(void)sil_reb_mem((void*)(sc->nic_addr + ED_P0_CNTR2));
			}
		}

	/* �^�[�Q�b�g�ˑ����̊����݃N���A */
#ifdef TARGET_KERNEL_JSP
	ed_inter_clear();
#endif
	}
