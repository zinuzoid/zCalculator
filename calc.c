#include <stm32f10x.h>

#include "stack.h"

#define CMD_SIN		1
#define CMD_COS		1
#define CMD_TAN		1
#define CMD_SQRT	1
#define CMD_LOG		1
#define CMD_ANS		1

#define CMD_DOUBLE	1
#define CMD_POW		1

u8 priority(char ch)
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
		(ch=='/')
		//(ch==CMD_POW)
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
		(ch=='.')||
		(ch=='i')
		)
		return 1;
	else
		return 0;
}

void infix2postfix(char *infix,char *postfix)
{
	struct stack sym;
	empty_stack(&sym);
	
	while(*infix)
	{
		while(*infix==' ')
			infix++;
		if(is_digit(*infix))
		{
			while(is_digit(*infix))
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
			push(&sym,*infix);
			infix++;
		}
		if(*infix==')')
		{
			char tmp=pop(&sym);
			while(tmp!='(')
			{
				*postfix=tmp;
				postfix++;
				*postfix=' ';
				postfix++;
				tmp=pop(&sym);
			}
			infix++;
		}
		if(is_op(*infix))
		{
			stack_display(sym);
			if(is_stack_empty(&sym))
			{
				push(&sym,*infix);
			}
			else
			{
				char tmp=pop(&sym);
				while((priority(tmp)>=priority(*infix))&&!is_stack_empty(&sym))
				{
					*postfix=tmp;
					postfix++;
					*postfix=' ';
					postfix++;
					tmp=pop(&sym);
				}
				push(&sym,tmp);
				push(&sym,*infix);
			}
			infix++;
		}
	}
	while(!is_stack_empty(&sym))
	{
		char a=pop(&sym);
		*postfix=a;
		postfix++;
		*postfix=' ';
		postfix++;
	}
	*postfix='\0';
}


