#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
   DDRB = 0b00001000;                       // setting Port 3 to output
   while(1)
   {
       PORTB = 0b00001000;
       _delay_ms(50);

       PORTB = 0b00000000;
       _delay_ms(50);

       PORTB = 0b00001000;
       _delay_ms(500);

       PORTB = 0b00000000;
       _delay_ms(500);
   }
}
