//================================================================================
//	FILE NAME: main.c
//
//	DESCRIPTION: sets up all the I/O's for GIMINI round boards and Test circuit
//
//	AUTHOR: Nima Ghods
//
//      EDITING: Nima Ghods
//
//
//================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <p33FJ128MC802.h>

/*
 * 
 */
#define ON 0
#define OFF 1

#define INPUT 1
#define OUTPUT 0

//led pins
#define GLED _LATA3
#define RLED _LATA4

//button pins
#define BUTTON PORTAbits.RA1 //_RA0

//led direction controls
#define GLED_PIN_DIRECTION _TRISA3
#define RLED_PIN_DIRECTION _TRISA4

//button direction controls
#define BUTTON_PIN_DIRECTION _TRISA1

void init_time(void);           //initialize timer
void init_LEDs(void);           //initialize LED outputs
void init_BUTTONs(void);           //initialize LED outputs
void init_PWM(void);
void delay(unsigned int);


int main(){
    unsigned int waitTime=1000;
    init_time();
    init_PWM();
    init_BUTTONs();
    init_LEDs();
    while(1){
        if (BUTTON==0){
            GLED=ON;
        }
        else{
            GLED=OFF;
        }
        delay(waitTime);
//        GLED=ON;
        RLED=OFF;
        delay(waitTime);
//        GLED=OFF;
        RLED=ON;
    }
    return (EXIT_SUCCESS);
}

void init_time(void){
   /* Configure Oscillator to operate the device at 40Mhz
	   Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 	   Fosc= 7.37*(43)/(2*2)~80Mhz for Fosc, Fcy ~ 40Mhz */

//initialize pll // 7.37/2*43/2=79.2275 for Fosc, Fcy ~ 39.61Mhz
    PLLFBDbits.PLLDIV = 43;
    CLKDIVbits.PLLPRE = 0;   // N1=2
    PLLFBD=41;               // M=43
    CLKDIVbits.PLLPOST = 0;  // N2=0
    while(OSCCONbits.LOCK != 1);    // wait for PLL ready

}

void init_PWM(void){

/* ~~~~~~~~~~~~~~~~~~~~~~~~~ PWM Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    P1TPER = 792;            /* PTPER = ((792) * 25.24 ns) = 20 us, where 500ns
							is the PWM period and 25.24 ns is PWM resolution. */

    P1DC1 = 200;             /* PWM1 duty cycle app 200 * 25.24ns */

    P1DC2 = 200;             /* PWM2 duty cycle app 200 * 25.24ns */

    /* Note that a pulse appears only on every other PWM cycle. So in push-pull
       mode, the effective duty cycle is 25% */

    PWM1CON1bits.PEN1H=1;
    PWM1CON1bits.PEN1L=1;
    PWM1CON1bits.PEN2H=1;
    PWM1CON1bits.PEN2L=1;
    P1TCONbits.PTEN = 1;     /* Turn ON PWM module */
}

void init_BUTTONs(void){
    BUTTON_PIN_DIRECTION=INPUT;
}

void init_LEDs(void)
{
    GLED_PIN_DIRECTION = OUTPUT;
    RLED_PIN_DIRECTION = OUTPUT;
    GLED=OFF;
    RLED=OFF;
}

void delay(unsigned int dTime){
    unsigned int i,j;
    for(i=0;i<dTime;i++){
        for(j=dTime;j>0;j--){
        }
    }
}

