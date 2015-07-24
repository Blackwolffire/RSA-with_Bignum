/** Bignum.cpp
 * by Blackwolffire
 * 02/13/2015 | 07/24/2015
 * Defines functions for Bignum class.
 */

#include "Bignum.h"

Bignum operator+(Bignum a, const Bignum& b)
{
    a += b;
    return a;
}

Bignum operator+(Bignum a, const unsigned long long int& b)
{
    a += b;
    return a;
}

Bignum operator-(Bignum a, const unsigned long long int& b)
{
    a -= b;
    return a;
}

Bignum operator-(Bignum a, const Bignum& b)
{
    a -= b;
    return a;
}

Bignum operator*(Bignum a, const unsigned long long int& b)
{
    a *= b;
    return a;
}

Bignum operator*(Bignum a, const Bignum& b)
{
    a *= b;
    return a;
}

Bignum operator/(Bignum a, const unsigned long long int& b)
{
    a /= b;
    return a;
}

Bignum operator/(Bignum a, const Bignum& b)
{
    a /= b;
    return a;
}

Bignum operator%(Bignum a, const unsigned long long int& b)
{
    a %= b;
    return a;
}

Bignum operator%(Bignum a, const Bignum& b)
{
    a %= b;
    return a;
}

std::ostream& operator<<( std::ostream &flux, Bignum const& nb )
{
    return nb.display(flux);
}

std::istream& operator>>( std::istream &flux, Bignum& nb )
{
    return nb.enter(flux);
}

void display(Bignum number)
{
    std::cout << number.getSize() << '\n';
    number.display(std::cout);
    std::cout << '\n';
}

unsigned long long int pow_int(const unsigned long long int& base, const unsigned int& exponent)
{
    unsigned long long int result = 1;

    for(unsigned int i = 0; i < exponent; ++i)
        result *= base;

    return result;
}

/// BigNum functions /////////////////////////////////////////////////////////////////////////////////

Bignum::Bignum(std::string str)
{
    *this = str;
}

Bignum::Bignum(unsigned long long int base, bool sign) : A_Bignum(0)
{
    A_IsSigned = false;
    *this += base;
    if(base)
        A_IsSigned = sign;
    else
        A_IsSigned = false;
    A_Rest.resize(0, 0);
}

Bignum::Bignum(const Bignum& nb) : A_IsSigned(nb.A_IsSigned)
{
    A_Bignum.resize(nb.A_Bignum.size());
    for(unsigned int i = 0; i < nb.A_Bignum.size(); ++i)
        A_Bignum[i] = nb.A_Bignum[i];
    A_Rest.resize(0, 0);
}

std::ostream& Bignum::display(std::ostream &flux) const
{
    if(A_IsSigned)
        flux << '-';

    if(A_Bignum.size() > 0)
        for(long long int i = A_Bignum.size() - 1; i >= 0; --i)
            flux <<  static_cast<uint16_t>(A_Bignum[i]);
    else
        flux << "NULL";

    return flux;
}

std::istream& Bignum::enter(std::istream &flux)
{
    std::string str;

    flux >> str;
    *this = str;

    return flux;
}

void Bignum::BigPow(unsigned long long int exponent)
{
    Bignum cp(*this);
    *this = 1;

    for(; exponent > 0; --exponent)
        *this *= cp;
}

void Bignum::BigPow(Bignum exponent)
{
    Bignum cp(*this);
    *this = 1;

    for(Bignum i(0); i < exponent; ++i)
        *this *= cp;
}

void Bignum::operator=(std::string str)
{
    unsigned char value;

    if(str[0] == '-'){
        A_IsSigned = true;
        str.erase(str.begin());
    }
    else
        A_IsSigned = false;

    A_Bignum.resize(str.length());

    for(unsigned int i(0); i < str.length(); ++i){
        value  = str[i] - '0';
        if(value < 10)
            A_Bignum[A_Bignum.size() - i - 1] = value;
        else
            A_Bignum[A_Bignum.size() - i - 1] = 0;
    }

    while(!A_Bignum.back())
        A_Bignum.pop_back();
    if(!A_Bignum.size())
        A_IsSigned = false;

    A_Rest.resize(0, 0);
}

void Bignum::operator=(const unsigned long long int& nb)
{
    A_Bignum.resize(0, 0);
    A_IsSigned = false;
    *this += nb;
}

