#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

int main() {
	int x, count;
	cin >> x;
	
	int y = x;
	while (y != 0) { // Contar el número de dígitos
		y = y/10;
		++count; }
		
	if (count%2 != 0 or x == 0) cout << "res" << endl; // En caso que sean impares
	//if (x == 0) cout << "res" << endl;
	
	else {
		int fin = 0;
		int ini = 0;
		for (int i = count; i != count/2; --i) { // Esto suma los últimos dígitos
			fin = fin + x%10;
			x = x/10;
		}
		for (int i = count; i != 0; --i) { // Esto suma los primeros dígitos
			ini = ini + x%10;
			x = x/10;
		}
		
		//Imprimir cada caso
		cout << ini;
		if (ini > fin) cout << " > ";
		if (ini < fin) cout << " < ";
		if (ini == fin) cout << " = ";
		cout << fin << endl;
	}
}