#include <iostream>
#include <vector>
#include <string>
using namespace std;

// PRE: Entrada de n, p, k, on n=#paraules, p=posició, k=paraules i un char e o d
//      seguit de una frase.
// POST: Escriure les k paraules a la dreta (d) o esquerra (e) de p. La frase és circular.

int main() {
	int n, p, k;
	char c;
	cin >> n >> p >> k >> c;
	vector<string> V(n); // Vector de medida n
	
	string pal;
	for (int i = 0; i < n; ++i) {
		cin >> pal;
		V[i] = pal;
	}
	
	int inc; // Incremento
	if (c == 'e') inc = -1;
	else inc = 1;
	
	while (k > 0) {
		p = (p + inc + n)%n; // Todo esto es para que sea circular
		if (k == 1) cout << V[p];
		else cout << V[p] << " ";
		--k;
	}
	cout << endl;
}
