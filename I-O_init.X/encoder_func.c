//================================================================================
//	FILE NAME:		CA_encoders.c
//
//	DESCRIPTION: This file includes functions associated with getting position
//                   info from the encoders.  Ultimately this will be a good place
//                   for velocity functions and if more complex position calcs are
//                   needed to return a good value, such as a position estimator.
//
//	AUTHOR: C. Alex Simpkins and Nima Ghods
//
//	COPYRIGHT 2014, General Vibration Corporation
//
//================================================================================

//standard includes
#include <p33FJ128MC802.h>

#include "definitions.h"
#include "globals.h"
#include "prototypes.h"

//requires qei.h which is the set of library functions for XC16 associated with
//the quadtrature encoder interface module.
#include "qei.h"

//returns position of the encoder requested, 1 or 2. Can also grab position directly
//but here we could perform checks if needed later. The ReadQEIN() functions are
//library functions for XC16.
long get_position(char encoder_number)
{
    if (encoder_number==1)
        return ((long)ReadQEI1());

    else if (encoder_number==2)
        return((long)ReadQEI2());

    else
        return 0;
}
