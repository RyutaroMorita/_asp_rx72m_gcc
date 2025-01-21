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
 *  @(#) $Id: in6_subr.c,v 1.5.4.1 2015/02/05 02:11:26 abe Exp abe $
 */

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1985, 1986, 1993
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
 */

#include <string.h>

#ifdef TARGET_KERNEL_ASP

#include <kernel.h>
#include <sil.h>
#include "kernel_cfg.h"

#endif	/* of #ifdef TARGET_KERNEL_ASP */

#ifdef TARGET_KERNEL_JSP

#include <s_services.h>
#include <t_services.h>
#include "kernel_id.h"
#include "tinet_id.h"

#endif	/* of #ifdef TARGET_KERNEL_JSP */

#include <tinet_defs.h>
#include <tinet_config.h>

#include <net/if.h>
#include <net/if_loop.h>
#include <net/if_ppp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_var.h>
#include <net/net_buf.h>
#include <net/net_timer.h>

#include <netinet/in.h>
#include <netinet/in_var.h>

#include <netinet6/in6.h>
#include <netinet6/in6_var.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet6/ah.h>
#include <netinet6/nd6.h>

#include <net/if6_var.h>

#ifdef SUPPORT_INET6

#if NUM_IN6_HOSTCACHE_ENTRY > 0

/*
 *  �z�X�g�L���b�V��
 */

static T_IN6_HOSTCACHE_ENTRY in6_hostcache[NUM_IN6_HOSTCACHE_ENTRY];

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

/*
 *  in6_lookup_ifaddr -- �l�b�g���[�N�C���^�t�F�[�X�Ɋ��蓖�Ă��Ă���A�h���X��T������B
 */

T_IN6_IFADDR *
in6_lookup_ifaddr (T_IFNET *ifp, T_IN6_ADDR *addr)
{
	int_t ix;

	for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
		if ((ifp->in_ifaddrs[ix].flags & IN6_IFF_DEFINED) &&
		    IN6_ARE_ADDR_EQUAL(addr, &ifp->in_ifaddrs[ix].addr))
			return &ifp->in_ifaddrs[ix];
		}
	return NULL;
	}

/*
 *  in6_lookup_multi -- �l�b�g���[�N�C���^�t�F�[�X�̃}���`�L���X�g�A�h���X����������B
 */

bool_t
in6_lookup_multi (T_IFNET *ifp, T_IN6_ADDR *maddr)
{
	int_t ix;

	for (ix = MAX_IN6_MADDR_CNT; ix -- > 0; )
		if (IN6_ARE_ADDR_EQUAL(maddr, &ifp->in_maddrs[ix]))
			return true;
	return false;
	}

/*
 *  in6_set_header -- IPv6 �w�b�_��ݒ肷��B
 */

ER
in6_set_header (T_NET_BUF *nbuf, uint_t len,
                T_IN6_ADDR *dstaddr, T_IN6_ADDR *srcaddr,
                uint8_t next, uint8_t hlim)
{
	T_IFNET		*ifp = IF_GET_IFNET();
	T_IP6_HDR	*ip6h;
	T_IN6_IFADDR	*ia;

	/*
	 *  ����A�h���X�ɂӂ��킵�����M���A�h���X���A
	 *  �l�b�g���[�N�C���^�t�F�[�X����T�����ė��p����B
	 */
	if (srcaddr == NULL || !IN6_IS_ADDR_UNSPECIFIED(srcaddr))
		;
	else if ((ia = in6_ifawithifp(ifp, dstaddr)) == NULL)
		return E_SYS;
	else
		srcaddr = &ia->addr;

	/* IPv6 �w�b�_��ݒ肷��B*/
	ip6h		= GET_IP6_HDR(nbuf);
	ip6h->vcf	= htonl(IP6_MAKE_VCF(IPV6_VERSION, 0));
	ip6h->plen	= htons(len);
	ip6h->next	= next;
	ip6h->hlim	= hlim;

	if (dstaddr == NULL)
		memset(&ip6h->dst, 0, sizeof(T_IN6_ADDR));
	else
		ip6h->dst = *dstaddr;

	if (srcaddr == NULL)
		memset(&ip6h->src, 0, sizeof(T_IN6_ADDR));
	else
		ip6h->src = *srcaddr;

	return E_OK;
	}

/*
 *  in6_get_datagram -- IPv6 �f�[�^�O�������l�����A�w�b�_��ݒ肷��B
 */

