#ifndef GAMAL_H
#define GAMAL_H

#include <iostream>
using namespace std;

#include <NTL/ZZ.h>
using namespace NTL;
#include <vector>

class Gamal
{
    public:
        Gamal(int bits);

        vector<ZZ> generarRaiz(ZZ primo);
        ZZ generator(ZZ p);
        vector<ZZ> primroot(ZZ val);


        ZZ raizprim(ZZ p);
        ZZ BlumBlumShub(ZZ MAX_BBS);
        bool esRP(ZZ g, ZZ n);


        ZZ expomod(ZZ base, ZZ exp, ZZ m);
        ZZ mod(ZZ a, ZZ n);
        ZZ euclides(ZZ m, ZZ n);
        ZZ euclides_bin(ZZ m, ZZ n);

        ZZ phi(ZZ n);
        ZZ inversaEuler(ZZ a, ZZ n);

        string normalizar(ZZ a, int tam);
        int Ndigitos(ZZ& a);
        ZZ convStoZZ(string str);


        string cifrado(ZZ _e1, ZZ _e2, ZZ _P, string mensaje);
        string descifrado(string TextoC);

        ZZ P;
//        ZZ e1;
        vector<ZZ> e1;
        ZZ e2;

        ZZ D;

        ZZ c1;
        ZZ c2;
        ZZ km;

        string alfabeto=" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 ,.";

    protected:

    private:

        int BIT;
};

#endif // GAMAL_H
