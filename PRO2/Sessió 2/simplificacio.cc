#include "Estudiant.hh"
#include <iostream>
#include <vector>
using namespace std;

typedef vector<Estudiant> vec;

void llegirVector(vec& v){
	int mida;
	cin >> mida;
	v = vec(mida);
	
	for(int i = 0; i < mida; ++i){
		int dni;
		double nota;
		cin >> dni;
		Estudiant est(dni);
		v[i] = est;
		cin >> nota;
		if (0 <= nota and nota <= 10) v[i].afegir_nota(nota);
	}
}

void escriureVector(const vec& v) {
	for (int i = 0; i < v.size(); ++i) v[i].escriure();
}

void simplificar(const vec& v, vec& u) {
	int iteracio = -1;
	int dni = -2;
	
	for (int i = 0; i < v.size(); ++i) {
		int DNI = v[i].consultar_DNI();
		if (DNI != dni) {
			dni = DNI;
			++iteracio;
			Estudiant est(DNI);
			u[iteracio] = est;
			
			if (v[i].te_nota()) {
				double nota = v[i].consultar_nota();
				u[iteracio].afegir_nota(nota);
			}
			
		} else {
			if (v[i].te_nota()) {
				if (u[iteracio].te_nota()) {
					double nota = v[i].consultar_nota();
					if (u[iteracio].consultar_nota() < nota) u[iteracio].modificar_nota(nota);
				} else {
					double nota = v[i].consultar_nota();
					u[iteracio].afegir_nota(nota);
				}
			}
		}
	}
}

int novaMida(const vec& v) { // Calcula la mida del nou vector
	int mida_nova = 0;
	int dni = -2;
	
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].consultar_DNI() != dni) {
			dni = v[i].consultar_DNI();
			++mida_nova;
		}
	}
	return mida_nova;
}

int main () {
	vec entrada;
	llegirVector(entrada);
	
	int n = novaMida(entrada);
	vec sortida(n);
	simplificar(entrada, sortida);
	
	escriureVector(sortida);
}
