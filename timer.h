#ifndef TIMER_H
#define TIMER_H
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

#define TIME1000ms 0x3E8 
#define TIME100ms  0x64

extern void TIM2_IRQ_Init(uint32_t period);

#endif 