#include <stm32f10x.h>

struct stack
{
	char value[50];
	s8 top;
};

struct stackfloat
{
	float value[50];
	s8 top;
};

void empty_stack(struct stack *s);
u8 is_stack_empty(struct stack *s);
void push(struct stack *s,char value);
char pop (struct stack *s);
void stack_display(struct stack s);

void empty_stackfloat(struct stackfloat *s);
u8 is_stackfloat_empty(struct stackfloat *s);
void pushfloat(struct stackfloat *s,float value);
float popfloat(struct stackfloat *s);

