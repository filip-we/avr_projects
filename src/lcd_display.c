#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void initLcd(void);
void sendChar(unsigned char msg);

// Port B is used for control signals
int RegisterSelectPin = 0b00000001;
int ReadWritePin = 0b00000010;
int EnablePin = 0b00000100;

int main(void) {
    //Port D is connected to the data-lines of the LCD
    DDRD = 0xff;

    PORTB = 0b00000000;     //  Set control pins low
    DDRB = 0b00000111;      //  Set control to output

    char tmp = 'a';
    initLcd();
    sendChar(tmp);
}

void initLcd(void) {
    char cmd[4];
    cmd[0] = 0b00001110;
    cmd[1] = 0b00111000;
    cmd[2] = 0b00000110;
    for (int i=0; i<3; i++) {
        PORTD = cmd[i];
        PORTB |= EnablePin;
        _delay_ms(1);
        PORTB &= ~EnablePin;  //  Keeps all pins as they were except the enable-pin
        _delay_ms(1);
    }
}

void sendChar(unsigned char msg) {
    PORTD = msg;                //  Set datapins
    PORTB |= RegisterSelectPin; //  Set RegisterSelect-pin
    _delay_ms(1);
    PORTB |= EnablePin;         //  Toggle Enable-pin
    _delay_ms(1);
    PORTB &= ~EnablePin;
    _delay_ms(1);
    PORTB &= ~RegisterSelectPin;
}
