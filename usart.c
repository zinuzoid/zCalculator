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

