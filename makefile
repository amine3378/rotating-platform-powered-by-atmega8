# Makefile for ATmega8 with winAVR

# Specify the target microcontroller
MCU = atmega8

# Define the CPU frequency
F_CPU = 16000000

# Compiler and tools
CC = avr-gcc
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Output file name
TARGET = main

# Source files
SRC = main.c lcd.c

# Object files
OBJ = $(SRC:.c=.o)

# Hex file name
HEX = $(TARGET).hex

# Programmer options (you can change these depending on your programmer)
PROGRAMMER = usbasp
PORT = usb

# Default target
all: $(HEX)

# Compile the source files into object files
%.o: %.c lcd.h
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into a final executable
$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJ)

# Convert ELF to HEX
$(HEX): $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(HEX)

# Program the device using USBasp (this step assumes you have USBasp and avrdude installed)
program: $(HEX)
	avrdude -c $(PROGRAMMER) -p m8 -U flash:w:$(HEX):i

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET).elf $(HEX)

# Flash and clean
flash: program clean
