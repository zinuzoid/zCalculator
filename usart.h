#define USART_WaitSend(usartport)	while(USART_GetFlagStatus(usartport,USART_FLAG_TXE)==RESET)
#define USART_Send_Ch(usartport,ch)\
							USART_WaitSend(usartport);\
							USART_SendData(usartport,ch)

void USART_Send_Str(USART_TypeDef *usartport,char *str);