ER
in6_get_datagram (T_NET_BUF **nbuf, uint_t len, uint_t maxlen,
                  T_IN6_ADDR *dstaddr, T_IN6_ADDR *srcaddr,
                  uint8_t next, uint8_t hlim, ATR nbatr, TMO tmout)
{
	ER		error;
	uint_t		align;

	/* �f�[�^���� 4 �I�N�e�b�g���E�ɒ�������B	*/
	align = (len + 3) >> 2 << 2;

	/* �l�b�g���[�N�o�b�t�@���l������B	*/
	if ((error = tget_net_buf_ex(nbuf, IF_IP6_HDR_SIZE + align,
	                                   IF_IP6_HDR_SIZE + maxlen, nbatr, tmout)) != E_OK)
		return error;

	/*
	 *  ���傫�ȃT�C�Y�̃l�b�g���[�N�o�b�t�@���l������ꍇ�̂ݒ����𒲐�����B
	 *  ��菬���ȃT�C�Y�̃l�b�g���[�N�o�b�t�@�̊l���́A���M�E�B���h�o�b�t�@��
	 *  �ȃR�s�[�@�\�Ŏg�p����A���ۂɑ��M����܂ŁA�f�[�^�T�C�Y�͌���ł��Ȃ��B
	 */
	if ((nbatr & NBA_SEARCH_ASCENT) != 0)
		(*nbuf)->len = IF_IP6_HDR_SIZE + len;

	/* IPv6 �w�b�_��ݒ肷��B*/
	if ((error = in6_set_header(*nbuf, len, dstaddr, srcaddr, next, hlim)) != E_OK)
		return error;

	/* 4 �I�N�e�b�g���E�܂Ńp�f�B���O�Ŗ��߂�B*/
	if (align > len)
		memset(GET_IP6_SDU(*nbuf) + len, 0, align - len);

	return E_OK;
	}

/*
 *  in6_get_maxnum_ifaddr -- �C���^�t�F�[�X�ɐݒ�\�ȍő�A�h���X����Ԃ��B
 */

ER_UINT
in6_get_maxnum_ifaddr (void)
{
	return NUM_IN6_IFADDR_ENTRY;
	}

/*
 *  in6_get_ifaddr -- �C���^�t�F�[�X�ɐݒ肳��Ă���A�h���X��Ԃ��B
 */

const T_IN6_ADDR *
in6_get_ifaddr (int_t index)
{
	T_IFNET		*ifp = IF_GET_IFNET();

	if (index < NUM_IN6_IFADDR_ENTRY &&
	    (ifp->in_ifaddrs[index].flags & IN6_IFF_DEFINED))
		return &ifp->in_ifaddrs[index].addr;
	else
		return NULL;
	}

/*
 *  ipv62str -- IPv6 �A�h���X�𕶎���ɕϊ�����B
 */

char *
ipv62str (char *buf, const T_IN6_ADDR *p_ip6addr)
{
	static char	addr_sbuf[NUM_IPV6ADDR_STR_BUFF][sizeof("0123:4567:89ab:cdef:0123:4567:89ab:cdef")];
	static int_t	bix = NUM_IPV6ADDR_STR_BUFF;

	bool_t	omit = false, zero = false;
	char	*start;
	int_t	ix;

	if (buf == NULL) {
		syscall(wai_sem(SEM_IP2STR_BUFF_LOCK));
		buf = addr_sbuf[-- bix];
		if (bix <= 0)
			bix = NUM_IPV6ADDR_STR_BUFF;
		syscall(sig_sem(SEM_IP2STR_BUFF_LOCK));
		}

	start = buf;
	if (p_ip6addr == NULL) {
		*buf ++ = ':';
		*buf ++ = ':';
		}
	else {
		for (ix = 0; ix < sizeof(T_IN6_ADDR) / 2; ix ++) {
			if (omit) {
				buf += convert_hexdigit(buf, ntohs(p_ip6addr->s6_addr16[ix]), 16, 0, ' '); 
				if (ix < 7)
					*buf ++ = ':';
				}
			else if (ix > 0 && ix < 7 && p_ip6addr->s6_addr16[ix] == 0)
				zero = true;
			else {
				if (zero) {
					omit = true;
					*buf ++ = ':';
					}
				buf += convert_hexdigit(buf, ntohs(p_ip6addr->s6_addr16[ix]), 16, 0, ' '); 
				if (ix < 7)
					*buf ++ = ':';
				}
			}
		}
	*buf = '\0';
	return start;
	}

