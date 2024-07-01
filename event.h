/* 
 * File:   evento.h
 * Author: Avell
 *
 * Created on 14 de Junho de 2017, 16:09
 */

#ifndef EVENT_H
#define	EVENT_H
enum{
    EV_B_0,
    EV_B_1,
    EV_B_2,
    EV_B_3,
    EV_B_4,
    EV_PROT_SERIAL,
    EV_NOEVENT //NOEVENT
};
void eventInit(void);
unsigned char eventRead(void);

#endif	/* EVENT_H */

