/*
 * USART.h
 *
 * Course number 62734
 *  Author: Anders s215453 and Oguzhan s215463
 */ 


#ifndef UART_H_
#define UART_H_

void uart0_Init(unsigned int ubrr);
char getchUART0(void);
void putchUART0(char tx);
void putsUART0(char *ptr);
void UART0_RX_INT_Init();



#endif /* UART_H_ */