
/*
 * my_xint.c
 *
 *  Created on: 25 de out de 2017
 *      Author: BARBARA
 */

#ifndef MY_XINT_C_
#define MY_XINT_C_

#include "DSP28x_Project.h"

volatile Uint32 Xint1Count;

void my_xint_init(void);

__interrupt void xint1_isr(void);

#endif /* MY_XINT_C_ */
