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

    if (argc <= 4) {
        cout << "usage: Crypter <input-file> <output-file> <key>" << endl;
        return 0;
    }

    /*string str(argv[1]);
    istringstream is(str);
    uint32_t numIter = 0;
    is >> numIter;*/

    uint8_t* key = new uint8_t[ b.keySize() ];
    
    for( unsigned int i = 0; i < b.keySize(); i++ ){
        char* p;
        key[ i ] = (uint8_t)strtol( argv[ 3 + i ], &p, 16);
        if (*p != 0) {
            cout << "ADJUDICATE!" << endl;
        }
    }
    
    print_uint8_hex(key, b.keySize(), "Key: ");
    b.setKey( key );

    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w+");

    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    rewind(input);

    uint8_t* text;
    time_t start = time(NULL) * 1000;
    for (int i = 0; i < size; i+= b.blockSize()) {
        text = new uint8_t[ b.blockSize() ];

        fseek(input, i, SEEK_SET);
        size_t readin = fread(text, b.blockSize(), 1, input); 

        long s = ftell(input);

        size_t delta = b.blockSize() - readin; 
        if (delta != 0) {
            for (unsigned int j = readin; j < b.blockSize(); j++) {
                text[j] = 0x00;
            }
        }
    
        b.encrypt( text );

        fseek(output, i, SEEK_SET);
        fwrite(text, b.blockSize(), 1, output);

        delete[] text;
    }

    fclose(input);
    fclose(output);
    time_t end = time(NULL) * 1000;

    cout << "Running Time: " << (end - start) << " msec" << endl;
    
}
