#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "UART.h"
#include "ADC.h"

#define BAUD 115200
#define MYUBBRF F_CPU / 8 / BAUD - 1

void init()
{
    init_fast_pwm();

    // ADC set uo
    ADC_init();
    
    // Uart set up
    uart0_Init(MYUBBRF);
    char send[32];
    // sprintf(send,"init");
    // putsUART0(send);
}

int main(void)
{
    init();
    sei();

    OCR1B = 90;
}



