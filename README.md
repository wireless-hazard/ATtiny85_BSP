# ATtiny85 Board Support Package

A simple board support package for the ATtiny85 Atmel 8-bit AVR Microcontroller

## Getting the toolchain ready

The C++ avr-gcc compiler is used to build the libraries and the examples.

### Getting the compiler

The first step is to download **AVR 8-Bit Toolchain (Linux)** from 

https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers

Put the **avr8-gnu-toolchain-linux_x86_64** folder on your /home/ folder. This is the path the current examples will search for the avr c++ compiler.

The other avr tools are still searched in the default avr instalation (if you were to install it using apt), so for that, install:

```
sudo apt update
sudo apt install gcc-avr binutils-avr avr-libc gdb-avr avrdude libusb-dev
```

### Getting the bootloader/flash utility

Micronucleus is used as the bootloader and also our flash utility. To install it, first clone it:

```
git clone https://github.com/micronucleus/micronucleus.git
```

Then, from inside the **micronucleus/commandline** folder:

```
make CONFIG=t85_default
```

Finally, copy the generated binary to your applications folder

```
sudo cp micronucleus /usr/local/bin/
```

## Building an example

To build an example, go to the respective folder and simply do a make all

```
cd examples/Jsn-sr04t
make all
```
If your installation was done correctly, you are going to see a similar message on your terminal:

```
/home/avr8-gnu-toolchain-linux_x86_64/bin/avr-g++ -g -O2 -fshort-enums -std=c++1z -mmcu=attiny85 -DF_CPU=16000000 main.cpp -o sensor.elf
avr-objcopy -O ihex sensor.elf sensor.hex
avr-size --format=avr --mcu=attiny85 sensor.elf
AVR Memory Usage
----------------
Device: attiny85

Program:    1264 bytes (15.4% Full)
(.text + .data + .bootloader)

Data:          4 bytes (0.8% Full)
(.data + .bss + .noinit)
```

### Flashing the Attiny85

To flash your program onto the microcontroller, run the script (from inside the respective example folder):
```
./program.sh
```

Then connect the microcontroller to your pc using a usb cable. In case it was connected already, remove it and reconnect it

## Simulate (TBD)