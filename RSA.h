/** RSA.h
 * by Blackwolffire
 * 07/16/2015 | 08/30/2015
 * Declaration of RSA class
 */

#ifndef RSA_H
#define RSA_H

#include <iostream>
#include "../Bignum/Bignum.h" // J'ai mis ce projet sur GitHub aussi

class RSA_System{

    public:

        enum{
            SMALL = 1009,
            NORMAL = 1000003,
            HUGE = 1000000007    //pour du vrai cryptage RSA, HUGE c'est ridicule
        };

        RSA_System(unsigned long long int keySize = SMALL);
        RSA_System(unsigned long long int keySize, std::string str);
        //~RSA_System();

        void RSA_Init(std::string str, unsigned long long int keySize = SMALL);
        void crypt_string(std::string destination, std::string data);
        void crypt_file(std::string destination, std::string dataFile);
        void decrypt_string(std::string destination, std::string data);
        void decrypt_file(std::string destination, std::string dataFile);

        static Bignum getLeastFactor(Bignum nb);
        static bool isPrime(const Bignum& nb);
        static Bignum getPrime(const unsigned int& nb);
        static Bignum getNextPrime(Bignum nb);
        static std::string getNumberStr(std::string str);
        static std::string getCaracStrNb(unsigned char carac);
        static std::vector<Bignum> Extended_Euclidean_Algorithm(const Bignum& a, const Bignum& b);
        static bool fileExist(const std::string& name);

    private:

        Bignum getHashKey(std::string str);
        std::vector<Bignum> getPrimeNumber(std::string str);

        void crypt_byte(char data, Bignum& result);
        char decrypt_Bignum(Bignum data);

        bool A_IsInit;
        unsigned long long int A_KeySize;
        Bignum n;
        Bignum e;
        Bignum d;

        ///\public key (n, e)   (c^e)%n
        ///\private key (d, n)  (c^d)%n
};

#endif
