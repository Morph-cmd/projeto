# 1 "var.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "var.c" 2
# 1 "./var.h" 1
# 11 "./var.h"
void varInit(void);

char getState(void);
void setState(char newState);
int getTime(void);
void setTime(int newTime);
int getAlarmLevel(void);
void setAlarmLevel(int newAlarmLevel);
char getLanguage(void);
void setLanguage(char newLanguage);
# 1 "var.c" 2



static char state;
static char language;
static int time;
static int alarmLevel;

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


char getLanguage(void){
    return language;
}
void setLanguage(char newLanguage){


    language = newLanguage%2;
}
