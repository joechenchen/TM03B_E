#ifndef BASE_125K
#define BASE_125K
#include "stm32f0xx_hal.h"
#define BaseHeadLen 29
#define BaseDataLen 32
#define	gBitDuration   63   // default value in AS3933 (12 in register 7[4:0]  16个时钟周期=16*4Tcarrier//520us左右
#define	gCarrierBurstDuration   350   // duration of the carrier burst (250 == 2 ms carrier burst),scan mode最小时间80Tclk + 16Tcarr
#define	gNrPreambleSymbols   5   // Number of Preamble Symbols， 3.5ms R7[4:0]*Tclk*2 = 3.5MS
#define	gManchesterPatternLength   16   // 16 bit
#define	gCorrelatorDoublePattern   0   // 0 = single pattern, 1 = double pattern
#define	gPattern   0x96695555

void Base_Para_Init(uint32_t* pBuff);
void Base_Ch1_Start(void);
#endif
