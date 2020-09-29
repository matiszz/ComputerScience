#include "ListaPalabras.hh"

void ListaPalabras::anadir_palabra(const Palabra &p) {
// PRE: El número de palabras en el parámetro implícito es menor que la 
//      longitud máxima o p ya está en él; p no es la palabra vacía
	
	bool b;
	int i;
	buscar_palabra_posicion(p, b, i);
	
	if (b) ++paraules[i].freq;
	else {
		paraules[i].par = p;
		paraules[i].freq = 1;
		++nparaules;
		++npar_long[p.long_pal() - 1];
	}
	++suma_frec_long[p.long_pal() - 1];
}
// POST: Post: si p estaba en el parámetro implícito original, su frecuencia se ha
//       incrementado en 1; si no, p pasa a estar en él, con frecuencia 1



void ListaPalabras::borrar_palabra(const Palabra &p) {
// PRE: si p pertence al p.i., tiene frecuencia f
	
	bool b;
	int i;
	buscar_palabra_posicion(p, b, i);
	
	if (b) {
		if (paraules[i].freq > 1) --paraules[i].freq;
		else {
			int allargada = longitud();
			paraules[i] = paraules[allargada - 1];
			--nparaules;
			--npar_long[p.long_pal() - 1];
		}
		/*if (paraules[i].freq == 1) {
			while (i < nparaules) {
				paraules[i] = paraules[i+1];
				--nparaules;
			}*/
	}
	--suma_frec_long[p.long_pal() - 1];
}
// POST:
// 		 si p no pertence al p.i., no cambia nada; 
//		 si f = 1, p ya no pertenece al p.i.; 
// 		 si f > 1, la frecuencia de p se ha decrementado en 1



void ListaPalabras::buscar_palabra_posicion(const Palabra &p, bool &b, int &i) const {
	b = false;
	i = 0;
	while (i < nparaules and not b) {
		if (paraules[i].par.iguales(p)) b = true;
		else ++i;
	}
	if (not b) i = nparaules;
}
// POST: b indica si p está en el parámetro implícito;
//       si b, entonces i es la posición en la que está p; si no, i es la 
//	     longitud del parámetro implícito
