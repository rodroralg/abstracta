#include <iostream>
#include <RSA.h>
#include <NTL/ZZ.h>
#include <sstream>
#include <cstdlib>
#include <fstream>
using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#endif

string leer(string name)
{
    ifstream lectura;
    lectura.open( name+".txt", ios::binary );

    string sms, linea;

    while(getline(lectura, linea))
        sms += linea;

    cout << linea<<endl;
    lectura.close();
    return sms;
}

void escribir(string name,string sms)
{
    ofstream escritura;
    escritura.open( name+".txt", ios::binary );
    escritura<<sms;

    escritura.close();
}

int main()
{

    RSA emisor(1024);
    emisor.show();
    bool sesion = true;
    int op = 0;
    while(sesion){
        cout<<"Opcion 1 -> Cifrar"<<endl;
        cout<<"Opcion 2 -> Descifrar"<<endl;
        cout<<"Opcion 3 -> Mostrar Claves"<<endl;
        cout<<"Opcion 4 -> Cerrar sesion"<<endl;
        cout<<"Opcion 5 -> Resto Chino"<<endl;
        cout<<"Ingrese la opcion: ";cin>>op;
        switch(op){
            case 1:{
                ZZ CP,N;
                string sms;
                int op;
                cout<<"Ingrese CP: ";cin>>CP;
                cout<<"Ingrese N: ";cin>>N;
                RSA receptor(CP,N);
                cout<<"Opcion 1 -> ALF: "<<endl;
                cout<<"Opcion 2 -> ASCII: "<<endl;
                cout<<"Ingresa opcion: ";cin>>op;
                /*cout<<"Ingresa mensaje: ";getline(cin,sms);
                getline(cin,sms);*/
                sms = leer("Texto_Original");
                string C = receptor.cifrar(sms,op);
                cout<<"Cifrado: "<<C<<endl;
                escribir("Texto_Cifrado",C);
                system("PAUSE");
                break;
            }
            case 2:{
                string sms;
                int op;
                cout<<"Opcion 1 -> ALF: "<<endl;
                cout<<"Opcion 2 -> ASCII: "<<endl;
                cout<<"Ingresa opcion: ";cin>>op;
                /*cout<<"Ingresa mensaje: ";getline(cin,sms);
                getline(cin,sms);*/
                sms = emisor.descifrar(leer("Texto_Cifrado"),op);
                cout<<"Descifrado: "<<sms<<endl;
                escribir("Texto_Descifrado",sms);

                system("PAUSE");
                break;
            }
            case 3:{
                emisor.show();
                system("PAUSE");
                break;
            }
            case 4:{
                sesion=false;
                break;
            }
            case 5:{
                ZZ aux;
                cout<<"Resto: "<<aux<<endl;
                system("PAUSE");
                break;
            }


        }system(CLEAR);


    }


    return 0;

}
