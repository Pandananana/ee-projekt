#ifndef CONTROLER_H_
#define CONTROLER_H_

// Include libraries
#include <avr/io.h>
#include <util/delay.h>
float e[3];
float u[3];

// Declare functions
float control(float ref, float mesurement);
void step(uint8_t base, uint8_t top, uint16_t delay);
#endif /* CONTROLER_H_ */