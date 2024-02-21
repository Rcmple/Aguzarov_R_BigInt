#include <iostream>
#include "BigInt/BigInt.h"
#include <chrono>
using namespace std;
unsigned BigInt :: accuracy;
void get_PI() {
    BigInt Pi(0);
    BigInt hex(1);
    for(int k = 0; k < BigInt::accuracy; k++) {
        BigInt sec(BigInt(4) / BigInt(8 * k + 1));
        BigInt third(BigInt(2) / BigInt(8 * k + 4));
        BigInt fourth(BigInt(1) / BigInt(8 * k + 5));
        BigInt fifth(BigInt(1) / BigInt(8 * k + 6));
        Pi += (sec - third - fourth - fifth) / hex;
        hex *= BigInt(16);
    }
    cout << Pi << '\n';
}
int main() {
    cout << "This programm calculates the value of Pi to the number of decimal places, enter this number :";
    unsigned n;
    cin >> n;
    auto start_time = std::chrono::high_resolution_clock::now();
    BigInt::accuracy = n;
    get_PI();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Time for calculating: " << duration.count() << std::endl;
    return 0;
}