/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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

#include <string.h>
#include <errno.h>

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "kernel_cfg.h"
#include "target_board.h"

#include "tinet_cfg.h"
#include <tinet_config.h>
#include <tinet_defs.h>

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "main.h"

/*
 *  smc_gen ディレクトリ内の内容に依存するため r_smc_entry.h はインクルードしない.
 */
#include "r_cg_macrodriver.h"
#include "Pin.h"
#include "Config_ICU/Config_ICU.h"
#include "Config_PORT/Config_PORT.h"
#include "Config_RSPI0/Config_RSPI0.h"


extern void r_Config_RSPI0_transmit_interrupt(void);
extern void r_Config_RSPI0_receive_interrupt(void);


#define SPI_PAYLOAD_LENGTH		11
#define SLAVE_ADDR				0x01
uint8_t tx_buf[32];
uint8_t rx_buf[32];
//uint8_t snd_buf[] = {0x01, 0x66, 0x00, 0x00, 0x00, 0x06, 0x01, 0x03, 0x00, 0x00, 0x00, 0x0A};
uint8_t snd_buf[TCP_MSS];
uint8_t rcv_buf[TCP_MSS];
uint8_t SPSR;	// デバッグのためグローバル変数とする

uint8_t TCP_SWBUFT[(TCP_MSS * 4)];
uint8_t TCP_RWBUFT[(TCP_MSS * 4)];


/*
 *  SPI 送信割り込みハンドラ
 */
void rspi_tx_handler(void)
{
	r_Config_RSPI0_transmit_interrupt();
}


/*
 *  SPI 受信割り込みハンドラ
 */
void rspi_rx_handler(void)
{
	r_Config_RSPI0_receive_interrupt();
}


/*
 *  メインタスク
 */
void main_task(intptr_t exinf)
{
	T_IPV4EP src;
	T_IPV4EP dst;
	ER ercd;
	volatile uint8_t dummy;
	int index;
	int i;
	uint8_t msg[80];
	uint8_t count = 0;

	/*
	 *  ペリフェラルの初期化
	 */
	//unlock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

	R_Config_PORT_Create();
	R_Config_ICU_Create();
	R_Config_RSPI0_Create();

	//lock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY);

	/*
	 *  プルアップ抵抗の設定
	 */
    sil_wrb_mem(
    		(void *)(PORTC_PCR_ADDR),
			(uint8_t)(sil_reb_mem((void *)PORTC_PCR_ADDR) | PORT_PCR_B4_BIT)
	);
    sil_wrb_mem(
    		(void *)(PORTC_PCR_ADDR),
			(uint8_t)(sil_reb_mem((void *)PORTC_PCR_ADDR) | PORT_PCR_B5_BIT)
	);
    sil_wrb_mem(
    		(void *)(PORTC_PCR_ADDR),
			(uint8_t)(sil_reb_mem((void *)PORTC_PCR_ADDR) | PORT_PCR_B6_BIT)
	);

	syslog(LOG_NOTICE, "\r\nWPT Demo Program for Hannover Release 0.5.0");
	syslog(LOG_NOTICE, "Copyrigth (C) 2025 by Aeterlink Corp., JAPAN\r\n");

	/*
	 *  PHY(KSZ8081MNX/RNB)のリセット
	 */
	PIN_WRITE(A,6) = 0;
	dly_tsk(10);
	PIN_WRITE(A,6) = 1;

	wup_tsk(ETHER_INPUT_TASK);

	//act_tsk(UDP_TASK);

	src.ipaddr = IPV4_ADDR_LOCAL;
	src.portno = 0xC010;
	dst.ipaddr = MAKE_IPV4_ADDR(192,168,0,1);
	dst.portno = 502;
	ercd = tcp_con_cep(ID_CEP0, &src, &dst, 10000);
	if (ercd != E_OK) {
		syslog(LOG_NOTICE, "ERROR: PLC(192.168.0.1:502) not found!");
	} else {
		syslog(LOG_NOTICE, "Connected to PLC(192.168.0.1:502)...");
	}

	/*
	 *  SPI の初期化
	 */
	ena_int(INTNO_RSPI_TX);
	ena_int(INTNO_RSPI_RX);
	R_Config_RSPI0_Start();

	while (1) {
		/*
		 *  SPI の受信開始
		 */
		R_Config_RSPI0_Send_Receive(tx_buf, SPI_PAYLOAD_LENGTH, rx_buf);
		if (tslp_tsk(2000) == E_TMOUT) {
			SPSR = RSPI0.SPSR.BYTE;
			if (SPSR & 0x1D) {
				// エラーステータスのクリア（次の通信のために必要！）
				dummy = RSPI0.SPSR.BYTE;
				RSPI0.SPSR.BYTE = 0xA0;
			}
			syslog(LOG_NOTICE, "ERROR: Not Received Data from SPI!");
			continue;
		}

		index = 0;
		msg[index] = '>';
		index++;
		msg[index] = '>';
		index++;
		msg[index] = ' ';
		index++;
		for (i = 0; i < SPI_PAYLOAD_LENGTH; i++) {
			msg[index] = '0' + ((rx_buf[i] / 100) % 10);
			index++;
			msg[index] = '0' + ((rx_buf[i] / 10) % 10);
			index++;
			msg[index] = '0' + ((rx_buf[i] / 1) % 10);
			index++;
			if (i < (SPI_PAYLOAD_LENGTH - 1)) {
				msg[index] = ',';
				index++;
			} else {
				msg[index] = 0;
			}
		}

		syslog(LOG_NOTICE, (const char *)msg);

		snd_buf[ 0] = 0x01;					// トランザクション識別子1
		snd_buf[ 1] = count;				// トランザクション識別子2（カウンタ）
		count++;
		snd_buf[ 2] = 0x00;					// プロトコル識別子＝ 0
		snd_buf[ 3] = 0x00;					// プロトコル識別子＝ 0
		snd_buf[ 4] = 0x00;					// フィールド長（上位バイト）＝ 0（なぜなら全てのメッセージは256 以下だから）
		snd_buf[ 5] = 27;					// フィールド長（下位バイト）＝以下に続くバイト列の数

		snd_buf[ 6] = SLAVE_ADDR;			// ユニット識別子（スレーブ・アドレスと言っていたもの）
		snd_buf[ 7] = 16;					// Modbus ファンクションコード(Preset Multiple Registers（16，0x10）)
		snd_buf[ 8] = 0x00;					// 開始アドレス（上位）
		snd_buf[ 9] = 0x00;					// 開始アドレス（下位）
		snd_buf[10] = 0x00;					// レジスタの数（上位）
		snd_buf[11] = 0x0A;					// レジスタの数（下位）
		snd_buf[12] = 0x14;					// バイト数

		/* R40001 */
		snd_buf[13] = 0;					// ネットワークID（上位）
		snd_buf[14] = rx_buf[ 0];			// ネットワークID（下位）
		/* R40002 */
		snd_buf[15] = 0;					// SlaveID（上位）
		snd_buf[16] = rx_buf[ 1];			// SlaveID（下位）
		/* R40003 */
		snd_buf[17] = 0;					// バッテリー電圧（上位）
		snd_buf[18] = rx_buf[ 2];			// バッテリー電圧（下位）
		/* R40004 */
		snd_buf[19] = 0;					// Rect電圧（上位）
		snd_buf[20] = rx_buf[ 3];			// Rect電圧（下位）
		/* R40005 */
		snd_buf[21] = rx_buf[ 4];			// センサーデータ0
		snd_buf[22] = rx_buf[ 5];			// センサーデータ1
		/* R40006 */
		snd_buf[23] = rx_buf[ 6];			// センサーデータ2
		snd_buf[24] = rx_buf[ 7];			// センサーデータ3
		/* R40007 */
		snd_buf[25] = 0;					// 受電状態（上位）
		snd_buf[26] = rx_buf[ 8] >> 4;		// 受電状態（下位）
		/* R40008 */
		snd_buf[27] = 0;					// 再送回数（上位）
		snd_buf[28] = rx_buf[ 8] & 0x0F;	// 再送回数（下位）
		/* R40009 */
		snd_buf[29] = 0;					// 受信RSSI（上位）
		snd_buf[30] = rx_buf[ 9];			// 受信RSSI（下位）
		/* R40010 */
		snd_buf[31] = 0;					// チャンネル（上位）
		snd_buf[32] = rx_buf[10];			// チャンネル（下位）

		/*
		 *  Modbus 通信
		 */
		if (ercd != E_OK)
			continue;

		tcp_snd_dat(ID_CEP0, (void *)snd_buf, 33, TMO_FEVR);
		if (tcp_rcv_dat(ID_CEP0, (void *)rcv_buf, TCP_MSS, 1000) <= 0) {
			syslog(LOG_NOTICE, "ERROR: Not Received Data from PLC!");
			continue;
		}
	}
}


