#include "Estudiant.hh"
#include <iostream>
#include <vector>
using namespace std;

// PRE: M (num est), N (num assig), S (num assig seleccionades).
//		a, b = assig per fer mitjana.
//		M vegades: DNI, N Assig.

// POST: Per cada estudiant, tornar: DNI + mitjana (= (a+b)/S)

typedef vector<int> vec;

bool guardar(int assignatura, const vec& s) {
	
	for(int i = 0; i < s.size(); i++) if((s[i] - 1) == assignatura) return true;
	return false;
	
}
 
int main() {
	int M, N, S;
	cin >> M >> N >> S;
	
	// Llegir
	vec assig(S);
	for(int i = 0; i < S; i++) cin >> assig[i];
	
	// Calcular mitjana
	vector<Estudiant> est(M);
	for(int i = 0; i < M; i++) {
		int dni;
		double mitjana = 0;
		cin >> dni;
		Estudiant estudiant = Estudiant(dni);
		
		for(int j = 0; j < N; j++) {
			double k;
			cin >> k;
			if(guardar(j, assig)) mitjana = mitjana + k;
		}
		
		mitjana = mitjana/S;
		estudiant.afegir_nota(mitjana);
		est[i] = estudiant;
	}
	
	// Escriure
	for(int i = 0; i < M; i++) est[i].escriure();
}
