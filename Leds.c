/* 
 * File:   Leds.c
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */

#include "Leds.h"
#include "GPIO.h"
#include <p32xxxx.h>

void setLed(int ledNumber, int state)
{
    switch(ledNumber)
    {
        case 0: LED0 = state; break;
        case 1: LED1 = state; break;
        case 2: LED2 = state; break;
        case 3: LED3 = state; break;
        case 4: LED4 = state; break;
        case 5: LED5 = state; break;
        case 6: LED6 = state; break;
        case 7: LED7 = state; break;
        default: break;
    }
}