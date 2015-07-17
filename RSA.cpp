/** RSA.cpp
 * by Blackwolffire
 * 07/16/2015 | 07/16/2015
 * Defines functions for RSA class.
 */

#include "RSA.h"

RSA_System::RSA_System(){}

Bignum RSA_System::getLeastFactor(Bignum nb)
{
    Bignum maxNb;
    maxNb = nb / 6;

    if (nb == 0 || nb == 1)
        return nb;
    if (nb % 2 == 0){
        nb = 2;
        return nb;
    }
    if (nb % 3 == 0){
        nb = 3;
        return nb;
    }
    if (nb % 5 == 0){
        nb = 5;
        return nb;
    }

    for(Bignum i(7); i < maxNb; i += 30){
        if (nb % i == 0)
            return i;
        if (nb % (i + 4) == 0)
            return i + 4;
        if (nb % (i + 6) == 0)
            return i + 6;
        if (nb % (i + 10) == 0)
            return i + 10;
        if (nb % (i + 12) == 0)
            return i + 12;
        if (nb % (i + 16) == 0)
            return i + 16;
        if (nb % (i + 22) == 0)
            return i + 22;
        if (nb % (i + 24) == 0)
            return i + 24;
    }

    return nb;
}

bool RSA_System::isPrime(const Bignum& nb)
{
    if(nb.getSign()){
        std::cout << "Erreur: Le nombre est negatif.\n";
        return false;
    }
    return nb == getLeastFactor(nb);
}

Bignum RSA_System::getPrime(const unsigned int& nb)
{
    Bignum result(1);

    for(unsigned int i = 0; i < nb; ++i){
        ++result;
        while(!isPrime(result))
            ++result;
    }
    return result;
}

Bignum RSA_System::getNextPrime(Bignum nb)
{
    if(nb % 2 == 0)
        ++nb;
    do{
        nb += 2;
    }while(!isPrime(nb));
    return nb;
}
