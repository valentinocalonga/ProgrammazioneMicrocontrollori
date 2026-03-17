#include "TIMER_Serie4_Es1_NOINTERRUPT.h"
#include "Timer.h"
#include <p32xxxx.h>
#include <string.h>

#define BAUDRATE 9600
#define LED_COUNT 8
#define TIMER500MS_HIGH_WORD 0x0001
#define TIMER500MS_LOW_WORD  0x312D

void initTimer23_32bit(void)
{
    T2CONbits.ON = 0;        // stop timer
    T2CONbits.T32 = 1;       // 32 bit mode
    T2CONbits.TCS = 0;       // internal clock
    T2CONbits.TCKPS = 0b111; // prescaler 1:256

    TMR2 = 0;
    TMR3 = 0;

    // NON uso PR2 e PR3

    T2CONbits.ON = 1;        // start timer
}

void wait500ms(void)
{
    T2CONbits.ON = 0;   // fermo il timer
    TMR2 = 0;
    TMR3 = 0;
    T2CONbits.ON = 1;   // riparto da zero

    while (TMR3 < TIMER500MS_HIGH_WORD)
    {
    }

    while (TMR2 < TIMER500MS_LOW_WORD)
    {
    }

    T2CONbits.ON = 0;   // opzionale, ma pulito
}

void ledsTurnOnSequence(void)
{
    putU4_string("Leds turning on\r\n");

    for (int i = 0; i < LED_COUNT; i++)
    {
        setLed(i, 1);

        if (i < (LED_COUNT - 1))
        {
            wait500ms();
        }
    }
}

void ledsTurnOffSequence(void)
{
    putU4_string("Leds turning off\r\n");

    for (int i = 7; i >= 0; i--)
    {
        setLed(i, 0);

        if (i > 0)
        {
            wait500ms();
        }
    }
}

void TIMER_Serie4_processCommand(char *cmd)
{
    if (strcmp(cmd, "ledon") == 0)
    {
        ledsTurnOnSequence();
    }
    else if (strcmp(cmd, "ledoff") == 0)
    {
        ledsTurnOffSequence();
    }
    else
    {
        putU4_string("Invalid command\r\n");
    }
}

void TIMER_Serie4_Es1_NOINTERRUPT(void) 
{
    /*
     * Scrivere un programma su microcontrollore in grado di: 
     * - attivare e disattivare l'accensione dei LED<0-7> con i comandi: 
     *   ledon e ledoff che arrivano da UART 
     *   (9600 baudrate, no parity, 1 stop bit, no HW control)
     * - il programma attende l'arrivo di un comando sulla UART (ricezione).
     *  se comando ledon: accensione dei LED<0-7> 
     *  con intervallo di 0.5 sec tra LEDi e il successivo 
     *  e risposta sul terminale (trasmissione) del messaggio "Leds turning on"
     *  se comando ledoff: spegnimento dei LED<7-0> 
     *  con intervallo di 0.5 sec tra LEDi e il successivo 
     *  e risposta sul terminale (trasmissione) del messaggio "Leds turning off"
     * 
     *  Il tempo che intercorre tra l'accensione di un led e il successivo viene gestito dal TIMER2.
     *  Analogamente per la fase di spegnimento dei leds.
     * 
     *  COMMENTO: 
     *  Ho scelto TIMER2/TIMER3 in modalità 32 bit perché TIMER2 singolo 
     *  a 16 bit non consente di ottenere direttamente 0.5 s 
     *  con il clock disponibile
     * 
     *  Se usiamo prescaler 1:256:
     *  f{timer} = 40 x 10^6 / 256 = 156'250 Hz
     *  PR:  156'250 x 0.5 = 78'125 
     *  78125 = 0x0001 312D
     * 
     */
    
    initLeds();
    initUART(BAUDRATE);
    initTimer23_32bit();

    putU4_string("UART ready. Commands: ledon / ledoff\r\n");

    while (1)
    {
        char *cmd = getString();

        if (cmd[0] != '\0')
        {
            TIMER_Serie4_processCommand(cmd);
        }
    }
}
