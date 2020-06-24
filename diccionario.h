#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_

#include "listaInt.h"
#include <iostream>
#include <fstream>

struct NodoABBD;
typedef int clave;
typedef int valor;
using namespace std;

class diccionario
{
    public:

    diccionario();
    bool contieneclave(clave k)const;
    valor buscarvalor(clave k)const;
    void definir(clave k, valor v);
    void indefinir(clave k);
    void unircon(const diccionario& d2);
    void intersecarcon( const diccionario& d2);
    int cantclaves()const;
    listaInt claves()const;
    listaInt valores()const;
    bool iguales(diccionario& d2)const;
    void borrar_diccionario();
    diccionario& operator=(const diccionario& d);
    diccionario(const diccionario& d);
    ~diccionario();
    friend ostream&
        operator<<(ostream& f,const diccionario& d);
    friend istream&
        operator>>(istream& is, diccionario& d);

    private:

    int cantidad;
    NodoABBD* arbol;

    bool contieneclave_aux
        (const NodoABBD* raiz,clave k)const;
    valor buscarvalor_aux
        (const NodoABBD* raiz,clave k)const;
    NodoABBD* definir_aux
        (NodoABBD* raiz,clave k, valor v);
    NodoABBD* indefinir_aux(NodoABBD* raiz,clave k);
    NodoABBD* unircon_aux
        (NodoABBD* raiz1, const NodoABBD* raiz2);
    NodoABBD* intersecarcon_aux
        (NodoABBD* raiz, const NodoABBD* raiz2);
    void claves_aux
        (NodoABBD* raiz,listaInt& _claves)const;
    void valores_aux
        (NodoABBD* raiz,listaInt& _valores)const;
    NodoABBD* borrar_diccionario_aux(NodoABBD* raiz);

};

#endif
