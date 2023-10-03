#include <iostream>
#include <cassert>
#include <cstring>
#include "TADs/MaxHeap.cpp"

using namespace std;

int main()
{

int n=0; 
cin >>n;


maxHeap *heap = new maxHeap(n);
int p , t , ur;
for(int i=0 ; i<n ; i++){
    cin >> p >> t >> ur;
    heap->insertarHeap(p,t,ur);  
}


while(!heap->esVacio()){
    cout << heap->obtenerMax() << endl;

}
delete heap; 

}