/*
 HC-SR04 Ping distance sensor]
 VCC  to pcDuino 3.3V 
 GND  to pcDuino GND
 ECHO to pcDuino pin 13
 TRIG to pcDuino pin 12
 */

#define trigPin 12
#define echoPin 13

void setup() {
  Serial.begin (9600);
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
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
