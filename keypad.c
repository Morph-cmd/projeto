// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2014
// -----------------------------------------------------------------------
//   Arquivo: keypad.c
//            Biblioteca de operação de um teclado matricial
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
//   Modificações: Placa PICGenius por Décio Rennó de M. Faria
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

#include "keypad.h"
#include "pic18f4520.h"

static unsigned char valor = 0x00;


unsigned char kpRead(void) {
    return valor;
}

void kpDebounce(void) {
#ifdef PICGENIUS
    if (!BitTst(PORTB, 0)) valor = 1;
    if (!BitTst(PORTB, 1)) valor = 64;
    if (!BitTst(PORTB, 2)) valor = 16;
    if (!BitTst(PORTB, 3)) valor = 4;
    if (!BitTst(PORTB, 4)) valor = 128;
    if (!BitTst(PORTB, 5)) valor = 32;
#else 
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned char valorNovo = 0x00000;
    static unsigned char valorAntigo = 0x00000;
    char portes[5] = {PORTB, PORTB, PORTB, PORTB, PORTE};
    char bits[5] = {2, 3, 5, 4, 1};

    /*for (i = 0; i < 4; i++) {
        TRISB = ~((unsigned char) 1 << i);
        PORTB = ~((unsigned char) 1 << i);

        //realiza o teste para cada bit e atualiza a variável
        for (j = 0; j < 2; j++) {
            if (!BitTst(PORTB, j + 4)) {
                BitSet(valorNovo, (i * 2) + j);
            } else {
                BitClr(valorNovo, (i * 2) + j);
            }
        }
    }*/
    for (j = 0; j < 5; j++) {
            if (!BitTst(portes[j], bits[j])) {
                BitSet(valorNovo, j);
            } else {
                BitClr(valorNovo, j);
            }
        }
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }
#endif
}

void kpInit(void) {
    TRISB = 0xFF; //quatro entradas e quatro saidas
    BitClr(INTCON2, 7); //liga pull up
    ADCON1 = 0b00001110; //apenas AN0 é analogico, a referencia é baseada na fonte

#ifdef PIC18F4550
    SPPCFG = 0x00; // SFR nao presente no PIC18F4520
#endif
}