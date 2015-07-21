#include <iostream>
#include "RSA.h"

using namespace std;

int main()
{
    Bignum p(7), q(4992), d, k(0), inter;
    vector<Bignum> re = RSA_System::Extended_Euclidean_Algorithm(p, q);

    for(int i = 0; i < 3; ++i)
        display(re[i]);

        //display(k*q);

    d = re[1];
    //while(d <= 2 || d >= q){
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
        d = re[1];
        inter = (k * q);
        d -= inter;
    display(re[1]);
    display(k);
    display(q);
    display(d);
    //}
//*/
    return 0;
}
