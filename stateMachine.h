/* 
 * File:   stateMachine.h
 * Author: Avell
 *
 * Created on 18 de Junho de 2017, 22:17
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H


//estados da maquina de Estados

enum {
    STATE_ALARMEL = 0,
    STATE_ALARMEH,
    STATE_TEMPO,
    STATE_TEMPOM,
    STATE_TEMPOD,
    STATE_TEMPOMO,
    STATE_TEMPOY,       
    STATE_IDIOMA,
    STATE_MAIN,
    STATE_ALERTA,
    STATE_ALERTA1,
    STATE_STANDBY,
    STATE_FIM
};


void smInit(void);
void smLoop(void);


#endif	/* STATEMACHINE_H */

