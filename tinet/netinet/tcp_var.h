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
 *  @(#) $Id: tcp_var.h,v 1.5 2009/12/24 05:47:21 abe Exp $
 */

/*
 * Copyright (c) 1982, 1986, 1993, 1994, 1995
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
 *	@(#)tcp_var.h	8.4 (Berkeley) 5/24/95
 * $FreeBSD: src/sys/netinet/tcp_var.h,v 1.49.2.1 1999/08/29 16:29:57 peter Exp $
 */
 
#ifndef _TCP_VAR_H_
#define _TCP_VAR_H_

/*
 *  TCP �w�b�_�E�y�C���[�h�A�N�Z�X�}�N��
 */

#define IP_TCP_HDR_SIZE			(IP_HDR_SIZE + TCP_HDR_SIZE)
#define IF_IP_TCP_HDR_SIZE		(IF_IP_HDR_SIZE + TCP_HDR_SIZE)
#define IF_IP_TCP_HDR_OFFSET		(IF_IP_HDR_SIZE)
#define IF_IP_TCP_SDU_OFFSET		(IF_IP_TCP_HDR_SIZE)

#define GET_TCP_HDR(nbuf,thoff)		((T_TCP_HDR*)((uint8_t*)((nbuf)->buf) + thoff))
#define GET_TCP_OPT(nbuf,thoff)		((uint8_t*)((nbuf)->buf) + thoff + TCP_HDR_SIZE)
#define GET_TCP_SDU(nbuf,thoff)		((uint8_t*)((nbuf)->buf) + thoff + GET_TCP_HDR_SIZE2(nbuf,thoff))

#define GET_TCP_HDR_OFFSET(nbuf)	(GET_IF_IP_HDR_SIZE(nbuf))

#define GET_TCP_HDR_SIZE2(nbuf,thoff)	(TCP_HDR_LEN(GET_TCP_HDR(nbuf,thoff)->doff))
#define GET_IP_TCP_HDR_SIZE2(nbuf,thoff) \
					(GET_IP_HDR_SIZE(GET_IP_HDR(nbuf)) + GET_TCP_HDR_SIZE2(nbuf,thoff))
#define GET_IF_IP_TCP_HDR_SIZE2(nbuf,thoff) \
					(IF_HDR_SIZE + GET_IP_TCP_HDR_SIZE2(nbuf,thoff))

/*
 *  TINET 1.1 �Ƃ̌݊����̂��߂̒�`
 */

#if defined(SUPPORT_INET4)

#define IP4_TCP_HDR_SIZE		IP_TCP_HDR_SIZE
#define IF_IP4_TCP_HDR_SIZE		IF_IP_TCP_HDR_SIZE
#define GET_IP4_TCP_HDR_SIZE(nbuf)	GET_IP_TCP_HDR_SIZE(nbuf)	
#define GET_IF_IP4_TCP_HDR_SIZE(nbuf)	GET_IF_IP_TCP_HDR_SIZE(nbuf)	

#endif	/* of #if defined(SUPPORT_INET4) */

/*
 *  TINET 1.3 �Ƃ̌݊����̂��߂̒�`
 */

#define	TMIN_TCP_CREPID			TMIN_TCP_REPID
#define	TMIN_TCP_CCEPID			TMIN_TCP_CEPID
#define	TNUM_TCP_CREPID			TNUM_TCP_REPID
#define	TNUM_TCP_CCEPID			TNUM_TCP_CEPID

/*
 *  �R�[���o�b�N�֐��̒�`
 */

typedef ER	(*t_tcp_callback)(ID cepid, FN fncd, void *p_parblk);

/*
 *  TCP ��t��
 */

/* IPv4 �p TCP ��t�� */
typedef struct t_tcp4_rep {

	/*
	 * ITRON TCP/IP API�ATCP ��t���Ɠ��������o
	 */
	ATR		repatr;		/* ��t������		*/
	T_IPV4EP	myaddr;		/* �����̃A�h���X	*/

#ifdef TCP_CFG_EXTENTIONS
	uint16_t	flags;		/* ��t���t���O		*/
	ID		semid_lock;	/* ��t�����b�N		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	} T_TCP4_REP;

/* IPv6 �p TCP ��t�� */
typedef struct t_tcp6_rep {

	/*
	 * ITRON TCP/IP API�ATCP ��t���Ɠ��������o
	 */
	ATR		repatr;		/* ��t������		*/
	T_IPV6EP	myaddr;		/* �����̃A�h���X	*/

#ifdef TCP_CFG_EXTENTIONS
	uint16_t	flags;		/* ��t���t���O		*/
	ID		semid_lock;	/* ��t�����b�N		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	} T_TCP6_REP;

#if defined(SUPPORT_INET4)
#define T_TCP_REP	T_TCP4_REP
#endif

#if defined(SUPPORT_INET6)
#define T_TCP_REP	T_TCP6_REP
#endif

/*
 *  ��t���t���O
 */

#define TCP_REP_FLG_DYNAMIC	UINT_C(0x0400)	/* ���I�����E�폜�\��t���B	*/
#define TCP_REP_FLG_VALID	UINT_C(0x0800)	/* �����ς݂ŗL���Ȏ�t���B	*/

/*
 *  TCP �ʐM�[�_
 */

typedef uint32_t T_TCP_SEQ;
typedef uint16_t T_TCP_SEG;
typedef uint16_t T_TCP_WND;

/*
 * �ʏ�� IPv4 TCP �ʐM�[�_
 */
typedef struct t_tcp4_cep {

	/*
	 * ITRON TCP/IP API�ATCP �ʐM�[�_�Ɠ��������o
	 */
	ATR		cepatr;		/* �ʐM�[�_����			*/
	void		*sbuf;		/* ���M�p�E�B���h�o�b�t�@	*/
	int_t		sbufsz;		/* ���M�p�E�B���h�o�b�t�@�T�C�Y	*/
	void		*rbuf;		/* ��M�p�E�B���h�o�b�t�@	*/
	int_t		rbufsz;		/* ��M�p�E�B���h�o�b�t�@�T�C�Y	*/
	t_tcp_callback	callback;	/* �R�[���o�b�N�֐�		*/

	/*
	 * TINET �Ǝ��̃����o
	 */
	uint32_t	flags;		/* �ʐM�[�_�t���O		*/
	ID		semid_lock;	/* �ʐM�[�_���b�N		*/
	ID		est_flgid;	/* �R�l�N�V������ԃC�x���g�t���O	*/
	ID		snd_flgid;	/* ���M�C�x���g�t���O		*/
	ID		rcv_flgid;	/* ��M�C�x���g�t���O		*/
	ID		snd_tskid;	/* ���M�^�X�N���ʎq		*/
	ID		rcv_tskid;	/* ��M�^�X�N���ʎq		*/
	uint8_t		*sbuf_rptr;	/* ���M�p�ǂݏo���|�C���^	*/
	uint8_t		*sbuf_wptr;	/* ���M�p�������݃|�C���^	*/
	uint8_t		*rbuf_rptr;	/* ��M�p�ǂݏo���|�C���^	*/
	uint8_t		*rbuf_wptr;	/* ��M�p�������݃|�C���^	*/
	T_TCP_SEQ	snd_ssthresh;	/* �t�s�E�B���h�T�C�Y(snd_cwnd)	*/
					/* �̂������l			*/
	T_TCP_TIME	rxtcur;		/* ���݂̍đ��^�C���A�E�g	*/
	T_TCP_TIME	srtt;		/* ���������ꂽ RTT		*/
	T_TCP_TIME	rttvar;		/* ���������ꂽ���U		*/
	T_TCP_WND	snd_cwnd;	/* �t�s�E�B���h�T�C�Y		*/

	/*
	 *  ����̍ő��M�Z�O�����g�T�C�Y	
	 *
	 *    �I���W�i���ł́A��ʂ̃Z�O�����g�̍ő�T�C�Y (t_maxseg) �ƁA
	 *    �I�v�V�����t���̃Z�O�����g�̍ő�T�C�Y (t_maxopd) ���ʂ�
	 *    �Ȃ��Ă���B����́A���݂̃C���^�[�l�b�g�ł́A�I�v�V�����t����
	 *    �Z�O�����g�̂ق�����������Ɛ�������Ă��邽�߂ł���B
	 *    �{�����ł́A�ő�Z�O�����g�T�C�Y�I�v�V�����ȊO�̃I�v�V������
	 *    �������Ȃ��̂ŁAt_maxseg �̎g�p����B
	 */
	T_TCP_SEG	maxseg;

	int16_t		snd_tfn;	/* ���M���쒆�� API �@�\�R�[�h	*/
	int16_t		rcv_tfn;	/* ��M���쒆�� API �@�\�R�[�h	*/

#ifdef TCP_CFG_NON_BLOCKING

	T_IPV4EP 	*p_dstaddr;	/* ����̃A�h���X�ւ̃|�C���^	*/
	T_IPV4EP 	*p_myaddr;	/* �����̃A�h���X�ւ̃|�C���^	*/
	int16_t		snd_nblk_tfn;	/* ���M���쒆�� API �@�\�R�[�h	*/
	int16_t		rcv_nblk_tfn;	/* ��M���쒆�� API �@�\�R�[�h	*/
	void		*snd_data;	/* ���M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		snd_len;	/* ���M�f�[�^�̈�̒���		*/
	void		*rcv_data;	/* ��M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		rcv_len;	/* ��M�f�[�^�̈�̒���		*/
	void		**snd_p_buf;	/* ���M�o�b�t�@�ւ̃|�C���^	*/
	void		**rcv_p_buf;	/* ��M�o�b�t�@�ւ̃|�C���^	*/

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

#ifdef TCP_CFG_SWBUF_CSAVE
	T_NET_BUF	*swbufq;	/* ���M�E�B���h�o�b�t�@�L���[	*/
#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

	/*
	 *  ����ȍ~�̃����o�[�� tcp_init_cep() �֐��Ń[���N���A�[�����B
	 */

	T_TCP_TIME	timer[NUM_TCP_TIMERS];	/* TCP �̃^�C�}		*/
	T_IPV4EP	dstaddr;	/* ����̃A�h���X		*/
	T_IPV4EP	myaddr;		/* �����̃A�h���X		*/
	T_TCP4_REP	*rep;		/* ��t��			*/
	T_NET_BUF	*reassq;	/* ��M�č\���L���[		*/

#ifdef TCP_CFG_RWBUF_CSAVE
	T_NET_BUF	*rwbufq;	/* ��M�E�B���h�o�b�t�@�L���[	*/
#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#ifdef TCP_CFG_EXTENTIONS
	T_TCP_HDR	*urg_tcph;	/* �ً}�f�[�^����̃Z�O�����g�� TCP �w�b�_	*/
	T_TCP_SEQ	snd_up;		/* ���M�����ً}�|�C���^		*/
	T_TCP_SEQ	rcv_up;		/* ��M�����ً}�|�C���^		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	T_TCP_SEQ	snd_una;	/* ���m�F�̍ŏ����M SEQ �܂�	*/
					/* �m�F���ꂽ�ő呗�M SEQ	*/
	T_TCP_SEQ	snd_max;	/* ���M�����ő� SEQ		*/
	T_TCP_SEQ	snd_nxt;	/* ���ɑ��M���� SEQ		*/
	T_TCP_SEQ	snd_old_nxt;	/* ���� snd_nxt			*/
	T_TCP_SEQ	snd_wl1;	/* �O��E�B���h���X�V���� SEQ	*/
	T_TCP_SEQ	snd_wl2;	/* �O��E�B���h���X�V���� ACK	*/
	T_TCP_SEQ	iss;		/* ������ SEQ �̏����l		*/
	T_TCP_SEQ	irs;		/* ����� SEQ �̏����l		*/
	T_TCP_SEQ	rcv_nxt;	/* ��M�����҂��Ă���ŏ��� SEQ	*/
	T_TCP_SEQ	rcv_adv;	/* ��M�����҂��Ă���ő�� SEQ	*/
	T_TCP_SEQ	rcv_wnd;	/* ��M�\�ȃE�B���h�T�C�Y	*/
	T_TCP_SEQ	rtseq;		/* ���Ԍv�����n�߂� SEQ		*/
	T_TCP_SEQ	last_ack_sent;	/* �Ō�ɑ��M���� ACK		*/
	T_TCP_TIME	idle;		/* �A�C�h������			*/
	ER		error;		/* �񓯊��ɔ��������G���[	*/
	ER		net_error;	/* �l�b�g���[�N�̃G���[���	*/
	T_TCP_WND	snd_wnd;	/* ����̎�M�\�E�B���h�T�C�Y	*/
	T_TCP_WND	max_sndwnd;	/* ���܂ł̍ő呗�M�E�B���h�T�C�Y	*/
	T_TCP_TIME	rtt;		/* ��������				*/
	uint16_t	swbuf_count;	/* ���M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint16_t	rwbuf_count;	/* ��M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint16_t	rcv_buf_len;	/* tcp_rcv_buf �̊����Ē�	*/
	uint16_t	get_buf_len;	/* tcp_rcv_buf �̊����Ē�	*/
	uint8_t		rxtshift;	/* �đ��M�񐔂� log(2)		*/
	uint8_t		fsm_state;	/* FSM ���			*/
	uint8_t		dupacks;	/* �đ� ACK ��			*/

#if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)
	uint8_t		rwbufq_entries;	/* ��M�E�B���h�o�b�t�@�L���[�̃G���g����	*/
#endif	/* of #if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)	*/

	} T_TCP4_CEP;

/*
 * Time Wait �p IPv4 TCP �ʐM�[�_
 */
typedef struct t_tcp4_twcep {
	int_t		rbufsz;		/* ��M�p�E�B���h�o�b�t�@�T�C�Y	*/
	T_TCP_TIME	timer_2msl;	/* 2MSL �^�C�}			*/
	T_IPV4EP	dstaddr;	/* ����̃A�h���X		*/
	T_IPV4EP	myaddr;		/* �����̃A�h���X		*/
	T_TCP_SEQ	snd_una;	/* ���m�F�̍ŏ����M SEQ �܂�	*/
					/* �m�F���ꂽ�ő呗�M SEQ	*/
	T_TCP_SEQ	rcv_nxt;	/* ��M�����҂��Ă���ŏ��� SEQ	*/
	uint16_t	rwbuf_count;	/* ��M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint8_t		fsm_state;	/* FSM ���			*/

	} T_TCP4_TWCEP;

/*
 * �ʏ�� IPv6 TCP �ʐM�[�_
 */
typedef struct t_tcp6_cep {

	/*
	 * ITRON TCP/IP API�ATCP �ʐM�[�_�Ɠ��������o
	 */
	ATR		cepatr;		/* �ʐM�[�_����			*/
	void		*sbuf;		/* ���M�p�E�B���h�o�b�t�@	*/
	int_t		sbufsz;		/* ���M�p�E�B���h�o�b�t�@�T�C�Y	*/
	void		*rbuf;		/* ��M�p�E�B���h�o�b�t�@	*/
	int_t		rbufsz;		/* ��M�p�E�B���h�o�b�t�@�T�C�Y	*/
	t_tcp_callback	callback;	/* �R�[���o�b�N�֐�		*/

	/*
	 * TINET �Ǝ��̃����o
	 */
	uint32_t	flags;		/* �ʐM�[�_�t���O		*/
	ID		semid_lock;	/* �ʐM�[�_���b�N		*/
	ID		est_flgid;	/* �R�l�N�V������ԃC�x���g�t���O	*/
	ID		snd_flgid;	/* ���M�C�x���g�t���O		*/
	ID		rcv_flgid;	/* ��M�C�x���g�t���O		*/
	ID		snd_tskid;	/* ���M�^�X�N���ʎq		*/
	ID		rcv_tskid;	/* ��M�^�X�N���ʎq		*/
	uint8_t		*sbuf_rptr;	/* ���M�p�ǂݏo���|�C���^		*/
	uint8_t		*sbuf_wptr;	/* ���M�p�������݃|�C���^		*/
	uint8_t		*rbuf_rptr;	/* ��M�p�ǂݏo���|�C���^		*/
	uint8_t		*rbuf_wptr;	/* ��M�p�������݃|�C���^		*/
	T_TCP_SEQ	snd_ssthresh;	/* �t�s�E�B���h�T�C�Y(snd_cwnd)	*/
					/* �̂������l			*/
	T_TCP_TIME	rxtcur;		/* ���݂̍đ��^�C���A�E�g		*/
	T_TCP_TIME	srtt;		/* ���������ꂽ RTT		*/
	T_TCP_TIME	rttvar;		/* ���������ꂽ���U		*/
	T_TCP_WND	snd_cwnd;	/* �t�s�E�B���h�T�C�Y		*/

	/*
	 *  ����̍ő��M�Z�O�����g�T�C�Y	
	 *
	 *    �I���W�i���ł́A��ʂ̃Z�O�����g�̍ő�T�C�Y (t_maxseg) �ƁA
	 *    �I�v�V�����t���̃Z�O�����g�̍ő�T�C�Y (t_maxopd) ���ʂ�
	 *    �Ȃ��Ă���B����́A���݂̃C���^�[�l�b�g�ł́A�I�v�V�����t����
	 *    �Z�O�����g�̂ق�����������Ɛ�������Ă��邽�߂ł���B
	 *    �{�����ł́A�ő�Z�O�����g�T�C�Y�I�v�V�����ȊO�̃I�v�V������
	 *    �������Ȃ��̂ŁAt_maxseg �̎g�p����B
	 */
	T_TCP_SEG	maxseg;

	T_IPV6EP 	*p_dstaddr;	/* ����̃A�h���X�ւ̃|�C���^	*/
	T_IPV6EP 	*p_myaddr;	/* �����̃A�h���X�ւ̃|�C���^	*/
	int16_t		snd_tfn;	/* ���M���쒆�� API �@�\�R�[�h	*/
	int16_t		rcv_tfn;	/* ��M���쒆�� API �@�\�R�[�h	*/

#ifdef TCP_CFG_NON_BLOCKING

	int16_t		snd_nblk_tfn;	/* ���M���쒆�� API �@�\�R�[�h	*/
	int16_t		rcv_nblk_tfn;	/* ��M���쒆�� API �@�\�R�[�h	*/
	void		*snd_data;	/* ���M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		snd_len;	/* ���M�f�[�^�̈�̒���		*/
	void		*rcv_data;	/* ��M�f�[�^�̈�̐擪�A�h���X	*/
	int_t		rcv_len;	/* ��M�f�[�^�̈�̒���		*/
	void		**snd_p_buf;	/* ���M�o�b�t�@�ւ̃|�C���^	*/
	void		**rcv_p_buf;	/* ��M�o�b�t�@�ւ̃|�C���^	*/

#endif	/* of #ifdef TCP_CFG_NON_BLOCKING */

#ifdef TCP_CFG_SWBUF_CSAVE
	T_NET_BUF	*swbufq;	/* ���M�E�B���h�o�b�t�@�L���[	*/
#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

	/*
	 *  ����ȍ~�̃����o�[�� tcp_init_cep() �֐��Ń[���N���A�[�����B
	 */

	T_TCP_TIME	timer[NUM_TCP_TIMERS];	/* TCP �̃^�C�}		*/
	T_IPV6EP	dstaddr;	/* ����̃A�h���X		*/
	T_IPV6EP	myaddr;		/* �����̃A�h���X		*/
	T_TCP6_REP	*rep;		/* ��t��			*/
	T_NET_BUF	*reassq;	/* ��M�č\���L���[		*/

#ifdef TCP_CFG_RWBUF_CSAVE
	T_NET_BUF	*rwbufq;	/* ��M�E�B���h�o�b�t�@�L���[	*/
#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#ifdef TCP_CFG_EXTENTIONS
	T_TCP_HDR	*urg_tcph;	/* �ً}�f�[�^����̃Z�O�����g�� TCP �w�b�_	*/
	T_TCP_SEQ	snd_up;		/* ���M�����ً}�|�C���^		*/
	T_TCP_SEQ	rcv_up;		/* ��M�����ً}�|�C���^		*/
#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

	T_TCP_SEQ	snd_una;	/* ���m�F�̍ŏ����M SEQ �܂�	*/
					/* �m�F���ꂽ�ő呗�M SEQ	*/
	T_TCP_SEQ	snd_max;	/* ���M�����ő� SEQ		*/
	T_TCP_SEQ	snd_nxt;	/* ���ɑ��M���� SEQ		*/
	T_TCP_SEQ	snd_old_nxt;	/* ���� snd_nxt			*/
	T_TCP_SEQ	snd_wl1;	/* �O��E�B���h���X�V���� SEQ	*/
	T_TCP_SEQ	snd_wl2;	/* �O��E�B���h���X�V���� ACK	*/
	T_TCP_SEQ	iss;		/* ������ SEQ �̏����l		*/
	T_TCP_SEQ	irs;		/* ����� SEQ �̏����l		*/
	T_TCP_SEQ	rcv_nxt;	/* ��M�����҂��Ă���ŏ��� SEQ	*/
	T_TCP_SEQ	rcv_adv;	/* ��M�����҂��Ă���ő�� SEQ	*/
	T_TCP_SEQ	rcv_wnd;	/* ��M�\�ȃE�B���h�T�C�Y	*/
	T_TCP_SEQ	rtseq;		/* ���Ԍv�����n�߂� SEQ		*/
	T_TCP_SEQ	last_ack_sent;	/* �Ō�ɑ��M���� ACK		*/
	T_TCP_TIME	idle;		/* �A�C�h������			*/
	ER		error;		/* �񓯊��ɔ��������G���[		*/
	ER		net_error;	/* �l�b�g���[�N�̃G���[���	*/
	T_TCP_WND	snd_wnd;	/* ����̎�M�\�E�B���h�T�C�Y	*/
	T_TCP_WND	max_sndwnd;	/* ���܂ł̍ő呗�M�E�B���h�T�C�Y	*/
	T_TCP_TIME	rtt;		/* ��������			*/
	uint16_t	swbuf_count;	/* ���M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint16_t	rwbuf_count;	/* ��M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint16_t	rcv_buf_len;	/* tcp_rcv_buf �̊����Ē�	*/
	uint16_t	get_buf_len;	/* tcp_rcv_buf �̊����Ē�	*/
	uint8_t		rxtshift;	/* �đ��M�񐔂� log(2)		*/
	uint8_t		fsm_state;	/* FSM ���			*/
	uint8_t		dupacks;	/* �đ� ACK ��			*/

#if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)
	uint8_t		rwbufq_entries;	/* ��M�E�B���h�o�b�t�@�L���[�̃G���g����	*/
#endif	/* of #if defined(TCP_CFG_RWBUF_CSAVE) && defined(TCP_CFG_RWBUF_CSAVE_MAX_QUEUES)	*/

	} T_TCP6_CEP;

/*
 * Time Wait �p IPv6 TCP �ʐM�[�_
 */
typedef struct t_tcp6_twcep {
	int_t		rbufsz;		/* ��M�p�E�B���h�o�b�t�@�T�C�Y	*/
	T_TCP_TIME	timer_2msl;	/* 2MSL �^�C�}			*/
	T_IPV6EP	dstaddr;	/* ����̃A�h���X		*/
	T_IPV6EP	myaddr;		/* �����̃A�h���X		*/
	T_TCP_SEQ	snd_una;	/* ���m�F�̍ŏ����M SEQ �܂�	*/
					/* �m�F���ꂽ�ő呗�M SEQ	*/
	T_TCP_SEQ	iss;		/* ������ SEQ �̏����l		*/
	T_TCP_SEQ	irs;		/* ����� SEQ �̏����l		*/
	T_TCP_SEQ	rcv_nxt;	/* ��M�����҂��Ă���ŏ��� SEQ	*/
	T_TCP_WND	snd_wnd;	/* ����̎�M�\�E�B���h�T�C�Y	*/
	uint16_t	rwbuf_count;	/* ��M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint8_t		fsm_state;	/* FSM ���			*/

	} T_TCP6_TWCEP;

#if defined(SUPPORT_INET4)
#define T_TCP_CEP	T_TCP4_CEP
#define T_TCP_TWCEP	T_TCP4_TWCEP
#endif	/* of #if defined(SUPPORT_INET4) */

#if defined(SUPPORT_INET6)
#define T_TCP_CEP	T_TCP6_CEP
#define T_TCP_TWCEP	T_TCP6_TWCEP
#endif	/* of #if defined(SUPPORT_INET6) */

#define T_TCP_CEP_DEFINED

/*
 *  TCP �ʐM�[�_�̏�ԃt���O
 */

#define TCP_CEP_FLG_ACK_NOW		ULONG_C(0x00000001)	/* �����ɑ���� ACK �𑗂�B	*/
#define TCP_CEP_FLG_DEL_ACK		ULONG_C(0x00000002)	/* ACK ��x������B		*/
#define TCP_CEP_FLG_SENT_FIN		ULONG_C(0x00000004)	/* FIN �𑗂��Ă���B		*/
#define TCP_CEP_FLG_NEED_SYN		ULONG_C(0x00000008)	/* SYN �𑗐M����B		*/
#define TCP_CEP_FLG_NEED_FIN		ULONG_C(0x00000010)	/* FIN �𑗐M����B		*/
#define TCP_CEP_FLG_FORCE		ULONG_C(0x00000020)	/* �������M�B			*/
#define TCP_CEP_FLG_NO_PUSH		ULONG_C(0x00000040)	/* push ���Ȃ��B		*/
#define TCP_CEP_FLG_NO_DELAY		ULONG_C(0x00000080)	/* �x�����Ȃ��B			*/
#define TCP_CEP_FLG_FORCE_CLEAR		ULONG_C(0x00000100)	/* �������M������t���O���N���A�[����B*/
#define TCP_CEP_FLG_POST_OUTPUT		ULONG_C(0x00000200)	/* ���M���J�n����B		*/
#define TCP_CEP_FLG_RESERVE_OUTPUT	ULONG_C(0x00000400)	/* ���M��\�񂷂�B		*/
#define TCP_CEP_FLG_DYNAMIC		ULONG_C(0x00001000)	/* ���I�����E�폜�\�ʐM�[�_�B	*/
#define TCP_CEP_FLG_VALID		ULONG_C(0x00002000)	/* �����ς݂ŗL���ȒʐM�[�_�B	*/
#define TCP_CEP_FLG_CLOSE_AFTER_OUTPUT	ULONG_C(0x00004000)	/* ���M������R�l�N�V���������B*/
#define TCP_CEP_FLG_RESTORE_NEXT_OUTPUT	ULONG_C(0x00008000)	/* ���M������Asnd_nxt �����ɖ߂��B*/

/* ����M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\ */
#define TCP_CEP_FLG_WBCS_NBUF_REQ	ULONG_C(0x00080000)	/* �l�b�g���[�N�o�b�t�@�����ėv��	*/
#define TCP_CEP_FLG_WBCS_MASK		ULONG_C(0x00070000)	/* �}�X�N			*/
#define TCP_CEP_FLG_WBCS_FREE		ULONG_C(0x00000000)	/* ���M�E�B���h�o�b�t�@���g�p	*/
#define TCP_CEP_FLG_WBCS_WOPEN_PEND	ULONG_C(0x00010000)	/* ����̎�M�E�B���h�̊J���҂�	*/
#define TCP_CEP_FLG_WBCS_NBUF_PEND	ULONG_C(0x00020000)	/* �l�b�g���[�N�o�b�t�@�\��҂�	*/
#define TCP_CEP_FLG_WBCS_NBUF_RSVD	ULONG_C(0x00030000)	/* �l�b�g���[�N�o�b�t�@�\��ς�	*/
#define TCP_CEP_FLG_WBCS_NBUF_READY	ULONG_C(0x00040000)	/* �l�b�g���[�N�o�b�t�@�����čς�	*/
#define TCP_CEP_FLG_WBCS_SEND_READY	ULONG_C(0x00050000)	/* ���M�\			*/
#define TCP_CEP_FLG_WBCS_SENT		ULONG_C(0x00060000)	/* ���M�ς݂ŁAACK�҂�		*/
#define TCP_CEP_FLG_WBCS_ACKED		ULONG_C(0x00070000)	/* ���M�ς݂ŁAACK����		*/

/*
 *  �ʐM�[�_�C�x���g�t���O
 */

#define TCP_CEP_EVT_ESTABLISHED		ULONG_C(0x00000001)	/* �R�l�N�V�����m��		*/
#define TCP_CEP_EVT_CLOSED		ULONG_C(0x00000002)	/* ���g�p���			*/
#define TCP_CEP_EVT_SWBUF_READY		ULONG_C(0x00000004)	/* ���M�E�B���h�o�b�t�@��	*/
#define TCP_CEP_EVT_RWBUF_READY		ULONG_C(0x00000008)	/* ���M�E�B���h�o�b�t�@�f�[�^����	*/
#define TCP_CEP_EVT_ALL			ULONG_C(0xffffffff)	/* �S�C�x���g			*/

/*
 *  �ǉ� API �@�\�E���ۃR�[�h
 */

/* TCP �֌W */

#define TFN_TCP_UNDEF		(0)

/*
 *  srtt:   ���������ꂽ RTT
 *  rttvar: ���������ꂽ���U
 *  rtt:    ���肳�ꂽ��������
 *
 *  ���������ꂽ RTT (srtt) �ƕ��������ꂽ���U (rttvar) ��
 *  �����^�Ōv�Z���邽�߂ɁA���V�t�g���ăX�P�[������B
 *  srtt �� 2 �i�����_�ȉ� 3 �r�b�g�A
 *  rttvar �� 2 �i�����_�ȉ� 2 �r�b�g��ێ�����B
 */

#define TCP_DELTA_SHIFT		2
			/* ���� = rtt/8 + srtt*7/8 �̌v�Z�̂��߂̃V�t�g�l	*/
#define TCP_SRTT_SHIFT		(TCP_DELTA_SHIFT + 3)
					/* srtt �̃V�t�g�l�A3(+2)�r�b�g	*/
#define TCP_RTTVAR_SHIFT	(TCP_DELTA_SHIFT + 2)
					/* rttvar �̃V�t�g�l�A2(+2)�r�b�g	*/
#define TCP_SRTT_SCALE		(1<<TCP_SRTT_SHIFT)
#define TCP_RTTVAR_SCALE	(1<<TCP_RTTVAR_SHIFT)

/*
 *  �����ē]�����J�n����đ� ACK ���̂������l
 */

#define MAX_TCP_REXMT_THRESH	3

/*
 *  ��M�č\���L���[�ł� TCP �w�b�_
 */

typedef struct t_tcp_q_hdr {
	uint16_t	sport;		/* ���M���|�[�g�ԍ�			*/
	uint16_t	dport;		/* ����|�[�g�ԍ�			*/

	uint32_t	seq;		/* SEQ �ԍ�				*/

	T_NET_BUF 	*next;		/* ���̃Z�O�����g�A���� ACK �ԍ�(ack)	*/

	uint8_t		doff;		/* �f�[�^�I�t�Z�b�g(���4�r�b�g)	*/
	uint8_t		flags;		/* �t���O(����6�r�b�g)			*/
	uint16_t	soff;		/* SDU �I�t�Z�b�g�A���̓E�B���h�T�C�Y(win)	*/

	uint16_t	slen;		/* SDU ���A���̓`�F�b�N�T��(sum)	*/
	uint16_t	urp;		/* �ً}�|�C���^�iSDU ���␳�j		*/
	} T_TCP_Q_HDR;

#define GET_TCP_Q_HDR(nbuf,thoff)	((T_TCP_Q_HDR*)((uint8_t*)((nbuf)->buf) + thoff))
#define GET_TCP_IP_Q_HDR(nbuf)		((T_TCP_IP_Q_HDR*)GET_IP_HDR(nbuf))

/*
 *  �I�u�W�F�N�g ID �̍ŏ��l�̒�`
 */

#define	TMIN_TCP_REPID		1	/* TCP ��t��   ID �̍ŏ��l			*/
#define	TMIN_TCP_CEPID		1	/* TCP �ʐM�[�_ ID �̍ŏ��l			*/
#define	TMIN_TCP_TWCEPID	1	/* Time Wait �p TCP �ʐM�[�_ ID �̍ŏ��l	*/

/*
 *  ����Z�O�����g�i�f�[�^�Ȃ��j�T�C�Y�̃l�b�g���[�N�o�b�t�@
 */

typedef struct t_net_buf_cseg {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_HDR_SIZE + IP_HDR_SIZE + TCP_HDR_SIZE];
				/* �o�b�t�@�{��		*/
	} T_NET_BUF_CSEG;

#ifdef SUPPORT_MIB

/*
 *  SNMP �� �Ǘ����x�[�X (MIB)
 */

typedef struct t_tcp_stats {
	uint32_t	tcpActiveOpens;
	uint32_t	tcpPassiveOpens;
	uint32_t	tcpAttemptFails;
	uint32_t	tcpEstabResets;
/*	uint32_t	tcpCurrEstab;*/
	uint32_t	tcpInSegs;
	uint32_t	tcpOutSegs;
	uint32_t	tcpRetransSegs;
	uint32_t	tcpInErrs;
	uint32_t	tcpOutRsts;
} T_TCP_STATS;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  �֐��V�~�����[�V�����}�N��
 */

#define VAID_TCP_REPID(id)	(TMIN_TCP_REPID<=(id)&&(id)<=tmax_tcp_repid)
#define VAID_TCP_CEPID(id)	(TMIN_TCP_CEPID<=(id)&&(id)<=tmax_tcp_cepid)

#define INDEX_TCP_REP(id)	((id)-TMIN_TCP_REPID)
#define INDEX_TCP_CEP(id)	((id)-TMIN_TCP_CEPID)

#define GET_TCP_REP(id)		(&(tcp_rep[INDEX_TCP_REP(id)]))
#define GET_TCP_CEP(id)		(&(tcp_cep[INDEX_TCP_CEP(id)]))

#define GET_TCP_REPID(rep)	((ID)(((rep)-tcp_rep)+TMIN_TCP_REPID))
#define GET_TCP_CEPID(cep)	((ID)(((cep)-tcp_cep)+TMIN_TCP_CEPID))
#define GET_TCP_TWCEPID(cep)	((ID)(((cep)-tcp_twcep)+TMIN_TCP_TWCEPID))

#define IS_TFN_TCP_RCV(t)	((t)==TFN_TCP_ACP_CEP||(t)==TFN_TCP_RCV_DAT||\
				 (t)==TFN_TCP_CLS_CEP||\
				 (t)==TFN_TCP_RCV_BUF||(t)==TFN_TCP_REL_BUF||\
				 (t)==TFN_TCP_RCV_OOB)

#define VALID_TFN_TCP_CAN(t)	((t)==TFN_TCP_ACP_CEP||(t)==TFN_TCP_CON_CEP||\
				 (t)==TFN_TCP_CLS_CEP||\
				 (t)==TFN_TCP_SND_DAT||(t)==TFN_TCP_RCV_DAT||\
				 (t)==TFN_TCP_GET_BUF||(t)==TFN_TCP_RCV_BUF||\
				 (t)==TFN_TCP_SND_OOB||\
				 (t)==TFN_TCP_ALL)

