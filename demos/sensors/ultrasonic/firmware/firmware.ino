/*
 * pcDuino HC-SR04 ultrasonic distance sensor example.
 * 
 * HC-SR04 to pcDuino
 * GND        GND (J9.7)
 * ECHO       GPIO2 (J11.3) through voltage divider (1).
 * TRIG       GPIO3 (J11.4) through inverter below (2).
 * VCC        5 V (J9.4)
 * 
 * Note: datasheets recommend connecting GND before VCC.
 *
 *
 * Voltage divider (1): 
 *                          +----------+ HC-SR04 ECHO 
 *                          |                         
 *                         +++                        
 *                         |R| 4.7k Ohm               
 *                         |1|                        
 *                         +++                        
 *                          |                         
 *  pcDuino GPIO2 +---------+                         
 *                          |                         
 *                         +++                        
 *                         |R| 4.7k Ohm               
 *                         |2|                        
 *                         +++                        
 *                          |                         
 *                          |                         
 *                          +                         
 *                         GND                        
 *
 * Pull-up inverter (2):
 *                                +-----------+ 5 V     
 *                                |                     
 *                               +++                    
 *                               |R| 1k Ohm             
 *                               |2|                    
 *                               +++                    
 *                                |                     
 *                                +-----------+ HC-SR04 
 *                4.7k Ohm        |C            TRIG    
 *                               +++                    
 *               +--+           B|Q| 2N3904             
 *  pcDuino +----+R1+------------+1|                    
 *  GPIO3        +--+            +++                    
 *                                |E                    
 *                                |                     
 *                                +                     
 *                               GND                    
 * 
 *
 */

#define trigPin 2
#define echoPin 3

#define ECHO_TIMEOUT_US 60*1000

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int duration, distance;
  // pulse is inverted by NPN transistor
  digitalWrite(trigPin, LOW);
  delay(10);
  digitalWrite(trigPin, HIGH);
  duration = pulseIn(echoPin, HIGH, ECHO_TIMEOUT_US);

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
