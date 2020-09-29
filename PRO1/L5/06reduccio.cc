#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Suma tots els digits d'un nombre.

int suma_digits(int x) {
	
	if (x < 10) return x;
	else return suma_digits(x/10) + x%10;
	
}

int reduccio_digits(int x) {
	
	if (x < 10) return x;
	else return reduccio_digits(suma_digits(x));
	
}

int main() {
	
	int x;
	cin >> x;
	cout << reduccio_digits(x) << endl;
	
}
