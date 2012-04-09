#include "Blowfish.h"
#include <iostream>
#include <cmath>

using namespace std;

int main( int argc, char* argv[] ){
    Blowfish b;

    b.setKey( ( unsigned char * ) "0123456789abcdef" );
    
    
    b.encrypt( (unsigned char * ) "01234567" );
}

Blowfish::Blowfish() {
    hexStart = 0;
}

int Blowfish::blockSize(){
    return 8;
}

int Blowfish::keySize(){
    //56 is the maximum, this is variable
    return 16;
}

void Blowfish::setKey(unsigned char* key){
	unsigned int* pArray = new unsigned int[18];
    s1 = new unsigned int[256];
    s2 = new unsigned int[256];
    s3 = new unsigned int[256];
    s4 = new unsigned int[256];

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
    
    int key_size = keySize();
    
    int subkey = 0;
    for (int i=0; i < 4; i++) {
    	subkey <<= 8;
    	subkey |= (int)key[i];
    }

}

void Blowfish::encrypt(unsigned char* text){
        
    cout << "text: " << text << endl;
    unsigned char xLChar[ blockSize()/2 + 1 ];
    unsigned char xRChar[ blockSize()/2 + 1 ];
    memcpy( &xLChar, text, blockSize()/2 );
    xLChar[ blockSize()/2 ] = '\0';
    memcpy( &xRChar, text + blockSize()/2, blockSize()/2 );
    xRChar[ blockSize()/2 ] = '\0';

    unsigned int xL, xR, temp;
    xL = charArrayToInt( xLChar );
    xR = charArrayToInt( xRChar );
    
    for( int i = 1; i <= 16; i++ ){
        xL ^= computeHexPi();
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

unsigned int Blowfish::F( unsigned int input ){
    unsigned char a, b, c, d;
    
    d = (unsigned char) input;
    cout << "d: " << (int) d << endl;
    input >> 8;
    c = (unsigned char) input;
    input >> 8;
    b = (unsigned char) input;
    input >> 8;
    a = (unsigned char) input;
    
    //The s boxes really accept 8 bit input, and produce 32 bit output... i think.
    //We gotta do this...
    //find s1,a s2,b s3,c s4,d

    return ( ( *s1 + *s2 ) ^ *s3 ) + *s4;
    
    
}

unsigned int Blowfish::charArrayToInt( unsigned char* input ){
    if( strlen( ( char * ) input ) == 4 ){
        unsigned int result = 0;
        for( int i = 0; i < 4; i++ ){
            result = result << 8;
            result += input[ i ];

        }
        return result;
    }else{
        return 0;
    }
}

unsigned int Blowfish::computeHexPi() {

    double s1 = series(hexStart, 1);
    double s2 = series(hexStart, 4);
    double s3 = series(hexStart, 5);
    double s4 = series(hexStart, 6);

    double pi = (4.0 * s1) - (2.0 * s2) - s3 - s4;
    pi = pi - (int)pi + 1.0;

    unsigned int pihex= 0;

    for (int i=0; i < 8; i++) {
	pi *= 16;
	unsigned int hVal = floor(pi);
	pihex <<= 4;
	pihex |= hVal;
	pi -= hVal;
    }

    hexStart += 8;

    return pihex;

}

double Blowfish::series(int d, int j) {

    double sum = 0;
    for (int k=0; k < d; k++) {
        sum += (binaryExp(16, (d - k), (8 * k + j))) / (8 * k + j);
        sum = sum - (int)sum;
    }

    for (int k = d; k < d + 100; k++) {
        sum += pow(16.0, d - k) / (8 * k + j);
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

