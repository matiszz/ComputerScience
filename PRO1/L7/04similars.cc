#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// PRE: Sequència de secuencies acabades amb 0, i amb l'ultima sequencia que es 0.
// POST: Dir quantes similars a la primera hi ha. Son similars si acaben igual i si sumen el mateix.

void info_sequencia(int& suma, int& ultim) {
	
	suma += next;
	while (next != 0) {
		cin >> next;
		ultim = next;
	}
	
}

int main() {
	int prim, act;
	int count = 1;
	
	while (act != 0) {
		
		// *** Inici de tractament de la sequencia petita ***
		
		int next, suma, ultim;
		info_sequencia(suma, ultim);
		cout << suma << " " << ultim;
		
		// *** Fi    de tractament de la sequencia petita ***
		
		if (act == prim) ++count;
	}
	cout << count << endl;
}
