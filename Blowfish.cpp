#include "Blowfish.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

// Prints a uint8_t array to stdout as a hex string, endline is printed at the end
void print_uint8_hex(uint8_t* buffer, uint32_t size, const char* label) {
    cout << label << hex;
    for ( unsigned int i = 0; i < size; i++ ) {
        cout << (uint32_t) buffer[ i ] << " ";
    }
    cout << dec << endl;
}

int main( int argc, char* argv[] ){
    Blowfish b;

    if( (unsigned int) argc != b.blockSize() + b.keySize() + 1 ){
        cout << "usage: Blowfish key[ 0th byte ] key[ 1st byte ] " \
                "etc... ptext[ 0th byte ] ptext[ 1st byte ] etc..." << endl;
        exit( 0 );
    }
    
    for( int i = 1; i < argc; i++ ){
        if( strlen( argv[ i ] ) != 2 ){
            cout << "This arg isn't 2 characters long." << endl;
            exit( 0 );
        }
    }
        
    uint8_t* key = new uint8_t[ b.keySize() ];
    
    for( unsigned int i = 0; i < b.keySize(); i++ ){
        char * p;
        key[ i ] = (uint8_t) strtol( argv[ 1 + i ], &p, 16 );
        if( *p != 0 ){
            cout << "Problem parsing string." << endl;
        }
    }
    
    print_uint8_hex(key, b.keySize(), "Key: ");
    b.setKey( key );
    

    uint8_t* text = new uint8_t[ b.blockSize() ];

    
    
    for( unsigned int i = 0; i < b.blockSize(); i++ ){
        char * p;
        text[ i ] = (uint8_t) strtol( argv[ b.keySize() + 1 + i ], &p, 16 );
        if( *p != 0 ){
            cout << "Problem parsing string." << endl;
        }
    }
    print_uint8_hex(text, b.blockSize(), "Plaintext: ");
    b.encrypt( text );
    print_uint8_hex(text, b.blockSize(), "Ciphertext: ");
    
}

Blowfish::Blowfish() {
    hexStart = 0;
}

uint32_t Blowfish::blockSize(){
    return 8;
}

uint32_t Blowfish::keySize(){
    //56 is the maximum, this is variable
    return 8;
}

void Blowfish::setKey(uint8_t* key){
    
    for (int i = 0; i < 18; i++) {
        pArray[i] = hexPi.Pi[hexStart++];
    }
    
    for (int i=0; i < 256; i++) {
    	s1[i] = hexPi.Pi[hexStart++];
    }
    
    for (int i=0; i < 256; i++) {
    	s2[i] = hexPi.Pi[hexStart++];
    }
    
    for (int i=0; i < 256; i++) {
    	s3[i] = hexPi.Pi[hexStart++];
    }
   
    for (int i=0; i < 256; i++) {
    	s4[i] = hexPi.Pi[hexStart++];
    }

    uint32_t key_size = keySize();
   
    uint32_t subkeyCounter = 0; 
    for (int pI=0; pI < 18; pI++) {
        
        uint32_t subkey = 0; 

        for (int i=0; i < 4; i++, subkeyCounter++) {
            if (subkeyCounter >= key_size) {
                subkeyCounter = 0;
            }
    	    subkey <<= 8;
            subkey |= (uint32_t)key[subkeyCounter];
        }

    	pArray[pI] ^= subkey;
    } 
        
    uint8_t* zeros = new uint8_t[ 8 ];
    for( int i = 0; i < 8; i++ ){
        zeros[ i ] = 0;
    }
        
    for (int i=0; i < 18; i += 2) {
        encrypt(zeros);
        pArray[i] = pack32BitWord(zeros, 0);
        pArray[i+1] = pack32BitWord(zeros, 4);
    }

    for (int i=0; i < 256; i += 2) {
        encrypt(zeros);
        s1[i] = pack32BitWord(zeros, 0);
        s1[i+1] = pack32BitWord(zeros, 4);
    } 

    for (int i=0; i < 256; i += 2) {
        encrypt(zeros);
        s2[i] = pack32BitWord(zeros, 0);
        s2[i+1] = pack32BitWord(zeros, 4);
    } 

    for (int i=0; i < 256; i += 2) {
        encrypt(zeros);
        s3[i] = pack32BitWord(zeros, 0);
        s3[i+1] = pack32BitWord(zeros, 4);
    } 

    for (int i=0; i < 256; i += 2) {
        encrypt(zeros);
        s4[i] = pack32BitWord(zeros, 0);
        s4[i+1] = pack32BitWord(zeros, 4);
    } 

}

void Blowfish::encrypt(uint8_t* text){
    
    uint32_t xL, xR, temp;
    xL = pack32BitWord( text, 0 );
    xR = pack32BitWord( text, 4 );
        
    for( int i = 0; i <= 15; i++ ){
        
        xL ^= pArray[ i ];
        xR ^= F( xL );
        
        temp = xL;
        xL = xR;
        xR = temp;
    }
    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xR ^= pArray[ 16 ];
    xL ^= pArray[ 17 ];
    
    //merge into xR and xL into xL
    uint64_t final = 0;
    final |= xL;
    final <<= 32;
    final |= xR;
    //now final is the ciphertext, need to convert to ascii
    
    text[ 0 ] = final >> 56;
    text[ 1 ] = final >> 48;
    text[ 2 ] = final >> 40;
    text[ 3 ] = final >> 32;
    text[ 4 ] = final >> 24;
    text[ 5 ] = final >> 16;
    text[ 6 ] = final >> 8;
    text[ 7 ] = final;
    
}

uint32_t Blowfish::F( uint32_t input ){
    uint8_t a, b, c, d;
        
    d = (uint8_t) input;
    input >>= 8;
    c = (uint8_t) input;
    input >>= 8;
    b = (uint8_t) input;
    input >>= 8;
    a = (uint8_t) input;
    
    return ( ( s1[ a ] + s2[ b ] ) ^ s3[ c ] ) + s4[ d ];
    
}

uint32_t Blowfish::pack32BitWord( uint8_t* input, uint32_t startVal ){
    uint32_t result = 0;
    for( unsigned int i = startVal; i < startVal + 4; i++ ){
        result <<= 8;
        result |= input[ i ];
    }
    return result; 
}
