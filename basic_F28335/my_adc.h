/**
 * my_adc.h
 *
 *  Created on: Jul 18, 2017
 *      Author: joaoantoniocardoso
 *
 *  Description: 
 *
 */

#ifndef MY_ADC_H_
#define MY_ADC_H_

#include "DSP28x_Project.h"

#define ADC_Cal (void (*) (void)) 0x380080

void my_adc_init(void);
__interrupt void adc_isr(void);
__interrupt void cpu_timer0_isr(void);

extern volatile float ADC_Iin1;
extern volatile float ADC_Iin2;
extern volatile float ADC_Iin3;
extern volatile float ADC_Vout;

void readCurrent1ADC(void);
void readCurrent2ADC(void);
void readCurrent3ADC(void);
void readVoltageADC(void);


#endif /* MY_ADC_H_ */
