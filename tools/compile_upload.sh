#!/bin/bash
#avr-gcc -mmcu=atmega328p -g -Os  -c led.c
#avr-gcc -mmcu=atmega328p -g -o led.elf led.o
#avr-objcopy -j .text -j .data -O ihex led.elf led.hex
#avr-size --mcu=atmega328p --format=avr #  led.bin



avr-gcc led.c -o tools/a.out -mmcu=atmega328p -g -Os
avr-objcopy tools/a.out bin/led.bin -j .text -j .data -O binary --pad-to 0x8000

avr-size tools/a.out --mcu=atmega328p --format=avr


#  Upload to TL866
minipro --device "ATMEGA328P@DIP28" -w bin/led.bin
minipro --device "ATMEGA328P@DIP28" -c config -w etc/fuses.conf
