#include "keypad.h"
#include "event.h"
#include "pic18f4520.h"
#include "lcd.h"
#include "serial.h"
#include "var.h"

#define LETRA_TROCAR_IDIOMA 'L'
#define LETRA_ALTERAR_TEMPERATURA 'T'

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

unsigned char eventRead(void) {
    int key;
    int ev = EV_NOEVENT;
    key = kpRead();
    if (key != key_ant) {
        if (BitTst(key, 0)) {
            ev = EV_B_0;
        }

        if (BitTst(key, 1)) {
            ev = EV_B_1;
        }

        if (BitTst(key, 2)) {
            ev = EV_B_2;
        }

        if (BitTst(key, 3)) {
            ev = EV_B_3;
        }

        if (BitTst(key, 4)) {
            ev = EV_B_4;
        }
    }

    key_ant = key;


    unsigned char data = serialRead();
    serialSend(data);
    unsigned char* prot;
    if (data != 0) {
        prot = getProt();
        if (prot[0] == 0) {
            switch (data) {
                case '2':
                    ev = EV_B_0;
                    break;
                case '8':
                    ev = EV_B_1;
                    break;
                case '4':
                    ev = EV_B_2;
                    break;
                case '6':
                    ev = EV_B_3;
                    break;
                case '5':
                    ev = EV_B_4;
                    break;
                case 'P': case'p':
                    ev = EV_NOEVENT;
                    setProt('p');
                    break;
                case 'l': case 'L':
                    ev = EV_NOEVENT;
                    setLanguage(getLanguage() + 1);
                    break;
                default:
                    break;
            }
        } else {
            setProt(data);

            if (prot_ready) {
                ev = EV_PROT_SERIAL;
            }
        }
    }


    return ev;


}
