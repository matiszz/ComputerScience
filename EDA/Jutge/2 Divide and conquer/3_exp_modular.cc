#include <iostream>
using namespace std;

// Entrada: n, k, m; Tal que n , m > 2
// Sortida: n^k mod(m)

int mipow(int n, int k, int m) {
	if (k == 0) return 1;
	int aux = (mipow(n, k/2, m))%m;
	aux = (aux*aux)%m;
	if (k%2 == 0) return aux; // n parell
	return (aux*n)%m;
}

int main() {
	int n, k, m;
	while (cin >> n >> k >> m) {
		cout << mipow(n, k, m) << endl;
	}
}
