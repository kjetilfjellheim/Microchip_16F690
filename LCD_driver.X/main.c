
#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#define _XTAL_FREQ 125000L       /* required for __delay_ms, __delay_us macros */
#define WAIT_TIME 500

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
/*
 * Address to set for first address.
 */
const unsigned char FIRST_ADDRESS = 3;
/*
 * Address to set for second address.
 */
const unsigned char SECOND_ADDRESS = 2;

/**
 * Sets value.
 */
void doChange(unsigned char, unsigned char);
void setAddress(unsigned char);
void setValue(unsigned char);
void latch();

void main(void) {
    /**
     * Initalize controller.
     */
    InitApp();
    /**
     * First value.
     */
    unsigned char firstVal = 0;
    /**
     * Second value.
     */
    unsigned char secondVal = 0;

    while (1) {   
        /**
         * Set values.
         */
        doChange(firstVal, SECOND_ADDRESS);
        doChange(secondVal, FIRST_ADDRESS);
        /**
         * Count
         */
        firstVal += 1;        
        if (firstVal == 10) {
            secondVal += 1;
            firstVal = 0;
            if (secondVal == 10) {
                secondVal = 0;
            }
        }
        /**
         * Wait one second.         
         */
        __delay_ms(1000);
    }

}

void doChange(unsigned char val, unsigned char addr) {
    /**
     * Set on output.
     */
    setAddress(addr);
    /**
     * Sets value on output. 
     */
    setValue(val);
    /**
     * Set the values on the driver.
     */
    latch();
}

/**
 * Set address. This also holds the latch HIGH.
 */
void setAddress(unsigned char addr) {
    unsigned char val = addr;
    val = val << 6;
    val = val | 0b00010000;
    PORTB = val;
    __delay_us(WAIT_TIME);
}

/**
 * Set the value on the output.
 */
void setValue(unsigned char val) {
    unsigned char output = val;
    output = output << 4;
    PORTC = output;
    __delay_us(WAIT_TIME);
}

/**
 * Latch the value on the LCD driver.
 */
void latch() {
    PORTB = PORTB & 0b11101111;
    __delay_us(WAIT_TIME);
    PORTB = PORTB | 0b00010000;
    __delay_us(WAIT_TIME);
}

