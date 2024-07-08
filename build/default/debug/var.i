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
enum
{
    SEC,
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
# 1 "var.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdString(const char *str);
    void lcdInt(int val, char digNum);
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
static unsigned char prot[6];
unsigned int temp;
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

    alarmLevelHigh = dsReadData(0x20);
    alarmLevelLow = dsReadData(0x21);
    language = dsReadData(0x23) != 1 ? 0 : 1;
    if(alarmLevelHigh + alarmLevelLow != dsReadData(0x22)){
        setAlarmLevel(0, 0);
        setAlarmLevel(120, 1);
    }

    (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x00)& 0x7f)) == 0 ? 0 : (bcd2dec(dsReadData(0x00)& 0x7f))),0x00));
    (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x01)& 0x7f)) == 0 ? 45 : (bcd2dec(dsReadData(0x01)& 0x7f))),0x01));
    (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x02)& 0x7f)) == 0 ? 15 : (bcd2dec(dsReadData(0x02)& 0x7f))),0x02));


    (dsWriteData(dec2bcd(18),0x04));
    (dsWriteData(dec2bcd(10),0x05));
# 52 "var.c"
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
        case 0: return (bcd2dec(dsReadData(0x00)& 0x7f));
        case 1: return (bcd2dec(dsReadData(0x01)& 0x7f));
        case 2: return (bcd2dec(dsReadData(0x02)& 0x7f));
        case 3: return (bcd2dec(dsReadData(0x04)& 0xcf));
        case 4: return (bcd2dec(dsReadData(0x05)& 0x3f));
        case 5: return (bcd2dec(dsReadData(0x06)& 0xff));
    }
}

void setTime(int newTime, char index) {
    switch(index)
    {
        case 0: return (dsWriteData(dec2bcd(newTime),0x00));
        case 1: return (dsWriteData(dec2bcd(newTime),0x01));
        case 2: return (dsWriteData(dec2bcd(newTime),0x02));
        case 3: return (dsWriteData(dec2bcd(newTime),0x04));
        case 4: return (dsWriteData(dec2bcd(newTime),0x05));
        case 5: return (dsWriteData(dec2bcd(newTime),0x06));
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


    language = newLanguage % 2;
    dsWriteData(language, 0x23);
}

unsigned char* getProt() {

    return prot;
}

void setProt(char newChar) {

    prot[index++] = newChar;

    if(index == 6) prot_ready = 1;
}

void resetProt()
{
    char i = 0;
    while (i < 6)
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
