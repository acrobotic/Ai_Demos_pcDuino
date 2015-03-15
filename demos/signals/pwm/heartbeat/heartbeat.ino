/*
 * pcDuino Heartbeat LED Example
 *
 * 1. Connect PWM11/GPIO11 (J8.4) to anode of the LED through a 300 Ohm 
 *    resistor.
 * 2. Connect GND (J9.7) to the cathod of the LED.
 *
 */
int led_pin = 11;

int value = 0,
    value_max = 128,
    number_of_steps = 255,
    step_delay_ms = 5,
    cycle_delay_ms = 1000;

void setup()
{
  pinMode(led_pin, OUTPUT);
}

int step_size = max( (int)value_max/number_of_steps, 1 );

void loop()
{
  analogWrite(led_pin, value);  
  delay(step_delay_ms);  
  value+=step_size;

  if( (value >= value_max)||(value<0) )
    step_size *= -1;
  if(value < 0)
  {
    value = 0;
    delay(cycle_delay_ms);
  }
}
