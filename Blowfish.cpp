#include "Blowfish.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

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
    
/*    for (int i = 0; i < 18; i++) {
        pArray[i] = hexPi.Pi[hexStart++];
    }*/
    
    pArray0 = hexPi.Pi[hexStart++];
    pArray1 = hexPi.Pi[hexStart++];
    pArray2 = hexPi.Pi[hexStart++];
    pArray3 = hexPi.Pi[hexStart++];
    
    pArray4 = hexPi.Pi[hexStart++];
    pArray5 = hexPi.Pi[hexStart++];
    pArray6 = hexPi.Pi[hexStart++];
    pArray7 = hexPi.Pi[hexStart++];

    pArray8 = hexPi.Pi[hexStart++];
    pArray9 = hexPi.Pi[hexStart++];
    pArray10 = hexPi.Pi[hexStart++];
    pArray11 = hexPi.Pi[hexStart++];

    pArray12 = hexPi.Pi[hexStart++];
    pArray13 = hexPi.Pi[hexStart++];
    pArray14 = hexPi.Pi[hexStart++];
    pArray15 = hexPi.Pi[hexStart++];

    pArray16 = hexPi.Pi[hexStart++];
    pArray17 = hexPi.Pi[hexStart++];


    
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
   
/*    for (int pI=0; pI < 18; pI++) {
        
        uint32_t subkey = 0; 

        for (int i=0; i < 4; i++, subkeyCounter++) {
            if (subkeyCounter >= key_size) {
                subkeyCounter = 0;
            }
    	    subkey <<= 8;
            subkey |= (uint32_t)key[subkeyCounter];
        }

    	pArray[pI] ^= subkey;
    }*/ 
    
    uint32_t subkey;
    uint32_t subkeyCounter = 0;
    
    subkey = 0;     
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray0 ^= subkey;

    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray1 ^= subkey;

    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray2 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray3 ^= subkey;
    
    subkey = 0;     
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray4 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray5 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray6 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray7 ^= subkey;

    
    subkey = 0;     
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray8 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray9 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray10 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray11 ^= subkey;
    
    subkey = 0;     
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray12 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray13 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray14 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray15 ^= subkey;
    

    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray16 ^= subkey;
    
    subkey = 0; 
    for (int i=0; i < 4; i++, subkeyCounter++) {
        if (subkeyCounter >= key_size) {
            subkeyCounter = 0;
        }
        subkey <<= 8;
        subkey |= (uint32_t)key[subkeyCounter];
    }
    pArray17 ^= subkey;

    
    
        
    uint8_t* zeros = new uint8_t[ 8 ];
    for( int i = 0; i < 8; i++ ){
        zeros[ i ] = 0;
    }
        
/*    for (int i=0; i < 18; i += 2) {
        encrypt(zeros);
        pArray[i] = pack32BitWord(zeros, 0);
        pArray[i+1] = pack32BitWord(zeros, 4);
    }*/
    
    encrypt(zeros);
    pArray0 = pack32BitWord(zeros, 0);
    pArray1 = pack32BitWord(zeros, 4);

    encrypt(zeros);    
    pArray2 = pack32BitWord(zeros, 0);
    pArray3 = pack32BitWord(zeros, 4);


    encrypt(zeros);
    pArray4 = pack32BitWord(zeros, 0);
    pArray5 = pack32BitWord(zeros, 4);
    
    encrypt(zeros);
    pArray6 = pack32BitWord(zeros, 0);
    pArray7 = pack32BitWord(zeros, 4);

    encrypt(zeros);
    pArray8 = pack32BitWord(zeros, 0);
    pArray9 = pack32BitWord(zeros, 4);

    encrypt(zeros);
    pArray10 = pack32BitWord(zeros, 0);
    pArray11 = pack32BitWord(zeros, 4);

    encrypt(zeros);
    pArray12 = pack32BitWord(zeros, 0);
    pArray13 = pack32BitWord(zeros, 4);

    encrypt(zeros);
    pArray14 = pack32BitWord(zeros, 0);
    pArray15 = pack32BitWord(zeros, 4);

    encrypt(zeros);
    pArray16 = pack32BitWord(zeros, 0);
    pArray17 = pack32BitWord(zeros, 4);


    

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
        
/*    for( int i = 0; i <= 15; i++ ){
        
        xL ^= pArray[ i ];
        xR ^= F( xL );
        
        temp = xL;
        xL = xR;
        xR = temp;
    }*/
    
    xL ^= pArray0;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;

    xL ^= pArray1;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;

    xL ^= pArray2;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;

    xL ^= pArray3;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;

    xL ^= pArray4;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray5;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray6;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray7;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray8;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray9;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray10;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray11;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray12;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray13;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray14;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xL ^= pArray15;
    xR ^= F( xL );    
    temp = xL;
    xL = xR;
    xR = temp;
    
    
    temp = xL;
    xL = xR;
    xR = temp;
    
    xR ^= pArray16;
    xL ^= pArray17;
    
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
