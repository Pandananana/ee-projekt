#include <avr/io.h>
#include "mppt.h"

int pwm_range = 255;

int calculatePower(uint16_t adcVoltage_new, uint16_t current) {
	uint32_t power = adcVoltage_new * current;
	return power;
}

int calcPWM(float adcVoltage, int desired_voltage) {
	//float duty_cycle = (desired_voltage / (float)adcVoltage) * 100; // Calculate duty cycle percentage
	//int pwm_value = (int)((adcVoltage / 100.0) * pwm_range); // Calculate timer value
	int pwm_value = round((adcVoltage / 255.0) * pwm_range);
	return pwm_value;
}	
