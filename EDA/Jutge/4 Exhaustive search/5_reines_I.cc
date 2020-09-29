/*
 * Created by Matias Szarfer - 2016
 * 
 * Dado n,
 * Calcular el número de posibilidades de poner n reinas
 * en un tablero nxn sin que haya ninguna reina compartiendo
 * fila, columna, o diagonal.
 * 
 *      Para ver si las reinas de las filas i y k comparten...
 *      - Columna: t[i] == t[k].
 *      - Diagonal desc: t[i]-i == t[k]-k;
 *      - Diagonal asce: t[i]+i == t[k]+k;
 */

#include <iostream>
#include <vector>
using namespace std;

int n;          // Medida tablero.
vector<bool> mc, md1, md2;
    // donde i es columna, y mc[i] dice si ya hay una reina en i.
    // donde md1[k] dice si ya hay reina en la diagonal i+j = k;
int count = 0;

int diag1(int i, int j) {
    return i+j;
}

int diag2(int i, int j) {
    return i-j + n-1;
}

void reinas(int i) {
    
    if (i == n) ++count;
    else {
        for (int j = 0; j < n; ++j) {
            if (not mc[j] and
                not md1[diag1(i,j)] and
                not md2[diag2(i,j)]) { 
                    
                    mc[j] = md1[diag1(i,j)] = md2[diag2(i,j)] = true;
                    reinas(i+1);
                    mc[j] = md1[diag1(i,j)] = md2[diag2(i,j)] = false;
                }
        }
    }
}

int main() {
    cin >> n;
    mc = vector<bool>(n, false);
    md1 = md2 = vector<bool>(2*n-1, false);
    
    reinas(0);
    cout << count << endl;
}
