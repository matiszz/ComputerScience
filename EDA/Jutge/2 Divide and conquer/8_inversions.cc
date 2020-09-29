/*
 * Created by Matias Szarfer - 2016
 * 
 * The program counts the number of inversios on a given sequence of ints.
 * Inversion ==> i < j, but v[i] > v[j], in a vector.
 */

#include <iostream>
#include <vector>
using namespace std;

int inversions(const vector<int>& v) {
   
    int count = 0;
    
    for (int i = 0; i < v.size(); ++i) {
        int x = v[i];
        for (int j = i+1; j < v.size(); ++j) {
            if (x > v[j]) ++count;
        }
    }
    return count;
}

int main() {
    
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        cout << inversions(v) << endl;
    }
}
