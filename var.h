/* 
 * File:   alarme.h
 * Author: Avell
 *
 * Created on 14 de Junho de 2017, 16:10
 */

#ifndef VAR_H
#define	VAR_H

#define PROT_TAM 6
#define LOW 0
#define HIGH 1

enum 
{
    SEC = 0,
    MIN,
    HOU,
    DAY,
    MON,
    YEA
};

char prot_ready;

void varInit(void);

char getState(void);
void setState(char newState);
int getTime(char index);
void setTime(int newTime, char index);
int getAlarmLevel(int lh);
void setAlarmLevel(int newAlarmLevel, char lh);
char getLanguage(void);
void setLanguage(char newLanguage);
unsigned char* getProt();
void setProt(char newLanguage);
void resetProt();
int getTemp(void);
void readTemp();
void setDate(char* date);
char* getDate(void);

#endif	/* VAR_H */
