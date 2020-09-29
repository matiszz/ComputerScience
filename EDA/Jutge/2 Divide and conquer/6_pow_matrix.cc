#include <iostream>
#include <vector>
using namespace std;

// Computar M^n  mod m.

typedef vector< vector<long long> > Matrix;

void escribir(Matrix M) {
    cout << M[0][0] << ' ' << M[0][1] << endl;
    cout << M[1][0] << ' ' << M[1][1] << endl;
}

Matrix mult(Matrix& A, Matrix& B, int m) {
    Matrix C (2, vector<long long> (2));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                C[i][j] += (A[i][k] * B[k][j])%m;
            }
        }
    }
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            C[i][j] = (C[i][j])%m;
        }
    }
    
    return C;
}

void pot(Matrix& M, int n, int m) {
   
    Matrix R (2, vector<long long> (2,0));
    R[0][0] = (M[0][0])%m;
    R[0][1] = (M[0][1])%m;
    R[1][0] = (M[1][0])%m;
    R[1][1] = (M[1][1])%m;
    
    
    if (n == 0) {
        M[0][0] = M[1][1] = 1;
        M[0][1] = M[1][0] = 0;
        return;
    }
    if (n == 1) {
        M = R;
        return;
    }
    else if (n%2 == 1) {
        pot(M, n-1, m);
        M = mult(M, R, m);
        return;
    }
    else {
        pot(M, n/2, m);
        M = mult(M, M, m);
        return;
    }
}

int main() {
    
    long long a, b, c , d;
    
    while (cin >> a >> b >> c >> d) {
        Matrix M (2, vector<long long> (2));
        
        M[0][0] = a;
        M[0][1] = b;
        M[1][0] = c;
        M[1][1] = d;
        
        int n, m;
        cin >> n >> m;
        
        pot(M, n, m);
        
        escribir(M);
        cout << "----------" << endl;
    }
}
