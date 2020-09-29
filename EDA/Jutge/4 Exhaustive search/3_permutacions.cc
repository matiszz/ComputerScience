/*
 * Created by Matias Szarfer - 2016
 */

#include <iostream>
#include <vector>
using namespace std;

void escribir(vector<int>& v) {
    
    cout << '(' << v[0];
    
    for (int i = 1; i < v.size(); ++i) {
        cout << ',' << v[i];
    }
    cout << ')' << endl;
}

void perm(int i, vector<int>& v, vector<bool> usado) {
    
    int n = v.size();
    if (i == n) escribir(v);
    else {
        for (int j = 0; j < n; ++j) {
            if (not usado[j]) {
                usado[j] = true;
                v[i] = j+1;
                perm(i+1, v, usado);
                usado[j] = false;
            }
        }
    }
}

int main() {
	
	int n;
    cin >> n;
    vector<int> v(n);
    vector<bool> usado(n);
    
    perm(0, v, usado);
}
