 #include <msp430.h>
#include "stdint.h"
#include "Serial.h"
#include "ADC.h"
/*
 * main.c
 */
int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    SysCLK_Init();
    Serial_Init();
    ADC_Init();
    while(1)
    {

    }
}