#define VALID_URG_POINTER(urg)	(TCP_CFG_URG_OFFSET==0||urg!=0)

#define VALID_TCP_CEP(cep)	(((cep)->flags&TCP_CEP_FLG_VALID)!=0)
#define DYNAMIC_TCP_CEP(cep)	(((cep)->flags&TCP_CEP_FLG_DYNAMIC)!=0)

#ifdef TCP_CFG_EXTENTIONS

#define VALID_TCP_REP(rep)	(((rep)->flags&TCP_REP_FLG_VALID)!=0)
#define DYNAMIC_TCP_REP(rep)	(((rep)->flags&TCP_REP_FLG_DYNAMIC)!=0)

#else	/* of #ifdef TCP_CFG_EXTENTIONS */

#define VALID_TCP_REP(rep)	(true)
#define DYNAMIC_TCP_REP(rep)	(false)

#endif	/* of #ifdef TCP_CFG_EXTENTIONS */

/*
 *  �S��ϐ�
 */

extern T_TCP_REP tcp_rep[];
extern T_TCP_CEP tcp_cep[];
extern uint8_t tcp_initialized;
extern const ID tmax_tcp_repid;
extern const ID tmax_tcp_cepid;
extern T_TCP_TWCEP tcp_twcep[];

#ifdef SUPPORT_MIB

