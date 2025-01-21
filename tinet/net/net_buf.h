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
 *  @(#) $Id: net_buf.h,v 1.5 2009/12/24 05:42:40 abe Exp $
 */

#ifndef _NET_BUF_H_
#define _NET_BUF_H_

/*
 *  �l�b�g���[�N�o�b�t�@
 *
 *    4 �I�N�e�b�g�ŃA���C������K�v�̂���v���Z�b�T���l�����āA
 *    IF �w�b�_�T�C�Y�� 4 �I�N�e�b�g���E�łȂ��̏ꍇ�A
 *    IP �w�b�_�ȍ~�� 4 �I�N�e�b�g���E�ɒ�������B
 */

#ifndef CPU_NET_ALIGN
#error "CPU_NET_ALIGN expected."
#endif

/*
 *  �e���v���[�g
 */

struct t_net_buf {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[4];	/* �o�b�t�@�{��		*/
	};

#ifndef T_NET_BUF_DEFINED

typedef struct t_net_buf T_NET_BUF;

#define T_NET_BUF_DEFINED

#endif	/* of #ifndef T_NET_BUF_DEFINED */
/*
 *  64 �I�N�e�b�g
 */

typedef struct t_net_buf_64 {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[64]; /* �o�b�t�@�{��	*/
	} T_NET_BUF_64;

/*
 *  128 �I�N�e�b�g
 */

typedef struct t_net_buf_128 {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[128]; /* �o�b�t�@�{��	*/
	} T_NET_BUF_128;

/*
 *  256 �I�N�e�b�g
 */

typedef struct t_net_buf_256 {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[256]; /* �o�b�t�@�{��	*/
	} T_NET_BUF_256;

/*
 *  512 �I�N�e�b�g
 */

typedef struct t_net_buf_512 {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[512];/* �o�b�t�@�{��	*/
	} T_NET_BUF_512;

/*
 *  1024 �I�N�e�b�g
 */

typedef struct t_net_buf_1024 {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[1024]; /* �o�b�t�@�{��	*/
	} T_NET_BUF_1024;

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�̍ő� PDU �T�C�Y
 */

typedef struct t_net_buf_if_pdu {
	uint16_t	len;	/* �f�[�^�̒���		*/
	uint8_t		idix;	/* mpfid �̃C���f�b�N�X	*/
	uint8_t		flags;	/* �t���O		*/
#ifdef IF_ETHER_NIC_NET_BUF_ALIGN
	uint8_t		nalign[IF_ETHER_NIC_NET_BUF_ALIGN];
#endif
#if CPU_NET_ALIGN == 4 && IF_HDR_ALIGN != 4
	uint8_t		halign[4 - IF_HDR_ALIGN];
#endif
	uint8_t		buf[IF_PDU_SIZE];
				/* �o�b�t�@�{��		*/
#if defined(IF_PDU_HDR_PADDING)
	uint8_t		padding[IF_PDU_HDR_PADDING];
#endif				/* �w�b�_�̗]��		*/
	} T_NET_BUF_IF_PDU;

/*
 *  �l�b�g���[�N�o�b�t�@�\
 */

typedef struct t_net_buf_entry {

	uint16_t	index;
	uint_t		size;

#if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF

	ulong_t		prepares;
	ulong_t		requests;
	ulong_t		allocs;
	ulong_t		errors;

#endif	/* of #if NET_COUNT_ENABLE & PROTO_FLG_NET_BUF */

	} T_NET_BUF_ENTRY;

/*
 *  �l�b�g���[�N�o�b�t�@�E�t���O	
 */

/*
 *  �l�b�g���[�N�C���^�t�F�[�X�o�͌�Ƀl�b�g���[�N�o�b�t�@���J�����Ȃ��B
 *  ����: �o�͌�ɂ��̃t���O�̓N���A�����B
 */
#define NB_FLG_NOREL_IFOUT	UINT_C(0x80)

/*
 *  ESP �p�t���O
 */
#define NB_FLG_DECRYPED		UINT_C(0x40)

/*
 *  �l�b�g���[�N�o�b�t�@�l������
 */

/* �T������ */

#define NBA_SEARCH_ASCENT	UINT_C(0x1000)	/* �傫�ȃT�C�Y�̕����ɒT������B	*/
#define NBA_SEARCH_DESCENT	UINT_C(0x2000)	/* �����ȃT�C�Y�̕����ɒT������B	*/
#define NBA_RESERVE_TCP		UINT_C(0x4000)	/* TCP �p�Ƀl�b�g���[�N�o�b�t�@��\�񂷂�B*/
#define NBA_ID_MASK		UINT_C(0x0fff)	/* �ʐM�[�_ ID ��n���ꍇ�̃}�X�N�l	*/

/*
 *  �֐��V�~�����[�V�����}�N��
 */

#define get_net_buf(b,l)	tget_net_buf((b),(l),TMO_FEVR)

/*
 *  �֐�
 */

extern ER tget_net_buf_ex (T_NET_BUF **blk, uint_t minlen, uint_t maxlen, ATR nbatr, TMO tmout);
extern ER tget_net_buf (T_NET_BUF **blk, uint_t len, TMO tmout);
extern ER rel_net_buf (T_NET_BUF *blk);
extern ER rus_net_buf (T_NET_BUF *blk);
extern ER_UINT net_buf_siz (T_NET_BUF *blk);
extern uint_t net_buf_max_siz (void);
extern const T_NET_BUF_ENTRY *nbuf_get_tbl (void);
extern uint_t nbuf_get_tbl_size (void);

#endif	/* of #ifndef _NET_BUF_H_ */
