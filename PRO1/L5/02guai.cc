#include <iostream>
using namespace std;

// Matias Szarfer Barenlbit
// Pre: n >= 0, b >=2
// Post: Es guai si tots els digits de n en base b són parells.

bool es_guai(int n, int b) {
	
	if (n < b) {
		if (n%2 == 0) return 1;
		else return 0;	
	} else {
		int r = n%b;
		if (r%2 != 0) return 0;
		else return es_guai (n/b, b);
	}
}

int main() {
	
	int x, y;
	cin >> x >> y;
	cout << es_guai(x, y) << endl;
	
}
