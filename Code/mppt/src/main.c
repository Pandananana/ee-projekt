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

uint16_t voltage_new_avg[5];
uint16_t current_new_avg[5];
uint16_t voltage_old_avg;
uint16_t current_old_avg;
uint16_t voltage_avg;
uint16_t current_avg;
uint16_t voltage_new;
uint16_t voltage_old;
uint16_t power_avg;
uint16_t current_new;
uint16_t current_old;
uint16_t desired_voltage = 5;
uint16_t OCR1B_old = 0;
uint8_t direction = 1;
uint8_t flag = 0;

void init()
{
	ADC_init();
	init_fast_pwm();
	sei();
	uart0_Init(MYUBBRF); // Uart setup
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
		voltage_old_avg = voltage_avg;
		current_old_avg = current_avg;
		OCR1B_old = OCR1B;
		//direction = OCR1B - OCR1B_old; //Positive number = going up, negative number = going down
		for(int i = 0; i < 5; i++)
		{
			voltage_new_avg[i] = adcVoltage_new;
			current_new_avg[i] = adcCurrent_new;
		}
		
		voltage_avg = (voltage_new_avg[0]+voltage_new_avg[1]+voltage_new_avg[2]+voltage_new_avg[3]+voltage_new_avg[4])/5;
		current_avg = (current_new_avg[0]+current_new_avg[1]+current_new_avg[2]+current_new_avg[3]+current_new_avg[4])/5;

		/*voltage_old = voltage_new;
		current_old = current_new;
		voltage_new = adcVoltage_new;
		current_new = adcCurrent_new;*/

		uint32_t power_old = voltage_old_avg * current_old_avg;
		uint32_t power_new = voltage_avg * current_avg;

		sprintf(send, "PWM: %i voltage: %i current: %i Pnew: %ld Pold: %ld dir: %i\n", OCR1B, voltage_avg, current_avg, power_new, power_old, direction);
		putsUART0(send);
		_delay_ms(100);
		if (power_new >= power_old)
		{

			if(OCR1B!=255 && OCR1B!=51)
			{
				if(direction)
				{
					OCR1B++;
				}
				else
				{
					OCR1B--;
				}
			}
			else
			{
				if(OCR1B!=51)
				{
					direction = 0;
					OCR1B++;
				}
				else
				{
					direction = 1;
					OCR1B--;
				}
			}
		}
		else
		{
			/*direction&=~0b00000001; // Toggle
			direction&=0b00000001;*/ // Clear 7 MSB

			if (direction)
			{
				direction = 0;
			}
			else
			{
				direction = 1;
			}

			if (direction)
			{
				OCR1B++;
			}
			else
			{
				OCR1B--;
			}
		}

		if (OCR1B >= 255)
		{
			OCR1B = 255;
		}
		else if (OCR1B <= 64)
		{
			OCR1B = 64;
		}


		/*if (power_new > power_old)
		{
			if (power_new < 255)
			{
				if (voltage_avg > voltage_avg)
				{
					OCR1B-=12; // Reverse
				}
				else if (voltage_avg < voltage_avg)
				{
					OCR1B+=12;
				}
				else
				{
					OCR1B-=12;
				}
			}
			else
			{
				OCR1B+=12;
			}
		}
		else if (power_new < power_old) //Power new less than power old
		{
			if (voltage_avg > voltage_avg)
			{
				OCR1B-=12;
			}
			else if (voltage_avg < voltage_avg)
			{
				OCR1B+=12;
			}
			else
			{
				OCR1B+=12;
			}
		}
		else
		{
			OCR1B+=12;
		}*/

	}
}
