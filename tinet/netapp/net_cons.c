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
 *  @(#) $Id: net_cons.c,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

/* 
 *  �l�b�g���[�N�o�R�R���\�[�����o��
 */

#include <stdarg.h>
#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include <syssvc/serial.h>
#include <syssvc/logtask.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>

#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include <netapp/netapp.h>
#include <netapp/netapp_var.h>
#include <netapp/net_cons.h>

#ifdef USE_NET_CONS

/*
 *  �}�N����`
 */

/*  ���l�[���̉���  */

#undef syslog
#undef serial_rea_dat
#undef serial_ctl_por

#define EOF		(-1)

/*  TELNET �I�v�V���� */

#define TELNET_OPT_SE		(240)
#define TELNET_OPT_NOP		(241)
#define TELNET_OPT_DM		(242)
#define TELNET_OPT_BRK		(243)
#define TELNET_OPT_IP		(244)
#define TELNET_OPT_AO		(245)
#define TELNET_OPT_AYT		(246)
#define TELNET_OPT_EC		(247)
#define TELNET_OPT_EL		(248)
#define TELNET_OPT_GA		(249)
#define TELNET_OPT_SB		(250)
#define TELNET_OPT_WILL		(251)
#define TELNET_OPT_WONT		(252)
#define TELNET_OPT_DO		(253)
#define TELNET_OPT_DONT		(254)
#define TELNET_OPT_IAC		(255)

/*
 *  �ϐ�
 */

/*  TCP ����M�E�B���h�o�b�t�@  */

uint8_t net_cons_swbuf[NET_CONS_SWBUF_SIZE];
uint8_t net_cons_rwbuf[NET_CONS_RWBUF_SIZE];

bool_t	connected	= false;	/* �R�l�N�V�����̏��	*/
bool_t	wait_accept	= false;	/* �ڑ��v���҂���	*/

#if defined(SUPPORT_INET4)

T_IPV4EP	dst;

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

T_IPV6EP	dst;

#endif	/* of #if defined(SUPPORT_INET6) */

uint8_t		*snd_buff	= NULL;
uint8_t		*rcv_buff	= NULL;
uint_t		snd_off		= 0;
uint_t		rcv_off		= 0;
uint_t		net_ioctl	= IOCTL_NULL;
ER_UINT		snd_len		= 0;
ER_UINT		rcv_len		= 0;

/*
 *  �m���u���b�L���O�R�[���̃R�[���o�b�N�֐�
 */

ER
callback_nblk_net_cons (ID cepid, FN fncd, void *p_parblk)
{
	ER	error = E_OK;
	SYSTIM	now;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		get_tim(&now);
		if (*(ER*)p_parblk == E_OK) {
			syslog(LOG_NOTICE, "[NCS:%02u CBN] connected:  %6lu, from: %s.%u",
			                   cepid, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
			connected = true;
			}
		else
			syslog(LOG_NOTICE, "[NCS:%02d CBN] error: %s", itron_strerror(*(ER*)p_parblk));
		snd_len = snd_off = rcv_len = rcv_off = 0;
		wait_accept = false;
		break;

	case TFN_TCP_CLS_CEP:
	case TFN_TCP_RCV_BUF:
	case TFN_TCP_GET_BUF:
	case TFN_TCP_RCV_DAT:
	case TFN_TCP_SND_DAT:
	case TFN_TCP_CON_CEP:
	case TFN_TCP_SND_OOB:
	default:
		error = E_PAR;
		break;
		}
	return error;
	}

/*
 *  ���M�o�b�t�@�̃t���b�V��
 */

void
flush_snd_buff (void)
{
	ER_UINT	error;

	if (connected) {
		syscall(wai_sem(SEM_NET_CONS_SEND));
		if (snd_off > 0) {
			if ((error = tcp_snd_buf(NET_CONS_CEPID, snd_off)) != E_OK && error != E_CLS)
				syslog(LOG_NOTICE, "[NCS:%02d SND] flush send error: %s",
				                   NET_CONS_CEPID, itron_strerror(error));
			snd_len = snd_off = 0;
			}
		syscall(sig_sem(SEM_NET_CONS_SEND));
		}
	return;
	}

/*
 *  �������M
 */

void
cons_putchar (ID portid, char ch)
{
	ER_UINT	error;

	if (connected) {
		if (ch == '\n' && (net_ioctl & IOCTL_CRLF) != 0)
			cons_putchar(portid, '\r');
		syscall(wai_sem(SEM_NET_CONS_SEND));
		if (snd_off >= snd_len) {
			if ((error = tcp_snd_buf(NET_CONS_CEPID, snd_off)) != E_OK) {
				if (error != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d SND] send buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(error));
				syscall(sig_sem(SEM_NET_CONS_SEND));
				return;
				}
			snd_off = 0;
			if ((snd_len = tcp_get_buf(NET_CONS_CEPID, (void*)&snd_buff, TMO_FEVR)) <= 0) {
				if (snd_len != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d SND] get buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(snd_len));
				syscall(sig_sem(SEM_NET_CONS_SEND));
				return;
				}
			}
		snd_buff[snd_off ++] = ch;
		syscall(sig_sem(SEM_NET_CONS_SEND));
		}
	else
		serial_wri_dat(portid, &ch, sizeof(ch));
	}

