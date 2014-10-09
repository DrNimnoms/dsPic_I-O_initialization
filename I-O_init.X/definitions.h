//================================================================================
//	FILE NAME:		definitions.h
//
//	DESCRIPTION: This file includes definitions for various useful values and
//                   references.  The clock frequency is defined, several useful
//                   pins and pin latch states are mapped to variables as well.
//
//	AUTHOR: Nima Ghods
//
//	COPYRIGHT 2014, Coactive Drive Corporation
//
//================================================================================

#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ON 0
#define OFF 1

#define INPUT 1
#define OUTPUT 0

//led pins
#define GLED _LATA3
#define RLED _LATA4

//button pins
#define BUTTON _RA0

//led direction controls
#define GLED_PIN_DIRECTION _TRISA3
#define RLED_PIN_DIRECTION _TRISA4

//button direction controls
#define BUTTON_PIN_DIRECTION _TRISA0


// The SparkFun breakout board defaults to 1, set to 0 if SA0 jumper on the bottom of the board is set
#define MMA8452_ADDRESS 0x1D  // 0x1D if SA0 is high, 0x1C if low
#define GSCALE 2 // Sets full-scale range to +/-2, 4, or 8g. Used to calc real g values.
//Define a few of the registers that we will be accessing on the MMA8452
#define OUT_X_MSB 0x01
#define XYZ_DATA_CFG  0x0E
#define WHO_AM_I   0x0D
#define CTRL_REG1  0x2A


#ifdef	__cplusplus
}
#endif

#endif	/* DEFINITIONS_H */

