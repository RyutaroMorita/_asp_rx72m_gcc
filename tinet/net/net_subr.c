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
 *  @(#) $Id: net_subr.c,v 1.5.4.1 2015/02/05 02:09:13 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* 
 *  �l�b�g���[�N�ėp�T�|�[�g���[�`��
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/net.h>

/*
 *  �ϐ�
 */

static uint32_t next = ULONG_C(1);

/*
 *  net_rand -- ������Ԃ��B
 */

uint32_t
net_rand (void)
{
	next = (next * 1103515245 + 12345) % (ULONG_C(0x7fffffff) + 1);
	return next;
	}

/*
 *  srand -- ����������������B
 */

void
net_srand (uint32_t seed)
{
	next += seed;
	}

/*
 *  convert_hexdigit -- 16�i����������ϊ�
 */

int_t
convert_hexdigit (char *buf, uint_t val, int_t radix, int_t width, char padchar)
{
	static const char radhex[] = "0123456789abcdef";

	char	digits[11], *start;
	int_t	ix, pad;

	ix = 0;
	start = buf;
	do {
		digits[ix ++] = radhex[(val % radix) & 0x0f];
		val /= radix;
		} while (val != 0);
	for (pad = ix; pad < width; pad ++)
		*buf ++ = padchar;
	while (ix -- > 0)
		*buf ++ = digits[ix];
	*buf = '\0';
	return (int_t)(buf - start);
	}

#ifdef SUPPORT_ETHER

/*
 *  mac2str -- MAC �A�h���X�𕶎���ɕϊ�����B
 */

char *
mac2str (char *buf, uint8_t *macaddr)
{
	static char	addr_sbuf[NUM_MACADDR_STR_BUFF][sizeof("00:00:00:00:00:00")];
	static int_t	bix = NUM_MACADDR_STR_BUFF;

	char *start;

	if (buf == NULL) {
		syscall(wai_sem(SEM_MAC2STR_BUFF_LOCK));
		buf = addr_sbuf[-- bix];
		if (bix <= 0)
			bix = NUM_MACADDR_STR_BUFF;
		syscall(sig_sem(SEM_MAC2STR_BUFF_LOCK));
		}

	start = buf;
	buf += convert_hexdigit(buf, (uint_t)(*macaddr ++), 16, 2, '0');
	*(buf ++) = ':';
	buf += convert_hexdigit(buf, (uint_t)(*macaddr ++), 16, 2, '0');
	*(buf ++) = ':';
	buf += convert_hexdigit(buf, (uint_t)(*macaddr ++), 16, 2, '0');
	*(buf ++) = ':';
	buf += convert_hexdigit(buf, (uint_t)(*macaddr ++), 16, 2, '0');
	*(buf ++) = ':';
	buf += convert_hexdigit(buf, (uint_t)(*macaddr ++), 16, 2, '0');
	*(buf ++) = ':';
	buf += convert_hexdigit(buf, (uint_t)(*macaddr ++), 16, 2, '0');
	*buf = '\0';
	return start;
	}

#endif	/* of #ifdef SUPPORT_ETHER */

#if _NET_CFG_BYTE_ORDER == _NET_CFG_LITTLE_ENDIAN

/*
 *  rev_memcpy_word -- ���]�������R�s�[�i4 �o�C�g�j
 *
 *    �o�C�g�P�ʂɃA�N�Z�X���鎖�ɂ��A
 *    ���E�ւ̃A���C���̖�����������B
 */

void
rev_memcpy_word (uint8_t *dst, uint8_t *src)
{
	*(dst    ) = *(src + 3);
	*(dst + 1) = *(src + 2);
	*(dst + 2) = *(src + 1);
	*(dst + 3) = *(src    );
	}

/*
 *  rev_memcmp_word -- ���]��������r�i4 �o�C�g�j
 *
 *    �o�C�g�P�ʂɃA�N�Z�X���鎖�ɂ��A
 *    ���E�ւ̃A���C���̖�����������B
 */

int_t
rev_memcmp_word (uint8_t *data1, uint8_t *data2)
{
	int_t	ix, diff;

	for (ix = 4; ix -- > 0; ) {
		diff = *(data1 + ix) -  *(data2 + (3 - ix));
		if (diff != 0)
			return diff;
		}
	return 0;
	}

#endif	/* of #if _NET_CFG_BYTE_ORDER == _NET_CFG_LITTLE_ENDIAN */
