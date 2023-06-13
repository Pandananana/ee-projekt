#ifndef ADC_H_
#define ADC_H_

// Include libraries
#include <avr/io.h>
#include <avr/interrupt.h>

// // Declare global varibel
uint16_t ADC_new;
volatile uint8_t flag_ADC, flag_ADC2;

// Declare functions
void CTC_Timer0_init();
void ADC_init();
ISR(TIMER0_COMPA_vect);
ISR(ADC_vect);

#endif /* ADC_H_ */