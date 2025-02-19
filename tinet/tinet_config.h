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
 *  @(#) $Id: tinet_config.h,v 1.5.4.1 2015/02/05 02:07:56 abe Exp abe $
 */

#ifndef _TINET_CONFIG_H_
#define _TINET_CONFIG_H_

/*
 *  TINET 1.2 �Ƃ̌݊����̂��߂̒�`
 */

/* TCP�̎󓮃I�[�v�����T�|�[�g����B*/

#define TCP_CFG_PASSIVE_OPEN

/* TCP�̃m���u���b�L���O�R�[���@�\��g���ށB*/

#define TCP_CFG_NON_BLOCKING

/* UDP�̃m���u���b�L���O�R�[���@�\��g���ށB*/

#define UDP_CFG_NON_BLOCKING

/*
 *  NIC�A�V�X�e���ACPU�A���p�v���O������
 *  �ˑ������`�t�@�C�����C���N���[�h����B
 */

#if defined(TARGET_KERNEL_JSP)

#ifdef SUPPORT_ETHER

#include "tinet_nic_config.h"

#endif	/* of #ifdef SUPPORT_ETHER */

#include "tinet_sys_config.h"
#include "tinet_cpu_config.h"
#include "tinet_app_config.h"

#elif defined(TARGET_KERNEL_ASP)

#ifdef SUPPORT_ETHER

#include "tinet_nic_config.h"

#endif	/* of #ifdef SUPPORT_ETHER */

#include "tinet_target_config.h"
#include "tinet_app_config.h"

#endif	/* of #if defined(TARGET_KERNEL_JSP) */

/*
 *  TINET 1.1 �Ƃ̌݊����̂��߂̒�`
 */

#ifdef  TMO_ICMP4_OUTPUT
#define TMO_ICMP_OUTPUT	TMO_ICMP4_OUTPUT
#endif

/*
 *  TINET 1.2 �Ƃ̌݊����̂��߂̒�`
 */

#ifdef  NUM_MPF_NET_BUF_4096
#define NUM_MPF_NET_BUF_REASSM	NUM_MPF_NET_BUF_4096
#endif

/*
 *  TINET 1.3 �Ƃ̌݊����̂��߂̒�`

#ifdef  NUM_MPF_NET_BUF_REASSM
#define NUM_MPF_NET_BUF4_REASSM	NUM_MPF_NET_BUF_REASSM
#endif
 */

/*
 *  TCP �Ɋւ����`
 */

/*
 *  MAX_TCP_RCV_SEG: ��M�Z�O�����g�T�C�Y�̍ő�l
 *
 *    ����: �ύX���ׂ��ł͂Ȃ��B
 */

#ifndef MAX_TCP_RCV_SEG
#define MAX_TCP_RCV_SEG		(IF_MTU - (IP_HDR_SIZE + TCP_HDR_SIZE))
#endif

/*
 *  DEF_TCP_SND_SEG: ���M�Z�O�����g�T�C�Y�̋K��l
 */

#ifndef DEF_TCP_SND_SEG
#define DEF_TCP_SND_SEG		MAX_TCP_SND_SEG
#endif

/*
 *  TCP �ʐM�[�_�̑���M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\
 */

#ifdef  TCP_CFG_SWBUF_CSAVE_ONLY
#ifndef TCP_CFG_SWBUF_CSAVE
#define TCP_CFG_SWBUF_CSAVE
#endif
#endif	/* of #ifdef  TCP_CFG_SWBUF_CSAVE_ONLY */

#ifdef  TCP_CFG_RWBUF_CSAVE_ONLY
#ifndef TCP_CFG_RWBUF_CSAVE
#define TCP_CFG_RWBUF_CSAVE
#endif
#endif	/* of #ifdef  TCP_CFG_RWBUF_CSAVE_ONLY */

/*
 *  TCP_CFG_URG_OFFSET: �ً}�f�[�^�̍Ō�̃o�C�g�̃I�t�Z�b�g
 *
 *    -1: BSD �̎����A�ً}�|�C���^�́A�ً}�f�[�^�̍Ō�̃o�C�g�̎��̃o�C�g�������B
 *     0: RFC1122 �̋K��A�ً}�|�C���^�́A�ً}�f�[�^�̍Ō�̃o�C�g�������B
 */

#ifndef TCP_CFG_URG_OFFSET
#define TCP_CFG_URG_OFFSET	-1
#endif

/*
 *  ARP �Ɋւ����`
 */

#ifndef ARP_CACHE_KEEP
#define ARP_CACHE_KEEP		(20*60*NET_TIMER_HZ)	/* ARP �L���b�V���̃^�C���A�E�g	*/
#endif

/*
 *  ���[�v�o�b�N�C���^�t�F�[�X�Ɋւ����`
 */

#ifndef LOMTU
#define LOMTU			1500	/* ���[�v�o�b�N�� MTU			*/
#endif

/*
 * TINET �T�|�[�g�֐��Ɋւ����`
 */

#ifndef NUM_IPV4ADDR_STR_BUFF		/* ip2str �ɂ����� IP �A�h���X������p�o�b�t�@�� */

#if defined(SUPPORT_PPP)

#define NUM_IPV4ADDR_STR_BUFF	2

#else	/* of #if defined(SUPPORT_PPP) */

#define NUM_IPV4ADDR_STR_BUFF	1

#endif	/* of #if defined(SUPPORT_PPP) */

#endif	/* of #ifndef NUM_IPV4ADDR_STR_BUFF */

#ifndef NUM_IPV6ADDR_STR_BUFF
#define NUM_IPV6ADDR_STR_BUFF	2	/* ip62str �ɂ����� IP �A�h���X������p�o�b�t�@�� */
#endif

#ifndef NUM_MACADDR_STR_BUFF		/* macstr �ɂ����� MAC �A�h���X������p�o�b�t�@�� */

#if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) && defined(ETHER_CFG_MCAST_WARNING)

#define NUM_MACADDR_STR_BUFF	2

#else	/* of #if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) && defined(ETHER_CFG_MCAST_WARNING) */

#define NUM_MACADDR_STR_BUFF	1

#endif	/* of #if defined(SUPPORT_INET4) && defined(ETHER_CFG_ACCEPT_ALL) && defined(ETHER_CFG_MCAST_WARNING) */

#endif	/* of #ifndef NUM_MACADDR_STR_BUFF */

/*
 *  TINET �����̃^�C���A�E�g�l�̐ݒ�
 */

#ifndef TMO_IP4_FRAG_GET_NET_BUF
#define TMO_IP4_FRAG_GET_NET_BUF	ULONG_C(1000)	/* [ms]�AIPv4 �f�[�^�O�����č\���p�l�b�g���[�N�o�b�t�@�l���^�C���A�E�g	*/
#endif

#ifndef TMO_IP6_FRAG_GET_NET_BUF
#define TMO_IP6_FRAG_GET_NET_BUF	ULONG_C(1000)	/* [ms]�AIPv6 �f�[�^�O�����č\���p�l�b�g���[�N�o�b�t�@�l���^�C���A�E�g	*/
#endif

#ifndef TMO_PPP_GET_NET_BUF
#define TMO_PPP_GET_NET_BUF		ULONG_C(1000)	/* [ms]�APPP ��M�p�l�b�g���[�N�o�b�t�@�l���^�C���A�E�g	*/
#endif

#ifndef TMO_ARP_GET_NET_BUF
#define TMO_ARP_GET_NET_BUF		ULONG_C(1000)	/* [ms]�AARP �̃l�b�g���[�N�o�b�t�@�l���^�C���A�E�g	*/
#endif

#ifndef TMO_TCP_GET_NET_BUF
#define TMO_TCP_GET_NET_BUF		ULONG_C(1000)	/* [ms]�ATCP �̃l�b�g���[�N�o�b�t�@�l���^�C���A�E�g	*/
#endif

#ifndef TMO_TCP_OUTPUT
#define TMO_TCP_OUTPUT			ULONG_C(1000)	/* [ms]�ATCP �o�̓^�C���A�E�g				*/
#endif

#ifndef TMO_UDP_OUTPUT
#define TMO_UDP_OUTPUT			ULONG_C(1000)	/* [ms]�AUDP �o�̓^�C���A�E�g				*/
#endif

#ifndef TMO_ICMP_OUTPUT
#define TMO_ICMP_OUTPUT			ULONG_C(1000)	/* [ms]�AICMP �o�̓^�C���A�E�g				*/
#endif

#ifndef TMO_ND6_NS_OUTPUT
#define TMO_ND6_NS_OUTPUT		ULONG_C(1000)	/* [ms]�A�ߗחv���o�̓^�C���A�E�g			*/
#endif

#ifndef TMO_ND6_NA_OUTPUT
#define TMO_ND6_NA_OUTPUT		ULONG_C(1000)	/* [ms]�A�ߗגʒm�o�̓^�C���A�E�g			*/
#endif

#ifndef TMO_ND6_RS_OUTPUT
#define TMO_ND6_RS_OUTPUT		ULONG_C(1000)	/* [ms]�A���[�^�v���o�̓^�C���A�E�g			*/
#endif

#ifndef TMO_ARP_OUTPUT
#define TMO_ARP_OUTPUT			ULONG_C(1000)	/* [ms]�A�A�h���X�����v���o�̓^�C���A�E�g		*/
#endif

#ifndef TMO_ND6_RTR_SOL_DELAY
#define TMO_ND6_RTR_SOL_DELAY		ULONG_C(1000)	/* [ms]�A���[�^�v���o�͒x��				*/
#endif

#ifndef TMO_ND6_RTR_SOL_INTERVAL
#define TMO_ND6_RTR_SOL_INTERVAL	ULONG_C(4000)	/* [ms]�A���[�^�v���o�͊Ԋu				*/
#endif

#ifndef TMO_IN_REDIRECT
					/* [s]�A�����������[�e�B���O�G���g���^�C���A�E�g*/
#define TMO_IN_REDIRECT			(10*60*NET_TIMER_HZ)
#endif

/*
 *  TINET �����̃^�X�N�̃X�^�b�N�T�C�Y�̐ݒ�
 */

#ifndef TCP_OUT_TASK_STACK_SIZE
#define	TCP_OUT_TASK_STACK_SIZE	1024	/* TCP �o�̓^�X�N�̃X�^�b�N�T�C�Y		*/
#endif

#ifndef UDP_OUT_TASK_STACK_SIZE
#define	UDP_OUT_TASK_STACK_SIZE	1024	/* UDP �o�̓^�X�N�̃X�^�b�N�T�C�Y			*/
#endif

#ifndef PPP_INPUT_STACK_SIZE
#define	PPP_INPUT_STACK_SIZE	1024	/* PPP �^�X�N�̃X�^�b�N�T�C�Y		*/
#endif

#ifndef PPP_OUTPUT_STACK_SIZE
#define	PPP_OUTPUT_STACK_SIZE	1024	/* PPP �o�̓^�X�N�̃X�^�b�N�T�C�Y		*/
#endif

#ifndef ETHER_INPUT_STACK_SIZE
#define	ETHER_INPUT_STACK_SIZE	1024	/* Ethernet ���̓^�X�N�̃X�^�b�N�T�C�Y	*/
#endif

#ifndef ETHER_OUTPUT_STACK_SIZE
#define	ETHER_OUTPUT_STACK_SIZE	1024	/* Ethernet �o�̓^�X�N�̃X�^�b�N�T�C�Y	*/
#endif

#ifndef LOOP_INPUT_STACK_SIZE
#define	LOOP_INPUT_STACK_SIZE	1024	/* ���[�v�o�b�N���̓^�X�N�̃X�^�b�N�T�C�Y	*/
#endif

#ifndef LOOP_OUTPUT_STACK_SIZE
#define	LOOP_OUTPUT_STACK_SIZE	1024	/* ���[�v�o�b�N�o�̓^�X�N�̃X�^�b�N�T�C�Y	*/
#endif

#ifndef NET_TIMER_STACK_SIZE
#define	NET_TIMER_STACK_SIZE	1024	/* �l�b�g���[�N�^�C�}�^�X�N�̃X�^�b�N�T�C�Y */
#endif

/*
 *  TINET �����̃^�X�N�̗D��x�̐ݒ�
 */

#ifndef TCP_OUT_TASK_PRIORITY
#define TCP_OUT_TASK_PRIORITY	2	/* TCP �o�̓^�X�N�̗D��x			*/
#endif

#ifndef UDP_OUT_TASK_PRIORITY
#define UDP_OUT_TASK_PRIORITY	2	/* UDP �o�̓^�X�N�̗D��x				*/
#endif

#ifndef PPP_INPUT_PRIORITY
#define PPP_INPUT_PRIORITY	3	/* PPP �^�X�N�̗D��x			*/
#endif

#ifndef PPP_OUTPUT_PRIORITY
#define PPP_OUTPUT_PRIORITY	3	/* PPP �^�X�N�̗D��x			*/
#endif

#ifndef ETHER_INPUT_PRIORITY
#define ETHER_INPUT_PRIORITY	2	/* Ethernet ���̓^�X�N�̗D��x		*/
#endif

#ifndef ETHER_OUTPUT_PRIORITY
#define ETHER_OUTPUT_PRIORITY	2	/* Ethernet �o�̓^�X�N�̗D��x		*/
#endif

#ifndef LOOP_INPUT_PRIORITY
#define LOOP_INPUT_PRIORITY	3	/* ���[�v�o�b�N���̓^�X�N�̗D��x		*/
#endif

#ifndef LOOP_OUTPUT_PRIORITY
#define LOOP_OUTPUT_PRIORITY	3	/* ���[�v�o�b�N�o�̓^�X�N�̗D��x		*/
#endif

#ifndef NET_TIMER_PRIORITY
#define NET_TIMER_PRIORITY	2	/* �l�b�g���[�N�^�C�}�^�X�N�̗D��x */
#endif

/*
 *  TINET �����̃f�[�^�L���[�̃G���g�����̐ݒ�
 */

/* UDP ��M�L���[�T�C�Y */

#ifndef NUM_DTQ_UDP_RCVQ
#define NUM_DTQ_UDP_RCVQ	1	/* ��R�[���o�b�N�p	*/
#endif

#ifndef NUM_DTQ_UDP_OUTPUT
#define NUM_DTQ_UDP_OUTPUT	1	/* UDP �o�̓f�[�^�L���[�T�C�Y			*/
#endif

#ifndef NUM_DTQ_PPP_OUTPUT
#define NUM_DTQ_PPP_OUTPUT	2	/* PPP �o�̓f�[�^�L���[�T�C�Y�A2 �ȏ�	*/
#endif

#ifndef NUM_DTQ_ETHER_OUTPUT
#define NUM_DTQ_ETHER_OUTPUT	2	/* Ethernet �o�̓f�[�^�L���[�T�C�Y	*/
#endif

#ifndef NUM_DTQ_LOOP_INPUT
#define NUM_DTQ_LOOP_INPUT	0	/* ���[�v�o�b�N���̓f�[�^�L���[�T�C�Y	*/
#endif

#ifndef NUM_DTQ_LOOP_OUTPUT
#define NUM_DTQ_LOOP_OUTPUT	0	/* ���[�v�o�b�N�o�̓f�[�^�L���[�T�C�Y	*/
#endif

/*
 *  TINET �v���g�R���X�^�b�N�����̃��l�[��
 */

#include <net/net_rename.h>
#include <netinet/in_rename.h>

#ifdef SUPPORT_INET6

#include <netinet6/in6_rename.h>

#endif	/* of #ifdef SUPPORT_INET6 */

#endif /* _TINET_CONFIG_H_ */
