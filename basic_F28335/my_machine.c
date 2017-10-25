/*
 * my_machine.c
 *
 *  Created on: 18 de out de 2017
 *      Author: BARBARA
 */

#include "my_machine.h"

/**
 * @brief
 */
inline void set_initializing_state(void)
{
    state_machine = STATE_INITIALIZING;
}

/**
 * @brief
 */
inline void set_running_state(void)
{
    state_machine = STATE_RUNNING;
}

/**
 * @brief
 */
inline void set_error_state(void)
{
    error_count++;
    state_machine = STATE_ERROR;
}

/**
 * @brief
 */
inline void task_initilizing(void)
{
    //
    set_running_state();
}

/**
 * @brief
 */
inline void check_current(void)
{
    /*if(current > blablabla){
        set_error_state();
    }*/
}

/**
 * @brief
 */
inline void check_voltage(void)
{
    /*if(voltage  > blablabla){
        set_error_state();
    }*/
}

/**
 * @brief
 */
inline void task_running(void)
{
    check_current();
    check_voltage();

    static Uint32 i = 0;

    dt = (0.5 + tabela[i++]) * 750;         // 750 = EPwm1Regs.TBPRD/2
    if(i > 418) i = 0;                      // recicla
    epwm1_set_dt(dt);

}

/**
 * @brief
 */
inline void task_error(void)
{
    if(error_count <= MAX_ACCEPTABLE_ERRORS)
        set_initializing_state();
    else
        for(;;);        // waits some watchdog to hard reset
}

/**
 * @brief
 */
inline void machine(void)
{
    switch(state_machine){
        case STATE_INITIALIZING:
            task_initilizing();
            break;
        case STATE_RUNNING:
            task_running();
            break;
        case STATE_ERROR: default:
            task_error();
            break;
    }
}
