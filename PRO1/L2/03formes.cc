#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// Donat un nombre, fa una figura.

int main() {
	int n;
	cin >> n;
	
	for (int i = n; i > 0; --i) {
		//for (int j = i - 1; j > 0; --j) cout << "+";
		for (int j = 0; j < i - 1; ++j) cout << '+';
		cout << "/";
		for (int j = 0; j < n - i; ++j) cout << "*";
		cout << endl;
	}
}
