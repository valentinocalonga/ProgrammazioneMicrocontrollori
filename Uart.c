/* 
 * File:   Uart.c
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */

#include <p32xxxx.h>
#include "Uart.h"


// per Serie2_ProMC - Esercizio 2
#define UART_BUFFER_SIZE 80
/* buffer globale per la ricezione della stringa */
static char dataIn[UART_BUFFER_SIZE];

/*
 * Dalle slide...
 */

void UART_ConfigurePins(void) {
    TRISFbits.TRISF12 = 0;      // TX DIGITAL OUTPUT
    RPF12R = 2;                 // 0010 U4TX = Mapping U4TX to RPF12 
    
    TRISFbits.TRISF13 = 1;      // RX DIGITAL INPUT
    U4RXR = 9;                  // 1001 RF13 = Mapping U4RX to RPF13
}

void UART_ConfigureUart(int baud)
{
    unsigned int PbusClock = 40000000;
    unsigned int UartBrg = 0;
    
	U4MODEbits.ON     = 0;
    U4MODEbits.SIDL   = 0;
    U4MODEbits.IREN   = 0; 
    U4MODEbits.RTSMD  = 0;
    U4MODEbits.UEN0   = 0; 
    U4MODEbits.UEN1   = 0;
    U4MODEbits.WAKE   = 0;
    U4MODEbits.LPBACK = 0; 
    U4MODEbits.ABAUD  = 0;
    U4MODEbits.RXINV  = 0; 
    U4MODEbits.PDSEL1 = 0; 
    U4MODEbits.PDSEL0 = 0; 
    U4MODEbits.STSEL  = 0;  
    
    U4MODEbits.BRGH   = 0; 
	
	// same as U4MODE = 0x0000; //all in one instruction

    /* calculate brg */
    UartBrg = (int)(((float)PbusClock/(16 * baud) - 1) + 0.5 ); // Add 0.5 to round
    U4BRG = UartBrg;

    U4STAbits.UTXEN    = 1;
    U4STAbits.URXEN    = 1;
    U4MODEbits.ON      = 1; 
}

void initUART(unsigned int DesiredBaudRate) 
{
    /* Data to send */
    unsigned char DataToSend[] = {'U', 'a', 'r', 't', '-', 'I', 'n', 'i', 't', '\r', '\n', '\0'};
    
    UART_ConfigurePins();
    UART_ConfigureUart(DesiredBaudRate);
    
    putU4_string(DataToSend);
}

void putU4( int c)
{
while(U4STAbits.UTXBF == 1);
    U4TXREG = c;
} // putU2

char getU4( void)
{
    //RTS=0; // assert Request To Send !RTS

    while (!U4STAbits.URXDA); // wait for a new char to arrive
    //RTS=1;
    return U4RXREG; // read char from receive buffer
} // getU4

void putU4_string(const char *szData)
{
    while(*szData)
    {
        putU4(*szData++);
    }
}

char* getString(void)
/*
 * Legge una stringa da UART4 fino a '\r' oppure '\n'.
 * I caratteri ricevuti vengono salvati in un buffer globale (uartRxBuffer)
 */
{
    int i = 0;
    char c;

    while(1)
    {
        c = getU4();

        /* ignora CR/LF iniziali residui */
        if(i == 0 && (c == '\r' || c == '\n'))
        {
            continue;
        }

        /* gestione backspace / delete */
        if(c == '\b' || c == 127)
        {
            if(i > 0)
            {
                i--;
                dataIn[i] = '\0';
            }
            continue;
        }

        /* fine comando */
        if(c == '\r' || c == '\n')
        {
            dataIn[i] = '\0';
            return dataIn;
        }

        /* salva il carattere se c'è spazio */
        if(i < (UART_BUFFER_SIZE - 1))
        {
            dataIn[i++] = c;
        }
    }
}