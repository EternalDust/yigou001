/*
 * main.c
 */
#include <msp430.h>
#include "Serial.h"
#include "ADCinit.h"
#include <stdint.h>


uint8_t combuff[20]={0};//长度20的数组用于保存串口接受的数据
uint8_t iscomend=0;//bool变量


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
        
       
    }
    else if(combuff[0]=='1')
    {
         
        
       }
    else if(combuff[0]=='2')
    {
           
          
       }
    else if(combuff[0]=='3')
    {
           
         
       }
    else   
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
