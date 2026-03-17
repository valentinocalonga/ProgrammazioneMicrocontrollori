/* 
 * File:   Uart.h
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */

#ifndef UART_H
#define UART_H

void UART_ConfigurePins(void);
void UART_ConfigureUart(int baud);
void initUART(unsigned int desiredBaudRate);
void putU4(int c);
char getU4(void);
void putU4_string(const char *szData);
char *getString(void);

#endif