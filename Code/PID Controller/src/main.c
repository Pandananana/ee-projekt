#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "UART.h"
#include "ADC.h"
#include "Controler.h"
#define BAUD 115200
#define MYUBBRF F_CPU / 8 / BAUD - 1

void init()
{
    init_fast_pwm();

    // ADC set uo
    ADC_init();

    // Uart set up
    uart0_Init(MYUBBRF);
    // char send[32];
    // dtostrf(y[0], 4, 2, send);
    //  sprintf(send,"init");
    //  putsUART0(send);
}

int main(void)
{
    init();
    sei();

    char send[32];

    OCR1B = 0;
    _delay_ms(2000);
    DDRB |= (1 << PB4);

    uint16_t test_count = 0;

    float ref = 520.0;

    while (1)
    {
        if (flag_ADC == 1)
        {
            OCR1B = round(control(ref, (float)ADC_new));
            flag_ADC = 0;
            

            // if ((int)u[0] > 55 && (int)u[0] < 65)
            //     {
            //         if ((int)u[1] > 55 && (int)u[1] < 65)
            //             {
            //                 if ((int)u[1] > 55 && (int)u[1] < 65)
            //                     {
            //                         OCR1B = 80;
            //                         sprintf(send, "BOOST\n");
            //                         putsUART0(send);
            //                         _delay_ms(100);
            //                     }
            //             }
            //     }

            test_count++;
            if (test_count >= 10000)
            {
                sprintf(send, "%d, %d\n", (int)e[0], (int)u[0]);
                putsUART0(send);
                test_count = 0;
            }
        }
    }
}
