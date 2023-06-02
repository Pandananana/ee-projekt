/**
 * Copyright (C) PlatformIO <contact@platformio.org>
 * See LICENSE for details.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <timer.h>

int main(void)
{   
    sei();
    init_fast_pwm();
    OCR1A = 0;
    
    
    while(1) {
        OCR1A++;
        _delay_ms(20);
        if (OCR1A >= 1023)
        {
            OCR1A = 0;
        }
        
    };
}