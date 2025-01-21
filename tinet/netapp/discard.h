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
 *  @(#) $Id: discard.h,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

#ifndef _DISCARD_H_
#define _DISCARD_H_

/* 
 *  DISCARD �T�[�o�E�N���C�A���g�̃X�^�b�N�T�C�Y
 */

#define TCP_DISCARD_SRV_STACK_SIZE	1024		/* TCP DISCARD �T�[�o�^�X�N�̃X�^�b�N�T�C�Y */
#define TCP_DISCARD_CLI_STACK_SIZE	1024		/* TCP DISCARD �N���C�A���g�^�X�N�̃X�^�b�N�T�C�Y */
#define UDP_DISCARD_CLI_STACK_SIZE	1024		/* UDP DISCARD �N���C�A���g�^�X�N�̃X�^�b�N�T�C�Y */

/* 
 *  DISCARD �T�[�o�E�N���C�A���g�̗D��x
 */

#define TCP_DISCARD_SRV_MAIN_PRIORITY	5	/* TCP DISCARD �T�[�o�^�X�N�̗D��x */
#define TCP_DISCARD_CLI_MAIN_PRIORITY	5	/* TCP DISCARD �N���C�A���g�^�X�N�̗D��x */
#define UDP_DISCARD_CLI_MAIN_PRIORITY	5	/* UDP DISCARD �N���C�A���g�^�X�N�̗D��x */

/*
 *  TCP ����M�E�C���h�o�b�t�@�T�C�Y
 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#define TCP_DISCARD_CLI_SWBUF_SIZE	((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)
#define TCP_DISCARD_SRV_RWBUF_SIZE	((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)

#else	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)

#define TCP_DISCARD_CLI_SWBUF_SIZE	(TCP_MSS)
#define TCP_DISCARD_SRV_RWBUF_SIZE	(TCP_MSS)

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_DISCARD_CLI_SWBUF_SIZE	(TCP6_MSS)
#define TCP_DISCARD_SRV_RWBUF_SIZE	(TCP6_MSS)

#endif	/* of #if defined(SUPPORT_INET6) */

#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

/*
 *  �ϐ�
 */

extern bool_t	tcp_discard_cli_valid;
extern bool_t	udp_discard_cli_valid;

/* TCP ����M�o�b�t�@ */

extern uint8_t tcp_discard_cli_swbuf[];
extern uint8_t tcp_discard_cli_rwbuf[];

extern uint8_t tcp_discard_srv_swbuf[];
extern uint8_t tcp_discard_srv_rwbuf[];

/*
 *  �^�X�N
 */

extern void tcp_discard_srv_task(intptr_t exinf);
extern void tcp_discard_cli_task(intptr_t exinf);

extern void udp_discard_cli_task(intptr_t exinf);

/*
 *  �֐�
 */

extern ER callback_nblk_tcp_discard_cli (ID cepid, FN fncd, void *p_parblk);

#endif	/* of #ifndef _DISCARD_H_ */
