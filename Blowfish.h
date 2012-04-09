#include "BlockCipher.h"

class Blowfish : public BlockCipher {
    
public:
    
    Blowfish();

	virtual int blockSize();
    
	virtual int keySize();
    
	virtual void setKey(unsigned char* key);
    
	virtual void encrypt(unsigned char* text);

private:

    /// The starting location for generating the hex values
    int hexStart;

    unsigned int *s1, *s2, *s3, *s4;
    unsigned int pArray[ 18 ];
    
	///
	/// Compute the next 8 hexadecimal digits of Pi
	/// Necessary for the creation of the S-boxes and P-values in the 
	/// Subkey generation	
	///
	/// @return  An unsigned char array consisting 8 hex digits of Pi
	///
	unsigned int computeHexPi();

    /// 
    /// Compute the series expansion for the values of pi
    ///
    /// @param  d The number of pi to compute (starting value)
    /// @param  j The number of the S-Series
    ///
    /// @return  The remainder of the series computation used to get the hex value of pi
    ///
    double series(int d, int j); 

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
    /// @return An unsigned int representing this char array
    unsigned int charArrayToInt( unsigned char* input );
    
    
    ///
    /// Computes the F function for Blowfish
    ///
    /// @param input    The input to apply the F function to
    /// @return The result of the F function
    unsigned int F( unsigned int input );
    
};
