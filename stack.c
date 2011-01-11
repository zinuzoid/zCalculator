#include <stm32f10x.h>

#include "stack.h"
#include "usart.h"
#include "stm32f10x_it.h"

#define	STACK_EMPTY	(u8)0


//////////////char///////////////
void empty_stack_char(struct stack_char *s)
{
	s->top=STACK_EMPTY;
}

u8 is_stack_empty_char(struct stack_char *s)
{
	if(s->top==STACK_EMPTY)
		return 1;
	else
		return 0;
}

void push_char(struct stack_char *s,char value)
{
	s->top++;
	s->value[s->top]=value;
}

char pop_char(struct stack_char *s)
{
	if(!is_stack_empty_char(s))
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
//////////////endchar///////////////

void stack_display_char(struct stack_char s)
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


/////////////double////////////////
void empty_stack_double(struct stack_double *s)
{
	s->top=STACK_EMPTY;
}

u8 is_stack_empty_double(struct stack_double *s)
{
	if(s->top==STACK_EMPTY)
		return 1;
	else
		return 0;
}

void push_double(struct stack_double *s,double value)
{
	s->top++;
	s->value[s->top]=value;
}

double pop_double(struct stack_double *s)
{
	if(!is_stack_empty_double(s))
	{
		double out;
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
/////////////enddouble////////////////


