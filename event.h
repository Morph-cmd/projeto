/* 
 * File:   evento.h
 * Author: Avell
 *
 * Created on 14 de Junho de 2017, 16:09
 */

#ifndef EVENT_H
#define	EVENT_H
enum{
    EV_0,
    EV_1,
    EV_2,
    EV_3,
    EV_4,
    EV_5 //NOEVENT
};
void eventInit(void);
unsigned int eventRead(void);

#endif	/* EVENT_H */

