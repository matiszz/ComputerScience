#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Calcula el màxim comú divisor de a i b utilitzan
// la versió ràpida de l’algorisme d’Euclides.

int mcd(int a, int b) {
	
	while (b != 0) {
		int r = a%b;
		a = b;
		b = r;
	}
	return a;
} 

int main() {
	
	int x, y;
	cin >> x >> y;
	cout << mcd (x, y) << endl;

}