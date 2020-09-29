#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> row;
typedef vector<row> Matriz;

void leer_matriz (Matriz& mat) {
	int fil = mat.size();
	int col = mat[0].size();
	
	for (int i = 0; i < fil; ++i) {
		for (int j = 0; j < col; ++j) {
			cin >> mat[i][j];
		}
	}
		 
}


int main() {
	int n, m;
	cin >> n >> m;
	Matriz mat(n, row(m));
	leer_matriz(mat);
	
	string cons;
	while (cin >> cons) {
		cout << cons << ' ';
		if (cons == "fila") {
			int fil;
			cin >> fil;
			cout << fil << ":";
			for (int i = 0; i < m; ++i) cout << ' ' << mat[fil-1][i];
		}
		
		else if (cons == "columna") {
			int col;
			cin >> col;
			cout << col << ":";
			for (int i = 0; i < n; ++i) cout << ' ' << mat[i][col-1]; 
		}
		
		else if (cons == "element") {
			int fil, col;
			cin >> fil >> col;
			cout << fil << ' ' << col << ": " << mat[fil-1][col-1];
		}
		
		cout << endl;
	}
}
