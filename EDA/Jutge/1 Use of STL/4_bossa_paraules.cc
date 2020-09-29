#include <iostream>
#include <map>
using namespace std;

//store p; delete p; maximum?; minimum?

int main() {
    
    map<string, int> m;
    string instr;
    
    while (cin >> instr) {
        
        map<string, int>::iterator it;
        string p;
        
        if (instr == "store") {
            cin >> p;
            m[p]++;
        } else if (instr == "delete") {
            cin >> p;
            m[p]--;
            it = m.find(p);
            if (m[p] <= 0) m.erase(p);
        } else if (instr == "minimum?") {
            if (m.size() == 0) cout << "indefinite minimum" << endl;
            else {
                it = m.begin();
                cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
        } else if (instr == "maximum?") {
            if (m.size() == 0) cout << "indefinite maximum" << endl;
            else {
                it = m.end();
                it--;
                cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
        }
    }
}