void Bignum::operator=(const Bignum& nb)
{
    A_IsSigned = nb.A_IsSigned;
    A_Bignum.resize(nb.A_Bignum.size());
    for(unsigned int i = 0; i < nb.A_Bignum.size(); ++i)
        A_Bignum[i] = nb.A_Bignum[i];
    A_Rest.resize(0, 0);
}

bool Bignum::operator==(unsigned long long int nb) const
{
    unsigned char i;

    if(A_IsSigned || A_Bignum.size() > 20)
        return false;

    if(!nb && A_Bignum.size() == 1 && !A_Bignum[0])
        return true;

    for(i = 0; nb > 0; ++i, nb /= 10)
        if(i >= A_Bignum.size() || A_Bignum[i] != nb % 10)
            return false;

    if(i != A_Bignum.size())
        return false;
    else
        return true;
}

bool Bignum::operator==(const Bignum& nb) const
{
    if(nb.A_Bignum.size() != A_Bignum.size() || nb.A_IsSigned != A_IsSigned)
        return false;
    for(unsigned long long int i = 0; i < A_Bignum.size(); ++i)
        if(A_Bignum[i] != nb.A_Bignum[i])
            return false;
    return true;
}

bool Bignum::operator!=(unsigned long long int nb) const
{
    return !(*this == nb);
}

bool Bignum::operator!=(const Bignum& nb) const
{
    return !(*this == nb);
}

bool Bignum::operator<(const unsigned long long int& nb) const
{
    if(A_IsSigned)
        return true;

    if(A_Bignum.size() > 20 || (A_Bignum.size() == 20 && A_Bignum.back() > 1))
        return false;

    if(nb / pow_int(10, A_Bignum.size() - 1) > 9)
        return true;
    else if(nb / pow_int(10, A_Bignum.size() - 1) == 0)
        return false;

    for(unsigned long long int i = 1; i <= A_Bignum.size(); ++i)
        if(A_Bignum[A_Bignum.size() - i] < (nb / pow_int(10, A_Bignum.size() - i)) % 10)
            return true;
        else if(A_Bignum[A_Bignum.size() - i] > (nb / pow_int(10, A_Bignum.size() - i)) % 10)
            return false;

    return false;
}

bool Bignum::operator<(const Bignum& nb) const
{
    bool result;

    if(*this == nb)
        return false;

    if(A_IsSigned != nb.A_IsSigned)
        return A_IsSigned;

    result = !A_IsSigned;

    if(A_Bignum.size() < nb.A_Bignum.size())
        return result;
    else if(A_Bignum.size() > nb.A_Bignum.size())
        return !result;

    for(unsigned long long int i = 1; i <= A_Bignum.size(); ++i)
        if(A_Bignum[A_Bignum.size() - i] < nb.A_Bignum[A_Bignum.size() - i])
            return result;
        else if(A_Bignum[A_Bignum.size() - i] > nb.A_Bignum[A_Bignum.size() - i])
            return !result;
    return !result;
}

bool Bignum::operator>(const unsigned long long int& nb) const
{
    return !(*this < nb || *this == nb);
}

bool Bignum::operator>(const Bignum& nb) const
{
    return !(*this < nb || *this == nb);
}

bool Bignum::operator<=(const unsigned long long int& nb) const
{
    return *this < nb || *this == nb;
}

bool Bignum::operator<=(const Bignum& nb) const
{
    return *this < nb || *this == nb;
}

bool Bignum::operator>=(const unsigned long long int& nb) const
{
    return !(*this < nb);
}

bool Bignum::operator>=(const Bignum& nb) const
{
    return !(*this < nb);
}

void Bignum::operator+=(unsigned long long int nb)
{
    unsigned int i;
    unsigned char retenue(0), value(0);

    if(A_IsSigned)
    {
        A_IsSigned = false;
        *this -= nb;
        A_IsSigned = !A_IsSigned;
    }
    else
    {
        for(i = 0; nb > 0 || retenue > 0; ++i)
        {
            if(i >= A_Bignum.size())
            {
                value = nb % 10 + retenue;
                A_Bignum.push_back(value % 10);
            }
            else
            {
                value = A_Bignum[i] + nb % 10 + retenue;
                A_Bignum[i] = value % 10;
            }
            retenue = value / 10;
            nb /= 10;
        }
    }
    A_Bignum.push_back(0);
    while(A_Bignum.size() > 1 && !A_Bignum.back())
        A_Bignum.pop_back();
    if(A_Bignum.size() <= 0)
        A_IsSigned = false;
    if(A_Rest.size())
        A_Rest.resize(0, 0);
}

