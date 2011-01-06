#include <stm32f10x.h>

#define	STACK_SIZE	50//max u8

struct stack_char
{
	char value[STACK_SIZE];
	u8 top;
};

struct stack_float
{
	float value[STACK_SIZE];
	u8 top;
};

void empty_stack_char(struct stack_char *s);
u8 is_stack_empty_char(struct stack_char *s);
void push_char(struct stack_char *s,char value);
char pop_char(struct stack_char *s);
void stack_display_char(struct stack_char s);

void empty_stack_float(struct stack_float *s);
u8 is_stack_empty_float(struct stack_float *s);
void push_float(struct stack_float *s,float value);
float pop_float(struct stack_float *s);

