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
# 13 "./var.h"
char prot_ready;

void varInit(void);

char getState(void);
void setState(char newState);
int getTime(void);
void setTime(int newTime);
int getAlarmLevel(void);
void setAlarmLevel(int newAlarmLevel);
char getLanguage(void);
void setLanguage(char newLanguage);
unsigned char* getProt();
void setProt(char newLanguage);
void resetProt();
# 1 "var.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdString(const char *str);
    void lcdInt(int val);
# 2 "var.c" 2





static char state;
static char language;
static int time;
static int alarmLevel;
static char index=0;
static unsigned char prot[4];


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


    language = newLanguage % 2;
}

unsigned char* getProt() {

    return prot;
}

void setProt(char newChar) {

    prot[index++] = newChar;

    if(index == 4) prot_ready = 1;
}

void resetProt()
{
    char i = 0;
    while (i < 4)
    {
        prot[i] = 0;
        i++;
    }
    prot_ready = 0;
    index = 0;
}
