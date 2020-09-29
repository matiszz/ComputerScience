/*
 * Created by Matias Szarfer - 2016
 * 
 * Donat n, m, n files, m caràcters.
 * . = Buit
 * X = Obstacle
 * y = Tresor
 * f, c indiquen posició inicial. Dir si es pot arribar a algun tresor.
 */

#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<char> > Mapa;

void leer(Mapa& M, int n, int m) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> M[i][j];
        }
    }    
}

void imprimir(Mapa& M, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << M[i][j];
        }
        cout << endl;
    }    
}

bool tresor(Mapa& M, int f, int c) {
    
    if (M[f][c] == 't') return true;
    if (M[f][c] == 'X') return false;
    
    M[f][c] = 'X';
    return (
        tresor(M,f+1,c) or 
        tresor(M,f-1,c) or 
        tresor(M,f,c+1) or 
        tresor(M,f,c-1));
}

int main() {
	
	int n, m, f, c;
    cin >> n >> m;
    
    Mapa M (n+2, vector<char> (m+2, 'X'));
    leer(M, n, m);
    
    cin >> f >> c;
    
    if (tresor(M,f,c)) cout << "yes" << endl;
    else cout << "no" << endl;
}

