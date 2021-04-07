#!/bin/bash
#avr-gcc -mmcu=atmega328p -g -Os  -c led.c
#avr-gcc -mmcu=atmega328p -g -o led.elf led.o
#avr-objcopy -j .text -j .data -O ihex led.elf led.hex
#avr-size --mcu=atmega328p --format=avr #  led.bin


echo Compiling...
avr-gcc $1 -o tools/a.out -mmcu=atmega328p -g -Os

echo Formatting bin-file...
avr-objcopy tools/a.out bin/a.bin -j .text -j .data -O binary --pad-to 0x8000
avr-size tools/a.out --mcu=atmega328p --format=avr


echo Uploading to TL866...
minipro --device "ATMEGA328P@DIP28" -w bin/a.bin

