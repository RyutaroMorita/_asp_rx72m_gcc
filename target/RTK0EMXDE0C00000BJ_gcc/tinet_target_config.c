/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id$
 */

/*
 *  �^�[�Q�b�g�ˑ����W���[���iRX72M�p�j
 */

#include <kernel.h>
#include <sil.h>
#include <tinet_defs.h>
#include <tinet_config.h>
#include "target_board.h"


/*
 * MAC�A�h���X�̐ݒ�
*/
uint8_t mac_addr[6] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };


/*
 *  rx72m_bus_init -- �^�[�Q�b�g�ˑ����̃o�X�̏�����
 */
void rx72m_bus_init(void)
{
	/*
	 *  �C�[�T�l�b�g�`���l��0��MII���[�h�ɐݒ�
	 */
	sil_wrb_mem(
			(void *)(MPC_PFENET_ADDR),
			(uint32_t)(sil_reb_mem((void *)MPC_PFENET_ADDR) | MPC_PFENET_PHYMODE0_BIT)
	);

	//unlock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

	/*
	 *  ���W���[���X�g�b�v�@�\�̐ݒ�
	 */
	sil_wrw_mem(
			(void *)(SYSTEM_MSTPCRB_ADDR),
			(uint32_t)(sil_rew_mem((void *)SYSTEM_MSTPCRB_ADDR) & ~SYSTEM_MSTPCRB_MSTPB15_BIT)
	);

	//lock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY);

	slp_tsk();	// ��� main.c ���� wup_tsk(ETHER_INPUT_TASK) �����
}


/*
 *  rx72m_inter_init -- �^�[�Q�b�g�ˑ����̊����݂̏�����
 */
void
rx72m_inter_init(void)
{
	/*
	 *  ---- KSZ8081MNX/RNB����̊��荞��(IRQ0:P10) ----
	 *
	 *  INTRP (�s�� 21) �́AKSZ8081MNX/RNB PHY ���W�X�^�̃X�e�[�^�X���X�V���ꂽ���Ƃ��O���R���g���[���ɒʒm���邽�߂Ɏg�p�����I�v�V�����̊��荞�ݐM���ł��B
	 *  ���W�X�^ 1Bh �̃r�b�g [15:8] �́AINTRP �M�����A�T�[�g���������L���܂��͖����ɂ��銄�荞�ݐ���r�b�g�ł��B
	 *  ���W�X�^ 1Bh �̃r�b�g [7:0] �́A�ǂ̊��荞�ݏ������������������������荞�݃X�e�[�^�X �r�b�g�ł��B
	 *  ���荞�݃X�e�[�^�X �r�b�g�́A���W�X�^ 1Bh �̓ǂݎ���ɃN���A����܂��B���W�X�^ 1Fh �̃r�b�g [9] �́A���荞�݃��x�����A�N�e�B�u �n�C�܂��̓A�N�e�B�u ���[�ɐݒ肵�܂��B
	 *  �f�t�H���g�̓A�N�e�B�u ���[�ł��BMII �Ǘ��o�X �I�v�V�����ɂ��AMAC �v���Z�b�T�� KSZ8081MNX/RNB ���䃌�W�X�^�ƃX�e�[�^�X ���W�X�^�Ɋ��S�ɃA�N�Z�X�ł��܂��B
	 *  ����ɁA���荞�݃s���ɂ��A�v���Z�b�T���X�e�[�^�X�ύX�̂��߂� PHY ���|�[�����O����K�v���Ȃ��Ȃ�܂��B
	 */
}


/*
 *  �߂�l�� TRUE ���w�肷��ƁATINET �ŏd������� MAC �A�h���X�� syslog �ɏo�͂��A
 *  �d������ɂ��d���������Ƃ�`����B
 *  FALSE ���w�肷��Ɖ������Ȃ��B
*/
bool_t arp_callback_duplicated(uint8_t *shost)
{
	/*
	 *  IP�A�h���X�̏d�������m�������̏���
	 */
	return false;
}
