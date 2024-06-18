#include "var.h"
#include "lcd.h"



//variáveis a serem armazenadas
static char state;
static char language;
static int time;
static int alarmLevel;
static char index=0;
static unsigned char prot[PROT_TAM];


void varInit(void) {
    state = 0;
    time = 1000;
    alarmLevel = 512;
}

char getState(void) {
    return state;
}

void setState(char newState) {
    state = newState;
}

int getTime(void) {
    return time;
}

void setTime(int newTime) {
    time = newTime;
}

int getAlarmLevel(void) {
    return alarmLevel;
}

void setAlarmLevel(int newAlarmLevel) {
    alarmLevel = newAlarmLevel;
}

char getLanguage(void) {
    return language;
}

void setLanguage(char newLanguage) {
    //só tem 2 linguas
    //usando resto pra evitar colocar valor errado
    language = newLanguage % 2;
}

unsigned char* getProt() {

    return prot;
}

void setProt(char newChar) {
    
    prot[index++] = newChar;
    //lcdData(newChar);
    if(index == PROT_TAM) prot_ready = 1;
}

void resetProt()
{
    char i = 0;
    while (i < PROT_TAM)
    {
        prot[i] = 0;
        i++;
    }
    prot_ready = 0;
    index = 0;
}