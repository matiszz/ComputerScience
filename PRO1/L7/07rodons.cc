#include <iostream>
using namespace std;

// PRE: Secuencia de parells x, b am b >= 2
// POST: Escriure si és rodona o no.
// Es redondo si la suma de las cifras en base b = numero de cifras en esa base


int sum(int n, int b) {
	if (n < b) return n;
	else return n%b + sum (n/b, b)
}


bool rodo (int n, int b) {
	int 
}


int main() {
	
}
