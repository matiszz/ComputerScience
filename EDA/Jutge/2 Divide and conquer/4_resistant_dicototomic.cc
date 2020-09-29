#include <iostream>
#include <vector>
using namespace std;

// Pot haver una inversió

bool cerca(double x, const vector<double>& v, int esq, int dre){
	if (esq > dre) return false;
	int m = (esq + dre)/2;
	if (x == v[m] and (m == 0 or v[m-1] != x)) return true;
	if (x > v[m]) {
		if (m >= 1)	return (v[m-1] == x or cerca(x, v, m+1, dre)); // Comprovo el de abans
		else return cerca(x, v, m+1, dre);
	}
	if (m < v.size()-1)	return (v[m+1] == x or cerca(x, v, esq, m-1)); // Comprovo el de després
	else return cerca(x, v, esq, m-1);
}


bool resistant_search(double x, const vector<double>& v) {
	return cerca(x, v, 0, v.size()-1);
}
