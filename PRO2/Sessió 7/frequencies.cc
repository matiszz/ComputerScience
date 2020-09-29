#include <iostream>
#include <string>
#include <map>
using namespace std;

// PRE: Entrada a o f seguit d'un string.
// POST: Si el codi és f, imprimir la freqüència.
//		 Si el codi es a, afegir al diccionari.

struct freq {
	int f;
};

map<string, freq> d;

int main() {
	
	char c;
	while (cin >> c) {
		string par;
		cin >> par;
		if (c == 'a') ++d[par].f;
		if (c == 'f') cout << d[par].f << endl;
	}
}
