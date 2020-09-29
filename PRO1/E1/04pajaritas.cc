#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Dibujar pajaritas de tamaño n introducido por el usuario.

int main() {
	
	int n;
	
	while (cin >> n) {
		
		
		int espacios = 0;
		int equis = (2*n)-1;
			
		// Bloque 1
		for (int fila = 0; fila < n-1; ++fila) {
			
			while (espacios < fila) {
				cout << " ";
				++espacios;
			}
			
			while (equis > 0) {
				cout << "X";
				--equis;
			}
			
			cout << endl;
			
			++espacios;
			equis = equis - 2;
		}
		
		// Bloque 2
		for (int s = 0; s < n-1; ++s) cout << " ";
		cout << "X" << endl;
		
		
		// Bloque 3
		
		
	}
}