extern T_TCP_STATS tcp_stats;

#endif	/* of #ifdef SUPPORT_MIB */

/*
 *  Inline �֐�
 */

#ifndef TCP_CFG_RWBUF_CSAVE

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\��
 *  �����̏ꍇ�͉������Ȃ����߂̃_�~�[�̊֐�
 */

/*
 *  tcp_free_rwbufq -- ��M�E�B���h�o�b�t�@�L���[���������B
 */

Inline void
tcp_free_rwbufq_ncs (T_TCP_CEP *cep)
{
	}

#endif	/* of #ifndef TCP_CFG_RWBUF_CSAVE */

#ifdef TCP_CFG_SWBUF_CSAVE_ONLY

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\�݂̂�
 *  �L���̏ꍇ�͉������Ȃ����߂̃_�~�[�̊֐�
 */

/*
 *  tcp_read_swbuf_cs -- ���M�E�B���h�o�b�t�@����f�[�^��ǂݏo���B
 */

Inline void
tcp_read_swbuf_cs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff)
{
	}

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE_ONLY */

#ifndef TCP_CFG_SWBUF_CSAVE

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\��
 *  �����̏ꍇ�͉������Ȃ����߂̃_�~�[�̊֐�
 */

/*
 *  tcp_free_swbufq -- ���M�E�B���h�o�b�t�@�L���[���������B
 */

Inline void
tcp_free_swbufq_ncs (T_TCP_CEP *cep)
{
	}

/*
 *  tcp_alloc_swbuf -- ���M�E�B���h�o�b�t�@�p�̃l�b�g���[�N�o�b�t�@�̊��蓖�Ă��w������B
 */

Inline void
tcp_alloc_swbuf_ncs (T_TCP_CEP *cep)
{
	}

/*
 *  tcp_push_res_nbuf -- �l�b�g���[�N�o�b�t�@��\�񂷂�B
 */

Inline T_NET_BUF *
tcp_push_res_nbuf_ncs (T_NET_BUF *nbuf)
{
	return nbuf;
	}

/*
 *  tcp_pull_res_nbuf -- �\�񂵂Ă���l�b�g���[�N�o�b�t�@�Ԃ��B
 */

Inline T_NET_BUF *
tcp_pull_res_nbuf_ncs (ATR nbatr)
{
	return NULL;
	}

#endif	/* of #ifndef TCP_CFG_SWBUF_CSAVE */

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\�̐؂�ւ��}�N��
 */

#ifdef TCP_CFG_RWBUF_CSAVE

#ifdef TCP_CFG_RWBUF_CSAVE_ONLY

#define TCP_FREE_RWBUFQ(cep)			tcp_free_rwbufq_cs(cep)
#define TCP_DROP_RWBUF(cep,len)			tcp_drop_rwbuf_cs(cep,len)
#define TCP_READ_RWBUF(cep,data,len)		tcp_read_rwbuf_cs(cep,data,len)
#define TCP_GET_RWBUF_ADDR(cep,buf)		tcp_get_rwbuf_addr_cs(cep,buf)
#define TCP_WRITE_RWBUF(cep,input,thoff)	tcp_write_rwbuf_cs(cep,input,thoff)

#else	/* of #ifdef TCP_CFG_RWBUF_CSAVE_ONLY */

#define TCP_FREE_RWBUFQ(cep)			tcp_free_rwbufq(cep)
#define TCP_DROP_RWBUF(cep,len)			tcp_drop_rwbuf(cep,len)
#define TCP_READ_RWBUF(cep,data,len)		tcp_read_rwbuf(cep,data,len)
#define TCP_GET_RWBUF_ADDR(cep,buf)		tcp_get_rwbuf_addr(cep,buf)
#define TCP_WRITE_RWBUF(cep,input,thoff)	tcp_write_rwbuf(cep,input,thoff)

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE_ONLY */

#else	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

#define TCP_FREE_RWBUFQ(cep)			tcp_free_rwbufq_ncs(cep)
#define TCP_DROP_RWBUF(cep,len)			tcp_drop_rwbuf_ncs(cep,len)
#define TCP_READ_RWBUF(cep,data,len)		tcp_read_rwbuf_ncs(cep,data,len)
#define TCP_GET_RWBUF_ADDR(cep,buf)		tcp_get_rwbuf_addr_ncs(cep,buf)
#define TCP_WRITE_RWBUF(cep,input,thoff)	tcp_write_rwbuf_ncs(cep,input,thoff)

#endif	/* of #ifdef TCP_CFG_RWBUF_CSAVE */

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\�̐؂�ւ��}�N��
 */

