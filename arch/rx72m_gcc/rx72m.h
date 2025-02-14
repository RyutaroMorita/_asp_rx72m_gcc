/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
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
 *  RX72Mに依存する定義
 */
#ifndef TOPPERS_RX72M_H
#define TOPPERS_RX72M_H

#include <sil.h>


/*
 *  CPU例外ハンドラ番号の定義(固定ベクタテーブル)
 *
 *  番号の範囲は0 - 31
 */
#define INT_PRIVILEGED_INSTRUNCTION		20		/* 特権命令例外 */
#define INT_UNDEF_INSTRUNCTION			23		/* 未定義命令例外 */
#define INT_ADDRESS_INSTRUNCTION		24		/* アドレス例外 */
#define INT_FLOATINGPOINT_INSTRUCTION	25		/* 浮動小数点例外 */
#define INT_NMI							30		/* ノンマスカブル割り込み */
#define INT_RESET						31		/* リセット */

/*
 *  割込み番号の定義(可変ベクタテーブル)
 */
#define INT_BSC_BUSERR		16
#define INT_ICU_GROUPIE0	17
#define INT_RAMERR			18
#define INT_FCU_FCUERR		21
#define INT_FCU_FRDYI		23
#define INT_ICU_SWINT2		26
#define INT_ICU_SWINT		27
#define INT_CMT0_CMI0		28
#define INT_CMT1_CMI1		29
#define INT_CMTW0_CMWI0		30
#define INT_CMTW1_CMWI1		31
#define INT_USB0_D0FIFO0	34
#define INT_USB0_D1FIFO0	35
#define INT_RSPI0_SPRI0		38
#define INT_RSPI0_SPTI0		39
#define INT_RSPI1_SPRI1		40
#define INT_RSPI1_SPTI1		41
#define INT_QSPI_SPRI		42
#define INT_QSPI_SPTI		43
#define INT_SDHI_SBFAI		44
#define INT_MMCIF_MBFAI     45
#define INT_SSIE0_SSITXI0	46
#define INT_SSIE0_SSIRXI0	47
#define INT_SSIE1_SSIRTI1	48
#define INT_RIIC1_RXI1		50
#define INT_RIIC1_TXI1		51
#define INT_RIIC0_RXI0		52
#define INT_RIIC0_TXI0		53
#define INT_RIIC2_RXI2		54
#define INT_RIIC2_TXI2		55
#define INT_SCI0_RXI0		58
#define INT_SCI0_TXI0		59
#define INT_SCI1_RXI1		60
#define INT_SCI1_TXI1		61
#define INT_SCI2_RXI2		62
#define INT_SCI2_TXI2		63
#define INT_IRQ0			64
#define INT_IRQ1			65
#define INT_IRQ2			66
#define INT_IRQ3			67
#define INT_IRQ4			68
#define INT_IRQ5			69
#define INT_IRQ6			70
#define INT_IRQ7			71
#define INT_IRQ8			72
#define INT_IRQ9			73
#define INT_IRQ10			74
#define INT_IRQ11			75
#define INT_IRQ12			76
#define INT_IRQ13			77
#define INT_IRQ14			78
#define INT_IRQ15			79
#define INT_SCI3_RXI3		80
#define INT_SCI3_TXI3		81
#define INT_SCI4_RXI4		82
#define INT_SCI4_TXI4		83
#define INT_SCI5_RXI5		84
#define INT_SCI5_TXI5		85
#define INT_SCI6_RXI6		86
#define INT_SCI6_TXI6		87
#define INT_LVD1_LVD1		88
#define INT_LVD2_LVD2		89
#define INT_USB_USBR0		90
#define INT_RTC_ALM			92
#define INT_RTC_PRD			93
#define INT_IWDT_IWUNI		95
#define INT_WDT_WUNI		96
#define INT_PDC_PCDFI		97
#define INT_SCI7_RXI7		98
#define INT_SCI7_TXI7		99
#define INT_SCI8_RXI8		100
#define INT_SCI8_TXI8		101
#define INT_SCI9_RXI9		102
#define INT_SCI9_TXI9		103
#define INT_SCI10_RXI10		104
#define INT_SCI10_TXI10		105
#define INT_ICU_GROUPBE0	106
#define INT_ICU_GROUPBL2	107
#define INT_RSPI2_SPRI2		108
#define INT_RSPI2_SPTI2		109
#define INT_ICU_GROUPBL0	110
#define INT_ICU_GROUPBL1	111
#define INT_ICU_GROUPAL0	112
#define INT_ICU_GROUPAL1	113
#define INT_SCI11_RXI11		114
#define INT_SCI11_TXI11		115
#define INT_SCI12_RXI12		116
#define INT_SCI12_TXI12		117
#define INT_DMAC_DMAC0I		120
#define INT_DMAC_DMAC1I		121
#define INT_DMAC_DMAC2I		122
#define INT_DMAC_DMAC3I		123
#define INT_DMAC_DMAC74I	124
#define INT_OST_OSTDI		125
#define INT_EXDMAC_EXDMAC0I	126
#define INT_EXDMAC_EXDMAC1I	127
#define INT_PERIB_INTB128	128
#define INT_PERIB_INTB129	129
#define INT_PERIB_INTB130	130
#define INT_PERIB_INTB131	131
#define INT_PERIB_INTB132	132
#define INT_PERIB_INTB133	133
#define INT_PERIB_INTB134	134
#define INT_PERIB_INTB135	135
#define INT_PERIB_INTB136	136
#define INT_PERIB_INTB137	137
#define INT_PERIB_INTB138	138
#define INT_PERIB_INTB139	139
#define INT_PERIB_INTB140	140
#define INT_PERIB_INTB141	141
#define INT_PERIB_INTB142	142
#define INT_PERIB_INTB143	143
#define INT_PERIB_INTB144	144
#define INT_PERIB_INTB145	145
#define INT_PERIB_INTB146	146
#define INT_PERIB_INTB147	147
#define INT_PERIB_INTB148	148
#define INT_PERIB_INTB149	149
#define INT_PERIB_INTB150	150
#define INT_PERIB_INTB151	151
#define INT_PERIB_INTB152	152
#define INT_PERIB_INTB153	153
#define INT_PERIB_INTB154	154
#define INT_PERIB_INTB155	155
#define INT_PERIB_INTB156	156
#define INT_PERIB_INTB157	157
#define INT_PERIB_INTB158	158
#define INT_PERIB_INTB159	159
#define INT_PERIB_INTB160	160
#define INT_PERIB_INTB161	161
#define INT_PERIB_INTB162	162
#define INT_PERIB_INTB163	163
#define INT_PERIB_INTB164	164
#define INT_PERIB_INTB165	165
#define INT_PERIB_INTB166	166
#define INT_PERIB_INTB167	167
#define INT_PERIB_INTB168	168
#define INT_PERIB_INTB169	169
#define INT_PERIB_INTB170	170
#define INT_PERIB_INTB171	171
#define INT_PERIB_INTB172	172
#define INT_PERIB_INTB173	173
#define INT_PERIB_INTB174	174
#define INT_PERIB_INTB175	175
#define INT_PERIB_INTB176	176
#define INT_PERIB_INTB177	177
#define INT_PERIB_INTB178	178
#define INT_PERIB_INTB179	179
#define INT_PERIB_INTB180	180
#define INT_PERIB_INTB181	181
#define INT_PERIB_INTB182	182
#define INT_PERIB_INTB183	183
#define INT_PERIB_INTB184	184
#define INT_PERIB_INTB185	185
#define INT_PERIB_INTB186	186
#define INT_PERIB_INTB187	187
#define INT_PERIB_INTB188	188
#define INT_PERIB_INTB189	189
#define INT_PERIB_INTB190	190
#define INT_PERIB_INTB191	191
#define INT_PERIB_INTB192	192
#define INT_PERIB_INTB193	193
#define INT_PERIB_INTB194	194
#define INT_PERIB_INTB195	195
#define INT_PERIB_INTB196	196
#define INT_PERIB_INTB197	197
#define INT_PERIB_INTB198	198
#define INT_PERIB_INTB199	199
#define INT_PERIB_INTB200	200
#define INT_PERIB_INTB201	201
#define INT_PERIB_INTB202	202
#define INT_PERIB_INTB203	203
#define INT_PERIB_INTB204	204
#define INT_PERIB_INTB205	205
#define INT_PERIB_INTB206	206
#define INT_PERIB_INTB207	207
#define INT_PERIB_INTB208	208
#define INT_PERIB_INTB209	209
#define INT_PERIB_INTB210	210
#define INT_PERIB_INTB211	211
#define INT_PERIB_INTB212	212
#define INT_PERIB_INTB213	213
#define INT_PERIB_INTB214	214
#define INT_PERIB_INTB215	215
#define INT_PERIB_INTB216	216
#define INT_PERIB_INTB217	217
#define INT_PERIB_INTB218	218
#define INT_PERIB_INTB219	219
#define INT_PERIB_INTB220	220
#define INT_PERIB_INTB221	221
#define INT_PERIB_INTB222	222
#define INT_PERIB_INTB223	223
#define INT_PERIB_INTB224	224
#define INT_PERIB_INTB225	225
#define INT_PERIB_INTB226	226
#define INT_PERIB_INTB227	227
#define INT_PERIB_INTB228	228
#define INT_PERIB_INTB229	229
#define INT_PERIB_INTB230	230
#define INT_PERIB_INTB231	231
#define INT_PERIB_INTB232	232
#define INT_PERIB_INTB233	233
#define INT_PERIB_INTB234	234
#define INT_PERIB_INTB235	235
#define INT_PERIB_INTB236	236
#define INT_PERIB_INTB237	237
#define INT_PERIB_INTB238	238
#define INT_PERIB_INTB239	239
#define INT_PERIB_INTB240	240
#define INT_PERIB_INTB241	241
#define INT_PERIB_INTB242	242
#define INT_PERIB_INTB243	243
#define INT_PERIB_INTB244	244
#define INT_PERIB_INTB245	245
#define INT_PERIB_INTB246	246
#define INT_PERIB_INTB247	247
#define INT_PERIB_INTB248	248
#define INT_PERIB_INTB249	249
#define INT_PERIB_INTB250	250
#define INT_PERIB_INTB251	251
#define INT_PERIB_INTB252	252
#define INT_PERIB_INTB253	253
#define INT_PERIB_INTB254	254
#define INT_PERIB_INTB255	255


/*
 *  各モジュールのレジスタ及び設定ビット情報
 */

/*
 * Register write protection
 */ 
#define SYSTEM_PRCR_ADDR			(0x000803FE)
#define SYSTEM_PRKEY				0xA500
#define SYSTEM_PRC0					(1UL << 0U)
#define SYSTEM_PRC1					(1UL << 1U)
#define SYSTEM_PRC3					(1UL << 3U)

/*
 * Clock generater 
 */
