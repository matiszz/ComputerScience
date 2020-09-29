#include <iostream>
#include <vector>
#include <string>
using namespace std;

// PRE: n seguit de n paraules-
// POST: Escriure la paraula més llarga i totes les lletres que no estan a la sequencia.


const int LONG_ALFABET = 'z' - 'a' + 1;


void escriu_fals(const vector<bool>& v) {
	for (int i = 0; i < LONG_ALFABET; ++i) {
		if (not v[i]) cout << char('a' + i) << endl;
	}
}

int main() {
	int n;
	cin >> n;
	
	string palabra, biggest;
	vector<bool> v(LONG_ALFABET, false);
	int max = 0;
	int mida = 0;
	
	for (int i = 0; i < n; ++i) {
		cin >> palabra;
		// Se queda con la más grande
		mida = palabra.size();
		if (mida > max) {
			biggest = palabra;
			max = mida;
		}
		
		for (int j = 0; j < mida; ++j) {
			v[palabra[j]-'a'] = true;
		}
		
	}
	cout << biggest << endl;
	escriu_fals(v);
}
