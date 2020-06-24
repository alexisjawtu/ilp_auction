#include "listaInt.h"
#include "diccionario.h"
#include <cstdlib>


struct NodoABBD
{
    int clave;
    int valor;
    NodoABBD* derecho;
    NodoABBD* izquierdo;
};

diccionario::diccionario()
{
    this->cantidad=0;
    this->arbol=NULL;
}
bool diccionario::contieneclave_aux
    (const NodoABBD* raiz,clave k)const
{
    if (raiz==NULL)
    {
        return false;
    }
    else if((raiz->clave) == k)
    {
        return true;
    }
    else if((raiz->clave) < k)
    {
        return this->
                contieneclave_aux(raiz->derecho,k);
    }
    else
    {
        return this->
                contieneclave_aux(raiz->izquierdo,k);
    }
}

bool diccionario::contieneclave(clave k)const
{
    return this->contieneclave_aux(this->arbol ,k);
}

valor diccionario::buscarvalor_aux
            (const NodoABBD* raiz,clave k)const
{
     if(raiz!=NULL)
     {
        if ((raiz->clave) == k)
        {
            return raiz->valor;
        }
        else
        {
            if((raiz->clave) < k)
            {
                return buscarvalor_aux
                            (raiz->derecho,k);
            }
            else
            {
                return buscarvalor_aux
                            (raiz->izquierdo,k);
            }
        }
     }
     return 0;
}

valor diccionario::buscarvalor(clave k)const
{
   return buscarvalor_aux(this->arbol,k);
}

NodoABBD* diccionario::definir_aux
                (NodoABBD* raiz,clave k, valor v)
{
    if(raiz == NULL)
    {
        raiz=new NodoABBD ;
        raiz->clave = k;
        raiz->valor = v;
        raiz->izquierdo = NULL;
        raiz->derecho = NULL;
        (this->cantidad)++;
    }
    else if((raiz->clave)< k)
    {
       raiz->derecho=definir_aux(raiz->derecho,k,v);
    }
    else if((raiz->clave) > k)
    {
        raiz->izquierdo=definir_aux
                            (raiz->izquierdo,k,v);
    }
    else
    {
        raiz->valor=v;
    }
    return raiz;
}

void diccionario::definir(clave k, valor v)
{
   this->arbol=definir_aux(this->arbol,k,v);
   return;
}

NodoABBD* diccionario::indefinir_aux
                        (NodoABBD* raiz,clave k)
{
    if(raiz!=NULL)
    {
        if(contieneclave_aux(raiz,k) == 1)
        {
            if(raiz->clave < k)
            {
               raiz->derecho=indefinir_aux
                                (raiz->derecho,k);
            }
            else if(raiz->clave > k)
            {
                raiz->izquierdo=indefinir_aux
                                (raiz->izquierdo,k);
            }
            else
            {
                if(raiz->derecho==NULL)
                {
                    NodoABBD* nodo_a_extraer = raiz;
                    raiz = raiz->izquierdo;
                    nodo_a_extraer->izquierdo = NULL;
                    delete nodo_a_extraer;
                    (this->cantidad)--;
                }

                else
                {
                    NodoABBD* nodominimo=
                                    raiz->derecho;
                    while(nodominimo->
                                    izquierdo!=NULL)
                    {
                        nodominimo=nodominimo->
                                           izquierdo;
                    }
                    raiz->clave=nodominimo->clave;
                    raiz->valor=nodominimo->valor;
                    raiz->derecho=indefinir_aux
                       (raiz->derecho,
                                nodominimo->clave);
                }
            }
        }
    }

    return raiz;
}

void diccionario::indefinir(clave k)
{
    this->arbol=indefinir_aux(this->arbol,k);
}

NodoABBD* diccionario::unircon_aux
            (NodoABBD* raiz1, const NodoABBD* raiz2)
{
    if(raiz2 != NULL)
    {
        if(contieneclave_aux(raiz1,raiz2->clave) == 0)
        {
            raiz1=definir_aux
                   (raiz1,raiz2->clave,raiz2->valor);
        }

        raiz1=unircon_aux(raiz1,raiz2->derecho);
        raiz1=unircon_aux(raiz1,raiz2->izquierdo);
    }
    return raiz1;
}

