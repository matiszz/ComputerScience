#include <iostream>
#include <list>
using namespace std;

// PRE: Em donen una llista de parells <codi, num> acabades en 0 0.
// POST: Per cada entrada, imprimir mínim, màxim i mitjana dels nombres.

struct parell {	int codi, num; };

void llegir_llista_pair(list<parell>& l, int m1, int m2) {
	
	parell p;
	list<parell>::iterator it = l.begin();
	
	
}

int main() {
	
	list<parell> l;
	
	list<parell>::iterator it = l.begin();
	
	cin >> p.codi >> p.num; 
	while (p.codi != 0 and p.num != 0) {
		if (p.codi = '-1') { // Afegir el nombre
			l.insert(it, p);
			
			// CODI AQUI
			
		} else if (codi = '-2') { // Eliminar el nombre
			
			// CODI AQUI
			
		}
			
		cin >> p.codi >> p.num;
	}
	
	if (l.empty()) cout << '0' << endl;
	else cout << min << ' ' << max << ' ' << mitjana << endl;
	
}
