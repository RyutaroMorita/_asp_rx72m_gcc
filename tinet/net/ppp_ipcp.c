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
 *  @(#) $Id: ppp_ipcp.c,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/*
 * ipcp.c - PPP IP Control Protocol.
 *
 * Copyright (c) 1989 Carnegie Mellon University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Carnegie Mellon University.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 *	PPP IP Control Protocol (IPCP) Module
 *
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan, Inc.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/ipcp.c,v 1.90.2.4 2000/08/19 09:30:03 brian Exp $
 *
 *	TODO:
 *		o Support IPADDRS properly
 *		o Validate the length in IpcpDecodeConfig
 */

#include <string.h>

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>
#include <net/ppp.h>
#include <net/ppp_var.h>
#include <net/ppp_fsm.h>
#include <net/ppp_lcp.h>
#include <net/ppp_ipcp.h>
#include <net/ppp_modem.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp_var.h>

#include <net/if_var.h>

#ifdef SUPPORT_PPP

/*
 *  �֐�
 */

static void ipcp_init (void);
static void ipcp_input (T_NET_BUF *input);
static void ipcp_protrej (void);
static void ipcp_lowerup (void);
static void ipcp_lowerdown (void);
static void ipcp_open (void);
static void ipcp_close (void);

/*
 * FSM ����ďo�����R�[���o�b�N��
 */

static void  ipcp_resetci(T_PPP_FSM *fsm);	/* ���\���������Z�b�g����B	*/
static int_t ipcp_cilen	(T_PPP_FSM *fsm);	/* �\�����̒�����Ԃ��B		*/
static void  ipcp_addci	(T_PPP_FSM *fsm, T_NET_BUF *output);
						/* ���\������ǉ�����B		*/
static bool_t  ipcp_ackci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* ACK ����M�����Ƃ��̏���	*/
static bool_t  ipcp_nakci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* NAK ����M�����Ƃ��̏���	*/
static bool_t  ipcp_rejci	(T_PPP_FSM *fsm, T_NET_BUF *input);
						/* REJ ����M�����Ƃ��̏���	*/
static int_t ipcp_reqci	(T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output);
						/* ����̍\�������m�F����B	*/
static void ipcp_up	(T_PPP_FSM *fsm);	/* �����N�ڑ����m������B		*/
static void ipcp_down	(T_PPP_FSM *fsm);	/* �����N�ڑ����������B		*/
static void ipcp_finished(T_PPP_FSM *fsm);	/* ���ʑw���I������B		*/

/*
 *  �ϐ�
 */

static T_IFNET ipcp_local_def_cfg = {		/* ���\�����̋K��l		*/
	NULL,
	{
		IPV4_ADDR_LOCAL,		/* IP �A�h���X			*/
		UINT_C(0),			/* �T�u�l�b�g�}�X�N		*/
		},
	};

static T_IFNET ipcp_remote_def_cfg = {		/* ����̍\�����̋K��l	*/
	NULL,
	{
		IPV4_ADDR_REMOTE,		/* IP �A�h���X			*/
		UINT_C(0),			/* �T�u�l�b�g�}�X�N		*/
		}
	};

static T_IFNET ipcp_local_neg_cfg;		/* �l�S���̎��\�����		*/

static T_IFNET ipcp_remote_neg_cfg;		/* �l�S���̑���̍\�����		*/

/*
 *  �S��ϐ�
 */

T_PPP_FSM_CALLBACKS ipcp_callbacks = {
	ipcp_resetci,			/* ���\���������Z�b�g����B	*/
	ipcp_cilen,			/* �\�����̒�����Ԃ��B		*/
	ipcp_addci,			/* ���\������ǉ�����B		*/
	ipcp_ackci,			/* ACK ����M�����Ƃ��̏���	*/
	ipcp_nakci,			/* NAK ����M�����Ƃ��̏���	*/
	ipcp_rejci,			/* REJ ����M�����Ƃ��̏���	*/
	ipcp_reqci,			/* ����̍\�������m�F����B	*/
	ipcp_up,			/* �����N�ڑ����m������B		*/
	ipcp_down,			/* �����N�ڑ����������B		*/
	NULL,				/* ���ʑw���J�n����B		*/
	ipcp_finished,			/* ���ʑw���I������B		*/
	NULL,				/* �đ�����B			*/
	NULL,				/* �s���� CP ����M�����Ƃ��̏���	*/
	};

T_PPP_FSM ipcp_fsm = {
	&ipcp_callbacks,		/* �R�[���o�b�N�֐�		*/
	PPP_IPCP,			/* �v���g�R��			*/
	};

T_PPP_PROTENT ipcp_protent = {
	PPP_IPCP,
	ipcp_init,			/* ������			*/
	ipcp_input,			/* ����				*/
	ipcp_protrej,			/* Proto-REJ ��M����		*/
	ipcp_lowerup,			/* ���ʑw���N������		*/
	ipcp_lowerdown,			/* ���ʑw���~����		*/
	ipcp_open,			/* �I�[�v������			*/
	ipcp_close,			/* �N���[�Y����			*/
	ip_input,			/* �f�[�^���́AIP ����		*/
	};

T_IFNET ipcp_local_ack_cfg;		/* ����ɋ����ꂽ�̎��\�����	*/
T_IFNET ipcp_remote_ack_cfg;		/* ����ɋ������\�����	*/

/*
 *  ppp_get_ifnet -- �l�b�g���[�N�C���^�t�F�[�X�\���̂�Ԃ��B
 */

T_IFNET *
ppp_get_ifnet (void)
{
	return &ipcp_local_ack_cfg;
	}

/*
 *  wait_ipcp -- IP �ڑ������܂ő҂B
 *
 *	�߂�l: �ڑ��Ɏ��s������ E_OBJ ��Ԃ��B
 */

ER
wait_ipcp (void)
{
#ifdef PPP_CFG_MODEM
	ER error;
#endif	/* of #ifdef PPP_CFG_MODEM */

	if (ipcp_fsm.state <= PPP_FSM_STOPPED) {

#ifdef PPP_CFG_MODEM

		/* ���f���̐ڑ������܂ő҂B*/
		if ((error = wait_modem()) != E_OK)
			return error;

#else	/* of #ifdef PPP_CFG_MODEM */

		/*
		 * �󓮃I�[�v�����A���肩��̐ڑ��҂��Ȃ� LCP ����x�N���[�Y���A
		 * �\���I�[�v����ԂŁA�ăI�[�v������B
		 */
		lcp_close();
		lcp_open(PPP_OPEN_ACTIVE);

#endif	/* of #ifdef PPP_CFG_MODEM */

		}

	if (ipcp_fsm.state != PPP_FSM_OPENED) {
		/* IP �ڑ������܂ő҂B*/
		wai_sem(SEM_IPCP_READY);
		if (ipcp_fsm.state != PPP_FSM_OPENED)
			return E_OBJ;
		}

	return E_OK;
	}

/*
 *  ipcp_init -- IPCP ���W���[���̏�����
 */

static void
ipcp_init (void)
{
	fsm_init(&ipcp_fsm);
	}

/*
 *  ipcp_input -- IPCP ����
 */

static void
ipcp_input (T_NET_BUF *input)
{
	NET_COUNT_PPP_IPCP(net_count_ppp_ipcp_in_octets,  input->len);
	NET_COUNT_PPP_IPCP(net_count_ppp_ipcp_in_packets, 1);
	fsm_input(&ipcp_fsm, input);
	}

/*
 *  ipcp_resetci -- IPCP�̍\���������Z�b�g����B
 */

static void
ipcp_resetci (T_PPP_FSM *fsm)
{
	/* ���\�����̏����ݒ� */
	ipcp_local_neg_cfg = ipcp_local_def_cfg;
	memset((void*)&ipcp_local_ack_cfg, 0, sizeof(T_IFNET));

	/* ����̍\�����̏����ݒ� */
	ipcp_remote_neg_cfg = ipcp_remote_def_cfg;
	memset((void*)&ipcp_remote_ack_cfg, 0, sizeof(T_IFNET));
	}

/*
 *  ipcp_cilen -- �\�����̒�����Ԃ��B
 */

static int_t
ipcp_cilen (T_PPP_FSM *fsm)
{
	int_t cilen = 0;

	cilen += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);	/* IP �A�h���X */

	return cilen;
	}

