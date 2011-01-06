#include <stm32f10x.h>

#include "stack.h"
#include "usart.h"
#include "stm32f10x_it.h"

#define	STACK_EMPTY	(s8)-1

void empty_stack(struct stack *s)
{
	s->top=STACK_EMPTY;
}

u8 is_stack_empty(struct stack *s)
{
	if(s->top==STACK_EMPTY)
		return 1;
	else
		return 0;
}

void push(struct stack *s,char value)
{
	s->top++;
	s->value[s->top]=value;
}

char pop (struct stack *s)
{
	if(!is_stack_empty(s))
	{
		char out;
		out=s->value[s->top];
		s->top--;
		return out;
	}
	else
	{
		UsageFault_Handler();
		return 0;
	}
}

void stack_display(struct stack s)
{
	USART_Send_Str(USART1,"\r\n");
	while(s.top!=STACK_EMPTY)
	{
		USART_Send_Ch(USART1,s.value[s.top]);
		USART_Send_Ch(USART1,' ');
		s.top--;
	}
	USART_Send_Str(USART1,"\r\n");
}

void empty_stackfloat(struct stackfloat *s)
{
	s->top=STACK_EMPTY;
}

u8 is_stackfloat_empty(struct stackfloat *s)
{
	if(s->top==STACK_EMPTY)
		return 1;
	else
		return 0;
}

void pushfloat(struct stackfloat *s,float value)
{
	s->top++;
	s->value[s->top]=value;
}

float popfloat(struct stackfloat *s)
{
	float out;
	out=s->value[s->top];
	s->top--;
	return out;
}



