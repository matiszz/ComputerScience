#include <iostream>
#include <list>
using namespace std;

// PRE: Em donen una llista de parells acabades en 0 0 i un dni N
// POST: Imprimir N, seguit del ombre de vegades que apareix

struct parell {	int dni, nota; };

void llegir_llista_pair(list<parell>& l, int m1, int m2) {
	
	parell p;
	list<parell>::iterator it = l.begin();
	cin >> p.dni >> p.nota; 
	
	while (p.dni != m1 and p.nota != m2) {
		l.insert(it, p);
		cin >> p.dni >> p.nota;
	}
	
}

int main() {
	
	list<parell> l;
	llegir_llista_pair(l, 0, 0);
	int N;
	cin >> N;
	
	list<parell>::iterator it = l.begin();
	int count = 0;
	
	while (it != l.end()) {
		if ((*it).dni == N) {
			++count;
		}
		++it;
	}
	
	cout << N << ' ' << count << endl;
	
}
