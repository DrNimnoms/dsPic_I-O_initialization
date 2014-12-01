//================================================================================
//	FILE NAME: main.c
//
//	DESCRIPTION: sets up all the I/O's for GIMINI round boards and Test circuit
//
//	AUTHOR: Nima Ghods
//
//      EDITING: Nima Ghods
//
//      COPYRIGHT 2014, General Vibration Corporation
//================================================================================

#include <stdio.h>
#include <stdlib.h>
//we need this for this pic to use any of its pin macros (ie outputs, inputs, etc)
#include <p33FJ128MC802.h>


//these are just what they say...
#include "definitions.h"
#include "globals.h"
#include "prototypes.h"
#include "I2CSlaveDrv.h"

int adcTest=0;
int encode0=0;
int encode1=0;
int i=0;

int main(){
//    unsigned int waitTime=1000;

    init_time();

    init_ADCs();    // Initialize the A/D converter to convert AN0 and AN1
    initDma0();     // Initialise the DMA controller to buffer ADC data in conversion order
    initTmr3();     // Initialise the Timer to generate sampling event to ADC @ 8Khz rate

    init_I2C();

    init_PPS_mappings();
    init_QEI_BIG_WRAP();

    init_PWM();
//    init_LEDs();

    for(i = 0;i<256;i++)
    {
        RAMBuffer[i] = i;	//Initlize RAMBuffer with some value
                                //in case MasterI2C device wants to read
                                //before it writes to it.
    }
    
    while(1){
//        adcTest=get_ADC(0);
        encode0=get_position(1);
        encode1=get_position(2);
        delay(1000);
        i++;
    }

    return (EXIT_SUCCESS);
}



void delay(unsigned int dTime){
    unsigned int i,j;
    for(i=0;i<dTime;i++){
        for(j=dTime;j>0;j--){
        }
    }
}

