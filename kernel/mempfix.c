/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: mempfix.c 2632 2014-04-13 11:30:37Z ertl-hiro $
 */

/*
 *		固定長メモリプール機能
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mempfix.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_GET_MPF_ENTER
#define LOG_GET_MPF_ENTER(mpfid, p_blk)
#endif /* LOG_GET_MPF_ENTER */

#ifndef LOG_GET_MPF_LEAVE
#define LOG_GET_MPF_LEAVE(ercd, blk)
#endif /* LOG_GET_MPF_LEAVE */

#ifndef LOG_PGET_MPF_ENTER
#define LOG_PGET_MPF_ENTER(mpfid, p_blk)
#endif /* LOG_PGET_MPF_ENTER */

#ifndef LOG_PGET_MPF_LEAVE
#define LOG_PGET_MPF_LEAVE(ercd, blk)
#endif /* LOG_PGET_MPF_LEAVE */

#ifndef LOG_TGET_MPF_ENTER
#define LOG_TGET_MPF_ENTER(mpfid, p_blk, tmout)
#endif /* LOG_TGET_MPF_ENTER */

#ifndef LOG_TGET_MPF_LEAVE
#define LOG_TGET_MPF_LEAVE(ercd, blk)
#endif /* LOG_TGET_MPF_LEAVE */

#ifndef LOG_REL_MPF_ENTER
#define LOG_REL_MPF_ENTER(mpfid, blk)
#endif /* LOG_REL_MPF_ENTER */

#ifndef LOG_REL_MPF_LEAVE
#define LOG_REL_MPF_LEAVE(ercd)
#endif /* LOG_REL_MPF_LEAVE */

#ifndef LOG_INI_MPF_ENTER
#define LOG_INI_MPF_ENTER(mpfid)
#endif /* LOG_INI_MPF_ENTER */

#ifndef LOG_INI_MPF_LEAVE
#define LOG_INI_MPF_LEAVE(ercd)
#endif /* LOG_INI_MPF_LEAVE */

#ifndef LOG_REF_MPF_ENTER
#define LOG_REF_MPF_ENTER(mpfid, pk_rmpf)
#endif /* LOG_REF_MPF_ENTER */

#ifndef LOG_REF_MPF_LEAVE
#define LOG_REF_MPF_LEAVE(ercd, pk_rmpf)
#endif /* LOG_REF_MPF_LEAVE */

/*
 *  固定長メモリプールの数
 */
#define tnum_mpf	((uint_t)(tmax_mpfid - TMIN_MPFID + 1))

/*
 *  固定長メモリプールIDから固定長メモリプール管理ブロックを取り出すた
 *  めのマクロ
 */
#define INDEX_MPF(mpfid)	((uint_t)((mpfid) - TMIN_MPFID))
#define get_mpfcb(mpfid)	(&(mpfcb_table[INDEX_MPF(mpfid)]))

/*
 *  特殊なインデックス値の定義
 */
#define INDEX_NULL		(~0U)		/* 空きブロックリストの最後 */
#define INDEX_ALLOC		(~1U)		/* 割当て済みのブロック */

/*
 *  固定長メモリプール機能の初期化
 */
#ifdef TOPPERS_mpfini

void
initialize_mempfix(void)
{
	uint_t	i;
	MPFCB	*p_mpfcb;

	for (i = 0; i < tnum_mpf; i++) {
		p_mpfcb = &(mpfcb_table[i]);
		queue_initialize(&(p_mpfcb->wait_queue));
		p_mpfcb->p_mpfinib = &(mpfinib_table[i]);
		p_mpfcb->fblkcnt = p_mpfcb->p_mpfinib->blkcnt;
		p_mpfcb->unused = 0U;
		p_mpfcb->freelist = INDEX_NULL;
	}
}

#endif /* TOPPERS_mpfini */

/*
 *  固定長メモリプールからブロックを獲得
 */
#ifdef TOPPERS_mpfget

