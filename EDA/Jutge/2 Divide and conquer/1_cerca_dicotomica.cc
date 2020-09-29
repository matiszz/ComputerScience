#include <iostream>
#include <vector>
using namespace std;

// Retornar posició dins del vector de x;
// PRE: v ordenat creixentment.
//      0 ≤ esq ≤ mida de v 
//		−1 ≤ dre < mida de v.
int posicio(double x, const vector<double>& v, int esq, int dre){
	if (esq > dre) return -1;
	int mid = (esq + dre)/2;
	if (x < v[mid]) return posicio(x, v, esq, mid-1);
	else if (x > v[mid]) return posicio(x, v, mid+1, dre);
	return mid;
}
