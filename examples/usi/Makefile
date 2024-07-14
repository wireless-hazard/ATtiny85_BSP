FREQ      = 16000000
DEVICE    = attiny85
SRC       = main.cpp
TARGET    = app
AVR_PATH  = /home/avr8-gnu-toolchain-linux_x86_64/bin

all: $(SRC)
	$(AVR_PATH)/avr-gcc -g -O2 -fshort-enums -std=c++1z -mmcu=$(DEVICE) -DF_CPU=$(FREQ) $(SRC) -o $(TARGET).elf
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex
	avr-size --format=avr --mcu=$(DEVICE) $(TARGET).elf

clean:
	rm $(TARGET).elf $(TARGET).hex