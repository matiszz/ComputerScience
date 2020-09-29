#include <iostream>
using namespace std;

//Matias Szarfer Barenblit

//Ens donen una seqüència de n (nord), s (sud), e (est), o (oest)
//He de donar la posició, sent (e-o, s-n)

int main() {
	char c;
	int a, b;
	
	while (cin >> c) {
		if (c == 'e') ++a;
		else if (c == 'o') --a;
		else if (c == 's') ++b;
		else if (c == 'n') --b;
	}
	cout << "(" << a << ", " << b << ")" << endl;
}