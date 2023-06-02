#include "timer.h"

void initTimer1(uint16_t compareValue){
	// Timer Mode 4, Prescaling = 8
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	// Set compare match value: 9500Hz = 1683
	// A and B registers are needed, since ADC Trigger Signal on Timer 1 is Match B,
	// but CTC mode clears on Match A. Write to high byte first, then low (17.3)
	OCR1AH = (compareValue>>8);
	OCR1AL = (compareValue & 0x00FF);
	OCR1BH = (compareValue>>8);
	OCR1BL = (compareValue & 0x00FF);
}

void initTimer3(uint16_t compareValue){
	// Enable Mode 4 (CTC) and prescaling of 1 on Timer 3
	TCCR3B |= (1<<WGM32) | (1<<CS30);
	// Enable Compare Match A interrupt
	TIMSK3 |= (1<<OCIE3A);
	// Set compare match value: 15999 = 1ms
	OCR3AH = (compareValue>>8);
	OCR3AL = (compareValue & 0x00FF);
}

void init_pc_pwm() {
	// Set data direction on pinb7 to output
	DDRB |= (1<<PB7);
	// Set Wave Gen Mode to PWM, Phase Correct
	TCCR0A |= (1<<WGM00)|(1<<COM0A1);
	// Set prescaling to 8
	TCCR0B |= (1<<CS01);
}

void init_fast_pwm() {
    // Set data direction on pinb7 to output
	DDRB |= (1<<PB7);
    // Set Wave Gen Mode to PWM, Phase Correct
	TCCR0A |= (1<<WGM10)|(1<<COM1A1);
	// Set prescaling to 8
	TCCR0B |= (1<<CS11);
}