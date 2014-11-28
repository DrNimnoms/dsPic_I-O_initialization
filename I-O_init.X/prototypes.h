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

// initializations...
void init_time(void);           // initialize timer
void init_LEDs(void);           // initialize LED outputs
void init_ADCs(void);           // initialize ADC inputs
void init_PWM(void);            // initialize PWM outputs
void init_PPS_mappings(void);   // set pin mapping
void init_QEI(void);            //initialize quadrature modules
void init_QEI_BIG_WRAP(void);   //change quadrature module initialization to 65535 wrap of position
void init_I2C(void);            // initialize I2C communication

// read ADC
int get_ADC(char pot_number);   // read the ADC from the given pot number

// motor functions




void delay(unsigned int);


#ifdef	__cplusplus
}
#endif

#endif	/* PROTOTYPES_H */

