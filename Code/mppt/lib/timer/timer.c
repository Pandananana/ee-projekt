#include <avr/io.h>
#include "timer.h"
/*
void initTimer1(unsigned int cmpvalue){ // Bruges ikke
	// Timer Mode 4, Prescaling = 8
	TCCR1B |= (1<<WGM12) | (1<<CS10); // CTC & No prescaler
	// Set compare match value: 9500Hz = 1683
	
	OCR1A = cmpvalue; //cmpvalue = 1683. 9500Hz
	OCR1B = cmpvalue; //b�de A og B er n�dvendig fordi ADC trigger signal p� timer 1 er match A, men ctc mode clear p� match B
	
	TIMSK1 |= (1<<OCIE1B);
}

void init_phasecorrect(){
	DDRB|=(1<<DDB7); //udgangen aktiveres
	TCCR0A|=(1<<WGM00)|(1<<COM0A1); //PWM phase correct set
	TCCR0B|=(1<<CS02); //No prescaler
	OCR0A |= 51; //OCR0A = Top value for counter. V�rdien overskrives senere
	TCNT0 = 0;
}*/

void init_fast_pwm() {
	// Set data direction on pinb6 to output
	DDRB |= (1<<PB5);
	// Set Wave Gen Mode to Fast PWM
	TCCR1A |= (1<<WGM11)|(1<<WGM10)|(1<<COM1A1);
	// Set prescaling to 1
	TCCR1B |= (1<<WGM12)|(1<<CS10);
	OCR1A = 512; 
}