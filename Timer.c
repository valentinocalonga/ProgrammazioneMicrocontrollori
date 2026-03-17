/* 
 * File:   Timer.c
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */

#include <p32xxxx.h>
#include "Timer.h"

void initTimer2(void)
{
    T2CONbits.ON = 0;
    T2CONbits.TCKPS = 0b111;
    T2CONbits.T32 = 0;
    TMR2 = 0;
    PR2 = 20000;
    T2CONbits.ON = 1;
}

void delay(int delay) {
    while(delay--);
}