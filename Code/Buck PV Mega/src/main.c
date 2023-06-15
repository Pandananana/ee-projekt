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
#define PWM_TOP 160
#define PWM_BOT 0

void init()
{
    init_fast_pwm();
    // 100 kHz at 16Mhz
    OCR1A = PWM_TOP;

    // ADC set up
    ADC_init();
}

int main(void)
{
    init();
    sei();

    uart0_Init(MYUBBRF);
    char send[32];

    int ref = 256;

    int OCR1B_signed = (PWM_TOP - 1);

    OCR1B = OCR1B_signed;

    while (1)
    {
        _delay_ms(1);
        if (ADC_new > ref)
        {
            OCR1B_signed++;
        }
        else if (ADC_new < ref)
        {
            OCR1B_signed--;
        }

        if (OCR1B_signed > PWM_TOP)
        {
            OCR1B_signed = PWM_TOP-1;
        }
        else if (OCR1B_signed < 0)
        {
            OCR1B_signed = 0;
        }
        OCR1B = OCR1B_signed;
    }
}
