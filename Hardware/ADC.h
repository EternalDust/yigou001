/*
 * ADC.h
 */

#ifndef ADC_H_
#define ADC_H_

#define BUFFER_SIZE 128
#define SingleTrig_SIZE 50


extern uint16_t ring_buffer[BUFFER_SIZE];
extern uint16_t write_index;
extern uint16_t read_index;
extern int flag;
extern uint16_t adcbuff[SingleTrig_SIZE];


void ADC_Init(void);
uint16_t ADC_GetValue(void);
void ADCConvert_Start(void);
void TimerA0_Init(void);
void ADC_AutoTrig(void);
void ADC_SingleTrig(void);

#endif /* ADC_H_ */
