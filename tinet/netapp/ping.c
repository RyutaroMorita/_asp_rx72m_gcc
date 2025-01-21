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
 *  @(#) $Id: ping.c,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

/* 
 *  ping -- ICMP ECHO ���b�Z�[�W�𑗐M����B
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/ppp_var.h>
#include <net/ppp_ipcp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp_var.h>

#ifdef USE_PING

/*
 *  �ϐ�
 */

static uint16_t	icmp_id = 0;
static uint16_t	curr_icmp_id;
static uint16_t	curr_icmp_len;
static SYSTIM	icmp_start_time;

/*
 *  icmp_reply_timeout -- ICMP REPLY �^�C���A�E�g����
 */

static void
icmp_reply_timeout (void *arg)
{
	syslog(LOG_NOTICE, "[PING] request timeout.");
	}

/*
 *  icmp_echo_reply -- ICMP ECHO REPLY ���b�Z�[�W����������B
 */

void
icmp_echo_reply (T_NET_BUF *input, uint_t ihoff)
{
	SYSTIM time;

	syscall(get_tim(&time));
	untimeout(icmp_reply_timeout, NULL);
	syslog(LOG_NOTICE, "[PING] reply, %d [ms].",
	                   (time - icmp_start_time) * 1000 / SYSTIM_HZ);
	}

/*
 *  ping4 -- ICMP ECHO ���b�Z�[�W�𑗐M����B
 */

void
ping4 (T_IN4_ADDR *addr, uint_t tmo, uint_t len)
{
	T_ICMP4_HDR	*icmp4h;
	T_NET_BUF	*output;
	uint8_t		*sdu;
	int_t		ix;

	/* ���M�p�� IP �f�[�^�O�������l������B*/
	if (in4_get_datagram(&output, ICMP4_HDR_SIZE + len, 0,
	                     addr, NULL, IPPROTO_ICMP,
	                     IP4_DEFTTL, NBA_SEARCH_ASCENT, TMO_FEVR) != E_OK)
		return;

	/* ICMP �w�b�_��ݒ肷��B*/
	icmp4h			= GET_ICMP4_HDR(output, IF_IP4_ICMP4_HDR_OFFSET);
	icmp4h->type		= ICMP4_ECHO_REQUEST;
	icmp4h->code		= 0;
	icmp4h->data.id_seq.id	= htons(icmp_id);
	icmp4h->data.id_seq.seq	= 0;

	/* �f�[�^��ݒ肷��B*/
	sdu = GET_ICMP4_SDU(output, IF_IP4_ICMP4_HDR_OFFSET) + len;
	for (ix = len; ix -- > 0; )
		*-- sdu = ('0' + icmp_id + ix) & 0xff;

	/* �`�F�b�N�T�����v�Z����B*/
	icmp4h->sum = 0;
	icmp4h->sum = in_cksum(icmp4h, ICMP4_HDR_SIZE + len);

	/* �����`�F�b�N�p�̕ϐ���ݒ肷��B*/
	curr_icmp_id  = icmp_id ++;
	curr_icmp_len = len;

	NET_COUNT_MIB(icmp_stats.icmpOutMsgs, 1);
	NET_COUNT_MIB(icmp_stats.icmpOutEchos, 1);

	/* ���M��A���݂̎��Ԃ��L�����A�^�C���A�E�g��ݒ肷��B*/
	ip_output(output, TMO_FEVR);

	syscall(get_tim(&icmp_start_time));
	timeout(icmp_reply_timeout, NULL, tmo * NET_TIMER_HZ);

	}

#endif	/* of #ifdef USE_PING */
