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
#define PWM_TOP 100
#define PWM_BOT 0

void init()
{
    init_fast_pwm();
    // 100 kHz at 16Mhz
    OCR1A = PWM_TOP;

    uart0_Init(MYUBBRF);

    // ADC set up
    ADC_init();
}

int main(void)
{
    init();
    sei();

    float ref = 512.0;

    int OCR1B_signed = (PWM_TOP - 1);

    char send[32];
    uint16_t test_count = 0;

    OCR1B = OCR1B_signed;

    while (1)
    {
        OCR1B = 50;
        // _delay_ms(1);
        // if (ADC_new > ref)
        // {
        //     OCR1B_signed++;
        // }
        // else if (ADC_new < ref)
        // {
        //     OCR1B_signed--;
        // }

        // if (OCR1B_signed > PWM_TOP)
        // {
        //     OCR1B_signed = PWM_TOP;
        // }
        // else if (OCR1B_signed < 0)
        // {
        //     OCR1B_signed = 0;
        //     DDRB &= (0 << PB6);
        // }
        // else
        // {
        //     DDRB |= (1 << PB6);
        // }
        // OCR1B = OCR1B_signed;
        // test_count++;
        // if (test_count >= 1000)
        // {
        //     sprintf(send, "%d\n", ADC_new);
        //     putsUART0(send);
        //     test_count = 0;
        // }
    }
}
