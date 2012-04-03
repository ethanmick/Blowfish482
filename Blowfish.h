#include "BlockCipher.h"

class Blowfish : public BlockCipher {
    
public:
    
	virtual int blockSize();
    
	virtual int keySize();
    
	virtual void setKey(unsigned char* key);
    
	virtual void encrypt(unsigned char* text);
};