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
 *  @(#) $Id: ping6.c,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

/* 
 *  ping6 -- ICMPv6 ECHO ���b�Z�[�W�𑗐M����B
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

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet6/nd6.h>

#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>

#include <net/if6_var.h>

#ifdef USE_PING

/*
 *  �ϐ�
 */

static uint16_t	send_icmp6_id = 0;
static uint16_t	curr_icmp6_id;
static uint16_t	curr_icmp6_size;
static uint16_t	reply_count;
static SYSTIM	icmp6_start_time;

/*
 *  icmp6_reply_timeout -- ICMP6 REPLY �^�C���A�E�g����
 */

static void
icmp6_reply_timeout (void *arg)
{
	if (reply_count == 0)
		syslog(LOG_NOTICE, "[PING6] request timeout.");
	}

/*
 *  icmp6_echo_reply -- ICMP6 ECHO REPLY ���b�Z�[�W����������B
 */

void
icmp6_echo_reply (T_NET_BUF *input, uint_t ihoff)
{
	T_IP6_HDR	*ip6h;
	SYSTIM		time;

	syscall(get_tim(&time));
	ip6h  = GET_IP6_HDR(input);

	syslog(LOG_NOTICE, "[PING6] reply: %5d [ms] from: %s",
	                   (time - icmp6_start_time) * 1000 / SYSTIM_HZ,
	                   ipv62str(NULL, &ip6h->src));
	reply_count ++;
	}

/*
 *  ping6 -- ICMP ECHO ���b�Z�[�W�𑗐M����B
 */

void
ping6 (T_IN6_ADDR *addr, uint_t tmo, uint_t size)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_ICMP6_HDR	*icmp6h;
	T_NET_BUF	*output;
	T_IN6_IFADDR	*ia;
	int_t		ix;
	uint16_t	ipflags = 0;
	uint8_t		*sdu;

	/*
	 *  ����A�h���X�ɂӂ��킵�����M���A�h���X���A
	 *  �l�b�g���[�N�C���^�t�F�[�X����T�����ė��p����B
	 */
	if ((ia = in6_ifawithifp(ifp, addr)) == NULL)
		return;

	if (IN6_IS_ADDR_MULTICAST(addr))
		ipflags = IPV6_OUT_SET_HOP_LIMIT(IPV6_OUT_FLG_HOP_LIMIT, IPV6_DEFHLIM);

	/* ���M�p�� IP �f�[�^�O�������l������B*/
	if (in6_get_datagram(&output, ICMP6_HDR_SIZE + size, 0,
	                     addr, &ia->addr, IPPROTO_ICMPV6,
	                     IPV6_DEFHLIM, NBA_SEARCH_ASCENT, TMO_FEVR) != E_OK)
		return;

	/* ICMP �w�b�_��ݒ肷��B*/
	icmp6h           = GET_ICMP6_HDR(output, IF_IP6_ICMP6_HDR_OFFSET);
	icmp6h->type     = ICMP6_ECHO_REQUEST;
	icmp6h->code     = 0;
	icmp6h->icmp6_id = htons(send_icmp6_id);
	icmp6h->icmp6_seq= 0;

	/* �f�[�^��ݒ肷��B*/
	sdu = GET_ICMP6_SDU(output, IF_IP6_ICMP6_HDR_OFFSET) + size;
	for (ix = size; ix -- > 0; )
		*-- sdu = ('0' + send_icmp6_id + ix) & 0xff;

	/* �`�F�b�N�T�����v�Z����B*/
	icmp6h->sum = 0;
	icmp6h->sum = in6_cksum(output, IPPROTO_ICMPV6,
	                        (uint8_t*)icmp6h - output->buf, ICMP6_HDR_SIZE + size);

	/* �����`�F�b�N�p�̕ϐ���ݒ肷��B*/
	curr_icmp6_id   = send_icmp6_id ++;
	curr_icmp6_size = size;

	reply_count = 0;

	syslog(LOG_NOTICE, "[PING6] send: TMO:%d, SIZE:%d, to: %s, from %s",
	                   tmo, size,
	                   ipv62str(NULL, addr), ipv62str(NULL, &ia->addr));

	/* ���M��A���݂̎��Ԃ��L�����A�^�C���A�E�g��ݒ肷��B*/
	ip6_output(output, ipflags, TMO_FEVR);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutMsgs, 1);
	NET_COUNT_MIB(icmp6_ifstat.ipv6IfIcmpOutEchos, 1);

	syscall(get_tim(&icmp6_start_time));
	timeout(icmp6_reply_timeout, NULL, tmo * NET_TIMER_HZ);

	}

#endif	/* of #ifdef USE_PING */
