/*
 * main.c
 */
#include <msp430.h>
#include "Serial.h"
#include "ADCinit.h"
#include <stdint.h>
extern uint8_t combuff[20]={0};//长度20的数组用于保存串口接受的数据
extern uint8_t iscomend=0;//bool变量
extern  uint16_t adcbuff[100];
#pragma vector =USCIAB0RX_VECTOR;//这个中断看.h
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
    //单单a0
    if(combuff[0]=='0')
    {
        Serial_SendString("A0单通道单次50次\n");
       
    }
    else if(combuff[0]=='1')
    {
           Serial_SendString("单通道单次温度50次\n");
        
       }
    else if(combuff[0]=='2')
    {
           Serial_SendString("单通道连续A0\n");
          
       }
    else if(combuff[0]=='3')
    {
           Serial_SendString("单通道连续温度\n");
         
       }
    else   Serial_SendString("非法输入\n");
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    SysCLK_Init();
    Serial_Init();

    __bis_SR_register(GIE);

    while(1)
        {
            if(iscomend)
            {
                iscomend=0;
                Execute(combuff);
            }
        }
}