/*
 *  ipcp_addci -- IPCP�̍\������ǉ�����B
 */

static void
ipcp_addci (T_PPP_FSM *fsm, T_NET_BUF *output)
{
	uint8_t *buf;

	buf = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);

	/* IP �A�h���X�I�v�V������ǉ�����B */
	*buf ++ = IPCP_CIT_ADDR;
	*buf ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
	ahtonl(buf, ipcp_local_neg_cfg.in_ifaddr.addr);
	buf += sizeof(uint32_t);
	}

/*
 *  ipcp_ackci -- ACK ����M�����Ƃ��̏���
 *
 *	�߂�l:	true  ACK �͐���
 *		false ACK �ُ͈�
 */

static bool_t
ipcp_ackci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	uint8_t		*buf;
	uint16_t	len;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	/*
	 *  �\�����͑��M�������Ɋ��S�Ɉ�v���Ȃ���΂Ȃ�Ȃ��B
	 *  �]���āAipcp_addci �ō쐬�������ɉ�͂���B
	 */

	/* ADDR �I�v�V��������͂���B */
	if (len < sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)	||
	    *buf ++ != IPCP_CIT_ADDR			||
	    *buf ++ != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)||
	    nahcmpl(buf, ipcp_local_neg_cfg.in_ifaddr.addr))
		return false;
	buf += sizeof(uint32_t);
	len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);

	return true;
	}

