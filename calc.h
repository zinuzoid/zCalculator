/*------------------------------------------------------------------------------------------------
** Program 	:	calc.h
** Project	:	Realtime
** CPU		:	STM32F100
** Date		:	12/1/2011
** Modify	:	Jetsada Machom <Zinuzoid Corporation Co.,Ltd.>
** Copyright:	
** Note 	:	
------------------------------------------------------------------------------------------------*/

double approx_sin(double rad);
double approx_sind(double deg);
double approx_cos(double rad);
double approx_cosd(double deg);
double approx_tan(double rad);
double approx_tand(double deg);
double approx_asin(double val);
double approx_acos(double val);
double approx_atan(double val);

double approx_exp(double pow);
void approx_expi(double real,double imag,double *realans,double *imagans);
double approx_log(double val);
void approx_logi(double real,double imag,double *realans,double *imagans);
double approx_ln(double val);
void approx_lni(double real,double imag,double *realans,double *imagans);
double approx_pow(double base,double power);
double approx_sqrt(double val);

double zmodf(double val,double div);


