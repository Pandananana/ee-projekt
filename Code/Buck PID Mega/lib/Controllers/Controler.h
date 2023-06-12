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
#endif /* CONTROLER_H_ */