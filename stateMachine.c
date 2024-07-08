#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"
#include "pic18f4520.h"
#include <pic18f4550.h>

char estado_ant = STATE_ALARMEL;
unsigned long int t;

void smInit(void) {
    varInit();
    setState(STATE_MAIN);
    eventInit();
    t = 0;
}

void smLoop(void) {
    unsigned char evento;
    readTemp();
    
    
    //máquina de estados
    evento = eventRead();
    if (evento == EV_NOEVENT) {
        t++;
    } else {
        t = 0;
    }
    if (t == 3000) {
        setState(STATE_MAIN);

    }

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

            if (evento == EV_B_4) {
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

            if (evento == EV_B_4) {
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

            if (evento == EV_B_4) {
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
                setTime(getTime(HOU) - 1, HOU);
            }
            if (evento == EV_B_1) {
                setTime(getTime(HOU) + 1, HOU);
            }
            if (evento == EV_B_2) {
                setState(STATE_IDIOMA);
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPOM);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }

            break;

        case STATE_TEMPOM:

            //execução de atividade
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setTime(getTime(MIN) - 1, MIN);
            }
            if (evento == EV_B_1) {
                setTime(getTime(MIN) + 1, MIN);
            }
            if (evento == EV_B_2) {
                setState(STATE_TEMPO);
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPOD);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }

            break;
            
            case STATE_TEMPOD:

            //execução de atividade
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                char* date = getDate();
                date[1]--;
                if(date[1] < 0)
                {
                    date[1] = 9;
                    date[0]--;
                }
                setDate(date);
            }
            if (evento == EV_B_1) {
                char* date = getDate();
                date[1]++;
                if(date[1] > 9)
                {
                    date[1] = 0;
                    date[0]++;
                }
                setDate(date);
            }
            if (evento == EV_B_2) {
                setState(STATE_TEMPOM);
                
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPOMO);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }
            
            break;
            case STATE_TEMPOMO:

            //execução de atividade
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setTime(getTime(MON) - 1, MON);
            }
            if (evento == EV_B_1) {
                setTime(getTime(MON) + 1, MON);
            }
            if (evento == EV_B_2) {
                setState(STATE_TEMPOD);
            }

            if (evento == EV_B_3) {
                setState(STATE_ALARMEL);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }
            break;
            /*
            case STATE_TEMPOY:

            //execução de atividade
            if (evento == EV_B_0) {
                //setAlarmLevel(getAlarmLevel() + 1);
                setTime(getTime(YEA) - 1, YEA);
            }
            if (evento == EV_B_1) {
                setTime(getTime(YEA) + 1, YEA);
            }
            if (evento == EV_B_2) {
                setState(STATE_TEMPOMO);
            }

            if (evento == EV_B_3) {
                setState(STATE_ALARMEL);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }

            break;
            */
        case STATE_MAIN:
            if (evento == EV_B_4)
                setState(estado_ant);

            if (evento == EV_B_0)
                setTime(getTime(MIN) + 1, MIN);

            if (evento == EV_B_1) {

            }
            break;
        
        case STATE_ALERTA:
            if(t%300 < 150)
                LATA = 0xff;
            else
                LATA = 0x00;
            
            break;
            
    }

    if (evento == EV_PROT_SERIAL) {
        unsigned char* prot;
        prot = getProt();

        switch (prot[1]) {
            case 't': case 'T':
                switch (prot[2]) {
                    case 'l': case 'L':
                    {
                        int l = (prot[3] - '0') * 100;
                        l += (prot[4] - '0') * 10;
                        l += (prot[5] - '0') * 1;
                        setAlarmLevel(l, LOW);
                    }
                    case 'h': case 'H':
                    {
                        int h = (prot[3] - '0') * 100;
                        h += (prot[4] - '0') * 10;
                        h += (prot[5] - '0') * 1;
                        setAlarmLevel(h, HIGH);
                    }
                        break;
                }
            case 'h': case 'H':
            {
                int h = (prot[2] - '0') * 10;
                h += (prot[3] - '0') * 1;

                if (h <= 23)
                    setTime(h, HOU);

                int m = (prot[4] - '0') * 10;
                m += (prot[5] - '0') * 1;

                if (m <= 59)
                    setTime(m, MIN);
            }
                break;
        }


        resetProt();
    }

    //Controle da temperatura
    int temp = getTemp();
    
    if(getState() != STATE_ALERTA && (temp < getAlarmLevel(LOW) || temp > getAlarmLevel(HIGH)))
    {
        setState(STATE_ALERTA);
    }


    outputPrint(getState(), getLanguage());
}
