#include <iostream>
using namespace std;

//Matias Szarfer

// A vence a P
// P vence a V
// V vence a A

//1 si gana el primero, 2 si gana el segundo, - si empata

int main(){
	char c, d;
	cin >> c >> d;
	
	if 		(c == 'A' and d == 'P') cout << "1" << endl;
	else if (c == 'P' and d == 'V') cout << "1" << endl;
	else if (c == 'V' and d == 'A') cout << "1" << endl;
	
	if 		(c == 'P' and d == 'A') cout << "2" << endl;
	else if (c == 'V' and d == 'P') cout << "2" << endl;
	else if (c == 'A' and d == 'V') cout << "2" << endl;
	
	if 		(c == 'A' and d == 'A') cout << "-" << endl;
	else if (c == 'P' and d == 'P') cout << "-" << endl;
	else if (c == 'V' and d == 'V') cout << "-" << endl;
	
}
