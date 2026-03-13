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


/* include user header file here*/
	/*for example #include "GPIO.h" */
/*
 * 
 */

#include "GPIO.h"




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
#pragma config FPLLODIV =	DIV_2


/* Add all #define here */
//for example #define DELAY 1000000 //1sec used if no Timer is implemented
/*
 * 
 */

#define DELAY 100000 //1sec used if no Timer is implemented


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

void accensioneLedEveryDELAY(void) 
{   
    /*
     * Accende automaticamente i led, uno alla volta, aspettando il DELAY 
     * definito nel main.c.
     * Accensione da LED0 (destra) a LED7 (sinistra) e spegnimento successivo
     */
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

void accensioneLedOnSwitch(void)
{
    /*
     * Accende il LED corrispondente allo SWItCH attivato
     */
    LED0 = readSwitch(0);
    LED1 = readSwitch(1);
    LED2 = readSwitch(2);
    LED3 = readSwitch(3);
    LED4 = readSwitch(4);
    LED5 = readSwitch(5);
    LED6 = readSwitch(6);
    LED7 = readSwitch(7);
}

/* Main function */
void main()
{
/* init local variables here*/

/* call init functions here */
    
    initLeds();
    initSwitches();

/* Endless loop */   
    while(1)    // forever loop
    {
        // decommentare la funzione che si vuole utilizzare
        
        accensioneLedEveryDELAY();
        // accensioneLedOnSwitch();
    }
}




