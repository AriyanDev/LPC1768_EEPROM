#include "delay.h"
#include<lpc17xx.h>

void delayUs(unsigned int count) {
	unsigned int j=0,i=0;
	for(j=0;j<count;j++) for(i=0;i<80;i++); // At 100Mhz, the below loop introduces DELAY of 1 us
}
void delayMs(unsigned int count) {
	unsigned int i;
	for (i=0;i<count;i++) delayUs(1000);
}
void delayS(unsigned int count) {
	unsigned int i;
	for (i=0;i<count;i++) delayMs(1000);	
}

void delayUs_Timer0( unsigned long int delay ) {
	LPC_TIM0->TCR = 0x02;		// reset timer
	LPC_TIM0->PR  = 0x00;		// set prescaler to zero
	LPC_TIM0->MR0 = delay * ((100000000/4)/(1000000-1));
	LPC_TIM0->IR  = 0xff;		// reset all interrrupts
	LPC_TIM0->MCR = 0x04;		// stop timer on match
	LPC_TIM0->TCR = 0x01;		// start timer

	// wait until delay time has elapsed
	while (LPC_TIM0->TCR & 0x01);
}
void delayMs_Timer0( unsigned long int delay ) {

	LPC_TIM0->TCR = 0x02;		// reset timer
	LPC_TIM0->PR  = 0x00;		// set prescaler to zero
	LPC_TIM0->MR0 = delay * ((100000000/4)/(1000-1));
	LPC_TIM0->IR  = 0xff;		// reset all interrrupts
	LPC_TIM0->MCR = 0x04;		// stop timer on match
	LPC_TIM0->TCR = 0x01;		// start timer

	// wait until delay time has elapsed
	while (LPC_TIM0->TCR & 0x01);
}
void delayS_Timer0( unsigned long int delay ) {

	LPC_TIM0->TCR = 0x02;		// reset timer
	LPC_TIM0->PR  = 0x00;		// set prescaler to zero
	LPC_TIM0->MR0 = delay * (100000000/4);
	LPC_TIM0->IR  = 0xff;		// reset all interrrupts
	LPC_TIM0->MCR = 0x04;		// stop timer on match
	LPC_TIM0->TCR = 0x01;		// start timer

	// wait until delay time has elapsed
	while (LPC_TIM0->TCR & 0x01);
}