void Bignum::operator+=(const Bignum& nb)
{
    unsigned long long int i = 0;
    unsigned char retenue = 0;
    unsigned char value;

    if(A_IsSigned != nb.A_IsSigned)
    {
        A_IsSigned = !A_IsSigned;
        *this -= nb;
        A_IsSigned = !A_IsSigned;
    }
    else
    {
        for(i = 0; i < nb.A_Bignum.size(); ++i)
        {
            if(i >= A_Bignum.size())
            {
                value = nb.A_Bignum[i] + retenue;
                A_Bignum.push_back(value % 10);
            }
            else
            {
                value = A_Bignum[i] + nb.A_Bignum[i] + retenue;
                A_Bignum[i] = value % 10;
            }
            retenue = value / 10;
        }
        for(; retenue > 0; ++i)
        {
            if(i >= A_Bignum.size())
            {
                value = retenue;
                A_Bignum.push_back(value % 10);
            }
            else
            {
                value = A_Bignum[i] + retenue;
                A_Bignum[i] = value % 10;
            }
            retenue = value / 10;
        }
    }
    A_Bignum.push_back(0);
    while(A_Bignum.size() > 1 && !A_Bignum.back())
        A_Bignum.pop_back();
    if(A_Bignum.size() <= 0)
        A_IsSigned = false;
    if(A_Rest.size())
        A_Rest.resize(0, 0);
}

void Bignum::operator-=(unsigned long long int nb)
{
    unsigned long long int masking(1);
    Bignum cp;

    ///if très Sale!!!
    if(*this == 0){
        *this += nb;
        A_IsSigned = true;
        return;
    }

    if(A_IsSigned)
    {
        A_IsSigned = false;
        *this += nb;
        A_IsSigned = true;
    }
    else
    {
        if(*this < nb)
        {
            cp = nb;
            cp -= *this;
            *this = cp;
            A_IsSigned = true;
        }
        else
        {
            for(unsigned long long int i(0); i < A_Bignum.size(); ++i, masking *= 10)
            {
                if((nb / masking) % 10 > A_Bignum[i])
                {
                    A_Bignum[i] += 10;
                    nb += masking * 10;
                }
                A_Bignum[i] -= (nb / masking) % 10;
            }
        }
    }
    A_Bignum.push_back(0);
    while(A_Bignum.size() > 1 && !A_Bignum.back())
        A_Bignum.pop_back();
    if(A_Bignum.size() <= 0)
        A_IsSigned = false;
    if(A_Rest.size())
        A_Rest.resize(0, 0);
}

void Bignum::operator-=(const Bignum& nb)
{
    Bignum cp(nb);


    if(*this == 0){
        cp.A_IsSigned = false;
        *this += cp;
        A_IsSigned = !nb.A_IsSigned;
        return;
    }

    if(A_IsSigned != nb.A_IsSigned)
    {
        A_IsSigned = !A_IsSigned;
        *this += nb;
        A_IsSigned = !A_IsSigned;
    }
    else
    {
        if((*this < nb && *this > 0) || (nb < 0 && *this > nb))
        {
            cp = *this;
            *this = nb;
            A_IsSigned = !A_IsSigned;
        }
        else
            cp = nb;

        for(unsigned long long int i(0); i < cp.A_Bignum.size(); ++i)
        {
            if(A_Bignum[i] < cp.A_Bignum[i])
            {
                A_Bignum[i] += 10;
                if(i == cp.A_Bignum.size() - 1)
                    cp.A_Bignum.push_back(1);
                else
                    ++cp.A_Bignum[i + 1];
            }
            A_Bignum[i] -= cp.A_Bignum[i];
        }
    }
    A_Bignum.push_back(0);
    while(A_Bignum.size() > 1 && !A_Bignum.back())
        A_Bignum.pop_back();
    if(A_Bignum.size() <= 0)
        A_IsSigned = false;
    if(A_Rest.size())
        A_Rest.resize(0, 0);
}

void Bignum::operator*=(const unsigned long long int& nb)
{
    Bignum cp_nb(nb);
    *this *= cp_nb;
}

