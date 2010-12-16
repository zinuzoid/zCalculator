#include <stm32f10x.h>

#include "stack.h"

char priority(char ch)
{
	if(
		(ch=='*')||
		(ch=='/')
		)
		return 2;
	else if(
		(ch=='+')||
		(ch=='-')
		)
		return 1;
	else
		return 0;
}

#define CMD_SIN		0
#define CMD_COS		0
#define CMD_TAN		0
#define CMD_SQRT	0
#define CMD_LOG		0
#define CMD_ANS		0

#define CMD_DOUBLE	0
#define CMD_POW		0

u8 is_alpha(char ch)
{
	if(
		(ch==CMD_SIN)||
		(ch==CMD_COS)||
		(ch==CMD_TAN)||
		(ch==CMD_SQRT)||
		(ch==CMD_LOG)||
		(ch==CMD_ANS)
		)
		return 1;
	else
		return 0;
}


u8 is_postalpha(char ch)
{
	if(
		(ch==CMD_DOUBLE)
		)
		return 1;
	else
		return 0;
}


u8 is_op(char ch)
{
	if(
		(ch=='+')||
		(ch=='-')||
		(ch=='*')||
		(ch=='/')||
		(ch==CMD_POW)
		)
		return 1;
	else
		return 0;
}

u8 is_digit(char ch)
{
	if(
		(ch=='1')||
		(ch=='2')||
		(ch=='3')||
		(ch=='4')||
		(ch=='5')||
		(ch=='6')||
		(ch=='7')||
		(ch=='8')||
		(ch=='9')||
		(ch=='0')||
		(ch=='.')
		)
		return 1;
	else
		return 0;
}

void newinfix2postfix(char *infix,char *postfix)
{
	struct stack st;
	empty_stack(&st);
	
	while(*infix)
	{
		push(&st,*infix);
		infix++;
	}
	
	while(!is_stack_empty(&st))
	{
		char a=pop(&st);
		*postfix=a+1;
		postfix++;
	}
	
}

void infix2postfix(char *infix,char *postfix)
{
	struct stack st;
	empty_stack(&st);
	
	while(*infix)
	{
		while(*infix==' ')
		{
			infix++;
		}
		if(is_digit(*infix)||is_alpha(*infix))//||is_postalpha(*infix))
		{
			while(is_digit(*infix)||is_alpha(*infix))//||is_postalpha(*infix))
			{
				*postfix=*infix;
				postfix++;
				infix++;
			}
			*postfix=' ';
			postfix++;
		}
		if(*infix=='(')
		{
			push(&st,*infix);
			infix++;
		}
		if(*infix==')')
		{
			char a=pop(&st);
			while(a!='(')
			{
				*postfix=a;
				postfix++;
				*postfix=' ';
				postfix++;
				a=pop(&st);
			}
			infix++;
		}
		if(is_op(*infix))
		{
			if(is_stack_empty(&st))
			{
				push(&st,*infix);
			}
			else
			{
				char a=pop(&st);
				while(priority(a)>=priority(*infix))
				{
					*postfix=a;
					postfix++;
					*postfix=' ';
					postfix++;
					a=pop(&st);
				}
				push(&st,a);
				push(&st,*infix);
			}
			infix++;
		}
	}
	while(!is_stack_empty(&st))
	{
		char a=pop(&st);
		*postfix=a;
		postfix++;
		*postfix=' ';
		postfix++;
	}
	*postfix='\0';
}

