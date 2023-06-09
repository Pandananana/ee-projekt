#include <Arduino.h>




const int pwmPin = 10;  // PWM output pin
const int trigger = 9;


void setup() {
  pinMode(pwmPin, OUTPUT);  // Set the PWM pin as output
  pinMode(trigger, OUTPUT);
  OCR1A = 320;
  TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS10);
  TCCR1A = (1<<WGM10)|(1<<WGM11)|(1<<COM1B1); 
}

void loop() {

OCR1B = 160;

  /*analogWrite(pwmPin, 153); 
  digitalWrite(trigger, 0);
  delay(10);  // Delay for a certain period (adjust as needed)

  analogWrite(pwmPin, 178);
  digitalWrite(trigger, 1);
  delay(10);  // Delay for a certain period (adjust as needed)

*/

}






