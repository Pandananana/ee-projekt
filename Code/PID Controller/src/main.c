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
#define MYUBBRF F_CPU / 8 / BAUD - 1

int dc2tc(float duty_cycle)
{
    return round(duty_cycle / 100 * 1023);
}

void init()
{

    init_fast_pwm();
    OCR1A = 0;

    // ADC set uo
    ADC_init();

    // Uart set up
    uart0_Init(MYUBBRF);
    sei();
    // char send[10];
    // sprintf(send,"init");
    // putsUART0(send);
}

int main(void)
{
    init();
    OCR1A = dc2tc(100);
    char send[32];
    while (1)
    {
        sprintf(send,"%d,%d,%d\n",ADC_new[2], ADC_new[1], ADC_new[0]);
            putsUART0(send);
            _delay_ms(1000);

        // if (flag_ADC==1)
        // {
        //     sprintf(send,"%i,%i,%i",ADC_new[2], ADC_new[1], ADC_new[0]);
        //     putsUART0(send);
        //     flag_ADC=0;
        // }
    }
    

    // float uvals, yvals = 0;
    // float y[3] = {0,0,0};

    // while (1)
    // {
    //     if (flag_ADC)
    //     {
    //         y[2] = y[1];
    //         y[1] = y[0];
    //         uvals = 127.3 * ADC_new[0] - 254 * ADC_new[1] + 126.7 * ADC_new[2];
    //         yvals = 1.993 * y[1] - 0.9932 * y[2];
    //         y[0] = uvals + yvals;
    //         flag_ADC=0;
    //     }
    // }
}