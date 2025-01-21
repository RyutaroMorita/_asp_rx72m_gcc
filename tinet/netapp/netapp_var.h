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
 *  @(#) $Id: netapp_var.h,v 1.5 2009/12/24 05:44:56 abe Exp $
 */

#ifndef _NETAPP_VAR_H_
#define _NETAPP_VAR_H_

/*
 *  �}�N����`
 */

#if defined(SUPPORT_INET4)
#define T_IPEP		T_IPV4EP
#endif

#if defined(SUPPORT_INET6)
#define T_IPEP		T_IPV6EP
#endif

/*
 *  �l�b�g���[�N�o�R�R���\�[�����o��
 */

#ifdef USE_NET_CONS

/* ���l�[�� */

#define syslog		net_syslog
#define serial_ctl_por	net_serial_ctl_por

/* �֐��V�~�����[�V�����}�N�� */

#define FLUSH_SND_BUFF()	flush_snd_buff()
#define WAI_NET_CONS_PRINTF()	syscall(wai_sem(SEM_NET_CONS_PRINTF))
#define SIG_NET_CONS_PRINTF()	sig_sem(SEM_NET_CONS_PRINTF)

#else	/* of #ifdef USE_NET_CONS */

/* �֐��V�~�����[�V�����}�N�� */

#define FLUSH_SND_BUFF()
#define WAI_NET_CONS_PRINTF()
#define SIG_NET_CONS_PRINTF()

#endif	/* of #ifdef USE_NET_CONS */

/*
 *  �֐�
 */

extern const char *in_strtfn (FN fncd);
extern const char *itron_strerror (ER ercd);
extern ER	net_syslog(uint_t prio, const char *format, ...) throw();
extern ER	net_serial_ctl_por(ID portid, uint_t ioctl) throw();
extern void	flush_snd_buff (void);
extern ER	discon_net_cons (void);
extern void	wup_net_cons (void);
extern ER	alloc_tcp_rep (ID *repid, ID tskid, T_TCP_CREP *crep);
extern ER	free_tcp_rep (ID repid, bool_t call_tcp_del_rep);
extern ER	alloc_tcp_cep (ID *cepid, ID tskid, T_TCP_CCEP *ccep);
extern ER	free_tcp_cep (ID cepid);
extern ER	alloc_udp_cep (ID *cepid, ID tskid, T_UDP_CCEP *ccep);
extern ER	free_udp_cep (ID cepid, bool_t call_udp_del_cep);

#if defined(SUPPORT_INET4)

#define TCP_CRE_REP(i,r)	tcp_cre_rep(i,r)
#define TCP_CRE_CEP(i,c)	tcp_cre_cep(i,c)
#define UDP_CRE_CEP(i,c)	udp_cre_cep(i,c)
#define TCP_ACP_CEP(c,r,d,t)	tcp_acp_cep(c,r,d,t)
#define TCP_CON_CEP(c,m,d,t)	tcp_con_cep(c,m,d,t)

#define UDP_SND_DAT(c,d,b,l,t)	udp_snd_dat(c,d,b,l,t)
#define UDP_RCV_DAT(c,d,b,l,t)	udp_rcv_dat(c,d,b,l,t)

#define IP2STR(s,a)		ip2str(s,a)

#define GET_IPADDR(a,l)		get_ipv4addr(a,l)
#define PING(a,t,l)		ping4(a,t,l)

extern void ping4 (T_IN4_ADDR *addr, uint_t tmo, uint_t len);
extern char *get_ipv4addr (T_IN4_ADDR *addr, char *line);

#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)

#define TCP_CRE_REP(i,r)	tcp6_cre_rep(i,r)
#define TCP_CRE_CEP(i,c)	tcp6_cre_cep(i,c)
#define UDP_CRE_CEP(i,c)	udp6_cre_cep(i,c)
#define TCP_ACP_CEP(c,r,d,t)	tcp6_acp_cep(c,r,d,t)
#define TCP_CON_CEP(c,m,d,t)	tcp6_con_cep(c,m,d,t)

#define UDP_SND_DAT(c,d,b,l,t)	udp6_snd_dat(c,d,b,l,t)
#define UDP_RCV_DAT(c,d,b,l,t)	udp6_rcv_dat(c,d,b,l,t)

#define IP2STR(s,a)		ipv62str(s,a)

#define GET_IPADDR(a,l)		get_ipv6addr(a,l)
#define PING(a,t,l)		ping6(a,t,l)

extern void ping6 (T_IN6_ADDR *addr, uint_t tmo, uint_t len);
extern char *get_ipv6addr (T_IN6_ADDR *addr, char *line);

#endif	/* of #if defined(SUPPORT_INET6) */

#endif	/* of #ifndef _NETAPP_VAR_H_ */
