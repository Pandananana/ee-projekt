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
    OCR1A = 0;

    // ADC set uo
    ADC_init();
    
    // Uart set up
    uart0_Init(MYUBBRF);
    char send[10];
    // sprintf(send,"init");
    // putsUART0(send);
}

int main(void)
{
    init();
    sei();

    float uvals, yvals = 0;
    float y[3] = {0,0,0};

    while (1)
    {
        if (flag_ADC==1)
        {
            y[2] = y[1];
            y[1] = y[0];
            uvals = 22.11 * ADC_new[0] - 44.15 * ADC_new[1] + 22.05 * ADC_new[2];
            yvals = 1.996 * y[1] - 0.9959 * y[2];
            y[0] = uvals + yvals;
            OCR1A = y[0];
            flag_ADC=0;
        }   
    }
}



