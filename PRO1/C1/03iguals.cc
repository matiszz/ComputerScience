#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Introdueix una seqüència de naturals n >= 100.
// Torna quins acaben amb les mateixes últimes 3 xifres que el primer.

int main() {
	
	int n, o;
	cin >> n;
	cout << "nombres que acaben igual que " << n << ":" << endl;
	
	int a, b, c;
	a = n%10;
	n = n/10;
	b = n%10;
	n = n/10;
	c = n%10;
	n = n/10;
	
	int d, e, f;
	int count = 0;
	while (cin >> o) {
		int x = o;
		d = x%10;
		x = x/10;
		e = x%10;
		x = x/10;
		f = x%10;
		x = x/10;
		if (d == a and e == b and f == c){
			cout << o << endl;
			++count;
		}
	}
	cout << "total: " << count << endl;
}