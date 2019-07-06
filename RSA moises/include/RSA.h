#ifndef RSA_H
#define RSA_H
#include <string>
#include <iostream>
#include <NTL/ZZ.h>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <Chino.h>

using namespace NTL;
using namespace std;
class RSA
{
    public:
        RSA(int);
        RSA(ZZ,ZZ);//Tamaño de bits
        void Gen_Claves();//Publicas y Privada
        //Funciones de cifrado Principales
        string cifrar(string,int);
        string descifrar(string,int);
        //Para cifrado ++
        string EstandarizarBloquesAlfabeto(string,int);
        string CifrarBloques(string,ZZ,ZZ,int);
        //Funciones para Bloques
        string Estandarizar(string,int);
        ZZ StringaZZ(string message);
        string  ZZaString(ZZ num);
        ZZ restoChino(ZZ);
        //Funcionnes para el RSA
        ZZ modulo(ZZ,ZZ);
        int mod(int,int);
        ZZ Binary_GCD(ZZ,ZZ);
        ZZ Binary_GCD_EXT(ZZ,ZZ);
        ZZ exponencial(ZZ,ZZ,ZZ);
        ZZ mcdExtendido(ZZ,ZZ);
        ZZ C_Publica,n;
        void show();

    private:
        ZZ p;
        ZZ q;
        ZZ fiN;
        ZZ C_Privada;


        string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";


};

#endif // RSA_H
