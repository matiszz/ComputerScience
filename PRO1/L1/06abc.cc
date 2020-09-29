#include <iostream>
using namespace std;

//Matias Szarfer

int main(){
	int x, y, z, a, b, c;
	string letras;
	cin >> x >> y >> z;
	cin >> letras;
	
	if (x < y and y < z){
		a = x;
		b = y;
		c = z;
	}
	else if (x < z and z < y){
		a = x;
		b = z;
		c = y;
	}
	else if (y < x and x < z){
		a = y;
		b = x;
		c = z;
	}
	else if (y < z and z < x){
		a = y;
		b = z;
		c = x;
	}
	else if (z < x and x < y){
		a = z;
		b = x;
		c = y;
	}
	else if (z < y and y < x){
		a = z;
		b = y;
		c = x;
	}
	
	if (letras == "ABC") cout << a << " " << b << " " << c << endl;
	if (letras == "ACB") cout << a << " " << c << " " << b << endl;
	if (letras == "BAC") cout << b << " " << a << " " << c << endl;
	if (letras == "BCA") cout << b << " " << c << " " << a << endl;
	if (letras == "CAB") cout << c << " " << a << " " << b << endl;
	if (letras == "CBA") cout << c << " " << b << " " << a << endl;
}
