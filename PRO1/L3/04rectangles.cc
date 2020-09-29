#include <iostream>
using namespace std;

//Matias Szarfer Barenblit

int main() {
	int h, l;
	
	while (cin >> h >> l) {
		int x = 9;
		for (int fila = h; fila != 0; --fila) {
			for (int columna = l; columna != 0; --columna) {
				cout << x;
				--x;
				if (x == -1) x = 9;
			}
			cout << endl;
		}
		cout << endl;
	}
}