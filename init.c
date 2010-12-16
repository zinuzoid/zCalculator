#include "stm32f10x.h"

void RCCInit(void)
{
	RCC_APB2PeriphClockCmd(
							RCC_APB2Periph_GPIOA|
							//RCC_APB2Periph_GPIOB|
							RCC_APB2Periph_GPIOC|
							//RCC_APB2Periph_ADC1|
							RCC_APB2Periph_USART1|
							RCC_APB2Periph_AFIO
							//RCC_APB2Periph_TIM1
							,ENABLE);
	RCC_APB1PeriphClockCmd(
							//RCC_APB1Periph_TIM2|
							RCC_APB1Periph_USART2
							//RCC_APB1Periph_USART3
							//RCC_APB1Periph_TIM3
							,ENABLE);
}

void GPIOInit(void)
{
	GPIO_InitTypeDef GPIOInit;

	//LED
	GPIOInit.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIOInit.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIOInit);
	
	//USART1
	GPIOInit.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOInit.GPIO_Pin=GPIO_Pin_9;
	GPIOInit.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIOInit);
	
	GPIOInit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIOInit.GPIO_Pin=GPIO_Pin_10;
	GPIOInit.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIOInit);
	
	//USART2
	GPIOInit.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOInit.GPIO_Pin=GPIO_Pin_2;
	GPIOInit.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIOInit);
	
	GPIOInit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIOInit.GPIO_Pin=GPIO_Pin_3;
	GPIOInit.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIOInit);
}

void USARTInit(void)
{
	USART_InitTypeDef	USARTInit;
	
	USARTInit.USART_BaudRate=115200;
	USARTInit.USART_WordLength=USART_WordLength_8b;
	USARTInit.USART_StopBits=USART_StopBits_1;
	USARTInit.USART_Parity=USART_Parity_No;
	USARTInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USARTInit.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1,&USARTInit);
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USARTInit.USART_BaudRate=115200;
	USARTInit.USART_WordLength=USART_WordLength_8b;
	USARTInit.USART_StopBits=USART_StopBits_1;
	USARTInit.USART_Parity=USART_Parity_No;
	USARTInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USARTInit.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART2,&USARTInit);
	USART_Cmd(USART2,ENABLE);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
}


void NVICInit(void)
{
	NVIC_InitTypeDef NVICInit;	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVICInit.NVIC_IRQChannel=USART1_IRQn;
	NVICInit.NVIC_IRQChannelPreemptionPriority=0;
	NVICInit.NVIC_IRQChannelSubPriority=10;
	NVICInit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVICInit);
	
	NVICInit.NVIC_IRQChannel=USART2_IRQn;
	NVICInit.NVIC_IRQChannelPreemptionPriority=0;
	NVICInit.NVIC_IRQChannelSubPriority=9;
	NVICInit.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVICInit);
}


