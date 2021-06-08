#!/bin/bash
echo Compiling...
avr-gcc src/main.c -o tools/a.out -mmcu=attiny85 -g -Os
avr-objcopy tools/a.out bin/main.bin -j .text -j .data -O binary --pad-to 0x2000
avr-size tools/a.out --mcu=attiny85 --format=avr

echo Uploading to TL866...
minipro --device "ATTINY85" -w bin/main.bin

