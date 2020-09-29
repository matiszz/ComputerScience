#include <iostream>
#include <cmath>
using namespace std;

// Matias Szarfer Barenblit

// PRE: Secuencia de naturales.
// POST: Indicar si la secuencia es o no narcisita.
// Es narcisista si la suma de sus cifras elevado al numero de cifras = n;

int cifras(int n) {
	int count = 0;
	while (n != 0) {
		++count;
		n /= 10;
	}
	return count;
}

bool es_narcicista(int n) {
	
	int cif = cifras(n);
	int m = n; // Para poder destrozar m
	int total = 0;
	
	while (m != 0) {
		total += pow(m%10, cif);
		m = m/10;
	}
	
	return (total == n); // if (total == n) return true;
}


int main() {
	
	int n;
	bool noNarcisista = false;
	
	while(cin >> n and not noNarcisista) {
		if (not es_narcicista(n)) noNarcisista = true;
	}
	if (not noNarcisista) cout << "SI" << endl;
	else cout << "NO" << endl;
}