#define CKG_SCKCR_ADDR				((volatile uint32_t *)0x00080020)
#define CKG_SCKCR_PD_DIV01			(0UL << 0)
#define CKG_SCKCR_PD_DIV02			(1UL << 0)
#define CKG_SCKCR_PD_DIV04			(2UL << 0)
#define CKG_SCKCR_PD_DIV08			(3UL << 0)
#define CKG_SCKCR_PD_DIV16			(4UL << 0)
#define CKG_SCKCR_PD_DIV32			(5UL << 0)
#define CKG_SCKCR_PD_DIV64			(6UL << 0)
#define CKG_SCKCR_PC_DIV01			(0UL << 4)
#define CKG_SCKCR_PC_DIV02			(1UL << 4)
#define CKG_SCKCR_PC_DIV04			(2UL << 4)
#define CKG_SCKCR_PC_DIV08			(3UL << 4)
#define CKG_SCKCR_PC_DIV16			(4UL << 4)
#define CKG_SCKCR_PC_DIV32			(5UL << 4)
#define CKG_SCKCR_PC_DIV64			(6UL << 4)
#define CKG_SCKCR_PB_DIV01			(0UL << 8)
#define CKG_SCKCR_PB_DIV02			(1UL << 8)
#define CKG_SCKCR_PB_DIV04			(2UL << 8)
#define CKG_SCKCR_PB_DIV08			(3UL << 8)
#define CKG_SCKCR_PB_DIV16			(4UL << 8)
#define CKG_SCKCR_PB_DIV32			(5UL << 8)
#define CKG_SCKCR_PB_DIV64			(6UL << 8)
#define CKG_SCKCR_PA_DIV01			(0UL << 12)
#define CKG_SCKCR_PA_DIV02			(1UL << 12)
#define CKG_SCKCR_PA_DIV04			(2UL << 12)
#define CKG_SCKCR_PA_DIV08			(3UL << 12)
#define CKG_SCKCR_PA_DIV16			(4UL << 12)
#define CKG_SCKCR_PA_DIV32			(5UL << 12)
#define CKG_SCKCR_PA_DIV64			(6UL << 12)
#define CKG_SCKCR_BCK_DIV01			(0UL << 16)
#define CKG_SCKCR_BCK_DIV02			(1UL << 16)
#define CKG_SCKCR_BCK_DIV04			(2UL << 16)
#define CKG_SCKCR_BCK_DIV08			(3UL << 16)
#define CKG_SCKCR_BCK_DIV16			(4UL << 16)
#define CKG_SCKCR_BCK_DIV32			(5UL << 16)
#define CKG_SCKCR_BCK_DIV64			(6UL << 16)
#define CKG_SCKCR_PSTOP0			(1UL << 22)
#define CKG_SCKCR_PSTOP1			(1UL << 23)
#define CKG_SCKCR_ICK_DIV01			(0UL << 24)
#define CKG_SCKCR_ICK_DIV02			(1UL << 24)
#define CKG_SCKCR_ICK_DIV04			(2UL << 24)
#define CKG_SCKCR_ICK_DIV08			(3UL << 24)
#define CKG_SCKCR_ICK_DIV16			(4UL << 24)
#define CKG_SCKCR_ICK_DIV32			(5UL << 24)
#define CKG_SCKCR_ICK_DIV64			(6UL << 24)
#define CKG_SCKCR_FCK_DIV01			(0UL << 28)
#define CKG_SCKCR_FCK_DIV02			(1UL << 28)
#define CKG_SCKCR_FCK_DIV04			(2UL << 28)
#define CKG_SCKCR_FCK_DIV08			(3UL << 28)
#define CKG_SCKCR_FCK_DIV16			(4UL << 28)
#define CKG_SCKCR_FCK_DIV32			(5UL << 28)
#define CKG_SCKCR_FCK_DIV64			(6UL << 28)

#define CKG_SCKCR2_ADDR				((volatile uint16_t *)0x00080024)
#define CKG_SCKCR2_UCK_NOT_USE		(1UL << 4)
#define CKG_SCKCR2_UCK_DIV2			(1UL << 4)
#define CKG_SCKCR2_UCK_DIV3			(2UL << 4)
#define CKG_SCKCR2_UCK_DIV4			(3UL << 4)
#define CKG_SCKCR2_UCK_DIV5			(4UL << 4)

//CLock Select register
#define CKG_SCKCR3_ADDR				((volatile uint16_t *)0x00080026)
#define CKG_SCKCR3_LOCO				(0UL << 8)
#define CKG_SCKCR3_HOCO				(1UL << 8)
#define CKG_SCKCR3_MAIN				(2UL << 8)
#define CKG_SCKCR3_SUB				(3UL << 8)
#define CKG_SCKCR3_PLL				(4UL << 8)

//PLL freq setting
#define CKG_PLLCR_ADDR				((volatile uint16_t *)0x00080028)
#define CKG_PLLCR_PLIDIV1			(0UL << 0U)
#define CKG_PLLCR_PLIDIV2			(1UL << 0U)
#define CKG_PLLCR_PLIDIV3			(2UL << 0U)
#define CKG_PLLCR_STC10				(0x13UL << 8U)
#define CKG_PLLCR_STC10_5			(0x14UL << 8U)
#define CKG_PLLCR_STC11				(0x15UL << 8U)
#define CKG_PLLCR_STC11_5			(0x16UL << 8U)
#define CKG_PLLCR_STC12				(0x17UL << 8U)
#define CKG_PLLCR_STC12_5			(0x18UL << 8U)
#define CKG_PLLCR_STC13				(0x19UL << 8U)
#define CKG_PLLCR_STC13_5			(0x1AUL << 8U)
#define CKG_PLLCR_STC14				(0x1BUL << 8U)
#define CKG_PLLCR_STC14_5			(0x1CUL << 8U)
#define CKG_PLLCR_STC15				(0x1DUL << 8U)
#define CKG_PLLCR_STC15_5			(0x1EUL << 8U)
#define CKG_PLLCR_STC16				(0x1FUL << 8U)
#define CKG_PLLCR_STC16_5			(0x20UL << 8U)
#define CKG_PLLCR_STC17				(0x21UL << 8U)
#define CKG_PLLCR_STC17_5			(0x22UL << 8U)
#define CKG_PLLCR_STC18				(0x23UL << 8U)
#define CKG_PLLCR_STC18_5			(0x24UL << 8U)
#define CKG_PLLCR_STC19				(0x25UL << 8U)
#define CKG_PLLCR_STC19_5			(0x26UL << 8U)
#define CKG_PLLCR_STC20				(0x27UL << 8U)
#define CKG_PLLCR_STC20_5			(0x28UL << 8U)
#define CKG_PLLCR_STC21				(0x29UL << 8U)
#define CKG_PLLCR_STC21_5			(0x2AUL << 8U)
#define CKG_PLLCR_STC22				(0x2BUL << 8U)
#define CKG_PLLCR_STC22_5			(0x2CUL << 8U)
#define CKG_PLLCR_STC23				(0x2DUL << 8U)
#define CKG_PLLCR_STC23_5			(0x2EUL << 8U)
#define CKG_PLLCR_STC24				(0x2FUL << 8U)
#define CKG_PLLCR_STC24_5			(0x30UL << 8U)
#define CKG_PLLCR_STC25				(0x31UL << 8U)
#define CKG_PLLCR_STC25_5			(0x32UL << 8U)
#define CKG_PLLCR_STC26				(0x33UL << 8U)
#define CKG_PLLCR_STC26_5			(0x34UL << 8U)
#define CKG_PLLCR_STC27				(0x35UL << 8U)
#define CKG_PLLCR_STC27_5			(0x36UL << 8U)
#define CKG_PLLCR_STC28				(0x37UL << 8U)
#define CKG_PLLCR_STC28_5			(0x38UL << 8U)
#define CKG_PLLCR_STC29				(0x39UL << 8U)
#define CKG_PLLCR_STC29_5			(0x3AUL << 8U)
#define CKG_PLLCR_STC30				(0x3BUL << 8U)

//Clock enable setting
#define CKG_PLLCR2_ADDR				((volatile uint16_t *)0x0008002A)

#define CKG_MOSCCR_ADDR				((volatile uint8_t *)0x00080032)

#define CKG_SOSCCR_ADDR				((volatile uint8_t *)0x00080033)

#define CKG_LOSCCR_ADDR				((volatile uint8_t *)0x00080034)

#define CKG_ILOCOCR_ADDR			((volatile uint8_t *)0x00080035)

#define CKG_HOCOCR_ADDR				((volatile uint8_t *)0x00080036)

#define CKG_CLOCK_ENABLE			(0UL)
#define CKG_COCCK_DISABLE			(1UL)


/*
 * モジュールストップコントロールレジスタA（MSTPCRA）
 */
#define SYSTEM_MSTPCRA_ADDR			((volatile uint32_t *)0x00080010)
#define SYSTEM_MSTPCRA_MSTPA0_BIT	(1UL << 0U)
#define SYSTEM_MSTPCRA_MSTPA1_BIT	(1UL << 1U)
#define SYSTEM_MSTPCRA_MSTPA4_BIT	(1UL << 4U)
#define SYSTEM_MSTPCRA_MSTPA5_BIT	(1UL << 5U)
#define SYSTEM_MSTPCRA_MSTPA7_BIT	(1UL << 7U)
#define SYSTEM_MSTPCRA_MSTPA9_BIT	(1UL << 9U)
#define SYSTEM_MSTPCRA_MSTPA10_BIT	(1UL << 10U)
#define SYSTEM_MSTPCRA_MSTPA11_BIT	(1UL << 11U)
#define SYSTEM_MSTPCRA_MSTPA13_BIT	(1UL << 13U)
#define SYSTEM_MSTPCRA_MSTPA14_BIT	(1UL << 14U)
#define SYSTEM_MSTPCRA_MSTPA15_BIT	(1UL << 15U)
#define SYSTEM_MSTPCRA_MSTPA16_BIT	(1UL << 16U)
#define SYSTEM_MSTPCRA_MSTPA17_BIT	(1UL << 17U)
#define SYSTEM_MSTPCRA_MSTPA19_BIT	(1UL << 19U)
#define SYSTEM_MSTPCRA_MSTPA24_BIT	(1UL << 24U)
#define SYSTEM_MSTPCRA_MSTPA27_BIT	(1UL << 27U)
#define SYSTEM_MSTPCRA_MSTPA28_BIT	(1UL << 28U)
#define SYSTEM_MSTPCRA_MSTPA29_BIT	(1UL << 29U)
#define SYSTEM_MSTPCRA_ACSE_BIT		(1UL << 31U)


/*
 * モジュールストップコントロールレジスタB（MSTPCRB）
 */
#define SYSTEM_MSTPCRB_ADDR			((volatile uint32_t *)0x00080014)
#define SYSTEM_MSTPCRB_MSTPB0_BIT	(1UL << 0U)
#define SYSTEM_MSTPCRB_MSTPB1_BIT	(1UL << 1U)
#define SYSTEM_MSTPCRB_MSTPB2_BIT	(1UL << 2U)
#define SYSTEM_MSTPCRB_MSTPB4_BIT	(1UL << 4U)
#define SYSTEM_MSTPCRB_MSTPB6_BIT	(1UL << 6U)
#define SYSTEM_MSTPCRB_MSTPB8_BIT	(1UL << 8U)
#define SYSTEM_MSTPCRB_MSTPB9_BIT	(1UL << 9U)
#define SYSTEM_MSTPCRB_MSTPB11_BIT	(1UL << 11U)
#define SYSTEM_MSTPCRB_MSTPB13_BIT	(1UL << 13U)
#define SYSTEM_MSTPCRB_MSTPB14_BIT	(1UL << 14U)
#define SYSTEM_MSTPCRB_MSTPB15_BIT	(1UL << 15U)
#define SYSTEM_MSTPCRB_MSTPB16_BIT	(1UL << 16U)
#define SYSTEM_MSTPCRB_MSTPB17_BIT	(1UL << 17U)
#define SYSTEM_MSTPCRB_MSTPB19_BIT	(1UL << 19U)
#define SYSTEM_MSTPCRB_MSTPB20_BIT	(1UL << 20U)
#define SYSTEM_MSTPCRB_MSTPB21_BIT	(1UL << 21U)
#define SYSTEM_MSTPCRB_MSTPB22_BIT	(1UL << 22U)
#define SYSTEM_MSTPCRB_MSTPB23_BIT	(1UL << 23U)
#define SYSTEM_MSTPCRB_MSTPB24_BIT	(1UL << 24U)
#define SYSTEM_MSTPCRB_MSTPB25_BIT	(1UL << 25U)
#define SYSTEM_MSTPCRB_MSTPB26_BIT	(1UL << 26U)
#define SYSTEM_MSTPCRB_MSTPB27_BIT	(1UL << 27U)
#define SYSTEM_MSTPCRB_MSTPB28_BIT	(1UL << 28U)
#define SYSTEM_MSTPCRB_MSTPB29_BIT	(1UL << 29U)
#define SYSTEM_MSTPCRB_MSTPB30_BIT	(1UL << 30U)
#define SYSTEM_MSTPCRB_MSTPB31_BIT	(1UL << 31U)


