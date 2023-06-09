#include "Controler.h"
#include "Data.h"

double e[3] = {0.0, 0.0, 0.0};
double u[3] = {0.0, 0.0, 0.0};

double control(double ref, double mesurement)
{
    e[0] = ref - mesurement;
    u[0] = (-den[1]) * u[1] + (-den[2]) * u[2] + num[0] * e[0] + num[1] * e[1] + num[2] * e[2];

    // if (u[0] < 0.00)
    // {
    //     u[0] = 0;
    // }
    // else if (u[0] >100.00)
    // {
    //     u[0] = 100;
    // }

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
