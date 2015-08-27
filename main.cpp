#include "RSA.h"

using namespace std;

int main()
{
    string str;
    RSA_System myrs;

    Bignum p(9694);

    cin >> str;
    myrs.RSA_Init(str);
cin >> str;
    myrs.crypt_string("link.txt", str);

cin >> str;
    myrs.decrypt_string("linki.txt", str);


    return 0;
}
