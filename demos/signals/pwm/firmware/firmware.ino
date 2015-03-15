/*
 * pcDuino PWM Signal Test Program
 *
 * 1. Connect PWM5/GPIO5 (J11.6) to an oscilloscope. Observe duty cycle 
 *    change from max to min.
 * 2. Alternatively, connect an LED through a resistor. Observe the 
 *    LED go from bright to dim.
 *
 */
#include <core.h>

int pwm_id = 5;
int delay_us = 200*1000;
int freq = 781;
int value = MAX_PWM_LEVEL;

void setup()
{
}

void set_pwm()
{
    int step = 0;
    step = pwmfreq_set(pwm_id, freq);
    printf("Set PWM%d freq %d Hz, duty cycle %d (range 0..%d)\n", 
            pwm_id, freq, value, step);
    analogWrite(pwm_id, value);
}

void loop()
{
    set_pwm();
    delayMicroseconds(delay_us); 
    value -= 10;
    if (value < 1)
        value = MAX_PWM_LEVEL;
}