/*
 *  in6_cksum -- IPv6 �̃g�����X�|�[�g�w�w�b�_�̃`�F�b�N�T�����v�Z����B
 *
 *  ����: �߂�l�̓l�b�g���[�N�o�C�g�I�[�_
 */

uint16_t
in6_cksum (T_NET_BUF *nbuf, uint8_t proto, uint_t off, uint_t len)
{
	uint32_t	sum;
	uint_t		align;

	/* 4 �I�N�e�b�g���E�̃f�[�^�� */
	align = (len + 3) >> 2 << 2;

	/* 4 �I�N�e�b�g���E�܂Ńp�f�B���O�Ŗ��߂�B*/
	if (align > len)
		memset((uint8_t*)nbuf->buf + off + len, 0, align - len);

	sum = in_cksum_sum(nbuf->buf + off, align)
	    + in_cksum_sum(&GET_IP6_HDR(nbuf)->src, sizeof(T_IN6_ADDR) * 2)
	    + len + proto;
	sum = in_cksum_carry(sum);

	return ~htons((uint16_t)sum);
	}

/*
 *  in6_is_dstaddr_accept -- ����A�h���X�Ƃ��Đ��������`�F�b�N����B
 */

bool_t
in6_is_dstaddr_accept (T_IN6_ADDR *myaddr, T_IN6_ADDR *dstaddr)
{
	if (IN6_IS_ADDR_UNSPECIFIED(myaddr))
		return in6_lookup_ifaddr(IF_GET_IFNET(), dstaddr) != NULL;
	else
		return IN6_ARE_ADDR_EQUAL(dstaddr, myaddr);
	}

/*
 *  get_ip6_hdr_size -- �g���w�b�_���܂߂� IPv6 �w�b�_����Ԃ��B
 */

uint_t
get_ip6_hdr_size (T_IP6_HDR *iph)
{
	uint_t	size = IP6_HDR_SIZE, hsize;
	uint8_t	curr = iph->next, next;
	uint8_t	*hdr = ((uint8_t *)iph) + IP6_HDR_SIZE;

	while (1) {
		next = *hdr;
		if (curr ==IPPROTO_NONE)		/* ���w�b�_����			*/
			break;
		else if (curr == IPPROTO_FRAGMENT)	/* �f�Љ�			*/
			hsize = sizeof(T_IP6_FRAG_HDR);
		else if (curr == IPPROTO_AH)		/* IPv6 �F��			*/
			hsize = (((T_IP6_AH_HDR *)hdr)->len + 2) * 4;
		else if (curr == IPPROTO_HOPOPTS ||	/* ���p�_ (Hop-by-Hop) �I�v�V����	*/
		         curr == IPPROTO_DSTOPTS ||	/* IPv6 �I�_�I�v�V����		*/
		         curr == IPPROTO_ROUTING)	/* �o�H����			*/
			hsize = (((T_IP6_EXT_HDR *)hdr)->len + 1) * 8;
		else
			break;
		size += hsize;
		hdr  += hsize;
		curr = next;
		}
	return size;
	}

/*
 *  in6_plen2pmask -- �v���t�B�b�N�X������}�X�N�𐶐�����B
 */

void
in6_plen2pmask (T_IN6_ADDR *mask, uint_t prefix_len)
{
	uint8_t	*ptr, bit;

	memset(mask->s6_addr + prefix_len / 8, 0, (128 - prefix_len + 7) / 8);
	for (ptr = mask->s6_addr; prefix_len > 0; ptr ++) {
		for (bit = 0x80; bit && (prefix_len > 0); prefix_len --) {
			*ptr |= bit;
			bit >>= 1;
			}
		}
	}

/*
 *  in6_rtalloc -- ���[�e�B���O�\��T������B
 */

