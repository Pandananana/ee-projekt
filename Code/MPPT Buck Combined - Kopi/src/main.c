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
float current_avg = 0;
float current_avg_new;
float current_avg_old;
uint16_t voltage_new;
uint16_t voltage_old;
uint16_t current_new;
uint16_t current_old;
uint16_t desired_voltage = 5;
uint16_t OCR1B_old = 0;
uint8_t flag = 0;
float power_avg_old;
uint32_t power_avg = 0;
float delta_power;
uint16_t adc_voltage_old;
uint16_t adc_voltage_new;
float delta_voltage;
int counter2 = 0;
uint8_t direction = 1;
char floatstring1[64];
char floatstring2[64];
char floatstring3[64];


float voltage;
float current;
float power;

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
    //OCR3A = PWM_TOP;
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
       /* if (BUCK_ADC_FLAG == 1)
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
			//sprintf(send,"%d, %d\n",OCR3B, ADC_new);
			//putsUART0(send);

        }*/
        
		while(flag==0){ // Calculate inital duty cycle
		OCR1B = calcPWM(adc_array[0][0], desired_voltage);
			if(OCR1B!=0)
			{
				flag = 1;
			}
		}

		if (flagADC == 1)
		{
			power_avg_old = 0;
			power_avg_old = power;
			power = 0;
			voltage_avg = 0;
			current_avg = 0;
			for (int i = 0; i < 100; i++)
			{
				voltage_avg += adc_array[i][0];
				current_avg += adc_array[i][1];
			}


			voltage_avg_old = voltage;
			voltage_avg_new = voltage_avg/100.0;
			current_avg_old = current;
			current_avg_new = current_avg/100.0;

			voltage = ((voltage_avg_new/1024.0)*5)*4.424;
			current = ((current_avg_new/1024.0)*5)/7.5;

			power = (voltage * current);
			
			delta_power = power - power_avg_old;
			delta_voltage = voltage - voltage_avg_old;

			/*counter2++;
			if(counter2==10)
			{
			dtostrf(voltage, 10, 2, send);
			//dtostrf(current_avg_new, 8, 2, send);
			//sprintf(send, "current: %s current_adc: %s\n", current, current_avg_new);
			putsUART0(send);
			counter2 = 0;
			}*/

			/*float current2 = current*100;
			float voltage2 = voltage*100;
			float power2 = power*100;*/

			//sprintf(send, "PWM: %d p_avg: %ld voltage: %ld current: %ld\n", OCR1B, (uint32_t)power2, (uint32_t)voltage2, (uint32_t)current2);
			//putsUART0(send);
			//dtostrf(delta_power,4,2,floatstring1);
			//dtostrf(current,4,2,floatstring2);
			//dtostrf(voltage,4,2,floatstring3);
			//sprintf(send, "delta_P: %s direction: %u stroem: %s, spaending: %s\n", floatstring1, direction, floatstring2, floatstring3);
			//putsUART0(send);

			if (delta_power+(float)0.01 >= (float)0.0) //delta power >= 1
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
			else //delta power < 0
			{
				if(direction)
				{
					direction = 0;
					OCR1B--;
				}
				else
				{
					direction = 1;
					OCR1B++;
				}
			}

			if (OCR1B >= 250)
			{
				OCR1B = 250;
				direction = 0;
			}
			else if (OCR1B <= 10)
			{
				OCR1B = 10;
				direction = 1;
			}

			flagADC = 0;
		}

	}
}
