#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// L'entrada és un número que indica quants components té la seqüencia i una seqüencia.
// La sortida és la suma dels números que tenen un parell darrere.

int main() {
	
	int n, x;
	int sum = 0;
	
	while (cin >> n) {
		cin >> x;
		for (int i = 0; i < n-1; ++i) {
			int p;
			cin >> p;
			if (p%2 == 0) sum = sum + x;
			x = p;
		}
		cout << sum << endl;
		sum = 0;
	}
}