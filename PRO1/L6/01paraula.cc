#include <iostream>
using namespace std;

int main() {
	string ant, act;
	
	cin >> ant >> act;
	
	// Escribir las palabras antes que la que esta mal ordenada.
	while (ant < act) {
		cout << ant << endl;
		ant = act;
		cin >> act;		
	}
	
	bool impreso = false;
	// Para el resto de las palabras
	while (act != "END") {
		if (not impreso and ant < act) {
			cout << ant << endl; // Escribe la palabra mal ordenada.
			impreso = true;
		}
		cout << act << endl; // Escribir el resto de la secuencia.
		cin >> act; // Leer el resto de la secuencia.
	}
	if (not impreso) cout << ant << endl;
	
}
