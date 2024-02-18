#include <iostream>
#include "BigInt.h"
using namespace std;

int main() {
    cout << "Input 2 long ints:\n";
    BigInt a, b;
    cin >> a >> b;
    cout << "Sum of 2 long integers: " << a + b;
    return 0;
}