#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "ADC.h"
#include "mppt.h"

#define NUM_READINGS 100 // Array index and size
#define ARRAY_SIZE 100

volatile uint16_t adcVoltage[NUM_READINGS];
volatile uint8_t adcIndex = 0;
volatile uint16_t current = 2; // Skal ogs� v�re en ADC m�ling. Hardcodet til 2A for nu.
float powerArray[ARRAY_SIZE];
int desired_voltage = 5; 


void init() {
	//ADC_init();
	//init_phasecorrect();
	init_fast_pwm();
	sei();
}

int main(void)
{
	init();
	
    while(1)
    {
			for (int i = 1; i < ARRAY_SIZE; i++) 
			{	
				float power_prev = calculatePower(adcVoltage[i - 1], current);
				float power_current = calculatePower(adcVoltage[i], current);
				
				if (power_current > power_prev) {
					// Increase voltage
					adcVoltage[i]++;
					} else {
					// Decrease voltage
					adcVoltage[i]--;
					}
			OCR0A = 75;
			//OCR0A = calcPWM(adcVoltage[i], desired_voltage); // Set timer 0 compare match value
			}
		}
}

ISR(TIMER0_COMPA_vect){
}

ISR(ADC_vect){ // Runs when a new ADC reading is ready
	adcVoltage[adcIndex] = ADC; // Read ADC into array
	powerArray[adcIndex] = calculatePower(adcVoltage[adcIndex], current);
	adcIndex++;
	if (adcIndex > NUM_READINGS) {
		adcIndex = 0;
	}
}
