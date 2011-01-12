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

#include "calc.h"
#include "stm32f10x_it.h"

#define PI			3.1415926535897932384626433832795
#define PI2			6.283185307179586476925286766559
#define PIDIV2		1.5707963267948966192313216916398

#define LN10		2.3025850929940456840179914546844

#define EPS_DOUBLE	0.00000000000000022204460492503131

#define SIN_ITERATION 9
#define COS_ITERATION 9
#define EXP_ITERATION 19
#define LN_ITERATION 100

const double _exp_square_table[10]=
	{
		2.71828182845904550000000000000000,	//e  1
		7.38905609893065040000000000000000,	//e  2
		54.59815003314423600000000000000000,	//e  4
		2980.95798704172830000000000000000000,	//e  8
		8886110.52050787210000000000000000000000,	//e 16
		78962960182680.68700000000000000000000000000000,	//e 32
		6235149080811616700000000000.00000000000000000000000000000000,	//e 64
		38877084059945954000000000000000000000000000000000000000.00000000000000000000000000000000,	//e128
		1511427665004103500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.00000000000000000000000000000000,	//e256
		2284413586539756500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.00000000000000000000000000000000,	//e512
	};
	
const double _invfac_table[19]=
	{
		1.00000000000000000000000000000000,	//1/ 0!
		1.00000000000000000000000000000000,	//1/ 1!
		0.50000000000000000000000000000000,	//1/ 2!
		0.16666666666666666000000000000000,	//1/ 3!
		0.04166666666666666400000000000000,	//1/ 4!
		0.00833333333333333320000000000000,	//1/ 5!
		0.00138888888888888890000000000000,	//1/ 6!
		0.00019841269841269841000000000000,	//1/ 7!
		0.00002480158730158730200000000000,	//1/ 8!
		0.00000275573192239858930000000000,	//1/ 9!
		0.00000027557319223985888000000000,	//1/10!
		0.00000002505210838544172000000000,	//1/11!
		0.00000000208767569878681000000000,	//1/12!
		0.00000000016059043836821613000000,	//1/13!
		0.00000000001147074559772972500000,	//1/14!
		0.00000000000076471637318198164000,	//1/15!
		0.00000000000004779477332387385300,	//1/16!
		0.00000000000000281145725434552060,	//1/17!
		0.00000000000000015619206968586225,	//1/18!
	};
	
const double _atan_table[]=
{
	+3.33333333333329318027e-01,
	-1.99999999998764832476e-01,
	+1.42857142725034663711e-01,
	-1.11111104054623557880e-01,
	+9.09088713343650656196e-02,
	-7.69187620504482999495e-02,
	+6.66107313738753120669e-02,
	-5.83357013379057348645e-02,
	+4.97687799461593236017e-02,
	-3.65315727442169155270e-02,
	+1.62858201153657823623e-02
};

const double _atanhi_table[]={
	4.63647609000806093515e-01,
	7.85398163397448278999e-01,
	9.82793723247329054082e-01,
	1.57079632679489655800e+00
};

const double _atanlo_table[]={
	2.26987774529616870924e-17,
	3.06161699786838301793e-17,
	1.39033110312309984516e-17,
	6.12323399573676603587e-17
};

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

double degtorad(double deg)
{
	return deg*0.01745329252;//(PI/180)
}

double zmodf(double val,double div)
{
	double fraction;
	fraction=val/div;
	fraction=(double)(s32)fraction;
	fraction=fraction*div;
	fraction=val-fraction;
	return fraction;
}

double zabsf(double val)
{
	if(val>=0)
		return val;
	else
		return -val;
}
//End Internal Fn///////////////////////////


//Trigonometric/////////////////////////////
double approx_sin(double rad)
{
	double ans=0,x2;
	u8 i;
	
	//move to [-2pi , 2pi]
	rad=zmodf(rad,PI2);
	
	//move to [-pi , pi]
	if(rad>=PI)
		rad=rad-PI2;
	else if(rad<=-PI)
		rad=rad+PI2;
		
	//move to [pi/2 , pi/2]
	if(rad>=PIDIV2)
		rad=PI-rad;
	else if(rad<=-PIDIV2)
		rad=-PI-rad;
	
	x2=rad*rad;
	for(i=1;i<=SIN_ITERATION;i++)
	{
		ans+=neg_pow(i+1)*rad*_invfac_table[i*2-1];
		rad=rad*x2;
	}
	return ans;
}

