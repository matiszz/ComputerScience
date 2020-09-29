#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Donat un nombre, iguala totes les seves xifres a la
// més gran, fins que hi ha una més gran

int engreixa(int x) {
	
	if (x < 10) return x;
	int engr = engreixa(x/10);
	int m = max(x%10,engr%10);
	return 10*engr+m;
	
}

int main() {
	
	int x;
	cin >> x;
	cout << engreixa(x) << endl;

}