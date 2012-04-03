///
// BlockCipher.h
///

class BlockCipher {

public:
	///
	/// Returns this block cipher's block size in bytes
	///
	/// @return  Block Size
	///
    virtual int blockSize() = 0;

	/// 
	/// Returns this block cipher's key size in bytes
	///
	/// @return  Key Size
	///
	virtual int keySize() = 0;

	///
	/// Set the key for this block cipher.  key must be an array
	/// of unsigned characters whose length is equal to keySize()
	///
	/// @param  key Key
	///
	virtual void setKey(unsigned char* key) = 0;

	///
	/// Encrypt the given plaintext.  text must be an array of 
	/// unsigned characters whose length is equal to blockSize().
	/// On input, text contains the plaintext block.  The plaintext
	/// block is encrypted using the key specified in the most recent
	/// call to setKey().  On output, text contains the ciphertext block
	/// 
	/// @param  text Plaintext (on input), ciphertext (on output)
	///
	virtual void encrypt(unsigned char* text) = 0;

};
