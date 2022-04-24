#include <LPC17xx.h>
#include "eeprom.h"
#include "gpio.h"


int main()
{
	uint32_t ByteAddress = 10;
	uint8_t IcAddress = 0;

	uint8_t Data;
	uint8_t DataRead[30];
	uint8_t DataSend[] = "Hello world";

	int32_t Number;
	float Number_F ;

  EEPROM_Init( AT24C128, P2_6/*SDA0*/, P2_7/*SCL0*/ );


  EEPROM_WriteByte( 0, 'G', IcAddress );
  EEPROM_WriteString( 1, DataSend, IcAddress );
  EEPROM_WriteNumber( 40, -123456, 10, IcAddress );
  EEPROM_WriteFloat( 60, -3.148, 3, IcAddress );


  Data = EEPROM_ReadByte( 0, IcAddress );
  EEPROM_ReadString ( 1, DataRead, IcAddress );
  Number = EEPROM_ReadNumber( 40, 10, IcAddress );
  Number_F = EEPROM_ReadFloat( 60, IcAddress );
	while(1)
  {  
  };
}
