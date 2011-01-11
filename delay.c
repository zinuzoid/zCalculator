/*------------------------------------------------------------------------------------------------
** Program 	:	delay.c
** Project	:	Realtime
** CPU		:	STM32F100
** Date		:	12/1/2011
** Modify	:	Jetsada Machom <Zinuzoid Corporation Co.,Ltd.>
** Copyright:	
** Note 	:	
------------------------------------------------------------------------------------------------*/

#include <stm32f10x.h>

#include "stm32f10x_it.h"

void _delay_ms(uint32_t time)
{
	_timming=time;
	while(_timming);
}

