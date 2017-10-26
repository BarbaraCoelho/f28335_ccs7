/*
 * my_xint.h
 *
 *  Created on: 25 de out de 2017
 *      Author: BARBARA
 */

#include "my_xint.h"

/**
 * @brief
 */
void my_xint_init(void)
{
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.XINT1 = &xint1_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

   // Enable Xint1 in the PIE: Group 1 interrupt 4
   // Enable int1 which is connected to WAKEINT:
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Gropu 1 INT4
    IER |= M_INT1;                              // Enable CPU int1
    EINT;                                       // Enable Global Interrupts

    // GPIO0 is XINT1
    EALLOW;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;   // Xint1 is GPIO0
    EDIS;

    // Configure XINT1
    XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // Falling edge interrupt

    // Enable XINT1
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable Xint1

    // GPIO34 will go low inside each interrupt.  Monitor this on a scope
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;        // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;         // output
    EDIS;

}

/**
 * @brief
 */
__interrupt void xint1_isr(void)
{
    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    Xint1Count++;

    // Acknowledge this interrupt to get more from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
