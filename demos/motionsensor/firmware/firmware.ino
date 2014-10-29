/*
 * PIR sensor tester
 *
 * Usage:
 * Using Female/Male Cables, connect:
 * PIR                 pcDuino
 * VCC              to 5 V (J9.5)
 * GND              to GND (J9.6)
 * OUT (0~3.3V TTL) to GPIO2 (J11.3)
 *
 * 1. LED anode to GPIO13 (J8.6).
 * 2. LED cathode to 300 Ohm resistor.
 * 3. 300 Ohm resistor to GND (J8.7).
 *
 * Use 2 potentiometer knobs on the sensor for sensitivity and triggering 
 * adjustments.
 * 
 * Sensitivity (Sx):
 * [MAX] Turn all the way CCW for detecting motion from over ~10 steps away
 * [MIN] Turn all the way CW for detecting motion from at most ~4 steps away
 *
 * Triggering (Tx):
 * [MAX] Turn all the way CCW and the trigger latches for ~20secs when
 * motion is detected.  It then takes ~3secs to arm itself for triggering.
 * [MIN] Turn all the way CW and the trigger latches for ~1sec when
 * motion is detected.  It then takes ~3secs to arm itself for triggering.
 * 
 * Recommend setting Sx and Tx to [MIN] for testing. 
 * 
 */

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int pirStateLast = pirState;
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  delay(30*1000);               // PIR sensor will output 0-3 motion sensing
                                // pulses during initialization. This may take
                                // up to 30 seconds. This is only applicable
                                // on first power-on.
}
 
void loop(){
  pirState = digitalRead(inputPin);  // read input value

  if (pirState == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirStateLast == LOW) {
      printf("Motion detected!\n");
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirStateLast == HIGH) {
      printf("Motion ended!\n");
    }
  }

  pirStateLast = pirState;

  delay(1*1000);
}
