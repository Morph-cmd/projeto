# 1 "output.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "output.c" 2
# 1 "./output.h" 1
# 10 "./output.h"
void outputInit(void);
void outputPrint(int numTela, int idioma);
# 1 "output.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdString(const char *str);
    void lcdInt(int val, char digNum);
# 2 "output.c" 2

# 1 "./stateMachine.h" 1
# 14 "./stateMachine.h"
enum {
    STATE_ALARMEL = 0,
    STATE_ALARMEH,
    STATE_TEMPO,
    STATE_TEMPOM,
    STATE_TEMPOD,
    STATE_TEMPOMO,
    STATE_TEMPOY,
    STATE_IDIOMA,
    STATE_MAIN,
    STATE_ALERTA,
    STATE_FIM
};


void smInit(void);
void smLoop(void);
# 3 "output.c" 2

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
# 4 "output.c" 2

# 1 "./ds1307.h" 1
# 15 "./ds1307.h"
 void dsInit(void);
 void dsStartClock(void);
 void dsStopClock(void);
 int dec2bcd(int value);
 int bcd2dec(int value);
 void dsWriteData(unsigned char value, int address);
 int dsReadData(int address);
# 5 "output.c" 2




long int m;



static char * msgs[STATE_FIM][2] = {
    {"Alterar alarme ", "Change alarm   "},
    {"Alterar alarme ", "Change alarm   "},
    {"Alterar tempo  ", "Change time    "},
    {"Alterar tempo  ", "Change time    "},
    {"Alterar idioma ", "Change language"}
};




void outputInit(void) {
    lcdInit();
}

void outputPrint(int numTela, int idioma) {

    if (numTela == STATE_TEMPO) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);

        lcdData('>');
        lcdInt((bcd2dec(dsReadData(0x02)& 0x7f)), 2);
        lcdData(':');
        lcdInt((bcd2dec(dsReadData(0x01)& 0x7f)), 2);
        lcdData(':');
        lcdInt((bcd2dec(dsReadData(0x00)& 0x7f)), 2);
        lcdString("           ");
    }
    if (numTela == STATE_TEMPOM) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);

        lcdInt((bcd2dec(dsReadData(0x02)& 0x7f)), 2);
        lcdData(':');
        lcdData('>');
        lcdInt((bcd2dec(dsReadData(0x01)& 0x7f)), 2);
        lcdData(':');
        lcdInt((bcd2dec(dsReadData(0x00)& 0x7f)), 2);
        lcdString("           ");
    }

    if (numTela == STATE_TEMPOD) {
        lcdCommand(0x80);
        lcdString(msgs[3][idioma]);
        lcdCommand(0xC0);

        lcdData('>');
        int d = (bcd2dec(dsReadData(0x04)& 0xcf));
        if (d == 0)
            lcdInt(d + 1, 2);
        else
            lcdInt(d, 2);
        lcdData('/');

        lcdInt((bcd2dec(dsReadData(0x05)& 0x3f)), 2);
        lcdData('/');
        lcdInt((bcd2dec(dsReadData(0x06)& 0xff)), 2);
        lcdString("           ");
    }

    if (numTela == STATE_TEMPOMO) {
        lcdCommand(0x80);
        lcdString(msgs[3][idioma]);
        lcdCommand(0xC0);

        lcdInt((bcd2dec(dsReadData(0x04)& 0xcf)), 2);
        lcdData('/');

        lcdData('>');
        lcdInt((bcd2dec(dsReadData(0x05)& 0x3f)), 2);
        lcdData('/');
        lcdInt((bcd2dec(dsReadData(0x06)& 0xff)), 2);
        lcdString("           ");
    }

    if (numTela == STATE_ALARMEL) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdData('>');
        lcdInt(getAlarmLevel(0), 3);
        lcdData('L');
        lcdString("   ");
        lcdData(' ');
        lcdInt(getAlarmLevel(1), 3);
        lcdData('H');

        lcdString("           ");
    }
    if (numTela == STATE_ALARMEH) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdData(' ');
        lcdInt(getAlarmLevel(0), 3);
        lcdData('L');
        lcdString("   ");
        lcdData('>');
        lcdInt(getAlarmLevel(1), 3);
        lcdData('H');
        lcdString("           ");
    }
    if (numTela == STATE_IDIOMA) {
        lcdCommand(0x80);
        lcdString(msgs[4][idioma]);
        lcdCommand(0xC0);
        if (getLanguage() == 0) {
            lcdString("Portugues       ");
        }
        if (getLanguage() == 1) {
            lcdString("English         ");
        }

    }

    if (numTela == STATE_MAIN) {
        lcdCommand(0x80);
        lcdInt((bcd2dec(dsReadData(0x02)& 0x7f)), 2);
        lcdData(':');
        lcdInt((bcd2dec(dsReadData(0x01)& 0x7f)), 2);


        lcdString("   ");
        int d = (bcd2dec(dsReadData(0x04)& 0xcf));
        if (d == 0)
            lcdInt(d + 1, 2);
        else
            lcdInt(d, 2);
        lcdData('/');
        lcdInt((bcd2dec(dsReadData(0x05)& 0x3f)), 2);
        lcdData('/');
        lcdInt((bcd2dec(dsReadData(0x06)& 0xff)), 2);

        lcdCommand(0xC0);
        lcdData('L');
        lcdInt(getAlarmLevel(0), 3);
        lcdData(' ');
        lcdData(' ');

        lcdData('H');
        lcdInt(getAlarmLevel(1), 3);
        lcdData(' ');
        lcdData(' ');

        lcdData('T');
        lcdInt(getTemp(), 3);

    }
    if (numTela == STATE_ALERTA) {
        lcdCommand(0x80);
        lcdString("TEMPERATURA!!!!");
        lcdCommand(0xC0);
        lcdString("TEMPERATURA!!!!");
    }
}
