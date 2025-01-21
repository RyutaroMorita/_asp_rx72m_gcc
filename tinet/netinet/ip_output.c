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
 *  @(#) $Id: ip_output.c,v 1.5.4.1 2015/02/05 02:10:53 abe Exp abe $
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
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
 *	@(#)output.c	8.3 (Berkeley) 1/21/94
 * $FreeBSD: src/sys/netinet/output.c,v 1.85.2.4 1999/08/29 16:29:49 peter Exp $
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/ppp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_count.h>

#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>

#if defined(SUPPORT_IPSEC)
#include <netinet6/ipsec.h>
#endif

static uint16_t frag_id = 0;

/*
 *  IP output -- IP �̏o�͊֐�
 *
 *    ����: �o�[�W�����ƃw�b�_���͏�ʑw�Őݒ肷��B
 */

ER
ip_output (T_NET_BUF *output, TMO tmout)
{
	T_IP4_HDR	*ip4h;
	ER		error = E_OK;
	T_IN4_ADDR	gw;

#ifdef SUPPORT_IPSEC
	T_SECPOLICY* sp;
	int ipsec_error;
        int policy;
#endif /* SUPPORT_IPSEC */

	NET_COUNT_MIB(ip_stats.ipOutRequests, 1);

#ifdef SUPPORT_IPSEC
        /* XXX: IPsec�̏����̓p�P�b�g�f�Љ��̑O�ɍs���� */

	/* SPD���擾���� */
	sp = ipsec4_getpolicybyaddr(output, IPSEC_DIR_OUTBOUND, &ipsec_error);
	if (sp==NULL) {
                error = ipsec_error;
                return error;
        }

        /* �|���V���`�F�b�N����*/
#if 0
        switch (sp->policy) {

        case IPSEC_POLICY_BYPASS:
        case IPSEC_POLICY_NONE:
        case IPSEC_POLICY_TCP:
                goto skip_ipsec;

                break; /* NOTREACHED */

        case  IPSEC_POLICY_IPSEC:
                /* XXX: SH2�ł͂�����illegal Instruction����������B�R���p�C���̃o�O? */
                if (sp->req == NULL) {
                        /* �������f�[�����ɑ΂���SA�̎擾��v������ */
                        goto bad;
                }
                break;

        default:
                /* �s���ȃ|���V */
                goto bad;
                break;
        }
#else /* 0 */
        /* XXX: �R���p�C���̕s�����̂��� switch�����if���ŏ��������� */
        policy = sp->spinitb->policy;

        if (policy == IPSEC_POLICY_BYPASS ||
            policy == IPSEC_POLICY_NONE ||
            policy == IPSEC_POLICY_TCP)
                goto skip_ipsec;
        else if (policy == IPSEC_POLICY_IPSEC) {
                if (sp->req == NULL)
                        /* �������f�[�����ɑ΂���SA�̎擾��v������ */
                        goto bad;
        } else
                goto bad;

#endif /* 0 */

		{
			T_IPSEC_OUTPUT_STATE state;

			state.m = output;
			/* XXX: ipsec4_output()���ł́Aip->{len,off}���l�b�g���[�N�o�C�g�I�[�_�Ƃ��� */
			error = ipsec4_output (&state, sp, 0 /* flags */ );
			output = state.m;

			if (error) {
				/* net_buf ��ipsec4_output�ɂ���Ċ��ɉ������Ă��� */
				switch (error) {
				default:
					syslog (LOG_NOTICE, "ip_output:%d error", __LINE__);
				}
			}
		}

        /* ipsec4_output�ɉe�����󂯂��l���X�V���� */
        /* XXX: �K�v��? */

skip_ipsec:
#endif /* SUPPORT_IPSEC */

#ifdef IP4_CFG_FRAGMENT

	ip4h = GET_IP4_HDR(output);

	gw = in4_rtalloc(ntohl(ip4h->dst));

	/*
	 *  �f�[�^�O�����T�C�Y���l�b�g���[�N�� MTU �𒴂��Ă���΁A
	 *  �������đ��M����B
	 */
	if (ntohs(ip4h->len) > IF_MTU) {
		T_NET_BUF	*frag;
		T_IP4_HDR	*fip4h;
		uint_t		off, hlen, len, flen, align;

		NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_OUT], 1);
		NET_COUNT_MIB(ip_stats.ipFragCreates, 1);

		len  = ntohs(ip4h->len);
		off  = hlen = GET_IP4_HDR_SIZE(ip4h);
		while (off < len) {
			if (off + (IF_MTU - IP4_HDR_SIZE) < len)
				flen = IF_MTU - IP4_HDR_SIZE;
			else
				flen = len - off;

			/* �f�[�^���� 4 �I�N�e�b�g���E�ɒ�������B	*/
			align = (flen + 3) >> 2 << 2;

			/* �l�b�g���[�N�o�b�t�@���l������B*/
			if (tget_net_buf(&frag, align + IF_IP4_HDR_SIZE, TMO_IP4_FRAG_GET_NET_BUF) == E_OK) {

				/* �t���O�����g���R�s�[����B*/
				memcpy(GET_IP4_SDU(frag), (uint8_t *)ip4h + off, flen);

				/* �w�b�_�𖄂߂�B*/
				fip4h		= GET_IP4_HDR(frag);
				*fip4h		= *ip4h;
				fip4h->flg_off	= htons(IP4_MAKE_FLGOFF(off + flen == len ? 0 : IP4_MF,
						                       (off - hlen) >> 3));
				fip4h->len	= htons(flen + IP4_HDR_SIZE);
				fip4h->id	= htons(frag_id);
				fip4h->sum	= 0;
				fip4h->sum	= in_cksum(fip4h, GET_IP4_HDR_SIZE(fip4h));

				NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_OCTETS], ntohs(fip4h->len));
				NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_PACKETS], 1);
				NET_COUNT_IP4(net_count_ip4[NC_IP4_FRAG_OUT_FRAGS], 1);

				IF_SET_PROTO(frag, IF_PROTO_IP);
				if ((error = IF_OUTPUT(frag, &gw, NULL, tmout)) != E_OK) {
					syscall(rel_net_buf(output));
					NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
					NET_COUNT_MIB(ip_stats.ipFragFails, 1);
					return error;
					}
				}
			else {
				/* �l���ł��Ȃ���΁A���M��������߂�B*/
				syscall(rel_net_buf(output));
				NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
				NET_COUNT_MIB(ip_stats.ipFragFails, 1);
				return E_NOMEM;
				}

			off += IF_MTU - IP4_HDR_SIZE;
			}
		syscall(rel_net_buf(output));
		frag_id ++;
		NET_COUNT_MIB(ip_stats.ipFragOKs, 1);
		}
	else {

		/* �w�b�_�𖄂߂�B*/
		ip4h->id  = htons(frag_id);
		frag_id ++;
		ip4h->sum = 0;
		ip4h->sum = in_cksum(ip4h, GET_IP4_HDR_SIZE(ip4h));

		NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_OCTETS], ntohs(ip4h->len));
		NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_PACKETS], 1);

		IF_SET_PROTO(output, IF_PROTO_IP);
		if ((error = IF_OUTPUT(output, &gw, NULL, tmout)) != E_OK)
			NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
		}

