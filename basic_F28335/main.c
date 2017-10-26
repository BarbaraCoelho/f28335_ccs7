/*
 * main.c
 *
 *  Created on: Jun 2, 2017
 *      Author: B�bara Coelho, Jo�o Ant�nio Cardoso
 *
 *  Description: Código para testar a placa do Raul
 *
 *  References: http://www.ti.com/product/TMS320F28335/technicaldocuments
 *
 *  To do:
 *          -Zerar indice da tabela na interr��o do pino de sincronismo
 *
 */

#include "DSP28x_Project.h"
#include "my_buttons.h"
#include "my_leds.h"
#include "my_adc.h"
#include "my_epwm.h"
#include "my_scia.h"
#include "my_sinc.h"
#include "my_machine.h"

#define MY_DEBUG_

// Vari�veis globais, acessiveis a todos os includes atravez do extern
volatile Uint32 dt = 0;
float tabela[419]={0,0.015079,0.030155,0.045224,0.060282,0.075327,0.090354,0.10536,0.12034,0.1353,0.15023,0.16512,0.17997,0.19478,0.20955,0.22427,0.23894,0.25356,0.26811,0.28261,0.29704,0.31141,0.3257,0.33992,0.35406,0.36812,0.3821,0.39599,0.4098,0.4235,0.43712,0.45063,0.46404,0.47734,0.49054,0.50362,0.51659,0.52945,0.54218,0.55479,0.56727,0.57962,0.59184,0.60393,0.61588,0.62769,0.63936,0.65088,0.66225,0.67348,0.68455,0.69546,0.70622,0.71681,0.72725,0.73751,0.74761,0.75754,0.7673,0.77688,0.78629,0.79552,0.80456,0.81343,0.8221,0.8306,0.8389,0.84701,0.85493,0.86265,0.87018,0.87751,0.88465,0.89158,0.8983,0.90483,0.91114,0.91725,0.92316,0.92885,0.93433,0.9396,0.94465,0.94949,0.95411,0.95852,0.96271,0.96668,0.97043,0.97396,0.97727,0.98035,0.98322,0.98586,0.98827,0.99046,0.99243,0.99417,0.99568,0.99697,0.99803,0.99886,0.99947,0.99985,1,0.99992,0.99962,0.99909,0.99833,0.99735,0.99613,0.9947,0.99303,0.99114,0.98903,0.98669,0.98412,0.98133,0.97832,0.97509,0.97163,0.96796,0.96406,0.95994,0.95561,0.95106,0.94629,0.94131,0.93611,0.9307,0.92508,0.91925,0.9132,0.90696,0.9005,0.89384,0.88698,0.87991,0.87265,0.86519,0.85753,0.84967,0.84162,0.83338,0.82496,0.81634,0.80754,0.79855,0.78938,0.78004,0.77051,0.76081,0.75094,0.7409,0.73069,0.72031,0.70977,0.69906,0.6882,0.67718,0.66601,0.65469,0.64322,0.6316,0.61983,0.60793,0.59589,0.58371,0.5714,0.55896,0.54639,0.5337,0.52089,0.50796,0.49491,0.48175,0.46849,0.45511,0.44163,0.42805,0.41438,0.4006,0.38674,0.37279,0.35876,0.34464,0.33045,0.31618,0.30184,0.28743,0.27295,0.25841,0.24382,0.22917,0.21446,0.19971,0.18491,0.17007,0.15519,0.14028,0.12533,0.11036,0.095359,0.080338,0.065299,0.050244,0.035179,0.020105,0,0.015079,0.030155,0.045224,0.060282,0.075327,0.090354,0.10536,0.12034,0.1353,0.15023,0.16512,0.17997,0.19478,0.20955,0.22427,0.23894,0.25356,0.26811,0.28261,0.29704,0.31141,0.3257,0.33992,0.35406,0.36812,0.3821,0.39599,0.4098,0.4235,0.43712,0.45063,0.46404,0.47734,0.49054,0.50362,0.51659,0.52945,0.54218,0.55479,0.56727,0.57962,0.59184,0.60393,0.61588,0.62769,0.63936,0.65088,0.66225,0.67348,0.68455,0.69546,0.70622,0.71681,0.72725,0.73751,0.74761,0.75754,0.7673,0.77688,0.78629,0.79552,0.80456,0.81343,0.8221,0.8306,0.8389,0.84701,0.85493,0.86265,0.87018,0.87751,0.88465,0.89158,0.8983,0.90483,0.91114,0.91725,0.92316,0.92885,0.93433,0.9396,0.94465,0.94949,0.95411,0.95852,0.96271,0.96668,0.97043,0.97396,0.97727,0.98035,0.98322,0.98586,0.98827,0.99046,0.99243,0.99417,0.99568,0.99697,0.99803,0.99886,0.99947,0.99985,1,0.99992,0.99962,0.99909,0.99833,0.99735,0.99613,0.9947,0.99303,0.99114,0.98903,0.98669,0.98412,0.98133,0.97832,0.97509,0.97163,0.96796,0.96406,0.95994,0.95561,0.95106,0.94629,0.94131,0.93611,0.9307,0.92508,0.91925,0.9132,0.90696,0.9005,0.89384,0.88698,0.87991,0.87265,0.86519,0.85753,0.84967,0.84162,0.83338,0.82496,0.81634,0.80754,0.79855,0.78938,0.78004,0.77051,0.76081,0.75094,0.7409,0.73069,0.72031,0.70977,0.69906,0.6882,0.67718,0.66601,0.65469,0.64322,0.6316,0.61983,0.60793,0.59589,0.58371,0.5714,0.55896,0.54639,0.5337,0.52089,0.50796,0.49491,0.48175,0.46849,0.45511,0.44163,0.42805,0.41438,0.4006,0.38674,0.37279,0.35876,0.34464,0.33045,0.31618,0.30184,0.28743,0.27295,0.25841,0.24382,0.22917,0.21446,0.19971,0.18491,0.17007,0.15519,0.14028,0.12533,0.11036,0.095359,0.080338,0.065299,0.050244,0.035179,0.020105,0.0, 0.0, 0.0};


