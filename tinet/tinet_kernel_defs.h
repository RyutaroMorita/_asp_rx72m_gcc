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
 *  @(#) $Id: tinet_kernel_defs.h,v 1.5 2009/12/24 05:38:58 abe Exp $
 */

/*
 *  �J�[�l���Ɋւ���݊�����`�t�@�C��
 */

#ifndef _TINET_KERNEL_DEFS_H_
#define _TINET_KERNEL_DEFS_H_

#if defined(TARGET_KERNEL_JSP)

#ifndef _MACRO_ONLY

/*
 *  �f�[�^�^�̒�`�iinttype.h�j
 */

#ifdef _int8_
typedef _int8_			int8_t;		/* �����t�� 8 �r�b�g���� */
typedef unsigned _int8_		uint8_t;	/* �������� 8 �r�b�g���� */
#endif	/* of #ifdef _int8_ */

#ifdef _int16_
typedef _int16_			int16_t;	/* �����t�� 16 �r�b�g���� */
typedef unsigned _int16_	uint16_t;	/* �������� 16 �r�b�g���� */
#endif	/* of #ifdef _int16_ */

#ifdef _int32_
typedef _int32_			int32_t;	/* �����t�� 32 �r�b�g���� */
typedef unsigned _int32_	uint32_t;	/* �������� 32 �r�b�g���� */
#endif	/* of #ifdef _int32_ */

#ifdef _int64_
typedef unsigned _int64_	uint64_t;	/* �������� 64 �r�b�g���� */
#endif	/* of #ifdef _int64_ */

typedef signed int		int_t;		/* ���R�ȃT�C�Y�̕����t������ */
typedef unsigned int		uint_t;		/* ���R�ȃT�C�Y�̕����������� */

typedef signed long		long_t;		/* ���߂̃T�C�Y�̕����t������ */
typedef unsigned long		ulong_t;	/* ���߂̃T�C�Y�̕����������� */

#ifdef _vp_int_
typedef _vp_int_		intptr_t;	/* �|�C���^�܂��͕����t������ */
#else	/* of #ifdef _vp_int_ */
typedef VP			intptr_t;	/* �|�C���^�܂��͕����t������ */
#endif	/* of #ifdef _vp_int_ */

typedef int			bool_t;		/* �^�U�l */

#ifndef true
#define true			1		/* �^ */
#endif /* true */

#ifndef false
#define false			0		/* �U */
#endif /* false */

#endif	/* of #ifndef _MACRO_ONLY */

/* �\���� structure ���̃t�B�[���h field �̃o�C�g�ʒu��Ԃ��}�N�� */
#ifndef offsetof
#define offsetof(structure, field) ((size_t) &(((structure *) 0)->field))
#endif	/* of #ifndef offsetof */

/*
 *  �����萔�����}�N��
 */
#ifndef UINT_C
#define UINT_C(val)		(val ## U)	/* uint_t�^�̒萔�����}�N�� */
#endif /* UINT_C */

#ifndef ULONG_C
#define ULONG_C(val)		(val ## UL)	/* ulong_t�^�̒萔�����}�N�� */
#endif /* ULONG_C */

#elif defined(TARGET_KERNEL_ASP)

#define syscall(api)		(api)

#endif	/* of #if defined(TARGET_KERNEL_JSP) */

#endif	/* of #ifndef _TINET_KERNEL_DEFS_H_ */
