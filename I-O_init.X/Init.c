//================================================================================
//	FILE NAME:		Init.c
//
//	DESCRIPTION: This file includes functions associated with intializing the
//                   basic functionality of the Gemini Shield.  This includes things like
//                   the encoder modules, mapping pins in the PPS setup (ie making
//                   a particular pin the TX for serial output, as some pins are
//                   mappable, and must be mapped), and the led pin directions.
//
//	AUTHOR: Nima Ghods and C. Alex Simpkins
//
//	COPYRIGHT 2014, General Vibration Corporation
//
//================================================================================

//uses our standard headers
#include <p33FJ128MC802.h>

#include "definitions.h"
#include "globals.h"
#include "prototypes.h"

void init_I2C(void){

    I2C_Add_PIN_DIRECTION = INPUT;      // set I2C address pin to input
    I2C_Add_PIN_ANALOG = OFF;        // set I2C address pin to digital
    //I2C_Add                           //I2C_Add is 0 or 1 depending on which gemini drive control it is on the shield

    I2C1CONbits.I2CEN=1;  // Enables the I2Cx module and configures the SDAx and SCLx pins as serial port pins

}

void init_ADCs(void){
    POT1_PIN_DIRECTION = INPUT; // set ADC pin to input
    POT2_PIN_DIRECTION = INPUT; // set ADC pin to input
    POT1_PIN_ANALOG = ON;       // set ADC pin to analog
    POT2_PIN_ANALOG = ON;       // set ADC pin to analog
    AD1CON2bits.VCFG=0;         // sets voltage reference to AVdd and AVss
    AD1CON2bits.CHPS=1;
    AD1CON1bits.ASAM=1;         // Sampling begins immediately after last conversion
    AD1CON1bits.ADON=1;         // ADC module is operating
}


void init_time(void){
   /* Configure Oscillator to operate the device at 40Mhz
	   Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 	   Fosc= 7.37*(43)/(2*2)~80Mhz for Fosc, Fcy ~ 40Mhz */

//initialize pll // 7.37/2*43/2=79.2275 for Fosc, Fcy ~ 39.61Mhz
    CLKDIVbits.PLLPRE = 0;   // N1=2
    PLLFBDbits.PLLDIV = 43;  // M=43
    CLKDIVbits.PLLPOST = 0;  // N2=0
    while(OSCCONbits.LOCK != 1);    // wait for PLL ready

}

void init_PWM(void){

/* ~~~~~~~~~~~~~~~~~~~~~~~~~ PWM Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    P1TPER = 792;            /* PTPER = ((792) * 25.24 ns) = 20 us, where 500ns
							is the PWM period and 25.24 ns (39.61Mhz) is PWM resolution. */

    P1DC1 = 200;             /* PWM1 duty cycle app 200 * 25.24ns */

    P1DC2 = 200;             /* PWM2 duty cycle app 200 * 25.24ns */

    /* Note that a pulse appears only on every other PWM cycle. So in push-pull
       mode, the effective duty cycle is 25% */

    PWM1CON1bits.PEN1H=1;
    PWM1CON1bits.PEN1L=1;
    PWM1CON1bits.PEN2H=1;
    PWM1CON1bits.PEN2L=1;
    P1TCONbits.PTEN = 1;     /* Turn ON PWM module */
}

void init_LEDs(void)
{
    GLED_PIN_DIRECTION = OUTPUT;
    RLED_PIN_DIRECTION = OUTPUT;
    GLED=OFF;
    RLED=OFF;
}

void init_PPS_mappings(void)
{
    //quadrature encoder 1
    _QEA1R = 2;   //RP2
    _QEB1R = 3;   //RP3
    _INDX1R = 4;  //RP4

    //quadrature encoder 2
    _QEA2R = 5; //RP5
    _QEB2R = 6; //RP6
    _INDX2R = 7; //RP7
}

