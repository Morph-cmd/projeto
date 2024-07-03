/*
 * File:   main.c
 * Author: André Luiz
 *
 * Created on 15 de Abril de 2024, 11:42
 */


#include "adc.h"
#include "config.h"
#include "stateMachine.h"
#include "pic18f4520.h"
#include <pic18f4550.h>
#include "lcd.h"
#include "serial.h"
#include "bits.h"
#include "keypad.h"
#include "soft_i2c.h"
#include "ds1307.h"
#include <xc.h>

//inicio do programa

void main(void) {
    
    //char slot;
    //inicializações
    kpInit();
    
    dsInit();
    smInit();
    serialInit();
    TRISA = 0x00;
    PORTA = 0x00;
    LATA = 0x00;
    adcInit();
    lcdInit();
    
    //dsWriteData(0x80,SEC);
    while (1) {
        /*kpDebounce();
        smLoop();*/
        unsigned int v = adcRead();
        
        lcdCommand(0x80);
        lcdInt(v, 5);
        
        //Tecla 1 (SW1)
        /*if (!BitTst(PORTB, 2)) 
            BitSet(PORTA, 0);
        else{
            BitClr (LATA, 0);
        }
        //Tecla 2(SW2)
        if (!BitTst(PORTB, 3)) 
            BitSet(LATA, 1);
        else{
            BitClr (LATA, 1);
        }
        //Tecla 3 (SW4)
        if (!BitTst(PORTB, 5)) 
            BitSet(LATA, 2);
        else{
            BitClr (LATA, 2);
        }
        //Tecla 4 (SW5)
        if (!BitTst(PORTB, 4)) 
            BitSet(LATA, 3);
        else{
            BitClr (LATA, 3);
        }
        //Tecla 5 (SW6)
        if (!BitTst(PORTE, 1))
            BitSet(LATA, 0);
        else{
            BitClr (LATA, 0);
        }
        if (!BitTst(PORTE, 1))
            BitSet(LATA, 1);
        else{
            BitClr (LATA, 1);
        }
        if (!BitTst(PORTE, 1))
            BitSet(LATA, 2);
        else{
            BitClr (LATA, 2);
        }
        if (!BitTst(PORTE, 1))
            BitSet(LATA, 3);
        else{
            BitClr (LATA, 3);
        }*/
    }
}