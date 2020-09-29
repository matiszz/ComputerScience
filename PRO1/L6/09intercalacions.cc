#include <iostream>
#include <cmath>
using namespace std;

// Matias Szarfer Barenblit

// PRE: a, b, on xifres_a = xifres_b
// POST: Escriure a i b intercalat

int digits(int n) { // Función que cuenta dígitos
		
	int dig = 0;
	while (n >= 1) {
		n = n/10;
		++dig; }
	return dig;
	
}

int intercalacio(int x, int y) {
	
	int n = 0;
	int it = 1;
	
	while (x != 0 or y != 0) {
		n = n + it * ((y%10) + (x%10)*10);
		it = it*100;
		x = x/10;
		y = y/10;
	}
	return n;
}


int main() {
	
	int a, b;
	while (cin >> a >> b) cout << intercalacio(a, b) << endl;	
	
}
