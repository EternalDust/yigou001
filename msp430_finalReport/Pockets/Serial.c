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
    /*����DCOΪ1MHz*/
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    /*����SMCLK��ʱ��ԴΪDCO*/
    BCSCTL2 &= ~SELS;
    /*SMCLK�ķ�Ƶϵ����Ϊ1*/
    BCSCTL2 &= ~(DIVS0 | DIVS1);
}






void Serial_Init(void)
{
    /*��λUSCI_Ax*/
    UCA0CTL1 |= UCSWRST;

    /*ѡ��USCI_AxΪUARTģʽ*/
    UCA0CTL0 &= ~UCSYNC;

    /*����UARTʱ��ԴΪSMCLK*/
    UCA0CTL1 |= UCSSEL1;

    /*���ò�����Ϊ9600@1MHz*/
    UCA0BR0 = 0x68;
    UCA0BR1 = 0x00;
    UCA0MCTL = 1 << 1;
    /*ʹ�ܶ˿ڸ���*/
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

    /*�����λλ��ʹ��UART*/
    UCA0CTL1 &= ~UCSWRST;

    //�����ж�����
    IE2 |= UCA0RXIE;
    //��ս����жϱ�־
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
    char str[50];               //�����ַ�����
    va_list arg;                //����ɱ�����б��������͵ı���arg
    va_start(arg,format);       //��format��ʼ�����ղ����б�arg����
    vsprintf(str,format,arg);   //ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б��ַ�������
    va_end(arg);                //��������arg
    Serial_SendString(str);     //���ڷ����ַ����飨�ַ�����
}