#ifdef TCP_CFG_SWBUF_CSAVE

#define TCP_PUSH_RES_NBUF(nbuf)			tcp_push_res_nbuf(nbuf)
#define TCP_PULL_RES_NBUF(atr)			tcp_pull_res_nbuf(atr)

#ifdef TCP_CFG_SWBUF_CSAVE_ONLY

#define TCP_FREE_SWBUFQ(cep)			tcp_free_swbufq_cs(cep)
#define TCP_ALLOC_SWBUF(cep)			tcp_alloc_swbuf_cs(cep)
#define TCP_DROP_SWBUF(cep,len)			tcp_drop_swbuf_cs(cep,len)
#define TCP_WRITE_SWBUF(cep,data,len)		tcp_write_swbuf_cs(cep,data,len)
#define TCP_READ_SWBUF(cep,output,len,doff)	tcp_read_swbuf_cs(cep,output,len,doff)
#define TCP_WAIT_SWBUF(cep,tmout)		tcp_wait_swbuf_cs(cep,tmout)
#define TCP_GET_SWBUF_ADDR(cep,buf)		tcp_get_swbuf_addr_cs(cep,buf)
#define TCP_SEND_SWBUF(cep,len)			tcp_send_swbuf_cs(cep,len)
#define TCP_IS_SWBUF_FULL(cep)			tcp_is_swbuf_full_cs(cep)

