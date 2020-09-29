#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

// PRE: 2 naturals a i b amb b >= 1;
// POST: x més petit tal que x >= a, i x = mb

int mcm(int a, int b) {
	
	int m;
	if (a%b == 0) m = a;
	else m = (a / b) * b + b;
	return m;
	
}



int main() {
	
	int a, b;
	int it = 1;
	
	while (cin >> a >> b) {
		cout << "#" << it << " : " << mcm(a, b) << endl;
		++it;
	}
}
