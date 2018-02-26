/**
 * my_buttons.h
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#ifndef MY_BUTTONS_H_
#define MY_BUTTONS_H_

#include "main.h"

#define botao1       GpioDataRegs.GPADAT.bit.GPIO26
#define botao2       GpioDataRegs.GPADAT.bit.GPIO16
#define botao3       GpioDataRegs.GPADAT.bit.GPIO20

void my_buttons_init(void);

#endif /* MY_BUTTONS_H_ */
