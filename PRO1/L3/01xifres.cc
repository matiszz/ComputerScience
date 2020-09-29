#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Donat "b(base) n(num)", tornar les xifres amb les que es representa

int main() {
	int b, n, c;
	
	while (cin >> b >> n) {
		c = 0;
		while (n != 0) {
			n = n/b;
			++c;
		}
	cout << c << endl;
	}
}