/*
 *  ������M�i�ϊ��Ȃ��j
 */

static int_t
cons_getchar_raw (void)
{
	ER	error = E_OK;

	if (connected) {
		if (rcv_off >= rcv_len) {
			rcv_off = 0;
			if ((error = tcp_rel_buf(NET_CONS_CEPID, rcv_len)) != E_OK) {
				if (error != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d RCV] release buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(error));
				discon_net_cons();
				return EOF;
				}
			if ((rcv_len = tcp_rcv_buf(NET_CONS_CEPID, (void*)&rcv_buff, TMO_FEVR)) == 0) {
				discon_net_cons();
				return EOF;
				}
			else if (rcv_len < 0) {
				if (rcv_len != E_CLS)
					syslog(LOG_NOTICE, "[NCS:%02d RCV] recieve buff error: %s",
					                   NET_CONS_CEPID, itron_strerror(rcv_len));
				discon_net_cons();
				return EOF;
				}
			}
		return rcv_buff[rcv_off ++];
		}
	else
		return EOF;
	}

/*
 *  ������M�iTELNET �I�v�V�������X�L�b�v�j
 */

int_t
cons_getchar (ID portid)
{
	T_SERIAL_RPOR	rpor;
	int_t		ch, req;
	char		uch;
	ER		error;

	if (!wait_accept && !connected) {
		wait_accept = true;
		error = TCP_ACP_CEP(NET_CONS_CEPID, NET_CONS_REPID, &dst, TMO_NBLK);
#if 0
		syslog(LOG_NOTICE, "[NCS:%02d ACP] status: %s",NET_CONS_CEPID, itron_strerror(error));
#endif
		if (error != E_WBLK)
			return EOF;
		}

	while (true) {
		if (connected) {
			while ((ch = cons_getchar_raw()) == TELNET_OPT_IAC || ch == '\0') {
				if (ch != '\0') {
					switch (ch = cons_getchar_raw()) {
					case TELNET_OPT_WILL:
					case TELNET_OPT_WONT:
					case TELNET_OPT_DO:
					case TELNET_OPT_DONT:
						req = cons_getchar_raw();
						break;
					case TELNET_OPT_SB:
						while ((ch = cons_getchar_raw()) != EOF && ch != TELNET_OPT_IAC) {
							if ((ch = cons_getchar_raw()) == EOF || ch == TELNET_OPT_SE)
								break;
							}
						break;
					default:
						break;
						}
					}
				}
			if (ch != '\n') {
				if ((net_ioctl & IOCTL_ECHO) != 0 && ch != EOF) {
					cons_putchar(portid, ch);
					flush_snd_buff();
					}
				return ch;
				}
			}

		else if (serial_ref_por(portid, &rpor) == E_OK && rpor.reacnt > 0) {
			if (serial_rea_dat(portid, &uch, sizeof(uch)) > 0)
				return uch;
			else
				return EOF;
			}
		dly_tsk(100);
		}
	return EOF;
	}

