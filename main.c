#include <stm32f10x.h>

#include <stdio.h>

#include <stdlib.h>

#include "main.h"
#include "delay.h"
#include "init.h"
#include "usart.h"
#include "stm32f10x_it.h"
#include "fixparse.h"
#include "calc.h"


int main(void)
{
	//char a[50]="1+sin(3*4+2)+cos(2-6*2)+10";//1 3 4 * 2 +  s +
	//char a[50]="1-5-1";
	
	RCCInit();
	GPIOInit();
	USARTInit();
	NVICInit();
	
	/*
	Infix2Postfix(a,b);
	
	EvalPostfix(b);
	
	USART_Send_Str(USART1,"\r\n\r\n###########");
	USART_Send_Str(USART1,a);
	USART_Send_Str(USART1,"\r\n\r\n");
	USART_Send_Str(USART1,b);
	*/
	
	SysTick_Config(SystemCoreClock/1000);//ms
	
	USART_Send_Ch(USART1,'\f');
	
	USART_Send_Str(USART1,WELCOMETEXT1);
	USART_Send_Str(USART1,WELCOMETEXT2);
	USART_Send_Str(USART1,WELCOMETEXT3);
	USART_Send_Str(USART1,WELCOMETEXT4);
	USART_Send_Str(USART1,WELCOMETEXT5);
	USART_Send_Str(USART1,WELCOMETEXT6);
	USART_Send_Str(USART1,WELCOMETEXT7);
	USART_Send_Str(USART1,WELCOMETEXT8);
	USART_Send_Str(USART1,WELCOMETEXT9);
	USART_Send_Str(USART1,WELCOMETEXT10);
	USART_Send_Str(USART1,WELCOMETEXT11);
	
	USART_Send_Str(USART1,"v0.1 rev 1000\r\n");
	USART_Send_Str(USART1,"-------------------------------------------------------------------\r\n");
	USART_Send_Str(USART1,COMMANDPROMPT);
	
	while(1)
	{
		if(ConsoleReaded)
		{
			double realans,imagans;
			char postfix[50];
			char sbuf[50];
			ConsoleReaded=0;
			
			Infix2Postfix(ConsoleBuffer,postfix);
			
			USART_Send_Str(USART2,postfix);
			USART_Send_Str(USART2,"\r\n");
			
			EvalPostfix(postfix,&realans,&imagans);
			
			sprintf(sbuf,"%f",realans);
			USART_Send_Str(USART1,"\r\n\r\n    ans = ");
			USART_Send_Str(USART1,sbuf);
			sprintf(sbuf,"%+f",imagans);
			USART_Send_Str(USART1,sbuf);
			USART_Send_Ch(USART1,'i');
			
			USART_Send_Str(USART1,"\r\n\r\n");
			USART_Send_Str(USART1,COMMANDPROMPT);
			
			//USART_Send_Ch(USART1,'#');
			//USART_Send_Str(USART1,ConsoleBuffer);
		}
		GPIO_WriteBit(GPIOC,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_8)));
		_delay_ms(100);
		GPIO_WriteBit(GPIOC,GPIO_Pin_9,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_9)));
		_delay_ms(200);
	}
}



