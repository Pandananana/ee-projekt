#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "UART.h"
#include "ADC.h"
#include "Controler.h"
#define BAUD 115200
#define MYUBBRF F_CPU / 8 / BAUD - 1

void init()
{
    init_fast_pwm();

    // ADC set uo
    ADC_init();

    // Uart set up
    uart0_Init(MYUBBRF);
    // char send[32];
    //  sprintf(send,"init");
    //  putsUART0(send);
}

int main(void)
{
    init();
    sei();

    char send[32];

    /*double uvals = 0, yvals = 0;
    double y[3] = {0.0, 0.0, 0.0};
    double u[3] = {0.0, 0.0, 0.0};

    double num[3] = {
        0.2192639,
        -0.2191587,
        0
    };

    double den[3] = {
        1,
        -1,
        0
    };
    */
    OCR1B = 0;
    _delay_ms(5000);
    DDRB |= (1 << PB4);
   
    
    float iMax = 200;
    float iMin = -200;
    int Err_Value;
    float P_Term;
    float I_Term;
    float D_Term;
    float Kp = 12.4, Ki = 0.1, Kd = 0.2;
    float d_Temp = 0;
    int i_Temp = 0;
    int PWM_Temp = 10;
    float ref = 600;

    while (1)
    {
        OCR1B = 45;
        PORTB &= (0<<PB4);
        _delay_ms(5000);
        OCR1B = 50;
        PORTB |= (1<<PB4);
        _delay_ms(5000);

        OCR1B = 45;
        PORTB &= (0<<PB4);
        _delay_ms(3000);
        OCR1B = 50;
        PORTB |= (1<<PB4);
        _delay_ms(3000);

        OCR1B = 45;
        PORTB &= (0<<PB4);
        _delay_ms(1000);
        OCR1B = 50;
        PORTB |= (1<<PB4);
        _delay_ms(1000);
        




        // if (flag_ADC == 1)
        // {
        //     /*Err_Value = (ref - ADC_new);
            
        //     P_Term = Kp * Err_Value;
        //     //test_count++;

        //     // if (test_count >= 60000)
        //     // {
        //     //     OCR1B = 0;
        //     //     _delay_ms(5000);
        //     //     Kp = Kp + 0.1;
        //     //     test_count=0;
        //     //     dtostrf(Kp, 4, 2, send);
        //     //     putsUART0(send);
        //     //     sprintf(send,",%d\n", OCR1B);
        //     //     putsUART0(send);
        //     // }
            
        //     // OCR1B = round(P_Term);

        //     D_Term = Kd * (d_Temp - Err_Value);
        //     d_Temp = Err_Value;
        //     i_Temp = i_Temp + Err_Value;

        //     // if (abs(i_Temp) < 50)
        //     // {
        //     //     i_Temp = 0;
        //     // }

        //     if (i_Temp > iMax)
        //     {
        //         i_Temp = iMax;
        //     }
        //     else if (i_Temp < iMin)
        //     {
        //         i_Temp = iMin;
        //     }

        //     I_Term = Ki * i_Temp;

        //     PWM_Temp = (P_Term + I_Term);

        //     // sprintf(send, "%d,%d,%d\n", round(PWM_Temp), round(P_Term), round(I_Term));
        //     // putsUART0(send);
        //     OCR1B = round(PWM_Temp);
        //     */

        //     OCR1B = (int)control(ref,(float)ADC_new);
        //     flag_ADC = 0;

        //     // PORTB ^= (1<<PB4);
        //     // Find error
        //     // u[0] = (ref - ADC_new)*0.139;
        //     // OCR1B = (int)u[0];
        //     /* // Calculate output
        //      uvals = num[0] * u[0] + num[1] * u[1] + num[2] * u[2];
        //      yvals = -den[1] * y[1] - den[2] * y[2];
        //      y[0] = uvals + yvals;

        //      OCR1B = (int)y[0];
        //      */
        //     // dtostrf(y[0], 4, 2, send);
        //     // sprintf(send, "%d\n", ADC_new);
        //     // putsUART0(send);

        //     // Cycling outputs
        //     /* y[2] = y[1];
        //      y[1] = y[0];

        //      // Cycling inputs
        //      u[2] = u[1];
        //      u[1] = u[0];*/

        //     // flag_ADC = 0;

        //     // if ((test_count > 999))
        //     // {
        //     //     sprintf(send, "\nDEBUG");
        //     //     putsUART0(send);
        //     //     for (uint16_t i = 0; i < 1000; i++)
        //     //     {
        //     //         sprintf(send, "%i\n", terminal[i]);
        //     //         putsUART0(send);
        //     //     }
        //     //     test_count = 0;
        //     // }
        // }
    }
}
