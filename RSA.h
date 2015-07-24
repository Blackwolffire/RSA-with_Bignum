/** RSA.h
 * by Blackwolffire
 * 07/16/2015 | 07/46/2015
 * Declaration of RSA class
 */

#ifndef RSA_H
#define RSA_H

#include <iostream>
#include "lib\Bignum.h"

#define MAX_HASH_NB 100019 // Grand nombre premier pour moins de collision pendant génération de clé de hachage

class RSA_System{

    public:

        RSA_System();
        RSA_System(std::string str);
        //~RSA_System();

        void RSA_Init(std::string str);
        Bignum crypt_byte(char data);
        void crypt(std::string destination, std::string data);
        void crypt(std::string destination, std::ifstream dataFile);

        static Bignum getLeastFactor(Bignum nb);
        static bool isPrime(const Bignum& nb);
        static Bignum getPrime(const unsigned int& nb);
        static Bignum getNextPrime(Bignum nb);
        static std::string getNumberStr(std::string str);
        static std::string getCaracStrNb(unsigned char carac);
        static std::vector<Bignum> Extended_Euclidean_Algorithm(const Bignum& a, const Bignum& b);
        static bool fileExist(const std::string& name);

    private:

        static Bignum getHashKey(std::string str);
        static std::vector<Bignum> getPrimeNumber(std::string str);

        bool A_IsInit;
        Bignum n;
        Bignum e;
        Bignum d;

        ///\public key (n, e)
        ///\private key (d, n)
};

#endif
