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

uint16_t voltage_new_avg[5] = {0};
uint16_t current_new_avg[5] = {0};	
uint16_t voltage_old_avg;
uint16_t current_old_avg;
uint16_t voltage_avg = 0;
float voltage_avg_new;
float voltage_avg_old;
uint16_t current_avg = 0;
float current_avg_new;
float current_avg_old;
uint16_t voltage_new;
uint16_t voltage_old;
uint16_t current_new;
uint16_t current_old;
uint16_t desired_voltage = 5;
uint16_t OCR1B_old = 0;
uint8_t direction = 1;
uint8_t flag = 0;
float power_avg_old;
uint32_t power_avg = 0;
uint32_t delta_power;
uint16_t adc_voltage_old;
uint16_t adc_voltage_new;
uint16_t delta_voltage;
int dutycycle;

char voltage_str[16];
char current_str[16];

void init()
{
	ADC_init();
	init_fast_pwm();
	uart0_Init(MYUBBRF); // Uart setup
	sei();
	
}

int main(void)
{	
	init();
	char send[128];
	sprintf(send, "flag:\n");
	putsUART0(send);

	

	while (1)
	{
		while(flag==0){ // Calculate inital duty cycle
		OCR1B = calcPWM(adc_array[0][0], desired_voltage);
			if(OCR1B!=0)
			{
				flag = 1;
			}
		}

		if (flagADC == 1)
		{
			power_avg_old = (float)power_avg;
			power_avg = 0;
			for (int i = 0; i < 100; i++)
			{
				voltage_avg += adc_array[i][0];
				current_avg += adc_array[i][1];
			}

			voltage_avg_old = (float)voltage_avg;
			voltage_avg_new = (float)voltage_avg/100.0;
			current_avg_old = (float)current_avg;
			current_avg_new = (float)current_avg/100.0;

			power_avg = (uint32_t)voltage_avg_new * current_avg_new;
			
			delta_power = power_avg - power_avg_old;
			delta_voltage = voltage_avg - voltage_avg_old;

			sprintf(send, "PWM: %d p_avg: %ld voltage: %d current: %d\n", 
			OCR1B, power_avg, (uint16_t)voltage_avg_new, (uint16_t)current_avg_new);
			putsUART0(send);

			if (delta_power > 0)
			{
				if (delta_voltage > 0)
				{
					OCR1B--;
				}
				else if (delta_voltage < 0)
				{
					OCR1B++;
				}
			}
			else if (delta_power < 0)
			{
				if (delta_voltage > 0)
				{
					OCR1B++;
				}
				else if (delta_voltage < 0)
				{
					OCR1B--;
				}
			}
			else if (delta_power == 0)
			{
				OCR1B = OCR1B;
			}

			if (OCR1B >= 269)
			{
				OCR1B = 269;
			}
			else if (OCR1B <= 15)
			{
				OCR1B = 15;
			}

			flagADC = 0;
		}

	}
}
