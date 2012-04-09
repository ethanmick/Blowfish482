#include "Blowfish.h"
#include <iostream>
#include <cmath>

using namespace std;

int main( int argc, char* argv[] ){
    Blowfish b;
    unsigned char* a = new unsigned char[10];
    b.setKey(a);
}

Blowfish::Blowfish() {
    hexStart = 0;
}

int Blowfish::blockSize(){
    return 0;
}

int Blowfish::keySize(){
    return 0;
}

void Blowfish::setKey(unsigned char* key){
    unsigned int* pArray = new unsigned int[18];
    unsigned int s1 = 0;
    unsigned int s2 = 0;
    unsigned int s3 = 0;
    unsigned int s4 = 0;

    for (int i = 0; i < 18; i++) {
        pArray[i] = computeHexPi();
    }

}

void Blowfish::encrypt(unsigned char* text){
    
    
    
    for( int i = 1; i <=16; i++ ){
        
        
        
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

