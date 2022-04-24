#include "softi2c.h"
#include "gpio.h"
#include "delay.h"
#include "BitByteNumber.h"


uint8_t SDA_PIN;
uint8_t SCL_PIN;

/***************************************************************************************************
                 void SoftI2C_Init(uint8_t sda_pin,uint8_t scl_pin)
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to initialize the I2C module.
***************************************************************************************************/
void SoftI2C_Init(uint8_t sda_pin,uint8_t scl_pin) {
	SDA_PIN = sda_pin;
	SCL_PIN = scl_pin;
	pinMode( SDA_PIN, PullUp, OUTPUT );
	pinMode( SCL_PIN, PullUp, OUTPUT );
}
/***************************************************************************************************
                         void SoftI2C_Start(void)
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate I2C Start Condition.
                 Start Condition: SDA goes low when SCL is High.

                               ____________
                SCL:          |            |
                      ________|            |______
                           _________
                SDA:                |
                                    |____________

***************************************************************************************************/
void SoftI2C_Start(void) {
    digitalWrite( SCL_PIN, LOW ); // Pull SCL low
    digitalWrite( SDA_PIN, HIGH ); // Pull SDA High
    delayUs(1);
    digitalWrite( SCL_PIN, HIGH ); //Pull SCL high
    delayUs(1);
    digitalWrite( SDA_PIN, LOW ); //Now Pull SDA LOW, to generate the Start Condition
    delayUs(1);
    digitalWrite( SCL_PIN, LOW ); //Finally Clear the SCL to complete the cycle
}
/***************************************************************************************************
                         void SoftI2C_Stop(void)
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate I2C Stop Condition.
                 Stop Condition: SDA goes High when SCL is High.

                               ____________
                SCL:          |            |
                      ________|            |______
                                 _________________
                SDA:            |
                      __________|

***************************************************************************************************/
void SoftI2C_Stop(void) {
    digitalWrite( SCL_PIN, LOW ); // Pull SCL low
    delayUs(1);
    digitalWrite( SDA_PIN, LOW ); // Pull SDA  low
    delayUs(1);
    digitalWrite( SCL_PIN, HIGH ); // Pull SCL High
    delayUs(1);
    digitalWrite( SDA_PIN, HIGH ); // Now Pull SDA High, to generate the Stop Condition
}
/***************************************************************************************************
                         void SoftI2C_Write(uint8_t v_i2cData_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t-->8bit data to be sent.
 * Return value  : none

 * description  :This function is used to send a byte on SDA line using I2C protocol
                 8bit data is sent bit-by-bit on each clock cycle.
                 MSB(bit) is sent first and LSB(bit) is sent at last.
                 Data is sent when SCL is low.

         ___     ___     ___     ___     ___     ___     ___     ___     ___     ___
 SCL:   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
      __|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___

 SDA:    D8       D7     D6      D5      D4       D3      D2      D1      D0     ACK


***************************************************************************************************/
void SoftI2C_Write(uint8_t v_i2cData_u8) {
	uint8_t i;

	for(i=0;i<8;i++) // loop 8 times to send 1-byte of data
	{
		digitalWrite( SDA_PIN, util_GetBitStatus(v_i2cData_u8,7) ); // Send Bit by Bit on SDA line starting from MSB
		softI2c_Clock(); // Generate Clock at SCL
		v_i2cData_u8 = v_i2cData_u8<<1;// Bring the next bit to be transmitted to MSB position
	}
                             
	softI2c_Clock();
}
/***************************************************************************************************
                         uint8_t SoftI2C_Read(uint8_t v_ackOption_u8)
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : uint8_t(received byte)

 * description :This fun is used to receive a byte on SDA line using I2C protocol.
               8bit data is received bit-by-bit each clock and finally packed into Byte.
               MSB(bit) is received first and LSB(bit) is received at last.


         ___     ___     ___     ___     ___     ___     ___     ___     ___     ___
SCL:    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
      __|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |__

 SDA:    D8       D7     D6      D5       D4     D3       D2      D1     D0      ACK


v_ackOption_u8 : 	
0 : Send ACK
1 : Dont Send ACK
2 : Noding
***************************************************************************************************/
uint8_t SoftI2C_Read(uint8_t v_ackOption_u8) {
	uint8_t i, v_i2cData_u8=0x00;

	pinMode( SDA_PIN, PullUp, INPUT ); // Make SDA as I/P
	
	for(i=0;i<8;i++) { // loop 8times to read 1-byte of data
		delayUs(1);
		digitalWrite( SCL_PIN, HIGH ); // Pull SCL High
		delayUs(1);

		v_i2cData_u8 = v_i2cData_u8<<1; //v_i2cData_u8 is Shifted each time and
		v_i2cData_u8 = v_i2cData_u8 | digitalRead(SDA_PIN); //ORed with the received bit to pack into byte

		digitalWrite( SCL_PIN, LOW ); // Clear SCL to complete the Clock
	}

	pinMode( SDA_PIN, PullUp, OUTPUT ); // Make SDA back as O/P
    
	     if(v_ackOption_u8 == 1) softI2c_Ack(); // Send the Ack/NoAck depending on the user option
	else if(v_ackOption_u8 == 0) softI2c_NoAck();
	else if(v_ackOption_u8 == 2){};
    
	return v_i2cData_u8;           // Finally return the received Byte*
}                              


/***************************************************************************************************
                         static void softI2c_Clock()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate a clock pulse on SCL line.
***************************************************************************************************/
void softI2c_Clock(void) {
    delayUs(1);
    digitalWrite( SCL_PIN, HIGH ); // Wait for Some time and Pull the SCL line High
    delayUs(1); // Wait for Some time
    digitalWrite( SCL_PIN, LOW ); // Pull back the SCL line low to Generate a clock pulse
}
/***************************************************************************************************
                         static void softI2c_Ack()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate the Positive ACK
                 pulse on SDA after receiving a byte.
***************************************************************************************************/
void softI2c_Ack(void) {
    digitalWrite( SDA_PIN, LOW ); //Pull SDA low to indicate Positive ACK
    softI2c_Clock(); //Generate the Clock
    digitalWrite( SDA_PIN, HIGH ); // Pull SDA back to High(IDLE state)
}
/***************************************************************************************************
                        static void softI2c_NoAck()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to generate the Negative/NO ACK
                 pulse on SDA after receiving all bytes.
***************************************************************************************************/
void softI2c_NoAck(void) {
    digitalWrite( SDA_PIN, HIGH ); //Pull SDA high to indicate Negative/NO ACK
    softI2c_Clock(); // Generate the Clock  
    digitalWrite( SCL_PIN, HIGH ); // Pull SDA back to High(IDLE state)
}