/*
 * モジュールストップコントロールレジスタC（MSTPCRC）
 */
#define SYSTEM_MSTPCRC_ADDR			((volatile uint32_t *)0x00080018)
#define SYSTEM_MSTPCRC_MSTPC0_BIT	(1UL << 0U)
#define SYSTEM_MSTPCRC_MSTPC2_BIT	(1UL << 2U)
#define SYSTEM_MSTPCRC_MSTPC6_BIT	(1UL << 6U)
#define SYSTEM_MSTPCRC_MSTPC7_BIT	(1UL << 7U)
#define SYSTEM_MSTPCRC_MSTPC17_BIT	(1UL << 17U)
#define SYSTEM_MSTPCRC_MSTPC19_BIT	(1UL << 19U)
#define SYSTEM_MSTPCRC_MSTPC22_BIT	(1UL << 22U)
#define SYSTEM_MSTPCRC_MSTPC23_BIT	(1UL << 23U)
#define SYSTEM_MSTPCRC_MSTPC24_BIT	(1UL << 24U)
#define SYSTEM_MSTPCRC_MSTPC25_BIT	(1UL << 25U)
#define SYSTEM_MSTPCRC_MSTPC26_BIT	(1UL << 26U)
#define SYSTEM_MSTPCRC_MSTPC27_BIT	(1UL << 27U)
#define SYSTEM_MSTPCRC_MSTPC28_BIT	(1UL << 28U)
#define SYSTEM_MSTPCRC_MSTPC29_BIT	(1UL << 29U)


/*
 * モジュールストップコントロールレジスタD（MSTPCRD）
 */
#define SYSTEM_MSTPCRD_ADDR			((volatile uint32_t *)0x0008001C)
#define SYSTEM_MSTPCRD_MSTPD0_BIT	(1UL << 0U)
#define SYSTEM_MSTPCRD_MSTPD1_BIT	(1UL << 1U)
#define SYSTEM_MSTPCRD_MSTPD2_BIT	(1UL << 2U)
#define SYSTEM_MSTPCRD_MSTPD3_BIT	(1UL << 3U)
#define SYSTEM_MSTPCRD_MSTPD4_BIT	(1UL << 4U)
#define SYSTEM_MSTPCRD_MSTPD5_BIT	(1UL << 5U)
#define SYSTEM_MSTPCRD_MSTPD6_BIT	(1UL << 6U)
#define SYSTEM_MSTPCRD_MSTPD7_BIT	(1UL << 7U)
#define SYSTEM_MSTPCRD_MSTPD31_BIT	(1UL << 31U)


/*
 * clock wait control register
 */
#define SYSTEM_MOSCWTR_ADDR			((volatile uint32_t *)0x000800A2)


/*
 * 割り込み要求レジスタ
 */

#define ICU_IR_BASE					0x00087000
#define ICU_IR_BIT					(1U << 0U)


/*
 * 割り込み要求許可レジスタ
 */
#define ICU_IER_BASE				0x00087200


/* 
 * 割り込み要因プライオリティレジスタi(i=00h～FFh)の設定
 */
#define ICU_IPR000_ADDR				((volatile uint8_t *)0x00087300) /* IPR000 */
#define ICU_IPR001_ADDR				((volatile uint8_t *)0x00087301) /* IPR001 */
#define ICU_IPR002_ADDR				((volatile uint8_t *)0x00087302) /* IPR002 */
#define ICU_IPR003_ADDR				((volatile uint8_t *)0x00087303) /* IPR003 */
#define ICU_IPR004_ADDR				((volatile uint8_t *)0x00087304) /* IPR004 */
#define ICU_IPR005_ADDR				((volatile uint8_t *)0x00087305) /* IPR005 */
#define ICU_IPR006_ADDR				((volatile uint8_t *)0x00087306) /* IPR006 */
#define ICU_IPR007_ADDR				((volatile uint8_t *)0x00087307) /* IPR007 */

#define ICU_IPR034_ADDR				((volatile uint8_t *)0x00087322) /* IPR034 */
#define ICU_IPR035_ADDR				((volatile uint8_t *)0x00087323) /* IPR035 */
#define ICU_IPR036_ADDR				((volatile uint8_t *)0x00087324) /* IPR036 */
#define ICU_IPR037_ADDR				((volatile uint8_t *)0x00087325) /* IPR037 */
#define ICU_IPR038_ADDR				((volatile uint8_t *)0x00087326) /* IPR038 */
#define ICU_IPR039_ADDR				((volatile uint8_t *)0x00087327) /* IPR039 */
#define ICU_IPR040_ADDR				((volatile uint8_t *)0x00087328) /* IPR040 */
#define ICU_IPR041_ADDR				((volatile uint8_t *)0x00087329) /* IPR041 */
#define ICU_IPR042_ADDR				((volatile uint8_t *)0x0008732A) /* IPR042 */
#define ICU_IPR043_ADDR				((volatile uint8_t *)0x0008732B) /* IPR043 */
#define ICU_IPR044_ADDR				((volatile uint8_t *)0x0008732C) /* IPR044 */
#define ICU_IPR045_ADDR				((volatile uint8_t *)0x0008732D) /* IPR045 */
#define ICU_IPR046_ADDR				((volatile uint8_t *)0x0008732E) /* IPR046 */
#define ICU_IPR047_ADDR				((volatile uint8_t *)0x0008732F) /* IPR047 */
#define ICU_IPR048_ADDR				((volatile uint8_t *)0x00087330) /* IPR048 */

#define ICU_IPR050_ADDR				((volatile uint8_t *)0x00087332) /* IPR050 */
#define ICU_IPR051_ADDR				((volatile uint8_t *)0x00087333) /* IPR051 */
#define ICU_IPR052_ADDR				((volatile uint8_t *)0x00087334) /* IPR052 */
#define ICU_IPR053_ADDR				((volatile uint8_t *)0x00087335) /* IPR053 */
#define ICU_IPR054_ADDR				((volatile uint8_t *)0x00087336) /* IPR054 */
#define ICU_IPR055_ADDR				((volatile uint8_t *)0x00087337) /* IPR055 */

#define ICU_IPR058_ADDR				((volatile uint8_t *)0x0008733A) /* IPR058 */
#define ICU_IPR059_ADDR				((volatile uint8_t *)0x0008733B) /* IPR059 */
#define ICU_IPR060_ADDR				((volatile uint8_t *)0x0008733C) /* IPR060 */
#define ICU_IPR061_ADDR				((volatile uint8_t *)0x0008733D) /* IPR061 */
#define ICU_IPR062_ADDR				((volatile uint8_t *)0x0008733E) /* IPR062 */
#define ICU_IPR063_ADDR				((volatile uint8_t *)0x0008733F) /* IPR063 */
#define ICU_IPR064_ADDR				((volatile uint8_t *)0x00087340) /* IPR064 */
#define ICU_IPR065_ADDR				((volatile uint8_t *)0x00087341) /* IPR065 */
#define ICU_IPR066_ADDR				((volatile uint8_t *)0x00087342) /* IPR066 */
#define ICU_IPR067_ADDR				((volatile uint8_t *)0x00087343) /* IPR067 */
#define ICU_IPR068_ADDR				((volatile uint8_t *)0x00087344) /* IPR068 */
#define ICU_IPR069_ADDR				((volatile uint8_t *)0x00087345) /* IPR069 */
#define ICU_IPR070_ADDR				((volatile uint8_t *)0x00087346) /* IPR070 */
#define ICU_IPR071_ADDR				((volatile uint8_t *)0x00087347) /* IPR071 */
#define ICU_IPR072_ADDR				((volatile uint8_t *)0x00087348) /* IPR072 */
#define ICU_IPR073_ADDR				((volatile uint8_t *)0x00087349) /* IPR073 */
#define ICU_IPR074_ADDR				((volatile uint8_t *)0x0008734A) /* IPR074 */
#define ICU_IPR075_ADDR				((volatile uint8_t *)0x0008734B) /* IPR075 */
#define ICU_IPR076_ADDR				((volatile uint8_t *)0x0008734C) /* IPR076 */
#define ICU_IPR077_ADDR				((volatile uint8_t *)0x0008734D) /* IPR077 */
#define ICU_IPR078_ADDR				((volatile uint8_t *)0x0008734E) /* IPR078 */
#define ICU_IPR079_ADDR				((volatile uint8_t *)0x0008734F) /* IPR079 */
#define ICU_IPR080_ADDR				((volatile uint8_t *)0x00087350) /* IPR080 */
#define ICU_IPR081_ADDR				((volatile uint8_t *)0x00087351) /* IPR081 */
#define ICU_IPR082_ADDR				((volatile uint8_t *)0x00087352) /* IPR082 */
#define ICU_IPR083_ADDR				((volatile uint8_t *)0x00087353) /* IPR083 */
#define ICU_IPR084_ADDR				((volatile uint8_t *)0x00087354) /* IPR084 */
#define ICU_IPR085_ADDR				((volatile uint8_t *)0x00087355) /* IPR085 */
#define ICU_IPR086_ADDR				((volatile uint8_t *)0x00087356) /* IPR086 */
#define ICU_IPR087_ADDR				((volatile uint8_t *)0x00087357) /* IPR087 */
#define ICU_IPR088_ADDR				((volatile uint8_t *)0x00087358) /* IPR088 */
#define ICU_IPR089_ADDR				((volatile uint8_t *)0x00087359) /* IPR089 */
#define ICU_IPR090_ADDR				((volatile uint8_t *)0x0008735A) /* IPR090 */

#define ICU_IPR092_ADDR				((volatile uint8_t *)0x0008735C) /* IPR092 */
#define ICU_IPR093_ADDR				((volatile uint8_t *)0x0008735D) /* IPR093 */

#define ICU_IPR095_ADDR				((volatile uint8_t *)0x0008735F) /* IPR095 */
#define ICU_IPR096_ADDR				((volatile uint8_t *)0x00087360) /* IPR096 */
#define ICU_IPR097_ADDR				((volatile uint8_t *)0x00087361) /* IPR097 */
#define ICU_IPR098_ADDR				((volatile uint8_t *)0x00087362) /* IPR098 */
#define ICU_IPR099_ADDR				((volatile uint8_t *)0x00087363) /* IPR099 */
#define ICU_IPR100_ADDR				((volatile uint8_t *)0x00087364) /* IPR100 */
#define ICU_IPR101_ADDR				((volatile uint8_t *)0x00087365) /* IPR101 */
#define ICU_IPR102_ADDR				((volatile uint8_t *)0x00087366) /* IPR102 */
#define ICU_IPR103_ADDR				((volatile uint8_t *)0x00087367) /* IPR103 */
#define ICU_IPR104_ADDR				((volatile uint8_t *)0x00087368) /* IPR104 */
#define ICU_IPR105_ADDR				((volatile uint8_t *)0x00087369) /* IPR105 */
#define ICU_IPR106_ADDR				((volatile uint8_t *)0x0008736A) /* IPR106 */
#define ICU_IPR107_ADDR				((volatile uint8_t *)0x0008736B) /* IPR107 */
#define ICU_IPR108_ADDR				((volatile uint8_t *)0x0008736C) /* IPR108 */
#define ICU_IPR109_ADDR				((volatile uint8_t *)0x0008736D) /* IPR109 */
#define ICU_IPR110_ADDR				((volatile uint8_t *)0x0008736E) /* IPR110 */
#define ICU_IPR111_ADDR				((volatile uint8_t *)0x0008736F) /* IPR111 */
#define ICU_IPR112_ADDR				((volatile uint8_t *)0x00087370) /* IPR112 */
#define ICU_IPR113_ADDR				((volatile uint8_t *)0x00087371) /* IPR113 */
#define ICU_IPR114_ADDR				((volatile uint8_t *)0x00087372) /* IPR114 */
#define ICU_IPR115_ADDR				((volatile uint8_t *)0x00087373) /* IPR115 */
#define ICU_IPR116_ADDR				((volatile uint8_t *)0x00087374) /* IPR116 */
#define ICU_IPR117_ADDR				((volatile uint8_t *)0x00087375) /* IPR117 */

