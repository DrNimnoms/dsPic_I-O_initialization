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


int main(){
    unsigned int waitTime=1000;
    init_time();
    init_PWM();
    init_LEDs();
    int blink=0;

    while(1){
        
        delay(waitTime);
        if(blink==0)GLED=ON;
        else RLED=ON;
        delay(waitTime);
        GLED=OFF;
        RLED=OFF;
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

