#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// PRE: Sequencia de n
// POST: Por cada n, sacar el valor de 2^n

int two_to_n(int n) {
	
	if (n == 0) return 1;
	else return 2 * two_to_n(n-1);

}

int main() {
	
	int n;
	while (cin >> n) cout << two_to_n(n) << endl;
	
}
