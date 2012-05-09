#ifndef BLOWFISH_H
#define BLOWFISH_H
#include "BlockCipher.h"
#include "Pi.h"

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
    HexPi hexPi;

    uint32_t s1[256], s2[256], s3[256], s4[256];
    uint32_t pArray[ 18 ];
    
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
