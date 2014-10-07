/* Photocell simple testing sketch. 
 *
 * 1. Connect one end of the photocell to 3 V, the other end to ADC0 (J12.1).
 * 2. Then connect one end of a 4.7K Ohm resistor from ADC0 to ground. 
 * 3. Connect LED from pin PWM9 (J8.2) through a resistor to ground.
 */
 
int photocellPin = A0;
int photocellReading;
int LEDpin = 9;
int LEDbrightness;

void setup(void) {
  pinMode(LEDpin, OUTPUT);
}
 
void loop(void) {
  photocellReading = analogRead(photocellPin);  
 
  printf("Analog reading = %d\n", photocellReading);
 
  LEDbrightness = map(photocellReading, 0, 63, 0, 20);
  analogWrite(LEDpin, LEDbrightness);
  
  delay(100);
}
