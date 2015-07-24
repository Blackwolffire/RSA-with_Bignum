#include "RSA.h"

using namespace std;

int main()
{
    string str;
    RSA_System myrs;

    Bignum p(7);

    cin >> str;
    myrs.RSA_Init(str);

    myrs.crypt("prout.txt", str);

    return 0;
}
