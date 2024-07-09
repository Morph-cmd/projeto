#include "var.h"
#include "lcd.h"
#include "ds1307.h"


//vari�veis a serem armazenadas
static char state;
static char language;
static unsigned char alarmLevelHigh;
static unsigned char alarmLevelLow;
static char index=0;
static unsigned char prot[PROT_TAM];
unsigned int temp;
char *date;
int t[33];
char i;

void varInit(void) {
    state = 0;
    alarmLevelHigh = dsReadData(0x20);
    alarmLevelLow = dsReadData(0x21);
    language = dsReadData(0x23) != 1 ? 0 : 1;
    if(alarmLevelHigh + alarmLevelLow != dsReadData(0x22)){
        setAlarmLevel(0, LOW); 
        setAlarmLevel(150, HIGH);
    }
    
    setSeconds(getSeconds() == 0 ? 0 : getSeconds());
    setMinutes(getMinutes() == 0 ? 45 : getMinutes());
    setHours(getHours() == 0 ? 15 : getHours());
    
    
    setDays(getDays());
    setMonths(getMonths());
    dsWriteData(dsReadData(0x29), 0x29);
    
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
        case 5: return dsReadData(0x29); 
    }
}

void setTime(int newTime, char index) {
    switch(index)
    {
        case 0:  setSeconds(newTime); break;
        case 1:  setMinutes(newTime); break;
        case 2:  setHours(newTime); break;
        case 3:  
            
            if(newTime > 31)
                newTime = 1;
            
            int m = getTime(MON);
            if(m < 8)
            {
                if(m%2 == 0){
                    if(newTime > 30)
                        newTime = 1;
                    else if(newTime == 0)
                        newTime = 30;
                }
                else
                {
                    if(newTime > 31)
                        newTime = 1;
                    else if(newTime == 0)
                        newTime = 31;
                }
            }
            else if(m > 7)
            {
                if(m%2 == 0){
                    if(newTime > 31)
                        newTime = 1;
                    else if(newTime == 0)
                        newTime = 31;
                }
                else
                {
                    if(newTime > 30)
                        newTime = 1;
                    else if(newTime == 0)
                        newTime = 30;
                }
            }
            
            setDays(newTime); 
            
            break;
        case 4:
            if(newTime > 12) newTime = 1;
            else if (newTime <= 0) newTime = 12; 
            
            setMonths(newTime);
            break;
        case 5:  dsWriteData(newTime, 0x29); break;
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
    
    temp = 0;
}