#define ICU_IPR120_ADDR				((volatile uint8_t *)0x00087378) /* IPR120 */
#define ICU_IPR121_ADDR				((volatile uint8_t *)0x00087379) /* IPR121 */
#define ICU_IPR122_ADDR				((volatile uint8_t *)0x0008737A) /* IPR122 */
#define ICU_IPR123_ADDR				((volatile uint8_t *)0x0008737B) /* IPR123 */
#define ICU_IPR124_ADDR				((volatile uint8_t *)0x0008737C) /* IPR124 */
#define ICU_IPR125_ADDR				((volatile uint8_t *)0x0008737D) /* IPR125 */
#define ICU_IPR126_ADDR				((volatile uint8_t *)0x0008737E) /* IPR126 */
#define ICU_IPR127_ADDR				((volatile uint8_t *)0x0008737F) /* IPR127 */
#define ICU_IPR128_ADDR				((volatile uint8_t *)0x00087380) /* IPR128 */
#define ICU_IPR129_ADDR				((volatile uint8_t *)0x00087381) /* IPR129 */
#define ICU_IPR130_ADDR				((volatile uint8_t *)0x00087382) /* IPR130 */
#define ICU_IPR131_ADDR				((volatile uint8_t *)0x00087383) /* IPR131 */
#define ICU_IPR132_ADDR				((volatile uint8_t *)0x00087384) /* IPR132 */
#define ICU_IPR133_ADDR				((volatile uint8_t *)0x00087385) /* IPR133 */
#define ICU_IPR134_ADDR				((volatile uint8_t *)0x00087386) /* IPR134 */
#define ICU_IPR135_ADDR				((volatile uint8_t *)0x00087387) /* IPR135 */
#define ICU_IPR136_ADDR				((volatile uint8_t *)0x00087388) /* IPR136 */
#define ICU_IPR137_ADDR				((volatile uint8_t *)0x00087389) /* IPR137 */
#define ICU_IPR138_ADDR				((volatile uint8_t *)0x0008738A) /* IPR138 */
#define ICU_IPR139_ADDR				((volatile uint8_t *)0x0008738B) /* IPR139 */
#define ICU_IPR140_ADDR				((volatile uint8_t *)0x0008738C) /* IPR140 */
#define ICU_IPR141_ADDR				((volatile uint8_t *)0x0008738D) /* IPR141 */
#define ICU_IPR142_ADDR				((volatile uint8_t *)0x0008738E) /* IPR142 */
#define ICU_IPR143_ADDR				((volatile uint8_t *)0x0008738F) /* IPR143 */
#define ICU_IPR144_ADDR				((volatile uint8_t *)0x00087390) /* IPR144 */
#define ICU_IPR145_ADDR				((volatile uint8_t *)0x00087391) /* IPR145 */
#define ICU_IPR146_ADDR				((volatile uint8_t *)0x00087392) /* IPR146 */
#define ICU_IPR147_ADDR				((volatile uint8_t *)0x00087393) /* IPR147 */
#define ICU_IPR148_ADDR				((volatile uint8_t *)0x00087394) /* IPR148 */
#define ICU_IPR149_ADDR				((volatile uint8_t *)0x00087395) /* IPR149 */
#define ICU_IPR150_ADDR				((volatile uint8_t *)0x00087396) /* IPR150 */
#define ICU_IPR151_ADDR				((volatile uint8_t *)0x00087397) /* IPR151 */
#define ICU_IPR152_ADDR				((volatile uint8_t *)0x00087398) /* IPR152 */
#define ICU_IPR153_ADDR				((volatile uint8_t *)0x00087399) /* IPR153 */
#define ICU_IPR154_ADDR				((volatile uint8_t *)0x0008739A) /* IPR154 */
#define ICU_IPR155_ADDR				((volatile uint8_t *)0x0008739B) /* IPR155 */
#define ICU_IPR156_ADDR				((volatile uint8_t *)0x0008739C) /* IPR156 */
#define ICU_IPR157_ADDR				((volatile uint8_t *)0x0008739D) /* IPR157 */
#define ICU_IPR158_ADDR				((volatile uint8_t *)0x0008739E) /* IPR158 */
#define ICU_IPR159_ADDR				((volatile uint8_t *)0x0008739F) /* IPR159 */
#define ICU_IPR160_ADDR				((volatile uint8_t *)0x000873A0) /* IPR160 */
#define ICU_IPR161_ADDR				((volatile uint8_t *)0x000873A1) /* IPR161 */
#define ICU_IPR162_ADDR				((volatile uint8_t *)0x000873A2) /* IPR162 */
#define ICU_IPR163_ADDR				((volatile uint8_t *)0x000873A3) /* IPR163 */
#define ICU_IPR164_ADDR				((volatile uint8_t *)0x000873A4) /* IPR164 */
#define ICU_IPR165_ADDR				((volatile uint8_t *)0x000873A5) /* IPR165 */
#define ICU_IPR166_ADDR				((volatile uint8_t *)0x000873A6) /* IPR166 */
#define ICU_IPR167_ADDR				((volatile uint8_t *)0x000873A7) /* IPR167 */
#define ICU_IPR168_ADDR				((volatile uint8_t *)0x000873A8) /* IPR168 */
#define ICU_IPR169_ADDR				((volatile uint8_t *)0x000873A9) /* IPR169 */
#define ICU_IPR170_ADDR				((volatile uint8_t *)0x000873AA) /* IPR170 */
#define ICU_IPR171_ADDR				((volatile uint8_t *)0x000873AB) /* IPR171 */
#define ICU_IPR172_ADDR				((volatile uint8_t *)0x000873AC) /* IPR172 */
#define ICU_IPR173_ADDR				((volatile uint8_t *)0x000873AD) /* IPR173 */
#define ICU_IPR174_ADDR				((volatile uint8_t *)0x000873AE) /* IPR174 */
#define ICU_IPR175_ADDR				((volatile uint8_t *)0x000873AF) /* IPR175 */
#define ICU_IPR176_ADDR				((volatile uint8_t *)0x000873B0) /* IPR176 */
#define ICU_IPR177_ADDR				((volatile uint8_t *)0x000873B1) /* IPR177 */
#define ICU_IPR178_ADDR				((volatile uint8_t *)0x000873B2) /* IPR178 */
#define ICU_IPR179_ADDR				((volatile uint8_t *)0x000873B3) /* IPR179 */
#define ICU_IPR180_ADDR				((volatile uint8_t *)0x000873B4) /* IPR180 */
#define ICU_IPR181_ADDR				((volatile uint8_t *)0x000873B5) /* IPR181 */
#define ICU_IPR182_ADDR				((volatile uint8_t *)0x000873B6) /* IPR182 */
#define ICU_IPR183_ADDR				((volatile uint8_t *)0x000873B7) /* IPR183 */
#define ICU_IPR184_ADDR				((volatile uint8_t *)0x000873B8) /* IPR184 */
#define ICU_IPR185_ADDR				((volatile uint8_t *)0x000873B9) /* IPR185 */
#define ICU_IPR186_ADDR				((volatile uint8_t *)0x000873BA) /* IPR186 */
#define ICU_IPR187_ADDR				((volatile uint8_t *)0x000873BB) /* IPR187 */
#define ICU_IPR188_ADDR				((volatile uint8_t *)0x000873BC) /* IPR188 */
#define ICU_IPR189_ADDR				((volatile uint8_t *)0x000873BD) /* IPR189 */
#define ICU_IPR190_ADDR				((volatile uint8_t *)0x000873BE) /* IPR190 */
#define ICU_IPR191_ADDR				((volatile uint8_t *)0x000873BF) /* IPR191 */
#define ICU_IPR192_ADDR				((volatile uint8_t *)0x000873C0) /* IPR192 */
#define ICU_IPR193_ADDR				((volatile uint8_t *)0x000873C1) /* IPR193 */
#define ICU_IPR194_ADDR				((volatile uint8_t *)0x000873C2) /* IPR194 */
#define ICU_IPR195_ADDR				((volatile uint8_t *)0x000873C3) /* IPR195 */
#define ICU_IPR196_ADDR				((volatile uint8_t *)0x000873C4) /* IPR196 */
#define ICU_IPR197_ADDR				((volatile uint8_t *)0x000873C5) /* IPR197 */
#define ICU_IPR198_ADDR				((volatile uint8_t *)0x000873C6) /* IPR198 */
#define ICU_IPR199_ADDR				((volatile uint8_t *)0x000873C7) /* IPR199 */
#define ICU_IPR200_ADDR				((volatile uint8_t *)0x000873C8) /* IPR200 */
#define ICU_IPR201_ADDR				((volatile uint8_t *)0x000873C9) /* IPR201 */
#define ICU_IPR202_ADDR				((volatile uint8_t *)0x000873CA) /* IPR202 */
#define ICU_IPR203_ADDR				((volatile uint8_t *)0x000873CB) /* IPR203 */
#define ICU_IPR204_ADDR				((volatile uint8_t *)0x000873CC) /* IPR204 */
#define ICU_IPR205_ADDR				((volatile uint8_t *)0x000873CD) /* IPR205 */
#define ICU_IPR206_ADDR				((volatile uint8_t *)0x000873CE) /* IPR206 */
#define ICU_IPR207_ADDR				((volatile uint8_t *)0x000873CF) /* IPR207 */
#define ICU_IPR208_ADDR				((volatile uint8_t *)0x000873D0) /* IPR208 */
#define ICU_IPR209_ADDR				((volatile uint8_t *)0x000873D1) /* IPR209 */
#define ICU_IPR210_ADDR				((volatile uint8_t *)0x000873D2) /* IPR210 */
#define ICU_IPR211_ADDR				((volatile uint8_t *)0x000873D3) /* IPR211 */
#define ICU_IPR212_ADDR				((volatile uint8_t *)0x000873D4) /* IPR212 */
#define ICU_IPR213_ADDR				((volatile uint8_t *)0x000873D5) /* IPR213 */
#define ICU_IPR214_ADDR				((volatile uint8_t *)0x000873D6) /* IPR214 */
#define ICU_IPR215_ADDR				((volatile uint8_t *)0x000873D7) /* IPR215 */
#define ICU_IPR216_ADDR				((volatile uint8_t *)0x000873D8) /* IPR216 */
#define ICU_IPR217_ADDR				((volatile uint8_t *)0x000873D9) /* IPR217 */
#define ICU_IPR218_ADDR				((volatile uint8_t *)0x000873DA) /* IPR218 */
#define ICU_IPR219_ADDR				((volatile uint8_t *)0x000873DB) /* IPR219 */
#define ICU_IPR220_ADDR				((volatile uint8_t *)0x000873DC) /* IPR220 */
#define ICU_IPR221_ADDR				((volatile uint8_t *)0x000873DD) /* IPR221 */
#define ICU_IPR222_ADDR				((volatile uint8_t *)0x000873DE) /* IPR222 */
#define ICU_IPR223_ADDR				((volatile uint8_t *)0x000873DF) /* IPR223 */
#define ICU_IPR224_ADDR				((volatile uint8_t *)0x000873E0) /* IPR224 */
#define ICU_IPR225_ADDR				((volatile uint8_t *)0x000873E1) /* IPR225 */
#define ICU_IPR226_ADDR				((volatile uint8_t *)0x000873E2) /* IPR226 */
#define ICU_IPR227_ADDR				((volatile uint8_t *)0x000873E3) /* IPR227 */
#define ICU_IPR228_ADDR				((volatile uint8_t *)0x000873E4) /* IPR228 */
#define ICU_IPR229_ADDR				((volatile uint8_t *)0x000873E5) /* IPR229 */
#define ICU_IPR230_ADDR				((volatile uint8_t *)0x000873E6) /* IPR230 */
#define ICU_IPR231_ADDR				((volatile uint8_t *)0x000873E7) /* IPR231 */
#define ICU_IPR232_ADDR				((volatile uint8_t *)0x000873E8) /* IPR232 */
#define ICU_IPR233_ADDR				((volatile uint8_t *)0x000873E9) /* IPR233 */
#define ICU_IPR234_ADDR				((volatile uint8_t *)0x000873EA) /* IPR234 */
#define ICU_IPR235_ADDR				((volatile uint8_t *)0x000873EB) /* IPR235 */
#define ICU_IPR236_ADDR				((volatile uint8_t *)0x000873EC) /* IPR236 */
#define ICU_IPR237_ADDR				((volatile uint8_t *)0x000873ED) /* IPR237 */
#define ICU_IPR238_ADDR				((volatile uint8_t *)0x000873EE) /* IPR238 */
#define ICU_IPR239_ADDR				((volatile uint8_t *)0x000873EF) /* IPR239 */
#define ICU_IPR240_ADDR				((volatile uint8_t *)0x000873F0) /* IPR240 */
#define ICU_IPR241_ADDR				((volatile uint8_t *)0x000873F1) /* IPR241 */
#define ICU_IPR242_ADDR				((volatile uint8_t *)0x000873F2) /* IPR242 */
#define ICU_IPR243_ADDR				((volatile uint8_t *)0x000873F3) /* IPR243 */
#define ICU_IPR244_ADDR				((volatile uint8_t *)0x000873F4) /* IPR244 */
#define ICU_IPR245_ADDR				((volatile uint8_t *)0x000873F5) /* IPR245 */
#define ICU_IPR246_ADDR				((volatile uint8_t *)0x000873F6) /* IPR246 */
#define ICU_IPR247_ADDR				((volatile uint8_t *)0x000873F7) /* IPR247 */
#define ICU_IPR248_ADDR				((volatile uint8_t *)0x000873F8) /* IPR248 */
#define ICU_IPR249_ADDR				((volatile uint8_t *)0x000873F9) /* IPR249 */
#define ICU_IPR250_ADDR				((volatile uint8_t *)0x000873FA) /* IPR250 */
#define ICU_IPR251_ADDR				((volatile uint8_t *)0x000873FB) /* IPR251 */
#define ICU_IPR252_ADDR				((volatile uint8_t *)0x000873FC) /* IPR252 */
#define ICU_IPR253_ADDR				((volatile uint8_t *)0x000873FD) /* IPR253 */
#define ICU_IPR254_ADDR				((volatile uint8_t *)0x000873FE) /* IPR254 */
#define ICU_IPR255_ADDR				((volatile uint8_t *)0x000873FF) /* IPR255 */
#define ICU_IPR_BIT					(0x0FU << 0U
#define SET_ICU_IPR(intno, pri_num)	((*((volatile uint8_t *)(ICU_IPR_BASE | intno))) = pri_num)


