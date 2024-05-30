# 1 "event.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "event.c" 2
# 1 "./keypad.h" 1
# 23 "./keypad.h"
 unsigned char kpRead(void);
 void kpDebounce(void);
 void kpInit(void);
# 1 "event.c" 2

# 1 "./event.h" 1
# 10 "./event.h"
enum{
    EV_0,
    EV_1,
    EV_2,
    EV_3,
    EV_4,
    EV_5
};
void eventInit(void);
unsigned int eventRead(void);
# 2 "event.c" 2

# 1 "./pic18f4520.h" 1
# 3 "event.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdString(const char *str);
    void lcdInt(int val);
# 4 "event.c" 2




static unsigned int ev_ant;
static unsigned int key_ant;
static unsigned int key;
static unsigned int dTimer;
static unsigned int dTimerMax;
static unsigned int ev = 'b';

void eventInit(void) {
    kpInit();

    ev_ant = 0;
    key = 1;
}

void delay2ms(void) {
    unsigned char j, k;
    for (j = 0; j < 20; j++)
        for (k = 0; k < 178; k++);
}

unsigned int eventRead(void) {
    int key;
    int ev = EV_5;
    key = kpRead();
    if (key != key_ant) {
        if (((key) & (1<<0))) {
            ev = EV_0;
        }

        if (((key) & (1<<1))) {
            ev = EV_1;
        }

        if (((key) & (1<<2))) {

        }
    }

    key_ant = key;
    return ev;
# 76 "event.c"
}
