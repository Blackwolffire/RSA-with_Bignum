/** RSA.cpp
 * by Blackwolffire
 * 07/16/2015 | 07/16/2015
 * Defines functions for RSA class.
 */

#include "RSA.h"

RSA_System::RSA_System(){}

bool RSA_System::isPrime(const Bignum& nb)
{
    Bignum maxNb;
    maxNb = nb / 2;

    if(nb % 2 == 0)
        return nb == 2;
    if(nb % 3 == 0)
        return nb == 3;

    if(nb.getSign()){
        std::cout << "Erreur: Le nombre est negatif.\n";
        return false;
    }
    //std::cout << nb / 2 << std::endl;

    for(Bignum i(4); i < maxNb; i += 6)
        if(nb % i == 0)
            return false;
    return true;
}

Bignum RSA_System::getPrime(const unsigned int& nb)
{
    Bignum result(1);

    for(unsigned int i = 0; i < nb; ++i){
        ++result;
        while(!isPrime(result) && result < 1000)
            ++result;
    }
    return result;
}
