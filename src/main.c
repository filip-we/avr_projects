#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usbdrv.h"

#define USB_LED_OFF 0
#define USB_LED_ON 1

// void initLcd(void);
// void sendChar(unsigned char msg);

int ledPin = 0b00000001;
int usbLedPin = 0b00001000;

USB_PUBLIC uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data; //cast data to correct type...

    switch (rq->bRequest) {
        case USB_LED_ON:
            PORTD |= usbLedPin;
            return 0;
        case USB_LED_OFF:
            PORTD &= ~usbLedPin;
            return 0;
    }
    return 0;
}

int main(void) {
    PORTC = 0;
    PORTD = 0;

    DDRC = ledPin | usbLedPin;      // LED pins set to output
    DDRD = ~USBMASK;

    usbInit();
    usbDeviceDisconnect();
    PORTD |= usbLedPin;         // Check that usbLedPin works
    _delay_ms(500);
    PORTD &= ~usbLedPin;
    usbDeviceConnect();

    while(1) {
        usbPoll();
        PORTC = ledPin;           // Blink LED
        _delay_ms(50);
        PORTC = 0b00000000;
        _delay_ms(50);

        PORTC = ledPin;           // Blink LED
        _delay_ms(500);
        PORTC = 0b00000000;
        _delay_ms(500);
    }
    return 0;
}

// void initLcd(void) {
//     char cmd[4];
//     cmd[0] = 0b00001110;
//     cmd[1] = 0b00111000;
//     cmd[2] = 0b00000110;
//     for (int i=0; i<3; i++) {
//         PORTD = cmd[i];
//         PORTB |= EnablePin;
//         _delay_ms(1);
//         PORTB &= ~EnablePin;  //  Keeps all pins as they were except the enable-pin
//         _delay_ms(1);
//     }
// }
// 
// void sendChar(unsigned char msg) {
//     PORTD = msg;                //  Set datapins
//     PORTB |= RegisterSelectPin; //  Set RegisterSelect-pin
//     _delay_ms(1);
//     PORTB |= EnablePin;         //  Toggle Enable-pin
//     _delay_ms(1);
//     PORTB &= ~EnablePin;
//     _delay_ms(1);
//     PORTB &= ~RegisterSelectPin;
// }
