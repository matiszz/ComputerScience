#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// Funció per cambiar de base

void canvi_base(int n, int b) {
	if (n < b) { // Los numeros que pueden representarse sin mas.
		cout << n;
	} else {
		canvi_base(n/b, b); 
		int r = n%b;
		if (r < 10) cout << r;
		else cout << 'A' + r - 10; // A partir de 10, converir en letras (como en HEX)
	}
}
