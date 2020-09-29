#include <iostream>
#include <list>
using namespace std;

// PRE: Em donen una llista de parells acabades en 0 0 i un numero N
// POST: Imprimir N, #vegades que apareix N, suma de tots els seus companys.

struct parell {	int primer, segon; };

void llegir_llista_pair(list<parell>& l, int m1, int m2) {
	
	parell p;
	list<parell>::iterator it = l.begin();
	cin >> p.primer >> p.segon; 
	
	while (p.primer != m1 and p.segon != m2) {
		l.insert(it, p);
		cin >> p.primer >> p.segon;
	}
	
}

int main() {
	
	list<parell> l;
	llegir_llista_pair(l, 0, 0);
	int N;
	cin >> N;
	
	list<parell>::iterator it = l.begin();
	int count = 0;
	int sum = 0;
	
	while (it != l.end()) {
		if ((*it).primer == N) {
			++count;
			sum += (*it).segon;
		}
		++it;
	}
	
	cout << N << ' ' << count << ' ' << sum << endl;
	
}
