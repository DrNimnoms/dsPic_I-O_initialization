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

int adcTest=0;
int i=0;

int main(){
//    unsigned int waitTime=1000;
//    int adcTest=0;
    init_time();

    init_ADCs();    // Initialize the A/D converter to convert AN0 and AN1
    initDma0();     // Initialise the DMA controller to buffer ADC data in conversion order
    initTmr3();     // Initialise the Timer to generate sampling event to ADC @ 8Khz rate
//    init_PWM();
//    init_LEDs();

    while(1){
//        adcTest=get_ADC(0);
        delay(100);
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

