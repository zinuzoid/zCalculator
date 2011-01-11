/*------------------------------------------------------------------------------------------------
** Program 	:	fixparse.h
** Project	:	Realtime
** CPU		:	STM32F100
** Date		:	12/1/2011
** Modify	:	Jetsada Machom <Zinuzoid Corporation Co.,Ltd.>
** Copyright:	
** Note 	:	
------------------------------------------------------------------------------------------------*/

void Infix2Postfix(char *infix,char *postfix);
void EvalPostfix(char *postfix,double *realans,double *imagans);



