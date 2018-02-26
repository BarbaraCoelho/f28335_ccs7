/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: Barbara Coelho, Joao Antonio Cardoso
 *
 *  Description: Código para testar a Malha de Corrente
 *
 *  References: http://www.ti.com/product/TMS320F28335/technicaldocuments
 *
 *
 *  TODO: TESTAR SE O CONTROLE ESTÁ ACONTECENDO, BOTAR UM LED DENTRO DO CTRL
 *  _LOOP
 *
 */

#include "main.h"

void main(void)
{

    my_leds_init();

    // Necessário para as funções que utilizam macros dos .asm, como o InitAdc.
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
    InitFlash();    // call InitFlash in RAM (SARAM - L0)

    InitSysCtrl();

    DINT;           // Disable Global interrupt

    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;


    InitPieVectTable();

    my_xint_init();
    my_buttons_init();
    my_epwm_init();
    my_adc_init();

#ifdef MY_DEBUG_
    my_scia_init();
#endif

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    machine_init();

    for(;;){

        machine_run();
        //if(sinc1)   led3_set(); // Acrecentar sinc aqui
        //else        led3_clear();
    }

}

