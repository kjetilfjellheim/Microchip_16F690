
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"


void InitApp(void)
{
    OSCCONbits.IRCF = 0b001;
    WPUB = 0b11111111;
    /**
     * This bit is used as chip select.
     */
    TRISBbits.TRISB4 = 0;

    /**
     * These tweo bits are used as adress select. Only one of these 
     * bits are used in this application as it`s driving two
     * seven segement displays.
     */
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    
    /**
     * This is the value that`s being set.
     */
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;    
}

