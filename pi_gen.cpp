///
/// Generates the header file for that contains
/// the first 8336 hexadecimal digits of Pi
///

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <stdint.h>

using namespace std;

int hexStart;


double binaryExp(int b, int n, double mod) {

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

double series(uint32_t d, uint32_t j) {

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

uint32_t computeHexPi() {

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

int main() {
  
    ofstream outfile("Pi.h");
    
    outfile << "///" << endl;
    outfile << "/// Repesents the necessary 8336 Hexadecminal Digits of Pi" << endl;
    outfile << "///" << endl;
    outfile << endl;
    outfile << "class HexPi {" << endl;
    outfile << "\tpublic:" << endl;
    outfile << "\t\tuint32_t Pi[1042];" << endl;
    outfile << endl;
    outfile << "\t\tHexPi() {" << endl;
    for (int i=0; i < 1042; i++) {
      outfile << "\t\t\tPi[" << i << "] = 0x" << hex << computeHexPi() << dec << ";" << endl;
    }
    outfile << "\t\t};" << endl;
    outfile << "};" << endl;

    outfile.close();
}
