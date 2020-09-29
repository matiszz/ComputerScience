#include <iostream>
#include <string>
using namespace std;

// Matias Szarfer Barenblit

int main() {
	
	string a, b;
	
	while (cin >> a >> b) {
		if (a <= b) cout << a << " "  << b << endl;
		else if (a > b) cout << b << " "  << a << endl;
	}
}