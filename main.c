#include <stm32f10x.h>

#include <stdio.h>

#include <stdlib.h>

#include "main.h"
#include "delay.h"
#include "init.h"
#include "usart.h"
#include "stm32f10x_it.h"
#include "calc.h"

#include "task.h"

void testtask(u32 val)
{
	USART_Send_Str(USART1,"TESTTASK1:");
	USART_Send_Ch(USART1,val);
	USART_Send_Str(USART1,"\r\n");
}

void testtask2(u32 val)
{
	USART_Send_Str(USART1,"TESTTASK2:");
	USART_Send_Ch(USART1,val);
	USART_Send_Str(USART1,"\r\n");
}

TTASK ztask1;
TTASK ztask2;
TTASK ztask3;

int main(void)
{
	//char a[]="1+9-5*8/4+2*2\0";
	char a[50]="1+2 6-7";
	char b[50];
	
	RCCInit();
	GPIOInit();
	USARTInit();
	NVICInit();
	
	//////////////////////////////////////////////
	//task
	USART_Send_Str(USART1,"\r\n\r\n");
	
	TaskInit();
	TaskCreate(&ztask1,&testtask,'x');
	TaskCreate(&ztask2,&testtask2,'y');
	TaskCreate(&ztask3,&testtask2,'z');
	TaskRun();
	/////////////////////////////////////////////
	
	
	while(1);
	
	newinfix2postfix(a,b);
	
	USART_Send_Str(USART1,b);
	
	SysTick_Config(SystemCoreClock/1000);//ms
	
	USART_Send_Str(USART1,"\r\n");
	
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
			float tmp;
			char ctmp[50];
			ConsoleReaded=0;
			
			tmp=strtof(ConsoleBuffer,NULL);
			tmp=tmp*1.2;
			sprintf(ctmp,"%f",tmp);
			
			USART_Send_Str(USART1,"\r\n");
			USART_Send_Str(USART1,ctmp);
			USART_Send_Str(USART1,"\r\n");
			USART_Send_Str(USART1,COMMANDPROMPT);
			
			//USART_Send_Ch(USART1,'#');
			//USART_Send_Str(USART1,ConsoleBuffer);
		}
		
		GPIO_WriteBit(GPIOC,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_8)));
		_delay_ms(100);
		GPIO_WriteBit(GPIOC,GPIO_Pin_9,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_9)));
		_delay_ms(200);
		
		//USART_Send_Ch(USART1,'z');
		//USART_Send_Ch(USART2,'x');
	}
}



