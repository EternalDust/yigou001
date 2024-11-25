/*
 * Serial.h
 */
#include <stdint.h>

#ifndef SERIAL_H_
#define SERIAL_H_

void SysCLK_Init(void);
void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendArray(uint8_t *arr,uint16_t len);
void Serial_SendString(char *str);
void Serial_printf(char *format, ...);

#endif /* SERIAL_H_ */
