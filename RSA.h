/** RSA.h
 * by Blackwolffire
 * 07/16/2015 | 08/27/2015
 * Declaration of RSA class
 */

#ifndef RSA_H
#define RSA_H

#include <iostream>
#include "lib\Bignum.h"

#define MAX_HASH_NB 1000003 // Grand nombre premier pour moins de collision pendant génération de clé de hachage & limite la taille des nombre premier

class RSA_System{

    public:

        RSA_System();
        RSA_System(std::string str);
        //~RSA_System();

        void RSA_Init(std::string str);
        void crypt_string(std::string destination, std::string data);
        void crypt_file(std::string destination, std::string dataFile);
        void decrypt_string(std::string destination, std::string data);

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

        void crypt_byte(char data, Bignum& result);
        char decrypt_Bignum(Bignum data);

        bool A_IsInit;
        Bignum n;
        Bignum e;
        Bignum d;

        ///\public key (n, e)   (c^e)%n
        ///\private key (d, n)  (c^d)%n
};

#endif