void serial_debug(void);
void botoes_leds(void);
inline void sinc(void);

void main(void)
  {

    DINT;   // Disable Global interrupt

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // � necess�rio para as fun��es que utilizam macros dos .asm, como o InitAdc.
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);
    InitFlash();    // call InitFlash in RAM (SARAM - L0)

    InitSysCtrl();

    InitPieCtrl();
    InitPieVectTable();

    my_buttons_init();
    my_sinc_init();
    my_leds_init();
    my_epwm_init();
    my_adc_init();

#ifdef MY_DEBUG_
    my_scia_init();
#endif

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    for(;;){
        //botoes_leds();

#ifdef MY_DEBUG_
        serial_debug();
#endif

        sinc();
        DELAY_US(2500);
    }

}

/**
 * @brief utiliza o sinal de sincronismo para ligar um led (utilizado para teste)
 */
inline void sinc(void)
{
    if(sinc1) led1_set = 1; // Acrecentar sinc aqui
    else led1_clear = 1;

    if(sinc2) led2_set = 1;
    else led2_clear = 1;

    if(sinc3) led3_set = 1;
    else led3_clear = 1;
}

/**
 * @brief envia dados de debug via serial
 */
void serial_debug(void)
{
    my_scia_send_string("dt: ");
    my_scia_send_uint16(dt);
    my_scia_send_string("\tADC0: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT0);
    my_scia_send_string("\tADC1: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT1);
    my_scia_send_string("\tADC2: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT2);
    my_scia_send_string("\tADC3: ");
    my_scia_send_uint16(AdcRegs.ADCRESULT3);
    my_scia_send_string("\r\n");
}

/**
 * Muda o estado dos leds de acordo com o estado dos botões.
 */
void botoes_leds(void)
{
    if (botao1)        led1_clear = 1;
    else{
        led1_set = 1;
        if(dt > 0) dt--;
    }

    if (botao2)        led2_clear = 1;
    else{
        led2_set = 1;
        if(dt < 1200) dt++;
    }

    if (botao3)        led3_clear = 1;
    else{
        led3_set = 1;
        dt=0;
    }

    // aplica dutycycle nos epwms 1 e 2
    epwm1_set_dt(dt);
    epwm2_set_dt(dt);

}
