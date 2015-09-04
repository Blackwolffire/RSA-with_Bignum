/** RSA.cpp
 * by Blackwolffire
 * 07/16/2015 | 08/30/2015
 * Defines functions for RSA class.
 */

#include <fstream>
#include "RSA.h"

using namespace std;

/// STATIC /////////////////////////////////////////////////////////

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
        cout << "Erreur: Le nombre est negatif.\n";
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

string RSA_System::getNumberStr(string str)
{
    string strResult = "";

    for(unsigned short int i(0); i < str.length(); ++i)
        strResult += getCaracStrNb(str[i]);
    return strResult;
}

string RSA_System::getCaracStrNb(unsigned char carac)
{
    string result = "";

    while(carac > 0){
        result += carac % 10 + '0';
        carac /= 10;
    }
    return result;
}

vector<Bignum> RSA_System::Extended_Euclidean_Algorithm(const Bignum& a, const Bignum& b)
{
    Bignum r(a), r_(b), u(1), v(0), u_(0), v_(1), q, rs, us, vs;
    vector<Bignum> result;

    if(a < 0 || b < 0){
        cout << "Erreur: Le nombre est negatif.\n";
        return result;
    }

/// MERCI WIKIPEDIA♥♥♥
    while(r_ != 0){
        q = r / r_;
        rs = r;
        us = u;
        vs = v;
        r = r_;
        u = u_;
        v = v_;
        r_ = rs - q * r_;
        u_ = us - q * u_;
        v_ = vs - q * v_;
    }
    result.resize(3, 0);
    result[0] = r;
    result[1] = u;
    result[2] = v;
    return result;
}

bool RSA_System::fileExist (const string& name)
{
    ifstream file(name.c_str());

    if (file.good()){
        file.close();
        return true;
    }else{
        file.close();
        return false;
    }
}

/// NON STATIC /////////////////////////////////////////////////////

RSA_System::RSA_System(unsigned long long int keySize) : A_IsInit(false), A_KeySize(keySize)
{
}

RSA_System::RSA_System(unsigned long long int keySize, string str) : A_IsInit(false), A_KeySize(keySize)
{
    RSA_Init(str);
}

Bignum RSA_System::getHashKey(string str)
{
    Bignum result;
    result = getNumberStr(str);
    result %= A_KeySize;
    return result;
}

vector<Bignum> RSA_System::getPrimeNumber(string str)
{
    char carac;
    string cp_str(str);
    Bignum p, q;
    vector<Bignum> result;
    result.resize(3, 0);

    result[0] = getNextPrime(getHashKey(str));

    for(unsigned short int i(0); i < str.length() / 2; ++i){
        carac = str[i];
        cp_str[i] = str[str.length() - 1 - i];
        cp_str[str.length() - 1 - i] = carac;
    }
    result[1] = getNextPrime(getHashKey(cp_str));

    p = getNumberStr(str);
    q = getNumberStr(cp_str);
    p *= q;

    result[2] = getNextPrime(p % getNextPrime(A_KeySize / 100));

    return result;
}

void RSA_System::RSA_Init(string str, unsigned long long int keySize)
{
    A_KeySize = keySize;

    Bignum fi, k(0);
    vector<Bignum> PQE = getPrimeNumber(str);

    n = PQE[0] * PQE[1];
    fi = (PQE[0] - 1) * (PQE[1] - 1);
    e = PQE[2];

    PQE = Extended_Euclidean_Algorithm(e, fi);

    d = PQE[1];
    while(d <= 2 || d >= fi){
        if(d < 0){
            if(k < 0)
                k = 1;
            else
                k = "-1";
        }else{
            if(d <= 2)
                if(k < 0)
                    --k;
                else
                    ++k;
            else
                if(k < 0)
                    ++k;
                else
                    --k;
        }
        d = PQE[1] - k * fi;
    }
    A_IsInit = true;

    cout << "Public Key : " << n << '\t' << e << "\nPrivate Key : " << d << '\t' << n << endl;
}

// Encryption

void RSA_System::crypt_byte(char data, Bignum& result)
{
    result = static_cast<unsigned long long int>(data);

    if(!A_IsInit){
        cout << "Erreur: RSA_System non initialise.\n";
        return;
    }

    result.BigPow(e);
    result %= n;
}

void RSA_System::crypt_string(string destination, std::string data)
{
    unsigned char carac;
    unsigned int nLength(n.getSize());
    ofstream file;
    Bignum nb;

    if(fileExist(destination)){
        cout << "Erreur: Le fichier " + destination + " existe deja. Voulez-vous le supprimer? (y/n)\n";
        cin >> carac;
        if(toupper(carac) == 'Y')
            remove(destination.c_str());
        else
            return;
    }

    file.open(destination.c_str());

    if(!file){
        cout << "Erreur: Le fichier " + destination + " ne peut pas s'ouvrir.\n";
        return;
    }

    carac = 0;
    cout << "chargement: 0%\n";
    for(unsigned long long int i(0); i < data.length(); ++i){
        crypt_byte(data[i], nb);
        file << nb.compress_Bignum(nLength);
        if(carac != ((i + 1) * 100 /  data.length())){
            carac = (i + 1) * 100 /  data.length();
            cout << "chargement: " <<  static_cast<unsigned short int>(carac) << "%\n";
        }
    }

    file.close();
    cout << '\a';
}

