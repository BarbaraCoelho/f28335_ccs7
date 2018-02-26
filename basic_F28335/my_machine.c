/*
 * my_machine.c
 *
 *  Created on: 18 de out de 2017
 *      Author: BARBARA
 */

#include "my_machine.h"

static Uint32 error_count = 0;

static state_machine_t state_machine = STATE_STANDBY;
static system_flags_t system_flags;
static error_flags_t error_flags;

/**
 * @brief
 */
void machine_init(void)
{
    DELAY_US(100000);

    system_flags.all = 0;
    error_flags.all = 0;

    set_standby_state();

    index_sinal_modulante = 0;

    readAndConvertCurrents();
    readVoltageADC();
    convertVoltage();

    interruptionEpwm = epwm1_timer_isr_collision = 0;

}

/**
 * @brief
 */
void machine_run(void)
{
    static Uint32 leds_delay = 0;
    my_leds_signals(leds_delay);

    //check_relay(); moved to ctrl_loop

    if(error_flags.all)    set_error_state();

#ifdef MY_DEBUG_
        serial_debug();
#endif

    switch (state_machine) {
        case STATE_STANDBY:
            leds_delay = 15;
            task_standby();
            break;
        case STATE_INITIALIZING:
            leds_delay = 1;
            task_initilizing();
            break;
        case STATE_RUNNING:
            leds_delay = 5;
            task_running();
            break;
        case STATE_TURNINGOFF:
            leds_delay = 2;
            task_turningoff();
            break;
        case STATE_ERROR:
        default:
            leds_delay = 0;
            task_error();
            break;
    }
}

/**
 * @brief
 */
inline void convertCurrent1(void)
{
    Iin1 = ((ADC_Iin1 -630) / 457) -3;
}

/**
 * @brief
 */
inline void convertCurrent2(void)
{
    Iin2 = ((ADC_Iin2 -630) / 457) -3;
}

/**
 * @brief
 */
inline void convertCurrent3(void)
{
    Iin3 = ((ADC_Iin3 -630) / 457) -3;
}

/**
 * @brief
 */
inline void readAndConvertCurrents(void)
{
    readCurrent1ADC();
    readCurrent2ADC();
    readCurrent3ADC();

    convertCurrent1();
    convertCurrent2();
    convertCurrent3();
}

/**
 * @brief
 */
inline void convertVoltage(void)
{
    Vout = ((ADC_Vout * 10 -300) / 364);
}

/**
 * @brief
 */
void set_standby_state(void)
{
    relay_clear();
    DELAY_US(10000);
    state_machine = STATE_STANDBY;
}

/**
 * @brief
 */
void set_initializing_state(void)
{
    relay_set();
    DELAY_US(10000);
    state_machine = STATE_INITIALIZING;
    Iref = IREF_INIT;
}

/**
 * @brief
 */
void set_running_state(void)
{
    state_machine = STATE_RUNNING;
}

/**
 * @brief
 */
void set_turningoff_state(void)
{
    relay_clear();
    DELAY_US(10000);
    state_machine = STATE_TURNINGOFF;
}


/**
 * @brief
 */
void set_error_state(void)
{
    error_count++;
    relay_clear();
    state_machine = STATE_ERROR;
}

/**
 * @brief
 */
inline void task_standby(void)
{
    readAndConvertCurrents();
    readVoltageADC();
    convertVoltage();

    check_standby_current();
    check_standby_voltage();

    interruptionEpwm = epwm1_timer_isr_collision = 0;
}

/**
 * @brief
 */
inline void check_standby_current(void)
{
    readAndConvertCurrents();

    if(abs(Iin1) > MAX_STANDBY_CURRENT) error_flags.StandbyOverCurrent1 = 1;
    if(abs(Iin2) > MAX_STANDBY_CURRENT) error_flags.StandbyOverCurrent2 = 1;
    if(abs(Iin3) > MAX_STANDBY_CURRENT) error_flags.StandbyOverCurrent3 = 1;
}

