# pcDuino v3 Resources

## Official Links

1. [pcDuino Wiki](http://www.pcduino.com/wiki/index.php?title=Book)

## Arduino Programming

Some things to keep in mind when developing with Arduino on the pcDuino.

1. There is not AVR micrcontroller on the target or being simulated. Instead, the low-level API has been implemented into the Arduino IDE to allow the Arduino code to compile into C code and run in a terminal on the pcDuino.
1. Some libraries need to be modified to support this board. Often, you will have to add C pre-processor statements or conditions using the `PCDUINO_IDE` macro defined during compilation.
1. Since the host and the target are the same, the serial monitor is not useful. Instead, use `printf()`. Alternative, you could loopback the serial transmit and receive pins and use a serial terminal program to connected to `/dev/ttyS01`.
