// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: pwm.c
//            Biblioteca de acesso �s sa�das PWM do PIC18F4520
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

#include "pwm.h"
#include "pic18f4520.h"

void pwmSet1(unsigned char porcento) {
    //formula do duty cycle:
    //DC_porcento = V / ((PR2+1)*4;
    //V = DC/100 * (PR2+1) * 4
    //V = DC * (PR2+1) /25

    unsigned int val = ((unsigned int) porcento) *(PR2 + 1);
    val = val / 25;
    //garante que tem apenas 10 bits
    val &= 0x03ff;
    //os 8 primeiros bits sao colocados no CCPR1L
    CCPR1L = val >> 2;
    //os ultimos dois s�o colocados na posi��o 5 e 4 do CCP1CON
    CCP1CON |= (val & 0x0003) << 4;
}

void pwmSet2(unsigned char porcento) {
    unsigned int val = ((unsigned int) porcento) *(PR2 + 1);
    val /= 25;
    //garante que tem apenas 10 bits
    val &= 0x03ff;
    //os 8 primeiros bits sao colocados no CCPR1L
    CCPR2L = val >> 2;
    //os ultimos dois s�o colocados na posi��o 5 e 4 do CCP1CON
    CCP2CON |= (val & 0x0003) << 4;
#ifdef PICGENIUS
    BitClr(TRISC, 5);  // PICGenius n�o utiliza PWM no aquecedor
    if (porcento) BitSet(PORTC, 5);
    else BitClr(PORTC, 5);
#endif
}

void pwmFrequency(unsigned int freq) {
    //PR2 = fosc/(fpwm*4*prescaler)-1;
    //PR2 = (8000000/(freq*4*16)) - 1;
    PR2 = (125000 / (freq)) - 1;
}

void pwmInit(void) {
    BitClr(TRISC, 1); //configura os pinos correspondentes como sa�das
    BitClr(TRISC, 2);

    T2CON |= 0b00000011; //configura o prescale do timer 2 para 1:16
    BitSet(T2CON, 2); //Liga o timer 2


    CCP1CON |= 0b00001100; //configura CCP1 como um PWM
    CCP2CON |= 0b00001100; //configura CCP2 como um PWM
}