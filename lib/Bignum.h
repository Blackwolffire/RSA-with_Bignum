/** Bignum.h
 * by Blackwolffire
 * 02/13/2015 | 07/16/2015
 * Declaration of Bignum class
 */

#ifndef BIGNUM_H
#define BIGNUM_H

#include <iostream>
#include <vector>

class Bignum
{

    public:
        Bignum(std::string str);
        Bignum(unsigned long long int base = 0, bool sign = false);
        Bignum(const Bignum& nb);
        //~Bignum();

        void operator=(std::string str);
        void operator=(const unsigned long long int& nb);
        void operator=(const Bignum& nb);
        bool operator==(unsigned long long int nb) const;
        bool operator==(const Bignum& nb) const;
        bool operator!=(unsigned long long int nb) const;
        bool operator!=(const Bignum& nb) const;
        bool operator<(const unsigned long long int& nb) const;
        bool operator<(const Bignum& nb) const;
        bool operator>(const unsigned long long int& nb) const;
        bool operator>(const Bignum& nb) const;
        bool operator<=(const unsigned long long int& nb) const;
        bool operator<=(const Bignum& nb) const;
        bool operator>=(const unsigned long long int& nb) const;
        bool operator>=(const Bignum& nb) const;

        void operator+=(unsigned long long int nb);
        void operator+=(const Bignum& nb);
        void operator-=(unsigned long long int nb);
        void operator-=(const Bignum& nb);
        void operator*=(const unsigned long long int& nb);
        void operator*=(const Bignum nb);
        void operator/=(const unsigned long long int& nb);
        void operator/=(Bignum nb);
        void operator%=(const unsigned long long int& nb);
        void operator%=(const Bignum& nb);
        Bignum& operator++();
        Bignum operator++(int);
        Bignum& operator--();
        Bignum operator--(int);

        std::ostream& display(std::ostream &flux) const;
        std::istream& enter(std::istream &flux);
        void BigPow(unsigned long long int exponent);
        void BigPow(Bignum exponent);
        unsigned long long int getSize() const {return A_Bignum.size();}
        bool getSign() const {return A_IsSigned;}

    private:
        std::vector<unsigned char> A_Bignum;
        bool A_IsSigned;
        std::vector<unsigned char> A_Rest;
};

Bignum operator+(Bignum a, const unsigned long long int& b);
Bignum operator+(Bignum a, const Bignum& b);
Bignum operator-(Bignum a, const unsigned long long int& b);
Bignum operator-(Bignum a, const Bignum& b);
Bignum operator*(Bignum a, const unsigned long long int& b);
Bignum operator*(Bignum a, const Bignum& b);
Bignum operator/(Bignum a, const unsigned long long int& b);
Bignum operator/(Bignum a, const Bignum& b);
Bignum operator%(Bignum a, const unsigned long long int& b);
Bignum operator%(Bignum a, const Bignum& b);

std::ostream& operator<<( std::ostream &flux, Bignum const& nb );
std::istream& operator>>( std::istream &flux, Bignum& nb );
void display(Bignum number);
unsigned long long int pow_int(const unsigned long long int& base, const unsigned int& exponent);

#endif
