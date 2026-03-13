/* 
 * File:   GPIO.h
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */


// macros for switches button read
#define SW0 PORTFbits.RF3
#define SW1 PORTFbits.RF5
#define SW2 PORTFbits.RF4
#define SW3 PORTDbits.RD15
#define SW4 PORTDbits.RD14
#define SW5 PORTBbits.RB11
#define SW6 PORTBbits.RB10
#define SW7 PORTBbits.RB9

// macros for Led write
#define LED0 LATAbits.LATA0
#define LED1 LATAbits.LATA1
#define LED2 LATAbits.LATA2
#define LED3 LATAbits.LATA3
#define LED4 LATAbits.LATA4
#define LED5 LATAbits.LATA5
#define LED6 LATAbits.LATA6
#define LED7 LATAbits.LATA7

// macro per maschera LED
#define LED_MASK 0x00FF         // 0b  0000 0000 1111 1111

// marco per maschera SWITCH
#define SWITCH_MASK_B 0x0E00    // 0b  0000 1110 0000 0000
#define SWITCH_MASK_D 0xC000    // 0b  1100 0000 0000 0000
#define SWITCH_MASK_F 0x0038    // 0b  0000 0000 0011 1000


void initLeds(void);
void initSwitches(void);

void togglePort(char port, int bit);
void toggleLed(int led);

int readSwitch(int sw);