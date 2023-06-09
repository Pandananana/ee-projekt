#include <Arduino.h>
#include <Controler.h>

const int pwmPin = 10; // PWM output pin
const int trigger = 8;
const int analogPin = A1;   // Analog pin to read from
volatile int analogValue;   // Volatile variable to store the analog value
const unsigned long samplingInterval = 100;  // Sampling interval in microseconds


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
    ICR1 = 159;

    DDRB |= (1<<PB0);

    // Set the PWM duty cycle by writing to OCR1A or OCR1B (value must be less than ICR1)
    OCR1B = 80;
    Serial.begin(9600);  // Initialize serial communication
    analogReference(DEFAULT);  // Set the default analog reference voltage (5V)

    ADCSRA = (1<<ADPS2) | (1<<ADPS1);

    // Configure Timer1 to generate an interrupt at the desired sampling rate
    cli();  // Disable interrupts
    TCCR0A = 0;  // Clear Timer0 control registers
    TCCR0B = 0;
    TCNT0 = 0;  // Initialize Timer0 counter value
    OCR0A = 199;  // Set the compare match value for 10 kHz sampling rate
    TCCR0A |= (1 << WGM01);  // Configure Timer0 for CTC mode
    TCCR0B |= (1 << CS01);  // Set prescaler to 64
    TIMSK0 |= (1 << OCIE0A);  // Enable Timer0 compare match interrupt
    sei();  // Enable interrupts
}

void loop() {
  // Print the analog value
  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  delay(1000);
}

// Interrupt Service Routine (ISR) for Timer1 compare match
ISR(TIMER0_COMPA_vect) {
  analogValue = analogRead(analogPin);  // Read analog value
  PORTB ^= (1<<PB0);
}
