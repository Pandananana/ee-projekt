#include "Controler.h"
float e[3] = {0.0 , 0.0, 0.0};
float u[3] = {0.0 , 0.0, 0.0};

float control(float ref, float mesurement){
    e[0] = ref - mesurement;
    u[0] = 1.9994*u[1] - 0.9994*u[2]+0.3146*e[0]-0.6288*e[1]+0.3142*e[2];
    e[2] = e[1];
    e[1] = e[0];
    u[2] = u[1];
    u[1] = u[0];

    return(u[0]);
}

void step(uint8_t base, uint8_t top, uint16_t delay){
    DDRB |= (1 << PB4);
    PORTB &= (0 << PB4);
    OCR1B = base;
    _delay_ms(delay);
    PORTB  |= (1 << PB4);
    OCR1B = top;
    _delay_ms(delay);
    PORTB &= (0 << PB4);
}

