#include "Cjt_estudiants.hh"

void Cjt_estudiants::afegir_estudiant(const Estudiant &est, bool& b) {
	
	b = false;
	int j = cerca_dicot(vest, 0, nest-1, est.consultar_DNI());
	
	if (vest[j].consultar_DNI() == est.consultar_DNI()) b = true;
	if (not b) {
		++nest;
		for (int i = nest-1; i > j; --i) vest[i] = vest[i-1];
		vest[j] = est;
		
		///Actualitzar imax
		recalcular_posicio_imax();
	}
}
/* POST: b = indica si el p.i. original conté un estudiant amb el dni d'est;
		 si b = fals, s'ha afegit l'estudiant est al paràmetre implícit */


void Cjt_estudiants::eliminar_estudiants_sense_nota() {
	
	for (int i = 0; i < nest; ++i) {
		if (not vest[i].te_nota()) {
			for (int j = i; j < nest; ++j) vest[j] = vest[j+1];
			--nest;
			--i;
		}
	}
	
	///Actualitzar imax
	recalcular_posicio_imax();
}

/* Post: el paràmetre implicit no conté cap estudiant sense nota */
