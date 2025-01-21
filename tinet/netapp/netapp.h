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
 *  @(#) $Id: netapp.h,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

#ifndef _NETAPP_H_
#define _NETAPP_H_

/*
 *  IPv4 �� IPv6 �̐؊����}�N��
 */

#if defined(SUPPORT_INET4)
#define PUT_IPADDR(p,a,w)	put_ipv4addr(p,a,w)
#endif

#if defined(SUPPORT_INET6)
#define PUT_IPADDR(p,a,w)	put_ipv6addr(p,a,w)
#endif

/*
 *  �R���\�[���ɗp����V���A���|�[�g�ԍ�
 */

#ifndef CONSOLE_PORTID

#define	CONSOLE_PORTID		LOGTASK_PORTID

#endif	/* of #ifndef CONSOLE_PORTID */

/*
 *  ���l�ϊ��̂��߂̕ϊ��\
 */

extern const char radhex[];
extern const char radHEX[];

/*
 *  �֐�
 */

extern char *skip_blanks (char *line);
extern int_t cons_getline (ID portid, char *line, int_t size);
extern char *get_int (int_t *val, char *line);
extern char *get_xuint (uint_t *val, char *line);
extern void cons_putchar (ID portid, char ch);
extern int_t cons_getchar (ID portid);
extern int_t cons_putnumber (ID portid, ulong_t val, int_t radix,
                           const char *radchar, int_t width,
                           bool_t minus, char padchar);
extern void cons_printf (ID portid, const char *fmt, ...);
extern int_t put_macaddr (ID portid, uint8_t *mac, int_t width);

#if defined(SUPPORT_INET4)
extern int_t put_ipv4addr (ID portid, T_IN4_ADDR *addr, int_t width);
#endif

#if defined(SUPPORT_INET6)
extern int_t put_ipv6addr (ID portid, const T_IN6_ADDR *addr, int_t width);
#endif

#endif	/* of #ifndef _NETAPP_H_ */
