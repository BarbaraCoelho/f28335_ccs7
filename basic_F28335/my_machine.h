/*
 * my_machine.h
 *
 *  Created on: 18 de out de 2017
 *      Author: BARBARA
 */

#ifndef MY_MACHINE_H_
#define MY_MACHINE_H_

#include "main.h"

#define MY_DEBUG_

#define MAX_STANDBY_CURRENT         0.1
#define MAX_STANDBY_VOLTAGE         0.1
#define MAX_INITIALIZING_CURRENT    0.1
#define MAX_INITIALIZING_VOLTAGE    0.1
#define MAX_RUNNING_CURRENT         4.5
#define MAX_RUNNING_VOLTAGE         110

typedef enum state_machine{
    STATE_STANDBY,
    STATE_INITIALIZING,
    STATE_RUNNING,
    STATE_TURNINGOFF,
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
        Uint32 StandbyOverCurrent1      :   1;
        Uint32 StandbyOverCurrent2      :   1;
        Uint32 StandbyOverCurrent3      :   1;
        Uint32 StandbyOverVoltage       :   1;
        Uint32 InitOverCurrent1         :   1;
        Uint32 InitOverCurrent2         :   1;
        Uint32 InitOverCurrent3         :   1;
        Uint32 InitOverVoltage          :   1;
        Uint32 RunningOverCurrent1      :   1;
        Uint32 RunningOverCurrent2      :   1;
        Uint32 RunningOverCurrent3      :   1;
        Uint32 RunningOverVoltage       :   1;
    };
    Uint32 all;
}error_flags_t;

#define MAX_ACCEPTABLE_ERRORS 100   //!< used to choose what to do in case of errors

//the machine itself
void machine_init(void);
void machine_run(void);

//setters
void set_standby_state(void);               // TIVE DE TIRAR O INLINE, POIS DAVA PROBLEMA AO CHAMAR ELE NA main.c
void set_initializing_state(void);
void set_running_state(void);
void set_turningoff_state(void);
void set_error_state(void);

//tasks
inline void task_standby(void);
inline void task_initilizing(void);
inline void task_running(void);
inline void task_turningoff(void);
inline void task_error(void);

//checks
inline void check_standby_current(void);
inline void check_standby_voltage(void);
inline void check_initializing_current(void);
inline void check_initializing_voltage(void);
inline void check_running_current(void);
inline void check_running_voltage(void);

//others
inline void readAndConvertCurrents(void);
inline void convertCurrent1(void);
inline void convertCurrent2(void);
inline void convertCurrent3(void);
inline void convertVoltage(void);
inline void serial_debug(void);

// getters
Uint32 is_standby(void);
Uint32 is_running(void);

#endif /* MY_MACHINE_H_ */
