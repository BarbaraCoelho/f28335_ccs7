/**
 * my_leds.c
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#include "my_leds.h"

void my_leds_init(void)
{
    EALLOW;

    // Configura rele
    GpioCtrlRegs.GPCDIR.bit.GPIO87 = 1;
    relay_clear();

    // Configura os pinos para os leds como saída
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;
    GpioCtrlRegs.GPCDIR.bit.GPIO86 = 1;

    EDIS;
}

void my_leds_signals(Uint32 counts_to_toggle)
{
    static Uint32 counter = 0;

    // toggle led1
    if(counter++ >= counts_to_toggle) {
        led1_toggle();
        counter = 0;
    }

}
