#include "eeprom.h"
#include "softi2c.h"
#include "delay.h"
#include "BitByteNumber.h"

uint8_t  EepromType_U8;
uint16_t EepromPageNumber_U16, EepromPageSize_U16;
uint32_t EepromByteNumber_U32;

/****************************************************************************************************/
uint8_t EEPROM_SelectAddress( uint32_t ByteAddress_U32, uint8_t IcAddress_U8 );
/****************************************************************************************************/
/****************************************************************************************************/
void DelayEeprom() {
	if( EepromType_U8 > AT24C64 ) delayMs(10);
	else 													delayMs(5);
}
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
/*
*/
void EEPROM_Init(uint8_t eepromType_u8, uint8_t sda_pin, uint8_t scl_pin) {
	SoftI2C_Init( sda_pin, scl_pin );
	EepromType_U8 = eepromType_u8;

	switch( EepromType_U8 ) {
		case AT24C01 		: EepromPageNumber_U16 = AT24C01_PAGE_Number;		EepromPageSize_U16 = AT24C01_PAGE_Size;		break;
		case AT24C02 		: EepromPageNumber_U16 = AT24C02_PAGE_Number;		EepromPageSize_U16 = AT24C02_PAGE_Size;		break;
		case AT24C04		:	EepromPageNumber_U16 = AT24C04_PAGE_Number;		EepromPageSize_U16 = AT24C04_PAGE_Size;		break;
		case AT24C08 		: EepromPageNumber_U16 = AT24C08_PAGE_Number;		EepromPageSize_U16 = AT24C08_PAGE_Size;		break;
		case AT24C16 		: EepromPageNumber_U16 = AT24C16_PAGE_Number;		EepromPageSize_U16 = AT24C16_PAGE_Size;		break;
		case AT24C32 		: EepromPageNumber_U16 = AT24C32_PAGE_Number;		EepromPageSize_U16 = AT24C32_PAGE_Size;		break;
		case AT24C64 		: EepromPageNumber_U16 = AT24C64_PAGE_Number;		EepromPageSize_U16 = AT24C64_PAGE_Size;		break;
		case AT24C128 	: EepromPageNumber_U16 = AT24C128_PAGE_Number;	EepromPageSize_U16 = AT24C128_PAGE_Size;	break;
		case AT24C256 	: EepromPageNumber_U16 = AT24C256_PAGE_Number;	EepromPageSize_U16 = AT24C256_PAGE_Size;	break;
		case AT24C512		: EepromPageNumber_U16 = AT24C512_PAGE_Number;	EepromPageSize_U16 = AT24C512_PAGE_Size;	break;
		case AT24C1024	: EepromPageNumber_U16 = AT24C1024_PAGE_Number;	EepromPageSize_U16 = AT24C1024_PAGE_Size;	break;
	}
}


