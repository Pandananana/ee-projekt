#include <Arduino.h>

const int pwmPin = 10; // PWM output pin
const int trigger = 8;

void setup()
{
    pinMode(pwmPin, OUTPUT); // Set the PWM pin as output
    pinMode(trigger, OUTPUT);

    // Clear Timer Control Registers
    TCCR1A = 0;
    TCCR1B = 0;

    // Set non-inverting mode for both OCR1A and OCR1B
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    // Set fast PWM Mode 14
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    // Set prescaler to 1
    TCCR1B |= (1 << CS10);

    // Set top count value (determines the PWM frequency)
    ICR1 = 319;

    // Set the PWM duty cycle by writing to OCR1A or OCR1B (value must be less than ICR1)
    OCR1B = 160;
}

void loop()
{
  OCR1B = 111;
  digitalWrite(trigger, 0);
  delay(5000);

  OCR1B = 143;
  digitalWrite(trigger, 1);
  delay(10000);
}
