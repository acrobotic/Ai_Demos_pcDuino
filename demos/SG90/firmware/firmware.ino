/*
 * pcDuino3 Servo PWM Example
 *
 *  1. Connect J11.7 GPIO6 / PWM6 to the left yellow pin
 *  2. Connect J9.4 3.3 V to the middle orange pin
 *  3. Connect J9.6 GND to the left brown pin
 *
 * The servo requires a 20 ms period (50 Hz). However, the pcDuino3 does not
 * provide a PWM pin that supports that low of a freqency. Therefore, this
 * code bit-bangs the PWM signal using digitalWrite().
 *
 */

int servopin = 6;
int val = 0;
int isNeg = 1;

void servo_pulse(int servopin, int myangle)
{
  int pulse_width_on_us = map(myangle, -90, 90, 1000, 2000);  
  int pulse_width_off_us = 20*1000 - pulse_width_on_us;

  digitalWrite(servopin, HIGH);
  delayMicroseconds(pulse_width_on_us);

  digitalWrite(servopin, LOW);
  delayMicroseconds(pulse_width_off_us);
}

void setup()
{
  pinMode(servopin, OUTPUT);
}

void loop()
{
  if (val >= 90)
  {
    isNeg = -1;
  }
  else if ( val <= -90 )
  {
    isNeg = 1;
  }
        
  val += isNeg * 90;
            
  //This will provide smoother movement to the desired angle
  for (int i = 0; i < 30; i++) {
    servo_pulse(servopin, val);
  }
  delay(1000);
}