/*
 *  �R�l�N�V������ؒf
 */

ER
discon_net_cons (void)
{
	ER	error = E_OK;
	SYSTIM	now;

	if (connected) {
		syscall(wai_sem(SEM_NET_CONS_SEND));
		if (snd_off > 0) {
			if ((error = tcp_snd_buf(NET_CONS_CEPID, snd_off)) != E_OK && error != E_CLS)
				syslog(LOG_NOTICE, "[NCS:%02d SND] send buff error: %s",
				                   NET_CONS_CEPID, itron_strerror(error));
			}
		if ((error = tcp_sht_cep(NET_CONS_CEPID)) != E_OK)
			syslog(LOG_NOTICE, "[NCS:%02d SHT] shutdown error: %s",
			                   NET_CONS_CEPID, itron_strerror(error));
		if ((error = tcp_cls_cep(NET_CONS_CEPID, TMO_FEVR)) != E_OK)
			syslog(LOG_NOTICE, "[NCS:%02d CLS] close error: %s",
			                   NET_CONS_CEPID, itron_strerror(error));
		connected = false;
		syscall(sig_sem(SEM_NET_CONS_SEND));
		get_tim(&now);
		syslog(LOG_NOTICE, "[NCS:%02u SND] disconnected:%5lu, from: %s.%u",
		                   NET_CONS_CEPID, now / SYSTIM_HZ, IP2STR(NULL, &dst.ipaddr), dst.portno);
		}
	return error;
	}

/*
 *  �V���A���|�[�g�̐���
 */

ER
net_serial_ctl_por (ID portid, uint_t ioctl)
{
	net_ioctl = ioctl;
	return serial_ctl_por(portid, ioctl);
	}

/*
 *  ���O�o��
 */

