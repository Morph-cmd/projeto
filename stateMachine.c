#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"

void smInit(void) {
    setState(STATE_ALARME);
    eventInit();
}

void smLoop(void) {
    unsigned char evento;

    //m�quina de estados
    evento = eventRead();

    switch (getState()) {
        case STATE_ALARME:
            //execu��o de atividade
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setLanguage(getLanguage() + 1);
                
            }
            
            if (evento == EV_B_1) {
                setLanguage(getLanguage() - 1);
            }
            
            if(evento == EV_PROT_SERIAL)
            {
                lcdData('s');
                unsigned char prot[4];
                getProt(prot);
                
                for(int i = 0; i < 4; i++)
                {
                    lcdData(prot[i]);
                }
                resetProt();
            }
            /*
            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_TEMPO);
            }
            break;
        case STATE_TEMPO:

            //execu��o de atividade
            if (evento == EV_RIGHT) {
                setTime(getTime() + 1);
            }
            if (evento == EV_LEFT) {
                setTime(getTime() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_IDIOMA);
            }
            break;

        case STATE_IDIOMA:

            //execu��o de atividade
            if (evento == EV_RIGHT) {
                setLanguage(getLanguage() + 1);
            }
            if (evento == EV_LEFT) {
                setLanguage(getLanguage() - 1);
            }

            //gest�o da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_ALARME);
            }
            break;
             * */

    }
    //outputPrint(getState(), getLanguage());
}
