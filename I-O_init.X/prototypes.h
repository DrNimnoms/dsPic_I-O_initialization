//================================================================================
//	FILE NAME:		prototypes.h
//
//	DESCRIPTION: This file includes all function prototypes used throughout.
//
//	AUTHOR: Nima Ghods and C. Alex Simpkins
//
//	COPYRIGHT 2014, General Vibration Corporation
//
//================================================================================

#include <p33FJ128MC802.h>

#ifndef PROTOTYPES_H
#define	PROTOTYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

//initializations...
void init_time(void);           //initialize timer
void init_LEDs(void);           //initialize LED outputs
void init_ADCs(void);
void init_PWM(void);            //initialize PWM outputs
void init_PPS_mappings(void);   //set pin mapping
void init_I2C(void);
void delay(unsigned int);


#ifdef	__cplusplus
}
#endif

#endif	/* PROTOTYPES_H */

