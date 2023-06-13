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
    // Set data direction on pinb6 to output
    DDRB |= (1<<PB6);
    // Set Wave Gen Mode to Fast PWM with OCR1A top
    TCCR1A = 1<<COM1C1 | 1<<COM1B1 | 1<<WGM11 | 1<<WGM10;
	TCCR1B = 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	// 160 kHz at 16Mhz
	OCR1A = 100;
}
void init_T3_fast_pwm() {
    // Set data direction on pinb6 to output
    DDRE |= (1<<DDE4)|(1<<DDE5);
    // Set Wave Gen Mode to Fast PWM with OCR1A top
    TCCR3A = 1<<COM3C1 | 1<<COM3B1 | 1<<WGM31 | 1<<WGM30;
	TCCR3B = 1<<WGM33 | 1<<WGM32 | 1<<CS30;
	// 160 kHz at 16Mhz
	OCR3A = 100;
}

