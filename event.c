#include "keypad.h"
#include "event.h"
#include "pic18f4520.h"
#include "lcd.h"



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
        if (BitTst(key, 0)) {
            ev = EV_0;
        }

        if (BitTst(key, 1)) {
            ev = EV_1;
        }

        if (BitTst(key, 2)) {
            
        }
    }

    key_ant = key;
    return ev;
    /*
    int ev = EV_5;
    key = kpRead();
    //if (dTimer > 0) {
    if(key != key_ant)
    if (!BitTst(PORTB, 2)) {
        ev = EV_0;
    }
    if (!BitTst(PORTB, 3)) {
        ev = EV_1;
    }
    
    if (BitTst(key, 1)) {
        ev = EV_LEFT;
    }

    if (BitTst(key, 2)) {
        ev = EV_ENTER;
    }
    //}

    //key_ant = key;
    if (ev != ev_ant) {
        ev_ant = ev;
        return ev;
    }
    return EV_5;*/

}
