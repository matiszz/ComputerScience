#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Introdueix interval i números.
// Torna suma de números dins de l'interval i valors fora.

int main () {
	
	int l, r, x;
	cin >> l >> r;
	
	int sum = 0;
	int count = 0;
	
	while (cin >> x) {
		if (x >= l and x <= r) sum = sum + x;
		else ++count;
	}
	cout << "Sum Inside: " << sum << endl << "Num Outside: " << count << endl;
}