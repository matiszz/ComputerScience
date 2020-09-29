/*
 * Created by Matias Szarfer - 2016
 * 
 * Dado n, u, (u <= n)
 * Escribir todas las combianciones de n-u ZEROS i u UNOS
 */

#include <iostream>
#include <vector>
using namespace std;

void escribir(vector<int>& v) {
    
    bool primer = true;
    for (int i = 0; i < v.size(); ++i) {
        if (primer) {
            primer = false;
            cout << v[i];
        }
        else cout << ' ' << v[i];
    }
    cout << endl;
}

void binario (int i, vector<int>& v, int z, int u, int zeros, int unos) {
    
    if (i == v.size()) escribir(v);
    else {
        if (z < zeros) {
            v[i] = 0;
            binario(i+1, v, z+1, u, zeros, unos);
        }
        if (u < unos) {
            v[i] = 1;
            binario(i+1, v, z, u+1, zeros, unos);
        }
    }
}

int main() {
	int n, u;
    cin >> n >> u;
    vector<int> v(n);
    
    binario(0, v, 0, 0, n-u, u);
}
