/**
 * my_scia.h
 *
 *  Created on: Jul 25, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 *  Ref:    http://www.ti.com/lit/ug/spru051d/spru051d.pdf
 *
 */

#ifndef MY_SCIA_H_
#define MY_SCIA_H_

#include "main.h"

#define my_scia_send_char(c) SciaRegs.SCITXBUF = (c)
#define my_scia_txempty SciaRegs.SCICTL2.bit.TXEMPTY

void my_scia_send_string(const char *s);
void my_scia_send_uint16(Uint16 num);
void my_scia_send_buffer(unsigned char *b, Uint32 lenght);

Uint32 my_scia_bytes_available(void);
void my_scia_get_char(void);

void my_scia_init(void);

#endif /* MY_SCIA_H_ */
