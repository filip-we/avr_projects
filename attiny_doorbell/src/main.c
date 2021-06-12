#ifndef F_CPU
#define F_CPU 1000000UL // or whatever may be your frequency
#endif
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <util/delay.h>

const int Note_C  = 239;
const int Note_CS = 225;
const int Note_D  = 213;
const int Note_DS = 201;
const int Note_E  = 190;
const int Note_F  = 179;
const int Note_FS = 169;
const int Note_G  = 159;
const int Note_GS = 150;
const int Note_A  = 142;
const int Note_AS = 134;
const int Note_B  = 127;

const int Output = 1;
const int Clock = ((F_CPU/1000000UL) == 16 ? 4 : ((F_CPU/1000000UL) == 8) ? 3 : 0);
const uint8_t scale[] = {239,226,213,201,190,179,169,160,151,142,134,127};

void tone(unsigned char note, unsigned char octave, unsigned long duration) {
    //TCCR1 = 0x90 | (8 - octave);
    //OCR1C = note - 1;
    //TCCR1 = 0x90;
    int prescaler = 8 + Clock - (octave + note/12);
    if (prescaler < 1 || prescaler > 15 || octave == 0) prescaler = 0;
    DDRB = (DDRB & ~(1 << Output)) | (prescaler != 0) << Output;
    OCR1C = (scale[note % 12]) - 1;
    GTCCR = (Output == 4) << COM1B0;
    TCCR1 = 1 << CTC1 | (Output == 1) << COM1A0 | prescaler << CS10;
    _delay_ms(duration);
}


int main(void)
{
    DDRB = (1 << PB3)|(1 << PB1)|(1 << PB0);

    //TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    //TCCR0B = (1 << CS00);
    //OCR0A = 128;

    PORTB = 0b00001000;
    _delay_ms(500);
    PORTB = 0b00000000;


    tone(1, 4, 400);
    tone(2, 4, 400);
    tone(3, 4, 400);
    tone(4, 4, 400);
    tone(5, 4, 400);
    tone(6, 4, 400);
    tone(7, 4, 400);
    tone(8, 4, 400);
    tone(9, 4, 400);
    tone(10, 4, 400);
    tone(11, 4, 400);
    tone(12, 4, 400);
    tone(Note_C, 5, 400);

    PORTB = 0b00001000;
    _delay_ms(50);

    PORTB = 0b00000000;
    _delay_ms(50);


    while(1)
    {
    }
}
