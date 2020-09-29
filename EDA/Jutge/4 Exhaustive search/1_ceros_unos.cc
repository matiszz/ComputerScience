#include <iostream>
#include <vector>
using namespace std;

void escriu(vector<int>& v) {
    
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

void binari(int i, vector<int>& v) {
    
    int n = v.size();
    
    if (i == n) escriu(v);  // Cas base
    else {                  // Cas inductiu
        binari(i+1, v);
        v[i] = 1;
        binari(i+1, v); 
        v[i] = 0;
    }
}

int main() {
    
    int n;
    cin >> n;
    vector<int> v(n);
    
    binari(0, v);
}
