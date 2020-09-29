#include <iostream>
#include "Cjt_estudiants.hh"

using namespace std;

int main() {
  Cjt_estudiants c;
  c.llegir(); 
  int op;
  cin >> op;
  while (op != -6){
    Estudiant est; bool b;
    switch (op) { 
    case -1:   // afegir
      est.llegir();
      c.afegir_estudiant(est, b);
      if (b)  cout << "l'estudiant " << est.consultar_DNI() << " ja hi era" << endl << endl;
      break;
    case -2:   // eliminar estudiants sense nota
      c.eliminar_estudiants_sense_nota();
      break; 
    case -3:   // modificar nota per dni
      est.llegir();
      c.modificar_estudiant(est, b);
      if (not b) cout << "l'estudiant " << est.consultar_DNI() << " no hi es" << endl << endl;
      break;
    case -4:   // escriure el conjunt
      cout << "Conjunt:" << endl;
      c.escriure();
      cout << endl;
      break;
    case -5:   // escriure l'estudiant de nota maxima
      cout << "Nota max: ";
      c.estudiant_nota_max().escriure();
      cout << endl;
      break;
    }
    cin >> op; 
  }
}

