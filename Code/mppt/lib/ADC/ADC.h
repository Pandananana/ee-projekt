#ifndef ADC_H_
#define ADC_H_

// Include libraries
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t adcVoltage_new;
volatile uint16_t adcVoltage_old;
volatile uint16_t adcCurrent_new;
volatile uint16_t adcCurrent_old;
volatile uint8_t flagADC;
volatile uint8_t counter;
uint16_t adc_array[100][2];


// Declare functions
void CTC_Timer0_init();
void ADC_init();
ISR(TIMER0_COMPA_vect);
ISR(ADC_vect);

#endif