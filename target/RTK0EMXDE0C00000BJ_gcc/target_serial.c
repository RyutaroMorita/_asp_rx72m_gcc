/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2004 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2003-2004 by Platform Development Center
 *                                          RICOH COMPANY,LTD. JAPAN
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
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
 */

/*
 *	RX72M UART用シリアルI/Oモジュール
 */
#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "target_board.h"
#include "target_serial.h"
#include "r_sci_rx_if.h"
#include "r_sci_rx_pinset.h"
#include "r_sci_rx_private.h"

ID g_siopid;
//sci_hdl_t g_uart_ctrl[TNUM_SIOP];

/*
 *  シリアルI/Oポート初期化ブロックの定義
 */
typedef struct sio_port_initialization_block {
	sci_hdl_t	hdl;
	uint8_t		chan;
} SIOPINIB;

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
struct sio_port_control_block {
	const SIOPINIB*	p_siopinib; 	/* シリアルI/Oポート初期化ブロック */
	intptr_t		exinf;			/* 拡張情報 */
	bool_t			openflag;		/* オープン済みフラグ */
	bool_t			sendflag;		/* 送信割込みイネーブルフラグ */
	bool_t			getready;		/* 文字を受信した状態 */
	bool_t			putready;		/* 文字を送信できる状態 */
	bool_t			is_initialized; /* デバイス初期化済みフラグ */
};

/*
 *  シリアルI/Oポート管理ブロックのエリア
 */
static SIOPCB	siopcb_table[TNUM_SIOP];

/*  レジスタテーブル */
static SIOPINIB siopinib_table[TNUM_SIOP];

/*
 *  シリアルI/OポートIDから管理ブロックを取り出すためのマクロ
 */
#define INDEX_SIOP(siopid)	 ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	 (&(siopcb_table[INDEX_SIOP(siopid)]))
#define get_siopinib(siopid) (&(siopinib_table[INDEX_SIOP(siopid)]))

/*
 *  SIOのコールバック関数
 */
void sio_callback(void *p_args)
{
	SIOPCB	*p_siopcb = get_siopcb(g_siopid);
	sci_cb_args_t *args;
	args = (sci_cb_args_t *)p_args;
	if (args->event == SCI_EVT_RX_CHAR)
	{
		/*
		 *  受信通知コールバックルーチンを呼び出す．
		 */
		sio_irdy_rcv(p_siopcb->exinf);
	}
	else
	if (args->event == SCI_EVT_TEI)
	{
		/*
		 *  送信可能コールバックルーチンを呼び出す．
		 */
		sio_irdy_snd(p_siopcb->exinf);
	}
}

/*
 *  SIOドライバの初期化
 */
void sio_initialize(intptr_t exinf)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  シリアルI/Oポート管理ブロックの初期化
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++){
		//siopinib_table[i].hdl = &g_uart_ctrl[i];
		siopinib_table[i].chan = (6 + i);	// SCI6を1番目のポートとする
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
		p_siopcb->sendflag = false;
	}
}

/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB* sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;
	sci_cfg_t		cfg;

	/*
	 *  シリアルI/O割込みをマスクする．
	 *  (dis_int関数は、"\kernel\interrupt.c"に記述)
	 */
	dis_int(INTNO_SIO_TX);
	dis_int(INTNO_SIO_RX);
	dis_int(INTNO_SIO_TE);
	
	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;

	/*
	 *  ハードウェアの初期化
	 *
	 *  既に初期化している場合は, 二重に初期化しない.
	 */
	if (!(p_siopcb->is_initialized)) {
		cfg.async.baud_rate = 9600;
		cfg.async.clk_src = SCI_CLK_INT;
		cfg.async.data_size = SCI_DATA_8BIT;
		cfg.async.parity_en = SCI_PARITY_OFF;
		cfg.async.parity_type = SCI_EVEN_PARITY;
		cfg.async.stop_bits = SCI_STOPBITS_1;
		cfg.async.int_priority = 3;

		R_SCI_Open(
				p_siopinib->chan,
				SCI_MODE_ASYNC,
				&cfg,
				sio_callback,
				(sci_hdl_t * const)&p_siopinib->hdl
		);
		// PORTB.PMR.BIT.B1 = 1U; // Please set the PMR bit after TE bit is set to 1.
		R_SCI_PinSet_SCI();

		p_siopcb->is_initialized = true;
	}

	p_siopcb->exinf = exinf;
	p_siopcb->getready = p_siopcb->putready = false;
	p_siopcb->openflag = true;

	/*
	 *  シリアルI/O割込みをマスク解除する．
	 *  (ena_int関数は、"\kernel\interrupt.c"に記述)
	 */
	ena_int(INTNO_SIO_TX);
	ena_int(INTNO_SIO_RX);
	ena_int(INTNO_SIO_TE);

	return(p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void sio_cls_por(SIOPCB *p_siopcb)
{
	/*
	 *  デバイス依存のクローズ処理．
	 */
	R_SCI_Close(p_siopcb->p_siopinib->hdl);

	p_siopcb->openflag = false;
	p_siopcb->is_initialized = false;

	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	dis_int(INTNO_SIO_TX);
	dis_int(INTNO_SIO_RX);
	dis_int(INTNO_SIO_TE);
}

/*
 *  SIOの割込みハンドラ
 */
void sio_tx_isr(intptr_t exinf)
{
	ID siopid = (ID)exinf;
	SIOPCB	*p_siopcb = get_siopcb(siopid);
	g_siopid = siopid;
	txi_handler(p_siopcb->p_siopinib->hdl);
}

/*
 *  SIOの割込みハンドラ
 */
void sio_rx_isr(intptr_t exinf)
{
	ID siopid = (ID)exinf;
	SIOPCB	*p_siopcb = get_siopcb(siopid);
	g_siopid = siopid;
	rxi_handler(p_siopcb->p_siopinib->hdl);
}

/*
 *  SIOの割込みハンドラ
 */
void sio_te_isr(intptr_t exinf)
{
	ID siopid = (ID)exinf;
	SIOPCB	*p_siopcb = get_siopcb(siopid);
	g_siopid = siopid;
	tei_handler(p_siopcb->p_siopinib->hdl);
}


/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t sio_snd_chr(SIOPCB *p_siopcb, char c)
{
	if (R_SCI_Send(p_siopcb->p_siopinib->hdl, (uint8_t*)&c, 1) != SCI_SUCCESS)
		return false;
	return true;
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t sio_rcv_chr(SIOPCB *p_siopcb)
{
	int_t	c;
	R_SCI_Receive(p_siopcb->p_siopinib->hdl, (uint8_t*)&c, 1);
	return c;
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void
sio_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		//*(uint8_t*)SCI_SCR_ADDR |= SCI_SCR_TEIE_BIT;
		*(uint8_t*)SCI_SCR_ADDR |= SCI_SCR_TIE_BIT;
		break;
	case SIO_RDY_RCV:
		*(uint8_t*)SCI_SCR_ADDR |= SCI_SCR_RIE_BIT;
		break;
	}
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void
sio_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		//*(uint8_t*)SCI_SCR_ADDR &= ~SCI_SCR_TEIE_BIT;
		*(uint8_t*)SCI_SCR_ADDR &= ~SCI_SCR_TIE_BIT;
		break;
	case SIO_RDY_RCV:
		*(uint8_t*)SCI_SCR_ADDR &= ~SCI_SCR_RIE_BIT;
		break;
	}
}
