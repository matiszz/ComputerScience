#include <iostream>
#include <vector>
using namespace std;

// PRE: n >= 1, seguido de n enteros.
// POST: Reescriure amb el criteri d'ordenació. Separar amb endl.

// Criteri: 1r, ultim, 2n, penultim, 3r, abantpenultim...

int main() {
	int n;
	while (cin >> n) {
	
		vector<int> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];
		
		bool primer = true;
		int c = 0;
		
		for (int i = 0; i < n; ++i) {
			if (primer) primer = false;
			else cout << ' ';
			
			if (i%2 == 0) {
				cout << v[c];
				++c;
			}
			else cout << v[n - c];
		}
		
		cout << endl;
	}
}
