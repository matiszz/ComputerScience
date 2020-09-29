#include "Cjt_estudiants.hh"

// PRE: Me dan 2 conjuntos de los mismos estudiantes con 1
//		nota cada uno. Primero introduce num estudiantes.
// POST: Escribir en el conj1 cada estudiante con la nota máxima. 0 es mejor que nada.
//		 Devolver el conj2.

Cjt_estudiants actualizar(Cjt_estudiants c1, Cjt_estudiants c2) {
	
	int m = c1.mida();
	
	for (int i = 1; i < m+1; ++i) {
		int dni = c1.consultar_iessim(i).consultar_DNI();
		Estudiant est1 = c1.consultar_iessim(i);
		Estudiant est2 = c2.consultar_estudiant(dni);
		
		double n1 = est1.consultar_nota();
		double n2 = est2.consultar_nota();
		
		if (est1.te_nota()) {
			if ( est2.te_nota() and ( n2 > n1 )) {
				c1.modificar_estudiant(est2);
			}
		} else if (est2.te_nota()) c1.modificar_estudiant(est2);
	}
	return c1;
}

/** HAY QUE CAMBIAR, QUE modificar_estudiant(); LO SUTITUYE POR UN NUVEO ESTUDIANTE. MIRAR CJT_ESTUDIANTS.HH **/

int main() {
	
	 Cjt_estudiants c1, c2;
	 c1.llegir();
	 c2.llegir();
	 c1 = actualizar(c1, c2);
	 c1.escriure();
	 
}