void RSA_System::crypt_file(string destination, string dataFile)
{
    unsigned char carac;
    unsigned int length, nlength(n.getSize());
    ofstream outfile;
    ifstream infile;
    Bignum nb;

    if(!fileExist(dataFile)){
        cout << "Erreur: Le fichier a crypter n'existe pas.\n";
        return;
    }

    if(destination == dataFile){
        cout << "Erreur: Tu es con.";
        return;
    }

    if(fileExist(destination)){
        cout << "Erreur: Le fichier " + destination + " existe deja. Voulez-vous le supprimer? (y/n)\n";
        cin >> carac;
        if(toupper(carac) == 'Y')
            remove(destination.c_str());
        else
            return;
    }

    outfile.open(destination.c_str());
    infile.open(dataFile.c_str());

    if(!outfile || !infile){
        cout << "Erreur: Un fichier ne peut pas s'ouvrir.\n";
        return;
    }

    infile.seekg(0, ios::end);
    length = infile.tellg();
    infile.seekg(0, ios::beg);
    carac = 0;
    cout << "chargement: 0%\n";
    for(unsigned long long int i(0); i < length; ++i){
        crypt_byte(infile.get(), nb);
        outfile << nb.compress_Bignum(nlength);
        if(carac != ((i + 1) * 100 / length)){
            carac = (i + 1) * 100 / length;
            cout << "chargement: " <<  static_cast<unsigned short int>(carac) << "%\n";
        }
    }

    outfile.close();
    infile.close();
    cout << '\a';
}

// Decryption

char RSA_System::decrypt_Bignum(Bignum data)
{
    string str;

    data.BigPow(d);
    data %= n;
    str = data.toChar();

    return str[0];
}

void RSA_System::decrypt_string(std::string destination, std::string data)
{
    unsigned char carac;
    unsigned int nLength(n.getSize());
    ofstream file;

    if(fileExist(destination)){
        cout << "Erreur: Le fichier " + destination + " existe deja. Voulez-vous le supprimer? (y/n)\n";
        cin >> carac;
        if(toupper(carac) == 'Y')
            remove(destination.c_str());
        else
            return;
    }

    file.open(destination.c_str());

    if(!file){
        cout << "Erreur: Le fichier " + destination + " ne peut pas s'ouvrir.\n";
        return;
    }

    carac = 0;
    cout << "chargement: 0%\n";
    for(unsigned long long int i(0); i < data.length(); i += (nLength / 2 + nLength % 2)){
        file << decrypt_Bignum(Bignum::decompress_Bignum(data.substr(i, (nLength / 2 + nLength % 2))));
        if(carac != ((i + (nLength / 2 + nLength % 2)) * 100 /  data.length())){
            carac = (i + (nLength / 2 + nLength % 2)) * 100 /  data.length();
            cout << "chargement: " <<  static_cast<unsigned short int>(carac) << "%\n";
        }
    }
    file.close();
    cout << '\a';
}

void RSA_System::decrypt_file(string destination, string dataFile)
{
    unsigned char carac;
    unsigned int length, nLength(n.getSize());
    string str;
    ofstream outfile;
    ifstream infile;

    if(!fileExist(dataFile)){
        cout << "Erreur: Le fichier a crypter n'existe pas.\n";
        return;
    }

    if(destination == dataFile){
        cout << "Erreur: Tu es con.";
        return;
    }

    if(fileExist(destination)){
        cout << "Erreur: Le fichier " + destination + " existe deja. Voulez-vous le supprimer? (y/n)\n";
        cin >> carac;
        if(toupper(carac) == 'Y')
            remove(destination.c_str());
        else
            return;
    }

    outfile.open(destination.c_str());
    infile.open(dataFile.c_str());

    if(!outfile || !infile){
        cout << "Erreur: Un fichier ne peut pas s'ouvrir.\n";
        return;
    }

    infile.seekg(0, ios::end);
    length = infile.tellg();
    infile.seekg(0, ios::beg);
    carac = 0;
    cout << "chargement: 0%\n";
    for(unsigned long long int i(0); i < length; i += (nLength / 2 + nLength % 2)){
        str = "";
        for(unsigned int j(0); j < (nLength / 2 + nLength % 2); ++j)
            str += infile.get();

        outfile << decrypt_Bignum(Bignum::decompress_Bignum(str));
        if(carac != ((i + (nLength / 2 + nLength % 2)) * 100 / length)){
            carac = (i + (nLength / 2 + nLength % 2)) * 100 / length;
            cout << "chargement: " <<  static_cast<unsigned short int>(carac) << "%\n";
        }
    }
    infile.close();
    outfile.close();
    cout << '\a';
}
