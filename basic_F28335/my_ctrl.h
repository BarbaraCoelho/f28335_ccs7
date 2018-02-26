/*
 * my_ctrl.c
 *
 *  Created on: 20 de fev de 2018
 *      Author: BARBARA
 */

#ifndef MY_CTRL_C_
#define MY_CTRL_C_

#include "main.h"

#define IREF_INIT 0.74162695476

extern volatile Uint32 dt;
extern volatile Uint32 index_sinal_modulante;
extern volatile Uint32 index_sinal_modulante2;

extern volatile float Iin1;
extern volatile float Iin2;
extern volatile float Iin3;
extern volatile float Vout;

extern volatile float Iref;
extern volatile float Iref_max;
extern volatile float Iref_passo;
extern volatile float Erro1;
extern volatile float Erro2;
extern volatile float U1;
extern volatile float U2;
extern volatile float Erro;
extern volatile float U;
extern volatile float Ref;
extern volatile float Ref1;
extern volatile float Ref2;
extern volatile float SF;
extern volatile float SF1;
extern volatile float SF2;

void test_sinc(void);
inline void test_sensors(void);
inline void check_buttons(void);
inline void check_relay(void);

void ctrl_loop(void);


#endif /* MY_CTRL_C_ */
