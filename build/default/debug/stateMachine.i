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
# 1 "stateMachine.c" 2

# 1 "./stateMachine.h" 1
# 14 "./stateMachine.h"
enum {
    STATE_ALARME,
    STATE_TEMPO,
    STATE_IDIOMA,
    STATE_FIM
};


void smInit(void);
void smLoop(void);
# 2 "stateMachine.c" 2

# 1 "./event.h" 1
# 10 "./event.h"
enum{
    EV_0,
    EV_1,
    EV_2,
    EV_3,
    EV_4,
    EV_5
};
void eventInit(void);
unsigned int eventRead(void);
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
    void lcdInt(int val);
# 5 "stateMachine.c" 2

# 1 "./keypad.h" 1
# 23 "./keypad.h"
 unsigned char kpRead(void);
 void kpDebounce(void);
 void kpInit(void);
# 6 "stateMachine.c" 2


void smInit(void) {
    setState(STATE_ALARME);
    eventInit();
}

void smLoop(void) {
    unsigned char evento;


    evento = eventRead();

    switch (getState()) {
        case STATE_ALARME:

            if (evento == EV_0) {

                setLanguage(getLanguage() + 1);

            }

            if (evento == EV_1) {
                setLanguage(getLanguage() - 1);
            }
# 70 "stateMachine.c"
    }
    outputPrint(getState(), getLanguage());
}
