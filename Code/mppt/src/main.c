#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "ADC.h"
#include "mppt.h"
#include "UART.h"

#define F_CPU 16000000UL
#define BAUD 115200
#define MYUBBRF F_CPU / 8 / BAUD - 1

#define NUM_READINGS 100 // Array index and size
#define ARRAY_SIZE 100

uint16_t voltage_new;
uint16_t voltage_old;
uint16_t current_new;
uint16_t current_old;
uint16_t desired_voltage = 5;
uint8_t flag = 0;

void init()
{
	ADC_init();
	init_fast_pwm();
	sei();
	uart0_Init(MYUBBRF); // Uart setup
						 // OCR1B = 150;
}

int main(void)
{
	init();
	char send[128];
	int flag = 0;
	while(flag==0){ // Calculate inital duty cycle
		OCR1B = calcPWM(adcVoltage_new, desired_voltage);
		if(OCR1B!=0)
		{
			flag = 1;
		}
	}

	while (1)
	{

		voltage_old = voltage_new;
		current_old = current_new;
		voltage_new = adcVoltage_new;
		current_new = adcCurrent_new;

		uint32_t power_old = voltage_old * current_old;
		uint32_t power_new = voltage_new * current_new;
		int delta_power = (int)power_new - (int)power_old;
		int delta_voltage = (int)voltage_new - (int)voltage_old;

		sprintf(send, "PWM: %i voltage: %i current: %i pnew: %ld pold: %ld\n", OCR1B, voltage_new, current_new, power_new, power_old);
		putsUART0(send);
		
		if (power_new > power_old)
		{
			if (voltage_new > voltage_old)
			{
				OCR1B++;
			}
			else if (voltage_new < voltage_old)
			{
				OCR1B--;
			}
		}
		else //Power new less than power old
		{
			if (voltage_new > voltage_old)
			{
				OCR1B++;
			}
			else if (voltage_new < voltage_old)
			{
				OCR1B--;
			}
		}

		if (OCR1B >= 320)
		{
			OCR1B = 320;
		}
		else if (OCR1B <= 10)
		{
			OCR1B = 10;
		}
	}
}
