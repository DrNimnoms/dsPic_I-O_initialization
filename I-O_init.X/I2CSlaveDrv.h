/* 
 * File:   I2CSlaveDrv.h
 * Author: nimaghods
 *
 * Created on November 30, 2014, 7:37 PM
 */

#ifndef I2CSLAVEDRV_H
#define	I2CSLAVEDRV_H

//Functions prototype
void i2c1_init(void);
void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt(void);

extern unsigned char RAMBuffer[256];	//RAM area which will work as EEPROM for Master I2C device

struct FlagType
{
	unsigned char AddrFlag:1;
	unsigned char DataFlag:1;
};
extern struct FlagType Flag;

#endif	/* I2CSLAVEDRV_H */

