#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"
#include "ds1307.h"

char estado_ant = STATE_ALARMEL;

void smInit(void) {
    varInit();
    setState(STATE_MAIN);
    eventInit();
}


void smLoop(void) {
    unsigned char evento;

    //máquina de estados
    evento = eventRead();

    switch (getState()) {
        case STATE_ALARMEL:
            if (evento == EV_B_0) {
                setAlarmLevel(getAlarmLevel(LOW) - 1, LOW);
            }
            
            if (evento == EV_B_1) {
                setAlarmLevel(getAlarmLevel(LOW) + 1, LOW);
            }
            
            if (evento == EV_B_2) {
                setState(STATE_TEMPOM);
            }

            if (evento == EV_B_3) {
                setState(STATE_ALARMEH);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_MAIN);
                estado_ant = STATE_ALARMEL;
            }
            break;
        
        case STATE_ALARMEH:
            if (evento == EV_B_0) {
                setAlarmLevel(getAlarmLevel(HIGH) - 1, HIGH);
            }
            
            if (evento == EV_B_1) {
                setAlarmLevel(getAlarmLevel(HIGH) + 1, HIGH);
            }
            
            if (evento == EV_B_2) {
                setState(STATE_ALARMEL);
            }

            if (evento == EV_B_3) {
                setState(STATE_IDIOMA);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_MAIN);
                estado_ant = STATE_ALARMEH;
            }
            break;
            
         
            
        case STATE_IDIOMA:
            //execução de atividade
            if (evento == EV_B_2) {
                setState(STATE_ALARMEH);
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPO);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_MAIN);
                estado_ant = STATE_IDIOMA;
            }
            
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setLanguage(getLanguage() + 1);

            }

            if (evento == EV_B_1) {
                setLanguage(getLanguage() - 1);
            }

            
            break;
        case STATE_TEMPO:

            //execução de atividade
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setHours(getHours() - 1);
            }
            if (evento == EV_B_1) {
                setHours(getHours() + 1);
            }
            if (evento == EV_B_2) {
                setState(STATE_IDIOMA);
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPOM);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }
            
            break;
            
        case STATE_TEMPOM:

            //execução de atividade
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setMinutes(getMinutes() - 1);
            }
            if (evento == EV_B_1) {
                setMinutes(getMinutes() + 1);
            }
            if (evento == EV_B_2) {
                setState(STATE_TEMPO);
            }

            if (evento == EV_B_3) {
                setState(STATE_ALARMEL);
            }
            
            if(evento == EV_B_4)
            {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }
            
            break;
            
        case STATE_MAIN:
            if(evento == EV_B_4)
                setState(estado_ant);
            
            if(evento == EV_B_0)
                setMinutes(getMinutes() + 1);
            
            if(evento == EV_B_1){
                
            }
            break;
    }
    
    if (evento == EV_PROT_SERIAL) {
        unsigned char* prot;
        prot = getProt();
        
        switch(prot[1])
        {
            
        }
        

        resetProt();
    }
    
    outputPrint(getState(), getLanguage());
}
