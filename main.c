#include <stm32f10x.h>

#include "delay.h"
#include "init.h"
#include "usart.h"

int main(void)
{
	RCCInit();
	GPIOInit();
	USARTInit();
	NVICInit();
	
	SysTick_Config(SystemCoreClock/1000);//ms
	
	while(1)
	{
		GPIO_WriteBit(GPIOC,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_8)));
		_delay_ms(100);
		GPIO_WriteBit(GPIOC,GPIO_Pin_9,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_9)));
		_delay_ms(200);
		
		USART_Send_Ch(USART1,'z');
		USART_Send_Ch(USART2,'x');
	}
}

