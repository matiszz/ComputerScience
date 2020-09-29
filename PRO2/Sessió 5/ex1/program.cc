#include <iostream>
#include <stack>
#include "PilaIOParInt.hh"
#include "ParInt.hh"
using namespace std;

// PRE:  Una seqüencia de parells d’enters acabada en 0 0 i un enter n.

// POST: S’escriu la pila i a continuació, si n éxisteix com primer
//		 enter d’un parell s’escriu el segon, en cas contrari s’escriu
//		 “No trobat”. Si n’hi ha més d’un, només es té en compte la
//		 primera aparició des d’el cim.

void escriureNum (stack<ParInt>& p, int n) {
	bool found = false;
	while(not p.empty() and not found){ 
		if (p.top().primer() != n) p.pop();
		else {
			cout << p.top().segon() << endl;
			found = true;
		}
    }
    if (not found) cout << "No trobat" << endl;
}

int main() {
	stack<ParInt> p;
	llegirPilaParInt(p);
	
	int n;
	cin >> n;
	
	escriurePilaParInt(p);
	escriureNum(p, n);
}
