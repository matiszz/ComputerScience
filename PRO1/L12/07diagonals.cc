#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Rows;
typedef vector<Rows> Matriz;

bool seguent(int& acti, int& actj, int inci, int incj, int n, int m) {
	acti = acti + inci;
	actj = actj + incj;
	return (acti >= 0 and acti < n and actj >= 0 and actj < m);
}

bool creix (const Matriz& mat, int i, int j, int inci, int incj) {
	int acti, actj, anti, antj;
	anti = acti = i;
	antj = actj = j;
	
	int n = mat.size();
	int m = mat[0].size();
	
	while (seguent(acti, actj, inci, incj, n, m)) {
		// Tratar elemento actual
		if (mat[anti][antj] >= mat[acti][actj]) return false;
		anti = acti;
		antj = actj;
	}
	return true;
}

// Pre: matriz como mínimo tendrá un elem
void leer_matriz (Matriz& mat) {
	int row = mat.size();
	int col = mat[0].size();
	
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			cin >> mat[i][j];
		}
	}
		 
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		Matriz mat(n, Rows(m));
		leer_matriz(mat);
		int i, j;
		cin >> i >> j;
		
		if (creix(mat, i, j,  1,  1) and
			creix(mat, i, j,  1, -1) and
			creix(mat, i, j, -1,  1) and
			creix(mat, i, j, -1, -1)) cout << "si" << endl;
		else cout << "no" << endl;
	}
}
