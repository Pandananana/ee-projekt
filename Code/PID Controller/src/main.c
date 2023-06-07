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

    char send[20];
    uint16_t terminal[1000], test_count = 0;

    double uvals = 0, yvals = 0;
    double y[3] = {0.0, 0.0, 0.0};
    double u[3] = {0.0, 0.0, 0.0};

    double num[3] = {
        0.2192639,
        -0.2191587,
        0
    };

    double den[3] = {
        1,
        -1,
        0
    };

    OCR1B = 71;
    _delay_ms(5000);
    DDRB |= (1<<PB4);

    uint16_t ref = 500;

    while (1)
    {
        if (flag_ADC == 1)
        {
            PORTB ^= (1<<PB4);
            // Find error
            u[0] = ref - ADC_new;

            // Calculate output
            uvals = num[0] * u[0] + num[1] * u[1] + num[2] * u[2];
            yvals = -den[1] * y[1] - den[2] * y[2];
            y[0] = uvals + yvals;
            
            OCR1B = (int)y[0];
            
            // dtostrf(y[0], 4, 2, send);
            // sprintf(send, "%d\n", ADC_new);
            // putsUART0(send);

            // Cycling outputs
            y[2] = y[1];
            y[1] = y[0];

            // Cycling inputs
            u[2] = u[1];
            u[1] = u[0];

            flag_ADC = 0;

            // if ((test_count > 999))
            // {
            //     sprintf(send, "\nDEBUG");
            //     putsUART0(send);
            //     for (uint16_t i = 0; i < 1000; i++)
            //     {
            //         sprintf(send, "%i\n", terminal[i]);
            //         putsUART0(send);
            //     }
            //     test_count = 0;
            // }
        }
    }
}
