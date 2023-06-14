 #include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h> 

void uart0_Init(unsigned int ubrr){
	UCSR0A = (1<<U2X0); // Double speed
	// Enable recive and transmit
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	// Frame: 1 start bit, 8 data bit, no parity:
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);
	// Baud rate values up to 16 bit therefore to registers	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
}

char getchUART0(void){
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;
}

void putchUART0(char tx){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = tx;
}
void putsUART0(char *ptr){
	while(*ptr){
		putchUART0(*ptr);
		ptr++;
	}
	
}

void UART0_RX_INT_Init(){
	UCSR0B |= (1<<RXCIE0); // Enable interupt at UART0
}