#ifndef _SoftI2C_H_
#define _SoftI2C_H_


#include <LPC17xx.h>


void    SoftI2C_Init( uint8_t sda_pin, uint8_t scl_pin );

void    SoftI2C_Start( void );
void    SoftI2C_Stop( void );

void    SoftI2C_Write( uint8_t );
uint8_t SoftI2C_Read( uint8_t );

void softI2c_Ack(void);
void softI2c_NoAck(void);

void softI2c_Clock(void);

#endif
