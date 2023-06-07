#include "controler.h"
float e[3] = {0.0 , 0.0, 0.0};
float u[3] = {0.0 , 0.0, 0.0};

float control(float ref, float mesurement){
    e[0] = ref - mesurement;
    u[0] = 1.9995*u[1] - 0.9995*u[2]+0.2694*e[0]-0.5385*e[1]+0.2691*e[2];
    e[2] = e[1];
    e[1] = e[0];
    u[2] = u[1];
    u[1] = u[0];

    return(u[0]);
}

