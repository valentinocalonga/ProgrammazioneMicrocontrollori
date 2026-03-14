/* 
 * File:   main.c
 * Author: Valentino Calonga
 * Title:  Serie
 * Created on :  Marzo 2026
 */
 

/* include general header file here*/
/*
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <string.h>



/* include user header file here*/
	/*for example #include "GPIO.h" */
/*
 * 
 */

#include "GPIO.h"
#include "Uart.h"
#include "Leds.h"
#include "EasterEgg.h"

/* Pragma definition */
/*
 * These instructions set SYSCLK and PBCLK (next weeks you will be able to write it)
 */
//for system clock and for pbclk
#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      

/* this set the SYSCLK (80 MHz) and the PBCLK (20 MHz)*/
// Device Config Bits in  DEVCFG1:	
#pragma config FNOSC =	FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	XT
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_2

// Device Config Bits in  DEVCFG2:	
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1


/* Add all #define here */
//for example #define DELAY 1000000 //1sec used if no Timer is implemented
/*
 * 
 */

#define DELAY 1000000 //1sec used if no Timer is implemented
#define BAUDRATE 9600 // baudrate da impostare su SerialTools


/* Init global variables here*/
/*
 * 
 */



/* Declare global functions here*/
/*
 * 
 */



/* Write function used in main.c*/

void delay(int delay) {
    while(delay--);
}

void GPIO_Serie1_es3_accensioneLedEveryDELAY(void) 
{   
    /*
     * Accende automaticamente i led, uno alla volta, aspettando il DELAY 
     * definito nel main.c.
     * Accensione da LED0 (destra) a LED7 (sinistra) e spegnimento successivo
     */
    while (1) {
        delay(DELAY);
        toggleLed(0);

        delay(DELAY);
        toggleLed(1);

        delay(DELAY);
        toggleLed(2);

        delay(DELAY);
        toggleLed(3);

        delay(DELAY);
        toggleLed(4);

        delay(DELAY);
        toggleLed(5);

        delay(DELAY);
        toggleLed(6);

        delay(DELAY);
        toggleLed(7);  
    }
}

unsigned char accensioneLedOnSwitch(void)
/*
 * Legge lo stato degli 8 switch e:
 *  - accende il LED corrispondente ad ogni switch attivo
 *  - costruisce una "maschera di bit" che rappresenta quali switch sono a ON
 *
 * Ogni bit della variabile swState rappresenta uno switch:
 *  bit 0 -> switch 0
 *  bit 1 -> switch 1
 *  ...
 *  bit 7 -> switch 7
 *
 * NOTA: Viene utilizzato l'operatore |= che è una OR bit a bit:
 * 
 * Esempio:
 *  Se sono attivi SW1 e SW3 -> swState = 00001010 
 *
 */
{
    unsigned char swState = 0;   // inizialmente nessuno switch attivo

    LED0 = readSwitch(0);         // accende/spegne LED0 in base allo switch 0
    if(LED0) swState |= (1 << 0); // se switch 0 attivo, setta il bit 0 a 1

    LED1 = readSwitch(1);         // accende/spegne LED1 in base allo switch 1
    if(LED1) swState |= (1 << 1); // se switch 1 attivo, setta il bit 1 a 1  

    LED2 = readSwitch(2);         // accende/spegne LED2 in base allo switch 2
    if(LED2) swState |= (1 << 2); // se switch 2 attivo, setta il bit 2 a 1

    LED3 = readSwitch(3);
    if(LED3) swState |= (1 << 3);

    LED4 = readSwitch(4);
    if(LED4) swState |= (1 << 4);

    LED5 = readSwitch(5);
    if(LED5) swState |= (1 << 5);

    LED6 = readSwitch(6);
    if(LED6) swState |= (1 << 6);

    LED7 = readSwitch(7);
    if(LED7) swState |= (1 << 7);

    return swState;   // ritorna lo stato complessivo degli switch
}

void GPIO_Serie1_es4_accensioneLedOnSwitch(void) 
{
    while(1)    // forever loop
    {
       accensioneLedOnSwitch();
    }
}

void UART_Slide3_Examples(void) {
    
    /* Delay counter */
    unsigned int UARTcounter = 10000000;
    
    while(1) {
        while(UARTcounter) {
            UARTcounter--;
        }
        
        putU4_string("Ciao!\r\n");
        UARTcounter = 10000000;
    }
   
}

unsigned char UART_Serie2_es1_SwitchToLedAndText(unsigned char previousState)
{
    unsigned char currentState = accensioneLedOnSwitch();   // stato attuale
    unsigned char newOn = currentState & (~previousState);  // nuovi LED accesi

    for(int i = 0; i < 8; i++)
    {
        if(newOn & (1 << i))   // verifica se il bit i-esimo è passato a 1
        {
            putU4_string("LED");
            putU4('0' + i);    // conversione da numero a carattere ASCII
            putU4_string(" ON\r\n");
        }
    }

    return currentState;   // aggiorna lo stato precedente
}

void UART_Serie2_es1(void) {
    unsigned char previousState = 0;
    
    while(1)    // forever loop
    {
        previousState = UART_Serie2_es1_SwitchToLedAndText(previousState);
    }
}

void processCommand(char *cmd)
{
    int ledNumber;

    /* controllo minimo sul formato: LEDx ... */
    if(cmd[0] == 'L' && cmd[1] == 'E' && cmd[2] == 'D' &&
       cmd[3] >= '0' && cmd[3] <= '7' && cmd[4] == ' ')
    {
        ledNumber = cmd[3] - '0';

        if(strcmp(&cmd[5], "ON") == 0)
        {
            setLed(ledNumber, 1);
            putU4_string("OK, LED");
            putU4('0' + ledNumber);
            putU4_string(" acceso\r\n");
        }
        else if(strcmp(&cmd[5], "OFF") == 0)
        {
            setLed(ledNumber, 0);
            putU4_string("OK, LED");
            putU4('0' + ledNumber);
            putU4_string(" spento\r\n");
        }
        else
        {
            putU4_string("Comando non valido\r\n");
        }
    }
    else
    {
        easter01();
    }
}

void UART_Serie2_es2(void) {
    putU4_string("SERIE 2 - ESERCIZIO 2.\r\n");
    putU4_string("UART4 pronta. Inserire comando:\r\n");
    
    while(1)
    {
        char *cmd = getString();    // legge l'intera riga da terminale
        
        if(cmd[0] != '\0')
        { 
            processCommand(cmd);    // interpreta il comando ed esegue l'azione
        }
    }
}

/* Main function */
void main()
{
/* init local variables here*/

/* call init functions here */
    
    initLeds();
    initSwitches();
    initUART(BAUDRATE);

/* Endless loop */   
    /* 
    * while(1)    // forever loop
    * {
    * }
    */
    
    // GPIO_Serie1_es4_accensioneLedOnSwitch();
    // GPIO_Serie1_es3_accensioneLedEveryDELAY();
    // UART_Slide3_Examples();
    // UART_Serie2_es1();
    UART_Serie2_es2();
}




