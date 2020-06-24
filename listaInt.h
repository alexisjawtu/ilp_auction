#ifndef _LISTAINT_H_
#define _LISTAINT_H_

struct NodoBi;
#include <iostream>
#include <fstream>
using namespace std;

class listaInt
{
    public:

    int tam()const;
    int iesimo(int i)const;
    listaInt();
    void ag_adelante(int x);
    void ag_atras(int x);
    void sin_primero();
    void sin_ultimo();
    void agregarle(const listaInt& l2);
    listaInt copiar()const;
    bool iguales(const listaInt& l2);
    void borrar_Lista();
    listaInt& operator=(const listaInt& l);
    listaInt(const listaInt& l);
    ~listaInt();
    friend ostream&
        operator<<(ostream& f,const listaInt& l);
    friend istream&
        operator>>(istream& is, listaInt& l);

    private:

    int cantidad;
    NodoBi* primero;
    NodoBi* ultimo;

};

#endif
