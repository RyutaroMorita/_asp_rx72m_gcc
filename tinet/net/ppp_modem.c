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
 *  @(#) $Id: ppp_modem.c,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

/* 
 *  PPP ���f������
 */

#include <string.h>

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
#include <net/ppp_hdlc.h>
#include <net/ppp_modem.h>
#include <net/ppp_lcp.h>

#ifdef SUPPORT_PPP

/*
 *  �S��ϐ�
 */

uint8_t	modem_state = PPP_MODEM_DOWN;	/* ���f���̏��		*/

/*
 *  ���f�����͕�����
 */

#define MODEM_RCODE_OK		0
#define MODEM_RCODE_CONNECT	1
#define MODEM_RCODE_RING	2
#define MODEM_RCODE_NO_CARRIER	3
#define MODEM_RCODE_ERROR	4
#define MODEM_RCODE_NO_DIALTONE	5
#define MODEM_RCODE_BUSY	6
#define MODEM_RCODE_DELAYED	7

/*
 *  �ϐ�
 */

static uint8_t *modem_rcode[] = {
	"OK",
	"CONNECT",
	"RING",
	"NO CARRIER",
	"ERROR",
	"NO DIALTONE",
	"BUSY",
	"DELAYED"
	};

static int_t dial_retry;

/*
 *  �֐�
 */

static void do_dial (void);
static void modem_putstr (uint8_t *str);
static void modem_wait (uint8_t *line);
static void modem_putline (uint8_t *line);

/*
 *  modem_getline -- ���f���s����
 */

T_NET_BUF *
modem_getline (T_NET_BUF *nbuf, uint16_t size)
{
	uint8_t *buf;

	buf = nbuf->buf;
	size --;			/* '\0' �̕� */
	while (size > 0 && (*buf = HDLC_raw_getoctet()) != '\r') {
		buf  ++;
		size --;
		}
	*buf = '\0';
	HDLC_raw_getoctet();		/* \n ��ǂݔ�΂��B*/
	nbuf->len = buf - nbuf->buf;
	return nbuf;
	}

/*
 *  ���f������
 *
 *	�߂�l: ���f������̃��U���g�R�[�h
 */

int_t
modem_cntl (T_NET_BUF *input)
{
	int_t	code;

	code = sizeof(modem_rcode) / sizeof(uint8_t*) - 1;
	while (strcmp(modem_rcode[code], input->buf) != 0) {
		if (code == 0)
			return modem_state;
		code --;
		}

	switch (modem_state) {

	case PPP_MODEM_UP:
		if (code == MODEM_RCODE_RING)
			modem_state = PPP_MODEM_RING;
		break;

	case PPP_MODEM_DIAL:
		if (code == MODEM_RCODE_CONNECT) {
			syslog(LOG_NOTICE, "[MODEM] up.");
			modem_state = PPP_MODEM_CONNECT;
			lcp_open(PPP_OPEN_ACTIVE);
			sig_sem(SEM_MODEM_READY);
			}
		else {
			syslog(LOG_NOTICE, "[MODEM] dial failed '%s'.", modem_rcode[code]);
			if (-- dial_retry == 0) {
				syslog(LOG_WARNING, "[MODEM] dial failed %d times.", MODEM_CFG_RETRY_CNT);
				modem_state = PPP_MODEM_UP;
				}
			else {
				syscall(dly_tsk(MODEM_CFG_RETRY_WAIT));
				do_dial();
				}
			}
		break;

	case PPP_MODEM_RING:
		if (code == MODEM_RCODE_CONNECT) {
			syslog(LOG_NOTICE, "[MODEM] up.");
			modem_state = PPP_MODEM_CONNECT;
			lcp_open(PPP_OPEN_PASSIVE);
			}
		else
			modem_state = PPP_MODEM_UP;
		break;

	default:
		if (code == MODEM_RCODE_NO_CARRIER) {
			if (lcp_fsm.state == PPP_FSM_OPENED)
				lcp_close();
			syslog(LOG_NOTICE, "[MODEM] down.");
			modem_state = PPP_MODEM_UP;
			}
		break;

		}

	return code;
	}

/*
 *  init_modem -- ���f��������������B
 */

void
init_modem (void)
{
	modem_putline("AT");

#ifdef MODEM_CFG_INIT

	modem_putline(MODEM_CFG_INIT);

#endif	/* of #ifdef MODEM_CFG_INIT */

	modem_state = PPP_MODEM_UP;
	}

/*
 *  wait_modem -- �ڑ������܂ő҂B
 *
 *	�߂�l: �ڑ��Ɏ��s������ E_OBJ ��Ԃ��B
 */

ER
wait_modem (void)
{
	ER error = E_OK;

	if (modem_state == PPP_MODEM_UP) {
		dial();
		}

	if (modem_state != PPP_MODEM_CONNECT) {
		/* �ڑ������܂ő҂B*/
		wai_sem(SEM_MODEM_READY);
		if (modem_state != PPP_MODEM_CONNECT)
			error = E_OBJ;
		}

	return error;
	}

/*
 *  dial -- �_�C��������B���g���C�񐔂��Z�b�g����B
 */

void
dial (void)
{
	do_dial();
	dial_retry = MODEM_CFG_RETRY_CNT;
	modem_state = PPP_MODEM_DIAL;
	}

/*
 *  do_dial -- �_�C��������Bdial() �̉������֐�
 */

static void
do_dial (void)
{
	syslog(LOG_NOTICE, "[MODEM] dial: %s.", MODEM_CFG_PHONE_NUMBER);
	modem_putstr(MODEM_CFG_DIAL);
	modem_putstr(MODEM_CFG_PHONE_NUMBER);
	modem_putstr("\r");
	}

/*
 *  modem_putstr -- ���f��������o��
 */

static void
modem_putstr (uint8_t *str)
{
	while (*str)
		HDLC_raw_putoctet(*str ++);
	}

/*
 *  modem_wait -- ���f�����當�����҂�
 */

static void
modem_wait (uint8_t *line)
{
	int_t ch, state, len = strlen(line);

	state = len;
	while (state != 0) {
		ch = HDLC_raw_getoctet();
		if (ch != line[len - state])
			state = len;
		if (ch == line[len - state])
			state --;
		}
	}

/*
 *  modem_putline -- ���f���s�o��
 */

static void
modem_putline (uint8_t *line)
{
	modem_putstr(line);
	modem_putstr("\r");
	modem_wait("OK\r\n");
	}

#endif	/* fo #ifdef SUPPORT_PPP */