/*
 *  ipcp_nakci -- NAK ����M�����Ƃ��̏���
 *
 *	�߂�l:	1  NAK �͐���
 *		0  NAK �ُ͈�
 */

static int_t
ipcp_nakci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_IFNET		new_cfg;
	uint32_t	cilong;
	uint16_t	len;
	uint8_t		*buf, cilen;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = ipcp_local_neg_cfg;

	/* ADDR �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == IPCP_CIT_ADDR				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)) {
	    	ntoahl(cilong, buf + 2);
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.in_ifaddr.addr = cilong;
		}

	/* ��͖�������B*/
	while (len > sizeof(T_PPP_CI_HDR)) {
		cilen = *(buf + 1);
		if (len < cilen)
			return 0;
		buf += cilen;
		len -= cilen;
		}

	/* ������ 0 �łȂ���΃G���[ */
	if (len != 0)
		return 0;

	/* �V�����I�v�V������ݒ肷��B*/
	if (fsm->state != PPP_FSM_OPENED)
		ipcp_local_neg_cfg = new_cfg;
               		
	return 1;
	}

/*
 *  ipcp_rejci -- REJ ����M�����Ƃ��̏���
 *
 *	�߂�l:	1  REJ �͐���
 *		0  REJ �ُ͈�
 */

static int_t
ipcp_rejci (T_PPP_FSM *fsm, T_NET_BUF *input)
{
	T_IFNET		new_cfg;
	uint8_t		*buf;
	uint16_t	len;

	buf = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	len = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));

	new_cfg = ipcp_local_neg_cfg;

	/* ADDR �I�v�V��������͂���B */
	if (len >= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)		&&
	    * buf      == IPCP_CIT_ADDR				&&
	    *(buf + 1) == sizeof(T_PPP_CI_HDR) + sizeof(uint32_t)) {
		buf += sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		len -= sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
		new_cfg.in_ifaddr.addr = 0;
		}

	/* ������ 0 �łȂ���΃G���[ */
	if (len != 0)
		return 0;

	/* �V�����I�v�V������ݒ肷��B*/
	if (fsm->state != PPP_FSM_OPENED)
		ipcp_local_neg_cfg = new_cfg;

	return 1;
	}

