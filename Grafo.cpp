#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

struct nodoLista
{
    int destino;
    nodoLista *sig;
    int costo;

    nodoLista(int x) : destino(x), sig(0){};
    nodoLista(int x, nodoLista *unSig) : destino(x), sig(unSig){};
};

class Grafo
{

private:
    nodoLista **vertices;
    int cantVertices;
    bool esDirigido;
    bool esPonderado;

    void agregarAristaPrivado(int origen, int destino, int peso)
    {
        nodoLista *nuevo = new nodoLista(destino);
        nuevo->sig = NULL;
        nuevo->costo = peso;
        for (int i = 0; i < this->cantVertices; i++) //cantvertices+1?
        {
            if (vertices[i]->destino == origen) //dudoso ese destino, pero si no los tipos no son compatibles 
            {
                nodoLista *actual = vertices[i];
                while (actual->sig != NULL)
                {
                    actual = actual->sig;
                }
                actual = nuevo;
            }
        }
    }

public:
    Grafo(int cantVertices, bool esDirigido = true, bool esPonderado = true)
    {
        this->cantVertices = cantVertices;
        this->vertices = new nodoLista *[cantVertices + 1]; // en duda
        this->esDirigido = esDirigido;
        this->esPonderado = esPonderado;
    }

    void agregarArista(int desde, int destino, int costo = NULL)
    {
        if (costo == NULL)
        {
            if (!esDirigido)
            {
                agregarAristaPrivado(desde, destino, 1);
                agregarAristaPrivado(destino, desde, 1);
            }
            else
            {
                agregarAristaPrivado(desde, destino, 1);
            }
        }
        else
        {
            if (!esDirigido)
            {
                agregarAristaPrivado(desde, destino, costo);
                agregarAristaPrivado(destino, desde, costo);
            }
            else
            {
                agregarAristaPrivado(desde, destino, costo);
            }
        }
    }
};


