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
    // init_fast_pwm();
    init_T3_fast_pwm();
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

    OCR3B = 0;
    PORTB = (1 << PB4);
    _delay_ms(2000);
    DDRB |= (1 << PB4);

    uint8_t OCR3C_mem[5] = {0};
    uint8_t motor_stop = 0;

    uint16_t test_count = 0;

    float ref_motor = 512.0, ref_buck = 247.0;
    uint16_t PWM_TOP = 100, PWM_buck;
    while (1)
    {
        if (flag_ADC == 1)
        {
            if (flag_ADC2 == 1)
            {
                if (motor_stop)
                {
                    OCR3B = 0;
                }
                else
                {
                    OCR3B = round(control(ref_motor, (float)ADC_new));
                }
            }

            if (flag_ADC2 == 2)
            {
                PWM_buck = BUCK_control((int)ref_buck, PWM_TOP, ADC_new, PWM_buck);
                OCR3C = PWM_buck;
                OCR3C_mem[4] = OCR3C_mem[3];
                OCR3C_mem[3] = OCR3C_mem[2];
                OCR3C_mem[2] = OCR3C_mem[1];
                OCR3C_mem[1] = OCR3C_mem[0];
                OCR3C_mem[0] = OCR3C;

                if (OCR3C_mem[0] >= 95 && OCR3C_mem[1] >= 95 && OCR3C_mem[2] >= 95 && OCR3C_mem[3] >= 95 && OCR3C_mem[4] >= 95)
                {
                    motor_stop = 1;
                }
                else
                {
                    motor_stop = 0;
                }

                test_count++;
                if (test_count >= 500)
                {
                    sprintf(send, "%d, %d, %d, %d, %d\n", OCR3C_mem[0], OCR3C_mem[1], OCR3C_mem[2], OCR3C_mem[3], OCR3C_mem[4]);
                    putsUART0(send);
                    test_count = 0;
                }
            }
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
        }
    }
}