#else	/* of #ifdef TCP_CFG_SWBUF_CSAVE_ONLY */

#define TCP_FREE_SWBUFQ(cep)			tcp_free_swbufq(cep)
#define TCP_ALLOC_SWBUF(cep)			tcp_alloc_swbuf(cep)
#define TCP_DROP_SWBUF(cep,len)			tcp_drop_swbuf(cep,len)
#define TCP_WRITE_SWBUF(cep,data,len)		tcp_write_swbuf(cep,data,len)
#define TCP_READ_SWBUF(cep,output,len,doff)	tcp_read_swbuf(cep,output,len,doff)
#define TCP_WAIT_SWBUF(cep,tmout)		tcp_wait_swbuf(cep,tmout)
#define TCP_GET_SWBUF_ADDR(cep,buf)		tcp_get_swbuf_addr(cep,buf)
#define TCP_SEND_SWBUF(cep,len)			tcp_send_swbuf(cep,len)
#define TCP_IS_SWBUF_FULL(cep)			tcp_is_swbuf_full(cep)

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE_ONLY */

#else	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

#define TCP_READ_SWBUF(cep,output,len,doff)	tcp_read_swbuf_ncs(cep,output,len,doff)
#define TCP_FREE_SWBUFQ(cep)			tcp_free_swbufq_ncs(cep)
#define TCP_ALLOC_SWBUF(cep)			tcp_alloc_swbuf_ncs(cep)
#define TCP_PUSH_RES_NBUF(nbuf)			tcp_push_res_nbuf_ncs(nbuf)
#define TCP_PULL_RES_NBUF(atr)			tcp_pull_res_nbuf_ncs(atr)
#define TCP_DROP_SWBUF(cep,len)			tcp_drop_swbuf_ncs(cep,len)
#define TCP_WRITE_SWBUF(cep,data,len)		tcp_write_swbuf_ncs(cep,data,len)
#define TCP_WAIT_SWBUF(cep,tmout)		tcp_wait_swbuf_ncs(cep,tmout)
#define TCP_GET_SWBUF_ADDR(cep,buf)		tcp_get_swbuf_addr_ncs(cep,buf)
#define TCP_SEND_SWBUF(cep,len)			tcp_send_swbuf_ncs(cep,len)
#define TCP_IS_SWBUF_FULL(cep)			tcp_is_swbuf_full_ncs(cep)

