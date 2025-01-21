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
 *  @(#) $Id: in_itron.h,v 1.5 2009/12/24 05:47:21 abe Exp $
 */
 
#ifndef _IN_ITRON_H_
#define _IN_ITRON_H_

/*
 *  API �@�\�E���ۃR�[�h
 */

/* TCP �֌W */

#define TFN_TCP_CRE_REP		(-0x201)
#define TFN_TCP_DEL_REP		(-0x202)
#define TFN_TCP_CRE_CEP		(-0x203)
#define TFN_TCP_DEL_CEP		(-0x204)
#define TFN_TCP_ACP_CEP		(-0x205)
#define TFN_TCP_CON_CEP		(-0x206)
#define TFN_TCP_SHT_CEP		(-0x207)
#define TFN_TCP_CLS_CEP		(-0x208)
#define TFN_TCP_SND_DAT		(-0x209)
#define TFN_TCP_RCV_DAT		(-0x20a)
#define TFN_TCP_GET_BUF		(-0x20b)
#define TFN_TCP_SND_BUF		(-0x20c)
#define TFN_TCP_RCV_BUF		(-0x20d)
#define TFN_TCP_REL_BUF		(-0x20e)
#define TFN_TCP_SND_OOB		(-0x20f)
#define TFN_TCP_RCV_OOB		(-0x210)
#define TFN_TCP_CAN_CEP		(-0x211)
#define TFN_TCP_SET_OPT		(-0x212)
#define TFN_TCP_GET_OPT		(-0x213)
#define TFN_TCP_ALL		(0)

#define TEV_TCP_RCV_OOB		(-0x201)

/* UDP �֌W */

#define TFN_UDP_CRE_CEP		(-0x221)
#define TFN_UDP_DEL_CEP		(-0x222)
#define TFN_UDP_SND_DAT		(-0x223)
#define TFN_UDP_RCV_DAT		(-0x224)
#define TFN_UDP_CAN_CEP		(-0x225)
#define TFN_UDP_SET_OPT		(-0x226)
#define TFN_UDP_GET_OPT		(-0x227)
#define TFN_UDP_ALL		(0)

#define TEV_UDP_RCV_DAT		(-0x221)

/* ��� */

#define NADR			((void*)(-1))	/* �����A�h���X */
#define IS_PTR_DEFINED(a)	((void*)(a)!=NADR&&(void*)(a)!=NULL)
#define TCP_REP_NONE		UINT_C(0)
#define TCP_CEP_NONE		UINT_C(0)
#define UDP_CEP_NONE		UINT_C(0)

/*
 *  �֐�
 */

/* TCP �֌W */

/* �y�W���@�\�z */

extern ER	tcp_acp_cep (ID cepid, ID repid, T_IPV4EP *p_dstaddr, TMO tmout);
extern ER	tcp_con_cep (ID cepid, T_IPV4EP *p_myaddr, T_IPV4EP *p_dstaddr, TMO tmout);
extern ER	tcp_sht_cep (ID cepid);
extern ER	tcp_cls_cep (ID cepid, TMO tmout);
extern ER_UINT	tcp_snd_dat (ID cepid, void *data, int_t len, TMO tmout);
extern ER_UINT	tcp_rcv_dat (ID cepid, void *data, int_t len, TMO tmout);
extern ER_UINT	tcp_get_buf (ID cepid, void **p_buf, TMO tmout);
extern ER	tcp_snd_buf (ID cepid, int_t len);
extern ER_UINT	tcp_rcv_buf (ID cepid, void **p_buf, TMO tmout);
extern ER	tcp_rel_buf (ID cepid, int_t len);
extern ER	tcp_can_cep (ID cepid, FN fncd);

extern ER	tcp6_acp_cep (ID cepid, ID repid, T_IPV6EP *p_dstaddr, TMO tmout);
extern ER	tcp6_con_cep (ID cepid, T_IPV6EP *p_myaddr, T_IPV6EP *p_dstaddr, TMO tmout);

/* �y�g���@�\�z */

extern ER	tcp_del_rep (ID cepid);
extern ER	tcp_cre_cep (ID cepid, T_TCP_CCEP *pk_crep);
extern ER	tcp_del_cep (ID cepid);
extern ER_UINT	tcp_snd_oob (ID cepid, void *data, int_t len, TMO tmout);
extern ER_UINT	tcp_rcv_oob (ID cepid, void *data, int_t len);
extern ER	tcp_set_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	tcp_get_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	tcp_cre_rep (ID repid, T_TCP_CREP *pk_crep);

extern ER	tcp6_cre_rep (ID repid, T_TCP6_CREP *pk_crep);

/* UDP �֌W */

/* �y�W���@�\�z */

extern ER_UINT	udp_snd_dat (ID cepid, T_IPV4EP *p_dstaddr, void *data, int_t len, TMO tmout);
extern ER_UINT	udp_rcv_dat (ID cepid, T_IPV4EP *p_dstaddr, void *data, int_t len, TMO tmout);
extern ER	udp_can_cep (ID cepid, FN fncd);

extern ER_UINT	udp6_snd_dat (ID cepid, T_IPV6EP *p_dstaddr, void *data, int_t len, TMO tmout);
extern ER_UINT	udp6_rcv_dat (ID cepid, T_IPV6EP *p_dstaddr, void *data, int_t len, TMO tmout);

/* �y�g���@�\�z */

extern ER	udp_del_cep (ID cepid);
extern ER	udp_set_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	udp_get_opt (ID cepid, int_t optname, void *optval, int_t optlen);
extern ER	udp_cre_cep (ID cepid, T_UDP_CCEP *pk_ccep);

extern ER	udp6_cre_cep (ID cepid, T_UDP6_CCEP *pk_ccep);

#endif	/* of #ifndef _IN_ITRON_H_ */
