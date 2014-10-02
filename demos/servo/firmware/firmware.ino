/* pcDuino Servo PWM Example
 * 
 *  1. Connect GPIO6 / PWM6 to the control pin
 */

int servopin = 6;
int val = 0;

void servopulse(int servopin, int myangle)
{
	int pulsewidth = (myangle*11)+500;	//translate angle to a pulse width value between 500-2480
	//printf("on %d\n", pulsewidth);
	digitalWrite(servopin, HIGH);		//pull the interface signal level to high
	delayMicroseconds(pulsewidth);		//delay in microseconds
	digitalWrite(servopin, LOW);		//pull the interface signal level to low
	delay(20-pulsewidth/1000);
	//printf("off %d\n", 20-pulsewidth/1000);
}

void setup()
{
	pinMode(servopin, OUTPUT);

	// center servo
	servopulse(servopin, 90);
	
	// wait long enough for horns to be adjusted/installed
	printf("servo centered: adjusted horns if needed (continuing in 10 seconds)\n");
	delay(10*1000);
}

void loop()
{
	int angle = val*(180/9);

	servopulse(servopin, angle);

	val = (val + 1) % 10;

	delay(1*500);
}
