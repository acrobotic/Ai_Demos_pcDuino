/* pcDuino Servo PWM Example
 *
 *  1. Connect J11.7 GPIO6 / PWM6 to the left yellow pin
 *  2. Connect J9.4 3.3 V to the middle orange pin
 *  3. Connect J9.6 GND to the left brown pin
 */

int servopin = 6;
int val = 0;

void servopulse(int servopin, int myangle)
{
	int pulsewidth = (myangle*11)+500;	//translate angle to a pulse width value between 500-2480
	digitalWrite(servopin, HIGH);
	delayMicroseconds(pulsewidth);
	digitalWrite(servopin, LOW);
	delay(20-pulsewidth/1000);
}

void setup()
{
	pinMode(servopin, OUTPUT);

	// center servo
	servopulse(servopin, 90);
}

void loop()
{
	int angle = val*(180/9);

	servopulse(servopin, angle);

	val = (val + 1) % 10;

	delay(1*1000);
}
