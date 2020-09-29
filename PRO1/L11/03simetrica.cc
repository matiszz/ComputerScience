#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<int> > Matriu;

bool es_simetrica(const Matriu& m) {
	
	int l = m.size();
	
	for (int i = 0; i < l; ++i) for (int j = 0; j < l; ++j) {
		if (m[i][j] != m[j][i]) return false;
	}
	return true;
	
}
