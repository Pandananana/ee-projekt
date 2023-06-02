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
    OCR1A = 512;
    
    
    while(1);
}