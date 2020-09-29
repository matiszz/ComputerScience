#include <iostream>
#include <vector>
using namespace std;

// ENTRADA: n, Seq S, m, a's

// SORTIDA: Numero des de 1. Per cada aj, posició del fixed point. Si no existeix, misstage.
//			Si hi ha més d'un, mostrar el més petit.

void llegirVector(int n, vector<int>& V) {
	for (int i = 0; i < n; ++i) cin >> V[i];
}

void fixed_rec(int e, int d, vector<int>& S, int a, int &pos) {
	if (e > d) return;
	int m = (e+d)/2;
	if (S[m] + a == m + 1) {
		pos = m+1;
		fixed_rec(e, m-1, S, a, pos);
	}
	else if (S[m] + a < m + 1) fixed_rec(m+1, d, S, a, pos);
	else fixed_rec(e, m-1, S, a, pos);
}

int fixed(int e, int d, vector<int>& S, int a) {
     int pos = -1;
     fixed_rec( e, d, S, a, pos);
     return pos;
}

void imprimeix(int n, vector<int>& S, int num_a, vector<int>& A) {
	for (int i = 0; i < num_a; ++i) {
		int res = fixed(0, n, S, A[i]);
		if (res == -1) cout << "no fixed point for " << A[i] << endl;
		else cout << "fixed point for " << A[i] << ": " << res << endl;
	}
	cout << endl;
}

int main() {
	
	int cas = 1;
	int n;
	
	while (cin >> n) {
		vector<int> S(n);
		llegirVector(n, S);
		
		int num_a;
		cin >> num_a;
		vector<int> A(num_a);
		llegirVector(num_a, A);
		
		cout << "Sequence #" << cas << endl;
		imprimeix(n, S, num_a, A);
		
		++cas;
	}
}

/*

int posicio(double x, const vector<double>& v, int esq, int dre){
	if (esq > dre) return -1;
	int mid = (esq + dre)/2;
	if (x < v[mid]) return posicio(x, v, esq, mid-1);
	else if (x > v[mid]) return posicio(x, v, mid+1, dre);
	return mid;
}

*/
