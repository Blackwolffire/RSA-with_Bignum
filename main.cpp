#include "RSA.h"

using namespace std;

int main()
{
    bool proceed(true);
    char carac(0), carac2(0); // me jugez pas pour les noms des variables
    string str(""), str2("");
    RSA_System myrsa;

    do{
        cout << '\a';
        do{
            cout << "Veuillez entrer votre mot de passe (5 caracteres ou plus):\n";
            cin >> str;
            for(unsigned short int i(0); i < 500; ++i)
                cout << endl;
        }while(str.length() < 5);

        do{
            cout << "Selectionnez la taille des cles: Small Normal ou Huge (S N H)\n";
            cin >> carac;
            carac = toupper(carac);
        }while(carac != 'S' && carac != 'N' && carac != 'H');

        cout << "Veuillez patienter longtemps pendant la generation de cles...\n";

        switch(carac)
        {
            case 'N':
                myrsa.RSA_Init(str, RSA_System::NORMAL);
                break;
            case 'H':
                myrsa.RSA_Init(str, RSA_System::HUGE);
                break;
            default:
                myrsa.RSA_Init(str, RSA_System::SMALL);
                break;
        }

        do{
            cout << "C pour crypter, D pour decrypter:\n";
            cin >> carac;
            carac = toupper(carac);
        }while(carac != 'C' && carac != 'D');

        do{
            cout << "M pour un message, F pour un fichier:\n";
            cin >> carac2;
            carac2 = toupper(carac2);
        }while(carac2 != 'M' && carac2 != 'F');

        if(carac2 == 'M'){
            cout << "Entrez le chemin du fichier de destination:\n";
            cin >> str2;
            if(carac == 'C')
                str2 += ".rsa";
            else
                str2 = str2.substr(0, str.find(".rsa", 0));
            cout << "Entrez votre message:\n";
            cin >> str;
        }else{
            cout << "Entrez le chemin du fichier:\n";
            cin >> str;
            if(str.find(".rsa", 0) == string::npos)
                str2 = str + ".rsa";
            else
                str2 = str.substr(0, str.find(".rsa", 0));
        }

        cout << "Veuillez patienter Tres longtemps, merci\n";

        if(carac == 'C'){
            if(carac2 == 'M')
                myrsa.crypt_string(str2, str);
            else
                myrsa.crypt_file(str2, str);
        }else{
            if(carac2 == 'M')
                myrsa.decrypt_string(str2, str);
            else
                myrsa.decrypt_file(str2, str);
        }

        cout << "Voulez vous faire autre chose? (Y/N)\n";
        cin >> carac;
        if(toupper(carac) == 'N')
            proceed = false;

    }while(proceed);

    return 0;
}
