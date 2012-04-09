#include "Blowfish.h"
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int main( int argc, char* argv[] ){
    Blowfish b;

    b.setKey( ( uint8_t * ) "0123456789abcdef" );
    
    
    b.encrypt( (uint8_t * ) "01234567" );
}

Blowfish::Blowfish() {
    hexStart = 0;

}

uint32_t Blowfish::blockSize(){
    return 8;
}

uint32_t Blowfish::keySize(){
    //56 is the maximum, this is variable
    return 16;
}

void Blowfish::setKey(uint8_t* key){
    
    for (int i = 0; i < 18; i++) {
        pArray[i] = computeHexPi();
    }
    
    for (int i=0; i < 256; i++) {
    	s1[i] = computeHexPi();
    }
    
    for (int i=0; i < 256; i++) {
    	s2[i] = computeHexPi();
    }
    
    for (int i=0; i < 256; i++) {
    	s3[i] = computeHexPi();
    }
    
    for (int i=0; i < 256; i++) {
    	s4[i] = computeHexPi();
    }

    uint32_t key_size = keySize();
    
    uint32_t subkey = 0;
    for (int i=0; i < 4; i++) {
    	subkey <<= 8;
    	subkey |= (uint32_t)key[i];
    }

}

void Blowfish::encrypt(uint8_t* text){
        
    cout << "text: " << text << endl;
    uint8_t xLChar[ blockSize()/2 + 1 ];
    uint8_t xRChar[ blockSize()/2 + 1 ];
    memcpy( &xLChar, text, blockSize()/2 );
    xLChar[ blockSize()/2 ] = '\0';
    memcpy( &xRChar, text + blockSize()/2, blockSize()/2 );
    xRChar[ blockSize()/2 ] = '\0';

    uint32_t xL, xR, temp;
    xL = charArrayToInt( xLChar );
    xR = charArrayToInt( xRChar );
    
    for( int i = 1; i <= 16; i++ ){
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
    xL = xL << 16;
    xL += xR;
    
    //now xL is the ciphertext
    
    cout << xL;
    
    
}

uint32_t Blowfish::F( uint32_t input ){
    uint8_t a, b, c, d;
    
    d = (uint8_t) input;
    input >> 8;
    c = (uint8_t) input;
    input >> 8;
    b = (uint8_t) input;
    input >> 8;
    a = (uint8_t) input;
    
    //The s boxes really accept 8 bit input, and produce 32 bit output... i think.
    //We gotta do this...
    //find s1,a s2,b s3,c s4,d

    return ( ( s1[ a ] + s2[ b ] ) ^ s3[ c ] ) + s4[ d ];
    
    
}

uint32_t Blowfish::charArrayToInt( uint8_t* input ){
    if( strlen( ( char * ) input ) == 4 ){
        uint32_t result = 0;
        for( int i = 0; i < 4; i++ ){
            result = result << 8;
            result += input[ i ];

        }
        return result;
    }else{
        return 0;
    }
}

uint32_t Blowfish::computeHexPi() {

    double s1 = series(hexStart, 1);
    double s2 = series(hexStart, 4);
    double s3 = series(hexStart, 5);
    double s4 = series(hexStart, 6);

    double pi = (4.0 * s1) - (2.0 * s2) - s3 - s4;
    pi = pi - (int)pi + 1.0;

    uint32_t pihex= 0;

    for (int i=0; i < 8; i++) {
	pi *= 16;
	uint32_t hVal = floor(pi);
	pihex <<= 4;
	pihex |= hVal;
	pi -= hVal;
    }

    hexStart += 8;

    return pihex;

}

double Blowfish::series(uint32_t d, uint32_t j) {

    double sum = 0;
    for (int k=0; k < d; k++) {
        sum += (binaryExp(16, (d - k), (8 * k + j))) / (8 * k + j);
        sum = sum - (int)sum;
    }

    for (int k = d; k < d + 100; k++) {
        sum += pow(16.0, (double) d - k) / (8 * k + j);
        sum = sum - (int)sum;
    }

    return sum;
}

double Blowfish::binaryExp(int b, int n, double mod) {

    if (mod == 1.0) {
        return 0;
    }
    
    // Largest power of 2 less than n
    double t = pow(2, floor(log2(n)));

    double r = 1;
    while (t >= 1) {
        if (n >= t) {
            r = fmod(b * r, mod);
            n = n - t;
        }
        
        t = t / 2;

        if (t >= 1) {
            r = fmod(r * r, mod);
        }
    }

    return r;
}

