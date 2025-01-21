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
 *  @(#) $Id: wwws.h,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

#ifndef _WWWS_H_
#define _WWWS_H_

/* 
 *  WWW �T�[�o
 */

#include <tinet_defs.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>

#include <netinet6/in6.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>

#ifdef TOPPERS_S810_CLG3_85
#define	WWW_SRV_STACK_SIZE		768		/* �^�X�N�̃X�^�b�N�T�C�Y	*/
#else	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define	WWW_SRV_STACK_SIZE		1024		/* �^�X�N�̃X�^�b�N�T�C�Y	*/
#endif	/* of #ifdef TOPPERS_S810_CLG3_85 */
#define WWW_SRV_MAIN_PRIORITY		5		/* �^�X�N�̗D��x		*/

/*
 *  TCP ����M�E�C���h�o�b�t�@�T�C�Y
 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0

#define WWW_SRV_SWBUF_SIZE	((IF_MTU-(IP_HDR_SIZE+TCP_HDR_SIZE))*1)

#else	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)
#define WWW_SRV_SWBUF_SIZE	(TCP_MSS)
#endif

#if defined(SUPPORT_INET6)
#define WWW_SRV_SWBUF_SIZE	(TCP6_MSS)
#endif

#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(SUPPORT_INET4)
#define WWW_SRV_RWBUF_SIZE	(TCP_MSS)
#endif

#if defined(SUPPORT_INET6)
#define WWW_SRV_RWBUF_SIZE	(TCP6_MSS)
#endif

#define WWW_RBUFF_SIZE		(WWW_SRV_RWBUF_SIZE)
#define WWW_LINE_SIZE		80
#define WWW_NUM_FIELDS		4

#ifndef _MACRO_ONLY

typedef struct line {
	uint8_t		len;
	uint8_t		num;
	uint8_t		off[WWW_NUM_FIELDS];
	char		buf[WWW_LINE_SIZE + 1];
	} T_WWW_LINE;

#ifdef USE_COPYSAVE_API

typedef struct www_buffer {
	char		*buf;
	uint16_t	len;
	uint16_t	index;
	} T_WWW_BUFFER;

#else	/* of #ifdef USE_COPYSAVE_API */

typedef struct www_buffer {
	uint16_t	len;
	uint16_t	index;
	char		buf[WWW_RBUFF_SIZE];
	} T_WWW_BUFFER;

#endif	/* of #ifdef USE_COPYSAVE_API */

typedef struct www_rwbuf {
	T_WWW_BUFFER	sbuf;
	T_WWW_BUFFER	rbuf;
	char		unget;
	} T_WWW_RWBUF;

/* �^�X�N */

extern void	www_srv_task (intptr_t exinf);

/*
 *  TCP ����M�o�b�t�@
 */

extern uint8_t www_srv_swbuf[NUM_WWW_SRV_TASKS][WWW_SRV_SWBUF_SIZE];
extern uint8_t www_srv_rwbuf[NUM_WWW_SRV_TASKS][WWW_SRV_RWBUF_SIZE];

#endif	/* of #ifndef _MACRO_ONLY */

#endif	/* of #ifndef _WWWS_H_ */
