#include <iostream>
using namespace std;

// Retorna cert si i només si el natural n és una potència de 3.

bool es_potencia_de_3(int n) {
	if (n == 0) return false;
	
	while (n%3 == 0) n = n/3;
	
	if (n == 1) return true;
	else return false;
		
}

int main() {
	int a;
	cin >> a;
	cout << es_potencia_de_3(a) << endl;
}
