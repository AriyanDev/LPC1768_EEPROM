#ifndef _BitByteNumber_H
#define _BitByteNumber_H


#include <LPC17xx.h>


/********************************************************************************************/
#define  util_GetBitMask(bit)          ((uint32_t)1<<(bit))
#define  _BitSet(x,bit)            ((x) |=  util_GetBitMask(bit))
#define  _BitClear(x,bit)          ((x) &= ~util_GetBitMask(bit))
#define  util_BitToggle(x,bit)         ((x) ^=  util_GetBitMask(bit))
#define  util_UpdateBit(x,bit,val)     ((val)? util_BitSet(x,bit): util_BitClear(x,bit))
/////////////
#define  util_GetBitStatus(x,bit)      (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitSet(x,bit)          (((x)&(util_GetBitMask(bit)))!=0u)
#define  util_IsBitCleared(x,bit)      (((x)&(util_GetBitMask(bit)))==0u)
/////////////
#define  util_AreAllBitsSet(x,BitMask) (((x)&(BitMask))==BitMask)
#define  util_AreAnyBitsSet(x,BitMask) (((x)&(BitMask))!=0x00u)
/********************************************************************************************/
#define util_ExtractNibble0to4(x)    (uint8_t) ((x) & 0x0Fu)
#define util_ExtractNibble4to8(x)    (uint8_t) (((x)>>4)  & 0x0Fu)
#define util_ExtractNibble8to12(x)   (uint8_t) (((x)>>8)  & 0x0Fu)
#define util_ExtractNibble12to16(x)  (uint8_t) (((x)>>12) & 0x0Fu)
/********************************************************************************************/
#define util_ExtractByte0to8(x)    (uint8_t) ((x) & 0xFFu)
#define util_ExtractByte8to16(x)   (uint8_t) (((x)>>8) & 0xFFu)
#define util_ExtractByte16to28(x)  (uint8_t) (((x)>>16) & 0xFFu)
#define util_ExtractByte28to32(x)  (uint8_t) (((x)>>28) & 0xFFu)
/********************************************************************************************/

void ChangeBit( uint8_t *Data, uint8_t Update, uint8_t StartWritingBitPos, uint8_t EndWritingBitPos  );

void reverse( uint8_t *str, int len, uint8_t Start );

uint8_t itoa( int32_t Number_32, uint8_t *str );
int32_t atoi( uint8_t *str );

void ftoa(float n, uint8_t *res, int afterpoint);
double atof( uint8_t* num );


#endif
