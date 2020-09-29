#include <iostream>
using namespace std;

//Codi creat per Matias Szarfer

//Escribe un programa que lea tres nĂşmeros y escriba su mĂ­nimo.

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	if (a<=b and a<=c) cout << a << endl;
	else if (b<=c) cout << b << endl;
	else cout << c << endl;
}