ER
net_syslog (uint_t prio, const char *format, ...)
{
#if defined(SUPPORT_INET4)
	T_IN4_ADDR	*addr;
#endif	/* of #if defined(SUPPORT_INET4) */

	ulong_t		val;
	SYSLOG		log;
	va_list		ap;
	char		padchar, *str;
	int_t		ch, width, left, i;
	bool_t		longflag;

	if (connected) {
		syscall(wai_sem(SEM_NET_CONS_PRINTF));
		va_start(ap, format);
		while ((ch = *format ++) != '\0') {
			if (ch != '%') {		/* �����w��ȊO */
				cons_putchar(CONSOLE_PORTID, (char)ch);
				continue;
				}

			width = 0;
			longflag = false;
			padchar = ' ';

			if (ch == '-') {		/* ���l�� */
				format ++;
				left = -1;
				}
			else
				left = 1;

			if ((ch = *format ++) == '0') {	/* ��ʌ��� 0 */
				padchar = '0';
				ch = *format ++;
				}

			while ('0' <= ch && ch <= '9') {	/* �o�͕� */
				width = width * 10 + ch - '0';
				ch = *format ++;
				}

			while (ch == 'l') {		/* long (long) �̎w�� */
				longflag = true;
				ch = *format ++;
				}

			switch (ch) {
			case 'd':
				val = longflag ? (ulong_t)va_arg(ap, long_t)
				               : (ulong_t)va_arg(ap, int_t);
				if ((long_t)val >= 0)
					cons_putnumber(CONSOLE_PORTID,  val, 10, radhex, width * left, false, padchar);
				else
					cons_putnumber(CONSOLE_PORTID, -val, 10, radhex, width * left, true, padchar);
				break;

			case 'u':
				val = longflag ? (ulong_t)va_arg(ap, ulong_t)
				               : (ulong_t)va_arg(ap, uint_t);
				cons_putnumber(CONSOLE_PORTID, val, 10, radhex, width * left, false, padchar);
				break;

			case 'x':
				val = longflag ? (ulong_t)va_arg(ap, ulong_t)
				               : (ulong_t)va_arg(ap, uint_t);
				cons_putnumber(CONSOLE_PORTID, val, 16, radhex, width * left, false, padchar);
				break;

			case 'X':
				val = longflag ? (ulong_t)va_arg(ap, ulong_t)
				               : (ulong_t)va_arg(ap, uint_t);
				cons_putnumber(CONSOLE_PORTID, val, 16, radHEX, width * left, false, padchar);
				break;

			case 'c':
				ch = va_arg(ap, int_t);
				cons_putchar(CONSOLE_PORTID, (char)ch);
				break;

			case 's':
				str = va_arg(ap, char*);
				while ((ch = *str ++) != '\0') {
					cons_putchar(CONSOLE_PORTID, (char)ch);
					width --;
					}
				while (width -- > 0)
					cons_putchar(CONSOLE_PORTID, ' ');
				break;

			case 'I':

#if defined(SUPPORT_INET4)

				addr = va_arg(ap, T_IN4_ADDR*);
				put_ipv4addr(CONSOLE_PORTID, addr, width);

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

				str = va_arg(ap, char*);
				put_ipv6addr(CONSOLE_PORTID, (T_IN6_ADDR *)str, width);

#endif	/* of #if defined(SUPPORT_INET6) */

				break;

			case 'M':
				str = va_arg(ap, char*);
				put_macaddr(CONSOLE_PORTID, str, width);
				break;

			case '%':
				cons_putchar(CONSOLE_PORTID, '%');
				break;

			case '0':
				format --;
				break;

			default:
				break;
				}

			}
		va_end(ap);
		cons_putchar(CONSOLE_PORTID, '\n');
		flush_snd_buff();
		syscall(sig_sem(SEM_NET_CONS_PRINTF));
		return E_OK;
		}
	else {
		log.logtype = LOG_TYPE_COMMENT;
		log.loginfo[0] = (intptr_t)format;
		i = 1;
		va_start(ap, format);

		while ((ch = *format++) != '\0' && i < TMAX_LOGINFO) {
			if (ch != '%') {
				continue;
				}

			longflag = false;

			ch = *format++;
			while ('0' <= ch && ch <= '9') {
				ch = *format++;
				}

			while (ch == 'l') {		/* long (long) �̎w�� */
				longflag = true;
				ch = *format ++;
				}

			switch (ch) {
			case 'd':
				log.loginfo[i++] = longflag
					? (intptr_t)va_arg(ap, long_t) 
					: (intptr_t)va_arg(ap, int_t);
				break;
			case 'u':
			case 'x':
			case 'X':
				log.loginfo[i++] = longflag
					? (intptr_t)va_arg(ap, ulong_t)
					: (intptr_t)va_arg(ap, uint_t);
				break;
			case 'p':
				log.loginfo[i++] = (intptr_t)va_arg(ap, void *);
				break;
			case 'c':
				log.loginfo[i++] = (intptr_t)va_arg(ap, int_t);
				break;
			case 's':
				log.loginfo[i++] = (intptr_t)va_arg(ap, const char *);
				break;
			case '\0':
				format--;
				break;
			default:
				break;
				}
			}
		va_end(ap);

#ifdef TARGET_KERNEL_ASP

		return(syslog_wri_log(prio, &log));

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

		return(vwri_log(prio, &log));

#endif	/* of #ifdef TARGET_KERNEL_JSP */

		}
	}

#endif	/* of #ifdef USE_NET_CONS */
