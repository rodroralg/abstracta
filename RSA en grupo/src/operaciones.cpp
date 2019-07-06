#include "operaciones.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include <string>
#include <math.h>
#include <sstream>

#include <NTL/ZZ.h>
using namespace NTL;

#include "RSA.h"

ZZ operaciones::convStoZZ(string str)
{
    ZZ number(NTL::INIT_VAL, str.c_str());
    return number;
}

string operaciones::convZZtoS(ZZ num)
{
    stringstream x;
    x << num;
    return x.str();
}

ZZ operaciones::mod(ZZ a, ZZ n)
{
    if(a >= 0)
        return (a - (a/n)* n);
    else
        return (a - ((a/n)-1)*n);
}

ZZ operaciones::euclides(ZZ m, ZZ n)
{
    while (n!=0){
        ZZ t;
        t=n;
        n=mod(m,n);
        m=t;
    }
    return m;
}

ZZ operaciones::inversa(ZZ num, ZZ m)
{
    num = mod(num,m);
    ZZ i;
    for (i=1; i<m; i++)
       if (mod((num*i), m) == 1)
          return i;
}

ZZ operaciones::expomod(ZZ base, ZZ exp, ZZ m)
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

ZZ operaciones::euclidesEx(ZZ a, ZZ b)
{
    ZZ r1,r2,r,q,s,s1,s2,t,t1,t2,arr[3];

    r1=a;
    r2=b;
    r=0;
    q=0;
    s=0;
    s1=1;
    s2=0;
    t=0;
    t1=0;
    t2=1;
    arr[3];

    while(r2>0) {
        q = (r1/r2);

        r = r1 - q*r2;
        r1 = r2;
        r2 = r;

        s = s1-q*s2;
        s1 = s2;
        s2 = s;

        t = t1 - q*t2;
        t1 = t2;
        t2 = t;
    }
    arr[0] = r1;   // mcd (r1,r2)
    arr[1] = s1;   // x
    arr[2] = t1;   // y
//    s1=s1%tamalf;
//    ZZ conver;
//    conv(conver,tamalf);
//    s1=mod(s1,conver);
    ZZ inv=s1;
    if(s1<0)
        inv=s1+b;

    return inv;
}




ZZ operaciones::phi(ZZ n) {
    ZZ result;
    result = n;
    ZZ i;
    for (i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}

ZZ operaciones::ferman(ZZ a,ZZ m){
    if (euclides(a, m) != 1) {
        cout << "no tiene inverso";
    }
    else {
        cout << ">> " << expomod(a, m - 2, m) << endl;
    }
    return expomod(a,m-2,m);
}



