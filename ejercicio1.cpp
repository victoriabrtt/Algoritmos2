#include <iostream>
#include <cassert>
#include <cstring>
#include "TADs/colaExt.cpp"

using namespace std;

int main()
{

int n=0; //cant ordenes
cin >>n;


string plato;
colaExtendida *cola = new colaExtendida(n);


for (int i = 1; i <= n; i++) {
        cin >> plato;
		
		if(!cola->existe(plato)){
		
          cola->encolar(plato,1);
		  
		}else{
		
		    cola->actualizarPrioridad(plato,cola->obtenerPrioridad(plato)+1);
		}
   
		
}

while (!cola->esVacia()) {

	cout << cola->tope() << endl;
    cola->desencolar();


}
cola->destruir();
delete cola;




};



    





		
