/*
 *  TINET (TCP/IP Protocol Stack)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2008-2009 by Hokkaido Industrial Research Institute, JAPAN
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
 *  @(#) $Id: esp.h,v 1.5 2009/12/24 05:48:16 abe Exp $
 */

/*	$FreeBSD: src/sys/netinet6/esp.h,v 1.6 2002/04/19 04:46:22 suz Exp $	*/
/*	$KAME: esp.h,v 1.19 2001/09/04 08:43:19 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
 
#ifndef _ESP_H_
#define _ESP_H_

#if defined(SUPPORT_INET6) || defined(SUPPORT_IPSEC)

/*
 *  RFC2406 �Í����w�b�_
 */

typedef struct t_esp_hdr {
	int32_t	spi;	/* Security Parameter Index (SPI)	*/
	int32_t	seq;	/* �V�[�P���X�ԍ�			*/
	} T_ESP_HDR;

typedef struct t_esp_tail {
	int8_t	padlen;	/* �p�f�B���O��				*/	
	int8_t	next;	/* Next Header				*/
	} T_ESP_TAIL;

struct t_secas_var;

struct t_esp_algorithm {
	size_t padbound;	/* pad boundary, in byte */
	int_t ivlenval;		/* iv length, in byte */
	int_t (*mature) (struct t_secas_var *);
	int_t keymin;	/* in bits */
	int_t keymax;	/* in bits */
	//int_t (*schedlen) (const struct t_esp_algorithm *);
	int32_t (*schedlen) (const struct t_esp_algorithm *);
	const char *name;
	int_t (*ivlen) (const struct t_esp_algorithm *, struct t_secas_var *);
	int_t (*decrypt) (T_NET_BUF *, size_t,
		struct t_secas_var *, const struct t_esp_algorithm *, int_t,
			T_NET_BUF *, size_t);
	int_t (*encrypt) (T_NET_BUF *, size_t, size_t, int8_t*,
		struct t_secas_var *, const struct t_esp_algorithm *, int_t,
			T_NET_BUF *, size_t);
	/* not supposed to be called directly */
	int_t (*schedule) (const struct t_esp_algorithm *, struct t_secas_var *);
	int_t (*blockdecrypt) (const struct t_esp_algorithm *,
		struct t_secas_var *, int8_t *, int8_t *);
	int_t (*blockencrypt) (const struct t_esp_algorithm *,
		struct t_secas_var *, int8_t *, int8_t *);
};

typedef struct t_esp_algorithm T_ESP_ALGORITHM;

#define MAXIVLEN	16

/*
 * �֐�
 */

extern const struct t_esp_algorithm *esp_algorithm_lookup (int_t);
extern int_t esp_max_ivlen (void);
extern int_t esp_schedule (const struct t_esp_algorithm *, struct t_secas_var *);
extern int_t esp4_input(T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);

#ifdef T_IPSEC_REQUEST_DEFINED

extern int_t esp4_output(T_NET_BUF *m, T_IPSEC_REQUEST *isr, T_NET_BUF** result);

#endif	/* of #ifdef T_IPSEC_REQUEST_DEFINED */

#endif /* defined(SUPPORT_INET6) || defined(SUPPORT_IPSEC) */

#endif	/* of #ifndef _ESP_H_ */
