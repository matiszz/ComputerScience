/*
 * Created by Matias Szarfer - 2016
 * 
 * Dado n, r.
 * Pintar todas las formas de poner r reyes en tablero de nxn
 * sin que no se amenacen entre ellos, es decir, sin que
 * hayan reyes adyacentes.
 */

#include <iostream>
#include <vector>
using namespace std;

int n, r;
vector< vector<bool> > t;

void pintar() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (t[i][j]) cout << 'K';
            else cout << '.';
        }
        cout << endl;
    }
    cout << "----------" << endl;
}

bool posok(int i, int j) {
    if (t[i][j]) return false;
    if (i > 0 and t[i-1][j]) return false;
    if (j > 0 and t[i][j-1]) return false;
    if (j < n-1 and t[i][j+1]) return false;
    if (j > 0 and i > 0 and t[i-1][j-1]) return false;
    if (i > 0 and j < n-1 and t[i-1][j+1]) return false;
    if (i < n-1 and t[i+1][j]) return false;
    if (i < n-1 and j < n-1 and t[i+1][j+1]) return false;
    if (i < n-1 and j > 0 and t[i+1][j-1]) return false;
    return true;
}

void reyes(int i) {
    if (i == n) pintar();
    else {
        bool primero = true;
        for (int j = 0; j < r; ++j) {
            for (int k = 0; k < n; ++k) {
                if (primero) primero = false; k = b;
                if (posok(i,k)){
                    t[i][k] = true;
                    reyes(i+1);
                }
            }
        }
    }
}

int main() {
	cin >> n >> r;
    t = vector< vector<bool> >(n,  vector<bool>(n,false));
    reyes(0);
}
