#ifndef TIMER_H_
#define TIMER_H_

// Include libraries
#include <avr/io.h>
#include <avr/interrupt.h>

// Declare functions
void initTimer1(uint16_t compareValue);
void initTimer3(uint16_t compareValue);
void init_pc_pwm();

#endif /* TIMER_H_ */