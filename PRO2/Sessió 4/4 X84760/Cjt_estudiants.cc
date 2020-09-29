#include <algorithm>
#include "Cjt_estudiants.hh"

Cjt_estudiants::Cjt_estudiants()
{
  nest = 0;
  vest = vector<Estudiant>(MAX_NEST);
  imax = -1;
}

int Cjt_estudiants::cerca_dicot(const vector<Estudiant> &vest, int left, int right, int x)
{
  int i;
  bool found=false;
  while (left <= right and not found) { 
    i = (left + right)/2;
    if (x < vest[i].consultar_DNI()) right = i - 1; 
    else if (x > vest[i].consultar_DNI()) left = i + 1; 
    else found = true;
  } 
  if (found) return i;
  else return left;
}  

void Cjt_estudiants::modificar_estudiant(const Estudiant &est, bool& b)
{
  int x = est.consultar_DNI();
  int i = cerca_dicot(vest,0, nest - 1, x);
  b = (i<nest) and (x== vest[i].consultar_DNI());
  if (b) { 
    if (imax == -1) {
       if (est.te_nota()) {imax=i; vest[i] = est;}
    }    
    else {  
      double x = vest[imax].consultar_nota();
      vest[i] = est;
      if (i == imax){ 
		if (not est.te_nota() or est.consultar_nota() < x)
			recalcular_posicio_imax();
		}	
      else {
		if (est.te_nota()){
			if (est.consultar_nota() > x or (est.consultar_nota()==x and est.consultar_DNI()< vest[imax].consultar_DNI()))
			 imax = i; 
		}
	  }
    }
  }
}

void Cjt_estudiants::recalcular_posicio_imax(){
  imax = -1;
  bool b = false; 
  int i=0;
  while (i<nest and not b) {
    if (vest[i].te_nota()) b=true;
    else ++i;
  }
  if (i < nest){
    imax=i;
    double notamax = vest[i].consultar_nota();
    ++i;
    for (; i<nest; ++i){
      if (vest[i].te_nota()){
		double notaact = vest[i].consultar_nota();
		if (notamax < notaact){
			notamax = notaact;
			imax = i;
		}
      }
    }
  }
}

int Cjt_estudiants::mida() const
{
  return nest;
}
  
Estudiant Cjt_estudiants::estudiant_nota_max() const
{
  return vest[imax];
}

void Cjt_estudiants::ordenar() {
  sort(vest.begin(), vest.begin() + nest, Estudiant::comp);
  recalcular_posicio_imax();
}

void Cjt_estudiants::llegir() {
  cin >> nest;
  for (int i = 0; i < nest; ++i) vest[i].llegir();
  ordenar();
}

void Cjt_estudiants::escriure() const {
  for (int i = 0; i < nest; ++i)
    vest[i].escriure();
}