/*
 * グループBL0/BL1/BL2 割り込み要求許可レジスタ
 */
#define ICU_GENBL0_ADDR				((volatile uint32_t *)0x00087670)
#define ICU_GENBL0_EN00_BIT			(1UL <<  0U)
#define ICU_GENBL0_EN01_BIT			(1UL <<  1U)
#define ICU_GENBL0_EN02_BIT			(1UL <<  2U)
#define ICU_GENBL0_EN03_BIT			(1UL <<  3U)
#define ICU_GENBL0_EN04_BIT			(1UL <<  4U)
#define ICU_GENBL0_EN05_BIT			(1UL <<  5U)
#define ICU_GENBL0_EN06_BIT			(1UL <<  6U)
#define ICU_GENBL0_EN07_BIT			(1UL <<  7U)
#define ICU_GENBL0_EN08_BIT			(1UL <<  8U)
#define ICU_GENBL0_EN09_BIT			(1UL <<  9U)
#define ICU_GENBL0_EN10_BIT			(1UL << 10U)
#define ICU_GENBL0_EN11_BIT			(1UL << 11U)
#define ICU_GENBL0_EN12_BIT			(1UL << 12U)
#define ICU_GENBL0_EN13_BIT			(1UL << 13U)
#define ICU_GENBL0_EN14_BIT			(1UL << 14U)
#define ICU_GENBL0_EN15_BIT			(1UL << 15U)
#define ICU_GENBL0_EN16_BIT			(1UL << 16U)
#define ICU_GENBL0_EN17_BIT			(1UL << 17U)
#define ICU_GENBL0_EN18_BIT			(1UL << 18U)
#define ICU_GENBL0_EN19_BIT			(1UL << 19U)
#define ICU_GENBL0_EN20_BIT			(1UL << 20U)
#define ICU_GENBL0_EN21_BIT			(1UL << 21U)
#define ICU_GENBL0_EN22_BIT			(1UL << 22U)
#define ICU_GENBL0_EN23_BIT			(1UL << 23U)
#define ICU_GENBL0_EN24_BIT			(1UL << 24U)
#define ICU_GENBL0_EN25_BIT			(1UL << 25U)
#define ICU_GENBL0_EN26_BIT			(1UL << 26U)
#define ICU_GENBL0_EN27_BIT			(1UL << 27U)
#define ICU_GENBL0_EN28_BIT			(1UL << 28U)
#define ICU_GENBL0_EN29_BIT			(1UL << 29U)
#define ICU_GENBL0_EN30_BIT			(1UL << 30U)
#define ICU_GENBL0_EN31_BIT			(1UL << 31U)


/*
 * グループAL0/AL1 割り込み要求許可レジスタ
 */
#define ICU_GENAL0_ADDR				((volatile uint32_t *)0x00087870)
#define ICU_GENAL0_EN00_BIT			(1UL <<  0U)
#define ICU_GENAL0_EN01_BIT			(1UL <<  1U)
#define ICU_GENAL0_EN02_BIT			(1UL <<  2U)
#define ICU_GENAL0_EN03_BIT			(1UL <<  3U)
#define ICU_GENAL0_EN04_BIT			(1UL <<  4U)
#define ICU_GENAL0_EN05_BIT			(1UL <<  5U)
#define ICU_GENAL0_EN06_BIT			(1UL <<  6U)
#define ICU_GENAL0_EN07_BIT			(1UL <<  7U)
#define ICU_GENAL0_EN08_BIT			(1UL <<  8U)
#define ICU_GENAL0_EN09_BIT			(1UL <<  9U)
#define ICU_GENAL0_EN10_BIT			(1UL << 10U)
#define ICU_GENAL0_EN11_BIT			(1UL << 11U)
#define ICU_GENAL0_EN12_BIT			(1UL << 12U)
#define ICU_GENAL0_EN13_BIT			(1UL << 13U)
#define ICU_GENAL0_EN14_BIT			(1UL << 14U)
#define ICU_GENAL0_EN15_BIT			(1UL << 15U)
#define ICU_GENAL0_EN16_BIT			(1UL << 16U)
#define ICU_GENAL0_EN17_BIT			(1UL << 17U)
#define ICU_GENAL0_EN18_BIT			(1UL << 18U)
#define ICU_GENAL0_EN19_BIT			(1UL << 19U)
#define ICU_GENAL0_EN20_BIT			(1UL << 20U)
#define ICU_GENAL0_EN21_BIT			(1UL << 21U)
#define ICU_GENAL0_EN22_BIT			(1UL << 22U)
#define ICU_GENAL0_EN23_BIT			(1UL << 23U)
#define ICU_GENAL0_EN24_BIT			(1UL << 24U)
#define ICU_GENAL0_EN25_BIT			(1UL << 25U)
#define ICU_GENAL0_EN26_BIT			(1UL << 26U)
#define ICU_GENAL0_EN27_BIT			(1UL << 27U)
#define ICU_GENAL0_EN28_BIT			(1UL << 28U)
#define ICU_GENAL0_EN29_BIT			(1UL << 29U)
#define ICU_GENAL0_EN30_BIT			(1UL << 30U)
#define ICU_GENAL0_EN31_BIT			(1UL << 31U)

#define ICU_GENAL1_ADDR				((volatile uint32_t *)0x00087874)
#define ICU_GENAL1_EN00_BIT			(1UL <<  0U)
#define ICU_GENAL1_EN01_BIT			(1UL <<  1U)
#define ICU_GENAL1_EN02_BIT			(1UL <<  2U)
#define ICU_GENAL1_EN03_BIT			(1UL <<  3U)
#define ICU_GENAL1_EN04_BIT			(1UL <<  4U)
#define ICU_GENAL1_EN05_BIT			(1UL <<  5U)
#define ICU_GENAL1_EN06_BIT			(1UL <<  6U)
#define ICU_GENAL1_EN07_BIT			(1UL <<  7U)
#define ICU_GENAL1_EN08_BIT			(1UL <<  8U)
#define ICU_GENAL1_EN09_BIT			(1UL <<  9U)
#define ICU_GENAL1_EN10_BIT			(1UL << 10U)
#define ICU_GENAL1_EN11_BIT			(1UL << 11U)
#define ICU_GENAL1_EN12_BIT			(1UL << 12U)
#define ICU_GENAL1_EN13_BIT			(1UL << 13U)
#define ICU_GENAL1_EN14_BIT			(1UL << 14U)
#define ICU_GENAL1_EN15_BIT			(1UL << 15U)
#define ICU_GENAL1_EN16_BIT			(1UL << 16U)
#define ICU_GENAL1_EN17_BIT			(1UL << 17U)
#define ICU_GENAL1_EN18_BIT			(1UL << 18U)
#define ICU_GENAL1_EN19_BIT			(1UL << 19U)
#define ICU_GENAL1_EN20_BIT			(1UL << 20U)
#define ICU_GENAL1_EN21_BIT			(1UL << 21U)
#define ICU_GENAL1_EN22_BIT			(1UL << 22U)
#define ICU_GENAL1_EN23_BIT			(1UL << 23U)
#define ICU_GENAL1_EN24_BIT			(1UL << 24U)
#define ICU_GENAL1_EN25_BIT			(1UL << 25U)
#define ICU_GENAL1_EN26_BIT			(1UL << 26U)
#define ICU_GENAL1_EN27_BIT			(1UL << 27U)
#define ICU_GENAL1_EN28_BIT			(1UL << 28U)
#define ICU_GENAL1_EN29_BIT			(1UL << 29U)
#define ICU_GENAL1_EN30_BIT			(1UL << 30U)
#define ICU_GENAL1_EN31_BIT			(1UL << 31U)


/*
 * DTCER Register
 */
#define ICU_DTCER_BASE				0x00087100
#define EN_ICU_DTCER_BI				0x1
#define DIS_ICU_DTCER_BIT			0x0

#ifndef TOPPERS_MACRO_ONLY
#define ENABLE_ICU_DTCER(intno)		(*((volatile uint8_t *)(ICU_DTCER_BASE + intno)) = EN_ICU_DTCER_BIT)

#define DISABLE_ICU_DTCER(intno)	(*((volatile uint8_t *)(ICU_DTCER_BASE + intno)) = DIS_ICU_DTCER_BIT)
#endif

#define ICU_IRQCR_BASE				0x00087500
#define SET_ICU_IRQCR(intno, sel_edge)	\
									(*((volatile uint8_t *)(ICU_IRQCR_BASE | intno)) = sel_edge)


/*
 * DTCa address define
 */
#define DTCA_BASE_ADDR				0x00082400


/*
 *  各チャンネルのレジスタ及び設定ビット情報
 */
