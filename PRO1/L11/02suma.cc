#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<int> > Matriu;

Matriu suma(const Matriu& a, const Matriu& b) {
	
	int f = a.size();
	Matriu r(f, vector<int>(f));
	
	for (int i = 0; i < f; ++i) for (int j = 0; j < f; ++j) {
		r[i][j] = a[i][j] + b[i][j];
	}
	
	return r;
}
