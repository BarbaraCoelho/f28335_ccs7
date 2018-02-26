/**
 * my_leds.h
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#ifndef MY_LEDS_H_
#define MY_LEDS_H_

#include "main.h"

#define led1_clear()   GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1
#define led1_set()     GpioDataRegs.GPBSET.bit.GPIO48 = 1
#define led1_toggle()  GpioDataRegs.GPBTOGGLE.bit.GPIO48 = 1
#define led2_clear()   GpioDataRegs.GPCCLEAR.bit.GPIO86 = 1
#define led2_set()     GpioDataRegs.GPCSET.bit.GPIO86 = 1
#define led2_toggle()  GpioDataRegs.GPBTOGGLE.bit.GPIO86 = 1
#define led3_clear()   GpioDataRegs.GPACLEAR.bit.GPIO15 = 1
#define led3_set()     GpioDataRegs.GPASET.bit.GPIO15 = 1
#define led3_toggle()  GpioDataRegs.GPBTOGGLE.bit.GPIO15 = 1
#define relay_clear()  GpioDataRegs.GPCSET.bit.GPIO87 = 1
#define relay_set()    GpioDataRegs.GPCCLEAR.bit.GPIO87 = 1

void my_leds_init(void);
void my_leds_signals(Uint32 counts_to_toggle);

#endif /* MY_LEDS_H_ */
