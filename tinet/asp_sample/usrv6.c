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
 *  @(#) $Id: usrv6.c,v 1.5 2009/12/24 06:20:39 abe Exp $
 */

/* 
 *  UDP ECHO �T�[�o
 *
 *    �E����M�^�X�N����^
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include "usrv6.h"

/*
 *  �O���֐��̒�`
 */

extern const char *itron_strerror (ER ercd);

/*
 *  �ϐ�
 */

#define BUF_SIZE	2048

/*
 *  UDP ECHO �T�[�o�^�X�N
 */

void
usrv_task(intptr_t exinf)
{
	static uint8_t buffer[BUF_SIZE];

	T_IPV6EP	dst;
	T_IN6_ADDR	addr;
	ER_UINT		len;
	ID		tskid;

	get_tid(&tskid);
	syslog(LOG_NOTICE, "[UDP ECHO SRV:%d,%d] started.", tskid, (ID)exinf);
	while (true) {
		if ((len = udp6_rcv_dat((ID)exinf, &dst, buffer, sizeof(buffer), 20 * 1000)) >= 0) {
			buffer[len] = '\0';
			syslog(LOG_NOTICE, "[UDP ECHO SRV] recv, addr: %s:%d,\n"
			                   "                     len: %d, msg: '%s'",
			                   ipv62str(NULL, &dst.ipaddr), dst.portno, len, buffer);
			if ((int)len > 0) {
				if ((len = udp6_snd_dat((ID)exinf, &dst, buffer, len, TMO_FEVR)) < 0)
					syslog(LOG_NOTICE, "[UDP ECHO SRV] send, error: %s", itron_strerror(len));
				}
			}
		else
			syslog(LOG_NOTICE, "[UDP ECHO SRV] recv, error: %s", itron_strerror(len));
		}
	}
