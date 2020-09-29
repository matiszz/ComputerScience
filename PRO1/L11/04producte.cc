#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<int> > Matriu;

int fes(int n, int m, const Matriu& a, const Matriu& b) {
	
	int res = 0;
	for (int i = 0; i < a.size(); ++i) res += a[n][i]*b[i][m];
	
	return res;
}

Matriu producte(const Matriu& a, const Matriu& b) {
	int m = a.size();
	Matriu R(m, vector <int>(m));
	
	for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) {
		R[i][j] = fes(i, j, a, b);
	}
	
	return R;
}

void llegir(Matriu& mat) {
	int n = mat.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> mat[i][j];
		}
	}	 
}

int main(){
	int n;
	
	cout << "Matriu 1:" << endl;
	cin >> n;
	Matriu M1(n, vector<int>(n));
	llegir(M1);
	
	cout << endl << "Matriu 2:" << endl;
	cin >> n;
	Matriu M2(n, vector<int>(n));
	llegir(M2);
	
	Matriu R(n, vector<int>(n));
	R = producte(M1, M2);
	
	cout << endl << "Resultat:" << endl;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
			cout << R[i][j] << ' ';
			if (j == n-1) cout << endl;
	}	
	
}
