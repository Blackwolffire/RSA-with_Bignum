/** RSA.h
 * by Blackwolffire
 * 07/16/2015 | 07/46/2015
 * Declaration of RSA class
 */

#ifndef RSA_H
#define RSA_H

#include "lib\Bignum.h"

class RSA_System{

    public:

        RSA_System();
        //~RSA_System();

        static Bignum getLeastFactor(Bignum nb); /// mettre en private
        static bool isPrime(const Bignum& nb); /// mettre en private
        static Bignum getPrime(const unsigned int& nb); /// mettre en private
        static Bignum getNextPrime(Bignum nb); /// mettre en private

    private:

        Bignum n;
        Bignum p;
        Bignum e;
};

#endif
