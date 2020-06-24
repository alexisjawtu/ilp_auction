#include <iostream>
#include "listaInt.h"
#include "diccionario.h"
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int main()
{
    diccionario cv_c;
    cv_c.definir(0,0);
    ifstream h("cv_c.txt");
    h>>cv_c;

    diccionario ta_c_2;
    ta_c_2.definir(0,0);
    ifstream k("ta_c_2.txt");
    k>>ta_c_2;

    diccionario tc_c_2_a;
    tc_c_2_a.definir(0,0);
    ifstream m("tc_c_2_a.txt");
    m>>tc_c_2_a;

    diccionario tmx_f_2;
    tmx_f_2.definir(0,0);
    ifstream q("tmx_f_2.txt");
    q>>tmx_f_2;

    cout<<endl<<"Prueba ta_c_2"<<endl<<ta_c_2;
    cout<<endl<<"Prueba tc_c_2_a"<<endl<<tc_c_2_a;
    cout<<endl<<"Prueba tmx_f_2"<<endl<<tmx_f_2;

    diccionario reg;
    for (int i = 1; i < 710; i++)
    {
      int etiqueta_i = 8*(cv_c.contieneclave(i)) +
      4*(ta_c_2.contieneclave(i)) +
      2*(tc_c_2_a.contieneclave(i)) +
      1*(tmx_f_2.contieneclave(i));
        reg.definir(i, etiqueta_i);
    }

    vector < pair<int , int > > A;
    int long_ = (reg.claves()).tam();
    for(int i = 0; i < long_; i++)
    {
        A.push_back(make_pair((reg.valores()).
            iesimo(i),(reg.claves()).iesimo(i)));
    }
    sort(A.begin(),A.end());
    ofstream regiones;
    regiones.open("regiones.txt");
    int _count_ = 1;
    listaInt _cantidades_;
    vector < string > S;
    S.push_back("ta_c_2");
    S.push_back("tc_c_2_a");
    S.push_back("tmx_f_2");
    string reg_ ("");
    int temp;
    for (int i = 0; i < long_; i++)
    {
        regiones<<A[i].first<<", ";
        regiones<<A[i].second<<endl;
        if (A[i].first == A[i + 1].first)
        {
            _count_ ++;
        }
        else
        {
            _cantidades_.ag_atras(_count_);
            temp = A[i].first;
            int pot_ = 2;
            while ( pot_ >= 0 )
            {
                if ( temp >= pow (2, pot_) )
                {
                    reg_ += S[2 - pot_];
                    reg_ += ", ";
                    temp = temp - pow (2, pot_);
                }
                pot_ --;
            }
            regiones<<endl<<"Total "<<A[i].first
            <<" = "<<reg_<<": "<<_count_<<endl<<endl;
            _count_ = 1;
            reg_ = "";
        }
    }
    int _total_escuelas_ = 0;
    int tam_cantidades = _cantidades_.tam();
    for (int n = 0; n < tam_cantidades; n ++)
    {
        _total_escuelas_ += _cantidades_.iesimo(n);
    }
    regiones<<endl<<"Total escuelas: "<<
                                    _total_escuelas_;
    regiones<<endl<<"long_ = "<<long_;
    regiones.close();
    return 0;
}
