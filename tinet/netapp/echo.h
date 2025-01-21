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
 *  @(#) $Id: echo.h,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

#ifndef _ECHO_H_
#define _ECHO_H_

/* 
 *  ECHO �N���C�A���g�E�T�[�o�̃X�^�b�N�T�C�Y
 */

#define TCP_ECHO_SRV_STACK_SIZE		1024		/* TCP ECHO �T�[�o�^�X�N�̃X�^�b�N�T�C�Y		*/

#ifdef TOPPERS_S810_CLG3_85
#define TCP_ECHO_CLI_RCV_STACK_SIZE	512		/* TCP ECHO �N���C�A���g��M�^�X�N�̃X�^�b�N�T�C�Y	*/
#define TCP_ECHO_CLI_SND_STACK_SIZE	512		/* TCP ECHO �N���C�A���g���M�^�X�N�̃X�^�b�N�T�C�Y	*/
#else	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define TCP_ECHO_CLI_RCV_STACK_SIZE	1024		/* TCP ECHO �N���C�A���g��M�^�X�N�̃X�^�b�N�T�C�Y	*/
#define TCP_ECHO_CLI_SND_STACK_SIZE	1024		/* TCP ECHO �N���C�A���g���M�^�X�N�̃X�^�b�N�T�C�Y	*/
#endif	/* of #ifdef TOPPERS_S810_CLG3_85 */

#define UDP_ECHO_SRV_STACK_SIZE		1024		/* UDP ECHO �T�[�o�^�X�N�̃X�^�b�N�T�C�Y		*/
#define UDP_ECHO_CLI_STACK_SIZE		1024		/* UDP ECHO �N���C�A���g�^�X�N�̃X�^�b�N�T�C�Y	*/

/* 
 *  ECHO �N���C�A���g�E�T�[�o�̗D��x
 */

#define TCP_ECHO_SRV_MAIN_PRIORITY	5		/* TCP ECHO �T�[�o�^�X�N�̗D��x			*/
#define TCP_ECHO_CLI_RCV_MAIN_PRIORITY	5		/* TCP ECHO �N���C�A���g��M�^�X�N�̗D��x		*/
#define TCP_ECHO_CLI_SND_MAIN_PRIORITY	5		/* TCP ECHO �N���C�A���g���M�^�X�N�̗D��x		*/

#define UDP_ECHO_SRV_MAIN_PRIORITY	5		/* UDP ECHO �T�[�o�^�X�N�̗D��x			*/
#define UDP_ECHO_CLI_MAIN_PRIORITY	5		/* UDP ECHO �N���C�A���g�^�X�N�̗D��x		*/

/*
 *  TCP ����M�E�C���h�o�b�t�@�T�C�Y
 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#define TCP_ECHO_CLI_SWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)
#define TCP_ECHO_CLI_RWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)

#define TCP_ECHO_SRV_SWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*2)
#define TCP_ECHO_SRV_RWBUF_SIZE		((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*2)

#else	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)

#define TCP_ECHO_CLI_SWBUF_SIZE		(TCP_MSS)
#define TCP_ECHO_CLI_RWBUF_SIZE		(TCP_MSS)

#define TCP_ECHO_SRV_SWBUF_SIZE		(TCP_MSS)
#define TCP_ECHO_SRV_RWBUF_SIZE		(TCP_MSS)

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_ECHO_CLI_SWBUF_SIZE		(TCP6_MSS)
#define TCP_ECHO_CLI_RWBUF_SIZE		(TCP6_MSS)

#define TCP_ECHO_SRV_SWBUF_SIZE		(TCP6_MSS)
#define TCP_ECHO_SRV_RWBUF_SIZE		(TCP6_MSS)

#endif	/* of #if defined(SUPPORT_INET6) */

#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

/*
 *  �^�X�N��
 */

#if !(defined(USE_TCP_ECHO_SRV1) && !defined(USE_TCP_NON_BLOCKING) && defined(USE_COPYSAVE_API))

#undef  NUM_TCP_ECHO_SRV_TASKS
#define NUM_TCP_ECHO_SRV_TASKS		1

#endif	/* of #if !(defined(USE_TCP_ECHO_SRV1) && !defined(USE_TCP_NON_BLOCKING) && defined(USE_COPYSAVE_API)) */

/*
 *  �ϐ�
 */

extern bool_t	tcp_echo_cli_valid;
extern bool_t	udp_echo_cli_valid;

/* TCP ����M�o�b�t�@ */

extern uint8_t tcp_echo_cli_swbuf[];
extern uint8_t tcp_echo_cli_rwbuf[];

#ifdef _TCP_H_

extern uint8_t tcp_echo_srv_swbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_SWBUF_SIZE];
extern uint8_t tcp_echo_srv_rwbuf[NUM_TCP_ECHO_SRV_TASKS][TCP_ECHO_SRV_RWBUF_SIZE];

#endif	/* of #ifdef _TCP_H_ */

/*
 *  �^�X�N
 */

extern void	tcp_echo_srv_task(intptr_t exinf);
extern void	tcp_echo_srv_rcv_task(intptr_t exinf);
extern void	tcp_echo_srv_snd_task(intptr_t exinf);
extern void	tcp_echo_cli_rcv_task(intptr_t exinf);
extern void	tcp_echo_cli_snd_task(intptr_t exinf);

extern void	udp_echo_srv_task(intptr_t exinf);
extern void	udp_echo_cli_task(intptr_t exinf);

/*
 *  �֐�
 */

extern ER callback_nblk_tcp_echo_srv (ID cepid, FN fncd, void *p_parblk);
extern ER callback_nblk_tcp_echo_cli (ID cepid, FN fncd, void *p_parblk);

extern ER callback_udp_echo_srv (ID cepid, FN fncd, void *p_parblk);
extern ER callback_udp_echo_cli (ID cepid, FN fncd, void *p_parblk);

extern ER callback_nblk_udp_echo_srv (ID cepid, FN fncd, void *p_parblk);
extern ER callback_nblk_udp_echo_cli (ID cepid, FN fncd, void *p_parblk);

#endif	/* of #ifndef _ECHO_H_ */
