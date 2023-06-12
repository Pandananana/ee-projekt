#include <avr/io.h>
#include "timer.h"

void init_fast_pwm() {
    // Set data direction on pinb6 to output
    DDRB |= (1<<PB6);
    // Set Wave Gen Mode to Fast PWM with OCR1A top
    TCCR1A = (1<<COM1B1)|(1<<WGM11)|(1<<WGM10);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS10);
	// 160 kHz at 16Mhz
	OCR1A = 270;
}