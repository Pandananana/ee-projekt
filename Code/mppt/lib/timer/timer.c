#include <avr/io.h>
#include "timer.h"

/*void initTimer1(unsigned int cmpvalue){ // Bruges ikke
	// Timer Mode 4, Prescaling = 8
	TCCR1B |= (1<<WGM12) | (1<<CS10); // CTC & No prescaler
	// Set compare match value: 9500Hz = 1683
	
	OCR1A = cmpvalue; //cmpvalue = 1683. 9500Hz
	OCR1B = cmpvalue; //b�de A og B er n�dvendig fordi ADC trigger signal p� timer 1 er match A, men ctc mode clear p� match B
	
	TIMSK1 |= (1<<OCIE1B);
}*/

void init_fast_pwm() {
    // Set data direction on pinb6 to output
    DDRB |= (1<<PB6);
    // Set Wave Gen Mode to Fast PWM with OCR1A top
    TCCR1A = 1<<COM1B1 | 1<<WGM11 | 1<<WGM10;
	TCCR1B = 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	// 160 kHz at 16Mhz
	OCR1A = 320;
}