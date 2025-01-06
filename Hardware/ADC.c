/*
 * ADC.c
 */

#include <msp430.h>
#include <stdint.h>
#include "ADC.h"
#include "Serial.h"
#include "Data.h"

int flag = 0;
uint16_t ring_buffer[BUFFER_SIZE];
uint16_t write_index = 0;  
uint16_t read_index = 0;   
uint16_t adcbuff[SingleTrig_SIZE] = {0};


void ADC_Init(void)
{
      /*����ADCʱ��MCLK*/
      ADC10CTL1 |= ADC10SSEL_2;
      /*ADC ����Ƶ*/
      ADC10CTL1 |= ADC10DIV_0;
      /*ADC����Դʹ��TimerA_OUT1*/
      ADC10CTL1 |= SHS_1;
      /*��ͨ������ת��ģʽ*/
      ADC10CTL1 |= CONSEQ_2;
      /*����ADC��׼Դ*/
      ADC10CTL0 |= SREF_1;
      /*����ADC��������ʱ��16CLK*/
      ADC10CTL0 |= ADC10SHT_2;
      /*����ADC������200k*/
      ADC10CTL0 |= ADC10SR;
      /*ADC��׼ѡ��2.5V*/
      ADC10CTL0 |= REF2_5V;
      /*������׼*/
      ADC10CTL0 |= REFON;
      /*ѡ��ADC����ͨ��A4*/
      ADC10CTL1 |= INCH_4;
      /*����A4ģ������*/
      ADC10AE0 |= 1 << 4;
      /*�ж�ʹ��*/
      ADC10CTL0 |= ADC10IE;
      /*DTC����ģʽ*/
      //ADC10DTC0 |= ADC10CT;
      /*�������*/
      //ADC10DTC1 = 50;
      /*��ʼ��ַ*/
      //ADC10SA = (uint16_t)(adcbuff);
      /*����ADC*/
      ADC10CTL0 |= ADC10ON;
      /*����ת��*/
      ADC10CTL0 |= ENC;
}



void TimerA0_Init(void)
{
    /*����ʱ��ԴΪSMCLK*/
    TA0CTL |= TASSEL_2;
    /*���ù���ģʽΪUp&Down*/
    TA0CTL |= MC_1;
    /*����TA1CCR0Ϊ0x00FF*/
    TA0CCR0 = 0x00FF;
    /*����TA1CCR1Ϊ0x00FF*/
    TA0CCR1 = 0x007F;//ռ�ձ�(TACCR0 - TACCR1) / TACCR0,Ƶ��=SMCLK/(TACCR0+1)/2
    /*����Ϊ�Ƚ�ģʽ*/
    TA0CCTL0 &= ~CAP;
    TA0CCTL1 &= ~CAP;
    /*���ñȽ����ģʽ*/
    TA0CCTL1 |= OUTMOD_6;
    /*����IO����*/
    P1SEL |= BIT2;
    P1DIR |= BIT2;
}



uint16_t ADC_GetValue(void)
{
    ADC10CTL0 |= ADC10SC|ENC;
    while(ADC10CTL1&ADC10BUSY);
    return ADC10MEM;
}



void ADCConvert_Start(void)
{
    ADC10CTL0 |= ADC10SC|ENC;
    while(ADC10CTL1&ADC10BUSY);
}


//��ѹ��������ģʽ
//ADC�����뱾�ļ�����һ�£�ͬʱ��ҪTimerA0_Init();
//��Ҫ����while(1)ѭ����
void ADC_AutoTrig(void)
{
    if (ADC10CTL0 & ADC10IFG) 
    {
        ring_buffer[write_index] = ADC10MEM;
        write_index = (write_index + 1) % BUFFER_SIZE; 
        ADC10CTL0 &= ~ADC10IFG;
    }
    while (read_index != write_index) 
    {
        uint16_t data = ring_buffer[read_index];
        uint16_t ppval = cal_ppvalue(ring_buffer);
        uint16_t ave = average_array(ring_buffer);
        uint16_t f = frequency(ring_buffer,BUFFER_SIZE);

        read_index = (read_index + 1) % BUFFER_SIZE; 
        Serial_printf("%d, %d, %d, %d, %d\n", data, (data * 2500L) / 1023, (ppval/* * 2500L*/)/* / 1023*/, (ave/* * 2500L*/)/* / 1023*/, f);
        __delay_cycles(30000);
    }
}



//��ѹ���δ���ģʽ
//ADC������Ҫ��DTCģʽ����ע��ȥ�����ɣ�ͬ�������ɼ���ע�ͼ��ϼ���
void ADC_SingleTrig(void)
{
    for (int i = 0; i < SingleTrig_SIZE; i++)
    {
        uint16_t ppval = cal_ppvalue(adcbuff);
        uint16_t ave = average_array(adcbuff);
        Serial_printf("%d, %d, %d, %d,\n", *(adcbuff+i), (*(adcbuff+i) * 2500L) / 1023, (ppval/* * 2500L*/)/* / 1023*/, (ave/* * 2500L*/)/* / 1023*/);
    }
}



