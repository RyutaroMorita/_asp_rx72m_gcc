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
 *  @(#) $Id: if_ed.h,v 1.5 2009/12/24 05:46:31 abe Exp $
 */

/*
 * Copyright (C) 1993, David Greenman. This software may be used, modified,
 *   copied, distributed, and sold, in both source and binary form provided
 *   that the above copyright and these terms are retained. Under no
 *   circumstances is the author responsible for the proper functioning
 *   of this software, nor does the author assume any responsibility
 *   for damages incurred with its use.
 */

#ifndef _IF_ED_H_
#define _IF_ED_H_

/*
 *  NIC �̑I���}�N��
 */

#define IF_ETHER_NIC_GET_SOFTC()	ed_get_softc()
#define IF_ETHER_NIC_WATCHDOG(i)	ed_watchdog(i)
#define IF_ETHER_NIC_PROBE(i)		ed_probe(i)
#define IF_ETHER_NIC_INIT(i)		ed_init(i)
#define IF_ETHER_NIC_READ(i)		ed_read(i)
#define IF_ETHER_NIC_RESET(i)		ed_reset(i)
#define IF_ETHER_NIC_START(i,o)		ed_start(i,o)

#define T_IF_ETHER_NIC_SOFTC		struct t_ed_softc

/* IPv6 �֌W */

#define IF_ETHER_NIC_IN6_IFID(i,a)	get_mac6_ifid(i,a)	/* �C���^�t�F�[�X���ʎq�̐ݒ�		*/
#define IF_ETHER_NIC_ADDMULTI(s)	ed_addmulti(s)		/* �}���`�L���X�g�A�h���X�̓o�^		*/

#if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY)

/*
 *  �O���Q��
 */

#ifndef T_IF_SOFTC_DEFINED

typedef struct t_if_softc T_IF_SOFTC;

#define T_IF_SOFTC_DEFINED

#endif	/* of #ifndef T_IF_SOFTC_DEFINED */

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */

/*
 *  �֐�
 */

extern T_IF_SOFTC *ed_get_softc(void);
extern void ed_watchdog(T_IF_SOFTC *ic);
extern void ed_probe(T_IF_SOFTC *ic);
extern void ed_init(T_IF_SOFTC *ic);
extern void ed_reset(T_IF_SOFTC *ic);
extern T_NET_BUF *ed_read(T_IF_SOFTC *ic);
extern void ed_start(T_IF_SOFTC *ic, T_NET_BUF *output);
extern ER ed_addmulti(T_IF_SOFTC *ic);
extern void if_ed_handler(void);

#endif /* #if !defined(TOPPERS_MACRO_ONLY) && !defined(_MACRO_ONLY) */

#endif	/* of #ifndef _IF_ED_H_ */
