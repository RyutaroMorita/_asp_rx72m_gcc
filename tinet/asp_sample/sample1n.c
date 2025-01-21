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
 *  @(#) $Id: sample1n.c,v 1.5.4.1 2015/02/05 02:08:29 abe Exp abe $
 */

/* 
 *  �l�b�g���[�N���T���v���v���O����(1)�̖{��
 */

#include <stdarg.h>

#include <kernel.h>
#include <t_syslog.h>
#include "syssvc/serial.h"
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>

#include "sample1n.h"

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

uint8_t tcp_swbuf[TCP_SWBUF_SIZE];
uint8_t tcp_rwbuf[TCP_RWBUF_SIZE];

bool_t		connected	= false;	/* �R�l�N�V�����̏��	*/
bool_t		wait_accept	= false;	/* �ڑ��v���҂���	*/

#ifdef SUPPORT_INET4

T_IPV4EP	dst;

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

T_IPV6EP	dst;

#endif	/* of #ifdef SUPPORT_INET6 */

uint8_t		*snd_buff	= NULL;
uint8_t		*rcv_buff	= NULL;
uint_t		snd_off		= 0;
uint_t		rcv_off		= 0;
ER_UINT		snd_len		= 0;
ER_UINT		rcv_len		= 0;
uint_t		net_ioctl	= IOCTL_NULL;
uint8_t		addr[sizeof("0123:4567:89ab:cdef:0123:4567:89ab:cdef")];

/*
 *  �l�b�g���[�N�w�̑I��
 */

#ifdef SUPPORT_INET4

#define TCP_ACP_CEP(c,r,d,t)	tcp_acp_cep(c,r,d,t)
#define IP2STR(s,a)		ip2str(s,a)

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

#define TCP_ACP_CEP(c,r,d,t)	tcp6_acp_cep(c,r,d,t)
#define IP2STR(s,a)		ipv62str(s,a)

#endif	/* of #ifdef SUPPORT_INET6 */

/*
 *  �m���u���b�L���O�R�[���̃R�[���o�b�N�֐�
 */

ER
callback_nblk_tcp (ID cepid, FN fncd, void *p_parblk)
{
	ER	error = E_OK;

	switch (fncd) {

	case TFN_TCP_ACP_CEP:
		IP2STR(addr, &dst.ipaddr);
		syslog(LOG_NOTICE, "connected:    %s.%d", addr, dst.portno);
		if (*(ER*)p_parblk == E_OK)
			connected = true;
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
 *  �R�l�N�V������ؒf
 */

ER
disconnecting (void)
{
	ER	error = E_OK;

	if (connected) {
		syscall(wai_sem(SEM_NET_SEND));
		if (snd_off > 0)
			tcp_snd_buf(TCP_CEPID, snd_off);
		tcp_sht_cep(TCP_CEPID);
		tcp_cls_cep(TCP_CEPID, TMO_FEVR);
		connected = false;
		syscall(sig_sem(SEM_NET_SEND));
		IP2STR(addr, &dst.ipaddr);
		syslog(LOG_NOTICE, "disconnected: %s.%d", addr, dst.portno);
		}
	return error;
	}

/*
 *  ���M�o�b�t�@�̃t���b�V��
 */

void
flush_snd_buff (ID cepid)
{
	if (connected) {
		syscall(wai_sem(SEM_NET_SEND));
		if (snd_off > 0) {
			tcp_snd_buf(cepid, snd_off);
			snd_len = snd_off = 0;
			}
		syscall(sig_sem(SEM_NET_SEND));
		}
	return;
	}

/*
 *  �������M
 */

void
put_char (ID cepid, char ch)
{
	if (connected) {
		if (ch == '\n' && (net_ioctl & IOCTL_CRLF) != 0)
			put_char(cepid, '\r');
		syscall(wai_sem(SEM_NET_SEND));
		if (snd_off >= snd_len) {
			if (tcp_snd_buf(cepid, snd_off) != E_OK) {
				syscall(sig_sem(SEM_NET_SEND));
				return;
				}
			snd_off = 0;
			if ((snd_len = tcp_get_buf(cepid, (void**)&snd_buff, TMO_FEVR)) <= 0) {
				syscall(sig_sem(SEM_NET_SEND));
				return;
				}
			}
		snd_buff[snd_off ++] = ch;
		syscall(sig_sem(SEM_NET_SEND));
		}
	}

/*
 *  ������M�i�ϊ��Ȃ��j
 */

int_t
get_char_raw (ID cepid)
{
	if (connected) {
		if (rcv_off >= rcv_len) {
			rcv_off = 0;
			if (tcp_rel_buf(TCP_CEPID, rcv_len) != E_OK) {
				disconnecting();
				return EOF;
				}
			if ((rcv_len = tcp_rcv_buf(TCP_CEPID, (void**)&rcv_buff, TMO_FEVR)) == 0) {
				disconnecting();
				return EOF;
				}
			else if (rcv_len < 0) {
				disconnecting();
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
get_char (ID cepid)
{
	int_t	ch, req;

	while ((ch = get_char_raw(cepid)) == TELNET_OPT_IAC || ch == '\0') {
		if (ch != '\0') {
			switch (ch = get_char_raw(cepid)) {
			case TELNET_OPT_WILL:
			case TELNET_OPT_WONT:
			case TELNET_OPT_DO:
			case TELNET_OPT_DONT:
				req = get_char_raw(cepid);
				break;
			case TELNET_OPT_SB:
				while ((ch = get_char_raw(cepid)) != EOF && ch != TELNET_OPT_IAC) {
					if ((ch = get_char_raw(cepid)) == EOF || ch == TELNET_OPT_SE)
						break;
					}
				break;
			default:
				break;
				}
			}
		}
	return ch;
	}

/*
 *  �V���A���|�[�g����̓Ǐo��
 */

ER_UINT
net_serial_rea_dat (ID portid, char_t *buf, uint_t len)
{
	T_SERIAL_RPOR	rpor;
	uint_t		off;
	int_t		ch;

	if (!wait_accept && !connected) {
		wait_accept = true;
		if (TCP_ACP_CEP(TCP_CEPID, TCP_REPID, &dst, TMO_NBLK) != E_WBLK)
			return 0;
		}

	while (true) {
		if (connected) {
			off = 0;
			while (off < len && (ch = get_char(TCP_CEPID)) != EOF) {
				*(buf + off ++) = ch;
				if ((net_ioctl & IOCTL_ECHO) != 0) {
					put_char(TCP_CEPID, ch);
					flush_snd_buff(TCP_CEPID);
					}
				}
			return off;
			}
		else if (serial_ref_por(portid, &rpor) == E_OK && rpor.reacnt > 0) {
			return serial_rea_dat(portid, buf, len);
			}
		dly_tsk(500);
		}
	return off;
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
 *  �����Ƃ����������^ (LONGEST) �ƕ����Ȃ������^ (ULONGEST)
 */

#ifdef LONGLONG_TYPE

typedef LONGLONG_TYPE		LONGEST;
typedef unsigned LONGLONG_TYPE	ULONGEST;

#else	/* of #ifdef LONGLONG_TYPE */

#ifdef LONG_TYPE

typedef LONG_TYPE		LONGEST;
typedef unsigned LONG_TYPE	ULONGEST;

#else	/* of #ifdef LONG_TYPE */

typedef int_t			LONGEST;
typedef uint_t			ULONGEST;

#endif	/* of #ifdef LONG_TYPE */

#endif	/* of #ifdef LONGLONG_TYPE */

/*
 *  ���O�̃V�~�����[�V����
 */

/*  ���l�ϊ��̂��߂̕ϊ��\  */

static const char radhex[] = "0123456789abcdef";
static const char radHEX[] = "0123456789ABCDEF";

/*
 *  put_num -- printf �̐��l�ϊ�
 */

int_t
put_num(ID cepid, ULONGEST val, int_t radix, const char *radchar, int_t width, bool_t minus, char padchar)
{
	char	digits[24];
	int_t	ix, pad, pchars;
	bool_t	left;

	if (width < 0) {
		width = -width;
		left = true;
		}
	else
		left = false;

	ix = 0;
	do {
		digits[ix ++] = radchar[val % radix];
		val /= radix;
		} while (val != 0);

	if (minus)
		digits[ix ++] = '-';

	if (width > ix)
		pchars = width;
	else
		pchars = ix;

	pad = ix;
	if (!left)	/* �E�l�� */
		for ( ; pad < width; pad ++)
			put_char(cepid, padchar);

	while (ix -- > 0)
		put_char(cepid, digits[ix]);

	if (left)	/* ���l�� */
		for ( ; pad < width; pad ++)
			put_char(cepid, padchar);

	return pchars;
	}

#ifdef SUPPORT_INET4

/*
 *  put_ipv4addr -- IPv4 �A�h���X�o��
 */

static int_t
put_ipv4addr (ID cepid, ULONGEST *addr, int_t width)
{
	int_t len = 3;	/* 3 �� '.' �̕����� */

#if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN

	len += put_num(cepid, (*addr >> 24) & 0xff, 10, radhex, 0, false, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >> 16) & 0xff, 10, radhex, 0, false, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >>  8) & 0xff, 10, radhex, 0, false, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid,  *addr        & 0xff, 10, radhex, 0, false, ' '); 

#else	/* of #if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN */

	len += put_num(cepid,  *addr        & 0xff, 10, radhex, 0, false, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >>  8) & 0xff, 10, radhex, 0, false, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >> 16) & 0xff, 10, radhex, 0, false, ' '); 
	put_char(cepid, '.');
	len += put_num(cepid, (*addr >> 24) & 0xff, 10, radhex, 0, false, ' '); 

#endif	/* of #if _NET_CFG_BYTE_ORDER == _NET_CFG_BIG_ENDIAN */

	for ( ; len < width; len ++)
		put_char(cepid, ' ');

	return len;
	}

#define PUT_IPADDR(p,a,w)	put_ipv4addr(p,a,w)

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

/*
 *  ipv6addr -- IPv6 �A�h���X�o��
 */

static int_t
put_ipv6addr (ID cepid, const T_IN6_ADDR *addr, int_t width)
{
	int_t	len = 0, ix;
	bool_t	omit = false, zero = false;

	if (addr == NULL) {
		put_char(cepid, '0');
		put_char(cepid, ':');
		put_char(cepid, ':');
		put_char(cepid, '0');
		len = 4;
		}
	else {
		for (ix = 0; ix < sizeof(T_IN6_ADDR) / 2; ix ++) {
			if (omit) {
				len += put_num(cepid, addr->s6_addr16[ix], 16, radhex, 0, false, ' '); 
				if (ix < 7) {
					put_char(cepid, ':');
					len ++;
					}
				}
			else if (ix > 0 && ix < 7 && addr->s6_addr16[ix] == 0)
				zero = true;
			else {
				if (zero) {
					omit = true;
					put_char(cepid, ':');
					len ++;
					}
				len += put_num(cepid, addr->s6_addr16[ix], 16, radhex, 0, false, ' '); 
				if (ix < 7) {
					put_char(cepid, ':');
					len ++;
					}
				}
			}

		for ( ; len < width; len ++)
			put_char(cepid, ' ');
		}
	return len;
	}

#define PUT_IPADDR(p,a,w)	put_ipv6addr(p,a,w)

#endif	/* of #ifdef SUPPORT_INET6 */

/*
 *  put_macaddr -- MAC �A�h���X�o��
 */

static int_t
put_macaddr (ID cepid, char *mac, int_t width)
{
	int_t oct, len;

	for (oct = 5; oct -- > 0; ) {
		put_num(cepid, *mac ++, 16, radhex, 2, false, '0'); 
		put_char(cepid, ':');
		}
	put_num(cepid, *mac, 16, radhex, 2, false, '0'); 

	for (len = 17; len < width; len ++)
		put_char(cepid, ' ');

	return len;
	}

/*
 *  ���������o�����߂̃}�N��
 */

#ifdef LONGLONG_TYPE

#ifdef LONG_TYPE

#define GET_ARG(ap,lf)	((lf > 1) ? va_arg(ap, LONGLONG_TYPE)	\
			 (lf      ? va_arg(ap, LONG_TYPE)	\
			          : va_arg(ap, int_t)))

#else	/* of #ifdef LONG_TYPE */

#define GET_ARG(ap,lf)	((lf > 1) ? va_arg(ap, LONGLONG_TYPE)	\
			          : va_arg(ap, int_t))

#endif	/* of #ifdef LONG_TYPE */

#else	/* of #ifdef LONGLONG_TYPE */

#ifdef LONG_TYPE

#define GET_ARG(ap,lf)	 (lf      ? va_arg(ap, LONG_TYPE)	\
			          : va_arg(ap, int_t))

#else	/* of #ifdef LONG_TYPE */

#define GET_ARG(ap,lf)	(va_arg(ap, int_t))

#endif	/* of #ifdef LONG_TYPE */

#endif	/* of #ifdef LONGLONG_TYPE */

/*
 *  ���O�o��
 */

ER
net_syslog (uint_t prio, const char *format, ...)
{
	LONGEST	val;
	SYSLOG	log;
	va_list	ap;
	char	padchar, *str;
	int_t	ch, width, longflag, left, i, c;

	if (connected) {
		syscall(wai_sem(SEM_TCP_SYSLOG));
		va_start(ap, format);
		while ((ch = *format ++) != '\0') {
			if (ch != '%') {		/* �����w��ȊO */
				put_char(TCP_CEPID, (char)ch);
				continue;
				}

			width = longflag = 0;
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
				longflag ++;
				ch = *format ++;
				}

			switch (ch) {
			case 'd':
				val = GET_ARG(ap, longflag);
				if (val >= 0)
					put_num(TCP_CEPID,  val, 10, radhex, width * left, false, padchar);
				else
					put_num(TCP_CEPID, -val, 10, radhex, width * left, true, padchar);
				break;

			case 'u':
				val = GET_ARG(ap, longflag);
				put_num(TCP_CEPID, val, 10, radhex, width * left, false, padchar);
				break;

			case 'x':
				val = GET_ARG(ap, longflag);
				put_num(TCP_CEPID, val, 16, radhex, width * left, false, padchar);
				break;

			case 'X':
				val = GET_ARG(ap, longflag);
				put_num(TCP_CEPID, val, 16, radHEX, width * left, false, padchar);
				break;

			case 'c':
				ch = va_arg(ap, int_t);
				put_char(TCP_CEPID, (char)ch);
				break;

			case 's':
				str = va_arg(ap, char*);
				while ((ch = *str ++) != '\0') {
					put_char(TCP_CEPID, (char)ch);
					width --;
					}
				while (width -- > 0)
					put_char(TCP_CEPID, ' ');
				break;

			case 'I':

#ifdef SUPPORT_INET4

				val = GET_ARG(ap, longflag);
				put_ipv4addr(TCP_CEPID, (ULONGEST *)val, width);

#endif	/* of #ifdef SUPPORT_INET4 */

#ifdef SUPPORT_INET6

				str = va_arg(ap, char*);
				put_ipv6addr(TCP_CEPID, (T_IN6_ADDR *)str, width);

#endif	/* of #ifdef SUPPORT_INET6 */

				break;

			case 'M':
				str = va_arg(ap, char*);
				put_macaddr(TCP_CEPID, str, width);
				break;

			case '%':
				put_char(TCP_CEPID, '%');
				break;

			case '0':
				format --;
				break;

			default:
				break;
				}

			}
		va_end(ap);
		put_char(TCP_CEPID, '\n');
		flush_snd_buff(TCP_CEPID);
		syscall(sig_sem(SEM_TCP_SYSLOG));
		return E_OK;
		}
	else {
		log.logtype = LOG_TYPE_COMMENT;
		log.loginfo[0] = (intptr_t)format;
		i = 1;
		va_start(ap, format);

		while ((c = *format++) != '\0' && i < TMAX_LOGINFO) {
			if (c != '%') {
				continue;
				}

			c = *format++;
			while ('0' <= c && c <= '9') {
				c = *format++;
				}
			switch (c) {
			case 'd':
				log.loginfo[i++] = (intptr_t)va_arg(ap, int_t);
				break;
			case 'u':
			case 'x':
			case 'X':
				log.loginfo[i++] = (intptr_t)va_arg(ap, uint_t);
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
		return(syslog_wri_log(prio, &log));
		}
	}
