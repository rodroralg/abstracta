#include "RSA.h"

RSA::RSA(int bit)
{
    while(p==q){
    GenPrime(p,bit);
    GenPrime(q,bit);
    }
    n=p*q;
    fiN=(p-1)*(q-1);
    Gen_Claves();
}
RSA::RSA(ZZ CP,ZZ N){
    C_Publica=CP;
    n=N;

}
string RSA::EstandarizarBloquesAlfabeto(string M,int op){
    string BloquesAlfabeto;
    if(op==1)
    {for(int i=0;i<M.size();i++){
       ZZ C = conv<ZZ>(alfabeto.find(M[i]));
       if(C<10)
            BloquesAlfabeto+=Estandarizar(ZZaString(C),2);
       else
            BloquesAlfabeto+=ZZaString(C);
    }
    return BloquesAlfabeto;
    }
    if(op==2)
    {for(int i=0;i<M.size();i++){
       ZZ C = conv<ZZ>(static_cast<int>(M[i]));
       if(C<100)
            BloquesAlfabeto+=Estandarizar(ZZaString(C),3);
       else
            BloquesAlfabeto+=ZZaString(C);
    }
    return BloquesAlfabeto;
    }
}

string RSA::cifrar(string M,int op){

    string BloquesAlfabeto=EstandarizarBloquesAlfabeto(M,op);
    string BloquesCifrado=CifrarBloques(BloquesAlfabeto,C_Publica,n,op);
    //cout<<"Estanderizado en boques de 2: "<<BloquesAlfabeto<<endl;
    //cout<<BloquesCifrado<<endl;
    return BloquesCifrado;
}
string RSA::CifrarBloques(string BloquesAlfabeto,ZZ CP,ZZ N,int op){
    string BloquesCifrado;
    string aux,C;
    string Tan = ZZaString(N);
    int Tan_N = Tan.size();
    int veri = Tan_N;
    int tan_Bloque;
    //Para alf o ascci
    cout<<"tam_N: "<<Tan_N<<endl;
    if(op==1){
        if(Tan_N%2!=0){Tan_N-=1;}
        tan_Bloque=2;
    }
    if(op==2){
        tan_Bloque=mod(Tan_N,3);
        Tan_N=Tan_N-tan_Bloque;
    }
    cout<<"tam_N: "<<Tan_N<<endl;
    while(BloquesAlfabeto.size()){
        cout<<"BloquesAlfabeto.size()"<<BloquesAlfabeto.size()<<endl;
        aux = BloquesAlfabeto.substr(0,Tan_N);
        if(StringaZZ(aux)<N){
            cout<<"Bloques: "<<aux<<endl;
            C=ZZaString(exponencial(StringaZZ(aux),CP,N));
            BloquesCifrado+=Estandarizar(C,veri);
            cout<<"Cifrado: "<<Estandarizar(C,veri)<<endl;
            BloquesAlfabeto.erase(0,Tan_N);

        }else{
            aux = BloquesAlfabeto.substr(0,Tan_N-tan_Bloque);
            cout<<"Bloques: "<<aux<<endl;
            C=ZZaString(exponencial(StringaZZ(aux),CP,N));
            BloquesCifrado+=Estandarizar(C,veri);
            cout<<"Cifrado: "<<Estandarizar(C,veri)<<endl;
            BloquesAlfabeto.erase(0,Tan_N-tan_Bloque);
        }
        cout<<"BloquesCifrado.size()"<<BloquesCifrado.size()<<endl;
    }
    cout<<"BloquesCifrado"<<BloquesCifrado<<endl;
    return BloquesCifrado;
}
string RSA::descifrar(string C,int op){
    string Bloques_Descifrados;
    string Descifrado;
    string aux;
    string tam_N = ZZaString(n);
    cout<<"C.size()"<<C.size()<<endl;
    cout<<"C."<<C<<endl;
    int Tan_N = tam_N.size();
    int veri = Tan_N;
    int tam_Bloque;
    cout<<"tam_N: "<<Tan_N<<endl;
    if(op==1){
        if(Tan_N%2!=0){
            veri-=1;
            tam_Bloque=2;
        }
    }
    if(op==2){
        tam_Bloque=3;
        veri=Tan_N-mod(Tan_N,3);
    }
    cout<<"tam_N: "<<Tan_N<<endl;
    //cout<<C<<endl;
    while(C.size()){
        cout<<"C.size()"<<C.size()<<endl;
        if(C.size()==Tan_N){
            aux = C.substr(0,Tan_N);
            //cout<<"Bloque: "<<aux<<endl;

            //string RP=ZZaString(exponencial(StringaZZ(aux),C_Privada,n));
            string RP=ZZaString(restoChino(StringaZZ(aux)));
            //cout<<"Descifra: "<<RP<<endl;
            Bloques_Descifrados+=Estandarizar(RP,veri);
            C.erase(0,Tan_N);
        }
        else{
            aux = C.substr(0,Tan_N);
            //cout<<"Bloque: "<<aux<<endl;
            //string RP=ZZaString(exponencial(StringaZZ(aux),C_Privada,n));
            string RP=ZZaString(restoChino(StringaZZ(aux)));
            //cout<<"Descifra: "<<RP<<endl;
            Bloques_Descifrados+=Estandarizar(RP,veri);
            //Bloques_Descifrados+=RP;
            C.erase(0,Tan_N);}
    }

    //cout<<Bloques_Descifrados<<endl;
    if(op==1){
    while(Bloques_Descifrados.size()){
        aux = Bloques_Descifrados.substr(0,tam_Bloque);
        int num = atoi(aux.c_str());
        //cout<<num<<endl;
        if(StringaZZ(aux)!=0&&StringaZZ(aux)>0){
            Descifrado+=alfabeto[num];
            Bloques_Descifrados.erase(0,tam_Bloque);
        }
    }
    }
    if(op==2){
    while(Bloques_Descifrados.size()){
        aux = Bloques_Descifrados.substr(0,tam_Bloque);
        int num = atoi(aux.c_str());
        //cout<<num<<endl;
        if(StringaZZ(aux)!=0){
            Descifrado+=static_cast<char>(num);

        }
        Bloques_Descifrados.erase(0,tam_Bloque);
    }}

    return Descifrado;
}

