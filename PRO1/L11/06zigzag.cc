#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> col;
typedef vector<col> Matriu;

bool es_creixent(const Matriu& mat, int f, int c) {
	
	int ant = mat[0][0] - 1;
	/// j files, i columnes ///
	
	for (int i = 0; i < c; ++i) {
		
		if (i%2 == 0) {
			for (int j = 0; j < f; ++j) {
				if (ant >= mat[j][i]) return false;
				else ant = mat[j][i];
			}
		}
		else {
			for (int j = f - 1; j >= 0; --j) {
				if (ant >= mat[j][i]) return false;
				else ant = mat[j][i];
			}
		}
	}
	return true;
	
}

void llegeix_mat(Matriu& mat, int f, int c) {
	
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> mat[i][j];
	} 	}
	
}

int main () {
	int f, c;
	int count = 0;
	
	while (cin >> f >> c) {
		++count;
		
		Matriu mat(f, col(c));
		llegeix_mat(mat, f, c);
		
		cout << "matriu " << count << ": ";
		if(es_creixent(mat, f, c)) cout << "si";
		else cout << "no";
		cout << endl;
	}
}
