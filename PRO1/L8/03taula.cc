#include <iostream>
#include <vector>
using namespace std;

// PRE: n>0, n numeros, n posiciones.
// POST: Ordenar seq n de numeros segun la posicion.

int main() {
	int n;
	cin >> n;
	vector<int> V(2 * n);
	// Vector del numero seguido de su posición.
	for (int i = 1; i < 2*n; i += 2) cin >> V[i];
	for (int j = 0; j < 2*n - 1; j += 2) cin >> V[j];
	
	vector<int> aux(n);
	int pos;
	for (int k = 0; k < 2*n; ++k) {
		pos = V[k];
		++k;
		aux[pos] = V[k];
	}
	
	bool pr = true;
	for (int l = 0; l < n; ++l) {
		if (not pr) cout << ' ';
		cout << aux[l];
		pr = false;
	}
        
	cout << endl; 
}
