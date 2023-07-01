#include<iostream>
#include<stdlib.h>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<conio.h>
#include <cstring>
//TENGO ESTAS BIBLOTECAS POR DEFECTO EN MI CODE, LAS DEJO PARA NO BORRAR Y HACER MACANA :)

using namespace std;
#include "parcial1.h"

class Componente_Mayor
{
private:
    int codigo;
    char nombre[30];
    Fecha fechaUltimaCompra;

public:
    int getCodigo(){return codigo;}
    const char *getNombre(){return nombre;}
    Fecha getFecha(){return fechaUltimaCompra;}


    void setCodigo(int cm){codigo=cm;}
    void setNombre(const char *m){strcpy(nombre,m);}
    void setFecha(Fecha ultima){fechaUltimaCompra=ultima;}
};

class ArchivoPunto1
{
private:
    char nombre[30];

public:
         ArchivoPunto1(const char *n){
         strcpy(nombre, n);
         }

        bool escribirRegistro(Componente_Mayor reg){
            FILE *p;
            p=fopen(nombre, "ab");
            if(p==NULL) return false;
            bool escribio = fwrite(&reg, sizeof reg, 1, p);
            fclose(p);
            return escribio;
    }
};


void Punto1_resolucion();
void Punto2_resolucion();


int main(){

Punto1_resolucion();
system("pause");
cout<<endl;
Punto2_resolucion();
system("pause");


return 0;

}

void Punto1_resolucion(){

    ArchivoComponente obj("componentes.dat");
    Componente reg;
    Componente_Mayor aux;
    ArchivoPunto1 arc("punto1.dat");

    int cant = obj.contarRegistros();

    for(int i=0; i<cant; i++)
        {
            reg = obj.leerRegistro(i);
            if((reg.getPU() > 50000)&& (reg.getTipo() == 6) && (reg.getActivo() == true))
            {
                aux.setCodigo(reg.getCodigo());
                aux.setNombre(reg.getNombre());
                aux.setFecha(reg.getFecha());
                arc.escribirRegistro(aux);
            }
        }
}


void Punto2_resolucion()
{
    ArchivoComponente obj("componentes.dat");
    Componente reg;

    int cant = obj.contarRegistros();
    int comp[6]={0};

    for(int i=0; i<cant; i++)
    {
        reg = obj.leerRegistro(i);

        if(reg.getActivo() == true){
        comp[reg.getTipo()-1]++;
        }
    }

    for(int i=0;i<6;i++){
        if(comp[i] < 2){
        cout<<"TIPO: "<<i+1<<" TIENE MENOS DE DOS COMPONENTES"<<endl;
        }
    }
}
