/*------------------------------------------------------------------------------------------------
** Program 	:	calc.c
** Project	:	Realtime
** CPU		:	STM32F100
** Date		:	12/1/2011
** Modify	:	Jetsada Machom <Zinuzoid Corporation Co.,Ltd.>
** Copyright:	
** Note 	:	
------------------------------------------------------------------------------------------------*/

#include <stm32f10x.h>

#include <math.h>

#define PI 3.1415926536

#define SIN_ITERATION 5
#define COS_ITERATION 5
#define EXP_ITERATION 11

//Internal Fn///////////////////////////////
double int_pow(double base,u8 pow)
{
	double ans=base;
	u8 i;
	
	if(pow==0)	return 1;
	
	for(i=2;i<=pow;i++)
	{
		ans*=base;
	}
	return ans;
}

double neg_pow(u8 val)
{
	if(val%2==0)
		return 1.0;
	return -1.0;
}

double fac(u8 n)
{
	double ans=1;
	u8 i;
	for(i=2;i<=n;i++)
	{
		ans*=i;
	}
	return ans;
}

double degtorad(double deg)
{
	return deg*0.01745329252;//(PI/180)
}
//End Internal Fn///////////////////////////


//Trigonometric/////////////////////////////
double approx_sin(double rad)
{
	/*
	double ans=0;
	u8 i;
	for(i=1;i<=SIN_ITERATION;i++)
	{
		ans+=neg_pow(i+1)*int_pow(rad,i*2-1)/fac(i*2-1);
		
	}
	return ans;
	*/
	return sin(rad);
}

double approx_sind(double deg)
{
	return approx_sin(degtorad(deg));
}

double approx_cos(double rad)
{
	/*
	double ans=1;
	u8 i;
	for(i=1;i<=COS_ITERATION-1;i++)
	{
		ans+=neg_pow(i)*int_pow(rad,i*2)/fac(i*2);
		
	}
	return ans;
	*/
	return cos(rad);
}

double approx_cosd(double deg)
{
	return approx_cos(degtorad(deg));
}

double approx_tan(double rad)
{
	return tan(rad);
}

double approx_tand(double deg)
{
	return approx_tan(degtorad(deg));
}
//End Trigonometric/////////////////////////


//Uncomplete////////////////////////////////
double approx_exp(double power)
{
	/*
	double ans=1;
	u8 i;
	for(i=1;i<=EXP_ITERATION-1;i++)
	{
		ans+=int_pow(pow,i)/fac(i);
	}
	return ans;
	*/
	return exp(power);
}

void approx_expi(double real,double imag,double *realans,double *imagans)
{
	double mul;
	mul=exp(real);
	*realans=mul*approx_cos(imag);
	*imagans=mul*approx_sin(imag);
}

double approx_ln(double val)
{
	return log(val);
}

void approx_lni(double real,double imag,double *realans,double *imagans)
{
	*realans=approx_ln(sqrt(real*real+imag*imag));	//////still use math.h
	*imagans=atan(imag/real);						//////still use math.h
}

double approx_log(double val)
{
	return log10(val);
}

double approx_pow(double base,double power)
{
	return pow(base,power);
}
//End Uncomplete////////////////////////////





