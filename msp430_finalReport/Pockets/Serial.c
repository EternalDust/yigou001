/*
 * Serial.c
 */
#include <msp430.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>



void SysCLK_Init(void)
{
    /*配置DCO为1MHz*/
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    /*配置SMCLK的时钟源为DCO*/
    BCSCTL2 &= ~SELS;
    /*SMCLK的分频系数置为1*/
    BCSCTL2 &= ~(DIVS0 | DIVS1);
}






void Serial_Init(void)
{
    /*复位USCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*选择USCI_Ax为UART模式*/
    UCA0CTL0 &= ~UCSYNC;

    /*配置UART时钟源为SMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*配置波特率为9600@1MHz*/
    UCA0BR0 = 0x68;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*使能端口复用*/
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    /*清除复位位，使能UART*/
    UCA0CTL1 &= ~UCSWRST;

    //接收中断启用
    IE2 |= UCA0RXIE;
    //清空接收中断标志
    IFG2 &= ~UCA0RXIFG;
}




void Serial_SendByte(uint8_t byte)
{
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = byte;
    while (!(IFG2 & UCA0TXIFG));
}





void Serial_SendArray(uint8_t *arr,uint16_t len)
{
    for(int i=0;i<len;i++)
    {
        Serial_SendByte(arr[i]);
    }
}




void Serial_SendString(char *str)
{
    for(int i = 0; str[i] !='\0'; i++)
    {
       Serial_SendByte(str[i]);
    }
}




void Serial_printf(char *format, ...)
{
    char str[50];               //定义字符数组
    va_list arg;                //定义可变参数列表数据类型的变量arg
    va_start(arg,format);       //从format开始，接收参数列表到arg变量
    vsprintf(str,format,arg);   //使用vsprintf打印格式化字符串和参数列表到字符数组中
    va_end(arg);                //结束变量arg
    Serial_SendString(str);     //串口发送字符数组（字符串）
}

