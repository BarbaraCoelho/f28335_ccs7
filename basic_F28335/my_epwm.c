/**
 * my_epwm.c
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description:
 *
 *  Reference: http://www.ti.com/lit/ug/sprug04a/sprug04a.pdf
 *
 */

#include "my_epwm.h"

/**
 * @brief Inicializa os pwms.
 * Uma observação importante é que os duty cycles são inicializados em zero e
 * somente depois da inicialização dos gpios é que devem ser modificados, pois
 * caso contrário, a defasagem no primeiro pulso não é garantida.
 */
void my_epwm_init(void)
{
    InitEPwm1();
    InitEPwm2();
    InitEPwm3();
    InitEPwm4();
    InitEPwm5();
    InitEPwm6();

    // Enable CPU INT3 which is connected to EPWM1-6 INT:
    IER |= M_INT3;

    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-6
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    MyInitEPwmGpio();

    // set phase
    epwm1_set_ph(0);
    epwm2_set_ph(0);
    epwm3_set_ph(0);
    epwm4_set_ph(0);
    epwm5_set_ph(0);
    epwm6_set_ph(0);

    // set duty cycle
    epwm1_set_dt(0);
    epwm2_set_dt(0);
    epwm3_set_dt(0);
    epwm4_set_dt(0);
    epwm5_set_dt(0);
    epwm6_set_dt(0);

}

/**
 * @brief
 */
void MyInitEPwmGpio(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO4 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO4 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;   // Enable pull-up on GPIO4 (EPWM6A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO2 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO2 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO2 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;  // Configure GPIO2 as EPWM6A
    EDIS;
}

/**
 * @brief PWM configurado como up-down-count, dual-edge symmetric,
 * apenas o EPWMxA ativo, sendo Freq e DutyCycle calcilados como:
 * TBPRD = (150MHz)/(2 x Freq)
 * half.CMPA = DutyCycle x TBPRD
 * Este EPWM1 está configurado como master para o sinal de
 * sincronismo
 * Foi configurado uma interrup��o no primeiro evento de quando o
 * comparador chega no topo.
 *
 */
void InitEPwm1(void)
{
    EALLOW;
    PieVectTable.EPWM1_INT = &epwm1_timer_isr;      // points to my isr declaration
    EDIS;

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

    EPwm1Regs.TBPRD = 1500;                         // Period = 2 x 1500 TBCLK counts
    EPwm1Regs.CMPA.half.CMPA = 0;                   // Init with duty cycle = 0
    EPwm1Regs.TBPHS.all = 0;                        // Set Phase register to zero
    EPwm1Regs.TBCTR = 0;                            // clear TB counter
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetric
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Master module
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;     // Sync down-stream module
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        // trigger when counter equals to top
    EPwm1Regs.ETSEL.bit.INTEN = 1;                  // EPwm1_int enable
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;             // generate an interrupt on the first event

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // clear when compare ascending
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;              // set when compare descending
    // Deadband config:
    //EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // enable Dead-band module
    //EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;       // Active Hi complementary
    //EPwm1Regs.DBFED = 50; // FED = 50 TBCLKs
    //EPwm1Regs.DBRED = 50; // RED = 50 TBCLKs
    // Interrupt config:

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;          // stars all the timers synced
    EDIS;

    //asm ("      ESTOP0");
}

/**
 * @brief PWM configurado como up-down-count, dual-edge symmetric,
 * apenas o EPWMxA ativo, sendo Freq e DutyCycle calcilados como:
 * TBPRD = (150MHz)/(2 x Freq)
 * half.CMPA = DutyCycle x TBPRD
 * Este EPWM1 está configurado como slave para o sinal de
 * sincronismo, estando assim sincronizado com o EPWM1
 */
void InitEPwm2(void)
{
    EPwm2Regs.TBPRD = 1500;                         // Period = 2*1500 TBCLK counts
    EPwm2Regs.CMPA.half.CMPA = 0;                   // Init with duty cycle = 0
    EPwm2Regs.TBPHS.all = 0;                        // Set Phase register to zero
    EPwm2Regs.TBCTR = 0;                            // clear TB counter
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetric
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
}

