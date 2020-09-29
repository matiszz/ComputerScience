#include <iostream>
#include <string>
#include <set>
using namespace std;

// ENTRADA: Llista de strings acabada en punt, n = #activitats, n llistes de jugadors.
// SORTIDA: ”Totes les activitats: ” / ”Cap activitat: ”.

void llegir_set(set<string>& jugadors) {
	string j;
	cin >> j;
	while (j != ".") {
		jugadors.insert(j);
		cin >> j;
	}
}

void separa (set<string> totes, set<string> cap, set<string> act) {
	// A "cap" tinc tots els jugadors que encara no han fet cap activitat
	// A "totes" els que han fet alguna activitat.
	// A "act" els d'aquesta activitat
	
	for (int 
	string j;
	cin >> j;
	while (j != '.') {
		cap.erase(j); // Esborro de cap el jugador.
		
	}
	// Al final vull que a "cap" quedin els jugadors que no han aparegut.
}

int main() {
	
	set<string> cap;
	llegir_set(cap);
	
	int a;
	cin >> a;
	
	set<string> totes;
	// Cap = tots els jugadors
	// Totes = 0 jugadors
	for (int i = 1; i <= a; ++i) {
		set<string> act;
		llegir_set(act);
		separa (totes, cap, act);
	}
	// Cap = jugadors que no han aparegut.
	// Totes = els que han fet a activitats.
		
}
