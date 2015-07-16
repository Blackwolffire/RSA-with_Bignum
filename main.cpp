#include <iostream>
#include "RSA.h"

using namespace std;

int main()
{
    Bignum prout("9007199254740881");

    //display(prout);
    cout << RSA_System::getPrime(1000) << '\n';

    return 0;
}