/**
 * @brief PWM configurado como up-down-count, dual-edge symmetric,
 * apenas o EPWMxA ativo, sendo Freq e DutyCycle calcilados como:
 * TBPRD = (150MHz)/(2 x Freq)
 * half.CMPA = DutyCycle x TBPRD
 * Este EPWM1 está configurado como slave para o sinal de
 * sincronismo, estando assim sincronizado com o EPWM1
 */
void InitEPwm3(void)
{
    EPwm3Regs.TBPRD = 1500;                         // Period = 2*1500 TBCLK counts
    EPwm3Regs.CMPA.half.CMPA = 0;                   // Init with duty cycle = 0
    EPwm3Regs.TBPHS.all = 0;                        // Set Phase register to zero
    EPwm3Regs.TBCTR = 0;                            // clear TB counter
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetric
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
}
/**
 * @brief PWM configurado como up-down-count, dual-edge symmetric,
 * apenas o EPWMxA ativo, sendo Freq e DutyCycle calcilados como:
 * TBPRD = (150MHz)/(2 x Freq)
 * half.CMPA = DutyCycle x TBPRD
 * Este EPWM1 está configurado como slave para o sinal de
 * sincronismo, estando assim sincronizado com o EPWM1
 */
void InitEPwm4(void)
{
    EPwm4Regs.TBPRD = 1500;                         // Period = 2*1500 TBCLK counts
    EPwm4Regs.CMPA.half.CMPA = 0;                   // Init with duty cycle = 0
    EPwm4Regs.TBPHS.all = 0;                        // Set Phase register to zero
    EPwm4Regs.TBCTR = 0;                            // clear TB counter
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetric
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
    EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
}

/**
 * @brief PWM configurado como up-down-count, dual-edge symmetric,
 * apenas o EPWMxA ativo, sendo Freq e DutyCycle calcilados como:
 * TBPRD = (150MHz)/(2 x Freq)
 * half.CMPA = DutyCycle x TBPRD
 * Este EPWM1 está configurado como slave para o sinal de
 * sincronismo, estando assim sincronizado com o EPWM1
 */
void InitEPwm5(void)
{
    EPwm5Regs.TBPRD = 1500;                         // Period = 2*1500 TBCLK counts
    EPwm5Regs.CMPA.half.CMPA = 0;                   // Init with duty cycle = 0
    EPwm5Regs.TBPHS.all = 0;                        // Set Phase register to zero
    EPwm5Regs.TBCTR = 0;                            // clear TB counter
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetric
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
    EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;
}

/**
 * @brief PWM configurado como up-down-count, dual-edge symmetric,
 * apenas o EPWMxA ativo, sendo Freq e DutyCycle calcilados como:
 * TBPRD = (150MHz)/(2 x Freq)
 * half.CMPA = DutyCycle x TBPRD
 * Este EPWM1 está configurado como slave para o sinal de
 * sincronismo, estando assim sincronizado com o EPWM1
 */
void InitEPwm6(void)
{
    EPwm6Regs.TBPRD = 1500;                         // Period = 2*1500 TBCLK counts
    EPwm6Regs.CMPA.half.CMPA = 0;                   // Init with duty cycle = 0
    EPwm6Regs.TBPHS.all = 0;                        // Set Phase register to zero
    EPwm6Regs.TBCTR = 0;                            // clear TB counter
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetric
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
    EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;      // sync flow-through
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;   // load on CTR = Zero
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
}

/**
 * @brief interrupçãp EPWM1
 */
__interrupt void epwm1_timer_isr(void)              // EPWM-1
{
    if(Calcula_dt == 1){
        if(++index_sinal_modulante >= 420) index_sinal_modulante = 0;  // 420 (25 kHz)    837 (50 kHz)
        if (index_sinal_modulante <= 208)                              // 208 (25 kHz)    418 (50 kHz)
        {
            dt = (0.5 + (sinal_modulante[index_sinal_modulante])/2)*EPwm1Regs.TBPRD;
        }
        else
        {
            dt = (0.5 - (sinal_modulante[index_sinal_modulante])/2)*EPwm1Regs.TBPRD;
        }
        Calcula_dt = 0;
    }
    else{
        Calcula_dt = 1;
    }
    epwm1_set_dt(dt);

    EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
