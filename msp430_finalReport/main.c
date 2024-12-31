/*
 * main.c
 */
#include <msp430.h>
#include "Serial.h"
#include <stdint.h>
uint8_t combuff[20]={0};//����20���������ڱ��洮�ڽ��ܵ�����
uint8_t iscomend=0;//bool����
#pragma vector =USCIAB0RX_VECTOR;//����жϿ�.h
__interrupt void UART_Receive_ISR(void)
{
    static uint8_t cnt=0;
    if(IFG2&UCA0RXIFG)
    {
        IFG2&=~UCA0RXIFG;
        combuff[cnt++]=UCA0RXBUF;
        cnt%=20;
        if(combuff[cnt-1]=='\n')
        {
            cnt=0;
            iscomend=1;
        }
    }
}
void Execute (uint8_t *combuff)
{
    //����a0
    if(combuff[0]=='0')
    {
        Serial_SendString("A0��ͨ��50��\n");
    }
    //
    else if(combuff[0]=='1')
    {
           Serial_SendString("��ͨ���¶�50��\n");
       }
    else if(combuff[0]=='2')
    {
           Serial_SendString("SingleRepeatA0init(void)\n");
       }
    else if(combuff[0]=='3')
    {
           Serial_SendString("singleRepeatA10InitAD\n");
       }
    else if(combuff[0]=='4')
    {
           Serial_SendString("DoubleOnceADC\n");
       }
    else if(combuff[0]=='5')
    {
           Serial_SendString(" DoubleRepeatADC\n");
       }
    else   Serial_SendString("f\n");
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |=BIT6;
    P1OUT &=~BIT6;
    SysCLK_Init();
    Serial_Init();

    __bis_SR_register(GIE);

    while(1)
        {
            if(iscomend)
            {
                 P1OUT|=BIT6;
                iscomend=0;
                Execute(combuff);
            }
        }
}
