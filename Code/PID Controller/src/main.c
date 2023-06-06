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

    char send[6];

    float uvals = 0, yvals = 0;
    float y[3] = {0.0,0.0,0.0};
    float u[3] = {0.0,0.0,0.0};

    OCR1B = 30;
    _delay_ms(5000);

    int ref = 800;

    while (1)
    {
        if (flag_ADC==1)
        {
            // Find error
            u[0] = ref - ADC_new;

            // Calculate output
            uvals = 2.447 * u[0] - 4.888 * u[1] + 2.441 * u[2];
            yvals = 1.996 * y[1] - 0.9964 * y[2];
            y[0] = uvals + yvals;
            // dtostrf((int)y[0], 4, 2, send);
            // sprintf(send, "%s\n", &send);
            // putsUART0(send);
            OCR1B = (int)y[0];

            // Cycling outputs
            y[2] = y[1];
            y[1] = y[0];

            // Cycling inputs
            u[2] = u[1];
            u[1] = u[0];

            flag_ADC=0;
        }   
    }
}