#endif	/* of #ifdef TCP_CFG_SWBUF_CSAVE */

/*
 *  �֐�
 */

extern uint_t tcp_input (T_NET_BUF **inputp, uint_t *offp, uint_t *nextp);
extern void tcp_init (void);
extern void tcp_init_iss (void);
extern T_TCP_CEP *tcp_close (T_TCP_CEP *cep);
extern T_TCP_CEP *tcp_drop  (T_TCP_CEP *cep, ER errno);
extern void tcp_respond (T_NET_BUF *nbuf, T_TCP_CEP *cep,
                         T_TCP_SEQ ack, T_TCP_SEQ seq, uint_t rbfree, uint8_t flags);
extern void tcp_set_header (T_NET_BUF *nbuf, T_TCP_CEP *cep, uint_t thoff, uint_t optlen);
extern ER tcp_get_segment (T_NET_BUF **nbuf, T_TCP_CEP *cep,
                           uint_t optlen, uint_t len, uint_t maxlen, ATR nbatr, TMO tmout);
extern void tcp_init_cep (T_TCP_CEP *cep);
extern void tcp_notify (T_NET_BUF *input, int code);
extern T_TCP_TIME tcp_rexmt_val (T_TCP_CEP *cep);
extern void tcp_set_persist_timer (T_TCP_CEP *cep);
extern void tcp_cancel_timers (T_TCP_CEP *cep);
extern void tcp_alloc_auto_port (T_TCP_CEP *cep);
extern ER tcp_alloc_port (T_TCP_CEP *cep, uint16_t portno);
extern void tcp_move_twcep (T_TCP_CEP *cep);
extern ER tcp_lock_cep (ID cepid, T_TCP_CEP **p_cep, FN tfn);
extern void tcp_free_reassq (T_TCP_CEP *cep);
extern ER tcp_can_send_more (T_TCP_CEP *cep, FN fncd, TMO tmout);
extern ER tcp_can_recv_more (ER *error, T_TCP_CEP *cep, FN fncd, TMO tmout);
extern uint8_t tcp_move_ra2rw (T_TCP_CEP *cep, uint8_t flags);
extern uint8_t tcp_write_raque (T_NET_BUF *input, T_TCP_CEP *cep, uint_t thoff, uint8_t flags);
extern ER tcp_wait_rwbuf (T_TCP_CEP *cep, TMO tmout);
extern T_TCP_CEP *tcp_user_closed (T_TCP_CEP *cep);

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�p�֐�
 */

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���L���̏ꍇ�A
 *  �֐��̑I���Ɏg�p����B
 */

