CC=avr-gcc
CLFAGS=-Wall -Os -mmcu=atmega328p

all: hex flash

hex:
	$(CC) $(CLFAGS) main.c -o main.bin
