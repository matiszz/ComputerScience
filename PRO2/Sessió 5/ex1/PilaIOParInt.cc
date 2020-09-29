#include "PilaIOParInt.hh"
#include "ParInt.hh"

void llegirPilaParInt(stack<ParInt>& p) {
	ParInt par;
	while (par.llegir()) {
		p.push(par);
	}
}
// Post: s’apilen el elements llegits a la pila p


void escriurePilaParInt(stack<ParInt> p) {
	while(not p.empty()){ 
		p.top().escriure();
		p.pop();
    }
}
// Post: s’escriuen el elements de la pila p i p queda buida 
