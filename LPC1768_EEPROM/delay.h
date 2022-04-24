#ifndef delay_h
#define delay_h

void delayUs(unsigned int count);
void delayMs(unsigned int count);
void delayS(unsigned int count);

void delayUs_Timer0( unsigned long int delay );
void delayMs_Timer0( unsigned long int delay );
void delayS_Timer0( unsigned long int delay );

#endif