void
get_mpf_block(MPFCB *p_mpfcb, void **p_blk)
{
	uint_t	blkidx;

	if (p_mpfcb->freelist != INDEX_NULL) {
		blkidx = p_mpfcb->freelist;
		p_mpfcb->freelist = (p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next;
	}
	else {
		blkidx = p_mpfcb->unused;
		p_mpfcb->unused++;
	}
	*p_blk = (void *)((char *)(p_mpfcb->p_mpfinib->mpf)
								+ p_mpfcb->p_mpfinib->blksz * blkidx);
	p_mpfcb->fblkcnt--;
	(p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next = INDEX_ALLOC;
}

#endif /* TOPPERS_mpfget */

/*
 *  固定長メモリブロックの獲得
 */
#ifdef TOPPERS_get_mpf

ER
get_mpf(ID mpfid, void **p_blk)
{
	MPFCB	*p_mpfcb;
	WINFO_MPF winfo_mpf;
	ER		ercd;

	LOG_GET_MPF_ENTER(mpfid, p_blk);
	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->fblkcnt > 0) {
		get_mpf_block(p_mpfcb, p_blk);
		ercd = E_OK;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_MPF);
		wobj_make_wait((WOBJCB *) p_mpfcb, (WINFO_WOBJ *) &winfo_mpf);
		dispatch();
		ercd = winfo_mpf.winfo.wercd;
		if (ercd == E_OK) {
			*p_blk = winfo_mpf.blk;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_GET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* TOPPERS_get_mpf */

/*
 *  固定長メモリブロックの獲得（ポーリング）
 */
#ifdef TOPPERS_pget_mpf

ER
pget_mpf(ID mpfid, void **p_blk)
{
	MPFCB	*p_mpfcb;
	ER		ercd;

	LOG_PGET_MPF_ENTER(mpfid, p_blk);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->fblkcnt > 0) {
		get_mpf_block(p_mpfcb, p_blk);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

  error_exit:
	LOG_PGET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* TOPPERS_pget_mpf */

/*
 *  固定長メモリブロックの獲得（タイムアウトあり）
 */
#ifdef TOPPERS_tget_mpf

ER
tget_mpf(ID mpfid, void **p_blk, TMO tmout)
{
	MPFCB	*p_mpfcb;
	WINFO_MPF winfo_mpf;
	TMEVTB	tmevtb;
	ER		ercd;

	LOG_TGET_MPF_ENTER(mpfid, p_blk, tmout);
	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	CHECK_TMOUT(tmout);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->fblkcnt > 0) {
		get_mpf_block(p_mpfcb, p_blk);
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_MPF);
		wobj_make_wait_tmout((WOBJCB *) p_mpfcb, (WINFO_WOBJ *) &winfo_mpf,
														&tmevtb, tmout);
		dispatch();
		ercd = winfo_mpf.winfo.wercd;
		if (ercd == E_OK) {
			*p_blk = winfo_mpf.blk;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_TGET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* TOPPERS_tget_mpf */

/*
 *  固定長メモリブロックの返却
 */
#ifdef TOPPERS_rel_mpf

ER
rel_mpf(ID mpfid, void *blk)
{
	MPFCB	*p_mpfcb;
	SIZE	blkoffset;
	uint_t	blkidx;
	TCB		*p_tcb;
	ER		ercd;
    
	LOG_REL_MPF_ENTER(mpfid, blk);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);
	CHECK_PAR(p_mpfcb->p_mpfinib->mpf <= blk);
	blkoffset = ((char *) blk) - (char *)(p_mpfcb->p_mpfinib->mpf);
	CHECK_PAR(blkoffset % p_mpfcb->p_mpfinib->blksz == 0U);
	CHECK_PAR(blkoffset / p_mpfcb->p_mpfinib->blksz < p_mpfcb->unused);
	blkidx = (uint_t)(blkoffset / p_mpfcb->p_mpfinib->blksz);
	CHECK_PAR((p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next == INDEX_ALLOC);

	t_lock_cpu();
	if (!queue_empty(&(p_mpfcb->wait_queue))) {
		p_tcb = (TCB *) queue_delete_next(&(p_mpfcb->wait_queue));
		((WINFO_MPF *)(p_tcb->p_winfo))->blk = blk;
		if (wait_complete(p_tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		p_mpfcb->fblkcnt++;
		(p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next = p_mpfcb->freelist;
		p_mpfcb->freelist = blkidx;
		ercd = E_OK;
	}
	t_unlock_cpu();

  error_exit:
	LOG_REL_MPF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_rel_mpf */

/*
 *  固定長メモリプールの再初期化
 */
#ifdef TOPPERS_ini_mpf

ER
ini_mpf(ID mpfid)
{
	MPFCB	*p_mpfcb;
	bool_t	dspreq;
	ER		ercd;
    
	LOG_INI_MPF_ENTER(mpfid);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	dspreq = init_wait_queue(&(p_mpfcb->wait_queue));
	p_mpfcb->fblkcnt = p_mpfcb->p_mpfinib->blkcnt;
	p_mpfcb->unused = 0U;
	p_mpfcb->freelist = INDEX_NULL;
	if (dspreq) {
		dispatch();
	}
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_INI_MPF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ini_mpf */

/*
 *  固定長メモリプールの状態参照
 */
#ifdef TOPPERS_ref_mpf

ER
ref_mpf(ID mpfid, T_RMPF *pk_rmpf)
{
	MPFCB	*p_mpfcb;
	ER		ercd;
    
	LOG_REF_MPF_ENTER(mpfid, pk_rmpf);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	pk_rmpf->wtskid = wait_tskid(&(p_mpfcb->wait_queue));
	pk_rmpf->fblkcnt = p_mpfcb->fblkcnt;
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_REF_MPF_LEAVE(ercd, pk_rmpf);
	return(ercd);
}

#endif /* TOPPERS_ref_mpf */
