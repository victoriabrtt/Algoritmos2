#include <iostream>
#include <cassert>

using namespace std;

struct nodoLista
{               // tabla
  string clave; // plato
  int valor;    // posicion
  nodoLista *sig;

  nodoLista(string unaClave, int unValor) : clave(unaClave), valor(unValor), sig(0){};
  nodoLista(string unaClave, int unValor, nodoLista *unSig) : clave(unaClave), valor(unValor), sig(unSig){};
};

struct nodoHeap
{
  string clave;
  int prioridad; // cantidad
};

class colaExtendida
{
private:
  nodoHeap **elementos;
  nodoLista **buckets;
  int capacidad;
  int primeroLibre;
  int cota;
  int cantElem;

  int funcionHash(string clave)
  {
    int suma = 0;
    for (int i = 0; i < clave.length(); i++)
    {
      suma = suma + clave[i];
    }
    return suma%this->capacidad;
  }

  bool compararString(string a,string b){
	int largo;
	if(a.length()<b.length()){
		largo = a.length();
	}else{
		largo= b.length();
	}



	for(int i=0;i<largo;i++){
		if(a[i]>b[i]){
			return true;
		}else if(a[i]<b[i]){
			return false;
		}



	}
	if(a.length()<b.length()){
		return true;
	}else{
		return false;
	}

}

  bool estaLLeno()
  {
    return this->primeroLibre >= this->capacidad;
  }
   

  void insertarHeap(string dato, int cant)
  {
    if (!this->estaLLeno())
    {
      nodoHeap *nuevo = new nodoHeap();
      nuevo->clave = dato;
      nuevo->prioridad = cant;
      this->elementos[this->primeroLibre] = nuevo;
      this->flotar(this->primeroLibre);
      this->primeroLibre++;
      
    }
  }
 



  void insertarHash(string clave, int pos)
  {
    int indice = funcionHash(clave);
    nodoLista *actual = this->buckets[indice];
  nodoLista *nuevoNodo = new nodoLista(clave, pos);
  nuevoNodo->sig = NULL;

  if (actual == NULL)
  {
    
    this->buckets[indice] = nuevoNodo;
    return;
  }
  while (actual != NULL){
   if (actual->clave == clave)
    {
      actual->valor = pos;
      return;
    }
    if (actual->sig == NULL)
    {
      break; 
    }
    actual = actual->sig;
  }
  actual->sig = nuevoNodo;
}

  void intercambiar(int x, int y)
  {
    nodoHeap *aux = this->elementos[x];
    this->elementos[x] = this->elementos[y];
    this->elementos[y] = aux;

    string claveX = this->elementos[x]->clave;
    string claveY = this->elementos[y]->clave;

    insertarHash(claveX, x);
    insertarHash(claveY, y);
  }

  
  
  
  void hundir(int pos)
  {
    if(this->primeroLibre==2){
      return;
    }
    int hijoIzq = pos * 2;
    int hijoDer = pos * 2 + 1;
    int hijoMayor = hijoIzq; // izquierda por defecto
   
    if(this->elementos[hijoIzq]==NULL || pos>= this->primeroLibre){
      return;
    }
    if (hijoDer < this->primeroLibre && this->elementos[hijoIzq]->prioridad < this->elementos[hijoDer]->prioridad)
    {
      hijoMayor = hijoDer;
    }

    if(hijoDer < this->primeroLibre && this->elementos[hijoIzq]->prioridad == this->elementos[hijoDer]->prioridad && !compararString(this->elementos[hijoDer]->clave,this->elementos[hijoIzq]->clave)){
      hijoMayor = hijoDer;
    }



    if (elementos[pos]->prioridad < elementos[hijoMayor]->prioridad)
    {

      intercambiar(pos, hijoMayor);
      hundir(hijoMayor);
    }
   

    else if (elementos[pos]->prioridad == elementos[hijoMayor]->prioridad && compararString(elementos[pos]->clave,elementos[hijoMayor]->clave))
    {
      intercambiar(pos, hijoMayor);
      hundir(hijoMayor);
    }
  }

  void flotar(int pos)
  {
    if (pos > 1)
    {
      int posPadre = pos / 2;
      if (elementos[pos]->prioridad > elementos[posPadre]->prioridad)
      {
        intercambiar(pos, posPadre);
        flotar(posPadre);
      }
      else if (elementos[pos]->prioridad == elementos[posPadre]->prioridad)
      {
        // Compara las claves alfabéticamente
        if (!compararString(elementos[pos]->clave,elementos[posPadre]->clave) )
        {
          intercambiar(pos, posPadre);
          flotar(posPadre);
        }
      }
    }
    
  }

 

public:
  colaExtendida(int tamanio)
  {
    this->elementos = new nodoHeap *[tamanio + 1]();
    this->capacidad = tamanio;
    this->primeroLibre = 1;
    this->buckets = new nodoLista *[tamanio]();
    this->cota = tamanio;
    this->cantElem = 0;
  }
    
  string tope(){
  return this->elementos[1]->clave;
 }


  bool esVacia()
  {
    return this->primeroLibre==1;
  }

  bool existe(string clave)
  {
    int indice = funcionHash(clave);
    nodoLista *actual = this->buckets[indice];
    
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

  int obtenerPosicion(string clave)
  {
    nodoLista *actual = this->buckets[funcionHash(clave)];
    while (actual != NULL)
    {
      if (actual->clave == clave)
      {
       
        return actual->valor;
      }
      actual = actual->sig;
    }
  }

  int obtenerPrioridad(string clave){
    int pos=obtenerPosicion(clave);
    return this->elementos[pos]->prioridad;
   

  }

  void actualizarPrioridad(string clave , int prioridad){
   int pos=obtenerPosicion(clave);
   int actual=this->elementos[pos]->prioridad;
   this->elementos[pos]->prioridad=prioridad;
   if(actual<prioridad){
      flotar(pos);
   }else{
    hundir(pos);
   }
  }

  void encolar(string clave , int prioridad)
  {
    if(!this->estaLLeno()){
        int posicion = this->primeroLibre;
        this->insertarHash(clave, posicion);
        this->insertarHeap(clave,prioridad);
        flotar(posicion);
      
    }
  }



void desencolar()
{
  if (!this->esVacia())
  {
    
    this->primeroLibre--;
    this->elementos[1] = this->elementos[this->primeroLibre];
    this->elementos[this->primeroLibre]=NULL;
  
    hundir(1);
   
  
  }

}

void destruir() {
    
    for (int i = 1; i < primeroLibre; i++) {
        delete this->elementos[i];
    }
    delete[] this->elementos;
    delete[] this->buckets;
    
   
    elementos = NULL;
    buckets = NULL;
    capacidad = 0;
    primeroLibre = 1;
    cota = 0;
    cantElem = 0;

}


};
