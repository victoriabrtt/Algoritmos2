#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

struct nodoListaString
{
    string clave; // genero //id
    string valor; // valor es nuestro cant //id pelicula //calificacion
    nodoListaString *sig;

    nodoListaString(string unaClave, string unValor) : clave(unaClave), valor(unValor), sig(0){};
    nodoListaString(string unaClave, string unValor, nodoListaString *unSig) : clave(unaClave), valor(unValor), sig(unSig){};
};

class tablaHashString
{
private:
    nodoListaString **buckets;
    int cota;
    int cantElem;

    int funcionHashString(string clave)
    { // que funcion de hash hacer
        int suma = 0;
        for (int i = 0; i < clave.length(); i++)
        {
            suma = suma + clave[i];
        }
        return suma%this->cota;
    }

public:
    tablaHashString(int tamanio)
    {
        this->buckets = new nodoListaString *[tamanio];
        this->cota = tamanio;
        this->cantElem = 0;

        for (int i = 0; i < tamanio; i++)
        {
            buckets[i] = nullptr;
        }
    }

    bool existeString(string clave)
    {
        int indice = funcionHashString(clave);
        nodoListaString *actual = buckets[indice];
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

    void insertarString(string clave, string valor)
    {
        int indice = funcionHashString(clave);
        nodoListaString *nuevoNodo = new nodoListaString(clave, valor);
        nuevoNodo->sig = NULL;
        if (buckets[indice] == NULL)
        {

            buckets[indice] = nuevoNodo;
        }
        else
        {
            nodoListaString *actual = buckets[indice];
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

    void insertarO1String(string clave, string valor) // insertar en orden 1
    {
        int indice = funcionHashString(clave);
        nodoListaString *nuevoNodo = new nodoListaString(clave, valor);
        nuevoNodo->sig = NULL;
        if (buckets[indice] == NULL)
        {

            buckets[indice] = nuevoNodo;
        }
        else
        {
            nodoListaString *actual = buckets[indice];
            nuevoNodo->sig = actual;
            buckets[indice] = nuevoNodo;
        }
        cantElem++;
    }

    bool esVacioString()
    {
        return this->cantElem == 0;
    }

    string obtenerValorString(string clave)
    {
        nodoListaString *actual = buckets[funcionHashString(clave)];

        while (actual != NULL)
        {
            if (actual->clave == clave)
            {
                return actual->valor;
            }
            actual = actual->sig;
        }
    }

    string idPeliMax(string genero, tablaHash* tabla)
    {
        int max = 0;
        string id;
        nodoListaString *actual = buckets[funcionHashString(genero)];
        while(actual != NULL){
            int promedio = tabla->promedio(actual->valor);
            if(promedio > max){
                max = promedio;
                id = actual->valor;
            }
            actual = actual->sig;
        }
        return id;
    }

    
};