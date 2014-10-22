/*
 * pcDuino HC-SR04 ultrasonic distance sensor example.
 * 
 * HC-SR04 to pcDuino
 * GND        GND
 * ECHO       GPIO2 (J11.3)
 * TRIG       GPIO3 (J11.4)
 * VCC        3.3V
 *
 * Note: datasheets recommend connecting GND before VCC.
 *
 */

#define trigPin 2
#define echoPin 3

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // Distance = Time-of-Flight (in one direction) /Inverse of Sound Speed

  distance = (duration/2) / 29.1;
  if (distance >= 200 || distance <= 0){
    printf("Out of range\n");
  }
  else {
    printf("%d cm\n", distance);
  }
  
  delay(500);
}
