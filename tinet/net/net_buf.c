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
 *  @(#) $Id: net_buf.c,v 1.5.4.1 2015/02/05 02:09:13 abe Exp abe $
 */

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet6/in6.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>

/*
 *  �֐�
 */

extern const char *itron_strerror (ER ercd);

/*
 *  �ϐ�
 */

static T_NET_BUF_ENTRY net_buf_table[] = {

#if defined(NUM_MPF_NET_BUF6_65536) && NUM_MPF_NET_BUF6_65536 > 0
	{
		MPF_NET_BUF6_65536,
		IF_IP6_HDR_SIZE + 65536,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF6_65536,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF6_65536) && NUM_MPF_NET_BUF6_65536 > 0 */

#if defined(NUM_MPF_NET_BUF6_REASSM) && NUM_MPF_NET_BUF6_REASSM > 0
	{
		MPF_NET_BUF_REASSM,
		IP6_CFG_FRAG_REASSM_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF6_REASSM,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF6_REASSM) && NUM_MPF_NET_BUF6_REASSM > 0 */

#if defined(NUM_MPF_NET_BUF4_REASSM) && NUM_MPF_NET_BUF4_REASSM > 0
	{
		MPF_NET_BUF_REASSM,
		IP4_CFG_FRAG_REASSM_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF4_REASSM,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF4_REASSM) && NUM_MPF_NET_BUF4_REASSM > 0 */

#if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0
	{
		MPF_NET_BUF_IF_PDU,
		IF_PDU_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_IF_PDU,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_IF_PDU) && NUM_MPF_NET_BUF_IF_PDU > 0 */

#if defined(NUM_MPF_NET_BUF_IPV6_MMTU) && NUM_MPF_NET_BUF_IPV6_MMTU > 0
	{
		MPF_NET_BUF_IPV6_MMTU,
		IF_HDR_SIZE + IPV6_MMTU,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_IPV6_MMTU,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_IPV6_MMTU) && NUM_MPF_NET_BUF_IPV6_MMTU > 0 */

#if defined(NUM_MPF_NET_BUF_1024) && NUM_MPF_NET_BUF_1024 > 0
	{
		MPF_NET_BUF_1024,
		UINT_C(1024),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_1024,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_1024) && NUM_MPF_NET_BUF_1024 > 0 */

#if defined(NUM_MPF_NET_BUF_IP_MSS) && NUM_MPF_NET_BUF_IP_MSS > 0
	{
		MPF_NET_BUF_IP_MSS,
		IF_HDR_SIZE + IP4_MSS,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_IP_MSS,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_IP_MSS) && NUM_MPF_NET_BUF_IP_MSS > 0 */

#if defined(NUM_MPF_NET_BUF_512) && NUM_MPF_NET_BUF_512 > 0
	{
		MPF_NET_BUF_512,
		UINT_C(512),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_512,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_512) && NUM_MPF_NET_BUF_512 > 0 */

#if defined(NUM_MPF_NET_BUF_256) && NUM_MPF_NET_BUF_256 > 0
	{
		MPF_NET_BUF_256,
		UINT_C(256),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_256,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_256) && NUM_MPF_NET_BUF_256 > 0 */

#if defined(NUM_MPF_NET_BUF_128) && NUM_MPF_NET_BUF_128 > 0
	{
		MPF_NET_BUF_128,
		UINT_C(128),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_128,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_128) && NUM_MPF_NET_BUF_128 > 0 */

#if defined(SUPPORT_INET4)

#if defined(NUM_MPF_NET_BUF_64) && NUM_MPF_NET_BUF_64 > 0
	{
		MPF_NET_BUF_64,
		UINT_C(64),

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_64,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_64) && NUM_MPF_NET_BUF_64 > 0 */

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(NUM_MPF_NET_BUF_CSEG) && NUM_MPF_NET_BUF_CSEG > 0
	{
		MPF_NET_BUF_CSEG,
		IF_HDR_SIZE + IP_HDR_SIZE + TCP_HDR_SIZE,

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

		NUM_MPF_NET_BUF_CSEG,

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

		},
#endif	/* of #if defined(NUM_MPF_NET_BUF_CSEG) && NUM_MPF_NET_BUF_CSEG > 0 */

	};

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

/*
 *  nbuf_get_tbl -- �l�b�g���[�N�o�b�t�@�Ǘ��\���l������B
 *
 *    ����: �l�b�g���[�N���v���̌v���p
 */

const T_NET_BUF_ENTRY *
nbuf_get_tbl (void)
{
	return net_buf_table;
	}

/*
 *  nbuf_get_tbl_size -- �l�b�g���[�N�o�b�t�@�Ǘ��G���g�������l������B
 *
 *    ����: �l�b�g���[�N���v���̌v���p
 */

uint_t
nbuf_get_tbl_size (void)
{
	return sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY);
	}

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

