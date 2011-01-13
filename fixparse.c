/*------------------------------------------------------------------------------------------------
** Program 	:	fixparse.c
** Project	:	Realtime
** CPU		:	STM32F100
** Date		:	12/1/2011
** Modify	:	Jetsada Machom <Zinuzoid Corporation Co.,Ltd.>
** Copyright:	
** Note 	:	
------------------------------------------------------------------------------------------------*/

#include <stm32f10x.h>
#include <stdlib.h>

#include "calc.h"
#include "stack.h"
#include "usart.h"

#define CMD_SIN1	's'
#define CMD_SIN2	'i'
#define CMD_SIN3	'n'

#define CMD_SIND1	's'
#define CMD_SIND2	'i'
#define CMD_SIND3	'n'
#define CMD_SIND4	'd'

#define CMD_ASIN1	'a'
#define CMD_ASIN2	's'
#define CMD_ASIN3	'i'
#define CMD_ASIN4	'n'

#define CMD_COS1	'c'
#define CMD_COS2	'o'
#define CMD_COS3	's'

#define CMD_COSD1	'c'
#define CMD_COSD2	'o'
#define CMD_COSD3	's'
#define CMD_COSD4	'd'

#define CMD_ACOS1	'a'
#define CMD_ACOS2	'c'
#define CMD_ACOS3	'o'
#define CMD_ACOS4	's'

#define CMD_TAN1	't'
#define CMD_TAN2	'a'
#define CMD_TAN3	'n'

#define CMD_TAND1	't'
#define CMD_TAND2	'a'
#define CMD_TAND3	'n'
#define CMD_TAND4	'd'

#define CMD_ATAN1	'a'
#define CMD_ATAN2	't'
#define CMD_ATAN3	'a'
#define CMD_ATAN4	'n'

#define CMD_LOG1	'l'
#define CMD_LOG2	'o'
#define CMD_LOG3	'g'

#define CMD_LN1		'l'
#define CMD_LN2		'n'

#define CMD_EXP1	'e'
#define CMD_EXP2	'x'
#define CMD_EXP3	'p'

#define CMD_SQRT1	's'
#define CMD_SQRT2	'q'
#define CMD_SQRT3	'r'
#define CMD_SQRT4	't'

#define CMD_POW1	'p'
#define CMD_POW2	'o'
#define CMD_POW3	'w'

#define CMD_ANS1	'a'
#define CMD_ANS2	'n'
#define CMD_ANS3	's'

#define OP_SIN		's'
#define OP_SIND		'd'
#define OP_ASIN		'f'
#define OP_COS		'c'
#define OP_COSD		'v'
#define OP_ACOS		'b'
#define OP_TAN		't'
#define OP_TAND		'y'
#define OP_ATAN		'u'
#define OP_LOG		'l'
#define OP_LN		'n'
#define OP_EXP		'e'
#define OP_SQRT		'q'
#define OP_POW		'p'
#define OP_ANS		'a'

#define OP_PLUS		'+'
#define OP_MINUS	'-'
#define OP_MUL		'*'
#define OP_DIV		'/'

u8 priority(char ch)
{
	if(
		(ch==OP_SIN)||
		(ch==OP_COS)||
		(ch==OP_TAN)||
		(ch==OP_LOG)||
		(ch==OP_LN)||
		(ch==OP_EXP)
		)
		return 3;
	else if(
		(ch==OP_MUL)||
		(ch==OP_DIV)
		)
		return 2;
	else if(
		(ch==OP_PLUS)||
		(ch==OP_MINUS)
		)
		return 1;
	else
		return 0;
}


u8 is_prealpha(char ch)
{
	if(
		(ch==CMD_SIN1)||
		(ch==CMD_SIND1)||
		(ch==CMD_ASIN1)||
		(ch==CMD_COS1)||
		(ch==CMD_COSD1)||
		(ch==CMD_ACOS1)||
		(ch==CMD_TAN1)||
		(ch==CMD_TAND1)||
		(ch==CMD_ATAN1)||
		(ch==CMD_LOG1)||
		(ch==CMD_LN1)||
		(ch==CMD_EXP1)||
		(ch==CMD_SQRT1)||
		(ch==CMD_POW1)
		)
		return 1;
	else
		return 0;
}

