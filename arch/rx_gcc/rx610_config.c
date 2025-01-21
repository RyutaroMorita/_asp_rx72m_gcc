/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by Witz Corporation, JAPAN
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
 *		プロセッサ依存モジュール（RX610用）
 */

#include "kernel_impl.h"


/*
 *  割込み要因プライオリティレジスタアドレステーブル
 */
volatile uint8_t * const ipr_reg_addr[ INHNO_MAX ] = {
	NULL, NULL, NULL, NULL, NULL,	/* No.0 - 4   予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.5 - 9   予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.10 - 14 予約 */
	NULL,							/* No.15  予約 */
	ICU_IPR00_ADDR,					/* No.16  バスエラー BUSERR */
	NULL, NULL, NULL, NULL,			/* No.17 - 20 予約 */
	ICU_IPR01_ADDR,					/* No.21  FCU FIFERR */
	NULL,							/* No.22  予約 */
	ICU_IPR02_ADDR,					/* No.23  FCU FRDYI */
	NULL, NULL, NULL, NULL,			/* No.24 -27  予約 */
	ICU_IPR04_ADDR,					/* No.28  CMTユニット0 CMT0 */
	ICU_IPR05_ADDR,					/* No.29  CMTユニット0 CMT1 */
	ICU_IPR06_ADDR,					/* No.30  CMTユニット1 CMT2 */
	ICU_IPR07_ADDR,					/* No.31  CMTユニット1 CMT3 */
	NULL, NULL, NULL, NULL, NULL,	/* No.32 - 36 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.37 - 41 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.42 - 46 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.47 - 51 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.52 - 56 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.57 - 61 予約 */
	NULL, NULL,						/* No.62 - 63 予約 */
	ICU_IPR20_ADDR,					/* No.64  外部端子 IRQ0 */
	ICU_IPR21_ADDR,					/* No.65  外部端子 IRQ1 */
	ICU_IPR22_ADDR,					/* No.66  外部端子 IRQ2 */
	ICU_IPR23_ADDR,					/* No.67  外部端子 IRQ3 */
	ICU_IPR24_ADDR,					/* No.68  外部端子 IRQ4 */
	ICU_IPR25_ADDR,					/* No.69  外部端子 IRQ5 */
	ICU_IPR26_ADDR,					/* No.70  外部端子 IRQ6 */
	ICU_IPR27_ADDR,					/* No.71  外部端子 IRQ7 */
	ICU_IPR28_ADDR,					/* No.72  外部端子 IRQ8 */
	ICU_IPR29_ADDR,					/* No.73  外部端子 IRQ9 */
	ICU_IPR2A_ADDR,					/* No.74  外部端子 IRQ10 */
	ICU_IPR2B_ADDR,					/* No.75  外部端子 IRQ11 */
	ICU_IPR2C_ADDR,					/* No.76  外部端子 IRQ12 */
	ICU_IPR2D_ADDR,					/* No.77  外部端子 IRQ13 */
	ICU_IPR2E_ADDR,					/* No.78  外部端子 IRQ14 */
	ICU_IPR2F_ADDR,					/* No.79  外部端子 IRQ15 */
	NULL, NULL, NULL, NULL, NULL,	/* No.80 - 84 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.85 - 89 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.90 - 94 予約 */
	NULL,							/* No.95  予約 */
	ICU_IPR40_ADDR,					/* No.96  WDT WOVI */
	NULL,							/* No.97  予約 */
	ICU_IPR44_ADDR,					/* No.98  AD0 ADI0 */
	ICU_IPR45_ADDR,					/* No.99  AD1 ADI1 */
	ICU_IPR46_ADDR,					/* No.100 AD2 ADI2 */
	ICU_IPR47_ADDR,					/* No.101 AD3 ADI3 */
	NULL, NULL,						/* No.102 - 103 予約 */
	ICU_IPR4C_ADDR,					/* No.104 TPU0 TGI0A */
	ICU_IPR4C_ADDR,					/* No.105 TPU0 TGI0B */
	ICU_IPR4C_ADDR,					/* No.106 TPU0 TGI0C */
	ICU_IPR4C_ADDR,					/* No.107 TPU0 TGI0D */
	ICU_IPR4D_ADDR,					/* No.108 TPU0 TCI0V */
	NULL, NULL,						/* No.109 - 110 予約 */
	ICU_IPR4E_ADDR,					/* No.111 TPU1 TGI1A */
	ICU_IPR4E_ADDR,					/* No.112 TPU1 TGI1B */
	NULL, NULL,						/* No.113 - 114 予約 */
	ICU_IPR4F_ADDR,					/* No.115 TPU1 TCI1V */
	ICU_IPR4F_ADDR,					/* No.116 TPU1 TCI1U */
	ICU_IPR50_ADDR,					/* No.117 TPU2 TGI2A */
	ICU_IPR50_ADDR,					/* No.118 TPU2 TGI2B */
	NULL,							/* No.119 予約 */
	ICU_IPR51_ADDR,					/* No.120 TPU2 TCI2V */
	ICU_IPR51_ADDR,					/* No.121 TPU2 TCI2U */
	ICU_IPR52_ADDR,					/* No.122 TPU3 TGI3A */
	ICU_IPR52_ADDR,					/* No.123 TPU3 TGI3B */
	ICU_IPR52_ADDR,					/* No.124 TPU3 TGI3C */
	ICU_IPR52_ADDR,					/* No.125 TPU3 TGI3D */
	ICU_IPR53_ADDR,					/* No.126 TPU3 TCI3V */
	ICU_IPR54_ADDR,					/* No.127 TPU4 TGI4A */
	ICU_IPR54_ADDR,					/* No.128 TPU4 TGI4B */
	NULL, NULL,						/* No.129 - 130 予約 */
	ICU_IPR55_ADDR,					/* No.131 TPU4 TCI4V */
	ICU_IPR55_ADDR,					/* No.132 TPU4 TCI4U */
	ICU_IPR56_ADDR,					/* No.133 TPU5 TGI5A */
	ICU_IPR56_ADDR,					/* No.134 TPU5 TGI5B */
	NULL,							/* No.135 予約 */
	ICU_IPR57_ADDR,					/* No.136 TPU5 TCI5V */
	ICU_IPR57_ADDR,					/* No.137 TPU5 TCI5U */
	ICU_IPR58_ADDR,					/* No.138 TPU6 TGI6A */
	ICU_IPR58_ADDR,					/* No.139 TPU6 TGI6B */
	ICU_IPR58_ADDR,					/* No.140 TPU6 TGI6C */
	ICU_IPR58_ADDR,					/* No.141 TPU6 TGI6D */
	ICU_IPR59_ADDR,					/* No.142 TPU6 TCI6V */
	NULL, NULL,						/* No.143 - 144 予約 */
	ICU_IPR5A_ADDR,					/* No.145 TPU7 TGI7A */
	ICU_IPR5A_ADDR,					/* No.146 TPU7 TGI7B */
	NULL, NULL,						/* No.147 - 148 予約 */
	ICU_IPR5B_ADDR,					/* No.149 TPU7 TCI7V */
	ICU_IPR5B_ADDR,					/* No.150 TPU7 TCI7U */
	ICU_IPR5C_ADDR,					/* No.151 TPU8 TGI8A */
	ICU_IPR5C_ADDR,					/* No.152 TPU8 TGI8B */
	NULL,							/* No.153 予約 */
	ICU_IPR5D_ADDR,					/* No.154 TPU8 TCI8V */
	ICU_IPR5D_ADDR,					/* No.155 TPU8 TCI8U */
	ICU_IPR5E_ADDR,					/* No.156 TPU9 TGI9A */
	ICU_IPR5E_ADDR,					/* No.157 TPU9 TGI9B */
	ICU_IPR5E_ADDR,					/* No.158 TPU9 TGI9C */
	ICU_IPR5E_ADDR,					/* No.159 TPU9 TGI9D */
	ICU_IPR5F_ADDR,					/* No.160 TPU9 TCI9V */
	ICU_IPR60_ADDR,					/* No.161 TPU10 TGI10A */
	ICU_IPR60_ADDR,					/* No.162 TPU10 TGI10B */
	NULL, NULL,						/* No.163 - 164 予約 */
	ICU_IPR61_ADDR,					/* No.165 TPU10 TCI10V */
	ICU_IPR61_ADDR,					/* No.166 TPU10 TCI10U */
	ICU_IPR62_ADDR,					/* No.167 TPU11 TGI11A */
	ICU_IPR62_ADDR,					/* No.168 TPU11 TGI11B */
	NULL,							/* No.169 予約 */
	ICU_IPR63_ADDR,					/* No.170 TPU11 TCI11V */
	ICU_IPR63_ADDR,					/* No.171 TPU11 TCI11U */
	NULL, NULL,						/* No.172 - 173 予約 */
	ICU_IPR68_ADDR,					/* No.174 TMR0 CMIA0 */
	ICU_IPR68_ADDR,					/* No.175 TMR0 CMIB0 */
	ICU_IPR68_ADDR,					/* No.176 TMR0 OVI0 */
	ICU_IPR69_ADDR,					/* No.177 TMR1 CMIA1 */
	ICU_IPR69_ADDR,					/* No.178 TMR1 CMIB1 */
	ICU_IPR69_ADDR,					/* No.179 TMR1 OVI1 */
	ICU_IPR6A_ADDR,					/* No.180 TMR2 CMIA2 */
	ICU_IPR6A_ADDR,					/* No.181 TMR2 CMIB2 */
	ICU_IPR6A_ADDR,					/* No.182 TMR2 OVI2 */
	ICU_IPR6B_ADDR,					/* No.183 TMR3 CMIA3 */
	ICU_IPR6B_ADDR,					/* No.184 TMR3 CMIB3 */
	ICU_IPR6B_ADDR,					/* No.185 TMR3 OVI3 */
	NULL, NULL, NULL, NULL, NULL,	/* No.186 - 190 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.191 - 195 予約 */
	NULL, NULL,						/* No.196 - 197 予約 */
	ICU_IPR70_ADDR,					/* No.198 DMAC DMTEND0 */
	ICU_IPR71_ADDR,					/* No.199 DMAC DMTEND1 */
	ICU_IPR72_ADDR,					/* No.200 DMAC DMTEND2 */
	ICU_IPR73_ADDR,					/* No.201 DMAC DMTEND3 */
	NULL, NULL, NULL, NULL, NULL,	/* No.202 - 206 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.207 - 211 予約 */
	NULL, NULL,						/* No.212 - 213 予約 */
	ICU_IPR80_ADDR,					/* No.214 SCI0 ERI0 */
	ICU_IPR80_ADDR,					/* No.215 SCI0 RXI0 */
	ICU_IPR80_ADDR,					/* No.216 SCI0 TXI0 */
	ICU_IPR80_ADDR,					/* No.217 SCI0 TEI0 */
	ICU_IPR81_ADDR,					/* No.218 SCI1 ERI1 */
	ICU_IPR81_ADDR,					/* No.219 SCI1 RXI1 */
	ICU_IPR81_ADDR,					/* No.220 SCI1 TXI1 */
	ICU_IPR81_ADDR,					/* No.221 SCI1 TEI1 */
	ICU_IPR82_ADDR,					/* No.222 SCI2 ERI2 */
	ICU_IPR82_ADDR,					/* No.223 SCI2 RXI2 */
	ICU_IPR82_ADDR,					/* No.224 SCI2 TXI2 */
	ICU_IPR82_ADDR,					/* No.225 SCI2 TEI2 */
	ICU_IPR83_ADDR,					/* No.226 SCI3 ERI3 */
	ICU_IPR83_ADDR,					/* No.227 SCI3 RXI3 */
	ICU_IPR83_ADDR,					/* No.228 SCI3 TXI3 */
	ICU_IPR83_ADDR,					/* No.229 SCI3 TEI3 */
	ICU_IPR84_ADDR,					/* No.230 SCI4 ERI4 */
	ICU_IPR84_ADDR,					/* No.231 SCI4 RXI4 */
	ICU_IPR84_ADDR,					/* No.232 SCI4 TXI4 */
	ICU_IPR84_ADDR,					/* No.233 SCI4 TEI4 */
	ICU_IPR85_ADDR,					/* No.234 SCI5 ERI5 */
	ICU_IPR85_ADDR,					/* No.235 SCI5 RXI5 */
	ICU_IPR85_ADDR,					/* No.236 SCI5 TXI5 */
	ICU_IPR85_ADDR,					/* No.237 SCI5 TEI5 */
	ICU_IPR86_ADDR,					/* No.238 SCI6 ERI6 */
	ICU_IPR86_ADDR,					/* No.239 SCI6 RXI6 */
	ICU_IPR86_ADDR,					/* No.240 SCI6 TXI6 */
	ICU_IPR86_ADDR,					/* No.241 SCI6 TEI6 */
	NULL, NULL, NULL, NULL,			/* No.242 - 245 予約 */
	ICU_IPR88_ADDR,					/* No.246 RIIC0 ICEEI0 */
	ICU_IPR89_ADDR,					/* No.247 RIIC0 ICRXI0 */
	ICU_IPR8A_ADDR,					/* No.248 RIIC0 ICTXI0 */
	ICU_IPR8B_ADDR,					/* No.249 RIIC0 ICTEI0 */
	ICU_IPR8C_ADDR,					/* No.250 RIIC1 ICEEI1 */
	ICU_IPR8D_ADDR,					/* No.251 RIIC1 ICRXI1 */
	ICU_IPR8E_ADDR,					/* No.252 RIIC1 ICTXI1 */
	ICU_IPR8F_ADDR,					/* No.253 RIIC1 ICTEI1 */
	NULL, NULL,						/* No.254 - 255 予約 */
};