/*
 *  tget_net_buf_up -- �傫�ȃT�C�Y�̕����ɒT�����āA�l�b�g���[�N�o�b�t�@���l������B
 */

static ER
tget_net_buf_up (T_NET_BUF **buf, uint_t minlen, uint_t maxlen, TMO tmout)
{
	int_t	ix, req_ix;
	ER	error = E_OK;

	/* �œK�ȃT�C�Y�̌Œ蒷�������v�[����T���B*/
	ix = sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY);
	while (ix -- > 0 && minlen > net_buf_table[ix].size)
		;
	req_ix = ix;

	NET_COUNT_NET_BUF(net_buf_table[req_ix].requests, 1);

	while (1) {
		if ((error = tget_mpf((ID)net_buf_table[ix].index, (void*)buf, ix == 0 ? tmout : TMO_POL)) == E_OK) {
			(*buf)->idix  = (uint8_t)ix;
			(*buf)->len   = (uint16_t)minlen;
			(*buf)->flags = 0;
			NET_COUNT_NET_BUF(net_buf_table[ix].allocs, 1);
			return error;
			}
		else if (ix == 0 || net_buf_table[ix].size > maxlen)
			break;
		ix --;
		}

	syslog(LOG_WARNING, "[NET BUF] busy, index=%d, len=%4d.", (uint16_t)req_ix, minlen);
	*buf = NULL;
	NET_COUNT_NET_BUF(net_buf_table[req_ix].errors, 1);
	return error;
	}

/*
 *  tget_net_buf_down -- �����ȃT�C�Y�̕����ɒT�����āA�l�b�g���[�N�o�b�t�@���l������B
 */

static ER
tget_net_buf_down (T_NET_BUF **buf, uint_t minlen, uint_t maxlen, TMO tmout)
{
	int_t	ix, req_ix;
	ER	error = E_OK;

	/* �œK�ȃT�C�Y�̌Œ蒷�������v�[����T���B*/
	ix = sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY);
	while (ix -- > 0 && maxlen > net_buf_table[ix].size)
		;
	req_ix = ix;

	NET_COUNT_NET_BUF(net_buf_table[req_ix].requests, 1);

	while (1) {
		if ((error = tget_mpf((ID)net_buf_table[ix].index, (void*)buf,
		                      ix == sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY) - 1 ? tmout : TMO_POL)) == E_OK) {
			(*buf)->idix  = (uint8_t)ix;
			(*buf)->len   = net_buf_table[ix].size;
			(*buf)->flags = 0;
			NET_COUNT_NET_BUF(net_buf_table[ix].allocs, 1);
			return error;
			}
		ix ++;
		if (ix == sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY) || net_buf_table[ix].size < minlen)
			break;
		}

	syslog(LOG_WARNING, "[NET BUF] busy, index=%d, len=%4d.", (uint16_t)req_ix, maxlen);
	*buf = NULL;
	NET_COUNT_NET_BUF(net_buf_table[req_ix].errors, 1);
	return error;
	}

/*
 *  tget_net_buf_ex -- �l�b�g���[�N�o�b�t�@���l������i�g���@�\�j�B
 */

