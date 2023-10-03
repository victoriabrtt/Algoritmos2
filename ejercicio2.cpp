#include <iostream>
#include <cassert>
#include <cstring>
#include "TADs/Tabla.cpp"
#include "TADs/TablaString.cpp"

using namespace std;

int main()
{

    int generos = 0;
    cin >> generos;
    cout<<"cant generos"<<endl;

    string *gens = new string[generos];

    tablaHashString *tabla1 = new tablaHashString(generos);
    for (int i = 0; i < generos; i++)
    {
        cin >> gens[i];
    }

    int peliculas = 0;
    cin >> peliculas;

    for (int i = 0; i < peliculas; i++)
    {
        string genero, pelicula;
        cin >> pelicula >> genero;
        tabla1->insertarO1String(genero, pelicula);
        printf("inserto en tabla 1");
    }

    int cantCalifs = 0;
    cin >> cantCalifs;

    tablaHash *tabla2 = new tablaHash(peliculas);
    for (int i = 0; i < cantCalifs; i++)
    {
        string pelicula;
        int calificacion;
        cin >> pelicula >> calificacion;
        tabla2->insertarO1(pelicula, calificacion);
        printf("inserto en tabla 2");
    }

    for (int i = 0; i < generos; i++)
    {
        cout << tabla1->idPeliMax(gens[i], tabla2) << endl;
    }
}