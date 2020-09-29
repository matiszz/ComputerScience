#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Devuelve un octágono de medida n

int main() {
	int n;
	
    while (cin >> n) {
		int espacios = n-1, equis = n; //Comparador de espacios espacios i comparador x equis
		
		// Bloque 1
		for (int s = n-1; s != 0; --s) { 
			for (int e = espacios; e != 0; --e) cout << ' ';
			for (int x = equis; x != 0; --x) cout << 'X';
			cout << endl;
			
			equis = equis + 2;
			--espacios;
		}
		
		// Bloque 2
		for (int s = n; s != 0; --s) {
			for (int e = equis; e != 0; --e) cout << 'X';
			cout << endl;
		}
			equis = equis - 2;
			espacios = 1;
		
		
		// Bloque 3
		for (int s = n-1; s != 0; --s) {
			for (int e = espacios; e != 0; --e) cout << ' ';
			for (int x = equis; x != 0; --x) cout << 'X';
			cout << endl;
			
			equis = equis -2;
			++espacios;
		}
		
	cout << endl;
	}
} 