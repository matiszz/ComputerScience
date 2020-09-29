#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

void cod(int n) {
	
	if (n < 3) { // Caso base
		if (n == 0) cout << "-"; // Codificación del 0
		if (n == 1) cout << "+"; // Codificación del 1
		if (n == 2) cout << "*"; // Codificación del 2
	}
	else {
		cod(n/3); // Caso recursivo
		if (n%3 == 0) cout << "-"; // Codificación del 0
		if (n%3 == 1) cout << "+"; // Codificación del 1
		if (n%3 == 2) cout << "*"; // Codificación del 2
	}
}


int main() {
	
	int x;
	while (cin >> x) {
		if (x < 0) { 		// Para numeros negativos
			cout << ":";
			x = x * (-1); 	// Cambiar a positivo
		}
		cod(x);
		cout << endl;
	}
}
