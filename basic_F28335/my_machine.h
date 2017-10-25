/*
 * my_machine.h
 *
 *  Created on: 18 de out de 2017
 *      Author: BARBARA
 */

#ifndef MY_MACHINE_H_
#define MY_MACHINE_H_

#include "DSP28x_Project.h"
#include "my_epwm.h"

typedef enum state_machine{
    STATE_INITIALIZING,
    STATE_RUNNING,
    STATE_ERROR,
} state_machine_t;

typedef union system_flags{
    struct{
        Uint32 none1    :   1;
    };
    Uint32 all;
}system_flags_t;

typedef union error_flags{
    struct{
        Uint32 none1    :   1;
    };
    Uint32 all;
}error_flags_t;

#define MAX_ACCEPTABLE_ERRORS 100   //!< used to choose what to do in case of errors
static Uint32 error_count = 0;

static state_machine_t state_machine;
static system_flags_t system_flags;
static error_flags_t error_flags;

inline void set_initializing_state(void);
inline void set_running_state(void);
inline void set_error_state(void);

inline void task_initilizing(void);
inline void task_running(void);
inline void task_error(void);

inline void check_current(void);
inline void check_voltage(void);

//externs from main.c
extern volatile Uint32 dt;
extern float tabela[419];

#endif /* MY_MACHINE_H_ */
