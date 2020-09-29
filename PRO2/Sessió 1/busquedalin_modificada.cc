#include "vectorIOint.hh"
#include <iostream>
using namespace std;

/* Buscar  */    
int busqueda_lin(const vector<int> &v, int x) {
/* Pre: cierto */
/* Post: el resultado indica la pos del numero, si está, y un -1 si no está */
  int tam = v.size();
  int i = 0;
  bool b = false;
  while (i < tam and not b) {
    if (v[i] == x) b = true; 
    else ++i;
  }
  if (b) return i;
  else return -1;
}

int main () {
  vector<int> v;
  leerVector_int(v); 
  
  cout << "Escribe el elemento a buscar: " << endl;
  int x;
  cin >> x;
  
  int b = busqueda_lin(v,x);
  if (b == -1)  cout << "El elemento " << x << " no esta en el vector." << endl << endl;
  else cout << "El elemento " << x << " esta en la posición " << b << endl << endl;
  
  cout << "Escribimos el vector para que se vea que no ha cambiado:" << endl;
  escribirVector_int(v);
}