#define CMT_CMSTR0_ADDR				((volatile uint16_t *)0x00088000)
#define CMT_CMSTR0_STR0_BIT			(1U << 0U)
#define CMT_CMSTR0_STR1_BIT			(1U << 1U)
#define CMT_CMSTR1_ADDR				((volatile uint16_t *)0x00088010)
#define CMT_CMSTR1_STR2_BIT			(1U << 0U)
#define CMT_CMSTR1_STR3_BIT			(1U << 1U)
#define CMT0_CMCR_ADDR				((volatile uint16_t *)0x00088002)
#define CMT0_CMCR_CKS_BIT			(3U)
#define CMT0_CMCR_CMIE_BIT			(1U << 6U)
#define CMT1_CMCR_ADDR				((volatile uint16_t *)0x00088008)
#define CMT1_CMCR_CKS_BIT			(3U)
#define CMT1_CMCR_CMIE_BIT			(1U << 6U)
#define CMT2_CMCR_ADDR				((volatile uint16_t *)0x00088012)
#define CMT2_CMCR_CKS_BIT			(3U)
#define CMT2_CMCR_CMIE_BIT			(1U << 6U)
#define CMT3_CMCR_ADDR				((volatile uint16_t *)0x00088018)
#define CMT3_CMCR_CKS_BIT			(3U)
#define CMT3_CMCR_CMIE_BIT			(1U << 6U)
#define CMT0_CMCNT_ADDR				((volatile uint16_t *)0x00088004)
#define CMT1_CMCNT_ADDR				((volatile uint16_t *)0x0008800A)
#define CMT2_CMCNT_ADDR				((volatile uint16_t *)0x00088014)
#define CMT3_CMCNT_ADDR				((volatile uint16_t *)0x0008801A)
#define CMT0_CMCOR_ADDR				((volatile uint16_t *)0x00088006)
#define CMT1_CMCOR_ADDR				((volatile uint16_t *)0x0008800C)
#define CMT2_CMCOR_ADDR				((volatile uint16_t *)0x00088016)
#define CMT3_CMCOR_ADDR				((volatile uint16_t *)0x0008801C)

#define SCI0_SMR_ADDR				((volatile uint8_t *)0x0008A000)
#define SCI0_BRR_ADDR				((volatile uint8_t *)0x0008A001)
#define SCI0_SCR_ADDR				((volatile uint8_t *)0x0008A002)
#define SCI0_TDR_ADDR				((volatile uint8_t *)0x0008A003)
#define SCI0_SSR_ADDR				((volatile uint8_t *)0x0008A004)
#define SCI0_RDR_ADDR				((volatile uint8_t *)0x0008A005)
#define SCI0_SCMR_ADDR				((volatile uint8_t *)0x0008A006)
#define SCI0_SEMR_ADDR				((volatile uint8_t *)0x0008A007)
#define SCI1_SMR_ADDR				((volatile uint8_t *)0x0008A020)
#define SCI1_BRR_ADDR				((volatile uint8_t *)0x0008A021)
#define SCI1_SCR_ADDR				((volatile uint8_t *)0x0008A022)
#define SCI1_TDR_ADDR				((volatile uint8_t *)0x0008A023)
#define SCI1_SSR_ADDR				((volatile uint8_t *)0x0008A024)
#define SCI1_RDR_ADDR				((volatile uint8_t *)0x0008A025)
#define SCI1_SCMR_ADDR				((volatile uint8_t *)0x0008A026)
#define SCI1_SEMR_ADDR				((volatile uint8_t *)0x0008A027)
#define SCI2_SMR_ADDR				((volatile uint8_t *)0x0008A040)
#define SCI2_BRR_ADDR				((volatile uint8_t *)0x0008A041)
#define SCI2_SCR_ADDR				((volatile uint8_t *)0x0008A042)
#define SCI2_TDR_ADDR				((volatile uint8_t *)0x0008A043)
#define SCI2_SSR_ADDR				((volatile uint8_t *)0x0008A044)
#define SCI2_RDR_ADDR				((volatile uint8_t *)0x0008A045)
#define SCI2_SCMR_ADDR				((volatile uint8_t *)0x0008A046)
#define SCI2_SEMR_ADDR				((volatile uint8_t *)0x0008A047)
#define SCI3_SMR_ADDR				((volatile uint8_t *)0x0008A060)
#define SCI3_BRR_ADDR				((volatile uint8_t *)0x0008A061)
#define SCI3_SCR_ADDR				((volatile uint8_t *)0x0008A062)
#define SCI3_TDR_ADDR				((volatile uint8_t *)0x0008A063)
#define SCI3_SSR_ADDR				((volatile uint8_t *)0x0008A064)
#define SCI3_RDR_ADDR				((volatile uint8_t *)0x0008A065)
#define SCI3_SCMR_ADDR				((volatile uint8_t *)0x0008A066)
#define SCI3_SEMR_ADDR				((volatile uint8_t *)0x0008A067)
#define SCI4_SMR_ADDR				((volatile uint8_t *)0x0008A080)
#define SCI4_BRR_ADDR				((volatile uint8_t *)0x0008A081)
#define SCI4_SCR_ADDR				((volatile uint8_t *)0x0008A082)
#define SCI4_TDR_ADDR				((volatile uint8_t *)0x0008A083)
#define SCI4_SSR_ADDR				((volatile uint8_t *)0x0008A084)
#define SCI4_RDR_ADDR				((volatile uint8_t *)0x0008A085)
#define SCI4_SCMR_ADDR				((volatile uint8_t *)0x0008A086)
#define SCI4_SEMR_ADDR				((volatile uint8_t *)0x0008A087)
#define SCI5_SMR_ADDR				((volatile uint8_t *)0x0008A0A0)
#define SCI5_BRR_ADDR				((volatile uint8_t *)0x0008A0A1)
#define SCI5_SCR_ADDR				((volatile uint8_t *)0x0008A0A2)
#define SCI5_TDR_ADDR				((volatile uint8_t *)0x0008A0A3)
#define SCI5_SSR_ADDR				((volatile uint8_t *)0x0008A0A4)
#define SCI5_RDR_ADDR				((volatile uint8_t *)0x0008A0A5)
#define SCI5_SCMR_ADDR				((volatile uint8_t *)0x0008A0A6)
#define SCI5_SEMR_ADDR				((volatile uint8_t *)0x0008A0A7)
#define SCI6_SMR_ADDR				((volatile uint8_t *)0x0008A0C0)
#define SCI6_BRR_ADDR				((volatile uint8_t *)0x0008A0C1)
#define SCI6_SCR_ADDR				((volatile uint8_t *)0x0008A0C2)
#define SCI6_TDR_ADDR				((volatile uint8_t *)0x0008A0C3)
#define SCI6_SSR_ADDR				((volatile uint8_t *)0x0008A0C4)
#define SCI6_RDR_ADDR				((volatile uint8_t *)0x0008A0C5)
#define SCI6_SCMR_ADDR				((volatile uint8_t *)0x0008A0C6)
#define SCI6_SEMR_ADDR				((volatile uint8_t *)0x0008A0C7)
#define SCI7_SMR_ADDR				((volatile uint8_t *)0x000D00E0)
#define SCI7_BRR_ADDR				((volatile uint8_t *)0x000D00E1)
#define SCI7_SCR_ADDR				((volatile uint8_t *)0x000D00E2)
#define SCI7_TDR_ADDR				((volatile uint8_t *)0x000D00E3)
#define SCI7_SSR_ADDR				((volatile uint8_t *)0x000D00E4)
#define SCI7_RDR_ADDR				((volatile uint8_t *)0x000D00E5)
#define SCI7_SCMR_ADDR				((volatile uint8_t *)0x000D00E6)
#define SCI7_SEMR_ADDR				((volatile uint8_t *)0x000D00E7)
#define SCI8_SMR_ADDR				((volatile uint8_t *)0x000D0000)
#define SCI8_BRR_ADDR				((volatile uint8_t *)0x000D0001)
#define SCI8_SCR_ADDR				((volatile uint8_t *)0x000D0002)
#define SCI8_TDR_ADDR				((volatile uint8_t *)0x000D0003)
#define SCI8_SSR_ADDR				((volatile uint8_t *)0x000D0004)
#define SCI8_RDR_ADDR				((volatile uint8_t *)0x000D0005)
#define SCI8_SCMR_ADDR				((volatile uint8_t *)0x000D0006)
#define SCI8_SEMR_ADDR				((volatile uint8_t *)0x000D0007)
#define SCI9_SMR_ADDR				((volatile uint8_t *)0x000D0020)
#define SCI9_BRR_ADDR				((volatile uint8_t *)0x000D0021)
#define SCI9_SCR_ADDR				((volatile uint8_t *)0x000D0022)
#define SCI9_TDR_ADDR				((volatile uint8_t *)0x000D0023)
#define SCI9_SSR_ADDR				((volatile uint8_t *)0x000D0024)
#define SCI9_RDR_ADDR				((volatile uint8_t *)0x000D0025)
#define SCI9_SCMR_ADDR				((volatile uint8_t *)0x000D0026)
#define SCI9_SEMR_ADDR				((volatile uint8_t *)0x000D0027)
#define SCI10_SMR_ADDR				((volatile uint8_t *)0x000D0040)
#define SCI10_BRR_ADDR				((volatile uint8_t *)0x000D0041)
#define SCI10_SCR_ADDR				((volatile uint8_t *)0x000D0042)
#define SCI10_TDR_ADDR				((volatile uint8_t *)0x000D0043)
#define SCI10_SSR_ADDR				((volatile uint8_t *)0x000D0044)
#define SCI10_RDR_ADDR				((volatile uint8_t *)0x000D0045)
#define SCI10_SCMR_ADDR				((volatile uint8_t *)0x000D0046)
#define SCI10_SEMR_ADDR				((volatile uint8_t *)0x000D0047)
#define SCI11_SMR_ADDR				((volatile uint8_t *)0x000D0060)
#define SCI11_BRR_ADDR				((volatile uint8_t *)0x000D0061)
#define SCI11_SCR_ADDR				((volatile uint8_t *)0x000D0062)
#define SCI11_TDR_ADDR				((volatile uint8_t *)0x000D0063)
#define SCI11_SSR_ADDR				((volatile uint8_t *)0x000D0064)
#define SCI11_RDR_ADDR				((volatile uint8_t *)0x000D0065)
#define SCI11_SCMR_ADDR				((volatile uint8_t *)0x000D0066)
#define SCI11_SEMR_ADDR				((volatile uint8_t *)0x000D0067)
#define SCI12_SMR_ADDR				((volatile uint8_t *)0x0008B300)
#define SCI12_BRR_ADDR				((volatile uint8_t *)0x0008B301)
#define SCI12_SCR_ADDR				((volatile uint8_t *)0x0008B302)
#define SCI12_TDR_ADDR				((volatile uint8_t *)0x0008B303)
#define SCI12_SSR_ADDR				((volatile uint8_t *)0x0008B304)
#define SCI12_RDR_ADDR				((volatile uint8_t *)0x0008B305)
#define SCI12_SCMR_ADDR				((volatile uint8_t *)0x0008B306)
#define SCI12_SEMR_ADDR				((volatile uint8_t *)0x0008B307)
#define SCI_SMR_CKS_BIT				(3U << 0U)
#define SCI_SMR_MP_BIT	    	   	(1U << 2U)
#define SCI_SMR_STOP_BIT			(1U << 3U)
#define SCI_SMR_PM_BIT				(1U << 4U)
#define SCI_SMR_PE_BIT				(1U << 5U)
#define SCI_SMR_CHR_BIT				(1U << 6U)
#define SCI_SMR_CM_BIT				(1U << 7U)
#define SCI_SCR_CKE_BIT				(3U << 0U)
#define SCI_SCR_TEIE_BIT			(1U << 2U)
#define SCI_SCR_MPIE_BIT			(1U << 3U)
#define SCI_SCR_RE_BIT				(1U << 4U)
#define SCI_SCR_TE_BIT				(1U << 5U)
#define SCI_SCR_RIE_BIT				(1U << 6U)
#define SCI_SCR_TIE_BIT				(1U << 7U)
#define SCI_SSR_MPBT_BIT			(1U << 0U)
#define SCI_SSR_MPB_BIT 			(1U << 1U)
#define SCI_SSR_TEND_BIT			(1U << 2U)
#define SCI_SSR_PER_BIT				(1U << 3U)
#define SCI_SSR_FER_BIT				(1U << 4U)
#define SCI_SSR_ORER_BIT			(1U << 5U)
#define SCI_SSR_RDRF_BIT			(1U << 6U)
#define SCI_SSR_TDRE_BIT			(1U << 7U)
#define SCI_SCMR_SMIF_BIT			(1U << 0U)
#define SCI_SCMR_SINV_BIT			(1U << 2U)
#define SCI_SCMR_SDIR_BIT			(1U << 3U)
#define SCI_SCMR_BCP2_BIT			(1U << 7U)
#define SCI_SEMR_ACS0_BIT			(1U << 0U)
#define SCI_SEMR_BRME_BIT			(1U << 2U)
#define SCI_SEMR_ABCSE_BIT			(1U << 3U)
#define SCI_SEMR_ABCS_BIT			(1U << 4U)
#define SCI_SEMR_NFEN_BIT			(1U << 5U)
#define SCI_SEMR_BGDM_BIT			(1U << 6U)
#define SCI_SEMR_RXDESEL_BIT		(1U << 7U)


