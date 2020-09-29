#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Introducido un número, devuelve con cuantas cifras se representa para cada base (de 2 a 16).

int main() {
	
	int k;
	cin >> k;
	
	for (int b = 2; b <= 16; ++b) {
		int count = 0;
		int x = k;
		
		while (x != 0) {
			x = x/b;
			++count; }
		cout << "Base " << b << ": " << count << " cifras." << endl;
	}
}