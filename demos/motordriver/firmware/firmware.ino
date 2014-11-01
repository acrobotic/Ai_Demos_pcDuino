/* pcDuino Motor Controller Example
 *
 * Polulo
 * TB6612FNG to pcDuino
 * (left side)
 * GND  (1)     GND (J9.6)
 * VCC  (2)     3.3 V (J9.4) 
 * AO1  (3)     (-) motor A
 * AO2  (4)     (+) motor A
 * BO2  (5)     (+) motor B
 * BO1  (6)     (-) motor B
 * VMOT (7)     (+) motor battery
 * GND  (8)     (-) motor battery
 * (right side)
 * PWMA (16)    VCC (J9.4 or TB6612FNG 2)
 * AIN2 (15)    GPIO2 (J11.3)
 * AIN1 (14)    GPIO3 (J11.4)
 * STBY (13)    VCC (J9.4 or TB6612FNG 2)
 * BIN1 (12)    GPIO4 (J11.5)
 * BIN2 (11)    GPIO5 (J11.6)
 * PWMB (10)    VCC (J9.4 or TB6612FNG 2)
 * GND  (9)     GND (J9.6 or TB6612FNG 1)
 *
 * Speed control is possible using PWM on pins PWMA and PWMB on the controller.
 * For simple testing, the aforementioned pins are connected to VCC so the 
 * motors will run at full speed. In addition, the active low standby is tied
 * to VCC to disable standby operation. Instead, a software "pause" is used.
 *  
 * Credit: http://www.embeddedrelated.com/showarticle/498.php
 */

#define AIN2 2
#define AIN1 3
#define BIN1 4
#define BIN2 5

void setup() 
{
  pinMode(AIN2 ,OUTPUT);
  pinMode(AIN1 ,OUTPUT);
  pinMode(BIN1 ,OUTPUT);
  pinMode(BIN2 ,OUTPUT);   
}

void loop() 
{
  int time = 1000;
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
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  delay(t);
}

void moveBackward(int t)
{
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  delay(t);  
}

void turnCCW(int t)
{
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  delay(t);  
}

void turnCW(int t)
{
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  delay(t);  
}

void pause(int t)
{
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  delay(t);  
}
