/*
 * pcDuino ADC test program
 * 
 * * A0 and A1 
 *  * max input voltage: 2 V
 *  * resolution: 6-bit
 *  * max value: 63
 * * A2~A5 
 *  * max input voltage is 3.3 V
 *  * resolution: 12-bit
 *  * max value: 4095
 *
 * 1. Let all pins float. Observe that there is no internal pull-up/down.
 * 2. Sequentially connect GND (J9.6) to each pin. Observe the min value.
 * 3. Sequentially connect 3.3 V (J9.4) to A2~A5. Observe the max value.
 * 4. Through a voltage divider (e.g. using a 1k Ohm and 300 Ohm resistor),
 *    connect ~1 V to A0 and A1. Observe the 1/2 value.
 *
 */
#include <core.h>

void setup()
{
}

void loop()
{
    int a0 = analogRead(0);
    int a1 = analogRead(1);
    int a2 = analogRead(2);
    int a3 = analogRead(3);
    int a4 = analogRead(4);
    int a5 = analogRead(5);
    printf("  A0,   A1,   A2,   A3,   A4,   A5\n");
    printf("%04d  %04d  %04d  %04d  %04d  %04d\n", a0, a1, a2, a3, a4, a5);
    delay(1000);
}
