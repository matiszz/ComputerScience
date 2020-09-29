#include "Cjt_estudiants.hh"

void Cjt_estudiants::afegir_estudiant(const Estudiant &est, bool& b) {
	
	b = false;
	int j = cerca_dicot(vest, 0, nest-1, est.consultar_DNI());
	
	if (vest[j].consultar_DNI() == est.consultar_DNI()) b = true;
	
	if (not b) {
		++nest;
		for (int i = nest-1; i > j; --i) vest[i] = vest[i-1];
		vest[j] = est;
		
		/// Actualitzar l'interval
		//if (vest[j].te_nota()) incrementar_interval(vest[j].consultar_nota());
		
		if (vest[j].te_nota()) {
			int a = est.consultar_nota();
			if (a == 10) a = 9;
			if (a < 10) ++intervals[a];
		}
	}
}
/* POST: b = indica si el p.i. original conté un estudiant amb el dni d'est;
		 si b = fals, s'ha afegit l'estudiant est al paràmetre implícit */



void Cjt_estudiants::esborrar_estudiant(int dni, bool& b) {
	
	b = false;
	int j = 0;
	
	while (not b and j < nest) {
		if (vest[j].consultar_DNI() == dni) b = true;
		++j;
	}
	
	if (b) {
		/// Actualitzar l'interval
		//if (vest[j].te_nota()) decrementar_interval(vest[j].consultar_nota());
		if (vest[j-1].te_nota()) {
			int a = vest[j-1].consultar_nota();
			if (a == 10) a = 9;
			if (a < 10) --intervals[a];
		}
		
		for (int i = j; i < nest; ++i) vest[i-1] = vest[i];
		--nest;
	}
}
/* POST: b indica si el paràmetre implícit original tenia un estudiant 
		 amb el dni dni; si b, aquest estudiant ha quedat eliminat
		 del paràmetre implícit */
