/*
 * ADC.c
 */

#include <msp430.h>
#include <stdint.h>

int flag = 0;
uint16_t adcbuff[50] = {0};


void ADC_Init(void)
{
      /*设置ADC时钟MCLK*/
      ADC10CTL1 |= ADC10SSEL_2;
      /*ADC 不分频*/
      ADC10CTL1 |= ADC10DIV_0;
      /*ADC触发源使用TimerA_OUT1*/
      ADC10CTL1 |= SHS0;
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
      ADC10DTC0 |= ADC10CT;
      /*传输次数*/
      ADC10DTC1 = 50;
      /*起始地址*/
      ADC10SA = (uint16_t)(adcbuff);
      /*开启ADC*/
      ADC10CTL0 |= ADC10ON;
      /*允许转换*/
      ADC10CTL0 |= ENC;
}



void TimerA0_Init(void)
{
    /*设置时钟源为SMCLK*/
    TA0CTL |= TASSEL1;
    /*设置工作模式为Up&Down*/
    TA0CTL |= MC0|MC1;
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
    P1SEL |= BIT6;
    P1DIR |= BIT6;
}

void TimerA1_Init(void)
{
    /*设置P1.6为输出*/
    P1DIR |= BIT6;

    /*设置时钟源为SMCLK*/
    TA1CTL |= TASSEL_2;
    /*设置工作模式为Up Mode*/
    TA1CTL |= MC_1;
    /*设置定时间隔*/
    TA1CCR0 = 99999;// 50ms 1MHz 1/1MHz 1ns 50ms / 1ns = 50000 50000 - 1 = 49999

    /*开启TAIFG中断*/
    TA1CTL &= ~TAIE;
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


/*
#pragma vector = TIMER1_A1_VECTOR
__interrupt void Time_Tick(void)
{
    switch(TA1IV)
        {
        case 0x02:
            break;
        case 0x04:
            break;
        case 0x0A:
            flag = 1;
            break;
        default:
            break;
        }

}
*/


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
    flag = 1;
    __no_operation();
}

