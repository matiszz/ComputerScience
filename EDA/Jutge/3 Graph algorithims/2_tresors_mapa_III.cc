#include <iostream>
#include <vector>
using namespace std;

// Entrada: n m; n,m > 0. n files, m carÄ‚Â cters (columnes). t = tresor. . = buit. X = obstacele. f i c pos inicial.
//			1 <= f <= n; 1 <= c <= m; Pos inicial buida.

typedef vector<char> vc;
typedef vector<vc> Mapa;
int accessibles = 0;

void tresor (Mapa& M, int f, int c) {
	if (M[f][c] == 't') {
		++accessibles;
		M[f][c] == 'X';
	}
	
	if (M[f][c] != 'X') {
		M[f][c] = 'X';
		tresor(M, f-1, c);
		tresor(M, f+1, c);
		tresor(M, f, c-1);
		tresor(M, f, c+1);
	}
}

int main () {
	int n, m;
	
	cin >> n >> m;
	Mapa M(n+2, vc(m+2, 'X'));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> M[i][j];
	}
	
	int f, c;
	cin >> f >> c;
	
	tresor(M, f, c);
	
	cout << accessibles << endl;
}

