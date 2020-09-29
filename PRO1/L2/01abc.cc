#include <iostream>
using namespace std;

//Matias Szarfer
// Entrada: L’entrada és un natural n≥ 1 seguit de n caràcters a, b o c.
// Sortida: Cal escriure el caràcter majoritari, seguit de quantes
//          vegades apareix, segons el format dels exemples.

int main(){
	int n, as, bs, cs;
	cin >> n;
	
	//Comptadors per cada lletra
	as = 0;
	bs = 0;
	cs = 0;
	
	char letra;
	
	while (n >= 1) {
		cin >> letra;
		if (letra == 'a') ++as;
		else if (letra == 'b') ++bs;
		else ++cs;
		--n;
	}
	
	if (bs <= as and cs <= as) cout << "majoria de a" << endl << as <<" repeticio(ns)" << endl;
	else if (cs <= bs) cout << "majoria de b" << endl << bs <<" repeticio(ns)" << endl;
	else cout << "majoria de c" << endl << cs <<" repeticio(ns)" << endl;
	
}