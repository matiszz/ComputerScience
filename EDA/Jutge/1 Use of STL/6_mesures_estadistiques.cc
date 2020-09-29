#include <iostream>
#include <map>
using namespace std;

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    
    map<int, int> m;
    string instr;
    
    while (cin >> instr) {
        
        map<int, int>::iterator it;
        double avg = 0.0000;
        int nums = 0;
        
        if (instr == "number") {
            ++nums;
            int x;
            cin >> x;
            m[x]++;
            avg += double(x);
            
            it = m.begin();
            cout << "minimum: " << it->first;
            
            it = m.end();
            --it;
            cout << ", maximum: " << it->first;
            
            cout << ", average: " << (double)avg/(double)nums << endl;
            
        } else if (instr == "delete") {
            if (m.size() == 0) cout << "no elements" << endl;
            else {
                --nums;
                it = m.begin();
                int x = it->first;
                m[x]--;
                if (m[x] <= 0) m.erase(x);
                avg = (avg-x)/nums;
            }
        }
    }
}
