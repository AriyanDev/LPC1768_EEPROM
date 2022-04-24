#include "BitByteNumber.h"
#include <math.h>


void ChangeBit( uint8_t *Data, uint8_t Update, uint8_t StartWritingBitPos, uint8_t EndWritingBitPos ) {
	uint8_t i;
	for(i=StartWritingBitPos; i<=EndWritingBitPos; i++) {
		if( ((Update>>i) & 0x1) == 1 ) _BitSet  ( *Data, i );
		else													 _BitClear( *Data, i );
	}
}

/* Reverse an Array*/
void reverse( uint8_t *str, int len, uint8_t Start ) {
	int i=Start, j=len-1, temp;
	while( i < j ) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}
/****************************************************************************************************/
uint8_t itoa( int32_t Number_32, uint8_t *str ) {
	uint8_t i = 0;

	if( Number_32 < 0 ) {
		str[i++] = '-';
		Number_32 = -Number_32;
	}

	while (Number_32) {
		str[i++] = (Number_32%10) + '0';
		Number_32 = Number_32/10;
	}

	// If number of digits required is more, then add 0s at the beginning
	//while (i < d) str[i++] = '0';

	if(str[0] == '-')	reverse(str, i, 1);
	else							reverse(str, i, 0);
	str[i] = '\0';

	return i;
}
int32_t atoi( uint8_t *str ) {
	int32_t res = 0;	// Initialize result
	int8_t sign = 1;	// Initialize sign as positive
	uint8_t i = 0;		// Initialize index of first digit

	if(*str == '\0') return 0;

	// If number is negative, then update sign
	if(str[0] == '-') {
		sign = -1;
		i++;	// Also update index of first digit
	}

	// Iterate through all digits of input string and update result
	for(; str[i] != '\0'; ++i) {
		if( !(str[i] >= '0' && str[i] <= '9') ) return 0; // You may add some lines to write error message to error stream
			res = res*10 + str[i] - '0';
	}

	return sign*res; // Return result with sign
}
/****************************************************************************************************/
void ftoa(float n, uint8_t *res, int afterpoint) {
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = itoa(ipart, res);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        itoa((int)fpart, res + i + 1);
    }
}
double atof( uint8_t* num ) {

	double fractionPart = 0, integerPart = 0;
	int sign = 1, divisorForFraction = 1;
	uint8_t inFraction = 0;
	
	if (!num || !*num) return 0; 
	
	// Take care of +/- sign
	if (*num == '-') {
		++num;
		sign = -1;
	}
	else if (*num == '+') {
		++num;
	}
	
	while (*num != '\0') {
		if (*num >= '0' && *num <= '9') {
			if(inFraction) {
				/*See how are we converting a character to integer*/
				fractionPart = fractionPart*10 + (*num - '0');
				divisorForFraction *= 10;
			}
			else {
				integerPart = integerPart*10 + (*num - '0');
			}
		}
		else if (*num == '.') {
			if(inFraction) 	return sign * (integerPart + fractionPart/divisorForFraction);
			else						inFraction = 1;
		}
		else {
			return sign * (integerPart + fractionPart/divisorForFraction);
		}

		++num;
	}

	return sign * (integerPart + fractionPart/divisorForFraction);
}
