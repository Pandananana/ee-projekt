#include <avr/io.h>
#include "ADC.h"
#include "mppt.h"

void ADC_init(){
	ADCSRB = (1<<ADTS1)|(1<<ADTS0);//Timer/Counter0 Compare Match A
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE)|(1<<ADATE); 
	ADMUX = (1<<REFS0)|(1<<REFS1); // Reference voltage of 2.56V 
	DDRF &= (0<<DDF0); //ADC voltage input signal on pin A0
	//DDRF &= (0<<DDF1); //ADC current input signal on pin A1
}