/*
 *  割込み要求許可レジスタアドレステーブル
 */
const IER_INFO ier_reg_addr[ INHNO_MAX ] = {
	{ NULL, INVALID_OFFSET },			/* No.0   予約 */
	{ NULL, INVALID_OFFSET },			/* No.1   予約 */
	{ NULL, INVALID_OFFSET },			/* No.2   予約 */
	{ NULL, INVALID_OFFSET },			/* No.3   予約 */
	{ NULL, INVALID_OFFSET },			/* No.4   予約 */
	{ NULL, INVALID_OFFSET },			/* No.5   予約 */
	{ NULL, INVALID_OFFSET },			/* No.6   予約 */
	{ NULL, INVALID_OFFSET },			/* No.7   予約 */
	{ NULL, INVALID_OFFSET },			/* No.8   予約 */
	{ NULL, INVALID_OFFSET },			/* No.9   予約 */
	{ NULL, INVALID_OFFSET },			/* No.10  予約 */
	{ NULL, INVALID_OFFSET },			/* No.11  予約 */
	{ NULL, INVALID_OFFSET },			/* No.12  予約 */
	{ NULL, INVALID_OFFSET },			/* No.13  予約 */
	{ NULL, INVALID_OFFSET },			/* No.14  予約 */
	{ NULL, INVALID_OFFSET },			/* No.15  予約 */
	{ ICU_IER02_ADDR, ICU_IEN0_BIT },	/* No.16  バスエラー BUSERR */
	{ NULL, INVALID_OFFSET },			/* No.17  予約 */
	{ NULL, INVALID_OFFSET },			/* No.18  予約 */
	{ NULL, INVALID_OFFSET },			/* No.19  予約 */
	{ NULL, INVALID_OFFSET },			/* No.20  予約 */
	{ ICU_IER02_ADDR, ICU_IEN5_BIT },	/* No.21  FCU FIFERR */
	{ NULL, INVALID_OFFSET },			/* No.22  予約 */
	{ ICU_IER02_ADDR, ICU_IEN7_BIT },	/* No.23  FCU FRDYI */
	{ NULL, INVALID_OFFSET },			/* No.24  予約 */
	{ NULL, INVALID_OFFSET },			/* No.25  予約 */
	{ NULL, INVALID_OFFSET },			/* No.26  予約 */
	{ NULL, INVALID_OFFSET },			/* No.27  予約 */
	{ ICU_IER03_ADDR, ICU_IEN4_BIT },	/* No.28  CMTユニット0 CMT0 */
	{ ICU_IER03_ADDR, ICU_IEN5_BIT },	/* No.29  CMTユニット0 CMT1 */
	{ ICU_IER03_ADDR, ICU_IEN6_BIT },	/* No.30  CMTユニット1 CMT2 */
	{ ICU_IER03_ADDR, ICU_IEN7_BIT },	/* No.31  CMTユニット1 CMT3 */
	{ NULL, INVALID_OFFSET },			/* No.32  予約 */
	{ NULL, INVALID_OFFSET },			/* No.33  予約 */
	{ NULL, INVALID_OFFSET },			/* No.34  予約 */
	{ NULL, INVALID_OFFSET },			/* No.35  予約 */
	{ NULL, INVALID_OFFSET },			/* No.36  予約 */
	{ NULL, INVALID_OFFSET },			/* No.37  予約 */
	{ NULL, INVALID_OFFSET },			/* No.38  予約 */
	{ NULL, INVALID_OFFSET },			/* No.39  予約 */
	{ NULL, INVALID_OFFSET },			/* No.40  予約 */
	{ NULL, INVALID_OFFSET },			/* No.41  予約 */
	{ NULL, INVALID_OFFSET },			/* No.42  予約 */
	{ NULL, INVALID_OFFSET },			/* No.43  予約 */
	{ NULL, INVALID_OFFSET },			/* No.44  予約 */
	{ NULL, INVALID_OFFSET },			/* No.45  予約 */
	{ NULL, INVALID_OFFSET },			/* No.46  予約 */
	{ NULL, INVALID_OFFSET },			/* No.47  予約 */
	{ NULL, INVALID_OFFSET },			/* No.48  予約 */
	{ NULL, INVALID_OFFSET },			/* No.49  予約 */
	{ NULL, INVALID_OFFSET },			/* No.50  予約 */
	{ NULL, INVALID_OFFSET },			/* No.51  予約 */
	{ NULL, INVALID_OFFSET },			/* No.52  予約 */
	{ NULL, INVALID_OFFSET },			/* No.53  予約 */
	{ NULL, INVALID_OFFSET },			/* No.54  予約 */
	{ NULL, INVALID_OFFSET },			/* No.55  予約 */
	{ NULL, INVALID_OFFSET },			/* No.56  予約 */
	{ NULL, INVALID_OFFSET },			/* No.57  予約 */
	{ NULL, INVALID_OFFSET },			/* No.58  予約 */
	{ NULL, INVALID_OFFSET },			/* No.59  予約 */
	{ NULL, INVALID_OFFSET },			/* No.60  予約 */
	{ NULL, INVALID_OFFSET },			/* No.61  予約 */
	{ NULL, INVALID_OFFSET },			/* No.62  予約 */
	{ NULL, INVALID_OFFSET },			/* No.63  予約 */
	{ ICU_IER08_ADDR, ICU_IEN0_BIT },	/* No.64  外部端子 IRQ0 */
	{ ICU_IER08_ADDR, ICU_IEN1_BIT },	/* No.65  外部端子 IRQ1 */
	{ ICU_IER08_ADDR, ICU_IEN2_BIT },	/* No.66  外部端子 IRQ2 */
	{ ICU_IER08_ADDR, ICU_IEN3_BIT },	/* No.67  外部端子 IRQ3 */
	{ ICU_IER08_ADDR, ICU_IEN4_BIT },	/* No.68  外部端子 IRQ4 */
	{ ICU_IER08_ADDR, ICU_IEN5_BIT },	/* No.69  外部端子 IRQ5 */
	{ ICU_IER08_ADDR, ICU_IEN6_BIT },	/* No.70  外部端子 IRQ6 */
	{ ICU_IER08_ADDR, ICU_IEN7_BIT },	/* No.71  外部端子 IRQ7 */
	{ ICU_IER09_ADDR, ICU_IEN0_BIT },	/* No.72  外部端子 IRQ8 */
	{ ICU_IER09_ADDR, ICU_IEN1_BIT },	/* No.73  外部端子 IRQ9 */
	{ ICU_IER09_ADDR, ICU_IEN2_BIT },	/* No.74  外部端子 IRQ10 */
	{ ICU_IER09_ADDR, ICU_IEN3_BIT },	/* No.75  外部端子 IRQ11 */
	{ ICU_IER09_ADDR, ICU_IEN4_BIT },	/* No.76  外部端子 IRQ12 */
	{ ICU_IER09_ADDR, ICU_IEN5_BIT },	/* No.77  外部端子 IRQ13 */
	{ ICU_IER09_ADDR, ICU_IEN6_BIT },	/* No.78  外部端子 IRQ14 */
	{ ICU_IER09_ADDR, ICU_IEN7_BIT },	/* No.79  外部端子 IRQ15 */
	{ NULL, INVALID_OFFSET },			/* No.80  予約 */
	{ NULL, INVALID_OFFSET },			/* No.81  予約 */
	{ NULL, INVALID_OFFSET },			/* No.82  予約 */
	{ NULL, INVALID_OFFSET },			/* No.83  予約 */
	{ NULL, INVALID_OFFSET },			/* No.84  予約 */
	{ NULL, INVALID_OFFSET },			/* No.85  予約 */
	{ NULL, INVALID_OFFSET },			/* No.86  予約 */
	{ NULL, INVALID_OFFSET },			/* No.87  予約 */
	{ NULL, INVALID_OFFSET },			/* No.88  予約 */
	{ NULL, INVALID_OFFSET },			/* No.89  予約 */
	{ NULL, INVALID_OFFSET },			/* No.90  予約 */
	{ NULL, INVALID_OFFSET },			/* No.91  予約 */
	{ NULL, INVALID_OFFSET },			/* No.92  予約 */
	{ NULL, INVALID_OFFSET },			/* No.93  予約 */
	{ NULL, INVALID_OFFSET },			/* No.94  予約 */
	{ NULL, INVALID_OFFSET },			/* No.95  予約 */
	{ ICU_IER0C_ADDR, ICU_IEN0_BIT },	/* No.96  WDT WOVI */
	{ NULL, INVALID_OFFSET },			/* No.97  予約 */
	{ ICU_IER0C_ADDR, ICU_IEN2_BIT },	/* No.98  AD0 ADI0 */
	{ ICU_IER0C_ADDR, ICU_IEN3_BIT },	/* No.99  AD1 ADI1 */
	{ ICU_IER0C_ADDR, ICU_IEN4_BIT },	/* No.100 AD2 ADI2 */
	{ ICU_IER0C_ADDR, ICU_IEN5_BIT },	/* No.101 AD3 ADI3 */
	{ NULL, INVALID_OFFSET },			/* No.102 予約 */
	{ NULL, INVALID_OFFSET },			/* No.103 予約 */
	{ ICU_IER0D_ADDR, ICU_IEN0_BIT },	/* No.104 TPU0 TGI0A */
	{ ICU_IER0D_ADDR, ICU_IEN1_BIT },	/* No.105 TPU0 TGI0B */
	{ ICU_IER0D_ADDR, ICU_IEN2_BIT },	/* No.106 TPU0 TGI0C */
	{ ICU_IER0D_ADDR, ICU_IEN3_BIT },	/* No.107 TPU0 TGI0D */
	{ ICU_IER0D_ADDR, ICU_IEN4_BIT },	/* No.108 TPU0 TCI0V */
	{ NULL, INVALID_OFFSET },			/* No.109 予約 */
	{ NULL, INVALID_OFFSET },			/* No.110 予約 */
	{ ICU_IER0D_ADDR, ICU_IEN7_BIT },	/* No.111 TPU1 TGI1A */
	{ ICU_IER0E_ADDR, ICU_IEN0_BIT },	/* No.112 TPU1 TGI1B */
	{ NULL, INVALID_OFFSET },			/* No.113 予約 */
	{ NULL, INVALID_OFFSET },			/* No.114 予約 */
	{ ICU_IER0E_ADDR, ICU_IEN3_BIT },	/* No.115 TPU1 TCI1V */
	{ ICU_IER0E_ADDR, ICU_IEN4_BIT },	/* No.116 TPU1 TCI1U */
	{ ICU_IER0E_ADDR, ICU_IEN5_BIT },	/* No.117 TPU2 TGI2A */
	{ ICU_IER0E_ADDR, ICU_IEN6_BIT },	/* No.118 TPU2 TGI2B */
	{ NULL, INVALID_OFFSET },			/* No.119 予約 */
	{ ICU_IER0F_ADDR, ICU_IEN0_BIT },	/* No.120 TPU2 TCI2V */
	{ ICU_IER0F_ADDR, ICU_IEN1_BIT },	/* No.121 TPU2 TCI2U */
	{ ICU_IER0F_ADDR, ICU_IEN2_BIT },	/* No.122 TPU3 TGI3A */
	{ ICU_IER0F_ADDR, ICU_IEN3_BIT },	/* No.123 TPU3 TGI3B */
	{ ICU_IER0F_ADDR, ICU_IEN4_BIT },	/* No.124 TPU3 TGI3C */
	{ ICU_IER0F_ADDR, ICU_IEN5_BIT },	/* No.125 TPU3 TGI3D */
	{ ICU_IER0F_ADDR, ICU_IEN6_BIT },	/* No.126 TPU3 TCI3V */
	{ ICU_IER0F_ADDR, ICU_IEN7_BIT },	/* No.127 TPU4 TGI4A */
	{ ICU_IER10_ADDR, ICU_IEN0_BIT },	/* No.128 TPU4 TGI4B */
	{ NULL, INVALID_OFFSET },			/* No.129 予約 */
	{ NULL, INVALID_OFFSET },			/* No.130 予約 */
	{ ICU_IER10_ADDR, ICU_IEN3_BIT },	/* No.131 TPU4 TCI4V */
	{ ICU_IER10_ADDR, ICU_IEN4_BIT },	/* No.132 TPU4 TCI4U */
	{ ICU_IER10_ADDR, ICU_IEN5_BIT },	/* No.133 TPU5 TGI5A */
	{ ICU_IER10_ADDR, ICU_IEN6_BIT },	/* No.134 TPU5 TGI5B */
	{ NULL, INVALID_OFFSET },			/* No.135 予約 */
	{ ICU_IER11_ADDR, ICU_IEN0_BIT },	/* No.136 TPU5 TCI5V */
	{ ICU_IER11_ADDR, ICU_IEN1_BIT },	/* No.137 TPU5 TCI5U */
	{ ICU_IER11_ADDR, ICU_IEN2_BIT },	/* No.138 TPU6 TGI6A */
	{ ICU_IER11_ADDR, ICU_IEN3_BIT },	/* No.139 TPU6 TGI6B */
	{ ICU_IER11_ADDR, ICU_IEN4_BIT },	/* No.140 TPU6 TGI6C */
	{ ICU_IER11_ADDR, ICU_IEN5_BIT },	/* No.141 TPU6 TGI6D */
	{ ICU_IER11_ADDR, ICU_IEN6_BIT },	/* No.142 TPU6 TCI6V */
	{ NULL, INVALID_OFFSET },			/* No.143 予約 */
	{ NULL, INVALID_OFFSET },			/* No.144 予約 */
	{ ICU_IER12_ADDR, ICU_IEN1_BIT },	/* No.145 TPU7 TGI7A */
	{ ICU_IER12_ADDR, ICU_IEN2_BIT },	/* No.146 TPU7 TGI7B */
	{ NULL, INVALID_OFFSET },			/* No.147 予約 */
	{ NULL, INVALID_OFFSET },			/* No.148 予約 */
	{ ICU_IER12_ADDR, ICU_IEN5_BIT },	/* No.149 TPU7 TCI7V */
	{ ICU_IER12_ADDR, ICU_IEN6_BIT },	/* No.150 TPU7 TCI7U */
	{ ICU_IER12_ADDR, ICU_IEN7_BIT },	/* No.151 TPU8 TGI8A */
	{ ICU_IER13_ADDR, ICU_IEN0_BIT },	/* No.152 TPU8 TGI8B */
	{ NULL, INVALID_OFFSET },			/* No.153 予約 */
	{ ICU_IER13_ADDR, ICU_IEN2_BIT },	/* No.154 TPU8 TCI8V */
	{ ICU_IER13_ADDR, ICU_IEN3_BIT },	/* No.155 TPU8 TCI8U */
	{ ICU_IER13_ADDR, ICU_IEN4_BIT },	/* No.156 TPU9 TGI9A */
	{ ICU_IER13_ADDR, ICU_IEN5_BIT },	/* No.157 TPU9 TGI9B */
	{ ICU_IER13_ADDR, ICU_IEN6_BIT },	/* No.158 TPU9 TGI9C */
	{ ICU_IER13_ADDR, ICU_IEN7_BIT },	/* No.159 TPU9 TGI9D */
	{ ICU_IER14_ADDR, ICU_IEN0_BIT },	/* No.160 TPU9 TCI9V */
	{ ICU_IER14_ADDR, ICU_IEN1_BIT },	/* No.161 TPU10 TGI10A */
	{ ICU_IER14_ADDR, ICU_IEN2_BIT },	/* No.162 TPU10 TGI10B */
	{ NULL, INVALID_OFFSET },			/* No.163 予約 */
	{ NULL, INVALID_OFFSET },			/* No.164 予約 */
	{ ICU_IER14_ADDR, ICU_IEN5_BIT },	/* No.165 TPU10 TCI10V */
	{ ICU_IER14_ADDR, ICU_IEN6_BIT },	/* No.166 TPU10 TCI10U */
	{ ICU_IER14_ADDR, ICU_IEN7_BIT },	/* No.167 TPU11 TGI11A */
	{ ICU_IER15_ADDR, ICU_IEN0_BIT },	/* No.168 TPU11 TGI11B */
	{ NULL, INVALID_OFFSET },			/* No.169 予約 */
	{ ICU_IER15_ADDR, ICU_IEN2_BIT },	/* No.170 TPU11 TCI11V */
	{ ICU_IER15_ADDR, ICU_IEN3_BIT },	/* No.171 TPU11 TCI11U */
	{ NULL, INVALID_OFFSET },			/* No.172 予約 */
	{ NULL, INVALID_OFFSET },			/* No.173 予約 */
	{ ICU_IER15_ADDR, ICU_IEN6_BIT },	/* No.174 TMR0 CMIA0 */
	{ ICU_IER15_ADDR, ICU_IEN7_BIT },	/* No.175 TMR0 CMIB0 */
	{ ICU_IER16_ADDR, ICU_IEN0_BIT },	/* No.176 TMR0 OVI0 */
	{ ICU_IER16_ADDR, ICU_IEN1_BIT },	/* No.177 TMR1 CMIA1 */
	{ ICU_IER16_ADDR, ICU_IEN2_BIT },	/* No.178 TMR1 CMIB1 */
	{ ICU_IER16_ADDR, ICU_IEN3_BIT },	/* No.179 TMR1 OVI1 */
	{ ICU_IER16_ADDR, ICU_IEN4_BIT },	/* No.180 TMR2 CMIA2 */
	{ ICU_IER16_ADDR, ICU_IEN5_BIT },	/* No.181 TMR2 CMIB2 */
	{ ICU_IER16_ADDR, ICU_IEN6_BIT },	/* No.182 TMR2 OVI2 */
	{ ICU_IER16_ADDR, ICU_IEN7_BIT },	/* No.183 TMR3 CMIA3 */
	{ ICU_IER17_ADDR, ICU_IEN0_BIT },	/* No.184 TMR3 CMIB3 */
	{ ICU_IER17_ADDR, ICU_IEN1_BIT },	/* No.185 TMR3 OVI3 */
	{ NULL, INVALID_OFFSET },			/* No.186 予約 */
	{ NULL, INVALID_OFFSET },			/* No.187 予約 */
	{ NULL, INVALID_OFFSET },			/* No.188 予約 */
	{ NULL, INVALID_OFFSET },			/* No.189 予約 */
	{ NULL, INVALID_OFFSET },			/* No.190 予約 */
	{ NULL, INVALID_OFFSET },			/* No.191 予約 */
	{ NULL, INVALID_OFFSET },			/* No.192 予約 */
	{ NULL, INVALID_OFFSET },			/* No.193 予約 */
	{ NULL, INVALID_OFFSET },			/* No.194 予約 */
	{ NULL, INVALID_OFFSET },			/* No.195 予約 */
	{ NULL, INVALID_OFFSET },			/* No.196 予約 */
	{ NULL, INVALID_OFFSET },			/* No.197 予約 */
	{ ICU_IER18_ADDR, ICU_IEN6_BIT },	/* No.198 DMAC DMTEND0 */
	{ ICU_IER18_ADDR, ICU_IEN7_BIT },	/* No.199 DMAC DMTEND1 */
	{ ICU_IER19_ADDR, ICU_IEN0_BIT },	/* No.200 DMAC DMTEND2 */
	{ ICU_IER19_ADDR, ICU_IEN1_BIT },	/* No.201 DMAC DMTEND3 */
	{ NULL, INVALID_OFFSET },			/* No.202 予約 */
	{ NULL, INVALID_OFFSET },			/* No.203 予約 */
	{ NULL, INVALID_OFFSET },			/* No.204 予約 */
	{ NULL, INVALID_OFFSET },			/* No.205 予約 */
	{ NULL, INVALID_OFFSET },			/* No.206 予約 */
	{ NULL, INVALID_OFFSET },			/* No.207 予約 */
	{ NULL, INVALID_OFFSET },			/* No.208 予約 */
	{ NULL, INVALID_OFFSET },			/* No.209 予約 */
	{ NULL, INVALID_OFFSET },			/* No.210 予約 */
	{ NULL, INVALID_OFFSET },			/* No.211 予約 */
	{ NULL, INVALID_OFFSET },			/* No.212 予約 */
	{ NULL, INVALID_OFFSET },			/* No.213 予約 */
	{ ICU_IER1A_ADDR, ICU_IEN6_BIT },	/* No.214 SCI0 ERI0 */
	{ ICU_IER1A_ADDR, ICU_IEN7_BIT },	/* No.215 SCI0 RXI0 */
	{ ICU_IER1B_ADDR, ICU_IEN0_BIT },	/* No.216 SCI0 TXI0 */
	{ ICU_IER1B_ADDR, ICU_IEN1_BIT },	/* No.217 SCI0 TEI0 */
	{ ICU_IER1B_ADDR, ICU_IEN2_BIT },	/* No.218 SCI1 ERI1 */
	{ ICU_IER1B_ADDR, ICU_IEN3_BIT },	/* No.219 SCI1 RXI1 */
	{ ICU_IER1B_ADDR, ICU_IEN4_BIT },	/* No.220 SCI1 TXI1 */
	{ ICU_IER1B_ADDR, ICU_IEN5_BIT },	/* No.221 SCI1 TEI1 */
	{ ICU_IER1B_ADDR, ICU_IEN6_BIT },	/* No.222 SCI2 ERI2 */
	{ ICU_IER1B_ADDR, ICU_IEN7_BIT },	/* No.223 SCI2 RXI2 */
	{ ICU_IER1C_ADDR, ICU_IEN0_BIT },	/* No.224 SCI2 TXI2 */
	{ ICU_IER1C_ADDR, ICU_IEN1_BIT },	/* No.225 SCI2 TEI2 */
	{ ICU_IER1C_ADDR, ICU_IEN2_BIT },	/* No.226 SCI3 ERI3 */
	{ ICU_IER1C_ADDR, ICU_IEN3_BIT },	/* No.227 SCI3 RXI3 */
	{ ICU_IER1C_ADDR, ICU_IEN4_BIT },	/* No.228 SCI3 TXI3 */
	{ ICU_IER1C_ADDR, ICU_IEN5_BIT },	/* No.229 SCI3 TEI3 */
	{ ICU_IER1C_ADDR, ICU_IEN6_BIT },	/* No.230 SCI4 ERI4 */
	{ ICU_IER1C_ADDR, ICU_IEN7_BIT },	/* No.231 SCI4 RXI4 */
	{ ICU_IER1D_ADDR, ICU_IEN0_BIT },	/* No.232 SCI4 TXI4 */
	{ ICU_IER1D_ADDR, ICU_IEN1_BIT },	/* No.233 SCI4 TEI4 */
	{ ICU_IER1D_ADDR, ICU_IEN2_BIT },	/* No.234 SCI5 ERI5 */
	{ ICU_IER1D_ADDR, ICU_IEN3_BIT },	/* No.235 SCI5 RXI5 */
	{ ICU_IER1D_ADDR, ICU_IEN4_BIT },	/* No.236 SCI5 TXI5 */
	{ ICU_IER1D_ADDR, ICU_IEN5_BIT },	/* No.237 SCI5 TEI5 */
	{ ICU_IER1D_ADDR, ICU_IEN6_BIT },	/* No.238 SCI6 ERI6 */
	{ ICU_IER1D_ADDR, ICU_IEN7_BIT },	/* No.239 SCI6 RXI6 */
	{ ICU_IER1E_ADDR, ICU_IEN0_BIT },	/* No.240 SCI6 TXI6 */
	{ ICU_IER1E_ADDR, ICU_IEN1_BIT },	/* No.241 SCI6 TEI6 */
	{ NULL, INVALID_OFFSET },			/* No.242 予約 */
	{ NULL, INVALID_OFFSET },			/* No.243 予約 */
	{ NULL, INVALID_OFFSET },			/* No.244 予約 */
	{ NULL, INVALID_OFFSET },			/* No.245 予約 */
	{ ICU_IER1E_ADDR, ICU_IEN6_BIT },	/* No.246 RIIC0 ICEEI0 */
	{ ICU_IER1E_ADDR, ICU_IEN7_BIT },	/* No.247 RIIC0 ICRXI0 */
	{ ICU_IER1F_ADDR, ICU_IEN0_BIT },	/* No.248 RIIC0 ICTXI0 */
	{ ICU_IER1F_ADDR, ICU_IEN1_BIT },	/* No.249 RIIC0 ICTEI0 */
	{ ICU_IER1F_ADDR, ICU_IEN2_BIT },	/* No.250 RIIC1 ICEEI1 */
	{ ICU_IER1F_ADDR, ICU_IEN3_BIT },	/* No.251 RIIC1 ICRXI1 */
	{ ICU_IER1F_ADDR, ICU_IEN4_BIT },	/* No.252 RIIC1 ICTXI1 */
	{ ICU_IER1F_ADDR, ICU_IEN5_BIT },	/* No.253 RIIC1 ICTEI1 */
	{ NULL, INVALID_OFFSET },			/* No.254 予約 */
	{ NULL, INVALID_OFFSET },			/* No.255 予約 */
};


