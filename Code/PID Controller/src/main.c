/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include <timer.h>
#include "UART.h"
#include "ADC.h"

#define BAUD 19200
#define MYUBBRF F_CPU/8/BAUD-1





void init(){
    
    init_fast_pwm();
    OCR1A = 0;

    // ADC set uo
    ADC_init();

    // Uart set up
    uart0_Init(MYUBBRF);
    sei();
    //char send[10];
    //sprintf(send,"init");
    //putsUART0(send);
}


int main(void)
{   
    init();
    char send[10];
    
    while(1) {
        OCR1A++;
        _delay_ms(20);
        if (OCR1A >= 1022){
            OCR1A = 0;
        }

       /* if (flag_ADC == 1){
            sprintf(send,"ADC %i",ADC_new);
            putsUART0(send);
            flag_ADC = 0;
        }*/
             
    }
}


