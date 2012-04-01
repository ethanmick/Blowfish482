///
// BlockCipher.h
///

public class BlockCipher {

	///
	/// Returns this block cipher's block size in bytes
	///
	/// @return  Block Size
	///
	public virtual int blockSize();

	/// 
	/// Returns this block cipher's key size in bytes
	///
	/// @return  Key Size
	///
	public virtual int keySize();

	///
	/// Set the key for this block cipher.  key must be an array
	/// of unsigned characters whose length is equal to keySize()
	///
	/// @param  key Key
	///
	public virtual void setKey(unsigned char* key);

	///
	/// Encrypt the given plaintext.  text must be an array of 
	/// unsigned characters whose length is equal to blockSize().
	/// On input, text contains the plaintext block.  The plaintext
	/// block is encrypted using the key specified in the most recent
	/// call to setKey().  On output, text contains the ciphertext block
	/// 
	/// @param  text Plaintext (on input), ciphertext (on output)
	///
	public virtual void encrypt(unsigned char* text);

};
