//================================================================================
//	FILE NAME:		Init.c
//
//	DESCRIPTION: This file includes functions associated with intializing the
//                   basic functionality of the module.  This includes things like
//                   the encoder modules, mapping pins in the PPS setup (ie making
//                   a particular pin the TX for serial output, as some pins are
//                   mappable, and must be mapped), and the led pin directions.
//
//	AUTHOR: Nima Ghods
//
//	COPYRIGHT 2014, Coactive Drive Corporation
//
//================================================================================

//uses our standard headers
#include <p33FJ128MC802.h>

#include "definitions.h"
#include "globals.h"
#include "prototypes.h"

void init_I2C(void){
    I2C1CONbits.I2CEN=1;  // Enables the I2Cx module and configures the SDAx and SCLx pins as serial port pins

}

void init_PPS_mappings(void)
{
//    //quadrature encoder 1
//    _QEA1R = 5; //0b00101;  //RP5
//    _QEB1R = 6; //0b00110;  //RP6
//    _INDX1R = 7; //0b00111; //RP7
//
//    //quadrature encoder 2
//    _QEA2R = 8;
//    _QEB2R = 9;
//    _INDX2R = 10;
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

void init_BUTTONs(void){
    AD1PCFGLbits.PCFG0=1;
    BUTTON_PIN_DIRECTION=INPUT;
}

void init_LEDs(void)
{
    GLED_PIN_DIRECTION = OUTPUT;
    RLED_PIN_DIRECTION = OUTPUT;
    GLED=OFF;
    RLED=OFF;
}