#include <iostream>
using namespace std;

// PRE: Secuencia de pares n,k
// POST: Por cada par, escribir n en binario representado con k bits


void write_binary(int n, int k) {
	
	if (k != ) {
		write binary (n/2, k-1);
		cout << n%2;
	}
	
}

int main () {
	int n, k;
	while (cin >> n >> k) write_binary(n, k);
	cout << endl;
}
