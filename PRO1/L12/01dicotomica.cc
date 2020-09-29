#include <iostream>
#include <vector>
using namespace std;

// PRE: v creixent. 0 <= esq <= v.size()
//					-1 <= dre < v.size()
// POST: Retorna pos on esta x dins del vector v[esq ... dre].
// 		 Si x no està, o esq > dre, retorna -1

int posicio(double x, const vector<double>& v, int esq, int dre) {
	
	if (esq > dre) return -1;
	int mid = (esq + dre) / 2;
	if (v[mid] > x) return posicio(x, v, esq, mid - 1);
	if (v[mid] < x) return posicio(x, v, mid + 1, dre);
	return mid;
	
}