string RSA::Estandarizar(string cifra,int tamN){
    int Num_0 = tamN-cifra.size();
    //cout<<tamN<<"-"<<Num_0<<endl;
    return cifra.insert(0,Num_0,'0');
}
string  RSA::ZZaString(ZZ num){
    stringstream temp;
    temp << num;
    return temp.str();
}
ZZ RSA::StringaZZ(string message){
    stringstream temp(message);
    ZZ number; temp >> number;
    return number;
}
void RSA::Gen_Claves(){
    bool mcd=true;
    while(mcd){
        RandomBnd(C_Publica,fiN);
        if(Binary_GCD(C_Publica,fiN)==1 && C_Publica>1)
            mcd=false;
    }

    C_Privada = Binary_GCD_EXT(C_Publica,fiN);
    C_Privada = modulo(C_Privada,fiN);}
ZZ RSA::modulo(ZZ numero,ZZ mod){
    ZZ num = numero-(numero/mod)*mod;
    return (num>=0) ? num:(num+mod);}
ZZ RSA::Binary_GCD(ZZ a,ZZ b){

    ZZ i;
    i=0;
    ZZ c;
	if(a==0) return b;
	if(b==0) return a;
	i++;
	while(((a|b)&1)==0){
		c++;
		a>>=1;
		b>>=1;i++;}
	while((a&1)==0) {a>>=1;i++;}
	while(b!=0){
		while((b&1)==0) {b>>=1;i++;}
		if(a>b) swap(a,b);
		b-=a;i++;}

	return a<<conv<int>(c);}
ZZ RSA::Binary_GCD_EXT(ZZ x1, ZZ y1){
    ZZ x,y;
    x=x1;
    y=y1;
	ZZ g,u,v,A,B,C,D;
	g=1;
	while(x%2==0 && y%2==0){
		x/=2;y/=2;g*=2;}
	u=x;v=y;A=1;B=0;C=0;D=1;
	while(u!=0){
		while(u%2==0){
			u/=2;
			if(A%2==0 && B%2==0){
				A/=2;B/=2;}
			else{
				A=(A+y)/2;B=(B-x)/2;}}
		while(v%2==0){
			v/=2;
			if(C%2==0 && D%2==0){
				C/=2;D/=2;}
			else{
				C=(C+y)/2;D=(D-x)/2;}}
		if(u>=v){
			u-=v;A-=C;B-=D;}
		else{v-=u;C-=A;D-=B;}
	}
	//cout<<C<<"*"<<x1<<"+"<<D<<"*"<<y1<<"="<<g*v<<endl;
	return C;}
ZZ RSA::exponencial(ZZ base,ZZ expo, ZZ mod){
    ZZ cont;
    cont=1;
    ZZ enter;
    enter=2;
    while(expo!=0){
        if(modulo(expo,enter)==1){
            cont=modulo(cont*base,mod);
        }
        base=modulo(base*base,mod);
        expo=expo/enter;
    }
    return cont;}
int RSA::mod(int numero, int modulo){
    int num = numero-(numero/modulo)*modulo;
    return (num>=0) ? num:(num+modulo);}
void RSA::show(){
    cout<<"Clave Publica: "<<C_Publica<<endl;
    cout<<"Clave Privada: "<<C_Privada<<endl;
    cout<<"N: "<<n<<endl;
    cout<<"p: "<<p<<endl;
    cout<<"q: "<<q<<endl;
}
ZZ RSA::restoChino(ZZ pos){
    ZZ dp,dq;
    Chino arrChino[1];
    dp=modulo(C_Privada,p-1);
    dq=modulo(C_Privada,q-1);

    arrChino[0].a = exponencial(pos,dp,p);
    arrChino[1].a = exponencial(pos,dq,q);

    arrChino[0].M = n/p;
    arrChino[1].M = n/q;

    arrChino[0].Mi=Binary_GCD_EXT(arrChino[0].M,p);
    arrChino[1].Mi=Binary_GCD_EXT(arrChino[1].M,q);

    ZZ res;
    res=0;
    res+=modulo(arrChino[0].a * arrChino[0].M * arrChino[0].Mi,n);
    res+=modulo(arrChino[1].a * arrChino[1].M * arrChino[1].Mi,n);
    //cout<<res<<endl;
    res=modulo(res,n);
    return res;

}
