
/* 
 * File:   gpio.c
 * Author: Valentino Calonga
 *
 * Created on Marzo 2026 */

#include "GPIO.h"

void initLeds(void)
{
    // uso &= --> AND bit a bit
    ANSELA &= ~LED_MASK;    // setto a DIGITALI i bit del registro A nella sezione che gestisce i LED 
    TRISA  &= ~LED_MASK;    // setto a OUTPUT i bit del registro A nella sezione che gestisce i LED 
    LATA   &= ~LED_MASK;    // setto a SPENTI i bit del registro A nella sezione che gestisce i LED 
}

void initSwitches(void)
{
    // setto a DIGITALI i bit dei registri B, D, F per la parte degli switch
    ANSELB &= ~SWITCH_MASK_B;
    ANSELD &= ~SWITCH_MASK_D;
    ANSELF &= ~SWITCH_MASK_F;
    
    // setto a INPUT i bit dei registri B, D, F per la parte degli switch
    TRISB  |=  SWITCH_MASK_B;
    TRISD  |=  SWITCH_MASK_D;
    TRISF  |=  SWITCH_MASK_F;
}

void togglePort(char port, int bit)
{
    /* creo una maschera (metto a 1 solo il bit che mi interessa)
     * mask avrà 0 in tutti i bit, tranne quello scelto passandolo alla funzione
     * "shifto" quindi a sinistra il numero 1 un numero "bit" di volte
    */
    unsigned int mask = 1 << bit;

    /* con lo switch seleziono la porta su cui eseguire l'operazione
     * con LATxINV eseguo l'inversione del bit dove la maschera contiene 1
     * p.es:  
     * bit 0 --> 00000001  [uso:    togglePort('x', 0)]
	 * bit 1 --> 00000010  [uso:    togglePort('x', 1)]
	 * bit 2 --> 00000100  [uso:    togglePort('x', 2)]
	 * bit 3 --> 00001000  [uso:    togglePort('x', 3)]
    */
    switch(port)
    {
        case 'A':
            LATAINV = mask;
            break;

        case 'B':
            LATBINV = mask;
            break;

        case 'C':
            LATCINV = mask;
            break;

        case 'D':
            LATDINV = mask;
            break;

        case 'E':
            LATEINV = mask;
            break;

        case 'F':
            LATFINV = mask;
            break;

        case 'G':
            LATGINV = mask;
            break;

        default:
            break;
    }
}

int readSwitch(int sw)
{
    switch(sw)
    {
        case 0: return SW0;
        case 1: return SW1;
        case 2: return SW2;
        case 3: return SW3;
        case 4: return SW4;
        case 5: return SW5;
        case 6: return SW6;
        case 7: return SW7;
        default: return 0;
    }
}