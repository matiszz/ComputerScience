#include "Estudiant.hh"
#include <iostream>
#include <vector>
using namespace std;

// PRE: M (num est), N (num assig), S (num assig seleccionades).
//		a, b = assig per fer mitjana.
//		M vegades: DNI, N Assig.

// POST: Per cada estudiant, tornar: DNI + mitjana (= (a+b)/S)

typedef vector<int> vec;

void llegirEstudiant(Estudiant est, int S, const vec& v){ // Només llegeix les assignatures seleccionades.
	
	for (int i = 0; i < S; ++i) {
		for (int j = 0; j < S; ++j) {
			if (i == v[j]) {
				double nota;
				cin >> nota;
				est.afegir_nota(nota);
			} else { // No fa res.
				double brossa;
				cin >> brossa;
			}
		}
	}
}

double calcularMitjana(const Estudiant est, int S) { // Tenim un est amb totes les notes 
													 // importants, i el nº de notes.
	double mitjana;
	for (int i = 0; i < S; ++i) mitjana += est.consultar_nota();
	return mitjana;
	
}

int main() {
	int M, N, S;
	cin >> M >> N >> S;
	
	// Vector amb les assignatures seleccionades.
	vec assig(S);
	for (int i = 0; i < S; ++i) cin >> assig[i];
	
	// Per a cada estudiant.
	for (int i = 0; i <= M; ++i) {
		int dni;
		cin >> dni;
		Estudiant est(dni);
		llegirEstudiant(est, S, assig);
		
		double mitjana = calcularMitjana(est, S);
		
		cout << est.consultar_DNI() << ' ' << mitjana << endl;
	}
}
