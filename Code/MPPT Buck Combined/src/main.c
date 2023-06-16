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
double voltage_avg = 0;
float voltage_avg_new;
float voltage_avg_old;
uint32_t current_avg = 0;
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
uint32_t power_avg_old;
uint32_t power_avg = 0;
int delta_power;
uint16_t adc_voltage_old;
uint16_t adc_voltage_new;
float delta_voltage;
int counter2 = 0;
//buck
#define PWM_TOP 160
#define PWM_BOT 0
//
void init()
{
	ADC_init();
	init_fast_pwm();
	uart0_Init(MYUBBRF); // Uart setup
    init_T3_fast_pwm();
    OCR3A = PWM_TOP;
	sei();
	
}

int main(void)
{	
	init();
	char send[64];

    // buck
    int ref = 256;

    int OCR3B_signed = (PWM_TOP - 1);
    OCR3B = OCR3B_signed;
    //
	while (1)
	{

        if (BUCK_ADC_FLAG == 1)
        {
            if (ADC_new > ref)
            {
                OCR3B_signed++;
            }
            else if (ADC_new < ref)
            {
                OCR3B_signed--;
            }

            if (OCR3B_signed > PWM_TOP)
            {
                OCR3B_signed = PWM_TOP-1;
            }
            else if (OCR3B_signed < 0)
            {
                OCR3B_signed = 0;
            }
            OCR3B = OCR3B_signed;
            BUCK_ADC_FLAG = 0;
        }
        
		while(flag==0){ // Calculate inital duty cycle
		OCR1B = calcPWM(adc_array[0][0], desired_voltage);
			if(OCR1B!=0)
			{
				flag = 1;
			}
		}

		if (flagADC == 1)
		{
			power_avg_old = power_avg;
			power_avg = 0;
			voltage_avg = 0;
			current_avg = 0;
			for (int i = 0; i < 100; i++)
			{
				voltage_avg += adc_array[i][0];
				current_avg += adc_array[i][1];
			}


			voltage_avg_old = voltage_avg_new;
			voltage_avg_new = voltage_avg/100.0;
			current_avg_old = current_avg_new;
			current_avg_new = current_avg/100.0;

			power_avg = (uint32_t)(voltage_avg_new * current_avg_new);
			
			delta_power = power_avg - power_avg_old;
			delta_voltage = voltage_avg_new - voltage_avg_old;

			counter2++;
			if(counter2==10)
			{
			//dtostrf(voltage_avg_new, 10, 2, send);
			//dtostrf(delta_voltage, 8, 2, send);
			sprintf(send, "Power_delta: %d power_avg: %d\n", delta_power, power_avg);
			putsUART0(send);
			counter2 = 0;
			}

		sprintf(send, "PWM: %d p_avg: %ld voltage: %d current: %d\n", 
			OCR1B, power_avg, (uint16_t)voltage_avg_new, (uint16_t)current_avg_new);
			putsUART0(send);

			if (delta_power > 0)
			{
				if (delta_voltage > 0) // Left side approaching MPP
				{
					OCR1B++;
				}
				else if (delta_voltage < 0) // Right side approaching MPP
				{
					OCR1B--;
				}
			}
			else if (delta_power < 0)
			{
				if (delta_voltage > 0) // Right side moving away from MPP
				{
					OCR1B--;
				}
				else if (delta_voltage < 0) // Left side moving away from MPP
				{
					OCR1B++;
				}
			}
			else if (delta_power == 0)
			{
				OCR1B = OCR1B;
			}

			if (OCR1B >= 255)
			{
				OCR1B = 255;
			}
			else if (OCR1B <= 15)
			{
				OCR1B = 15;
			}

			flagADC = 0;
		}

	}
}
