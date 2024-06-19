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
        lcdInt(getTime());
        lcdString("           "); //para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARMEL) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdInt(getAlarmLevel(LOW));
        lcdString("           "); //para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARMEH) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdInt(getAlarmLevel(HIGH));
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
        lcdData(((getHours() % 100) / 10) + 48);
        lcdData(((getHours() % 100) % 10) + 48);
        lcdData(':');
        lcdData(((getMinutes() % 100) / 10) + 48);
        lcdData(((getMinutes() % 100) % 10) + 48);
        lcdString("           ");
        
        lcdInt(getSeconds());
        //lcdData(':');
 
        
        
        
    }

}

