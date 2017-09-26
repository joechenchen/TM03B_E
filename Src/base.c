#include "base.h"
#include "tim.h"

//1,1010,1010,1010,1001,0110,0110,1001<-11,0,1010101010,1001011001101001 carrier+separation bit+Preamble(10)+Pattern(16)
const uint32_t BaseHead =  0x1aaa9669;
#define BaseHeadMsk 0x10000000
volatile uint8_t  BaseSendBitCount;//记录发送次数
uint32_t BaseData ;
#define BaseDataMsk 0x80000000
uint32_t Base_Period[60];//每次通过dma更新RCR值 
GPIO_PinState BaseCh1_CurrentState;
uint8_t finish;
uint16_t BasePwmNum;
typedef enum 
{
	head,//发送头
	data//发送数据
}BaseSendState_t;
uint8_t BaseSendState;//发送状态
void Base_Para_Init(uint32_t* pBuff)
{
	uint8_t i;
	*pBuff++ = 350;
//	*pBuff++ = 5;
	for(i=0;i<BaseHeadLen;i++)
	{
		*pBuff++ = gBitDuration;
	}
	for(i=0;i<BaseDataLen;i++)
	{
		*pBuff++ = gBitDuration;
	}
	BaseSendBitCount = 0;
	BasePwmNum = 0;
	BaseSendState = head;
}

void Base_Ch1_Start(void)
{
	Base_Para_Init(Base_Period);
	HAL_GPIO_WritePin(BaseCh1_GPIO_Port, BaseCh1_Pin, GPIO_PIN_SET);
//	HAL_TIM_DMABurst_MultiWriteStart(&htim1, TIM_DMABASE_RCR, TIM_DMA_CC2, 
//                                                   Base_Period, TIM_DMABURSTLENGTH_1TRANSFER, 2);
	 /* Enable the TIM Update interrupt */
//  __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

	HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_2);		


}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if( htim->Instance == TIM1)
	{
		finish++;
		if(finish >= 1)
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
		}
//		__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_UPDATE);
//		finish = 1;
//		__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_UPDATE);
			
//		HAL_TIM_DMABurst_WriteStop(&htim1,TIM_DMA_CC2);
		
//		switch(BaseSendState)
//		{
//			case head:
//			{
//				if (BaseSendBitCount < BaseHeadLen)
//				{
//					BaseCh1_CurrentState = (BaseHead&BaseHeadMsk)?GPIO_PIN_SET:GPIO_PIN_RESET;
//					BaseSendBitCount++;
//				}	
//				else
//				{
//					BaseSendState = data;
//					BaseSendBitCount = 0;
//				}
//			}
//			break;
//			case data:
//			{
//				if (BaseSendBitCount < BaseDataLen)
//				{
//					BaseCh1_CurrentState = (BaseHead&BaseHeadMsk)?GPIO_PIN_SET:GPIO_PIN_RESET;
//					BaseSendBitCount++;
//				}			
//			}
//			break;
//		}
//		HAL_GPIO_WritePin(BaseCh1_GPIO_Port, BaseCh1_Pin, GPIO_PIN_SET);
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if( htim->Instance == TIM1)
	{
		BasePwmNum++;
		if(BasePwmNum >= 5)
		{
			HAL_TIM_PWM_Stop_IT(&htim1,TIM_CHANNEL_2);
		}	
//		HAL_TIM_DMABurst_WriteStop(&htim1,TIM_DMA_CC2);
//		HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
		
	}
}

