#ifndef BASE_125K
#define BASE_125K
#include "stm32f0xx_hal.h"
#define BaseHeadLen 27
#define BaseDataLen 64
#define	gBitDuration   63   // default value in AS3933 (12 in register 7[4:0]  16个时钟周期=16*4Tcarrier//520us左右
#define	gCarrierBurstDuration   350   // duration of the carrier burst (250 == 2 ms carrier burst),scan mode最小时间80Tclk + 16Tcarr
#define	gNrPreambleSymbols   5   // Number of Preamble Symbols， 3.5ms R7[4:0]*Tclk*2 = 3.5MS
#define	gManchesterPatternLength   16   // 16 bit
#define	gCorrelatorDoublePattern   0   // 0 = single pattern, 1 = double pattern
#define	gPattern   0x96695555

typedef enum
{
	BASE_XOR_IDX = 0,
	BASE_DATA_IDX =1,
	BASE_ID_IDX = 2
}Base_125k_t;
typedef struct
{
	uint32_t BitPeriod[2];//每位周期
	uint8_t Data[4];
	uint32_t tHead;//临时缓存头
	uint32_t tData0;
	uint64_t tData;//临时缓存数据
	volatile uint16_t PwmNum;//pwm个数计数
	volatile uint8_t  SendBitCount;//记录发送次数
	uint8_t idx;//索引
	uint8_t sfinish;//发送完成
	uint8_t isOpen;//通道打开标志位
	uint8_t SendState;//发送状态
	GPIO_PinState IOCurrentState;//io状态
}Base_Ch_t;

typedef enum 
{
	S_BHead,//发送头
	S_BData//发送数据
}BaseSendState_e;
//通道号
typedef enum
{
	B_Channel0=0,
	B_Channel1=1,
	B_Channel2=2,
	B_Channel3=3
}BaseChannel_e;

typedef struct
{
	uint8_t cnt;
	uint8_t flag;
}Time_t;

//通道发射顺序
typedef enum
{
	S_Channel0=0,
	S_Channel1=1,
	S_Channel2=2,
	S_Channel3=3
}S_Channel_e;
//
typedef struct
{
	uint8_t ID[2];//基准ID
	uint8_t isOpen[4];//通道打开
	uint8_t Send_Period;//每通道发送周期
	uint8_t SendSeq;//通道发送顺序
	uint8_t AllowSend;//需要启动发射
	uint8_t NewStartSend;//新发送周期
	uint8_t Data;//指示标签
}Base_Mode_Typedef;
//参数字节索引
typedef enum
{
	BASEP_AUTOREPORT_IDX = 2,//激活周期间隔
	BASEP_CH0OPEN_IDX = 3,//通道 0 参数
	BASEP_CH0DATA_IDX = 3,
	BASEP_CH1OPEN_IDX = 4,
	BASEP_CH1DATA_IDX = 4,
	BASEP_CH2OPEN_IDX = 5,
	BASEP_CH2DATA_IDX = 5,
	BASEP_CH3OPEN_IDX = 6,
	BASEP_CH3DATA_IDX = 6,
}BaseP_Typedef;
#define BASEP_AUTOREPORT_Msk  0x07
#define BASEP_AUTOREPORT_Pos  0

#define BASEP_CHOPEN_Msk  0x01
#define BASEP_CHOPEN_Pos  0
#define BASEP_CHDATA_Msk  0x06
#define BASEP_CHDATA_Pos  1

void Base_Para_Init(void);
void Base_Process(void);
void Base_Ch1_Start(void);
void Base_Ch0_Start(void);
#endif
