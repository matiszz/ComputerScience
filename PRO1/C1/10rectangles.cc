#include <iostream>
using namespace std;

//Matias Szarfer Barenblit

int main() {
	int k, h, l;
	cin >> k >> h >> l;
	
	for (int i = k; i > 0; --i) {
		int x = 9;
		for (int g = 0; g < h; ++g) {
			for (int j = 0; j < l; ++j) {
				cout << x;
				--x;
				if (x == -1) x = 9;
			}
		cout << endl;
		}
		cout << endl;
	}
}