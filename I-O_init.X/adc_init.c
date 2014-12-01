//================================================================================
//	FILE NAME:		Init.c
//
//	DESCRIPTION: This file includes functions associated with intializing the
//                   ADC module
//
//	AUTHOR: Nima Ghods
//
//	COPYRIGHT 2014, General Vibration Corporation
//
//================================================================================


//uses our standard headers
#include <p33FJ128MC802.h>

#include "definitions.h"
#include "globals.h"
#include "prototypes.h"

// Define Message Buffer Length for ECAN1/ECAN2
#define  MAX_CHNUM	 		1		// Highest Analog input number enabled for alternate sampling
#define  SAMP_BUFF_SIZE	 		16		// Size of the input buffer per analog input


// Number of locations for ADC buffer = 2 (AN4 and AN5) x 16 = 32 words
// Align the buffer to 32words or 64 bytes. This is needed for peripheral indirect mode
int  BufferA[MAX_CHNUM+1][SAMP_BUFF_SIZE] __attribute__((space(dma),aligned(64)));
int  BufferB[MAX_CHNUM+1][SAMP_BUFF_SIZE] __attribute__((space(dma),aligned(64)));

void ProcessADCSamples(int * AdcBuffer);

void init_ADCs(void){
    POT1_PIN_DIRECTION = INPUT;         // set ADC pin to input
    POT2_PIN_DIRECTION = INPUT;         // set ADC pin to input

    AD1CON1bits.SSRC   = 2;		// Sample Clock Source: GP Timer starts conversion
    AD1CON1bits.ASAM   = 1;		// ADC Sample Control: Sampling begins immediately after conversion
    AD1CON1bits.AD12B  = 0;		// 10-bit ADC operation


    AD1CON2bits.ALTS  = 1;			// Alternate Input Sample Mode Select Bit
    AD1CON2bits.CHPS  = 0;		// Converts CH0

    AD1CON3bits.ADRC = 0;		// ADC Clock is derived from Systems Clock
    AD1CON3bits.ADCS = 63;		// ADC Conversion Clock Tad=Tcy*(ADCS+1)= (1/40M)*64 = 1.6us (625Khz)
                                                            // ADC Conversion Time for 10-bit Tc=12*Tab = 19.2us

    AD1CON1bits.ADDMABM = 0; 	// DMA buffers are built in scatter/gather mode
    AD1CON2bits.SMPI    = 1;	// SMPI Must be programmed to 1 for this case
    AD1CON4bits.DMABL   = 4;	// Each buffer contains 16 words

    //AD1CHS0: A/D Input Select Register
    AD1CHS0bits.CH0SA=0;		// MUXA +ve input selection (AIN4) for CH0
    AD1CHS0bits.CH0NA=0;		// MUXA -ve input selection (Vref-) for CH0

    AD1CHS0bits.CH0SB=1;		// MUXB +ve input selection (AIN5) for CH0
    AD1CHS0bits.CH0NB=0;		// MUXB -ve input selection (Vref-) for CH0		// MUXB -ve input selection (Vref-) for CH0

    //AD1PCFGH/AD1PCFGL: Port Configuration Register
    AD1PCFGL           = 0xFFFF;
    POT1_PIN_ANALOG = ON;       // set ADC pin to analog
    POT2_PIN_ANALOG = ON;       // set ADC pin to analog


    IFS0bits.AD1IF = 0;			// Clear the A/D interrupt flag bit
    IEC0bits.AD1IE = 0;			// Do Not Enable A/D interrupt
    AD1CON1bits.ADON = 1;		// Turn on the A/D converter         // ADC module is operating

}

/*=============================================================================
Timer 3 is setup to time-out every 125 microseconds (8Khz Rate). As a result, the module
will stop sampling and trigger a conversion on every Timer3 time-out, i.e., Ts=125us.
=============================================================================*/
void initTmr3()
{
    TMR3 = 0x0000;
    PR3 = 4999;
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 0;

    //Start Timer 3
    T3CONbits.TON = 1;

}


// DMA0 configuration
// Direction: Read from peripheral address 0-x300 (ADC1BUF0) and write to DMA RAM
// AMODE: Peripheral Indirect Addressing Mode
// MODE: Continuous, Ping-Pong Mode
// IRQ: ADC Interrupt
// ADC stores results stored alternatively between DMA_BASE[0]/DMA_BASE[16] on every 16th DMA request

void initDma0(void)
{
    DMA0CONbits.AMODE = 2;			// Configure DMA for Peripheral indirect mode
    DMA0CONbits.MODE  = 2;			// Configure DMA for Continuous Ping-Pong mode

    DMA0PAD=(int)&ADC1BUF0;
    DMA0CNT = (SAMP_BUFF_SIZE*2)-1;

    DMA0REQ=13;

    DMA0STA = __builtin_dmaoffset(BufferA);
    DMA0STB = __builtin_dmaoffset(BufferB);

    IFS0bits.DMA0IF = 0;			//Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = 1;			//Set the DMA interrupt enable bit

    DMA0CONbits.CHEN=1;

}

/*=============================================================================
_DMA0Interrupt(): ISR name is chosen from the device linker script.
=============================================================================*/

unsigned int DmaBuffer = 0;

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{

    if(DmaBuffer==0) {
            ProcessADCSamples(&BufferA[0][0]);
            ProcessADCSamples(&BufferA[1][0]);

    } else {
            ProcessADCSamples(&BufferB[0][0]);
            ProcessADCSamples(&BufferB[1][0]);
    }

    DmaBuffer ^= 1;

    IFS0bits.DMA0IF = 0;		//Clear the DMA0 Interrupt Flag
}


void ProcessADCSamples(int * AdcBuffer)
{
	/* Do something with ADC Samples */
    
}