double approx_sind(double deg)
{
	return approx_sin(degtorad(deg));
}

double approx_cos(double rad)
{
	return approx_sin(rad+PIDIV2);
}

double approx_cosd(double deg)
{
	return approx_cos(degtorad(deg));
}

double approx_tan(double rad)
{
	return approx_sin(rad)/approx_cos(rad);
}

double approx_tand(double deg)
{
	return approx_tan(degtorad(deg));
}

double approx_atan(double val)
{
	double x=zabsf(val),z,y,w,s1,s2;
	u8 id;
	if(x<0.4375)
	{
		id=4;
	}
	else if(x<0.6875)
	{
		id=0;
		y=(2*x-1)/(2+x);
	}
	else if(x<1.1875)
	{
		id=1;
		y=(x-1)/(x+1);
	}
	else if(x<2.4375)
	{
		id=2;
		y=(x-1.5)/(1+1.5*x);
	}
	else
	{
		id=3;
		y=-1/x;
	}
	z=y*y;
	w=z*z;
	
	s1=z*(_atan_table[0]+w*(_atan_table[2]+w*(_atan_table[4]+w*(_atan_table[6]+w*(_atan_table[8]+w*_atan_table[10])))));
	s2=w*(_atan_table[1]+w*(_atan_table[3]+w*(_atan_table[5]+w*(_atan_table[7]+w*_atan_table[9]))));
	
	if(id>3)
		return (y-y*(s1+s2));
	else
	{
		z=_atanhi_table[id]-((y*(s1+s2)-_atanlo_table[id])-y);
		if(val<0)
			return -z;
		else
			return z;
	}
}

double approx_asin(double val)
{
	return approx_atan(val/approx_sqrt(1-val*val));
}

double approx_acos(double val)
{
	return (PIDIV2-approx_asin(val));
}
//End Trigonometric/////////////////////////

double approx_pow(double base,double power)
{
	return approx_exp(power*approx_ln(base));
}

double approx_sqrt(double val)
{
	return approx_pow(val,0.5);
}

void approx_sqrti(double val,double *realans,double *imagans)
{
	double result;
	result=approx_pow(zabsf(val),0.5);
	if(val>=0)
	{
		*realans=result;
		*imagans=0;
	}
	else
	{
		*realans=0;
		*imagans=result;
	}
}

double approx_exp(double power)
{
	u8 i;
	u32 int_part;
	double frac_part;
	
	double xn=1;
	double result=0;
	
	int_part=(u32)power;
	frac_part=power -(double)int_part;
	
	
	if(int_part>512)	UsageFault_Handler();
	
	//take taylor series x=0
	for(i=0;i<EXP_ITERATION;i++)
	{
		result+=xn*_invfac_table[i];
		xn=xn*frac_part;
	}
	//end take taylor series
	
	//get from table
	for(i=0;i<10;i++)
	{
		if(int_part&((u32)1<<i))
		{
			result*=_exp_square_table[i];
		}
	}
	//end get from table
	
	return result;
}

void approx_expi(double real,double imag,double *realans,double *imagans)
{
	double mul;
	mul=approx_exp(real);
	*realans=mul*approx_cos(imag);
	*imagans=mul*approx_sin(imag);
}

double approx_ln(double val)
{
	//use Newton-Raphson
	double y0,y1,ey;
	u8 count;
	
	y0=0;
	y1=1;
	
	while(
			(y1>y0+EPS_DOUBLE)||
			(y1<y0-EPS_DOUBLE)
		)
	{
		y0=y1;
		ey=approx_exp(y1);
		y1=y1-(ey-val)/ey;
		
		if(count>LN_ITERATION)	break;
		count++;
	}
	
	return y1;
}

void approx_lni(double real,double imag,double *realans,double *imagans)
{
	*realans=approx_ln(approx_sqrt(real*real+imag*imag));
	*imagans=approx_atan(imag/real);
}

double approx_log(double val)
{
	return approx_ln(val)/LN10;
}

void approx_logi(double real,double imag,double *realans,double *imagans)
{
	approx_lni(real,imag,realans,imagans);
	*realans=*realans/LN10;
	*imagans=*imagans/LN10;
}









