#include "timer.h"

void TIM2_IRQ_Init(uint32_t period)
{
  TIM_TimeBaseInitTypeDef timerInitStruct;
  NVIC_InitTypeDef NVIC_InitStructure;
  RCC_ClocksTypeDef clockFreq;
  
  RCC_GetClocksFreq(&clockFreq);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  
  timerInitStruct.TIM_Prescaler = clockFreq.PCLK1_Frequency/1000;
  timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
  timerInitStruct.TIM_Period = period;
  timerInitStruct.TIM_ClockDivision = TIM_CKD_DIV1 ;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  NVIC_Init(&NVIC_InitStructure);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  
  TIM_TimeBaseInit(TIM2,&timerInitStruct);
  TIM_Cmd(TIM2, ENABLE);
  return ;
}


void TIM2_IRQHandler()
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
   {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
      GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
   }
   return;
}