extern void tcp_free_rwbufq (T_TCP_CEP *cep);
extern void tcp_drop_rwbuf (T_TCP_CEP *cep, uint_t len);
extern void tcp_write_rwbuf (T_TCP_CEP *cep, T_NET_BUF *input, uint_t tcpoff);
extern uint_t tcp_read_rwbuf (T_TCP_CEP *cep, void *data, uint_t len);
extern uint_t tcp_get_rwbuf_addr (T_TCP_CEP *cep, void **p_buf);

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\�p�֐�
 */

extern void tcp_free_rwbufq_cs (T_TCP_CEP *cep);
extern void tcp_drop_rwbuf_cs (T_TCP_CEP *cep, uint_t len);
extern void tcp_write_rwbuf_cs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t tcpoff);
extern uint_t tcp_read_rwbuf_cs (T_TCP_CEP *cep, void *data, uint_t len);
extern uint_t tcp_get_rwbuf_addr_cs (T_TCP_CEP *cep, void **p_buf);

/*
 *  TCP �ʐM�[�_�̎�M�E�B���h�o�b�t�@�́y��z�ȃR�s�[�@�\�p�֐�
 */

extern void tcp_free_rwbufq_ncs (T_TCP_CEP *cep);
extern void tcp_drop_rwbuf_ncs (T_TCP_CEP *cep, uint_t len);
extern void tcp_write_rwbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *input, uint_t tcpoff);
extern uint_t tcp_read_rwbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len);
extern uint_t tcp_get_rwbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf);

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�p�֐�
 */

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\���L���̏ꍇ�A
 *  �֐��̑I���Ɏg�p����B
 */

