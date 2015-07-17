#include <iostream>
#include "RSA.h"

using namespace std;

int main()
{
    Bignum prout(0);

    //cout << RSA_System::isPrime(prout);

    //display(prout);
    for(; prout < 1000000; prout = RSA_System::getNextPrime(prout))
        cout << prout << ' ';

    return 0;
}
