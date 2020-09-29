/*
 * Created by Matias Szarfer - 2016
 */

#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> vecBol;
typedef vector<int>  vecInt;

int n;
vecBol c, d1, d2;
vecInt t; // i filas t[i] columnas

void pinta() {
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (t[i] == j) cout << 'Q';
            else cout << '.';
        }
        cout << endl;
    }
    cout << endl;
}

int dg1 (int i, int j) { return i+j; }
int dg2 (int i, int j) { return i-j + n-1; }

void reinas(int i) {
    if (i == n) pinta();
    else {
        for (int j = 0; j < n; ++j) {
            if(not c[j] and not d1[dg1(i,j)] and not d2[dg2(i,j)]) {
                t[i] = j;
                c[j] = d1[dg1(i,j)] = d2[dg2(i,j)] = true;
                reinas(i+1);
                c[j] = d1[dg1(i,j)] = d2[dg2(i,j)] = false;
            }
        }
    }
}

int main() {
	cin >> n;
    t = vecInt(n);
    c = vecBol(n, false);
    d1 = d2 = vecBol(2*n-1, false);
    reinas(0);
}
