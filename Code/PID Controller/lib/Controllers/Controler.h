#ifndef CONTROLER_H_
#define CONTROLER_H_

// Include libraries
#include <avr/io.h>
#include <util/delay.h>
double e[3];
double u[3];

// Declare functions
double control(double ref, double mesurement);
void step(uint8_t base, uint8_t top, uint16_t delay);
uint16_t BUCK_control(uint16_t ref , uint16_t PWM_top, uint16_t ADC_mes, uint16_t PWM);

#endif /* CONTROLER_H_ */