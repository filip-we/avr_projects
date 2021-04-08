#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usbdrv/usbdrv.h"

#define USB_LED_OFF 0
#define USB_LED_ON 1

void initLcd(void);
void sendChar(unsigned char msg);

// Port B is used for control signals
int RegisterSelectPin = 0b00000001;
int ReadWritePin = 0b00000010;
int EnablePin = 0b00000100;

char c1 = 'a'
char c2 = 'b'

USB_PUBLIC uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data; //cast data to correct type...

    switch (rq->bRequest) {
        case USB_LED_ON:
            sendChar(c1);
            return 0;
        case USB_LED_OFF:
            sendChar(c2);
            return 0;
    return 0;
}

int main(void) {
    //Port D is connected to the data-lines of the LCD
    DDRD = 0xff;

    PORTB = 0b00000000;     //  Set control pins low
    DDRB = 0b00000111;      //  Set control to output

    initLcd();

    usbInit();
    usbDeviceDisconnect();
    _delay_ms(500);
    usbDeviceConnect();

    char tmp = 'a';
    while(1) {
        usbPoll();
    }
    return 0;
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
