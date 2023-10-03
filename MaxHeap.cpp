#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

struct nodoHeap {
	int p;  
	int t;
	int u;
};

class maxHeap{
  private:
	nodoHeap **elementos;
	int capacidad;
	int primeroLibre;

	void intercambiar(int x, int y)
	{
		nodoHeap *aux = this->elementos[x];
		this->elementos[x] = this->elementos[y];
		this->elementos[y] = aux;
       
	}

	void flotar(int pos)
	{
		if (pos > 1)
		{
			int posPadre = pos/2;
			if(elementos[pos]->u >elementos[posPadre]->u){
				intercambiar(pos,posPadre);
				flotar(posPadre);
			}else if (elementos[pos]->u == elementos[posPadre]->u) {
          
             if (elementos[pos]->t < elementos[posPadre]->t) {
              intercambiar(pos, posPadre);
              flotar(posPadre);
             }else if(  elementos[pos]->u== this->elementos[posPadre]->u && elementos[pos]->t== this->elementos[posPadre]->t && this->elementos[pos]-> p < this->elementos[posPadre]->p){
				intercambiar(pos, posPadre);
                flotar(posPadre);
			 }
			}
		
		}
	}

void hundir(int pos) {
	if(this->primeroLibre==2){
      return;
    }
    int hijoIzq = pos * 2;
    int hijoDer = pos * 2 + 1;
    int hijoMayor = hijoIzq; // Izquierda por defecto

	if(hijoIzq > this->primeroLibre-1){  
      return;
    }
    if (hijoDer < this->primeroLibre && this->elementos[hijoIzq]->u < this->elementos[hijoDer]->u) {
        hijoMayor = hijoDer;
    }else if(hijoDer < this->primeroLibre && this->elementos[hijoIzq]->u == this->elementos[hijoDer]->u && this->elementos[hijoDer]->t < this->elementos[hijoIzq]->t){
      hijoMayor = hijoDer;
    }
	else if( hijoDer < this->primeroLibre && this->elementos[hijoIzq]->u == this->elementos[hijoDer]->u && this->elementos[hijoIzq]->t == this->elementos[hijoDer]->t && this->elementos[hijoDer]->p < this->elementos[hijoIzq]->p){ // verificar la urgencia 
		hijoMayor= hijoDer;
	}

    if (this->elementos[pos]->u < this->elementos[hijoMayor]->u ){
      intercambiar(pos, hijoMayor);
      hundir(hijoMayor);
	}  
	else if (this->elementos[pos]->u == this->elementos[hijoMayor]->u && this->elementos[pos]->t > this->elementos[hijoMayor]->t) {
      intercambiar(pos, hijoMayor);
      hundir(hijoMayor);
    }else if ( this->elementos[pos]->u == this->elementos[hijoMayor]->u && this->elementos[pos]->t == this->elementos[hijoMayor]->t && this->elementos[pos]->p > this->elementos[hijoMayor]->p ){
	  intercambiar(pos, hijoMayor); 
      hundir(hijoMayor);   
	}    

 

}

	public:
    maxHeap(int tamanio)
	{
		// representacion del heap que arranca en 1
		this->elementos= new nodoHeap *[tamanio + 1]();
		this->capacidad = tamanio;
		this->primeroLibre = 1;
	}

	bool estaLLeno(){
		return this->primeroLibre >= this->capacidad+1;
	}

	void insertarHeap(int p, int t , int ur ) {
	  if (!this->estaLLeno()) {
        nodoHeap* nuevo = new nodoHeap();
        nuevo->p = p;
        nuevo->t = t;
		nuevo->u = ur;
        this->elementos[this->primeroLibre] = nuevo;
        this->flotar(this->primeroLibre);
		
        this->primeroLibre++;
		
      }
    }  
	bool esVacio(){
		return this->primeroLibre == 1;;
	}

	
  //no sea vacio
    
	int obtenerMax() {
    nodoHeap* max = NULL; 
      if (!this->esVacio()) {
        nodoHeap* max = this->elementos[1];
        int maxPaciente = max->p;  
        this->elementos[1] = this->elementos[this->primeroLibre - 1];
        this->primeroLibre--; 
        hundir(1);
        return maxPaciente;  
      }
	}
	


   void imprimirHeap(){
	for(int i=1 ; i< this->primeroLibre; i++){
		cout << "paciente " << this->elementos[i]->p << " tiempo "<<this->elementos[i]->t << " urgencia " << this->elementos[i]->u << endl;
	}
   }
	void destruir() {
    for (int i = 1; i < primeroLibre; i++) {
        delete this->elementos[i];
    }
    delete[] this->elementos;

    elementos = NULL;
    capacidad = 0;
    primeroLibre = 1;
   


}

 

};