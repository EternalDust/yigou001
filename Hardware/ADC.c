/*
 * ADC.c
 */

#include <msp430.h>
#include <stdint.h>

int flag = 0;
uint16_t adcbuff[50] = {0};


void ADC_Init(void)
{
      /*����ADCʱ��MCLK*/
      ADC10CTL1 |= ADC10SSEL_2;
      /*ADC ����Ƶ*/
      ADC10CTL1 |= ADC10DIV_0;
      /*ADC����Դʹ��TimerA_OUT1*/
      ADC10CTL1 |= SHS0;
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
      ADC10DTC0 |= ADC10CT;
      /*�������*/
      ADC10DTC1 = 50;
      /*��ʼ��ַ*/
      ADC10SA = (uint16_t)(adcbuff);
      /*����ADC*/
      ADC10CTL0 |= ADC10ON;
      /*����ת��*/
      ADC10CTL0 |= ENC;
}



void TimerA0_Init(void)
{
    /*����ʱ��ԴΪSMCLK*/
    TA0CTL |= TASSEL1;
    /*���ù���ģʽΪUp&Down*/
    TA0CTL |= MC0|MC1;
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
    P1SEL |= BIT6;
    P1DIR |= BIT6;
}

void TimerA1_Init(void)
{
    /*����P1.6Ϊ���*/
    P1DIR |= BIT6;

    /*����ʱ��ԴΪSMCLK*/
    TA1CTL |= TASSEL_2;
    /*���ù���ģʽΪUp Mode*/
    TA1CTL |= MC_1;
    /*���ö�ʱ���*/
    TA1CCR0 = 99999;// 50ms 1MHz 1/1MHz 1ns 50ms / 1ns = 50000 50000 - 1 = 49999

    /*����TAIFG�ж�*/
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

