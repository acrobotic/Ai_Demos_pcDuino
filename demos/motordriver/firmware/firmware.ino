// Pinout and wiring: 
// http://www.embeddedrelated.com/showarticle/498.php
// Speed control is possible using PWM on pins PWMA and PWMB on the controller.
// For simple testing connect the aforementioned pins to VCC (the motors will
// then run at full speed).
/*
GND - Microcontroller ground
VCC - VCC from microcontroller (2.7V-5.5V)
AO1 - Output to (-) lead of motor A
AO2 - Output to (+) lead of motor A
BO2 - Output to (+) lead of motor B
BO1 - Output to (-) lead of motor B
VMOT - positive pole of motor battery
GND - negative pole of motor battery

PWMA - VCC
AIN2 - digital pin 6
AIN1 - digital pin 7
STBY - VCC (or use a digital pin to have it software enabled)
BIN1 - digital pin 8
BIN2 - digital pin 9
PWMB - VCC
GND - GND of microcontroller
*/

void setup() 
{
  pinMode(6 ,OUTPUT);
  pinMode(7 ,OUTPUT);
  pinMode(8 ,OUTPUT);
  pinMode(9 ,OUTPUT);   
}

void loop() 
{
  uint8_t time = 1000;
  moveForward(time);
  pause(2*time);
  moveBackward(time);
  pause(2*time);
  turnCCW(time);
  pause(2*time);  
  turnCW(time);
  pause(2*time);
}

void moveForward(int t)
{
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(t);
}

void moveBackward(int t)
{
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  delay(t);  
}

void turnCCW(int t)
{
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(t);  
}

void turnCW(int t)
{
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  delay(t);  
}

void pause(int t)
{
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(t);  
}
