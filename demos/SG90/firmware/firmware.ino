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

#define SG90_CENTER_DEG 0
#define SG90_LEFT_DEG   -90
#define SG90_RIGHT_DEG  90
#define SG90_CENTER_US  1000
#define SG90_LEFT_US    1500
#define SG90_RIGHT_US   2000
#define SG90_PERIOD_US  20000

void servo_pulse(int servopin, int myangle)
{
  int pulse_width_on_us = map(myangle, 
                              SG90_LEFT_DEG, SG90_RIGHT_DEG, 
                              SG90_LEFT_US,  SG90_RIGHT_US);  
  int pulse_width_off_us = SG90_PERIOD_US - pulse_width_on_us;

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
            
  for (int i = 0; i < 30; i++) {
    servo_pulse(servopin, val);
    delayMicroseconds(1);
  }

  delay(1000);
}
