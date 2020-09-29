#include <iostream>
#include <string>
using namespace std;

//Matias Szarfer Barenblit

//Donada una frase, compta quantes "hola" hi ha.

int main() {
	string a;
	
	int holas = 0;
	
	while (cin >> a){
		if (a == "hola") holas = holas + 1; 
	}
	cout << holas << endl;
}