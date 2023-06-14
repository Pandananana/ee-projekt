#include "ADC.h"

uint16_t ADC_new = 0;
volatile uint8_t flag_ADC = 0;
volatile uint8_t ADCflag = 0;
volatile uint16_t adcVoltage_new = 0;
volatile uint16_t adcVoltage_old = 0;
volatile uint16_t adcCurrent_new = 0;
volatile uint16_t adcCurrent_old = 0;
volatile uint8_t flagADC = 0;
volatile uint8_t counter = 0;
volatile uint16_t adc_array[100][2];

void CTC_Timer0_init(){
	TIMSK0 |=(1<<OCIE0A);
	OCR0A = 199; //10kHz 
	TCCR0B|= (1<<CS01); // set to prescaler to 8
	TCCR0A |= (1<<WGM01); // set to CTC mode
}

void ADC_init(){
    CTC_Timer0_init();
	ADCSRB = (1<<ADTS1)|(1<<ADTS0);//Timer/Counter0 Compare Match A
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0)|(1<<ADIE)|(1<<ADATE);
	ADMUX = (1<<REFS0)|(1<<ADLAR); //Sample on ADC 0 ore pin A0
    DDRF &= (0<<DDF0); //ADC signal on pin A0
}


ISR(TIMER0_COMPA_vect){  
}

ISR(ADC_vect){ // Runs when a new ADC reading is ready
    if(ADCflag==0) {
		adcVoltage_old = adcVoltage_new;
		adc_array[counter][0] = ADCH; //Read ADC input
		ADCflag = 1;
		ADMUX |= (1<<MUX0); //ADC input fra pin A1 (strøm)
	} 
	else if(ADCflag==1) {
		adcCurrent_old = adcCurrent_new; 
		adc_array[counter][1] = ADCH;
		ADCflag = 0;
		ADMUX &=~(1<<MUX0); //ADC input fra pin A0 (spænding)
		counter++;
	}
	if (counter == 99)
	{
		flagADC = 1;
		counter = 0;
	}
}