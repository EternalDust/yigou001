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
      /*设置ADC时钟MCLK*/
      ADC10CTL1 |= ADC10SSEL_2;
      /*ADC 不分频*/
      ADC10CTL1 |= ADC10DIV_0;
      /*ADC触发源使用TimerA_OUT1*/
      ADC10CTL1 |= SHS_1;
      /*单通道连续转换模式*/
      ADC10CTL1 |= CONSEQ_2;
      /*设置ADC基准源*/
      ADC10CTL0 |= SREF_1;
      /*设置ADC采样保持时间16CLK*/
      ADC10CTL0 |= ADC10SHT_2;
      /*设置ADC采样率200k*/
      ADC10CTL0 |= ADC10SR;
      /*ADC基准选择2.5V*/
      ADC10CTL0 |= REF2_5V;
      /*开启基准*/
      ADC10CTL0 |= REFON;
      /*选择ADC输入通道A4*/
      ADC10CTL1 |= INCH_4;
      /*允许A4模拟输入*/
      ADC10AE0 |= 1 << 4;
      /*中断使能*/
      ADC10CTL0 |= ADC10IE;
      /*DTC传输模式*/
      //ADC10DTC0 |= ADC10CT;
      /*传输次数*/
      //ADC10DTC1 = 50;
      /*起始地址*/
      //ADC10SA = (uint16_t)(adcbuff);
      /*开启ADC*/
      ADC10CTL0 |= ADC10ON;
      /*允许转换*/
      ADC10CTL0 |= ENC;
}



void TimerA0_Init(void)
{
    /*设置时钟源为SMCLK*/
    TA0CTL |= TASSEL_2;
    /*设置工作模式为Up&Down*/
    TA0CTL |= MC_1;
    /*设置TA1CCR0为0x00FF*/
    TA0CCR0 = 0x00FF;
    /*设置TA1CCR1为0x00FF*/
    TA0CCR1 = 0x007F;//占空比(TACCR0 - TACCR1) / TACCR0,频率=SMCLK/(TACCR0+1)/2
    /*设置为比较模式*/
    TA0CCTL0 &= ~CAP;
    TA0CCTL1 &= ~CAP;
    /*设置比较输出模式*/
    TA0CCTL1 |= OUTMOD_6;
    /*设置IO复用*/
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


//电压连续触发模式
//ADC配置与本文件保持一致，同时需要TimerA0_Init();
//需要放在while(1)循环中
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



//电压单次触发模式
//ADC配置需要打开DTC模式，将注释去掉即可，同样连续采集将注释加上即可
void ADC_SingleTrig(void)
{
    for (int i = 0; i < SingleTrig_SIZE; i++)
    {
        uint16_t ppval = cal_ppvalue(adcbuff);
        uint16_t ave = average_array(adcbuff);
        Serial_printf("%d, %d, %d, %d,\n", *(adcbuff+i), (*(adcbuff+i) * 2500L) / 1023, (ppval/* * 2500L*/)/* / 1023*/, (ave/* * 2500L*/)/* / 1023*/);
    }
}



