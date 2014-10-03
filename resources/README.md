# pcDuino3 Resources

## Official Links

1. [pcDuino3 Homepage](http://www.pcduino.com/pcduino-v3/)
1. [pcDuino Wiki](http://www.pcduino.com/wiki/index.php?title=Book)
1. [pcDuino C Library using Arduino syntax](https://github.com/pcduino/c_environment)

## Arduino Differences

Some things to keep in mind when developing with Arduino on the pcDuino.

1. There is not AVR micrcontroller on the target or being simulated. Instead, the low-level API has been implemented into the Arduino IDE to allow the Arduino code to compile into C code and run in a terminal on the pcDuino.
1. Some libraries need to be modified to support this board. Often, you will have to add C pre-processor statements or conditions using the `PCDUINO_IDE` macro defined during compilation.
1. Since the host and the target are the same, the serial monitor is not useful. Instead, use `printf()`. Alternative, you could loopback the serial transmit and receive pins and use a serial terminal program to connected to `/dev/ttyS01`.

### ADC

* ADC0 and ADC1 are 6-bit ADC, the return value is from 0 ~ 63, ranging from 0V to 2V.
* ADC2~ADC5 are 12-bit ADC, the return value is from 0 ~ 4095, means from 0V to 3.3V.

For ADC0 and ADC1, though this function will return in 4us, the actual conversion rate is 250Hz. So if the input  voltage changed, it can be detected in 4ms. For ADC2~ADC5, this function will return in 35us, the return value  is the actual value measured.

### PWM

* PWM1 and PWM2 are hardware PWMs. They are set to 520Hz with 256 duty cycle level by default. 
* PWM1/3/4/5 are 5Hz with 10 duty cycle level by default. Thus, the actual duty level is value*10/256. 
 * PWM1/3/4/5 are simulated by GPIO in software, so they couldn’t set high frequency. If you need simulate high frequency and accurate PWM with software GPIO, the CPU will be in very high use
* The six PWM pins are shared with GPIO, and PWM4/PWM5 pins are also shared with SPI IO. So if you are using  PWM, don’t call pinMode() or SPI function to specific IO.