/*
 *  割込み要求レジスタアドレステーブル
 */
volatile uint8_t  * const ir_reg_addr[ INHNO_MAX ] = {
	NULL, NULL, NULL, NULL, NULL,	/* No.0 - 4   予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.5 - 9   予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.10 - 14 予約 */
	NULL,							/* No.15  予約 */
	ICU_IR016_ADDR,					/* No.16  バスエラー BUSERR */
	NULL, NULL, NULL, NULL,			/* No.17 - 20 予約 */
	ICU_IR021_ADDR,					/* No.21  FCU FIFERR */
	NULL,							/* No.22  予約 */
	ICU_IR023_ADDR,					/* No.23  FCU FRDYI */
	NULL, NULL, NULL, NULL,			/* No.24 -27  予約 */
	ICU_IR028_ADDR,					/* No.28  CMTユニット0 CMT0 */
	ICU_IR029_ADDR,					/* No.29  CMTユニット0 CMT1 */
	ICU_IR030_ADDR,					/* No.30  CMTユニット1 CMT2 */
	ICU_IR031_ADDR,					/* No.31  CMTユニット1 CMT3 */
	NULL, NULL, NULL, NULL, NULL,	/* No.32 - 36 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.37 - 41 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.42 - 46 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.47 - 51 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.52 - 56 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.57 - 61 予約 */
	NULL, NULL,						/* No.62 - 63 予約 */
	ICU_IR064_ADDR,					/* No.64  外部端子 IRQ0 */
	ICU_IR065_ADDR,					/* No.65  外部端子 IRQ1 */
	ICU_IR066_ADDR,					/* No.66  外部端子 IRQ2 */
	ICU_IR067_ADDR,					/* No.67  外部端子 IRQ3 */
	ICU_IR068_ADDR,					/* No.68  外部端子 IRQ4 */
	ICU_IR069_ADDR,					/* No.69  外部端子 IRQ5 */
	ICU_IR070_ADDR,					/* No.70  外部端子 IRQ6 */
	ICU_IR071_ADDR,					/* No.71  外部端子 IRQ7 */
	ICU_IR072_ADDR,					/* No.72  外部端子 IRQ8 */
	ICU_IR073_ADDR,					/* No.73  外部端子 IRQ9 */
	ICU_IR074_ADDR,					/* No.74  外部端子 IRQ10 */
	ICU_IR075_ADDR,					/* No.75  外部端子 IRQ11 */
	ICU_IR076_ADDR,					/* No.76  外部端子 IRQ12 */
	ICU_IR077_ADDR,					/* No.77  外部端子 IRQ13 */
	ICU_IR078_ADDR,					/* No.78  外部端子 IRQ14 */
	ICU_IR079_ADDR,					/* No.79  外部端子 IRQ15 */
	NULL, NULL, NULL, NULL, NULL,	/* No.80 - 84 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.85 - 89 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.90 - 94 予約 */
	NULL,							/* No.95  予約 */
	ICU_IR096_ADDR,					/* No.96  WDT WOVI */
	NULL,							/* No.97  予約 */
	ICU_IR098_ADDR,					/* No.98  AD0 ADI0 */
	ICU_IR099_ADDR,					/* No.99  AD1 ADI1 */
	ICU_IR100_ADDR,					/* No.100 AD2 ADI2 */
	ICU_IR101_ADDR,					/* No.101 AD3 ADI3 */
	NULL, NULL,						/* No.102 - 103 予約 */
	ICU_IR104_ADDR,					/* No.104 TPU0 TGI0A */
	ICU_IR105_ADDR,					/* No.105 TPU0 TGI0B */
	ICU_IR106_ADDR,					/* No.106 TPU0 TGI0C */
	ICU_IR107_ADDR,					/* No.107 TPU0 TGI0D */
	ICU_IR108_ADDR,					/* No.108 TPU0 TCI0V */
	NULL, NULL,						/* No.109 - 110 予約 */
	ICU_IR111_ADDR,					/* No.111 TPU1 TGI1A */
	ICU_IR112_ADDR,					/* No.112 TPU1 TGI1B */
	NULL, NULL,						/* No.113 - 114 予約 */
	ICU_IR115_ADDR,					/* No.115 TPU1 TCI1V */
	ICU_IR116_ADDR,					/* No.116 TPU1 TCI1U */
	ICU_IR117_ADDR,					/* No.117 TPU2 TGI2A */
	ICU_IR118_ADDR,					/* No.118 TPU2 TGI2B */
	NULL,							/* No.119 予約 */
	ICU_IR120_ADDR,					/* No.120 TPU2 TCI2V */
	ICU_IR121_ADDR,					/* No.121 TPU2 TCI2U */
	ICU_IR122_ADDR,					/* No.122 TPU3 TGI3A */
	ICU_IR123_ADDR,					/* No.123 TPU3 TGI3B */
	ICU_IR124_ADDR,					/* No.124 TPU3 TGI3C */
	ICU_IR125_ADDR,					/* No.125 TPU3 TGI3D */
	ICU_IR126_ADDR,					/* No.126 TPU3 TCI3V */
	ICU_IR127_ADDR,					/* No.127 TPU4 TGI4A */
	ICU_IR128_ADDR,					/* No.128 TPU4 TGI4B */
	NULL, NULL,						/* No.129 - 130 予約 */
	ICU_IR131_ADDR,					/* No.131 TPU4 TCI4V */
	ICU_IR132_ADDR,					/* No.132 TPU4 TCI4U */
	ICU_IR133_ADDR,					/* No.133 TPU5 TGI5A */
	ICU_IR134_ADDR,					/* No.134 TPU5 TGI5B */
	NULL,							/* No.135 予約 */
	ICU_IR136_ADDR,					/* No.136 TPU5 TCI5V */
	ICU_IR137_ADDR,					/* No.137 TPU5 TCI5U */
	ICU_IR138_ADDR,					/* No.138 TPU6 TGI6A */
	ICU_IR139_ADDR,					/* No.139 TPU6 TGI6B */
	ICU_IR140_ADDR,					/* No.140 TPU6 TGI6C */
	ICU_IR141_ADDR,					/* No.141 TPU6 TGI6D */
	ICU_IR142_ADDR,					/* No.142 TPU6 TCI6V */
	NULL, NULL,						/* No.143 - 144 予約 */
	ICU_IR145_ADDR,					/* No.145 TPU7 TGI7A */
	ICU_IR146_ADDR,					/* No.146 TPU7 TGI7B */
	NULL, NULL,						/* No.147 - 148 予約 */
	ICU_IR149_ADDR,					/* No.149 TPU7 TCI7V */
	ICU_IR150_ADDR,					/* No.150 TPU7 TCI7U */
	ICU_IR151_ADDR,					/* No.151 TPU8 TGI8A */
	ICU_IR152_ADDR,					/* No.152 TPU8 TGI8B */
	NULL,							/* No.153 予約 */
	ICU_IR154_ADDR,					/* No.154 TPU8 TCI8V */
	ICU_IR155_ADDR,					/* No.155 TPU8 TCI8U */
	ICU_IR156_ADDR,					/* No.156 TPU9 TGI9A */
	ICU_IR157_ADDR,					/* No.157 TPU9 TGI9B */
	ICU_IR158_ADDR,					/* No.158 TPU9 TGI9C */
	ICU_IR159_ADDR,					/* No.159 TPU9 TGI9D */
	ICU_IR160_ADDR,					/* No.160 TPU9 TCI9V */
	ICU_IR161_ADDR,					/* No.161 TPU10 TGI10A */
	ICU_IR162_ADDR,					/* No.162 TPU10 TGI10B */
	NULL, NULL,						/* No.163 - 164 予約 */
	ICU_IR165_ADDR,					/* No.165 TPU10 TCI10V */
	ICU_IR166_ADDR,					/* No.166 TPU10 TCI10U */
	ICU_IR167_ADDR,					/* No.167 TPU11 TGI11A */
	ICU_IR168_ADDR,					/* No.168 TPU11 TGI11B */
	NULL,							/* No.169 予約 */
	ICU_IR170_ADDR,					/* No.170 TPU11 TCI11V */
	ICU_IR171_ADDR,					/* No.171 TPU11 TCI11U */
	NULL, NULL,						/* No.172 - 173 予約 */
	ICU_IR174_ADDR,					/* No.174 TMR0 CMIA0 */
	ICU_IR175_ADDR,					/* No.175 TMR0 CMIB0 */
	ICU_IR176_ADDR,					/* No.176 TMR0 OVI0 */
	ICU_IR177_ADDR,					/* No.177 TMR1 CMIA1 */
	ICU_IR178_ADDR,					/* No.178 TMR1 CMIB1 */
	ICU_IR179_ADDR,					/* No.179 TMR1 OVI1 */
	ICU_IR180_ADDR,					/* No.180 TMR2 CMIA2 */
	ICU_IR181_ADDR,					/* No.181 TMR2 CMIB2 */
	ICU_IR182_ADDR,					/* No.182 TMR2 OVI2 */
	ICU_IR183_ADDR,					/* No.183 TMR3 CMIA3 */
	ICU_IR184_ADDR,					/* No.184 TMR3 CMIB3 */
	ICU_IR185_ADDR,					/* No.185 TMR3 OVI3 */
	NULL, NULL, NULL, NULL, NULL,	/* No.186 - 190 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.191 - 195 予約 */
	NULL, NULL,						/* No.196 - 197 予約 */
	ICU_IR198_ADDR,					/* No.198 DMAC DMTEND0 */
	ICU_IR199_ADDR,					/* No.199 DMAC DMTEND1 */
	ICU_IR200_ADDR,					/* No.200 DMAC DMTEND2 */
	ICU_IR201_ADDR,					/* No.201 DMAC DMTEND3 */
	NULL, NULL, NULL, NULL, NULL,	/* No.202 - 206 予約 */
	NULL, NULL, NULL, NULL, NULL,	/* No.207 - 211 予約 */
	NULL, NULL,						/* No.212 - 213 予約 */
	ICU_IR214_ADDR,					/* No.214 SCI0 ERI0 */
	ICU_IR215_ADDR,					/* No.215 SCI0 RXI0 */
	ICU_IR216_ADDR,					/* No.216 SCI0 TXI0 */
	ICU_IR217_ADDR,					/* No.217 SCI0 TEI0 */
	ICU_IR218_ADDR,					/* No.218 SCI1 ERI1 */
	ICU_IR219_ADDR,					/* No.219 SCI1 RXI1 */
	ICU_IR220_ADDR,					/* No.220 SCI1 TXI1 */
	ICU_IR221_ADDR,					/* No.221 SCI1 TEI1 */
	ICU_IR222_ADDR,					/* No.222 SCI2 ERI2 */
	ICU_IR223_ADDR,					/* No.223 SCI2 RXI2 */
	ICU_IR224_ADDR,					/* No.224 SCI2 TXI2 */
	ICU_IR225_ADDR,					/* No.225 SCI2 TEI2 */
	ICU_IR226_ADDR,					/* No.226 SCI3 ERI3 */
	ICU_IR227_ADDR,					/* No.227 SCI3 RXI3 */
	ICU_IR228_ADDR,					/* No.228 SCI3 TXI3 */
	ICU_IR229_ADDR,					/* No.229 SCI3 TEI3 */
	ICU_IR230_ADDR,					/* No.230 SCI4 ERI4 */
	ICU_IR231_ADDR,					/* No.231 SCI4 RXI4 */
	ICU_IR232_ADDR,					/* No.232 SCI4 TXI4 */
	ICU_IR233_ADDR,					/* No.233 SCI4 TEI4 */
	ICU_IR234_ADDR,					/* No.234 SCI5 ERI5 */
	ICU_IR235_ADDR,					/* No.235 SCI5 RXI5 */
	ICU_IR236_ADDR,					/* No.236 SCI5 TXI5 */
	ICU_IR237_ADDR,					/* No.237 SCI5 TEI5 */
	ICU_IR238_ADDR,					/* No.238 SCI6 ERI6 */
	ICU_IR239_ADDR,					/* No.239 SCI6 RXI6 */
	ICU_IR240_ADDR,					/* No.240 SCI6 TXI6 */
	ICU_IR241_ADDR,					/* No.241 SCI6 TEI6 */
	NULL, NULL, NULL, NULL,			/* No.242 - 245 予約 */
	ICU_IR246_ADDR,					/* No.246 RIIC0 ICEEI0 */
	ICU_IR247_ADDR,					/* No.247 RIIC0 ICRXI0 */
	ICU_IR248_ADDR,					/* No.248 RIIC0 ICTXI0 */
	ICU_IR249_ADDR,					/* No.249 RIIC0 ICTEI0 */
	ICU_IR250_ADDR,					/* No.250 RIIC1 ICEEI1 */
	ICU_IR251_ADDR,					/* No.251 RIIC1 ICRXI1 */
	ICU_IR252_ADDR,					/* No.252 RIIC1 ICTXI1 */
	ICU_IR253_ADDR,					/* No.253 RIIC1 ICTEI1 */
	NULL, NULL,						/* No.254 - 255 予約 */
};


/*
 *  IRQコントロールレジスタアドレステーブル
 */
volatile uint8_t  * const irqcr_reg_addr[ IRQ_MAX ] = {
	ICU_IRQ0_ADDR,
	ICU_IRQ1_ADDR,
	ICU_IRQ2_ADDR,
	ICU_IRQ3_ADDR,
	ICU_IRQ4_ADDR,
	ICU_IRQ5_ADDR,
	ICU_IRQ6_ADDR,
	ICU_IRQ7_ADDR,
	ICU_IRQ8_ADDR,
	ICU_IRQ9_ADDR,
	ICU_IRQ10_ADDR,
	ICU_IRQ11_ADDR,
	ICU_IRQ12_ADDR,
	ICU_IRQ13_ADDR,
	ICU_IRQ14_ADDR,
	ICU_IRQ15_ADDR,
};