ER
tget_net_buf_ex (T_NET_BUF **buf, uint_t minlen, uint_t maxlen, ATR nbatr, TMO tmout)
{
	/* �ŏ��T�C�Y���ő�T�C�Y�𒴂��Ă�����G���[ */
	if ((nbatr & NBA_SEARCH_DESCENT) != 0 && minlen > maxlen) {
		syslog(LOG_WARNING, "[NET BUF] E_PAR, minlen=%4d > maxlen=%4d.", minlen, maxlen);
		return E_PAR;
		}

	/* �����ĉ\�ȍő�̃T�C�Y�𒴂��Ă�����G���[ */
	if (minlen > net_buf_table[0].size || maxlen > net_buf_table[0].size) {
		syslog(LOG_WARNING, "[NET BUF] E_PAR, minlen=%4d or maxlen=%4d > %4d",
		                    minlen, maxlen, net_buf_table[0].size);
		return E_PAR;
		}

	/* TCP �ŗ\�񂵂��l�b�g���[�N�o�b�t�@�����o���B*/
	if ((nbatr & NBA_RESERVE_TCP) != 0) {
		if ((*buf = TCP_PULL_RES_NBUF(nbatr)) != NULL) {
			return E_OK;
			}
		}

	if ((nbatr & NBA_SEARCH_DESCENT) != 0)
		return tget_net_buf_down(buf, minlen, maxlen, tmout);
	else if ((nbatr & NBA_SEARCH_ASCENT) != 0)
		return tget_net_buf_up(buf, minlen, (uint_t)net_buf_table[0].size, tmout);
	else {
		syslog(LOG_WARNING, "[NET BUF] E_PAR, nbatr=%08x.", nbatr);
		return E_PAR;
		}
	}

/*
 *  tget_net_buf -- �l�b�g���[�N�o�b�t�@���l������i�݊��j�B
 */

ER
tget_net_buf (T_NET_BUF **buf, uint_t len, TMO tmout)
{
	return tget_net_buf_ex(buf, len, (uint_t)net_buf_table[0].size, NBA_SEARCH_ASCENT, tmout);
	}

/*
 * rel_net_buf -- �l�b�g���[�N�o�b�t�@��ԋp����B
 */

ER
rel_net_buf (T_NET_BUF *buf)
{
	ER	error = E_OK;

	/* �l�b�g���[�N�o�b�t�@�� ID �̐����������؂���B*/
	if ((int_t)buf->idix >= (int_t)(sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY))) {
		syslog(LOG_WARNING, "[NET BUF] E_ID, ID=%d.", buf->idix);
		error = E_ID;
		}
	else {

		/* TCP �ŁA�l�b�g���[�N�o�b�t�@��\�񂷂�B*/
		if (TCP_PUSH_RES_NBUF(buf) == NULL)
			return E_OK;

		/* �Œ胁�����v�[���ɕԂ��B*/
		if ((error = rel_mpf((ID)net_buf_table[buf->idix].index, buf)) != E_OK)
			syslog(LOG_WARNING, "[NET BUF] %s, ID=%d.", itron_strerror(error), buf->idix);
		}
	return error;
	}

/*
 * rus_net_buf -- �l�b�g���[�N�o�b�t�@���ė��p����B
 */

ER
rus_net_buf (T_NET_BUF *buf)
{
	ER	error = E_OK;

	if (buf->idix >= sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY)) {
		syslog(LOG_WARNING, "[NET BUF] E_ID, ID=%d.", buf->idix);
		error = E_ID;
		}
	else {
		buf->len   = net_buf_table[buf->idix].size;
		buf->flags = 0;
		error = E_OK;
		}
	return error;
	}

/*
 * net_buf_siz -- �l�b�g���[�N�o�b�t�@�̃T�C�Y��Ԃ��B
 */

ER_UINT
net_buf_siz (T_NET_BUF *buf)
{
	if (buf->idix >= sizeof(net_buf_table) / sizeof(T_NET_BUF_ENTRY)) {
		syslog(LOG_WARNING, "[BUF SIZ] E_ID, ID=%d.", buf->idix);
		return E_ID;
		}
	else
		return (ER_UINT)net_buf_table[buf->idix].size;
	}

/*
 * net_buf_max_siz -- �l�b�g���[�N�o�b�t�@�̍ő�T�C�Y��Ԃ��B
 */

uint_t
net_buf_max_siz (void)
{
	return (uint_t)net_buf_table[0].size;
	}
