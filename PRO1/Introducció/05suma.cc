#include <iostream>
using namespace std;

//Codi creat per Matias Szarfer

//Escribe un programa que lea tres números y escrba la suma de su mínimo y su máximo.

int main() {
	int a, b, c, max, min;
	cin >> a >> b >> c;
	if (a<=b and a<=c) min = a;
	else if (b<=c) min = b;
	else min = c;

	if (a>=b and a>=c) max = a;
	else if (b>=c) max = b;
	else max = c;

	cout << min+max << endl;
}