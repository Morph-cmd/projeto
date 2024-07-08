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
unsigned int temp;
char *date;
char volt;
char voltMin;
int maxTemp;
int t[33];
char i;

void varInit(void) {
    maxTemp = 100;
    volt = 50;
    voltMin = 33;
    state = 0;
    time = 1000;
    //dsWriteData(50, 0x20);
    alarmLevelHigh = dsReadData(0x20);
    alarmLevelLow = dsReadData(0x21);
    language = dsReadData(0x23) != 1 ? 0 : 1;
    if(alarmLevelHigh + alarmLevelLow != dsReadData(0x22)){
        setAlarmLevel(0, LOW); 
        setAlarmLevel(120, HIGH);
    }
    
    setSeconds(getSeconds() == 0 ? 0 : getSeconds());
    setMinutes(getMinutes() == 0 ? 45 : getMinutes());
    setHours(getHours() == 0 ? 15 : getHours());
    
    
    setDays(18);
    setMonths(10);
    //setYears(4);
    
    //setYears(getYears() == 1 ? 4 : getYears());
    
    /*
    setDays(getDays() == 1 ? 8 : getDays());
    setMonths(getMonths() == 1 ? 7 : getMonths());
    setYears(getYears() == 1 ? 4 : getYears());
    */
}


char getState(void) {
    return state;
}

void setState(char newState) {
    state = newState;
    lcdCommand(0x01);
}

int getTime(char index) {
    switch(index)
    {
        case 0: return getSeconds(); 
        case 1: return getMinutes(); 
        case 2: return getHours(); 
        case 3: return getDays(); 
        case 4: return getMonths(); 
        case 5: return getYears(); 
    }
}

void setTime(int newTime, char index) {
    switch(index)
    {
        case 0: return setSeconds(newTime); 
        case 1: return setMinutes(newTime); 
        case 2: return setHours(newTime); 
        case 3: return setDays(newTime); 
        case 4: return setMonths(newTime); 
        case 5: return setYears(newTime); 
    }
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

int getTemp(void)
{
    return temp;
}
void readTemp()
{
    t[i++] = (adcRead() - 230) * ((float)100/77);
    
    int tempT = 0;
    for(char j = 0; j < 33; j++)
    {
        tempT += t[j];
    }
    tempT /= 33;
    
    if(i >= 33){
        i = 0;
        temp = tempT;
    }
}

void setDate(char* date)
{
    /*if(date[0] >= 3)
    {
        char mes = date[2] * 10 + date[3];
        switch(mes){
            case 1: if(date[1] > 1){date[0] = 0; date[1] = 0;} break;
            case 2: break;
            case 3: if(date[1] > 1){date[0] = 0; date[1] = 0;} break;
            case 4: if(date[1] > 0){date[0] = 0; date[1] = 0;} break;
            case 5: if(date[1] > 1){date[0] = 0; date[1] = 0;} break;
            case 6: if(date[1] > 0){date[0] = 0; date[1] = 0;} break;
            case 7: if(date[1] > 1){date[0] = 0; date[1] = 0;} break;
            case 8: if(date[1] > 1){date[0] = 0; date[1] = 0;} break;
            case 9: if(date[1] > 0){date[0] = 0; date[1] = 0;} break;
            case 10: if(date[1] > 1){date[0] = 0; date[1] = 0;} break;
            case 11: if(date[1] > 0){date[0] = 0; date[1] = 0;} break;
            case 12: if(date[1] > 1){date[0] = 0; date[1] = 0;} break;
        }
    }

    if(date[0] >= 2 && date[2] == 0 && date[3] == 2)
    {
        if(date[1] > 8){date[0] = 0; date[1] = 0;}
    }

    if(date[2] >= 1 && date[3] >= 3)
    {
        date[2] = 0;
        date[3] = 0;
    }
    
    //negativos
    if(date[1] < 0)
    {
        date[0] = 3;
        date[1] = 0;
    }

    if(date[3] < 0)
    {
        date[2] = 1;
        date[3] = 2;
    }*/
    
    setTime(date[0] * 10 + date[1], DAY);
    setTime(date[2] * 10 + date[3], MON);
    setTime(date[4] * 10 + date[5], YEA);
    
}
char* getDate(void)
{
    return date;
}
