#ifndef BLOWFISH_H
#define BLOWFISH_H
#include "BlockCipher.h"

class Blowfish : public BlockCipher {
    
public:
    
    Blowfish();

	virtual uint32_t blockSize();
    
	virtual uint32_t keySize();
    
	virtual void setKey(uint8_t* key);
    
	virtual void encrypt(uint8_t* text);

private:

    /// The starting location for generating the hex values
    int hexStart;

    uint32_t s1[256], s2[256], s3[256], s4[256];
    uint32_t pArray[ 18 ];
    
	///
	/// Compute the next 8 hexadecimal digits of Pi
	/// Necessary for the creation of the S-boxes and P-values in the 
	/// Subkey generation	
	///
	/// @return  An unsigned char array consisting 8 hex digits of Pi
	///
	uint32_t computeHexPi();

    /// 
    /// Compute the series expansion for the values of pi
    ///
    /// @param  d The number of pi to compute (starting value)
    /// @param  j The number of the S-Series
    ///
    /// @return  The remainder of the series computation used to get the hex value of pi
    ///
    double series(uint32_t d, uint32_t j); 

	///
	/// Compute b^n mod k using binary exponentiation modulo k
	/// Faster way to compute than just using regular exponentiation
	///
	/// @param  b 	The number to compute
	/// @param  n 	The power to compute to
	/// @param  mod The modulus to use
	///
	/// @return  The compute value of b^n mod k
	///
	double binaryExp(int b, int n, double mod);
    
    
    
    ///
    /// Computes an integer based on a given char*
    ///
    /// @param input    The char array to convert
    /// @param startVal Where to start to pack the values
    /// @return An unsigned int representing this char array
    uint32_t pack32BitWord( uint8_t* input, uint32_t startVal );
    
    
    ///
    /// Computes the F function for Blowfish
    ///
    /// @param input    The input to apply the F function to
    /// @return The result of the F function
    uint32_t F( uint32_t input );
    
};
#endif
