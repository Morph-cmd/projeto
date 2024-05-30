# 1 "serial.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "serial.c" 2
# 22 "serial.c"
# 1 "./serial.h" 1
# 23 "./serial.h"
 void serialSend(unsigned char c);
 unsigned char serialRead(void);
 void serialInit(void);
# 22 "serial.c" 2

# 1 "./pic18f4520.h" 1
# 23 "serial.c" 2


void serialSend(unsigned char c) {
    while (!(((*(volatile __near unsigned char*)0xF9E)) & (1<<4)));
    (*(volatile __near unsigned char*)0xFAD) = c;
}

unsigned char serialRead(void) {
    char resp = 0;

    if ((((*(volatile __near unsigned char*)0xFAB)) & (1<<1)))
    {
        (((*(volatile __near unsigned char*)0xFAB)) &= ~(1<<4));
        (((*(volatile __near unsigned char*)0xFAB)) |= (1<<4));
    }

    if ((((*(volatile __near unsigned char*)0xF9E)) & (1<<5)))
    {
        resp = (*(volatile __near unsigned char*)0xFAE);
    }
    return resp;


}

void serialInit(void) {
    (*(volatile __near unsigned char*)0xFAC) = 0b00101100;
    (*(volatile __near unsigned char*)0xFAB) = 0b10010000;
    (*(volatile __near unsigned char*)0xFB8) = 0b00001000;
    (*(volatile __near unsigned char*)0xFB0) = 0b00000000;
    (*(volatile __near unsigned char*)0xFAF) = 0b00100010;
    (((*(volatile __near unsigned char*)0xF94)) |= (1<<6));
    (((*(volatile __near unsigned char*)0xF94)) |= (1<<7));
}
