#include <iostream>
#include <cmath>
using namespace std;

// Matias Szarfer Barenblit

// PRE: x, k, x sense cap 0.
// POST: resultat d'aplicr k rotacions a x;

int digits(int n) { // Función que cuenta dígitos.
		
	int dig = 0;
	while (n >= 1) {
		n = n/10;
		++dig; }
	return dig;
	
}

int rotacio_dreta(int x, int k) {
	
	for (int i = 1; i <= k; ++i) { // K veces
		
			/* EXPLICACIÓN
			 * ultim = x%10.
			 * Convertimos el último en el primero,
			 * elevándolo al numero de dígitos -1.
			 * 
			 * Luego, primers es el x menos el útlimo dígito.
			 * Sumamos úlitmo + primero.
			 * */
			 
		int ultim   = x%10 * pow(10, digits(x) - 1);
		int primers = x/10;
		
		x = ultim + primers;
	}
	return x;
}


int main() {
	
	int n, k;
	while (cin >> n >> k) {
		cout << rotacio_dreta(n, k) << endl;
	}
	
}
