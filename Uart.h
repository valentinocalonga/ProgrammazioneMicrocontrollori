/* 
 * File:   Uart.h
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */

void UART_ConfigurePins(void);
void UART_ConfigureUart(int baud);
void initUART(unsigned int DesiredBaudRate);
void putU4( int c);
char getU4( void);
void putU4_string(char szData[]);
char* getString(void);