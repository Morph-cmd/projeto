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
# 15 "./var.h"
char prot_ready;

void varInit(void);

char getState(void);
void setState(char newState);
int getTime(void);
void setTime(int newTime);
int getAlarmLevel(int lh);
void setAlarmLevel(int newAlarmLevel, char lh);
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

# 1 "./ds1307.h" 1
# 15 "./ds1307.h"
 void dsInit(void);
 void dsStartClock(void);
 void dsStopClock(void);
 int dec2bcd(int value);
 int bcd2dec(int value);
 void dsWriteData(unsigned char value, int address);
 int dsReadData(int address);
# 3 "var.c" 2




static char state;
static char language;
static int time;
static unsigned char alarmLevelHigh;
static unsigned char alarmLevelLow;
static char index=0;
static unsigned char prot[5];


void varInit(void) {
    state = 0;
    time = 1000;

    alarmLevelHigh = dsReadData(0x20);
    alarmLevelLow = 35;
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
        alarmLevelLow = newAlarmLevel;
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

    if(index == 5) prot_ready = 1;
}

void resetProt()
{
    char i = 0;
    while (i < 5)
    {
        prot[i] = 0;
        i++;
    }
    prot_ready = 0;
    index = 0;
}
