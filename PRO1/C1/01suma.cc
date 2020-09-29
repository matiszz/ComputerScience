#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Suma les 3 útlimes xifres d'un natural n >= 100.

int main() {
	
	int n;
	int suma = 0;
	cin >> n;
	
	for (int i = 0; i < 3; ++i) {
		suma = suma + (n%10);
		n = n/10;
	}
	cout << suma << endl;
}