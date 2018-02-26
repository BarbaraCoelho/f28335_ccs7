
/*
 * my_xint.c
 *
 *  Created on: 25 de out de 2017
 *      Author: BARBARA
 */

#ifndef MY_XINT_C_
#define MY_XINT_C_

#include "main.h"

#define sinc1 GpioDataRegs.GPBDAT.bit.GPIO33
#define sinc2 GpioDataRegs.GPADAT.bit.GPIO31
#define sinc3 GpioDataRegs.GPADAT.bit.GPIO29

void my_xint_init(void);

//__interrupt void xint1_isr(void);
__interrupt void xint3_isr(void);

#endif /* MY_XINT_C_ */
