//================================================================================
//	FILE NAME:		ADC_func.c
//
//	DESCRIPTION: This file includes functions associated with getting ADC
//                   info from the potentiometer.  Ultimately this will be a
//                   good placefor any filtering or averaging that needs to be
//                   done on the ADC value.
//
//	AUTHOR: Nima Ghods
//
//	COPYRIGHT 2014, General Vibration Corporation
//
//================================================================================

//standard includes
#include <p33FJ128MC802.h>

#include "definitions.h"
#include "globals.h"
#include "prototypes.h"


//returns ADC value of the potentiometer requested, 1 or 2.
int get_ADC(char pot_number)
{
    if(pot_number == 0) AD1CSSLbits.CSS0 = 1;
    if(pot_number == 1) AD1CSSLbits.CSS1 = 1;
    AD1CON1bits.SAMP = 0;
    AD1CON1bits.DONE = 0;
    while(AD1CON1bits.DONE);
    return ADC1BUF0;
}