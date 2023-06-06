#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "ADC.h"
#include "mppt.h"
#include "UART.h"

#define BAUD 115200
#define MYUBBRF F_CPU / 8 / BAUD - 1

#define NUM_READINGS 100 // Array index and size
#define ARRAY_SIZE 100

volatile uint16_t adcVoltage_new = 0;
volatile uint16_t adcVoltage_old = 0;
volatile uint16_t adcCurrent_new = 0;
volatile uint16_t adcCurrent_old = 0;
uint16_t voltage_new;
uint16_t voltage_old;
uint16_t current_new;
uint16_t current_old;

int desired_voltage = 5; 
int ADCflag = 0;

void init() {
	ADC_init();
	init_fast_pwm();
	sei();

	 // Uart set up
    uart0_Init(MYUBBRF);
}

int main(void)
{
	init();
	char send[32];
	//sprintf(send,"test");
	//putsUART0(send);

   while(1)
    {
		voltage_old = adcVoltage_old;
		voltage_new = adcVoltage_new;
		current_old = adcCurrent_old;
		current_new = adcCurrent_new;

		float power_old = calculatePower(voltage_old, current_old);
		float power_new = calculatePower(voltage_new, current_new);

		if (power_new > power_old) {
			// Increase voltage
			OCR1B++;
		} 
		else if (power_new < power_old) {
			// Decrease voltage
			OCR1B--;
		}
		else if (power_new == power_old)
		{
			OCR1B = OCR1B;
		}

		if (OCR1B>=320) {
			OCR1B = 320;
		}
		else if (OCR1B<=10) {
			OCR1B = 10;
		}
		

		//calcPWM(adcVoltage_new, desired_voltage); // Set timer 0 compare match value
		_delay_ms(100);
		sprintf(send,"%d\n",OCR1B);
		putsUART0(send);
	}
}

ISR(TIMER0_COMPA_vect){
}

ISR(ADC_vect) { // Runs when a new ADC reading is ready
	if(ADCflag==0) {
		ADMUX |= 0b000000; //ADC input fra pin A0 (spænding)
		adcVoltage_old = adcVoltage_new; //Track previous ADC value for compare
		adcVoltage_new = ADC; //Read ADC input
		ADCflag = 1;
	} 
	if(ADCflag==1) {
		ADMUX |= 0b000001; //ADC input fra pin A1 (strøm)
		adcCurrent_old = adcCurrent_new;
		adcVoltage_new = ADC; 
		ADCflag = 0;
	}
}
