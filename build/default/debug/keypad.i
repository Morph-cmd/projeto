# 1 "keypad.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "keypad.c" 2
# 23 "keypad.c"
# 1 "./keypad.h" 1
# 23 "./keypad.h"
 unsigned char kpRead(void);
 void kpDebounce(void);
 void kpInit(void);
# 23 "keypad.c" 2

# 1 "./pic18f4520.h" 1
# 24 "keypad.c" 2


static unsigned char valor = 0x00;


unsigned char kpRead(void) {
    return valor;
}

void kpDebounce(void) {
# 42 "keypad.c"
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned char valorNovo = 0x00000;
    static unsigned char valorAntigo = 0x00000;
    char portes[5] = {(*(volatile __near unsigned char*)0xF81), (*(volatile __near unsigned char*)0xF81), (*(volatile __near unsigned char*)0xF81), (*(volatile __near unsigned char*)0xF81), (*(volatile __near unsigned char*)0xF84)};
    char bits[5] = {2, 3, 5, 4, 1};
# 62 "keypad.c"
    for (j = 0; j < 5; j++) {
            if (!((portes[j]) & (1<<bits[j]))) {
                ((valorNovo) |= (1<<j));
            } else {
                ((valorNovo) &= ~(1<<j));
            }
        }
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }

}

void kpInit(void) {
    (*(volatile __near unsigned char*)0xF93) = 0xFF;
    (((*(volatile __near unsigned char*)0xFF1)) &= ~(1<<7));
    (*(volatile __near unsigned char*)0xFC1) = 0b00001110;


    (*(volatile __near unsigned char*)0xF63) = 0x00;

}
