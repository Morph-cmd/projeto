# 1 "event.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "event.c" 2
# 1 "./keypad.h" 1
# 23 "./keypad.h"
 unsigned char kpRead(void);
 void kpDebounce(void);
 void kpInit(void);
# 1 "event.c" 2

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
unsigned int eventRead(void);
# 2 "event.c" 2

# 1 "./pic18f4520.h" 1
# 3 "event.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdString(const char *str);
    void lcdInt(int val);
# 4 "event.c" 2

# 1 "./serial.h" 1
# 23 "./serial.h"
 void serialSend(unsigned char c);
 unsigned char serialRead(void);
 void serialInit(void);
# 5 "event.c" 2

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
void getProt(unsigned char[]);
void setProt(char newLanguage);
void resetProt();
# 6 "event.c" 2





static unsigned int ev_ant;
static unsigned int key_ant;
static unsigned int key;
static unsigned int dTimer;
static unsigned int dTimerMax;
static unsigned int ev = 'b';


void eventInit(void) {
    kpInit();

    ev_ant = 0;
    key = 1;
}

void delay2ms(void) {
    unsigned char j, k;
    for (j = 0; j < 20; j++)
        for (k = 0; k < 178; k++);
}

unsigned int eventRead(void) {
    int key;
    int ev = EV_NOEVENT;
    key = kpRead();
    if (key != key_ant) {
        if (((key) & (1<<0))) {
            ev = EV_B_0;
        }

        if (((key) & (1<<1))) {
            ev = EV_B_1;
        }

        if (((key) & (1<<2))) {

        }
    }

    key_ant = key;


    unsigned char data = serialRead();
    unsigned char prot[4];
    if (data != 0) {
        serialSend(data);
        getProt(prot);
        if (prot[0] == 0) {
            switch (data) {
                case '0':
                    ev = EV_B_0;
                    break;
                case '1':
                    ev = EV_B_1;
                    break;
                case '2':
                    ev = EV_B_2;
                    break;
                case '3':
                    ev = EV_B_3;
                    break;
                case '4':
                    ev = EV_B_4;
                    break;
                case 'P': case'p':
                    ev = EV_NOEVENT;
                    setProt('p');

                    break;
                default:
                    break;
            }
        } else {
            setProt(data);

            if(prot_ready)
            {
                ev = EV_PROT_SERIAL;
                lcdData('k');
            }
        }
    }


    return ev;


}