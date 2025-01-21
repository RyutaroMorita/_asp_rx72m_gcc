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
 *  @(#) $Id: udp_var.h,v 1.5 2009/12/24 05:47:21 abe Exp $
 */

/*
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)udp_var.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/udp_var.h,v 1.16.2.2 1999/08/29 16:29:59 peter Exp $
 */
 
#ifndef _UDP_VAR_H_
#define _UDP_VAR_H_

/*
 *  UDP �w�b�_�E�y�C���[�h�A�N�Z�X�}�N��
 */

#define IP_UDP_HDR_SIZE			(IP_HDR_SIZE + UDP_HDR_SIZE)
#define IF_IP_UDP_HDR_SIZE		(IF_IP_HDR_SIZE + UDP_HDR_SIZE)
#define IF_IP_UDP_HDR_OFFSET		(IF_IP_HDR_SIZE)

#define GET_UDP_HDR(nbuf,uhoff)		((T_UDP_HDR*)((uint8_t*)((nbuf)->buf) + uhoff))
#define GET_UDP_SDU(nbuf,uhoff)		((uint8_t*)((nbuf)->buf) + uhoff+ UDP_HDR_SIZE)

#define GET_UDP_HDR_OFFSET(nbuf)	(GET_IF_IP_HDR_SIZE(nbuf))

#define GET_IP_UDP_HDR_SIZE(nbuf)	(GET_IP_HDR_SIZE(GET_IP_HDR(nbuf)) + UDP_HDR_SIZE)
#define GET_IF_IP_UDP_HDR_SIZE(nbuf)	(IF_HDR_SIZE + GET_IP_UDP_HDR_SIZE(nbuf))

/*
 *  TINET 1.1 �Ƃ̌݊����̂��߂̒�`
 */

#if defined(SUPPORT_INET4)

#define IP4_UDP_HDR_SIZE		IP_UDP_HDR_SIZE
#define IF_IP4_UDP_HDR_SIZE		IF_IP_UDP_HDR_SIZE
#define GET_IP4_UDP_HDR_SIZE(nbuf)	GET_IP_UDP_HDR_SIZE(nbuf)	
#define GET_IF_IP4_UDP_HDR_SIZE(nbuf)	GET_IF_IP_UDP_HDR_SIZE(nbuf)

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  �R�[���o�b�N�֐��̒�`
 */

typedef ER	(*t_udp_callback)(ID cepid, FN fncd, void *p_parblk);

/*
 *  UDP �ʐM�[�_
 */


/*
 *  IPv4 UDP �ʐM�[�_
 */
typedef struct t_udp4_cep {

	/*
	 * ITRON TCP/IP API�ATCP �ʐM�[�_�Ɠ��������o
	 */
	ATR		cepatr;		/* UDP �ʐM�[�_����		*/
	T_IPV4EP	myaddr;		/* �����̃A�h���X		*/
	t_udp_callback	callback;	/* �R�[���o�b�N�֐�		*/

	/*
	 * TINET �Ǝ��̃����o
	 */
	uint16_t	flags;		/* �ʐM�[�_�t���O		*/
	ID		semid_lock;	/* �ʐM�[�_���b�N		*/
	ID		snd_tskid;	/* ���M�^�X�N���ʎq		*/
	ID		rcv_tskid;	/* ��M�^�X�N���ʎq		*/
	ID		rcvqid;		/* ��R�[���o�b�N�p��M�L���[���ʎq*/
	T_NET_BUF	*cb_netbuf;	/* �R�[���o�b�N�p��M�l�b�g���[�N�o�b�t�@*/

#ifdef UDP_CFG_NON_BLOCKING

	T_IPV4EP 	*snd_p_dstaddr;	/* ���M����̃A�h���X�ւ̃|�C���^*/
	T_IPV4EP 	*rcv_p_dstaddr;	/* ��M����̃A�h���X�ւ̃|�C���^*/
	void		*snd_data;	/* ���M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		snd_len;	/* ���M�f�[�^�̈�̒���		*/
	void		*rcv_data;	/* ��M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		rcv_len;	/* ��M�f�[�^�̈�̒���		*/

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#ifdef UDP_CFG_EXTENTIONS
	ER		error;		/* �҂����ɔ��������G���[	*/
#endif

	} T_UDP4_CEP;

#if defined(SUPPORT_INET4)
#define T_UDP_CEP	T_UDP4_CEP
#endif

/*
 *  IPv6 UDP �ʐM�[�_
 */

typedef struct t_udp6_cep {

	/*
	 * ITRON TCP/IP API�ATCP �ʐM�[�_�Ɠ��������o
	 */
	ATR		cepatr;		/* UDP �ʐM�[�_����		*/
	T_IPV6EP	myaddr;		/* �����̃A�h���X		*/
	t_udp_callback	callback;	/* �R�[���o�b�N�֐�		*/

	/*
	 * TINET �Ǝ��̃����o
	 */
	uint16_t	flags;		/* �ʐM�[�_�t���O		*/
	ID		semid_lock;	/* �ʐM�[�_���b�N		*/
	ID		snd_tskid;	/* ���M�^�X�N���ʎq		*/
	ID		rcv_tskid;	/* ��M�^�X�N���ʎq		*/
	ID		rcvqid;		/* ��R�[���o�b�N�p��M�L���[���ʎq*/
	T_NET_BUF	*cb_netbuf;	/* �R�[���o�b�N�p��M�l�b�g���[�N�o�b�t�@*/

#ifdef UDP_CFG_NON_BLOCKING

	T_IPV6EP 	*snd_p_dstaddr;	/* ���M����̃A�h���X�ւ̃|�C���^*/
	T_IPV6EP 	*rcv_p_dstaddr;	/* ��M����̃A�h���X�ւ̃|�C���^*/
	void		*snd_data;	/* ���M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		snd_len;	/* ���M�f�[�^�̈�̒���		*/
	void		*rcv_data;	/* ��M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		rcv_len;	/* ��M�f�[�^�̈�̒���		*/

#endif	/* of #ifdef UDP_CFG_NON_BLOCKING */

#ifdef UDP_CFG_EXTENTIONS
	ER		error;		/* �҂����ɔ��������G���[	*/
#endif

	} T_UDP6_CEP;

#if defined(SUPPORT_INET6)
#define T_UDP_CEP	T_UDP6_CEP
#endif

/*
 *  UDP �ʐM�[�_�t���O
 */

#define UDP_CEP_FLG_POST_OUTPUT	UINT_C(0x0200)	/* ���M���J�n����B		*/
#define UDP_CEP_FLG_DYNAMIC	UINT_C(0x0400)	/* ���I�����E�폜�\�ʐM�[�_�B	*/
#define UDP_CEP_FLG_VALID	UINT_C(0x0800)	/* �����ς݂ŗL���ȒʐM�[�_�B	*/

/*
 *  �I�u�W�F�N�g ID �̍ŏ��l�̒�`
 */

#define	TMIN_UDP_CEPID		1	/* UDP �ʐM�[�_ ID �̍ŏ��l */

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

typedef struct t_udp_stats {
	uint32_t	udpInDatagrams;
	uint32_t	udpNoPorts;
	uint32_t	udpInErrors;
	uint32_t	udpOutDatagrams;
} T_UDP_STATS;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �֐��V�~�����[�V�����}�N��
 */

#define VALID_UDP_CEPID(id)	(TMIN_UDP_CEPID<=(id)&&(id)<=tmax_udp_cepid)

#define INDEX_UDP_CEP(id)	((id)-TMIN_UDP_CEPID)

#define GET_UDP_CEP(id)		(&(udp_cep[INDEX_UDP_CEP(id)]))

#define GET_UDP_CEPID(cep)	((ID)(((cep)-udp_cep)+TMIN_UDP_CEPID))

#define VALID_TFN_UDP_CAN(t)	((t)==TFN_UDP_SND_DAT||(t)==TFN_UDP_RCV_DAT||\
				 (t)==TFN_UDP_ALL)

#define VALID_UDP_CEP(cep)	(((cep)->flags&UDP_CEP_FLG_VALID)!=0)
#define DYNAMIC_UDP_CEP(cep)	(((cep)->flags&UDP_CEP_FLG_DYNAMIC)!=0)

/*
 *  �S��ϐ�
 */

extern T_UDP_CEP udp_cep[];
extern const ID tmax_udp_cepid;

#ifdef SUPPORT_MIB

extern T_UDP_STATS udp_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  TINET 1.3 �Ƃ̌݊����̂��߂̒�`
 */

#define	TMIN_UDP_CCEPID		TMIN_UDP_CEPID
#define	TNUM_UDP_CCEPID		TNUM_UDP_CEPID

/*
 *  �֐�
 */

extern uint_t udp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern ER_UINT udp_send_data (T_UDP_CEP *cep, T_IPEP *p_dstaddr,
                              void *data, int_t len, TMO tmout);
extern ER udp_can_snd (T_UDP_CEP *cep, ER error);
extern ER udp_can_rcv (T_UDP_CEP *cep, ER error);
extern ER udp_alloc_auto_port (T_UDP_CEP *cep);
extern ER udp_alloc_port (T_UDP_CEP *cep, uint16_t portno);

/* �m���u���b�L���O�R�[�����s���ꍇ�ɑg�ݍ��ރ^�X�N */

extern void	udp_output_task(intptr_t exinf);

#endif	/* of #ifndef _UDP_VAR_H_ */
