#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

struct nodoLista
{
    string clave;  //id
    int valor;    // valor es nuestro cant //id pelicula //calificacion
    nodoLista *sig;

    nodoLista(string unaClave, int unValor) : clave(unaClave), valor(unValor), sig(0){};
    nodoLista(string unaClave, int unValor, nodoLista *unSig) : clave(unaClave), valor(unValor), sig(unSig){};
};

class tablaHash
{
private:
    nodoLista **buckets;
    int cota;
    int cantElem;

    int funcionHash(string clave)
    { // que funcion de hash hacer
        int suma = 0;
        for (int i = 0; i < clave.length(); i++)
        {
            suma = suma + clave[i];
        }
        return suma%this->cota;
    }

public:
    tablaHash(int tamanio)
    {
        this->buckets = new nodoLista *[tamanio];
        this->cota = tamanio;
        this->cantElem = 0;

        for (int i = 0; i < tamanio; i++)
        {
            buckets[i] = nullptr;
        }
    }

    bool existe(string clave)
    {
        int indice = funcionHash(clave);
        nodoLista *actual = buckets[indice];
        while (actual != NULL)
        {
            if (actual->clave == clave)
            {
                return true;
            }
            actual = actual->sig;
        }
        return false;
    }

    void insertar(string clave, int valor)
    {
        int indice = funcionHash(clave);
        nodoLista *nuevoNodo = new nodoLista(clave, valor);
        nuevoNodo->sig = NULL;
        if (buckets[indice] == NULL)
        {

            buckets[indice] = nuevoNodo;
        }
        else
        {
            nodoLista *actual = buckets[indice];
            while (actual->sig != NULL)
            {
                if (actual->clave == clave)
                {
                    return;
                }

                actual = actual->sig;
            }

            actual->sig = nuevoNodo;
        }
        cantElem++;
    }

    void insertarO1(string clave, int valor)  //insertar en orden 1
    {
        int indice = funcionHash(clave);
        nodoLista *nuevoNodo = new nodoLista(clave, valor);
        nuevoNodo->sig = NULL;
        if (buckets[indice] == NULL)
        {
            buckets[indice] = nuevoNodo;
        }
        else
        {
            nodoLista *actual = buckets[indice];
            nuevoNodo->sig = actual;
            buckets[indice] = nuevoNodo;
        }
        cantElem++;
    }

    bool esVacio()
    {
        return this->cantElem == 0;
    }

    void aumentar(string clave)
    {
        int indice = funcionHash(clave);
        nodoLista *actual = buckets[indice];

        while (actual != NULL)
        {
            if (actual->clave == clave)
            {
                actual->valor++;
                return;
            }
            actual = actual->sig;
        }
    }

    int obtenerValor(string clave)
    {
        nodoLista *actual = buckets[funcionHash(clave)];

        while (actual != NULL)
        {
            if (actual->clave == clave)
            {
                return actual->valor;
            }
            actual = actual->sig;
        }
    }

    int promedio(string clave)
    { // puede llegar a ser un float
        nodoLista *aux = buckets[funcionHash(clave)];
        int cant;
        int suma;

        while (aux != NULL)
        {
            cant++;
            suma += aux->valor;
            aux = aux->sig;
            printf("hola");
        }

        return suma / cant;
    }
};