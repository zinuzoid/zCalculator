/*------------------------------------------------------------------------------------------------
** Program 	:	usart.c
** Project	:	Realtime
** CPU		:	STM32F100
** Date		:	12/1/2011
** Modify	:	Jetsada Machom <Zinuzoid Corporation Co.,Ltd.>
** Copyright:	
** Note 	:	
------------------------------------------------------------------------------------------------*/

#include <stm32f10x.h>

#include "usart.h"

void USART_Send_Str(USART_TypeDef *usartport,char *str)
{
	while(*str)
	{
		USART_WaitSend(usartport);
		USART_SendData(usartport,*str);
		str++;
	}
}

