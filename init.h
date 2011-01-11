/*------------------------------------------------------------------------------------------------
** Program 	:	init.h
** Project	:	Realtime
** CPU		:	STM32F100
** Date		:	12/1/2011
** Modify	:	Jetsada Machom <Zinuzoid Corporation Co.,Ltd.>
** Copyright:	
** Note 	:	
------------------------------------------------------------------------------------------------*/

#include <stm32f10x.h>

void RCCInit(void);
//void ADCInit(void);
void GPIOInit(void);
//void TimerInit(void);
void NVICInit(void);
//void EXTIInit(void);
void USARTInit(void);

