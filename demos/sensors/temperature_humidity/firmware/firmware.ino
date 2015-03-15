/* 
 * Digital Humidity and Temperature Sensor pcDuino Test Program
 *
 * Note: the RHT-03 is also known as the DHT-22 sensor.
 *
 *  1. Connect from left to right:
 *   1. Pin 1 to 3.3 V
 *   2. Pin 2 to ADC5 (J12.6)
 *   3. Pin 3 Not Connected
 *   4. Pin 4 to GND (J9.6)
 *  2. Connect a pull-up 10k Ohm resistor from signal pin 2 to Vdd pin 1.
 *
 */
#include "dht.h"

dht DHT;

#define DHT22_PIN 5
#define DHT22_SAMPLE_RATE_MAX_MS 2*1000

void setup()
{
    printf("DHT TEST PROGRAM\n");
    printf("LIBRARY VERSION: ");
    printf(DHT_LIB_VERSION);
    printf("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)\n");
}

void loop()
{
    printf("DHT22, \t");

    uint32_t start = micros();
    int chk = DHT.read22(DHT22_PIN);
    uint32_t stop = micros();

    switch (chk)
    {
    case DHTLIB_OK:
        printf("OK,\t");
        break;
    case DHTLIB_ERROR_CHECKSUM:
        printf("Checksum error,\t");
        break;
    case DHTLIB_ERROR_TIMEOUT:
        printf("Time out error,\t");
        break;
    default:
        printf("Unknown error,\t");
        break;
    }

    printf("%f", DHT.humidity);
    printf(",\t");
    printf("%f", DHT.temperature);
    printf(",\t");
    printf("%f\n", stop - start);

    delay(DHT22_SAMPLE_RATE_MAX_MS);
}