void diccionario::unircon(const diccionario& d2)
{
    this->arbol=unircon_aux(this->arbol,d2.arbol);
}

int diccionario::cantclaves()const
{
    return this->cantidad;
}

NodoABBD* diccionario::intersecarcon_aux
            (NodoABBD* raiz1, const NodoABBD* raiz2)
{
    if(raiz1 != NULL && raiz2 != NULL)
    {
       if(contieneclave_aux(raiz2,raiz1->clave)==0)
       {
           raiz1=indefinir_aux(raiz1,raiz1->clave);
           raiz1=intersecarcon_aux(raiz1,raiz2);
       }
       else
       {
           raiz1->derecho=intersecarcon_aux
                            (raiz1->derecho,raiz2);
           raiz1->izquierdo=intersecarcon_aux
                          (raiz1->izquierdo,raiz2);
       }
    }
    return raiz1;
}

void diccionario::intersecarcon
                            (const diccionario& d2)
{
    this->arbol=intersecarcon_aux
                            (this->arbol, d2.arbol);
}

void diccionario::claves_aux
            (NodoABBD* raiz, listaInt& _claves)const
{

    if(raiz!=NULL)
    {
        claves_aux(raiz->izquierdo,_claves);
        _claves.ag_atras(raiz->clave);
        claves_aux(raiz->derecho,_claves);
        return;
    }

}

listaInt diccionario::claves()const
{
    listaInt lista_claves;
    claves_aux(this->arbol,lista_claves);
    return lista_claves;
}

void diccionario::valores_aux
            (NodoABBD* raiz, listaInt& _valores)const
{
    if(raiz!=NULL)
    {
        valores_aux(raiz->izquierdo,_valores);
        _valores.ag_atras(raiz->valor);
        valores_aux(raiz->derecho,_valores);
        return;
    }
}

listaInt diccionario::valores()const
{
    listaInt lista_valores;
    valores_aux(this->arbol,lista_valores);
    return lista_valores;
}

bool diccionario::iguales(diccionario& d)const
{
    return(this->cantidad==d.cantidad &&
        this->claves().iguales(d.claves()) &&
        this->valores().iguales(d.valores()));
}

NodoABBD* diccionario::borrar_diccionario_aux
                                    (NodoABBD* raiz)
{
    while (raiz != NULL)
    {
        raiz = indefinir_aux(raiz, raiz->clave);
    }
    return raiz;
}

void diccionario::borrar_diccionario()
{
    this->arbol = borrar_diccionario_aux
                                    (this->arbol);
    return;
}

NodoABBD* copiar_arbol(const NodoABBD* raiz)
{
    if(raiz == NULL)
    {
        return NULL;
    }
    else
    {
        NodoABBD* copia = new NodoABBD;
        copia->clave = raiz->clave;
        copia->valor = raiz->valor;
        copia->derecho = copiar_arbol(raiz->derecho);
        copia->izquierdo = copiar_arbol
                                   (raiz->izquierdo);
        return copia;
    }
}

diccionario& diccionario::operator=
                               (const diccionario& d)
{
    (*this).borrar_diccionario();
    this->arbol = copiar_arbol(d.arbol);
    this->cantidad = d.cantidad;
    return *this;
}

diccionario::diccionario(const diccionario& d)
{
    this->cantidad = 0;
    this->arbol = NULL;
    *this = d;
}

diccionario::~diccionario()
{
    (*this).borrar_diccionario();
}

ostream& operator<<(ostream& f,const diccionario& d)
{
    listaInt l_claves=d.claves();
    listaInt l_valores=d.valores();
    if(d.cantidad != 0)
    {
        f<<"[("<< l_claves.iesimo(0)<<","
                        <<l_valores.iesimo(0)<<")";
    }
    for( int i=1;i<d.cantidad;i++)
    {
        f<<";("<< l_claves.iesimo(i)<<","
                        <<l_valores.iesimo(i)<<")";
    }
    f<<']';
    return f;
}

istream& operator>>(istream& is, diccionario& d)
{
    d.~diccionario();
    is.get();
    char c = is.peek();
    while( c != ']')
    {
        clave x = 0;
        is >> x;
        valor y = 0;
        is >> y;
        is.get();
        d.definir(x,y);
        c = is.peek();
        if(c == ',')
        {
            is.get();
        }
    }
    return is;
}