void Bignum::operator*=(const Bignum nb)
{
    unsigned char value, retenue;
    Bignum cp(*this);
    std::vector<Bignum> tab;
    *this = 0;

    if(cp == 0 || nb == 0)
        return;

    /*
    c'est de la merde ça pour multiplier
    for(Bignum i(0); i < nb; ++i)
        *this += cp;
    */

    tab.resize(nb.A_Bignum.size(), 0);
    tab[0].A_Bignum.pop_back();

    for(unsigned long long int  i(0); i < nb.A_Bignum.size(); ++i){
        retenue = 0;
        for(unsigned long long int j(1); j < i; ++j)
            tab[i].A_Bignum.push_back(0);
        for(unsigned long long int j(0); j < cp.A_Bignum.size(); ++j){

            value = nb.A_Bignum[i] * cp.A_Bignum[j] + retenue;
            tab[i].A_Bignum.push_back(value % 10);
            retenue = value / 10;
        }
        if(retenue)
            tab[i].A_Bignum.push_back(retenue);
    }

    for(unsigned long long int  i(0); i < nb.A_Bignum.size(); ++i)
        *this += tab[i];

    A_IsSigned = A_Bignum.size() && ((cp.A_IsSigned || nb.A_IsSigned) && !(cp.A_IsSigned && nb.A_IsSigned));
    if(A_Rest.size())
        A_Rest.resize(0, 0);
}

void Bignum::operator/=(const unsigned long long int& nb)
{
    Bignum cp_nb(nb);
    *this /= cp_nb;
}

void Bignum::operator/=(Bignum nb)
{
    bool cpSign(A_IsSigned), cpNbSign(nb.A_IsSigned);
    unsigned long long int dividand;
    Bignum cp(*this), change;
    *this = 0;

    if(cp == 0 || nb == 0)
        return;

    cp.A_IsSigned = nb.A_IsSigned = false;

    while(cp.A_Bignum.size() > 0){
        dividand = 0;
        change = 0;

        //if(cp.A_Bignum[cp.A_Bignum.size() - 1] != 0){
            while(cp.A_Bignum.size() > 0 && change < nb){
                change = change * 10 + cp.A_Bignum[cp.A_Bignum.size() - 1];
                cp.A_Bignum.pop_back();
            }
          //  std::cout << change * 10;
            while(change >= nb){
                change -= nb;
                ++dividand;
            }
            *this = (*this) * 10 + dividand;

            if(change != 0 && cp.A_Bignum.size())
                for(unsigned long long int i(0); i < change.A_Bignum.size(); ++i)
                    cp.A_Bignum.push_back(change.A_Bignum[i]);
        /*}else{
            cp.A_Bignum.pop_back();
            while(cp.A_Bignum.size() > 0 && cp.A_Bignum[cp.A_Bignum.size() - 1] == 0){
                change.A_Bignum.push_back(0);
                cp.A_Bignum.pop_back();
            }
            *this *= pow_int(10, change.A_Bignum.size());
            std::cout << "c " << change << std::endl;
        }*/
    }

    /*if(cp.A_Bignum[cp.A_Bignum.size() - 1] == 0)
        *this *= pow_int(10, cp.A_Bignum.size());*/

    A_Rest.resize(0, 0);
    if(change != 0)
        for(unsigned long long int i(0); i < change.A_Bignum.size(); ++i)
            cp.A_Bignum.push_back(change.A_Bignum[i]);
    for(unsigned long long int i(0); i < cp.A_Bignum.size(); ++i)
        A_Rest.push_back(cp.A_Bignum[i]);

    A_IsSigned = A_Bignum.size() && ((cpSign || cpNbSign) && !(cpSign && cpNbSign));
}

void Bignum::operator%=(const unsigned long long int& nb)
{
    Bignum cp_nb(nb);
    *this %= cp_nb;
}

void Bignum::operator%=(const Bignum& nb)
{
    *this /= nb;
    A_IsSigned = false;
    A_Bignum.resize(0, 0);
    for(unsigned long long int i(0); i < A_Rest.size(); ++i)
        A_Bignum.push_back(A_Rest[i]);

    A_Bignum.push_back(0);
    while(A_Bignum.size() > 1 && !A_Bignum.back())
        A_Bignum.pop_back();
    A_Rest.resize(0, 0);
}

Bignum& Bignum::operator++()
{
    *this += 1;
    return *this;
}

Bignum Bignum::operator++(int)
{
    Bignum cp(*this);
    ++(*this);
    return cp;
}

Bignum& Bignum::operator--()
{
    *this -= 1;
    return *this;
}

Bignum Bignum::operator--(int)
{
    Bignum cp(*this);
    --(*this);
    return cp;
}

