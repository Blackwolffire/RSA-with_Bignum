#include "RSA.h"

using namespace std;

int main()
{
    string str;
    RSA_System myrs;

    Bignum p(65);

    cin >> str;
    myrs.RSA_Init(str);
    myrs.crypt_string("link.txt", "prout");
    myrs.decrypt_file("linki.txt", "link.txt");

    return 0;
}
