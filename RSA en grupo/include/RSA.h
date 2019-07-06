#ifndef RSA_H
#define RSA_H

#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include <string>
#include <math.h>


#include <NTL/ZZ.h>
using namespace NTL;

class RSA
{
    public:
        RSA(int bits);
        RSA(ZZ _p, ZZ _q,ZZ clavpriv);
        RSA(ZZ _e,ZZ _n);

        void genclaves();

        ZZ genclavPublica();
        ZZ genclavPrivada();

        ZZ cifrado(string T,ZZ clavePublica,ZZ N);
        string cifradobloques(string T, ZZ clavPublica, ZZ N);
        string descifrado(string TC);



        ZZ euclides(ZZ m, ZZ n);
        ZZ euclidesEx(ZZ a, ZZ b);

        ZZ euclides_bin(ZZ m, ZZ n);



        ZZ restochino(ZZ T);
        ZZ ferman(ZZ a, ZZ m);
        ZZ phi(ZZ n);
        ZZ phinversa(ZZ n);


        ZZ inversa(ZZ num, ZZ mod);
        ZZ expomod(ZZ base, ZZ exp, ZZ mod);
        ZZ mod(ZZ a, ZZ n);

        string normalizarString(int num);
        string normalizarStringAscii(int num);
        string normalizar(ZZ num);

        ZZ convStoZZ(string str);
        string convZZtoS(ZZ num);

        string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
        int tamalf=alfabeto.size();


        ZZ clavPublica;
        ZZ clavPrivada;

        ZZ P;
        ZZ Q;
        ZZ N;
        int tamN;
        ZZ phiN;
        int BIT;



    protected:

    private:
};

#endif // RSA_H
