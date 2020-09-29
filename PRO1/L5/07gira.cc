#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// Llegeix una seqüència de paraules fins a la primera
// ocurrència de la paraula “fi”, i l'escriu en ordre invers.

// Pre: parámetro implícito: entrada -> lista de palabras acabadas en fi
// Post: escribe giradas las palabras en la entrada
void gira() {
	string s;
	cin >> s;
	int a = 0;
	if (s != "fi") {
		gira(); // gira la entrada en ese momento (E: que tal fi)
		// S: tal que
		cout << s;
		// S: tal que hola
		++a;
	}
	if (a != 0) cout << endl;
}

int main() {
	gira(); // E: hola que tal fi
}
