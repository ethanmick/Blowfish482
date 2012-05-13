#include "Blowfish.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

// Prints a uint8_t array to stdout as a hex string, endline is printed at the end
void print_uint8_hex(uint8_t* buffer, uint32_t size, const char* label) {
    printf("%s: ", label);
    for ( unsigned int i = 0; i < size; i++ ) {
        printf("%.2X ", buffer[ i ]);
        //cout << (uint32_t) buffer[ i ] << " ";
    }
    printf("\n");
}

int main( int argc, char* argv[] ){
    Blowfish b;

    if (argc != 2) {
        cout << "usage: Profile <num-iterations>" << endl;
        return 0;
    }

    string str(argv[1]);
    istringstream is(str);
    uint32_t numIter = 0;
    is >> numIter;

    uint8_t* key = new uint8_t[ b.keySize() ];
    
    for( unsigned int i = 0; i < b.keySize(); i++ ){
        key[ i ] = 0x00;
    }
    
    print_uint8_hex(key, b.keySize(), "Key: ");
    b.setKey( key );


    uint8_t* text;// = new uint8_t[ b.blockSize() ];
    time_t start = time(NULL) * 1000;
    for (unsigned int i = 0; i < numIter; i++) {
        text = new uint8_t[ b.blockSize() ];
    
        for( unsigned int i = 0; i < b.blockSize(); i++ ){
            text[ i ] = 0x00;
        }

        b.encrypt( text );
        delete[] text;
    }
    time_t end = time(NULL) * 1000;

    cout << "Running Time: " << (end - start) << " msec" << endl;
    //print_uint8_hex(text, b.blockSize(), "Plaintext");
    //print_uint8_hex(text, b.blockSize(), "Ciphertext");
    
}
