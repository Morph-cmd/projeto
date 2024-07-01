#include "var.h"
#include "lcd.h"
#include "ds1307.h"


//vari�veis a serem armazenadas
static char state;
static char language;
static int time;
static unsigned char alarmLevelHigh;
static unsigned char alarmLevelLow;
static char index=0;
static unsigned char prot[PROT_TAM];


void varInit(void) {
    state = 0;
    time = 1000;
    //dsWriteData(50, 0x20);
    alarmLevelHigh = dsReadData(0x20);
    alarmLevelLow = dsReadData(0x21);
    language = dsReadData(0x23) != 1 ? 0 : 1;
    if(alarmLevelHigh + alarmLevelLow != dsReadData(0x22)){
        setAlarmLevel(50, LOW); 
        setAlarmLevel(100, HIGH);
    }
    
    setSeconds(getSeconds() == 0 ? 0 : getSeconds());
    setMinutes(getMinutes() == 0 ? 45 : getMinutes());
    setHours(getHours() == 0 ? 15 : getHours());
}


char getState(void) {
    return state;
}

void setState(char newState) {
    state = newState;
    lcdCommand(0x01);
}

int getTime(void) {
    return time;
}

void setTime(int newTime) {
    time = newTime;
}

int getAlarmLevel(int lh) {
    int l;
    if(lh == 0){
        l = alarmLevelLow;
    }
    else
    {
        l = alarmLevelHigh;
    }
    return l;
}

void setAlarmLevel(int newAlarmLevel, char lh) {
    if(lh == 1){
        alarmLevelHigh = newAlarmLevel;
        
        dsWriteData(alarmLevelHigh, 0x20);
    }
    else
    {
        alarmLevelLow = newAlarmLevel;
        
        dsWriteData(alarmLevelLow, 0x21);
    }
    dsWriteData(alarmLevelHigh + alarmLevelLow, 0x22);
    
}

char getLanguage(void) {
    return language;
}

void setLanguage(char newLanguage) {
    //s� tem 2 linguas
    //usando resto pra evitar colocar valor errado
    language = newLanguage % 2;
    dsWriteData(language, 0x23);
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