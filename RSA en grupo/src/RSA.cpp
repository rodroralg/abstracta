#include "RSA.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#include <string>
#include <math.h>
#include <sstream>

#include <NTL/ZZ.h>
using namespace NTL;


RSA::RSA(int bits)
{
    BIT=bits;
    while(P==Q){
    GenPrime(P,BIT);
    GenPrime(Q,BIT);
    }

    N=P*Q;
    phiN=(P-1)*(Q-1);
//    phiN=phi(N);

    while(clavPublica==clavPrivada){
    clavPublica=genclavPublica();
    clavPrivada=genclavPrivada();
    }

}
RSA::RSA(ZZ _e,ZZ _n)
{

    N=_n;
    clavPublica=_e;
    clavPrivada=clavPrivada;

}

//RSA::RSA(ZZ _p, ZZ _q,ZZ clavpriv)
//{
//    P=_p;
//    Q=_q;
//    N=P*Q;
////    phiN=(P-1)*(Q-1);
//    phiN=phi(N);
//    clavPrivada=clavpriv;
//}

void RSA::genclaves()
{

    clavPublica=genclavPublica();
    clavPrivada=genclavPrivada();

}


ZZ RSA::genclavPublica()
{
    while(true){
//        ZZ E_aux=GenPrime_ZZ(BIT);
        ZZ E_aux=RandomLen_ZZ(BIT);
        if ((euclides_bin(E_aux,phiN)==1) && E_aux<phiN)
            return E_aux;
    }
}

ZZ RSA::genclavPrivada()
{
    ZZ D_aux;
//    return D_aux=euclidesEx(clavPublica,phi(N));


    return D_aux=euclidesEx(clavPublica,phiN);
//    return D_aux=ferman(ZZ phiN, ZZ clavPublica);
//    return D_aux=ferman(clavPublica,phiN);


}


ZZ RSA::convStoZZ(string str)
{
    ZZ number(NTL::INIT_VAL, str.c_str());
    return number;
}

string RSA::convZZtoS(ZZ num)
{
    stringstream x;
    x << num;
    return x.str();
}



string RSA::cifradobloques(string Texto, ZZ publica, ZZ Nn)
{

    string cifrado;
///tamaño de N
    string Ntam_aux=convZZtoS(Nn);
    tamN=Ntam_aux.size();
    cout << "tamN: " << tamN << endl;
///
    string bloque;
    int pos;
    char ch;
    for(int i=0;i<Texto.size();i++){
        ch=Texto[i];
        pos=static_cast<int>(ch);
        bloque+=normalizarStringAscii(pos);
        ///cout << "bloqe por pasos: " << bloque << endl;
    }
    cout << "letras: " << bloque << "\n" << endl;

    ZZ bloqueZZ;//agarra los numeros de las letras y va comparando
    bloqueZZ=0;

    string aux;

    while(bloque.size()>0){
        bool verify_bloque=true;
        while(verify_bloque)
        {
            if(bloqueZZ<Nn && aux.size()<=tamN && bloque.size()!=0)
            {
                aux+=bloque.substr(0,3);

                ///cout << "aux: " << aux << endl;
                bloqueZZ=convStoZZ(aux);
                ///cout << "bloqueZZ: " << bloqueZZ << endl;
                aux=convZZtoS(bloqueZZ);


                if(bloqueZZ< Nn && aux.size()<=tamN)
                    bloque.erase(0,3);
                ///cout << "bloque: " << bloque << endl;
                ///cout << endl;

//                cout << "bloqueZZ: " << bloqueZZ << endl;
//                cout << "acumulador: " << bloque << endl;

            }
            else
            {
                if(bloque.size()!=0)
                    bloqueZZ/=1000;
                aux.clear();
                verify_bloque=false;
            }
        }

        ZZ x;
        x=expomod(bloqueZZ,publica,Nn);

        string almacen;
        almacen=normalizar(x);
//        cout << "almacen: " << almacen << endl;

        cifrado+=almacen;
    }

    return cifrado;

}

