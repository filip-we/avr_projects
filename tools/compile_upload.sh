#!/bin/bash
echo Compiling...
avr-gcc src/main.c -o tools/a.out -mmcu=atmega328p -g -Os
avr-objcopy tools/a.out bin/main.bin -j .text -j .data -O binary --pad-to 0x8000
avr-size tools/a.out --mcu=atmega328p --format=avr

echo Uploading to TL866...
minipro --device "ATMEGA328P@DIP28" -w bin/main.bin
minipro --device "ATMEGA328P@DIP28" -c config -w etc/fuses.conf

