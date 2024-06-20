#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"
#include "ds1307.h"

#define NUM_IDIOMAS 2

//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs[STATE_FIM][NUM_IDIOMAS] = {
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
        lcdInt(getHours(), 2);
        lcdData(':');
        lcdInt(getMinutes(), 2);
        lcdData(':');
        lcdInt(getSeconds(), 2);
        lcdString("           "); //para apagar os textos depois do numero
    }
    if (numTela == STATE_TEMPOM) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        
        lcdInt(getHours(), 2);
        lcdData(':');
        lcdData('>');
        lcdInt(getMinutes(), 2);
        lcdData(':');
        lcdInt(getSeconds(), 2);
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
        lcdString(msgs[numTela][idioma]);
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
        lcdInt(getHours(), 2);
        lcdData(':');
        lcdInt(getMinutes(), 2);
        lcdData(':');
        lcdInt(getSeconds(), 2);
        lcdString("           ");
        
        //lcdInt(getSeconds());
        //lcdData(':');
 
        
        
        
    }

}

