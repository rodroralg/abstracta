#include <iostream>


#include <NTL/ZZ.h>
using namespace NTL;

#include <stdlib.h>
#include <time.h>
#include <string>
#include <math.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include "RSA.h"


string leer(string nombre)
{
    ifstream lectura;
    lectura.open( nombre+".txt",ios::binary );

    string mensaje, linea;
    while(getline(lectura,linea))
        mensaje+=linea;

    cout << linea << endl;
    lectura.close();

    return mensaje;
}

void escribir(string nombre, string mensaje)
{
    ofstream escritura;
    escritura.open( nombre+".txt",ios::binary );
    escritura<<mensaje;

    escritura.close();
}


int main()
{

///cifrado bloques
/*
    string x="hola123";

    RSA a(8);
    cout << "P: " << a.P << endl;
    cout << "Q: " << a.Q << endl;

    cout << "N: " << a.N << endl;

    cout << "phiN: " << a.phiN << endl;
    cout << "Publica :" << a.clavPublica << "\n" << endl;
    cout << "Privada :" << a.clavPrivada << "\n" << endl;

    string cifbloq=a.cifradobloques(x,a.clavPublica,a.N);
    cout << "mensaje cifrado:" << endl;
    cout << cifbloq << "\n" << endl;

    string decif=a.descifrado(cifbloq);
    cout << "mensaje descifrado:" << endl;
    cout << decif << endl;
*/

////

//
//    ZZ p,q,clavpriv;
//
//    p=143514251661041087021956818435834569329978567314318685307630523791297526718368578544270524810700544795263941355978963744934959014860854725287853008559074386356127036740729895490088437846403204725930146597449176023582071202160017173181755825902069113812655014854275152654701751775586138083057988956812976979853;
//    q=163172365676725106012345175874638648436677536444434312060395208456910677065904491255089648545327446278892879719334146904855960262616939972370563912861009899390464317037057144246903274299131522284011526142495182049167338581298689472817855915970128982188462155494489315027720283135488232656400016842825240030331;
//    clavpriv=16705050377351687322631020967881642222473027303149283595799931828196169595278701007065571770095766356413000974440157922646312533904086285437722244006039144869215442926374251834963814012511277923292613306835429086676680820853926686784592526579296509597073936528650002481094087591691295231870582561439388758868976615020256927613257777895015793746363606944184038275078934139611352663601399196772177870656517373373759658647117921033658736536300911668417825723770673345020339469004642414595861124805762822142039517318434819890230937142067737125922120726753346988322815887802003728589974514132026912957925530746488471991627;
//
//    RSA d(p,q,clavpriv);
//
//    string de="21834365375682456110164819547190460475775482716717048640062937857107577625573772754659396512622689098022186871935859825730112814011611442718440333090381213374530534906988021409144767694186456124700872894777815152018784912495183540980398190772595186904889634541376088803252795202195744749678376007602681124031822488892581379563889968845118547756272588524039930385291246477401180528230472805960665432838319908537171322379119561425946929972236985139888151608540890310000100410891183896972128325725241987406005927972990562263745470754405256612101136013097156041009835656088795730450139061294065252375892024386465961988466";
//    string decif=d.descifrado(de);
//    cout << "mensaje descifrado:" << endl;
//    cout << decif << endl;



///numeros primos robustos, que sean dificiles de ser factorizados

/*
    RSA a(8);

int opcion;
    do{
       system("cls");
       cout <<"1. Encriptar: "<<endl;
       cout <<"2. Descencriptar:"<<endl;
       cout <<"3. Claves"<<endl;
       cout <<"4. Salir:"<<endl;
       cout <<"opcion: ";
       cin>>opcion;

       switch(opcion){
           case 1:{
               ZZ e_,n_;
               string msg;
               cout <<"ingrese e:";cin>>e_;
               cout <<"ingrese n:";cin>>n_;
               RSA mo(e_,n_);
               cout<<"ingrese mensaje: ";
               cin.get();getline(cin,msg);
               string cif=a.cifradobloques(msg,mo.clavPublica,mo.N);
               cout <<"mensaje encriptado: " << cif << endl;
               system("pause");
               break;
           }
           case 2:{
                string msg;
                cout<<"ingrese mensaje: ";
                cin.get();getline(cin,msg);
                string decif=a.descifrado(msg);
                cout << decif << endl;
                system("pause");
                break;
           }
           case 3:
            system("cls");
            cout << "claves de a :" << endl;
//            cout <<"clave privada: "<<a.clavPrivada<<endl;
            cout <<"clave publica: "<<a.clavPublica<<endl;
            cout <<"modulo n: "<<a.N<<endl;
            cin.get();
            getchar();
            system("pause");
            break;

        }
        system("pause");
    }while(opcion!=4);
*/

///************************************************

    RSA a(1024);

int opcion;
    do{
       system("cls");
       cout <<"1. Encriptar: "<<endl;
       cout <<"2. Descencriptar:"<<endl;
       cout <<"3. Claves"<<endl;
       cout <<"4. Salir:"<<endl;
       cout <<"opcion: ";
       cin>>opcion;

       switch(opcion){
           case 1:{
               ZZ e_,n_;
               string msg;
               cout <<"ingrese e:";cin>>e_;
               cout <<"ingrese n:";cin>>n_;
               RSA mo(e_,n_);
               cout<<"ingrese mensaje: ";
               msg=leer("Texto_Original");
               string cif=mo.cifradobloques(msg,mo.clavPublica,mo.N);
               cout <<"mensaje encriptado: " << cif << endl;
               escribir("Texto_Cifrado",cif);
               system("pause");
               break;
           }
           case 2:{
                cout<<"ingrese mensaje: ";
                cout << "clavpriv:" << a.clavPrivada << endl;

                string decif=a.descifrado(leer("Texto_Cifrado"));
                cout << "mensaje desencriptado: " << endl;
                cout << decif << endl;
                escribir("Texto_Descifrado", decif);
                system("pause");
                break;
           }
           case 3:
            system("cls");
            cout << "claves de a :" << endl;
            cout <<"clave privada: "<<a.clavPrivada<<endl;
            cout <<"clave publica: "<<a.clavPublica<<endl;
            cout <<"modulo n: "<<a.N<<endl;
            cin.get();
            getchar();
            system("pause");
            break;

        }
        system("pause");
    }while(opcion!=4);






}
