#include "dht.h"

dht DHT;

#define DHT22_PIN 5

void setup()
{
    Serial.begin(115200);
    printf("DHT TEST PROGRAM ");
    //printf("LIBRARY VERSION: ");
    //printf(DHT_LIB_VERSION);
    //printfln("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");
}

void loop()
{
    // READ DATA
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
    // DISPLAY DATA
    printf("%f", DHT.humidity);
    printf(",\t");
    printf("%f", DHT.temperature);
    printf(",\t");
    printf("%f\n", stop - start);

    delay(2000);
}
//
// END OF FILE
//
