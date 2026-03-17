/* 
 * File:   GPIO.h
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */
#include <p32xxxx.h>

#ifndef GPIO_H
#define GPIO_H

// Switch input macros
#define SW0 PORTFbits.RF3
#define SW1 PORTFbits.RF5
#define SW2 PORTFbits.RF4
#define SW3 PORTDbits.RD15
#define SW4 PORTDbits.RD14
#define SW5 PORTBbits.RB11
#define SW6 PORTBbits.RB10
#define SW7 PORTBbits.RB9

// LED output macros
#define LED0 LATAbits.LATA0
#define LED1 LATAbits.LATA1
#define LED2 LATAbits.LATA2
#define LED3 LATAbits.LATA3
#define LED4 LATAbits.LATA4
#define LED5 LATAbits.LATA5
#define LED6 LATAbits.LATA6
#define LED7 LATAbits.LATA7

#define LED_MASK       0x00FF
#define SWITCH_MASK_B  0x0E00
#define SWITCH_MASK_D  0xC000
#define SWITCH_MASK_F  0x0038

void initLeds(void);
void initSwitches(void);
void togglePort(char port, int bit);
int readSwitch(int sw);

#endif