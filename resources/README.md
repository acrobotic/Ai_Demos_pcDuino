# pcDuino3 Resources

## Official Links

1. [pcDuino3 Homepage](http://www.pcduino.com/pcduino-v3/)
1. [pcDuino Wiki](http://www.pcduino.com/wiki/index.php?title=Book)

## Arduino-like Programming

1. [pcDuino C Library using Arduino syntax](https://github.com/pcduino/c_environment)

Some things to keep in mind when developing with Arduino on the pcDuino.


1. All I/O on the pcDuino is 3.3V. If your Arduino shield need a 5V input or output, you need a bridge board for pcDuino to avoid damage. For external breadboard circuits you need a voltage divider.
1. There is no AVR microcontroller on the target nor is one being simulated. Instead, the low-level API has been implemented into the Arduino IDE to allow the Arduino code to compile into C code and run in a terminal on the pcDuino.
1. Since the host and the target are the same, the serial monitor is not useful. Instead, use `printf()`. Alternative, you could loopback the serial transmit and receive pins and use a serial terminal program to connected to `/dev/ttyS01`.
1. Some libraries need to be modified to support this board. Often, you will have to add the `PCDUINO_IDE` C pre-processor macro or add it to conditionals. The macro is defined as a compiler command line argument.

### ADC

* ADC0/1 are 6-bit ADC, the return value is from 0~63, ranging from 0V to 2V.
 * This function will return in 4us, the actual conversion rate is 250Hz. So if the input voltage changed, it can be detected in 4ms.
* ADC2~ADC5 are 12-bit ADC, the return value is from 0~4095, means from 0V to 3.3V.
 * This function will return in 35us, the return value is the actual value measured.

### PWM

* PWM0/1 are hardware PWMs with a 16-bit counter (1~4096). They are set to 520Hz with 256 duty cycle level by default. 
* PWM2/3/4/5 are 5Hz with 10 duty cycle level by default. Thus, the actual duty level is value*10/256. 
 * PWM2/3/4/5 are simulated by GPIO in software, so they cannot be set to a high frequency. If you use a high frequency PWM with software GPIO, the CPU usage will be in very high.
* PWM2~PWM5 are shared with GPIO and PWM4/5 pins are shared with SPI I/O. If you are using PWM, don’t call pinMode() or SPI function to specific I/O.

### SPI

* SPI maximum clock frequency is 200 MHz.
