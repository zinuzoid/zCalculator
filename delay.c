#include <stm32f10x.h>

#include "stm32f10x_it.h"

void _delay_ms(uint32_t time)
{
    _timming=time;
    while(_timming);
}

