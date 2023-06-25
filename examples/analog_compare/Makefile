FREQ      = 2000000
DEVICE    = attiny85
SRC       = main.c
TARGET    = app

all: $(SRC)
	avr-gcc -g -O2 -fshort-enums -mmcu=$(DEVICE) -DF_CPU=$(FREQ) $(SRC) -o $(TARGET).elf
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex
	avr-size --format=avr --mcu=$(DEVICE) $(TARGET).elf

clean:
	rm $(TARGET).elf $(TARGET).hex