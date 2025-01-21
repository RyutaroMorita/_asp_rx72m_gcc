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
 *  @(#) $Id: route_cfg.c,v 1.5 2009/12/24 06:20:39 abe Exp $
 */

/* 
 *  ���[�e�B���O�\
 */

#include <kernel.h>

#include <tinet_defs.h>
#include <tinet_config.h>

#include <netinet/in.h>
#include <netinet/in_var.h>

/* IPv4 �Ɋւ����` */

#ifdef SUPPORT_INET4

#ifdef SUPPORT_LOOP

T_IN4_RTENTRY routing_tbl[NUM_ROUTE_ENTRY] = {
	{ 0, 0, 0 },
	};

#endif	/* of #ifdef SUPPORT_LOOP */

#ifdef SUPPORT_PPP

T_IN4_RTENTRY routing_tbl[NUM_ROUTE_ENTRY] = {
	{ 0, 0, 0 },
	};

#endif	/* of #ifdef SUPPORT_PPP */

#ifdef SUPPORT_ETHER

T_IN4_RTENTRY routing_tbl[NUM_ROUTE_ENTRY] = {

	/* �قȂ� LAN�Adefault gateway �ɂ��Ԑڔz��	*/
	{ 0,			0,			IPV4_ADDR_DEFAULT_GW	},

	/* ���� LAN ���A���ڔz��				*/
	{ IPV4_ADDR_LOCAL &
	  IPV4_ADDR_LOCAL_MASK,	IPV4_ADDR_LOCAL_MASK,	0			},

	/* ���� LAN ���ւ̃u���[�h�L���X�g�A���ڔz��	*/
	{ 0xffffffff,		0xffffffff,		0			},

	};

#endif	/* of #ifdef SUPPORT_ETHER */

#endif	/* of #ifdef SUPPORT_INET4 */

/* IPv6 �Ɋւ����` */

#ifdef SUPPORT_INET6

#if NUM_ROUTE_ENTRY > 0

T_IN6_RTENTRY routing_tbl[NUM_ROUTE_ENTRY] = { };

#endif	/* of #if NUM_ROUTE_ENTRY > 0 */

#endif	/* of #ifdef SUPPORT_INET6 */
