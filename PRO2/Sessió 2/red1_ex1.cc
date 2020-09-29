#include "Estudiant.hh"

// Redondear, version accion

void redondear_e_a(Estudiant& est) {
	/* Pre: est tiene nota */
	/* Post: est pasa a tener su nota original redondeada */
	est.modificar_nota(((int) (10. * (est.consultar_nota() + 0.05))) / 10.0);
}

int main() {
	
	Estudiant est;
	est.llegir();
	
	while (est.te_nota()) {
		redondear_e_a(est);
		est.escriure();
		est.llegir();
	}
}
	

