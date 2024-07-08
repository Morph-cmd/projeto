#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"
#include "ds1307.h"

#define NUM_IDIOMAS 2

long int m;

//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs[STATE_FIM][NUM_IDIOMAS] = {
    {"Alterar alarme ", "Change alarm   "},
    {"Alterar alarme ", "Change alarm   "},
    {"Alterar tempo  ", "Change time    "},
    {"Alterar tempo  ", "Change time    "},
    {"Alterar idioma ", "Change language"}
};

#define ALT_TEMPO 3
#define ALT_IDIOMA 4

void outputInit(void) {
    lcdInit();
}

void outputPrint(int numTela, int idioma) {

    if (numTela == STATE_TEMPO) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        
        lcdData('>');
        lcdInt(getTime(HOU), 2);
        lcdData(':');
        lcdInt(getTime(MIN), 2);
        lcdData(':');
        lcdInt(getTime(SEC), 2);
        lcdString("           "); //para apagar os textos depois do numero
    }
    if (numTela == STATE_TEMPOM) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        
        lcdInt(getTime(HOU), 2);
        lcdData(':');
        lcdData('>');
        lcdInt(getTime(MIN), 2);
        lcdData(':');
        lcdInt(getTime(SEC), 2);
        lcdString("           "); //para apagar os textos depois do numero
    }
    
    if (numTela == STATE_TEMPOD) {
        lcdCommand(0x80);
        lcdString(msgs[ALT_TEMPO][idioma]);
        lcdCommand(0xC0);
        
        lcdData('>');
        int d = getDays();
        if (d == 0)
            lcdInt(d + 1, 2);
        else
            lcdInt(d, 2);
        lcdData('/');
        
        lcdInt(getMonths(), 2);
        lcdData('/');
        lcdInt(getYears(), 2);
        lcdString("           "); //para apagar os textos depois do numero
    }
    
    if (numTela == STATE_TEMPOMO) {
        lcdCommand(0x80);
        lcdString(msgs[ALT_TEMPO][idioma]);
        lcdCommand(0xC0);
        
        lcdInt(getDays(), 2);
        lcdData('/');
        
        lcdData('>');
        lcdInt(getMonths(), 2);
        lcdData('/');
        lcdInt(getYears(), 2);
        lcdString("           "); //para apagar os textos depois do numero
    }
    
    if (numTela == STATE_ALARMEL) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdData('>');
        lcdInt(getAlarmLevel(LOW), 3);
        lcdData('L');
        lcdString("   ");
        lcdData(' ');
        lcdInt(getAlarmLevel(HIGH), 3);
        lcdData('H');
        
        lcdString("           "); //para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARMEH) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdData(' ');
        lcdInt(getAlarmLevel(LOW), 3);
        lcdData('L');
        lcdString("   ");
        lcdData('>');
        lcdInt(getAlarmLevel(HIGH), 3);
        lcdData('H');
        lcdString("           "); //para apagar os textos depois do numero
    }
    if (numTela == STATE_IDIOMA) {
        lcdCommand(0x80);
        lcdString(msgs[ALT_IDIOMA][idioma]);
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
        lcdInt(getTime(HOU), 2);
        lcdData(':');
        lcdInt(getTime(MIN), 2);
        /*lcdData(':');
        lcdInt(getSeconds(), 2);*/
        lcdString("   ");
        int d = getDays();
        if (d == 0)
            lcdInt(d + 1, 2);
        else
            lcdInt(d, 2);
        lcdData('/');
        lcdInt(getMonths(), 2);
        lcdData('/');
        lcdInt(getYears(), 2);
        
        lcdCommand(0xC0);
        lcdData('L');
        lcdInt(getAlarmLevel(LOW), 3);
        lcdData(' ');
        lcdData(' ');
        
        lcdData('H');
        lcdInt(getAlarmLevel(HIGH), 3);
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

