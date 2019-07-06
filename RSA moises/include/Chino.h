#ifndef CHINO_H
#define CHINO_H
#include <NTL/ZZ.h>

using namespace NTL;
class Chino
{
    public:
        Chino(){
            a=0;
            M=0;
            Mi=0;
        }

        ZZ a,M,Mi;
};

#endif // CHINO_H
