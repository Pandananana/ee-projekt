#include "ADC.h"

uint16_t ADC_new = 0;
volatile uint8_t flag_ADC = 0,flag_ADC2 = 0 ;

void CTC_Timer0_init(){
	TIMSK0 |=(1<<OCIE0A);
	OCR0A = 99;
	TCCR0B|= (1<<CS01); // set to prescaler to 8
	TCCR0A |= (1<<WGM01); // set to CTC mode
}

void ADC_init(){
    CTC_Timer0_init();
	ADCSRB = (1<<ADTS1)|(1<<ADTS0);//Timer/Counter0 Compare Match A
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADIE)|(1<<ADATE);
	ADMUX = (1<<REFS0); //Sample on ADC 0 ore pin A0
    DDRF &= (0<<DDF0)&(0<<DDF1); //ADC signal on pin A0
}


ISR(TIMER0_COMPA_vect){
    
}


ISR(ADC_vect){ // Runs when a new ADC reading is ready
	static uint8_t count = 0;
    ADC_new = ADC;
    flag_ADC = 1;	
	count++;
	flag_ADC2 = 1;
	if(count == 8){
		ADMUX |= (1 << MUX0);
	}
	if (count == 9 || count >9)
	{
		ADMUX &=~(1<<MUX0);
		count = 0;
		flag_ADC2 = 2;
	}
}