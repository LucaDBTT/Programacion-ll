#include<iostream>
#include<cstring>

using namespace std;
#include "parcial2.h"

class Punto1
{
private:
    int codigoRestaurante;
    char nombre[30];
    float importeTotal;
    bool estado;

public:
    int getCodigoRestaurante(){return codigoRestaurante;}
    const char *getNombre(){return nombre;}
    float getImporte(){return importeTotal;}
    bool getEstado(){return estado;};

    void setCodigoRestaurante(int cod){codigoRestaurante=cod;}
    void setNombre(const char* n) {strcpy(nombre, n);}
    void setImporte(float imp){importeTotal=imp;}
    void setEstado(bool est){estado=est;}

    void Cargar(int cod, const char *nom, float imp, bool est){
    setCodigoRestaurante(cod);
    setNombre(nom);
    setImporte(imp);
    setEstado(true);
    }
    void Mostrar(){
    cout<<codigoRestaurante<<endl;
    cout<<nombre<<endl;
    cout<<importeTotal<<endl;
    }

};

class ArchivoPunto1
{
private:
    char nombre[30];

public:
         ArchivoPunto1(const char *n){
         strcpy(nombre, n);
         }
        bool escribirRegistro(Punto1 reg){
            FILE *p;
            p=fopen(nombre, "ab");
            if(p==NULL) return false;
            bool escribio = fwrite(&reg, sizeof reg, 1, p);
            fclose(p);
            return escribio;
        }
        int contarRegistros(){
            FILE *p;
            p=fopen(nombre, "rb");
            if(p==NULL) return -1;
            fseek(p, 0,2);
            int tam=ftell(p);
            fclose(p);
            return tam/sizeof(Punto1);
        }
        Punto1 leerRegistro(int pos){
            Punto1 reg;
            reg.setNombre("NONE");
            FILE *p;
            p=fopen(nombre, "rb");
            if(p==NULL) return reg;
            fseek(p, sizeof reg*pos,0);
            fread(&reg, sizeof reg,1, p);
            fclose(p);
            return reg;
        }
        bool listarArchivo(){
        Punto1 reg;
        FILE *p;
        p = fopen(nombre, "rb");
        if (p == NULL){
        cout << "No se pudo abrir " << endl;
        return false;
        }
        while (fread(&reg, sizeof reg, 1, p)==1 ){
        reg.Mostrar();
        cout << endl;
        }
        fclose(p);
        return true;
        }
};


void Punto1Resolucion();
void Punto2Resolucion();

int main(){


Punto1Resolucion();
system("pause");
system("cls");
Punto2Resolucion();
system("pause");
system("cls");


return 0;

}


void Punto1Resolucion()
{
    Restaurante res;
    ArchivoRestaurantes Ares("restaurantes.dat");

    Venta ven;
    ArchivoVentas Aven("ventas.dat");

    Punto1 reg;
    ArchivoPunto1 Areg("punto1.dat");

    int cantidadRestaurantes = Ares.contarRegistros();
    int cantidadVentas = Aven.contarRegistros();
    float* importeTotal = new float[cantidadRestaurantes]{};

    if(importeTotal == nullptr){
    cout<<"error"<<endl;
    return;
    }

    for(int i=0; i<cantidadRestaurantes;i++){

    res = Ares.leerRegistro(i);

        for(int j=0;j<cantidadVentas;j++){

            ven = Aven.leerRegistro(j);
            if((res.getCodigoRestaurante() == ven.getCodigoRestaurante()) && (res.getCategoria() == 3) && (ven.getFechaReserva().getAnio() == 2023) && (res.getEstado() && ven.getEstado())){
            importeTotal[i] += ven.getImporte();
            }
        }

    if(res.getCategoria() == 3 && res.getEstado()){ //SOLO GUARDO LOS RESTAURANTES DE CATEGORIA 3 Y DADOS DE ALTA
    reg.Cargar(res.getCodigoRestaurante(), res.getNombre(), importeTotal[i], true); //SETEO EL ESTADO DIRECTAMENTE EN TRUE PORQUE DICHA VALIDACION YA LA HAGO EN EL IF
    Areg.escribirRegistro(reg);
    }

    }

    Areg.listarArchivo();

delete importeTotal;
}


void Punto2Resolucion()
{

    Restaurante res;
    ArchivoRestaurantes Ares("restaurantes.dat");

    int cantidadRestaurantes = Ares.contarRegistros();
    int provincias[24]{};

    for(int i=0;i<cantidadRestaurantes;i++){

        res = Ares.leerRegistro(i);

        if((res.getCategoria() == 3) && (res.getEstado())){
            provincias[res.getProvincia()-1]++;
        }

    }

    cout<<"LAS PROVINCIAS CON MENOS DE 3 RESTAURANTES DE LA CATEGORIA 3 SON: "<<endl;
    for(int j=0;j<24;j++){
        if(provincias[j] < 3){
        cout<<"PROVINCIA: "<<j+1<<endl;
        }
    }
}