/*
 *  ipcp_reqci -- ����̍\��������͂���B
 */

static int_t
ipcp_reqci (T_PPP_FSM *fsm, T_NET_BUF *input, T_NET_BUF *output)
{
	uint32_t	addr;
	uint16_t	code, final, len, cilen;
	uint8_t		*np, *rp, *ap, *cp, type = 0;

	rp = ap = input->buf +  sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
				/* rp: REJ�Aap: ACK ���� CI �̃|�C���^	*/
				/* ���ۂ���ꍇ�́A���� buf �ɏ㏑������B	*/
	len   = input->len - (sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
	np    = output->buf + sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR);
	final = PPP_CONFACK;	/* �ŏI�I�ɑ��M����R�[�h */
	while (len > 0) {
		code = PPP_CONFACK;
		cp   = ap;	/* cp: ���ݏ������� CI	*/

		if (len < sizeof(T_PPP_CI_HDR)) {

			/* �c�肪 CI �w�b�_���Z�� */
			syslog(LOG_NOTICE, "[PPP/IPCP] bad CI len: %d.", len);
			cilen = len;	/* �f�[�^�����ُ�̏ꍇ�̏��u	*/
			len  = 0;	/* ���[�v���甲����B		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}

		type  = *ap ++;	/* CI �̌^		*/
		cilen = *ap ++;	/* CI �̒���		*/
		if (len < cilen) {

			/* �c�肪 CI �����Z�� */
			syslog(LOG_NOTICE, "[PPP/IPCP] bad CI len: %d.", cilen);
			cilen = len;	/* �f�[�^�����ُ�̏ꍇ�̏��u	*/
			len  = 0;	/* ���[�v���甲����B		*/
			code  = PPP_CONFREJ;
			goto endswitch;
			}
		len -= sizeof(T_PPP_CI_HDR);

		/* CI �̌^�ɂ�蕪�򂷂�B*/
		switch (type) {

		case IPCP_CIT_ADDR:	/* IP �A�h���X */

		 	/* CI �����A�w�b�_ + 4 �I�N�e�b�g�łȂ���΃G���[ */
		 	if (cilen != sizeof(T_PPP_CI_HDR) + sizeof(uint32_t))
				code = PPP_CONFREJ;
			else {
				ntoahl(addr, ap);
				if (addr != ipcp_remote_neg_cfg.in_ifaddr.addr &&
				    (addr == 0 || ipcp_remote_neg_cfg.in_ifaddr.addr != 0)) {
					*np ++ = IPCP_CIT_ADDR;
					*np ++ = sizeof(T_PPP_CI_HDR) + sizeof(uint32_t);
					ahtonl(np, ipcp_remote_neg_cfg.in_ifaddr.addr);
					np  += sizeof(uint32_t);
					code = PPP_CONFNAK;
					}
#if 1	/* �v�m�F */
				else if (addr == 0 && ipcp_remote_neg_cfg.in_ifaddr.addr == 0)
#else
				else if (addr == 0 || ipcp_remote_neg_cfg.in_ifaddr.addr == 0)
#endif
					code = PPP_CONFREJ;
				else
					ipcp_remote_neg_cfg.in_ifaddr.addr = addr;
				}
			break;

		default:
			syslog(LOG_INFO, "[PPP/IPCP] unexp opt: %d.", type);
			code = PPP_CONFREJ;
			break;
			}
endswitch:

		if (code == PPP_CONFNAK) {
			/* CI �̌^�� Magic Number �̏ꍇ�������āANAK �̉񐔂�	*/
			/* �ő�l MAX_PPP_FAILURES  �𒴂����狑�ۂ���B	*/
			if (fsm->failures >= MAX_PPP_FAILURES)
				code = PPP_CONFREJ;
			else if (final != PPP_CONFREJ)
				final = PPP_CONFNAK;
			}

		/* ���� CI �����ۂ��� */
		if (code == PPP_CONFREJ) {
			if (rp < cp)		/* �O�ɋl�߂�B*/
				memcpy(rp, cp, cilen);
			rp += cilen;
			final = PPP_CONFREJ;
			}

		ap   += cilen - sizeof(T_PPP_CI_HDR);
		len  -= cilen - sizeof(T_PPP_CI_HDR);
		}

	/* �ŏI�I�Ȓ����𒲐�����B*/
	switch (final) {
	case PPP_CONFNAK:
		output->len = np - output->buf;
		memcpy(output->buf, input->buf, sizeof(T_PPP_HDR) + sizeof(T_PPP_CP_HDR));
		break;
	case PPP_CONFREJ:
		memcpy(output->buf, input->buf, output->len = rp - input->buf);
		break;
	case PPP_CONFACK:
		memcpy(output->buf, input->buf, input->len);
		break;
		}

	return final;
	}

/*
 *  ipcp_up -- �����N�ڑ����m������B
 */

static void
ipcp_up (T_PPP_FSM *fsm)
{
	/* ���\�����̏����ݒ� */
	ipcp_local_ack_cfg = ipcp_local_neg_cfg;

	/*
	 *  �T�u�l�b�g�}�X�N��
	 *  ���[�J���E�u���[�h�L���X�g IP �A�h���X��ݒ肷��B
	 */
	ipcp_local_ack_cfg.in_ifaddr.mask = MAKE_IPV4_LOCAL_MASK(ipcp_local_neg_cfg.in_ifaddr.addr);

	/* ����̍\�����̏����ݒ� */
	ipcp_remote_ack_cfg = ipcp_remote_neg_cfg;

	/*
	 *  �T�u�l�b�g�}�X�N��
	 *  ���[�J���E�u���[�h�L���X�g IP �A�h���X��ݒ肷��B
	 */
	ipcp_remote_ack_cfg.in_ifaddr.mask = MAKE_IPV4_LOCAL_MASK(ipcp_remote_neg_cfg.in_ifaddr.addr);

	sig_sem(SEM_IPCP_READY);

	syslog(LOG_NOTICE, "[PPP/IPCP] up, Local IP Addr: %s, Remote IP Addr: %s.",
	                   ip2str(NULL, &ipcp_local_neg_cfg.in_ifaddr.addr),
	                   ip2str(NULL, &ipcp_remote_neg_cfg.in_ifaddr.addr));
	}

/*
 *  ipcp_down -- �����N�ڑ����������B
 */

static void
ipcp_down (T_PPP_FSM *fsm)
{
	sig_sem(SEM_IPCP_READY);
	syslog(LOG_NOTICE, "[PPP/IPCP] down.");
	}

/*
 *  ipcp_finished -- ���ʑw���I������B
 */

static void
ipcp_finished (T_PPP_FSM *fsm)
{
	}

/*
 *  ipcp_protrej -- Proto-REJ ����M�����Ƃ��̏���
 */

static void
ipcp_protrej (void)
{
	fsm_lowerdown(&ipcp_fsm);
	}

/*
 *  ipcp_lowerup -- IPCP ���ʑw���N������B
 */

static void
ipcp_lowerup (void)
{
	fsm_lowerup(&ipcp_fsm);
	}

/*
 *  ipcp_lowerdown -- IPCP ���ʑw���~����B
 */

static void
ipcp_lowerdown (void)
{
	fsm_lowerdown(&ipcp_fsm);
	}

/*
 *  ipcp_open -- IPCP �̃I�[�v��
 */

static void
ipcp_open (void)
{
	fsm_open(&ipcp_fsm);
	}

/*
 *  ipcp_close -- IPCP �̃N���[�Y
 */

static void
ipcp_close (void)
{
	fsm_close(&ipcp_fsm);
	}

#endif	/* fo #ifdef SUPPORT_PPP */