/**
 * @brief
 */
inline void check_standby_voltage(void)
{
    readVoltageADC();
    convertVoltage();

    if(Vout > MAX_STANDBY_VOLTAGE)      error_flags.StandbyOverVoltage = 1;
}

/**
 * @brief
 */
inline void task_initilizing(void)
{
    check_initializing_current();
    check_initializing_voltage();

    if(!error_flags.all)    set_running_state();
    interruptionEpwm = 0;
}

/**
 * @brief
 */
inline void check_initializing_current(void)
{
    readAndConvertCurrents();

    if(abs(Iin1) > MAX_INITIALIZING_CURRENT) error_flags.InitOverCurrent1 = 1;
    if(abs(Iin2) > MAX_INITIALIZING_CURRENT) error_flags.InitOverCurrent2 = 1;
    if(abs(Iin3) > MAX_INITIALIZING_CURRENT) error_flags.InitOverCurrent3 = 1;
}

/**
 * @brief
 */
inline void check_initializing_voltage(void)
{
    readVoltageADC();
    convertVoltage();

    if(Vout > MAX_INITIALIZING_VOLTAGE)     error_flags.InitOverVoltage = 1;
}

/**
 * @brief
 */
inline void check_running_current(void)
{
    readAndConvertCurrents();

    if(abs(Iin1) > MAX_RUNNING_CURRENT) error_flags.RunningOverCurrent1 = 1;
    if(abs(Iin2) > MAX_RUNNING_CURRENT) error_flags.RunningOverCurrent2 = 1;
    if(abs(Iin3) > MAX_RUNNING_CURRENT) error_flags.RunningOverCurrent3 = 1;
}

/**
 * @brief
 */
inline void check_running_voltage(void)
{
    readVoltageADC();
    convertVoltage();

    if(Vout > MAX_RUNNING_VOLTAGE)      error_flags.RunningOverVoltage = 1;

}

/**
 * @brief
 */
inline void task_running(void)
{
    check_running_current();
    check_running_voltage();

    //check_buttons();  moved to ctrl_loop

    //ctrl_loop(); // moved to my_epwm isr
}

/**
 * @brief
 */
inline void task_turningoff(void)
{

    Iref = 0;
    set_standby_state();

}

/**
 * @brief
 */
inline void task_error(void)
{
    if(error_count <= MAX_ACCEPTABLE_ERRORS){
        set_initializing_state();
        interruptionEpwm = 0;
    }else
        for(;;){
            interruptionEpwm = 0;
            // waits some watchdog to hard reset
#ifdef MY_DEBUG_
            serial_debug();
#endif
        }

}

Uint32 is_running(void)
{
    if(state_machine == STATE_RUNNING)  return 1;
    else                                return 0;
}

Uint32 is_standby(void)
{
    if(state_machine == STATE_STANDBY)  return 1;
    else                                return 0;
}

/**
 * @brief envia dados de debug via serial
 */
inline void serial_debug(void)
{
    my_scia_send_string("dt: ");
    my_scia_send_uint16(dt);
    my_scia_send_string("\t Iref: ");
    my_scia_send_uint16(Iref*1000);
    my_scia_send_string("mA ");
    my_scia_send_string("\t Iin1: ");
    my_scia_send_uint16(Iin1*1000);
    my_scia_send_string("mA ");
    my_scia_send_string("\t Vout: ");
    my_scia_send_uint16(Vout);
    my_scia_send_string("V ");
    my_scia_send_string("\t Rl: ");
    my_scia_send_uint16(GpioDataRegs.GPCDAT.bit.GPIO87);
    my_scia_send_string("\t Index: ");
    my_scia_send_uint16(index_sinal_modulante);
    my_scia_send_string("\t Err: ");
    my_scia_send_uint16(error_flags.all);
    my_scia_send_string("\r\n");
}