/*
 * Multi function Pin Controler configration define
 */
#define MPC_PFENET_ADDR				((volatile uint8_t *)0x0008C10E)
#define MPC_PFENET_PHYMODE0_BIT		(1U << 4)
#define MPC_PFENET_PHYMODE1_BIT		(1U << 5)

#define MPC_PWPR_ADDR				((volatile uint8_t *)0x0008C11F)
#define MPC_PWPR_PFSWE_BIT			(1U << 6)
#define MPC_PWPR_B0WI_BIT			(1U << 7)
#define MPC_PWPR_PFSW_CLEAR			0U

#define MPC_P00PFS_ADDR				((volatile uint8_t *)0x0008C140)
#define MPC_P01PFS_ADDR				((volatile uint8_t *)0x0008C141)
#define MPC_P02PFS_ADDR				((volatile uint8_t *)0x0008C142)
#define MPC_P03PFS_ADDR				((volatile uint8_t *)0x0008C143)
#define MPC_P05PFS_ADDR				((volatile uint8_t *)0x0008C145)
#define MPC_P07PFS_ADDR				((volatile uint8_t *)0x0008C147)
#define MPC_P10PFS_ADDR				((volatile uint8_t *)0x0008C148)
#define MPC_P11PFS_ADDR				((volatile uint8_t *)0x0008C149)
#define MPC_P12PFS_ADDR				((volatile uint8_t *)0x0008C14A)
#define MPC_P13PFS_ADDR				((volatile uint8_t *)0x0008C14B)
#define MPC_P14PFS_ADDR				((volatile uint8_t *)0x0008C14C)
#define MPC_P15PFS_ADDR				((volatile uint8_t *)0x0008C14D)
#define MPC_P16PFS_ADDR				((volatile uint8_t *)0x0008C14E)
#define MPC_P17PFS_ADDR				((volatile uint8_t *)0x0008C14F)
#define MPC_P20PFS_ADDR				((volatile uint8_t *)0x0008C150)
#define MPC_P21PFS_ADDR				((volatile uint8_t *)0x0008C151)
#define MPC_P22PFS_ADDR				((volatile uint8_t *)0x0008C152)
#define MPC_P23PFS_ADDR				((volatile uint8_t *)0x0008C153)
#define MPC_P24PFS_ADDR				((volatile uint8_t *)0x0008C154)
#define MPC_P25PFS_ADDR				((volatile uint8_t *)0x0008C155)
#define MPC_P26PFS_ADDR				((volatile uint8_t *)0x0008C156)
#define MPC_P27PFS_ADDR				((volatile uint8_t *)0x0008C157)
#define MPC_P30PFS_ADDR				((volatile uint8_t *)0x0008C158)
#define MPC_P31PFS_ADDR				((volatile uint8_t *)0x0008C159)
#define MPC_P32PFS_ADDR				((volatile uint8_t *)0x0008C15A)
#define MPC_P33PFS_ADDR				((volatile uint8_t *)0x0008C15B)
#define MPC_P34PFS_ADDR				((volatile uint8_t *)0x0008C15C)
#define MPC_P40PFS_ADDR				((volatile uint8_t *)0x0008C160)
#define MPC_P41PFS_ADDR				((volatile uint8_t *)0x0008C161)
#define MPC_P42PFS_ADDR				((volatile uint8_t *)0x0008C162)
#define MPC_P43PFS_ADDR				((volatile uint8_t *)0x0008C163)
#define MPC_P44PFS_ADDR				((volatile uint8_t *)0x0008C164)
#define MPC_P45PFS_ADDR				((volatile uint8_t *)0x0008C165)
#define MPC_P46PFS_ADDR				((volatile uint8_t *)0x0008C166)
#define MPC_P47PFS_ADDR				((volatile uint8_t *)0x0008C167)
#define MPC_P50PFS_ADDR				((volatile uint8_t *)0x0008C168)
#define MPC_P51PFS_ADDR				((volatile uint8_t *)0x0008C169)
#define MPC_P52PFS_ADDR				((volatile uint8_t *)0x0008C16A)
#define MPC_P54PFS_ADDR				((volatile uint8_t *)0x0008C16C)
#define MPC_P55PFS_ADDR				((volatile uint8_t *)0x0008C16D)
#define MPC_P56PFS_ADDR				((volatile uint8_t *)0x0008C16E)
#define MPC_P57PFS_ADDR				((volatile uint8_t *)0x0008C16F)
#define MPC_P60PFS_ADDR				((volatile uint8_t *)0x0008C170)
#define MPC_P61PFS_ADDR				((volatile uint8_t *)0x0008C171)
#define MPC_P62PFS_ADDR				((volatile uint8_t *)0x0008C172)
#define MPC_P63PFS_ADDR				((volatile uint8_t *)0x0008C173)
#define MPC_P64PFS_ADDR				((volatile uint8_t *)0x0008C174)
#define MPC_P66PFS_ADDR				((volatile uint8_t *)0x0008C176)
#define MPC_P67PFS_ADDR				((volatile uint8_t *)0x0008C177)
#define MPC_P70PFS_ADDR				((volatile uint8_t *)0x0008C178)
#define MPC_P71PFS_ADDR				((volatile uint8_t *)0x0008C179)
#define MPC_P72PFS_ADDR				((volatile uint8_t *)0x0008C17A)
#define MPC_P73PFS_ADDR				((volatile uint8_t *)0x0008C17B)
#define MPC_P74PFS_ADDR				((volatile uint8_t *)0x0008C17C)
#define MPC_P75PFS_ADDR				((volatile uint8_t *)0x0008C17D)
#define MPC_P76PFS_ADDR				((volatile uint8_t *)0x0008C17E)
#define MPC_P77PFS_ADDR				((volatile uint8_t *)0x0008C17F)
#define MPC_P80PFS_ADDR				((volatile uint8_t *)0x0008C180)
#define MPC_P81PFS_ADDR				((volatile uint8_t *)0x0008C181)
#define MPC_P82PFS_ADDR				((volatile uint8_t *)0x0008C182)
#define MPC_P83PFS_ADDR				((volatile uint8_t *)0x0008C183)
#define MPC_P84PFS_ADDR				((volatile uint8_t *)0x0008C184)
#define MPC_P85PFS_ADDR				((volatile uint8_t *)0x0008C185)
#define MPC_P86PFS_ADDR				((volatile uint8_t *)0x0008C186)
#define MPC_P87PFS_ADDR				((volatile uint8_t *)0x0008C187)
#define MPC_P90PFS_ADDR				((volatile uint8_t *)0x0008C188)
#define MPC_P91PFS_ADDR				((volatile uint8_t *)0x0008C189)
#define MPC_P92PFS_ADDR				((volatile uint8_t *)0x0008C18A)
#define MPC_P93PFS_ADDR				((volatile uint8_t *)0x0008C18B)
#define MPC_P94PFS_ADDR				((volatile uint8_t *)0x0008C18C)
#define MPC_P95PFS_ADDR				((volatile uint8_t *)0x0008C18D)
#define MPC_P96PFS_ADDR				((volatile uint8_t *)0x0008C18E)
#define MPC_P97PFS_ADDR				((volatile uint8_t *)0x0008C18F)
#define MPC_PA0PFS_ADDR				((volatile uint8_t *)0x0008C190)
#define MPC_PA1PFS_ADDR				((volatile uint8_t *)0x0008C191)
#define MPC_PA2PFS_ADDR				((volatile uint8_t *)0x0008C192)
#define MPC_PA3PFS_ADDR				((volatile uint8_t *)0x0008C193)
#define MPC_PA4PFS_ADDR				((volatile uint8_t *)0x0008C194)
#define MPC_PA5PFS_ADDR				((volatile uint8_t *)0x0008C195)
#define MPC_PA6PFS_ADDR				((volatile uint8_t *)0x0008C196)
#define MPC_PA7PFS_ADDR				((volatile uint8_t *)0x0008C197)
#define MPC_PB0PFS_ADDR				((volatile uint8_t *)0x0008C198)
#define MPC_PB1PFS_ADDR				((volatile uint8_t *)0x0008C199)
#define MPC_PB2PFS_ADDR				((volatile uint8_t *)0x0008C19A)
#define MPC_PB3PFS_ADDR				((volatile uint8_t *)0x0008C19B)
#define MPC_PB4PFS_ADDR				((volatile uint8_t *)0x0008C19C)
#define MPC_PB5PFS_ADDR				((volatile uint8_t *)0x0008C19D)
#define MPC_PB6PFS_ADDR				((volatile uint8_t *)0x0008C19E)
#define MPC_PB7PFS_ADDR				((volatile uint8_t *)0x0008C19F)
#define MPC_PC0PFS_ADDR				((volatile uint8_t *)0x0008C1A0)
#define MPC_PC1PFS_ADDR				((volatile uint8_t *)0x0008C1A1)
#define MPC_PC2PFS_ADDR				((volatile uint8_t *)0x0008C1A2)
#define MPC_PC3PFS_ADDR				((volatile uint8_t *)0x0008C1A3)
#define MPC_PC4PFS_ADDR				((volatile uint8_t *)0x0008C1A4)
#define MPC_PC5PFS_ADDR				((volatile uint8_t *)0x0008C1A5)
#define MPC_PC6PFS_ADDR				((volatile uint8_t *)0x0008C1A6)
#define MPC_PC7PFS_ADDR				((volatile uint8_t *)0x0008C1A7)
#define MPC_PD0PFS_ADDR				((volatile uint8_t *)0x0008C1A8)
#define MPC_PD1PFS_ADDR				((volatile uint8_t *)0x0008C1A9)
#define MPC_PD2PFS_ADDR				((volatile uint8_t *)0x0008C1AA)
#define MPC_PD3PFS_ADDR				((volatile uint8_t *)0x0008C1AB)
#define MPC_PD4PFS_ADDR				((volatile uint8_t *)0x0008C1AC)
#define MPC_PD5PFS_ADDR				((volatile uint8_t *)0x0008C1AD)
#define MPC_PD6PFS_ADDR				((volatile uint8_t *)0x0008C1AE)
#define MPC_PD7PFS_ADDR				((volatile uint8_t *)0x0008C1BF)
#define MPC_PE0PFS_ADDR				((volatile uint8_t *)0x0008C1B0)
#define MPC_PE1PFS_ADDR				((volatile uint8_t *)0x0008C1B1)
#define MPC_PE2PFS_ADDR				((volatile uint8_t *)0x0008C1B2)
#define MPC_PE3PFS_ADDR				((volatile uint8_t *)0x0008C1B3)
#define MPC_PE4PFS_ADDR				((volatile uint8_t *)0x0008C1B4)
#define MPC_PE5PFS_ADDR				((volatile uint8_t *)0x0008C1B5)
#define MPC_PE6PFS_ADDR				((volatile uint8_t *)0x0008C1B6)
#define MPC_PE7PFS_ADDR				((volatile uint8_t *)0x0008C1B7)
#define MPC_PF0PFS_ADDR				((volatile uint8_t *)0x0008C1B8)
#define MPC_PF1PFS_ADDR				((volatile uint8_t *)0x0008C1B9)
#define MPC_PF2PFS_ADDR				((volatile uint8_t *)0x0008C1BA)
#define MPC_PF5PFS_ADDR				((volatile uint8_t *)0x0008C1BD)
#define MPC_PFS_PSEL0				0x0
#define MPC_PFS_PSEL1				0x1
#define MPC_PFS_PSEL2				0x2
#define MPC_PFS_PSEL3				0x3
#define MPC_PFS_PSEL4				0x4
#define MPC_PFS_PSEL5				0x5
#define MPC_PFS_PSEL6				0x6
#define MPC_PFS_PSEL7				0x7
#define MPC_PFS_PSEL8				0x8
#define MPC_PFS_PSEL9				0x9
#define MPC_PFS_PSELA				0xA
#define MPC_PFS_PSELB				0xB
#define MPC_PFS_PSELC				0xC
#define MPC_PFS_PSELD				0xD
#define MPC_PFS_PSELE				0xE
#define MPC_PFS_PSELF				0xF
#define MPC_PFS_ISEL				(1U << 6)
#define MPC_PFS_ASEL				(1U << 7)


