#ifndef CONTROLER_H_
#define CONTROLER_H_

// Include libraries
#include <avr/io.h>
float e[3] = {0.0 , 0.0, 0.0};
float u[3] = {0.0 , 0.0, 0.0};

// Declare functions
float control(float ref, float mesurement);

#endif /* CONTROLER_H_ */