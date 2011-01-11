#include <stm32f10x.h>
#include <stdlib.h>

#include <stdio.h>

#include "calc.h"
#include "stack.h"
#include "usart.h"

#define CMD_SIN1	's'
#define CMD_SIN2	'i'
#define CMD_SIN3	'n'

#define CMD_COS1	'c'
#define CMD_COS2	'o'
#define CMD_COS3	's'

#define CMD_TAN1	't'
#define CMD_TAN2	'a'
#define CMD_TAN3	'n'

#define CMD_LOG1	'l'
#define CMD_LOG2	'o'
#define CMD_LOG3	'g'

#define CMD_LN1		'l'
#define CMD_LN2		'n'

#define OP_SIN		's'
#define OP_COS		'c'
#define OP_TAN		't'
#define OP_LOG		'l'
#define OP_LN		'n'
#define CMD_SQRT	1
#define CMD_ANS		1

#define CMD_DOUBLE	1
#define CMD_POW		1

#define OP_PLUS		'+'
#define OP_MINUS	'-'
#define OP_MUL		'*'
#define OP_DIV		'/'

u8 priority(char ch)
{
	if(
		(ch==OP_SIN)||
		(ch==OP_COS)||
		(ch==OP_TAN)
		)
		return 3;
	else if(
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


u8 is_prealpha(char ch)
{
	if(
		(ch==CMD_SIN1)||
		(ch==CMD_COS1)||
		(ch==CMD_TAN1)||
		(ch==CMD_LOG1)||
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

u8 is_alpha(char ch)
{
	if(
		(ch>='a'&&ch<='z')||
		(ch>='A'&&ch<='z')
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

void Infix2Postfix(char *infix,char *postfix)
{
	struct stack_char sym;
	empty_stack_char(&sym);
	
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
			push_char(&sym,*infix);
			infix++;
		}
		if(*infix==')')
		{
			char tmp=pop_char(&sym);
			while(tmp!='(')
			{
				*postfix=tmp;
				postfix++;
				*postfix=' ';
				postfix++;
				tmp=pop_char(&sym);
			}
			infix++;
		}
		if(is_prealpha(*infix))//reduce fn form
		{
			char *ptr=infix;
			while(is_alpha(*ptr))
				ptr++;
			if((ptr-infix)==2)
			{
				
			}
			else if((ptr-infix)==3)
			{
				if(
					(*infix==CMD_SIN1)&&
					(*(infix+1)==CMD_SIN2)&&
					(*(infix+2)==CMD_SIN3)
					)
				{
					infix+=2;
					*infix=OP_SIN;
				}
				else if(
					(*infix==CMD_COS1)&&
					(*(infix+1)==CMD_COS2)&&
					(*(infix+2)==CMD_COS3)
					)
				{
					infix+=2;
					*infix=OP_COS;
				}
				else if(
					(*infix==CMD_TAN1)&&
					(*(infix+1)==CMD_TAN2)&&
					(*(infix+2)==CMD_TAN3)
					)
				{
					infix+=2;
					*infix=OP_TAN;
				}
				else if(
					(*infix==CMD_LOG1)&&
					(*(infix+1)==CMD_LOG2)&&
					(*(infix+2)==CMD_LOG3)
					)
				{
					infix+=2;
					*infix=OP_LOG;
				}
			}
			else
			{
			}
		}
		if(is_op(*infix)||is_prealpha(*infix))
		{
			if(is_stack_empty_char(&sym))
			{
				push_char(&sym,*infix);
			}
			else
			{
				char tmp=pop_char(&sym);
				while(priority(tmp)>=priority(*infix))
				{
					*postfix=tmp;
					postfix++;
					*postfix=' ';
					postfix++;
					if(!is_stack_empty_char(&sym))
						tmp=pop_char(&sym);
					else
						tmp=0;
				}
				push_char(&sym,tmp);
				push_char(&sym,*infix);
			}
			infix++;
		}
	}
	while(!is_stack_empty_char(&sym))
	{
		char a=pop_char(&sym);
		*postfix=a;
		postfix++;
		*postfix=' ';
		postfix++;
	}
	*postfix='\0';
}


#define NUMBER_LENGTH_BUFFER	20
float EvalPostfix(char *postfix,float *realans,float *imagans)
{
	//char buf[50];/////////
	float svalue;//////////
		
	struct stack_float real,imag;
	empty_stack_float(&real);
	empty_stack_float(&imag);
	
	while(*postfix)
	{
		while(*postfix==' ')
			postfix++;
		if(is_digit(*postfix))
		{
			char buff[NUMBER_LENGTH_BUFFER];
			char *buffptr=buff;
			u8 is_real;
			float value=0;
			while(is_digit(*postfix))
			{
				*buffptr=*postfix;
				postfix++;
				buffptr++;
			}
			buffptr--;
			if(*buffptr=='i')
			{
				is_real=0;
				if(buffptr==buff)	value=1;
			}
			else
			{
				is_real=1;
				buffptr++;
			}
			*buffptr='\0';
			if(value==0)	value=strtod(buff,NULL);
			if(is_real)
			{
				push_float(&real,value);
				push_float(&imag,0);
			}
			else
			{
				push_float(&real,0);
				push_float(&imag,value);
			}
		}
		else if(is_op(*postfix))
		{
			float	real1,
					real2,
					imag1,
					imag2,
					realresult=0,
					imagresult=0;
			
			real1=pop_float(&real);
			real2=pop_float(&real);
			imag1=pop_float(&imag);
			imag2=pop_float(&imag);
			
			switch(*postfix)
			{
				float divden;
				case OP_PLUS	:
					realresult=real1+real2;
					imagresult=imag1+imag2;
					break;
				case OP_MINUS	:
					realresult=real2-real1;
					imagresult=imag2-imag1;
					break;
				case OP_MUL		:
					realresult=(real1*real2)-(imag1*imag2);
					imagresult=(real1*imag2)+(real2*imag1);
					break;
				case OP_DIV		:
					divden=(real1*real1)+(imag1*imag1);
					realresult=(real2*real1)+(imag2*imag1);
					realresult=realresult/divden;
					imagresult=(imag2*real1)-(real2*imag1);
					imagresult=imagresult/divden;
					break;
			}
			push_float(&real,realresult);
			push_float(&imag,imagresult);
			postfix++;
		}
		else if(is_prealpha(*postfix))
		{
			float	real1,
					//imag1,
					realresult=0;
					//imagresult;
					
			real1=pop_float(&real);
			//imag1=pop_float(&imag);
			
			switch(*postfix)
			{
				case OP_SIN		:
					realresult=approx_sin(real1);
					break;
				case OP_COS		:
					realresult=approx_cos(real1);
					break;
				case OP_TAN		:
					realresult=approx_sin(real1)/approx_cos(real1);
					break;
				case OP_LOG		:
					realresult=approx_sin(real1);
					break;
				case OP_LN		:
					realresult=approx_sin(real1);
					break;
			}
			push_float(&real,realresult);
			postfix++;
		}
		else if(*postfix)
		{
			postfix++;
		}
	}
	
	while(!is_stack_empty_float(&real))
	{
		svalue=pop_float(&real);
		*realans=svalue;
		//sprintf(buf,"%f",svalue);
		//USART_Send_Str(USART1,buf);
		//USART_Send_Str(USART1,"\t");
		svalue=pop_float(&imag);
		*imagans=svalue;
		//sprintf(buf,"%f",svalue);
		//USART_Send_Str(USART1,buf);
		//USART_Send_Str(USART1,"i\r\n");
	}
	return 0;
}


