#include "Controler.h"
float e[3] = {0.0, 0.0, 0.0};
float u[3] = {0.0, 0.0, 0.0};

float num[3] = {
    0.076165731271768,
    -0.152059913859139,
    0.075894386290424
};

float den[3] = {
    1.0,
    -1.998337962774935,
    0.998337962774935
    };

float control(float ref, float mesurement)
{
    e[0] = ref - mesurement;
    u[0] = (-den[1]) * u[1] + (-den[2]) * u[2] + num[0] * e[0] + num[1] * e[1] + num[2] * e[2];
    e[2] = e[1];
    e[1] = e[0];
    u[2] = u[1];
    u[1] = u[0];

    return (u[0]);
}

void step(uint8_t base, uint8_t top, uint16_t delay)
{
    DDRB |= (1 << PB4);
    PORTB &= (0 << PB4);
    OCR1B = base;
    _delay_ms(delay);
    PORTB |= (1 << PB4);
    OCR1B = top;
    _delay_ms(delay);
    PORTB &= (0 << PB4);
}
