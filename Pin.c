/* 
 * File:   Pin.c
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */

#include <p32xxxx.h>
#include "Pin.h"

void initPins(void)
{
    TRISAbits.TRISA1 = 0;
    LATAbits.LATA1 = 0;
}