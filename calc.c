#include <stm32f10x.h>

#include <math.h>

#define PI 3.1415926536

#define SIN_ITERATION 5
#define COS_ITERATION 5
#define EXP_ITERATION 11

//Internal Fn///////////////////////////////
float int_pow(float base,u8 pow)
{
	float ans=base;
	u8 i;
	
	if(pow==0)	return 1;
	
	for(i=2;i<=pow;i++)
	{
		ans*=base;
	}
	return ans;
}

float neg_pow(u8 val)
{
	if(val%2==0)
		return 1.0;
	return -1.0;
}

float fac(u8 n)
{
	float ans=1;
	u8 i;
	for(i=2;i<=n;i++)
	{
		ans*=i;
	}
	return ans;
}

float degtorad(float deg)
{
	return deg*0.01745329252;//(PI/180)
}
//End Internal Fn///////////////////////////


//Trigonometric/////////////////////////////
float approx_sin(float rad)
{
	/*
	float ans=0;
	u8 i;
	for(i=1;i<=SIN_ITERATION;i++)
	{
		ans+=neg_pow(i+1)*int_pow(rad,i*2-1)/fac(i*2-1);
		
	}
	return ans;
	*/
	return sin(rad);
}

float approx_sind(float deg)
{
	return approx_sin(degtorad(deg));
}

float approx_cos(float rad)
{
	/*
	float ans=1;
	u8 i;
	for(i=1;i<=COS_ITERATION-1;i++)
	{
		ans+=neg_pow(i)*int_pow(rad,i*2)/fac(i*2);
		
	}
	return ans;
	*/
	return cos(rad);
}

float approx_cosd(float deg)
{
	return approx_cos(degtorad(deg));
}
//End Trigonometric/////////////////////////


//Uncomplete////////////////////////////////
float approx_exp(float power)
{
	/*
	float ans=1;
	u8 i;
	for(i=1;i<=EXP_ITERATION-1;i++)
	{
		ans+=int_pow(pow,i)/fac(i);
	}
	return ans;
	*/
	return exp(power);
}

float approx_ln(float val)
{
	return log(val);
}

float approx_log(float val)
{
	return log10(val);
}

float approx_pow(float base,float power)
{
	return pow(base,power);
}
//End Uncomplete////////////////////////////





