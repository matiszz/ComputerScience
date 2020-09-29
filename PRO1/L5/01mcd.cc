#include <iostream>
using namespace std;

// Matias Szarfer Barenlbit

int mcd(int a, int b) {
	if (b != 0) return mcd(b, a%b);
	else return a;
}

int main() {
	int x, y;
	cin >> x >> y;
	cout << mcd(x, y);
}
	