string RSA::descifrado(string TextoC)
{
    string descifrado;
    string bloque_L;
    ZZ x;

    string Ntam_aux=convZZtoS(N);
    tamN=Ntam_aux.size();
    cout << "tamN: " << tamN << endl;


    ZZ bloqueZZ;

    while(TextoC.size()>0)
    {
        bloqueZZ=0;
        string bloques_Ntam;

        bloques_Ntam+=TextoC.substr(0,tamN);
        bloqueZZ=convStoZZ(bloques_Ntam);
        TextoC.erase(0,tamN);
        ///cout << "bloques agarrados:" << bloqueZZ << endl;



        x=expomod(bloqueZZ,clavPrivada,N);
//        x=restochino(bloqueZZ);
        ///cout << "bloque desexponenciado: " << x << endl;

        string x_str=convZZtoS(x);
        int tamx;
        tamx=x_str.size();

        if(tamx%3!=0){
            bloque_L+='0';
            bloque_L+=convZZtoS(x);
        }
        else{
            bloque_L+=convZZtoS(x);
        }
        ///cout << "bloque desexponenciado y normaliado: " << bloque_L << endl;

    }
    cout << "bloque L: " << bloque_L << endl;
    int ch;
    for(int i=0;i<bloque_L.size();i+=3){
//        cout << "bloque L: " << bloque_L << endl;
        string bloqueTOint=bloque_L.substr(i,3);
        int pos=stoi(bloqueTOint);//para regresar al alfabeto
        ch=pos;
//        cout << "ch: " << ch << endl;
        descifrado+=ch;
//        cout << "descifrado:  " << descifrado << endl;
    }
    return descifrado;

}

ZZ RSA::mod(ZZ a, ZZ n)
{
    if(a >= 0)
        return (a - (a/n)* n);
    else
        return (a - ((a/n)-1)*n);
}

ZZ RSA::euclides(ZZ m, ZZ n)
{
    while (n!=0){
        ZZ t;
        t=n;
        n=mod(m,n);
        m=t;
    }
    return m;
}

ZZ RSA::euclides_bin(ZZ m , ZZ n)
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

ZZ RSA::inversa(ZZ num, ZZ m)
{
    num = mod(num,m);
    ZZ i;
    for (i=1; i<m; i++)
       if (mod((num*i), m) == 1)
          return i;
}

ZZ RSA::expomod(ZZ base, ZZ exp, ZZ m)
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



ZZ RSA::euclidesEx(ZZ a, ZZ b)
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

string RSA::normalizarString(int num){
    string letraStringTemp = to_string(num);
//    cout << letraStringTemp << endl;
    int letraTamTemp = letraStringTemp.size();
//    cout << letraTamTemp << endl;
    int letraTam=2;
    string temp = "0";
    if(letraTam > letraTamTemp){
        for(int i=0;i<(letraTam-1);i++){
            letraStringTemp.insert(0,temp);
        }
    }
    return letraStringTemp;
}

string RSA::normalizar(ZZ num)
{
    string almacen;
    string Num_str=convZZtoS(num);
    int tamNum;
    tamNum=Num_str.size();
    int diferencia=tamN-tamNum;
    if(diferencia)
    {
        for(int i=0;i<diferencia;i++)
        {
            almacen+="0";
        }
        almacen+=Num_str;
    }
    else
    {
        almacen+=Num_str;
    }

    return almacen;
}

string RSA::normalizarStringAscii(int num){
    string letraStringTemp = to_string(num);
//    cout << letraStringTemp << endl;
    int letraTamTemp = letraStringTemp.size();
//    cout << letraTamTemp << endl;
    int letraTam=3;
    int relleno=0;
    if(letraTamTemp==2)
        relleno=2;
    else if(letraTamTemp==1)
        relleno=1;
    string temp = "0";
    if(letraTam > letraTamTemp){
        for(int i=0;i<(letraTam-relleno);i++){
            letraStringTemp.insert(0,temp);
        }
    }
    return letraStringTemp;
}

ZZ RSA::restochino(ZZ T)
{
    ZZ descompP=mod(clavPrivada,P-1);
    ZZ descompQ=mod(clavPrivada,Q-1);
    ZZ M1,M2;
    M1=N/P;
    M2=N/Q;
    ZZ M1inv,M2inv;
    M1inv=euclidesEx(M1,P);
    M2inv=euclidesEx(M2,Q);


    ZZ Tp,Tq;
    Tp=mod(T,P);
    Tq=mod(T,Q);

    ZZ Mp,Mq;
    Mp=expomod(Tp,descompP,P);
    Mq=expomod(Tq,descompQ,Q);

    ZZ x1,x2;
    x1=mod((Mp*M1inv*M1),N);
    x2=mod((Mq*M2inv*M2),N);


    return mod((x1+x2),N);

}


ZZ RSA::phi(ZZ n) {
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

ZZ RSA::ferman(ZZ a,ZZ m){
    if (euclides(a, m) != 1) {
        cout << "no tiene inverso";
    }
    else {
        cout << ">> " << expomod(a, m - 2, m) << endl;
    }
    return expomod(a,m-2,m);
}
