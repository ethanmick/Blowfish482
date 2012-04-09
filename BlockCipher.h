///
// BlockCipher.h
///
#ifndef BLOCK_CIPHER_H
#define BLOCK_CIPHER_H

#include <stdint.h>

class BlockCipher {

public:
	///
	/// Returns this block cipher's block size in bytes
	///
	/// @return  Block Size
	///
    virtual uint32_t blockSize() = 0;

	/// 
	/// Returns this block cipher's key size in bytes
	///
	/// @return  Key Size
	///
	virtual uint32_t keySize() = 0;

	///
	/// Set the key for this block cipher.  key must be an array
	/// of unsigned characters whose length is equal to keySize()
	///
	/// @param  key Key
	///
	virtual void setKey(uint8_t* key) = 0;

	///
	/// Encrypt the given plaintext.  text must be an array of 
	/// unsigned characters whose length is equal to blockSize().
	/// On input, text contains the plaintext block.  The plaintext
	/// block is encrypted using the key specified in the most recent
	/// call to setKey().  On output, text contains the ciphertext block
	/// 
	/// @param  text Plaintext (on input), ciphertext (on output)
	///
	virtual void encrypt(uint8_t* text) = 0;

};
#endif

