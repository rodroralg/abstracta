#include <iostream>

using namespace std;

#include <string>

#include <NTL/ZZ.h>
using namespace NTL;

#include <sstream>

#include "Gamal.h"

const int BITS= 10;

ZZ mod(ZZ a, ZZ n)
{
    if(a >= 0)
        return (a - (a/n)* n);
    else
        return (a - ((a/n)-1)*n);
}

ZZ expomod(ZZ base, ZZ exp, ZZ m)
{
    ZZ result;
    result = 1;
    ZZ dos;
    dos=2;
    while (exp != 0) {
        if (mod(exp,dos)!= 0)
            result = mod((result * base) , m);
        exp = exp/ 2;
        base = mod((base * base) , m);
    }
    return result;
}




ZZ priroot(ZZ &p, int op)
{
    ZZ num, limit = ZZ(2);
    limit <<=BITS;
    if (op==1){
        num=mod(RandomLen_ZZ(BITS),p-limit-1) + limit/2;
        return num;
    }
    else if(op==2){
        num=mod(RandomLen_ZZ(BITS),p-limit-3) + limit/2;
        return num;
    }
    else if(op==3){
        bool found= true;
        while(found){
            num=mod(RandomLen_ZZ(BITS),p-limit-1) + limit/2;
            if(mod(num*num,p)!= 1 && expomod(num,(p-1)/2,p) != 1){
                found = false;
            }
        }
        return num;
    }
}


int main()
{

    string mensaje="hola";

    Gamal a(10);

    string cif=a.cifrado(a.e1[5],a.e2,a.P,mensaje);
    cout << cif << endl;
    string decif=a.descifrado(cif);
    cout << decif << endl;


///

/*
     ZZ x;
    x=RandomLen_ZZ(BITS);
    cout << "numro aleatorio de " << BITS << endl;
    cout << "numero: " << x << endl;

//    ZZ p;
//    p=1019;
    cout << priroot(x,1) << endl;
    cout << endl;
    cout << priroot(x,2) << endl;
    cout << endl;
    cout << priroot(x,3) << endl;


//    ZZ mensaje;
//    mensaje=123456789;
//
//    Gamal a(64);
//    cout << a.e1[20] << endl;
//    cout << a.e2 << endl;
//    cout << "P: " << a.P << endl;
////    a.generarRaiz(a.P);
//    a.cifrado(a.e1[1],a.e2,a.P,mensaje);


*/

    return 0;
}
