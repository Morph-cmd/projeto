// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: ssd.c
//            Biblioteca de controle dos displays de 7 segmentos
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licen�a: GNU GPL 2
//   Modifica��es: Placa PICGenius por D�cio Renn� de M. Faria
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

//#define PICGENIUS

#include "ssd.h"
#include "pic18f4520.h"

//vetor para armazenar a convers�o do display
static const char valor[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
//armazena qual � o display disponivel
static char display;
//armazena o valor a ser enviado ao display
static char v0, v1, v2, v3;

void ssdDigit(char val, char pos) {
    if (pos == 0) {
        v0 = val;
    }
    if (pos == 1) {
        v1 = val;
    }
    if (pos == 2) {
        v2 = val;
    }
    if (pos == 3) {
        v3 = val;
    }

}

void ssdUpdate(void) {
    //desliga todos os displays
    PORTA = 0x00;
    PORTE = 0x00;
    //desliga todos os leds
    PORTD = 0x00;

    switch (display) //liga apenas o display da vez
    {
        case 0:
            PORTD = valor[v0];
#ifdef PICGENIUS
            BitSet(PORTA, 5);
#else
            BitSet(PORTA, 5);
#endif
            display = 1;
            break;

        case 1:
            PORTD = valor[v1];
#ifdef PICGENIUS
            BitSet(PORTA, 4);
#else
            BitSet(PORTA, 2);
#endif            
            display = 2;
            break;

        case 2:
            PORTD = valor[v2];
#ifdef PICGENIUS
            BitSet(PORTA, 3);
#else
            BitSet(PORTE, 0);
#endif            
            display = 3;
            break;

        case 3:
            PORTD = valor[v3];
#ifdef PICGENIUS
            BitSet(PORTA, 2);
#else
            BitSet(PORTE, 2);
#endif            
            display = 0;
            break;

        default:
            display = 0;
            break;
    }
}

void ssdInit(void) {
    v0 = 0;
    v1 = 0;
    v2 = 0;
    v3 = 0;
    //configura��o dos pinos de controle
#ifdef PICGENIUS
    BitClr(TRISA, 2);
    BitClr(TRISA, 3);
    BitClr(TRISA, 4);
    BitClr(TRISA, 5);
#else
    BitClr(TRISA, 2);
    BitClr(TRISA, 5);
    BitClr(TRISE, 0);
    BitClr(TRISE, 2);
#endif
    ADCON1 = 0x0E; //apenas AN0 � analogico, a referencia � baseada na fonte
    TRISD = 0x00; //Porta de dados

}