u8 is_prealphaop(char ch)
{
	if(
		(ch==OP_SIN)||
		(ch==OP_SIND)||
		(ch==OP_ASIN)||
		(ch==OP_COS)||
		(ch==OP_COSD)||
		(ch==OP_ACOS)||
		(ch==OP_TAN)||
		(ch==OP_TAND)||
		(ch==OP_ATAN)||
		(ch==OP_LOG)||
		(ch==OP_LN)||
		(ch==OP_EXP)||
		(ch==OP_SQRT)||
		(ch==OP_POW)
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
		(ch==OP_PLUS)||
		(ch==OP_MINUS)||
		(ch==OP_MUL)||
		(ch==OP_DIV)
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
		(ch=='i')||
		(ch==OP_ANS)
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
		if(is_prealpha(*infix))//reduce fn form
		{
			char *ptr=infix;
			while(is_alpha(*ptr))
				ptr++;
			if((ptr-infix)==2)
			{
				if(
					(*infix==CMD_LN1)&&
					(*(infix+1)==CMD_LN2)
					)
				{
					infix+=1;
					*infix=OP_LN;
				}
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
				else if(
					(*infix==CMD_EXP1)&&
					(*(infix+1)==CMD_EXP2)&&
					(*(infix+2)==CMD_EXP3)
					)
				{
					infix+=2;
					*infix=OP_EXP;
				}
				else if(
					(*infix==CMD_POW1)&&
					(*(infix+1)==CMD_POW2)&&
					(*(infix+2)==CMD_POW3)
					)
				{
					infix+=2;
					*infix=OP_POW;
				}
				else if(
					(*infix==CMD_ANS1)&&
					(*(infix+1)==CMD_ANS2)&&
					(*(infix+2)==CMD_ANS3)
					)
				{
					infix+=2;
					*infix=OP_ANS;
				}
			}
			else if((ptr-infix)==4)
			{
				if(
					(*infix==CMD_SIND1)&&
					(*(infix+1)==CMD_SIND2)&&
					(*(infix+2)==CMD_SIND3)&&
					(*(infix+3)==CMD_SIND4)
					)
				{
					infix+=3;
					*infix=OP_SIND;
				}
				else if(
					(*infix==CMD_ASIN1)&&
					(*(infix+1)==CMD_ASIN2)&&
					(*(infix+2)==CMD_ASIN3)&&
					(*(infix+3)==CMD_ASIN4)
					)
				{
					infix+=3;
					*infix=OP_ASIN;
				}
				else if(
					(*infix==CMD_COSD1)&&
					(*(infix+1)==CMD_COSD2)&&
					(*(infix+2)==CMD_COSD3)&&
					(*(infix+3)==CMD_COSD4)
					)
				{
					infix+=3;
					*infix=OP_COSD;
				}
				else if(
					(*infix==CMD_ACOS1)&&
					(*(infix+1)==CMD_ACOS2)&&
					(*(infix+2)==CMD_ACOS3)&&
					(*(infix+3)==CMD_ACOS4)
					)
				{
					infix+=3;
					*infix=OP_ACOS;
				}
				else if(
					(*infix==CMD_TAND1)&&
					(*(infix+1)==CMD_TAND2)&&
					(*(infix+2)==CMD_TAND3)&&
					(*(infix+3)==CMD_TAND4)
					)
				{
					infix+=3;
					*infix=OP_TAND;
				}
				else if(
					(*infix==CMD_ATAN1)&&
					(*(infix+1)==CMD_ATAN2)&&
					(*(infix+2)==CMD_ATAN3)&&
					(*(infix+3)==CMD_ATAN4)
					)
				{
					infix+=3;
					*infix=OP_ATAN;
				}
				else if(
					(*infix==CMD_SQRT1)&&
					(*(infix+1)==CMD_SQRT2)&&
					(*(infix+2)==CMD_SQRT3)&&
					(*(infix+3)==CMD_SQRT4)
					)
				{
					infix+=3;
					*infix=OP_SQRT;
				}
			}
			else
			{
			}
		}
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
		if(is_op(*infix)||is_prealphaop(*infix))
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

double reallastans=0;
double imaglastans=0;
#define NUMBER_LENGTH_BUFFER	20
void EvalPostfix(char *postfix,double *realans,double *imagans)
{
	struct stack_double real,imag;
	empty_stack_double(&real);
	empty_stack_double(&imag);
	
	while(*postfix)
	{
		while(*postfix==' ')
			postfix++;
		if(is_digit(*postfix))
		{
			if(*postfix==OP_ANS)
			{
				push_double(&real,reallastans);
				push_double(&imag,imaglastans);
				postfix++;
			}
			else
			{
				char buff[NUMBER_LENGTH_BUFFER];
				char *buffptr=buff;
				u8 is_real;
				double value=0;
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
					push_double(&real,value);
					push_double(&imag,0);
				}
				else
				{
					push_double(&real,0);
					push_double(&imag,value);
				}
			}
		}
		else if(is_op(*postfix))
		{
			double	real1,
					real2,
					imag1,
					imag2,
					realresult=0,
					imagresult=0;
			
			real1=pop_double(&real);
			real2=pop_double(&real);
			imag1=pop_double(&imag);
			imag2=pop_double(&imag);
			
			switch(*postfix)
			{
				double divden;
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
			push_double(&real,realresult);
			push_double(&imag,imagresult);
			postfix++;
		}
		else if(is_prealphaop(*postfix))
		{
			double	real1,
					imag1,
					realresult=0,
					imagresult=0;
					
			real1=pop_double(&real);
			imag1=pop_double(&imag);
			
			switch(*postfix)
			{
				case OP_SIN		:
					realresult=approx_sin(real1);
					break;
				case OP_SIND	:
					realresult=approx_sind(real1);
					break;
				case OP_ASIN	:
					realresult=approx_asin(real1);
					break;
				case OP_COS		:
					realresult=approx_cos(real1);
					break;
				case OP_COSD	:
					realresult=approx_cosd(real1);
					break;
				case OP_ACOS	:
					realresult=approx_acos(real1);
					break;
				case OP_TAN		:
					realresult=approx_tan(real1);
					break;
				case OP_TAND	:
					realresult=approx_tand(real1);
					break;
				case OP_ATAN	:
					realresult=approx_atan(real1);
					break;
				case OP_LOG		:
					approx_logi(real1,imag1,&realresult,&imagresult);
					break;
				case OP_LN		:
					approx_lni(real1,imag1,&realresult,&imagresult);
					break;
				case OP_EXP		:
					approx_expi(real1,imag1,&realresult,&imagresult);
					break;
				case OP_SQRT	:
					approx_sqrti(real1,&realresult,&imagresult);
					break;
				case OP_POW		:
					realresult=approx_pow(real1,imag1);
					break;
			}
			push_double(&real,realresult);
			push_double(&imag,imagresult);
			postfix++;
		}
		else if(*postfix)
		{
			postfix++;
		}
	}
	
	while(!is_stack_empty_double(&real))
	{
		reallastans=pop_double(&real);
		*realans=reallastans;
		imaglastans=pop_double(&imag);
		*imagans=imaglastans;
	}
}


