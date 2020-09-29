#include <iostream>
#include <string>
using namespace std;

// PRE: Secuencia de 12 dígitos.
// POST: 12 digitos + el 13o.

int main() {
	
	string v;
	while (cin >> v) {
		
		int sum = 0;
		
		for (int i = 11; i >= 0; --i) {
			if (i%2 == 0) sum += (v[i] - 48);
			else sum += (v[i] - 48)*3;
		}
		
		int digit = 10 - sum%10;
		if (digit == 10) digit = 0;
		
		cout << v << digit << endl;
	}
}
