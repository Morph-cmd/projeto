# 1 "stateMachine.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "stateMachine.c" 2
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
# 1 "stateMachine.c" 2

# 1 "./stateMachine.h" 1
# 14 "./stateMachine.h"
enum {
    STATE_ALARMEL = 0,
    STATE_ALARMEH,
    STATE_TEMPO,
    STATE_TEMPOM,
    STATE_IDIOMA,
    STATE_MAIN,
    STATE_FIM
};


void smInit(void);
void smLoop(void);
# 2 "stateMachine.c" 2

# 1 "./event.h" 1
# 10 "./event.h"
enum{
    EV_B_0,
    EV_B_1,
    EV_B_2,
    EV_B_3,
    EV_B_4,
    EV_PROT_SERIAL,
    EV_NOEVENT
};
void eventInit(void);
unsigned char eventRead(void);
# 3 "stateMachine.c" 2

# 1 "./output.h" 1
# 10 "./output.h"
void outputInit(void);
void outputPrint(int numTela, int idioma);
# 4 "stateMachine.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdString(const char *str);
    void lcdInt(int val, char digNum);
# 5 "stateMachine.c" 2

# 1 "./keypad.h" 1
# 23 "./keypad.h"
 unsigned char kpRead(void);
 void kpDebounce(void);
 void kpInit(void);
# 6 "stateMachine.c" 2

# 1 "./ds1307.h" 1
# 15 "./ds1307.h"
 void dsInit(void);
 void dsStartClock(void);
 void dsStopClock(void);
 int dec2bcd(int value);
 int bcd2dec(int value);
 void dsWriteData(unsigned char value, int address);
 int dsReadData(int address);
# 7 "stateMachine.c" 2


char estado_ant = STATE_ALARMEL;
long int t;

void smInit(void) {
    varInit();
    setState(STATE_MAIN);
    eventInit();
    t = 0;
}

void smLoop(void) {
    unsigned char evento;



    evento = eventRead();
    if (evento == EV_NOEVENT) {
        t++;
    } else {
        t = 0;
    }
    if (t == 3000) {
        setState(STATE_MAIN);

    }

    switch (getState()) {
        case STATE_ALARMEL:
            if (evento == EV_B_0) {
                setAlarmLevel(getAlarmLevel(0) - 1, 0);
            }

            if (evento == EV_B_1) {
                setAlarmLevel(getAlarmLevel(0) + 1, 0);
            }

            if (evento == EV_B_2) {
                setState(STATE_TEMPOM);
            }

            if (evento == EV_B_3) {
                setState(STATE_ALARMEH);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_ALARMEL;
            }
            break;

        case STATE_ALARMEH:
            if (evento == EV_B_0) {
                setAlarmLevel(getAlarmLevel(1) - 1, 1);
            }

            if (evento == EV_B_1) {
                setAlarmLevel(getAlarmLevel(1) + 1, 1);
            }

            if (evento == EV_B_2) {
                setState(STATE_ALARMEL);
            }

            if (evento == EV_B_3) {
                setState(STATE_IDIOMA);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_ALARMEH;
            }
            break;



        case STATE_IDIOMA:

            if (evento == EV_B_2) {
                setState(STATE_ALARMEH);
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPO);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_IDIOMA;
            }

            if (evento == EV_B_0) {

                setLanguage(getLanguage() + 1);

            }

            if (evento == EV_B_1) {
                setLanguage(getLanguage() - 1);
            }


            break;
        case STATE_TEMPO:


            if (evento == EV_B_0) {

                (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x02)& 0x7f)) - 1),0x02));
            }
            if (evento == EV_B_1) {
                (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x02)& 0x7f)) + 1),0x02));
            }
            if (evento == EV_B_2) {
                setState(STATE_IDIOMA);
            }

            if (evento == EV_B_3) {
                setState(STATE_TEMPOM);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }

            break;

        case STATE_TEMPOM:


            if (evento == EV_B_0) {

                (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x01)& 0x7f)) - 1),0x01));
            }
            if (evento == EV_B_1) {
                (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x01)& 0x7f)) + 1),0x01));
            }
            if (evento == EV_B_2) {
                setState(STATE_TEMPO);
            }

            if (evento == EV_B_3) {
                setState(STATE_ALARMEL);
            }

            if (evento == EV_B_4) {
                setState(STATE_MAIN);
                estado_ant = STATE_TEMPO;
            }

            break;

        case STATE_MAIN:
            if (evento == EV_B_4)
                setState(estado_ant);

            if (evento == EV_B_0)
                (dsWriteData(dec2bcd((bcd2dec(dsReadData(0x01)& 0x7f)) + 1),0x01));

            if (evento == EV_B_1) {

            }
            break;
    }

    if (evento == EV_PROT_SERIAL) {
        unsigned char* prot;
        prot = getProt();

        switch (prot[1]) {
            case 't': case 'T':
                switch (prot[2]) {
                    case 'l': case 'L':
                    {
                        int l = (prot[3] - '0') * 100;
                        l += (prot[4] - '0') * 10;
                        l += (prot[5] - '0') * 1;
                        setAlarmLevel(l, 0);
                    }
                    case 'h': case 'H':
                    {
                        int h = (prot[3] - '0') * 100;
                        h += (prot[4] - '0') * 10;
                        h += (prot[5] - '0') * 1;
                        setAlarmLevel(h, 1);
                    }
                        break;
                }
            case 'h': case 'H':
            {
                int h = (prot[2] - '0') * 10;
                h += (prot[3] - '0') * 1;

                if (h <= 23)
                    (dsWriteData(dec2bcd(h),0x02));

                int m = (prot[4] - '0') * 10;
                m += (prot[5] - '0') * 1;

                if (m <= 59)
                    (dsWriteData(dec2bcd(m),0x01));
            }
                break;
        }


        resetProt();
    }



    outputPrint(getState(), getLanguage());
}
