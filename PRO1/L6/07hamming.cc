#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// PRE: n
// POST: n primers nombres de Hamming:
//       es de hamming si (n%2 o n%3 o n%5)

bool es_de_hamming(int x) {
	
	if (x == 1) return true; // Cas base
	else if (x%2 == 0) return es_de_hamming(x/2); // Casos recursius
	else if (x%3 == 0) return es_de_hamming(x/3);
	else if (x%5 == 0) return es_de_hamming(x/5);
	else return false;
	
}


int main() {
	
	int x;
	while (cin >> x) {
		
		int i = 0;
		int n = 1; // Primer número de Hamming
		
		while (i < x) { // Número de veces que va a calcular
			
			if (es_de_hamming(n)) {
				if (i == 0) cout << n; // El primer número (por la ,)
				else if (n > 0) cout << "," << n; // Los otros (por la ,)
				++i; // Siguiente iteracion
			} ++n; // Prueba con el siguiente numero
		}
		cout << endl;
	}
}