/*
 *  I/Oポートのレジスタ及び設定ビット情報
 */
#define PORT0_PDR_ADDR				((volatile uint8_t *)0x0008C000)
#define PORT1_PDR_ADDR				((volatile uint8_t *)0x0008C001)
#define PORT2_PDR_ADDR				((volatile uint8_t *)0x0008C002)
#define PORT3_PDR_ADDR				((volatile uint8_t *)0x0008C003)
#define PORT4_PDR_ADDR				((volatile uint8_t *)0x0008C004)
#define PORT5_PDR_ADDR				((volatile uint8_t *)0x0008C005)
#define PORT6_PDR_ADDR				((volatile uint8_t *)0x0008C006)
#define PORT7_PDR_ADDR				((volatile uint8_t *)0x0008C007)
#define PORT8_PDR_ADDR				((volatile uint8_t *)0x0008C008)
#define PORT9_PDR_ADDR				((volatile uint8_t *)0x0008C009)
#define PORTA_PDR_ADDR				((volatile uint8_t *)0x0008C00A)
#define PORTB_PDR_ADDR				((volatile uint8_t *)0x0008C00B)
#define PORTC_PDR_ADDR				((volatile uint8_t *)0x0008C00C)
#define PORTD_PDR_ADDR				((volatile uint8_t *)0x0008C00D)
#define PORTE_PDR_ADDR				((volatile uint8_t *)0x0008C00E)
#define PORTF_PDR_ADDR				((volatile uint8_t *)0x0008C00F)
#define PORTG_PDR_ADDR				((volatile uint8_t *)0x0008C010)
#define PORTH_PDR_ADDR				((volatile uint8_t *)0x0008C011)
#define PORTJ_PDR_ADDR				((volatile uint8_t *)0x0008C012)
#define PORTK_PDR_ADDR				((volatile uint8_t *)0x0008C013)
#define PORTL_PDR_ADDR				((volatile uint8_t *)0x0008C014)
#define PORTM_PDR_ADDR				((volatile uint8_t *)0x0008C015)
#define PORTN_PDR_ADDR				((volatile uint8_t *)0x0008C016)
#define PORTQ_PDR_ADDR				((volatile uint8_t *)0x0008C017)
#define PORT_PDR_B0_BIT				(0x01U << 0U)
#define PORT_PDR_B1_BIT				(0x01U << 1U)
#define PORT_PDR_B2_BIT				(0x01U << 2U)
#define PORT_PDR_B3_BIT				(0x01U << 3U)
#define PORT_PDR_B4_BIT				(0x01U << 4U)
#define PORT_PDR_B5_BIT				(0x01U << 5U)
#define PORT_PDR_B6_BIT				(0x01U << 6U)
#define PORT_PDR_B7_BIT				(0x01U << 7U)
#define PORT0_PODR_ADDR				((volatile uint8_t *)0x0008C020)
#define PORT1_PODR_ADDR				((volatile uint8_t *)0x0008C021)
#define PORT2_PODR_ADDR				((volatile uint8_t *)0x0008C022)
#define PORT3_PODR_ADDR				((volatile uint8_t *)0x0008C023)
#define PORT4_PODR_ADDR				((volatile uint8_t *)0x0008C024)
#define PORT5_PODR_ADDR				((volatile uint8_t *)0x0008C025)
#define PORT6_PODR_ADDR				((volatile uint8_t *)0x0008C026)
#define PORT7_PODR_ADDR				((volatile uint8_t *)0x0008C027)
#define PORT8_PODR_ADDR				((volatile uint8_t *)0x0008C028)
#define PORT9_PODR_ADDR				((volatile uint8_t *)0x0008C029)
#define PORTA_PODR_ADDR				((volatile uint8_t *)0x0008C02A)
#define PORTB_PODR_ADDR				((volatile uint8_t *)0x0008C02B)
#define PORTC_PODR_ADDR				((volatile uint8_t *)0x0008C02C)
#define PORTD_PODR_ADDR				((volatile uint8_t *)0x0008C02D)
#define PORTE_PODR_ADDR				((volatile uint8_t *)0x0008C02E)
#define PORTF_PODR_ADDR				((volatile uint8_t *)0x0008C02F)
#define PORTG_PODR_ADDR				((volatile uint8_t *)0x0008C030)
#define PORTH_PODR_ADDR				((volatile uint8_t *)0x0008C031)
#define PORTJ_PODR_ADDR				((volatile uint8_t *)0x0008C032)
#define PORTK_PODR_ADDR				((volatile uint8_t *)0x0008C033)
#define PORTL_PODR_ADDR				((volatile uint8_t *)0x0008C034)
#define PORTM_PODR_ADDR				((volatile uint8_t *)0x0008C035)
#define PORTN_PODR_ADDR				((volatile uint8_t *)0x0008C036)
#define PORTQ_PODR_ADDR				((volatile uint8_t *)0x0008C037)
#define PORT_PODR_B0_BIT			(0x01U << 0U)
#define PORT_PODR_B1_BIT			(0x01U << 1U)
#define PORT_PODR_B2_BIT			(0x01U << 2U)
#define PORT_PODR_B3_BIT			(0x01U << 3U)
#define PORT_PODR_B4_BIT			(0x01U << 4U)
#define PORT_PODR_B5_BIT			(0x01U << 5U)
#define PORT_PODR_B6_BIT			(0x01U << 6U)
#define PORT_PODR_B7_BIT			(0x01U << 7U)
#define PORT0_PIDR_ADDR				((volatile uint8_t *)0x0008C040)
#define PORT1_PIDR_ADDR				((volatile uint8_t *)0x0008C041)
#define PORT2_PIDR_ADDR				((volatile uint8_t *)0x0008C042)
#define PORT3_PIDR_ADDR				((volatile uint8_t *)0x0008C043)
#define PORT4_PIDR_ADDR				((volatile uint8_t *)0x0008C044)
#define PORT5_PIDR_ADDR				((volatile uint8_t *)0x0008C045)
#define PORT6_PIDR_ADDR				((volatile uint8_t *)0x0008C046)
#define PORT7_PIDR_ADDR				((volatile uint8_t *)0x0008C047)
#define PORT8_PIDR_ADDR				((volatile uint8_t *)0x0008C048)
#define PORT9_PIDR_ADDR				((volatile uint8_t *)0x0008C049)
#define PORTA_PIDR_ADDR				((volatile uint8_t *)0x0008C04A)
#define PORTB_PIDR_ADDR				((volatile uint8_t *)0x0008C04B)
#define PORTC_PIDR_ADDR				((volatile uint8_t *)0x0008C04C)
#define PORTD_PIDR_ADDR				((volatile uint8_t *)0x0008C04D)
#define PORTE_PIDR_ADDR				((volatile uint8_t *)0x0008C04E)
#define PORTF_PIDR_ADDR				((volatile uint8_t *)0x0008C04F)
#define PORTG_PIDR_ADDR				((volatile uint8_t *)0x0008C050)
#define PORTH_PIDR_ADDR				((volatile uint8_t *)0x0008C051)
#define PORTJ_PIDR_ADDR				((volatile uint8_t *)0x0008C052)
#define PORTK_PIDR_ADDR				((volatile uint8_t *)0x0008C053)
#define PORTL_PIDR_ADDR				((volatile uint8_t *)0x0008C054)
#define PORTM_PIDR_ADDR				((volatile uint8_t *)0x0008C055)
#define PORTN_PIDR_ADDR				((volatile uint8_t *)0x0008C056)
#define PORTQ_PIDR_ADDR				((volatile uint8_t *)0x0008C057)
#define PORT_PIDR_B0_BIT			(0x01U << 0U)
#define PORT_PIDR_B1_BIT			(0x01U << 1U)
#define PORT_PIDR_B2_BIT			(0x01U << 2U)
#define PORT_PIDR_B3_BIT			(0x01U << 3U)
#define PORT_PIDR_B4_BIT			(0x01U << 4U)
#define PORT_PIDR_B5_BIT			(0x01U << 5U)
#define PORT_PIDR_B6_BIT			(0x01U << 6U)
#define PORT_PIDR_B7_BIT			(0x01U << 7U)
#define PORT0_PMR_ADDR				((volatile uint8_t *)0x0008C060)
#define PORT1_PMR_ADDR				((volatile uint8_t *)0x0008C061)
#define PORT2_PMR_ADDR				((volatile uint8_t *)0x0008C062)
#define PORT3_PMR_ADDR				((volatile uint8_t *)0x0008C063)
#define PORT4_PMR_ADDR				((volatile uint8_t *)0x0008C064)
#define PORT5_PMR_ADDR				((volatile uint8_t *)0x0008C065)
#define PORT6_PMR_ADDR				((volatile uint8_t *)0x0008C066)
#define PORT7_PMR_ADDR				((volatile uint8_t *)0x0008C067)
#define PORT8_PMR_ADDR				((volatile uint8_t *)0x0008C068)
#define PORT9_PMR_ADDR				((volatile uint8_t *)0x0008C068)
#define PORTA_PMR_ADDR				((volatile uint8_t *)0x0008C06A)
#define PORTB_PMR_ADDR				((volatile uint8_t *)0x0008C06B)
#define PORTC_PMR_ADDR				((volatile uint8_t *)0x0008C06C)
#define PORTD_PMR_ADDR				((volatile uint8_t *)0x0008C06D)
#define PORTE_PMR_ADDR				((volatile uint8_t *)0x0008C06E)
#define PORTF_PMR_ADDR				((volatile uint8_t *)0x0008C06F)
#define PORTG_PMR_ADDR				((volatile uint8_t *)0x0008C070)
#define PORTH_PMR_ADDR				((volatile uint8_t *)0x0008C071)
#define PORTJ_PMR_ADDR				((volatile uint8_t *)0x0008C072)
#define PORTK_PMR_ADDR				((volatile uint8_t *)0x0008C073)
#define PORTL_PMR_ADDR				((volatile uint8_t *)0x0008C074)
#define PORTM_PMR_ADDR				((volatile uint8_t *)0x0008C075)
#define PORTN_PMR_ADDR				((volatile uint8_t *)0x0008C076)
#define PORTQ_PMR_ADDR				((volatile uint8_t *)0x0008C077)
#define PORT_PMR_B0_BIT				(0x01U << 0U)
#define PORT_PMR_B1_BIT				(0x01U << 1U)
#define PORT_PMR_B2_BIT				(0x01U << 2U)
#define PORT_PMR_B3_BIT				(0x01U << 3U)
#define PORT_PMR_B4_BIT				(0x01U << 4U)
#define PORT_PMR_B5_BIT				(0x01U << 5U)
#define PORT_PMR_B6_BIT				(0x01U << 6U)
#define PORT_PMR_B7_BIT				(0x01U << 7U)


/*
 *  UART関連の定義
 *
 *  pdicのrx72M_uart.cで使用する．
 */

/*
 *  シリアルI/Oの個数
 */
#define TNUM_SIOP			(4)

#endif	/* TOPPERS_RX72M_H */
