/*
 * my_xint.h
 *
 *  Created on: 25 de out de 2017
 *      Author: BARBARA
 *
 *  Description:
 *
 *  Reference: http://www.ti.com/lit/ug/sprufb0d/sprufb0d.pdf
 *
 */

#include "my_xint.h"

/**
 * @brief inicializa os XINTn
 */
void my_xint_init(void)
{
    EALLOW;  // This is needed to write to EALLOW protected registers
    //PieVectTable.XINT1 = &xint1_isr;    // XINT1
    PieVectTable.XINT3 = &xint3_isr;    // XINT3
    EDIS;   // This is needed to disable write to EALLOW protected registers


    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    // Enable Xint1 in the PIE: Group 1 interrupt 4
    //PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Gropu 1 INTx4 (XINT1)
    IER |= M_INT12;                             // Enable CPU int12
    // Enable Xint1 in the PIE: Group 12 interrupt 1
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;         // Enable PIE Gropu 12 INTx1 (XINT3)
    //PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Gropu 1 INTx5 (XINT2)
    //IER |= M_INT1;                              // Enable CPU int1
   EINT;                                       // Enable Global Interrupts

    EALLOW;
    // GPIO 33 are input
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;        // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;         // INPUT - SINC1
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 0;       // Xint Synch to SYSCLKOUT only

    // old sinc.c
//    GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;     //sinc3
//    GpioCtrlRegs.GPADIR.bit.GPIO31 = 0;     //sinc2
//    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;     //sinc1

    // GPIO 01 are input
    //GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;         // GPIO
    //GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;          // input
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 0;        // Xint Synch to SYSCLKOUT only
    EDIS;

    EALLOW;
    // GPIO1 is XINT1
    //GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 1;   // Xint1 is GPIO1
    // GPIO33 is XINT3
    GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 1;   // Xint3 is GPIO33
    EDIS;

    // Configure XINT1 and XINT3
    //XIntruptRegs.XINT1CR.bit.POLARITY = 1;      // Rising edge interrupt
    XIntruptRegs.XINT3CR.bit.POLARITY = 1;      // Rising edge interrupt

    // Enable XINT1 and XINT3
    //XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable Xint1
    XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // Enable Xint3
}

/**
 * @brief interrupção XINT3
 */
__interrupt void xint3_isr(void)
{
    // Só zera o index se for maior que 75% da tabela
    if(index_sinal_modulante >= 312){
        index_sinal_modulante = 0;
        index_sinal_modulante2++;
    }
    // Acknowledge this interrupt to get more from group 1
    //PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    // Acknowledge this interrupt to get more from group 12
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;

}
