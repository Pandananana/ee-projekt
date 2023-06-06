#include <avr/io.h>
#include "mppt.h"

int pwm_range = 255; // timer0 8 bit 0-255

int calculatePower(uint16_t adcVoltage, uint16_t current) {
	return adcVoltage * current;
}

int calcPWM(uint16_t adcVoltage, int desired_voltage) {
	float duty_cycle = (desired_voltage / (float)adcVoltage) * 100; // Calculate duty cycle percentage
	int pwm_value = (int)((duty_cycle / 100.0) * pwm_range); // Calculate timer value
	return pwm_value;
}	
