#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// PRE: Seq >= 3, acabado en 0.
// POST: Indicar si hay un pico > 3143 o no.

int main() {
	
	int ant, mig, succ;
	cin >> ant >> mig >> succ;
	bool encontrado = false;
	
	while (not encontrado and succ != 0) { // Es de búsqueda, si ya lo hemos encontrado puede acabar. Si no, cuando llegue la centinela
		
		if (mig > 3143 and ant < mig and mig > succ) encontrado = true;
		
		ant = mig;
		mig = succ;
		cin >> succ; // Siguiente succ
	}
	
	if (encontrado) cout << "SI" << endl;
	else			cout << "NO" << endl;
}