void init_QEI(void)
{
    //-------module 1--------

    //Make pins associated with encoder inputs...
    _TRISB2 = INPUT;
    _TRISB3 = INPUT;
    _TRISB4 = INPUT;

    QEI1CONbits.QEIM = 0; //disable QEI module for setup
    QEI1CONbits.CNTERR = 0; //clear count errors
    //QEI1CONbits.QEISIDLE = 0; //don't stop during sleep
    QEI1CONbits.SWPAB = 0; //QEA and B not swapped
    QEI1CONbits.PCDOUT = 1; //normal io pin operation
    QEI1CONbits.POSRES = 1; //index pulse resets position
    QEI1CONbits.QEIM = 6; //0b110; //position counter reset by index //101;//
    POS1CNT = 0; //reset position counter
    MAX1CNT = 256; //reset after 512 counts
    DFLT1CONbits.QEOUT = 1;
    DFLT1CONbits.QECK = 1;
    //------------------------



    //========module 2=========

    //Make pins associated with encoder inputs...
    _TRISB5 = INPUT;
    _TRISB6 = INPUT;
    _TRISB7 = INPUT;

    QEI2CONbits.QEIM = 0; //disable QEI module for setup
    QEI2CONbits.CNTERR = 0; //clear count errors
    //QEI1CONbits.QEISIDLE = 0; //don't stop during sleep
    QEI2CONbits.SWPAB = 0; //QEA and B not swapped
    QEI2CONbits.PCDOUT = 1; //normal io pin operation
    QEI2CONbits.POSRES = 1; //index pulse resets position
    QEI2CONbits.QEIM = 6; //position counter reset by index
    POS2CNT = 0; //reset position counter
    MAX2CNT = 256;
    DFLT2CONbits.QEOUT = 1;
    DFLT2CONbits.QECK = 1;
    //==========================

}

//initialize the quadrature encoder to not reset every rotation.  This has an
//advantage in the the control can lag behind but eventually catch up.  It gets
//complex to reset the encoder every rotation.  This wraps at 65535.
void init_QEI_BIG_WRAP(void)
{

    //*****************module 1********************

    //Make pins associated with encoder inputs...
    _TRISB2 = INPUT;
    _TRISB3 = INPUT;
    _TRISB4 = INPUT;

    QEI1CONbits.QEIM = 0; //disable QEI module for setup
    QEI1CONbits.CNTERR = 0; //clear count errors
    //QEI1CONbits.QEISIDLE = 0; //don't stop during sleep
    QEI1CONbits.SWPAB = 0; //QEA and B not swapped
    QEI1CONbits.PCDOUT = 1; //normal io pin operation
    QEI1CONbits.POSRES = 0; //index pulse resets position
    QEI1CONbits.QEIM = 0b111; //0b110; //position counter reset by index //101;//
    POS1CNT = 0; //reset position counter
    MAX1CNT = 65535;
    DFLT1CONbits.QEOUT = 1;
    DFLT1CONbits.QECK = 1;
    //*********************************************


    //^^^^^^^^^^^^^^^^^module 2^^^^^^^^^^^^^^^^^^^^

    //Make pins associated with encoder inputs...
    _TRISB5 = INPUT;
    _TRISB6 = INPUT;
    _TRISB7 = INPUT;

    QEI2CONbits.QEIM = 0; //disable QEI module for setup
    QEI2CONbits.CNTERR = 0; //clear count errors
    //QEI1CONbits.QEISIDLE = 0; //don't stop during sleep
    QEI2CONbits.SWPAB = 0; //QEA and B not swapped
    QEI2CONbits.PCDOUT = 1; //normal io pin operation
    QEI2CONbits.POSRES = 0; //index pulse resets position
    QEI2CONbits.QEIM = 0b111; //position counter reset by index
    POS2CNT = 0; //reset position counter
    MAX2CNT = 65535;
    DFLT2CONbits.QEOUT = 1;
    DFLT2CONbits.QECK = 1;
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
