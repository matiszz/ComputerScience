#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// PRE: Cadena de A, C, T o G
// POST: A partir de TAG,    A <-> T    i    C <-> G.   Si no TAG -> 0


char complement(char c) {
	
	// Complementaris
	if (c == 'A') return 'T';
	else if (c == 'T') return 'A';
	else if (c == 'C') return 'G';
	else if (c == 'G') return 'C';
	else return 0;
	
}


int main() {
	char a;
	int it = 1;
	bool seq = false;
	
	while (not seq and cin >> a) {
		if (it == 1) {
			if (a == 'T') it = 2; }
			
		else if (it == 2) {
			if (a == 'A') it = 3;
			else if (a != 'A' or a != 'T') it = 1; }
		
		else if (it == 3) {
			if (a == 'G') seq = true;
			else if (a == 'T') it = 2;
			else it = 1; }
	}
	
	if (seq == true) while (cin >> a) cout << complement(a);
	cout << endl;;
}