T_IN6_ADDR *
in6_rtalloc (T_IFNET *ifp, T_IN6_ADDR *dst)
{
	if (IN6_IS_ADDR_LINKLOCAL(dst) || IN6_IS_ADDR_MULTICAST(dst))
		return dst;
	else {
		T_IN6_IFADDR	*ia;
		SYSTIM		now;
		int_t		ix;

		/*
		 *  �T�C�g���[�J���A�h���X���W��\�i�O���[�o���j�A�h���X�̏ꍇ�́A
		 *  ���ꃊ���N���̃m�[�h�ł��邩���`�F�b�N����B
		 */

		syscall(get_tim(&now));
		now /= SYSTIM_HZ;

		/* �����L�����ԓ��̃A�h���X��T������B*/
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if (IFA6_IS_READY(ia) &&
			    in6_are_prefix_equal(dst, &ia->addr, ia->prefix_len) &&
			    (int32_t)(ia->lifetime.preferred - now) > 0) {
		                   /* ia->lifetime.preferred > now */
				return dst;
				}
			}

		/* �L�����ԓ��̃A�h���X��T������B*/
		for (ix = NUM_IN6_IFADDR_ENTRY; ix -- > 0; ) {
			ia = &ifp->in_ifaddrs[ix];
			if (IFA6_IS_READY(ia) &&
			    in6_are_prefix_equal(dst, &ia->addr, ia->prefix_len) &&
			    (int32_t)(ia->lifetime.expire - now) > 0)
		                   /* ia->lifetime.expire > now */
				return dst;
			}

		/*
		 *  �v���t�B�b�N�X��T������B
		 */
		if (nd6_onlink_prefix_lookup (dst) != NULL)
			return dst;

		/*
		 *  �ÓI�o�H�\��T������B
		 */

#if NUM_ROUTE_ENTRY > 0

		syscall(wai_sem(SEM_IN_ROUTING_TBL));
		for (ix = NUM_ROUTE_ENTRY; ix --; ) {
			if ((routing_tbl[ix].flags & IN_RTF_DEFINED) &&
			    in6_are_prefix_equal(dst, &routing_tbl[ix].target,
			                               routing_tbl[ix].prefix_len)) {

				/*
				 *  ���������ɂ��G���g���́A�L�����Ԃ��؂�鎞������������B
				 *  expire �̒P�ʂ� [s]�B
				 *  TMO_IN_REDIRECT �̒P�ʂ� [ms]�B
				 */
				if (ix > NUM_STATIC_ROUTE_ENTRY) {
					SYSTIM	now;

					syscall(get_tim(&now));
					routing_tbl[ix].expire = now / SYSTIM_HZ + TMO_IN_REDIRECT / 1000;
					}

				syscall(sig_sem(SEM_IN_ROUTING_TBL));
				return &routing_tbl[ix].gateway;
				}
			}
		syscall(sig_sem(SEM_IN_ROUTING_TBL));

#endif	/* of #if NUM_ROUTE_ENTRY > 0 */

		/*
		 *  �f�B�t�H���g���[�^�E���X�g��T������B
		 */
		return nd6_router_lookup();
		}
	}

#if NUM_REDIRECT_ROUTE_ENTRY > 0

/*
 *  in6_gateway_lookup -- ���[�e�B���O�\�̃��[�^��T������B
 */

T_IN_RTENTRY *
in6_gateway_lookup (T_IN6_ADDR *gw)
{
	int_t	ix;

	for (ix = NUM_ROUTE_ENTRY; ix --; )
		if ((routing_tbl[ix].flags & IN_RTF_DEFINED) &&
		    IN6_ARE_ADDR_EQUAL(&routing_tbl[ix].gateway, gw))
			return &routing_tbl[ix];
	return NULL;
	}

/*
 *  in6_rtredirect -- ���[�e�B���O�\�ɃG���g����o�^����B
 *
 *    ����: ���� tmo �̒P�ʂ� [ms]�B
 */

void
in6_rtredirect (T_IN6_ADDR *gateway, T_IN6_ADDR *target, uint_t prefix_len, uint8_t flags, uint32_t tmo)
{
	T_IN_RTENTRY	*frt;

	frt = in_rtnewentry(flags, tmo);
	frt->gateway    = *gateway;
	frt->target     = *target;
	frt->prefix_len = prefix_len;
	}

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

#if NUM_IN6_HOSTCACHE_ENTRY > 0

/*
 *  in6_hostcache_lookup -- IPv6 �z�X�g�L���b�V����T������B
 */

static T_IN6_HOSTCACHE_ENTRY*
in6_hostcache_lookup (T_IN6_ADDR *dst)
{
	int_t ix;

	for (ix = NUM_IN6_HOSTCACHE_ENTRY; ix -- > 0; ) {
		if (IN6_ARE_ADDR_EQUAL(dst, &in6_hostcache[ix].dst))
			return &in6_hostcache[ix];
		}
	return NULL;
	}

/*
 *  in6_hostcache_update -- IPv6 �z�X�g�L���b�V�����X�V����B
 */

