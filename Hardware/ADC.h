/*
 * ADC.h
 */

#ifndef ADC_H_
#define ADC_H_

extern int flag;
extern uint16_t adcbuff[50];


void ADC_Init(void);
uint16_t ADC_GetValue(void);
void ADCConvert_Start(void);
void TimerA0_Init(void);
void TimerA1_Init(void);


#endif /* ADC_H_ */