#else	/* of #ifdef IP4_CFG_FRAGMENT */

	ip4h = GET_IP4_HDR(output);

	/* �f�[�^�O�����T�C�Y���l�b�g���[�N�� MTU �𒴂��Ă���΃G���[ */
	if (ntohs(ip4h->len) > IF_MTU)
		return E_PAR;

	/* �w�b�_�𖄂߂�B*/
	ip4h->id  = htons(frag_id);
	frag_id ++;
	ip4h->sum = 0;
	ip4h->sum = in_cksum(ip4h, (uint_t)GET_IP4_HDR_SIZE(ip4h));

	NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_OCTETS], ntohs(ip4h->len));
	NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_PACKETS], 1);

	gw = in4_rtalloc(ntohl(ip4h->dst));
	IF_SET_PROTO(output, IF_PROTO_IP);
	if ((error = IF_OUTPUT(output, &gw, NULL, tmout)) != E_OK)
		NET_COUNT_IP4(net_count_ip4[NC_IP4_OUT_ERR_PACKETS], 1);
		NET_COUNT_MIB(ip_stats.ipOutDiscards, 1);

#endif	/* of #ifdef IP4_CFG_FRAGMENT */

#ifdef SUPPORT_IPSEC
	bad:
#endif /* SUPPORT_IPSEC */

	return error;
	}