/****************************************************************************************************/
/*
Select Address for Read And Write

return 0 : IcAddress Range InCorrect
IcAddress AT24C01 	: 0-7
IcAddress AT24C02 	: 0-7
IcAddress AT24C04 	: 0-3
IcAddress AT24C08 	: 0-1
IcAddress AT24C16 	: 0
IcAddress AT24C32 	: 0-7
IcAddress AT24C64 	: 0-7
IcAddress AT24C128 	: 0-3
IcAddress AT24C256 	: 0-3
IcAddress AT24C512 	: 0-3
IcAddress AT24C1024 : 0-1
*/
uint8_t EEPROM_SelectAddress( uint32_t ByteAddress_U32, uint8_t IcAddress_U8 ) {

	uint8_t WordAddress_HighByte_U8 = (ByteAddress_U32>>8) & 0xff, WordAddress_LowByte_U8 = ByteAddress_U32 & 0xff;
	uint8_t DeviceAddress_U8 = EepromWriteMode;

	switch( EepromType_U8 )
	{
		case AT24C01 		: if(IcAddress_U8 > 7)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<1) 															 	 	, 1, 3 	);	break;
		case AT24C02 		: if(IcAddress_U8 > 7)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<1) 																 	, 1, 3 	);	break;
		case AT24C04		:	if(IcAddress_U8 > 3)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<2) | (((ByteAddress_U32>>8)&0x1)<<1) , 1, 3	);	break;
		case AT24C08 		: if(IcAddress_U8 > 1)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<3) | (((ByteAddress_U32>>8)&0x3)<<1) , 1, 3	);	break;
		case AT24C16 		: if(IcAddress_U8 > 0)return 0;	ChangeBit( &DeviceAddress_U8,                  	  (((ByteAddress_U32>>8)&0x7)<<1) , 1, 3	);	break;
		case AT24C32 		: if(IcAddress_U8 > 7)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<1) 															 	 	, 1, 3	);	break;
		case AT24C64 		: if(IcAddress_U8 > 7)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<1) 															   	, 1, 3	);	break;
		case AT24C128 	: if(IcAddress_U8 > 3)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<1) 															 	 	, 1, 2	);	break;
		case AT24C256 	: if(IcAddress_U8 > 3)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<1) 															 	 	, 1, 2	);	break;
		case AT24C512		: if(IcAddress_U8 > 3)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<1) 															 	 	, 1, 2	);	break;
		case AT24C1024	: if(IcAddress_U8 > 1)return 0;	ChangeBit( &DeviceAddress_U8, (IcAddress_U8<<2) | ((ByteAddress_U32>>16)&0x1) 	 	, 1, 2	);	break;
	}

	SoftI2C_Start();

	SoftI2C_Write(DeviceAddress_U8);
	if( EepromType_U8 > AT24C16) SoftI2C_Write(WordAddress_HighByte_U8); 	
	SoftI2C_Write(WordAddress_LowByte_U8);
	
	return DeviceAddress_U8;
}
/****************************************************************************************************/
/*
return 1 : Success
*/
void EEPROM_WriteByte( uint32_t ByteAddress_U32, uint8_t Data, uint8_t IcAddress_U8 ) {

	EEPROM_SelectAddress( ByteAddress_U32, IcAddress_U8 );

	SoftI2C_Write(Data);

	SoftI2C_Stop();

	DelayEeprom();
}          
uint8_t EEPROM_ReadByte( uint32_t ByteAddress_U32, uint8_t IcAddress_U8 ) {

	uint8_t DeviceAddress_U8;
	uint8_t DataRead = 0x00;

	// Set Address
	DeviceAddress_U8 = EEPROM_SelectAddress( ByteAddress_U32, IcAddress_U8 );

	// Read Curent Address
	SoftI2C_Start();
	SoftI2C_Write( DeviceAddress_U8 | 0x1 );
	DataRead = SoftI2C_Read(0); // Dont Sned ACK
	SoftI2C_Stop();

	DelayEeprom();

	return DataRead;
}
/****************************************************************************************************/
void EEPROM_WriteString( uint32_t ByteAddress_U32, uint8_t *DataWrite,	uint8_t IcAddress_U8 ) {
	do {
		EEPROM_WriteByte( ByteAddress_U32, *DataWrite, IcAddress_U8 );	// Write a byte from RAM to EEPROM
		DataWrite++;                                										// Increment the RAM Address
		ByteAddress_U32++;                                							// Increment the Eeprom Address
	} while( *DataWrite != '\0' );

	EEPROM_WriteByte( ByteAddress_U32, '\0', IcAddress_U8 );
}
void EEPROM_ReadString ( uint32_t ByteAddress_U32, uint8_t *DataSave, 	uint8_t IcAddress_U8 ) {
	do {
		*DataSave = EEPROM_ReadByte( ByteAddress_U32, IcAddress_U8 );	// Read a byte from EEPROM to RAM
		DataSave++;					// Increment the RAM Address
		ByteAddress_U32++;	// Increment the Eeprom Address
	} while( *(DataSave-1) != '\0' );
}
/****************************************************************************************************/
void		EEPROM_WriteNumber( uint32_t ByteAddress_U32, int32_t Number_32, uint8_t Base, uint8_t IcAddress_U8 ) {
  uint8_t Data[10];
	itoa( Number_32, Data);
	EEPROM_WriteString( ByteAddress_U32, Data, IcAddress_U8 );
}
int32_t EEPROM_ReadNumber ( uint32_t ByteAddress_U32,                    uint8_t Base, uint8_t IcAddress_U8 ) {
	uint8_t Data[10];
	EEPROM_ReadString( ByteAddress_U32, Data, IcAddress_U8);
	return atoi(Data);
}
/****************************************************************************************************/
void	EEPROM_WriteFloat( uint32_t ByteAddress_U32, float Number_F, uint8_t FloatDigit,	uint8_t IcAddress_U8 ) {
	uint8_t Data[20];
	if( Number_F < 0.0 ) {
		EEPROM_WriteByte( ByteAddress_U32++, '-', IcAddress_U8 );
		Number_F = -Number_F;
	}
	ftoa( Number_F, Data, FloatDigit );
	EEPROM_WriteString( ByteAddress_U32, Data, IcAddress_U8 );
}
float	EEPROM_ReadFloat ( uint32_t ByteAddress_U32,                                   		uint8_t IcAddress_U8 ) {
	uint8_t Data[10];
	EEPROM_ReadString( ByteAddress_U32, Data, IcAddress_U8 );
	return atof( Data );
}
/****************************************************************************************************/
void EEPROM_WriteStringPage( uint32_t ByteAddress_U32, uint8_t *Data, uint8_t IcAddress_U8 ) {

	uint32_t i=0;

	UP_EEPROM_WriteStringPage:
	EEPROM_SelectAddress( ByteAddress_U32, IcAddress_U8 );

	do {
		SoftI2C_Write( Data[i++] );
		ByteAddress_U32++;
		if( ((ByteAddress_U32-1) % EepromPageSize_U16) == (EepromPageSize_U16-1) ) { 
			SoftI2C_Stop();

			DelayEeprom();

			goto UP_EEPROM_WriteStringPage;
		}
	} while( Data[i-1] != '\0' );

	SoftI2C_Stop();

	DelayEeprom();
}

