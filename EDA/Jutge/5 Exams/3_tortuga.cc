/*
 * Created by Matias Szarfer - 2016
 * 
 * INT: n, m, n linies, m lletres. f,c ini, f,c desti.
 * Escriure camí del terra nxm entre inici i desti.
 */

#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matriz;
typedef vector< vector<bool> > M_Vistos;

int n, m, xi, yi, xd, yd;
Matriz M;
Row cam;

void leer() {
    
    cin >> n >> m;
    M = Matriz(n, Row(m));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> M[i][j];
        }
    }
    
    cin >> xi >> yi >> xd >> yd;
}

void escribir() {
    for (int i = 0; i < cam.size(); ++i) cout << cam[i];
    cout << endl;
}

void camino(int x, int y, M_Vistos visto) {
    if (x >= 0 and x < n and y >= 0 and y < m and not visto[x][y]) {
        visto[x][y] = true;
        cam.push_back(M[x][y]);
        if (x == xd and y == yd) escribir();
        else {
            camino(x+1, y, visto);
            camino(x-1, y, visto);
            camino(x, y+1, visto);
            camino(x, y-1, visto);
        }
    }
}

int main() {
	leer();
    
    M_Vistos visto(n, vector<bool>(m, false));
    camino(xi, yi, visto);
}
