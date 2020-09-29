#include "Cjt_estudiants.hh"

void Cjt_estudiants::afegir_estudiant(const Estudiant &est, bool& b) {
	
	b = false;
	int p = cerca_dicot(vest, 0, nest-1, est.consultar_DNI());
	
	if (vest[p].consultar_DNI() == est.consultar_DNI()) b = true;
	
	if (not b) {
		nest++;
		for (int i = nest-1; i > p; i--) vest[i] = vest[i-1];
		vest[p] = est;
		
		if (vest[p].te_nota()) {
			if (nest_amb_nota == 0) suma_notes = est.consultar_nota();
			else suma_notes += est.consultar_nota();
			nest_amb_nota++;
		}
	}
}

/* Post: b = indica si el p.i. original conté un estudiant amb el dni d'est;
   si b = fals, s'ha afegit l'estudiant est al paràmetre implícit */

void Cjt_estudiants::esborrar_estudiant(int dni, bool& b) {
	
	b = false;
	int p = 0;
	
	while (not b and p < nest) {
		if (vest[p].consultar_DNI() == dni) b = true;
		p++;
	}
	
	if (b) {
		suma_notes -= vest[p-1].consultar_nota();
		nest_amb_nota--;
		
		for (int i = nest; i > p; i--) vest[i-1] = vest[i];
		nest--;
	}
}

/* Post: b indica si el paràmetre implícit original tenia un estudiant 
   amb el dni dni; si b, aquest estudiant ha quedat eliminat
   del paràmetre implícit */