void EEPROM_ReadStringPage( uint32_t ByteAddress_U32, uint8_t *DataSave, uint8_t IcAddress_U8 ) {

	uint8_t DeviceAddress_U8;


	// Set Address
	DeviceAddress_U8 = EEPROM_SelectAddress( ByteAddress_U32, IcAddress_U8 );

	// Read Curent Address Until '\0'
	SoftI2C_Start();
	SoftI2C_Write( DeviceAddress_U8 | 0x1 );
	do {
		*DataSave = SoftI2C_Read(2); // ? ACK
		if( *DataSave == '\0' ) { softI2c_NoAck(); goto Down_EEPROM_ReadStringPage; }
		else 										{ softI2c_Ack();																		}
		DataSave++;
	} while(1);
	Down_EEPROM_ReadStringPage:
	SoftI2C_Stop();
	

	DelayEeprom();
}

/****************************************************************************************************/
void EEPROM_Erase( uint8_t IcAddress_U8 ) {
	uint32_t ByteAddress_U32 = 0;

	UP_EEPROM_WriteStringPage:
	EEPROM_SelectAddress( ByteAddress_U32, IcAddress_U8 );

	do {
		SoftI2C_Write( '\0' );
		ByteAddress_U32++;
		if( ((ByteAddress_U32-1) % EepromPageSize_U16) == (EepromPageSize_U16-1) ) { 
			SoftI2C_Stop();

			DelayEeprom();

			goto UP_EEPROM_WriteStringPage;
		}
	} while( ByteAddress_U32 < EepromByteNumber_U32 );

	SoftI2C_Stop();

	DelayEeprom();
}