void
in6_hostcache_update (T_IN6_ADDR *dst, uint32_t mtu)
{
	T_IN6_HOSTCACHE_ENTRY	*hc;
	SYSTIM	now, old;
	int_t	ix, oix;

	syscall(get_tim(&now));

	/* ���ɓo�^����Ă��邩�T������B*/
	if ((hc = in6_hostcache_lookup (dst)) == NULL) {

		/* �󂫂̃z�X�g�L���b�V����T���B*/
		for (ix = NUM_IN6_HOSTCACHE_ENTRY; ix -- > 0; ) {
			if (IN6_IS_HOSTCACHE_FREE(&in6_hostcache[ix]))
				break;
			}

		if (ix < 0) {
			/*
			 *  �󂫂��������́A�L�����Ԃ̐؂�鎞�Ԃ��A
			 *  �ł��Z���z�X�g�L���b�V����u������B
			 */
			old = now - 1;
			oix = 0;
			for (ix = NUM_IN6_HOSTCACHE_ENTRY; ix -- > 0; ) {
				hc = &in6_hostcache[ix];
				if (IN6_IS_HOSTCACHE_BUSY(hc) && (int32_t)(hc->expire - old) < 0) {
				                                        /* hc->expire < old */
					oix = ix;
					old = hc->expire;
					}
				}
			ix = oix;
			}
		hc = &in6_hostcache[ix];
		}
	else if (mtu > hc->mtu &&
	         (int32_t)(hc->expire - now) >= (IN6_HOSTCACHE_EXPIRE - IN6_HOSTCACHE_INCREASE)) {

		/*
		 *  ���ɓo�^����Ă��āA�V���� MTU ���A�o�^����Ă��� MTU ���傫���Ƃ��A
		 *  IN6_HOSTCACHE_INCREASE�i���� 10 ���j�Ԃ͍X�V���Ȃ��B
		 */
		return;
		}
	hc->dst    = *dst;
	hc->expire = now + IN6_HOSTCACHE_EXPIRE;
	hc->mtu    = mtu;
	}

/*
 *  in6_hostcache_getmtu -- IPv6 �z�X�g�L���b�V�������� MTU ���擾����B
 *
 *    �߂�l�� 0 �ł���΁A�z�X�g�L���b�V���ɓo�^����Ă��Ȃ��B
 */

uint32_t
in6_hostcache_getmtu (T_IN6_ADDR *dst)
{
	T_IN6_HOSTCACHE_ENTRY	*hc;

	/* ���ɓo�^����Ă��邩�T������B*/
	if ((hc = in6_hostcache_lookup(dst)) == NULL)
		return 0;
	else
		return hc->mtu;
	}

/*
 *  in6_hostcache_timer -- IPv6 �z�X�g�L���b�V���X�V�^�C�}�[
 *
 *    1�b�����ŋN�������B
 */

static void
in6_hostcache_timer (void)
{
	static int_t interval = IN6_HOSTCACHE_PRUNE / SYSTIM_HZ;

	SYSTIM	now;

	interval --;
	if (interval <= 0) {
		syscall(get_tim(&now));
		interval = IN6_HOSTCACHE_PRUNE / SYSTIM_HZ;
		}
	}

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

/*
 *  in6_timer -- IPv6 ���ʃ^�C�}�[
 *
 *    1�b�����ŋN�������B
 */

static void
in6_timer (void)
{
#if NUM_REDIRECT_ROUTE_ENTRY > 0

	in_rttimer();

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

#ifdef IP6_CFG_FRAGMENT

	frag6_timer();

#endif	/* of #ifdef IP6_CFG_FRAGMENT */

#if NUM_IN6_HOSTCACHE_ENTRY > 0

	in6_hostcache_timer();

#endif	/* of #if NUM_IN6_HOSTCACHE_ENTRY > 0 */

	timeout((callout_func)in6_timer, NULL, IN_TIMER_TMO);
	}

/*
 *  in6_init -- IPv6 ���ʋ@�\������������B
 */

void
in6_init (void)
{
#if NUM_REDIRECT_ROUTE_ENTRY > 0

	in_rtinit();

#endif	/* of #if NUM_REDIRECT_ROUTE_ENTRY > 0 */

	timeout((callout_func)nd6_timer, NULL, ND6_TIMER_TMO);
	timeout((callout_func)in6_timer, NULL, IN_TIMER_TMO);
	}

#endif /* of #ifdef SUPPORT_INET6 */
