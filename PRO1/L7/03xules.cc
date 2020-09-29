#include <iostream>
#include <string>
using namespace std;

// Matias Szarfer Barenblit
// PRE: Seq. de una o més linies. Cada línea comença amb un natural.
// POST: Cal escriure “totes xules”, “cap de xula”, o bé “dels dos tipus” segons convingui.

int main() {
	
	bool xula = false;
	bool noXula = false;
	int n;
	
	while (cin >> n and not(xula and noXula)) { // Cabecera de la secuencia de líneas
		
		// Tratar cada línea
		
		string prim;
		
		if (n%2 == 0) {
			noXula = true;
			for(int i = 1; i <= n; ++i) cin >> prim;
			
		} else {
			string mig, ult, altres;
			cin >> prim;
			for (int i = 2; i <= n; ++i) {
				cin >> altres;
				if (i == (n+1)/2) mig = altres;
				if (i == n) ult = altres;
			}
	
		if (prim == mig and mig == ult) xula = true;
		else noXula = true;
		}
		// Acaba la secuencia de una línea
	}
	
	// Diferentes respuestas para cada caso de linea
	if (xula and not noXula) cout << "totes xules" << endl;
	else if (not xula) cout << "cap de xula" << endl;
	else cout << "dels dos tipus" << endl;
	
}