/*
 * UDPテストタスク
 */
#define UDP_MAX_DATA_SIZE	1024
static uint_t		buffer[2][UDP_MAX_DATA_SIZE/sizeof(uint_t)];
void udp_task(intptr_t exinf)
{
	int_t tskno = (int_t) exinf;
	int8_t *buf_snd = (int8_t *)buffer[0];
	int8_t *buf_rcv = (int8_t *)buffer[1];
	T_IPV4EP dst;			// 通信相手ＩＰ情報
	ID id = 0;
	int_t len = 0;
	int i;
	ER er;			// サービスコール戻り値

	dst.ipaddr = MAKE_IPV4_ADDR(192,168,0,1);
	dst.portno = 1001;
	id = ID_UDP0;
	len = UDP_MAX_DATA_SIZE;

	for ( i = 0; i < len; i++ )
		buf_snd[i] = (int8_t)i;

	while (true) {
		// UDP送信
		er = udp_snd_dat(id, &dst, (void *)buf_snd, len, 1000);
		if ( er <= 0 ) {	// エラーの場合
			syslog(LOG_NOTICE, "Error in udp_snd_dat() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
		er = udp_rcv_dat(id, &dst, (void *)buf_rcv, len, 1000);
		if ( er <= 0 ) {	// エラーの場合
			syslog(LOG_NOTICE, "Error in udp_rcv_dat() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
		if ( memcmp(buf_snd, buf_rcv, len) != 0 ) {
			syslog(LOG_NOTICE, "Error in memcmp() - no.:%d err.:%d", tskno, er);
			dly_tsk(1000);
			continue;
		}
	}
}


/*
 *  以下 syscalls のダミー.
 */
int getpid(void)
{
	return 1;
}

int kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	kill(status, -1);
	while (1) {}		/* Make sure we hang here */
}

extern int errno;
caddr_t sbrk(int incr)
{
	errno = ENOMEM;
	return (caddr_t) -1;
}
