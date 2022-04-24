#ifndef _EEPROM_H
#define _EEPROM_H


#include <LPC17xx.h>


#define AT24C01  	1		// 1024  	bits = 128		Bytes = 16 	Page
#define AT24C02  	2		// 2048  	bits = 256		Bytes = 32 	Page
#define AT24C04  	3		// 4096  	bits = 512		Bytes = 32 	Page
#define AT24C08  	4		// 8192  	bits = 1024  	Bytes = 64 	Page
#define AT24C16  	5  	// 16384  bits = 2048  	Bytes = 128	Page
#define AT24C32  	6  	// 32768	bits = 4096  	Bytes = 128	Page
#define AT24C64  	7  	// 65536  bits = 8192  	Bytes = 256	Page
#define AT24C128 	8 	// 128K   bits = 16384 	Bytes = 256	Page
#define AT24C256 	9		// 256K   bits = 32768 	Bytes = 512	Page
#define AT24C512 	10	// 512K   bits = 65536 	Bytes = 512 Page
#define AT24C1024 11	// 512K   bits = 65536 	Bytes = 512 Page

#define AT24C01_PAGE_Number  	16
#define AT24C02_PAGE_Number		32
#define AT24C04_PAGE_Number		32
#define AT24C08_PAGE_Number  	64
#define AT24C16_PAGE_Number  	128
#define AT24C32_PAGE_Number  	128
#define AT24C64_PAGE_Number  	256
#define AT24C128_PAGE_Number 	256
#define AT24C256_PAGE_Number 	512
#define AT24C512_PAGE_Number 	512
#define AT24C1024_PAGE_Number	512

#define AT24C01_PAGE_Size  		8
#define AT24C02_PAGE_Size			8
#define AT24C04_PAGE_Size			16
#define AT24C08_PAGE_Size  		16
#define AT24C16_PAGE_Size  		16
#define AT24C32_PAGE_Size  		32
#define AT24C64_PAGE_Size  		32
#define AT24C128_PAGE_Size 		64
#define AT24C256_PAGE_Size 		64
#define AT24C512_PAGE_Size 		128
#define AT24C1024_PAGE_Size		256

#define AT24C01_Byte_Number 	128
#define AT24C02_Byte_Number		256
#define AT24C04_Byte_Number		512
#define AT24C08_Byte_Number  	1024
#define AT24C16_Byte_Number  	2048
#define AT24C32_Byte_Number  	4096
#define AT24C64_Byte_Number  	8192
#define AT24C128_Byte_Number 	16384
#define AT24C256_Byte_Number 	32768
#define AT24C512_Byte_Number 	65536
#define AT24C1024_Byte_Number	131072


#define EepromWriteMode 0xA0u
#define EepromReadMode  0xA1u


void EEPROM_Init( uint8_t eepromType_u8, uint8_t sda_pin, uint8_t scl_pin );

void    EEPROM_WriteByte( uint32_t ByteAddress_U32, uint8_t Data, uint8_t IcAddress_U8 );
uint8_t EEPROM_ReadByte ( uint32_t ByteAddress_U32,								uint8_t IcAddress_U8 );

void EEPROM_WriteString( uint32_t ByteAddress_U32, uint8_t *DataWrite,	uint8_t IcAddress_U8 );
void EEPROM_ReadString ( uint32_t ByteAddress_U32, uint8_t *DataSave, 	uint8_t IcAddress_U8 );

void EEPROM_WriteStringPage( uint32_t ByteAddress_U32, uint8_t *Data,     uint8_t IcAddress_U8 );
void EEPROM_ReadStringPage ( uint32_t ByteAddress_U32, uint8_t *DataSave, uint8_t IcAddress_U8 );

void		EEPROM_WriteNumber( uint32_t ByteAddress_U32, int32_t Number_32, uint8_t Base, uint8_t IcAddress_U8 );
int32_t EEPROM_ReadNumber ( uint32_t ByteAddress_U32,                    uint8_t Base, uint8_t IcAddress_U8 );

void	EEPROM_WriteFloat( uint32_t ByteAddress_U32, float Number_F, uint8_t FloatDigit,	uint8_t IcAddress_U8 );
float EEPROM_ReadFloat ( uint32_t ByteAddress_U32,                                   		uint8_t IcAddress_U8 );

void EEPROM_Erase( uint8_t IcAddress_U8 );


#endif
