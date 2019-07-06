#include "Gamal.h"

#include <iostream>
using namespace std;

#include <NTL/ZZ.h>
using namespace NTL;
#include <vector>
#include <sstream>


Gamal::Gamal(int bits)
{
    BIT=bits;
    GenPrime(P,BIT);
    D=RandomLen_ZZ(BIT);
    e1=primroot(P);
    e2=expomod(e1[5],D,P);

}

vector<ZZ> Gamal::primroot(ZZ val) {

    vector<ZZ> res;
    ZZ start;
    ZZ i,j;
    for (i = 2; i<val - 1; i++) {
        start = 1;
        bool flag = 1;
        for ( j = 0; j<val / 2; j++) {
            start = (start * i) % val;
            if (start % val == 1) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            res.push_back(i);
        }
    }
    return res;
}

string Gamal::normalizar(ZZ a,int tam)
{
  stringstream stream;
  stream.str();
  stream << a;
  string cadena=stream.str();
  string ans(tam-cadena.size(),'0');
  return ans+cadena;
}

int Gamal::Ndigitos(ZZ &a)
{
  stringstream stream;
  stream << a;
  string cadena = stream.str();
  return cadena.size();
}

ZZ Gamal::convStoZZ(string str)
{
    ZZ number(NTL::INIT_VAL, str.c_str());
    return number;
}

string Gamal::cifrado(ZZ _e1, ZZ _e2, ZZ _p, string mensaje)
{
    ZZ r;
    RandomBnd(r, _p);
    c1=expomod(_e1,r,_p);
    km=expomod(_e2,r,_p);
    string encriptar;


    for(int i=0;i<mensaje.size();i++)
    {
//        ZZ alf;
//        alf=convStoZZ(alfabeto.find(mensaje[i]));

        encriptar+=normalizar(to_ZZ(alfabeto.find(mensaje[i])),2);
    }
    int tam=Ndigitos(_p)-1;
    while(encriptar.size()%tam)
    {
        encriptar.push_back('0');
    }
    string c2;
    for(int i=0;i<encriptar.size();i+=tam)
    {
        string bloque=encriptar.substr(i,tam);
        cout << "bloques: " << bloque << endl;

        ZZ pos;
        pos=convStoZZ(bloque);
        cout << "POS" << pos << endl;
        pos=(pos*km)%P;
        cout << "pos " << pos << endl;
        c2+=(normalizar(pos,tam+1));

    }
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;

    return normalizar(c1,tam+1)+c2;

}

string Gamal::descifrado(string TextoC)
{
    string C1=TextoC.substr(0,Ndigitos(P));
//    c1=to_ZZ(c1.c_str());
    c1=convStoZZ(C1);

    km=expomod(c1,D,P);
    km=inversaEuler(km,P);

    string aux;
    for(int i=Ndigitos(P);i<TextoC.size();i+=Ndigitos(P))
    {
        string pos=TextoC.substr(i,Ndigitos(P));
        ZZ c;
        c= convStoZZ(pos);

        aux+=normalizar((c*km)%P,Ndigitos(P)-1);
    }
    string ans;
    for(int i=0;i<aux.size();i+=2)
    {
        string pos=aux.substr(i,2);
        ans.push_back(alfabeto[stoi(pos)]);
    }
    return ans;
}


ZZ Gamal::mod(ZZ a, ZZ n)
{
    if(a >= 0)
        return (a - (a/n)* n);
    else
        return (a - ((a/n)-1)*n);
}

ZZ Gamal::euclides(ZZ m, ZZ n)
{
    while (n!=0){
        ZZ t;
        t=n;
        n=mod(m,n);
        m=t;
    }
    return m;
}

ZZ Gamal::euclides_bin(ZZ m , ZZ n)
{
    ZZ i,c;
    i=0;
    if(m==0)
        return m;
    if(n==0)
        return n;
    while(((m|n)&1)==0){
        c++;
        m>>=1;
        n>>=1;
        i++;
    }
    while((m&1)==0){
        m>>=1;
        i++;
    }
    while(n!=0){
        while((n&1)==0){
            n>>=1;
            i++;
        }
        if(m>n)
            swap(m,n);
            n-=m;
            i++;
    }
    return m<<conv<int>(c);
}

ZZ Gamal::expomod(ZZ base, ZZ exp, ZZ m)
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


ZZ Gamal::inversaEuler(ZZ a, ZZ n){
    if(euclides(a,n)==1){
        return expomod(a,phi(n)-1,n);
    }
}

ZZ Gamal::phi(ZZ n) {
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