extern void tcp_free_swbufq (T_TCP_CEP *cep);
extern void tcp_drop_swbuf (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_write_swbuf (T_TCP_CEP *cep, void *data, uint_t len);
extern void tcp_read_swbuf (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff);
extern void tcp_send_swbuf (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_get_swbuf_addr (T_TCP_CEP *cep, void **p_buf);
extern ER tcp_wait_swbuf (T_TCP_CEP *cep, TMO tmout);
extern T_NET_BUF *tcp_push_res_nbuf (T_NET_BUF *buf);
extern T_NET_BUF *tcp_pull_res_nbuf (ATR nbatr);
extern void tcp_alloc_swbuf (T_TCP_CEP *cep);
extern bool_t tcp_is_swbuf_full (T_TCP_CEP *cep);
extern void tcp_init_swbuf (T_TCP_CEP *cep);

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\�p�֐�
 */

extern void tcp_free_swbufq_cs (T_TCP_CEP *cep);
extern void tcp_drop_swbuf_cs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_write_swbuf_cs (T_TCP_CEP *cep, void *data, uint_t len);
extern void tcp_read_swbuf_cs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff);
extern void tcp_send_swbuf_cs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_get_swbuf_addr_cs (T_TCP_CEP *cep, void **p_buf);
extern ER tcp_wait_swbuf_cs (T_TCP_CEP *cep, TMO tmout);
extern void tcp_alloc_swbuf_cs (T_TCP_CEP *cep);
extern bool_t tcp_is_swbuf_full_cs (T_TCP_CEP *cep);

/*
 *  TCP �ʐM�[�_�̑��M�E�B���h�o�b�t�@�́y��z�ȃR�s�[�@�\�p�֐�
 */

extern void tcp_free_swbufq_ncs (T_TCP_CEP *cep);
extern void tcp_drop_swbuf_ncs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_write_swbuf_ncs (T_TCP_CEP *cep, void *data, uint_t len);
extern void tcp_read_swbuf_ncs (T_TCP_CEP *cep, T_NET_BUF *output, uint_t len, uint_t doff);
extern void tcp_send_swbuf_ncs (T_TCP_CEP *cep, uint_t len);
extern ER_UINT tcp_get_swbuf_addr_ncs (T_TCP_CEP *cep, void **p_buf);
extern ER tcp_wait_swbuf_ncs (T_TCP_CEP *cep, TMO tmout);
extern T_NET_BUF *tcp_push_res_nbuf_ncs (T_NET_BUF *buf);
extern T_NET_BUF *tcp_pull_res_nbuf_ncs (ATR nbatr);
extern void tcp_alloc_swbuf_ncs (T_TCP_CEP *cep);
extern bool_t tcp_is_swbuf_full_ncs (T_TCP_CEP *cep);

/*
 *  tcp_find_cep -- �|�[�g�ԍ����� TCP �ʐM�[�_�𓾂�B
 *
 *    ����: myaddr �́A
 *          TINET-1.2 ����l�b�g���[�N�o�C�g�I�[�_�A
 *          TINET-1.1 �܂ł́A�z�X�g�o�C�g�I�[�_
 */
extern T_TCP_CEP *tcp_find_cep (T_IN_ADDR *dstaddr,  uint16_t dstport,
                                T_IN_ADDR *peeraddr, uint16_t peerport);

/*
 *  TCP �w�b�_�̃g���[�X�o�͋@�\�p�֐�
 */
extern void tcp_output_trace (T_NET_BUF *output, T_TCP_CEP *cep);
extern void tcp_input_trace  (T_NET_BUF *input,  T_TCP_CEP *cep);

/* TCP �o�̓^�X�N */

extern void	tcp_output_task(intptr_t exinf);

#endif	/* of #ifndef _TCP_VAR_H_ */
