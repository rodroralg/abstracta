#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include <string>
#include <math.h>


#include <NTL/ZZ.h>
using namespace NTL;


#include "RSA.h"

class operaciones
{
    public:
        operaciones();
        ZZ euclides(ZZ m, ZZ n);
        ZZ euclidesEx(ZZ a, ZZ b);
        ZZ ferman(ZZ a, ZZ m);
        ZZ phi(ZZ n);
        ZZ phinversa(ZZ n);

        ZZ inversa(ZZ num, ZZ mod);
        ZZ expomod(ZZ base, ZZ exp, ZZ mod);
        ZZ mod(ZZ a, ZZ n);


        ZZ convStoZZ(string str);
        string convZZtoS(ZZ num);




};

#endif // OPERACIONES_H
