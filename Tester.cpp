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
