#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// Escriu la barreja de les representacions en base 2 de dos
// naturals donats x i y amb el mateix nombre de bits n

void barreja(int n, int m) {
	if (n > 0 and m > 0) {
		barreja(n/2, m/2);
		cout << n%2 << m%2;
	}
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		barreja(n, m);
		cout << endl;
	}
}
