#include <iostream>
#include <math.h>
using namespace std;

//Matias Szarfer Barenblit

//Entrada: L’entrada és una seqüència de parells d’enters a i b.
//Sortida: Escriure la suma dels cubs entre a i b.
//Per exemple, per "3 6", el cout es "3^3+4^3+5^3+6^3"

int main() {
	int x, y;
	//cin >> x >> y;
	
	while (cin >> x >> y){
		cout << "suma dels cubs entre " << x << " i " << y << ": ";
		int res = 0;
		
		for (int i = x; i <= y; ++i) res = res + pow(i, 3);
		
		cout << res << endl;
	}
}