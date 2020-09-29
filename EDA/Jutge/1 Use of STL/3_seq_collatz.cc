#include <iostream>
#include <map>
using namespace std;

const int MAX = 100000000;

void collatz(int x, int y, int& n) {
    if(n%2 == 0) n = (n/2) + x;
    else n = (3*n) + y;
}

int main() {
    
    int x, y, n;
    
    while (cin >> x >> y >> n) {
        
        map<int, int> M;
        map<int, int>::iterator it;
        bool cicle = false;
        int i = 0;
        M[n] = i;
        
        while (n <= MAX and not cicle) {
            ++i;
            collatz(x,y,n);
            it = M.find(n);
            if(it == M.end()) M[n] = i;
            else cicle = true;
        }
        if (cicle) cout << (M.size() - it->second) << endl;
        else cout << n << endl;
    }
    
}
