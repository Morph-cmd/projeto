#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"

char estado_ant;

void smInit(void) {
    setState(STATE_ALARME);
    eventInit();
}

void smLoop(void) {
    unsigned char evento;

    //máquina de estados
    evento = eventRead();

    switch (getState()) {
        case STATE_ALARME:
            if (evento == EV_B_2) {
                setState(STATE_IDIOMA);
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPO);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_HORA);
            }
            break;
        case STATE_IDIOMA:
            //execução de atividade
            if (evento == EV_B_2) {
                setState(STATE_TEMPO);
            }

            if (evento == EV_B_3) {
                setState(STATE_ALARME);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_HORA);
            }
            
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setLanguage(getLanguage() + 1);

            }

            if (evento == EV_B_1) {
                setLanguage(getLanguage() - 1);
            }

            if (evento == EV_PROT_SERIAL) {
                unsigned char* prot;
                prot = getProt();

                if (prot[1] == 'l') {
                    setLanguage(prot[3]);
                }

                resetProt();
            }
            break;
        case STATE_TEMPO:

            //execução de atividade
            
            if (evento == EV_B_2) {
                setState(STATE_ALARME);
            }

            if (evento == EV_B_3) {
                setState(STATE_IDIOMA);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_HORA);
            }
            
            break;
        case STATE_HORA:
            if(evento != EV_B_4)
                setState(STATE_ALARME);
            break;
    }
    outputPrint(getState(), getLanguage());
}
