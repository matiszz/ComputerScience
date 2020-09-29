#include <iostream>
using namespace std;

// Matias Szarfer Barenblit
// Introdueix un caràcter i torna si es dígit, lletra o res.

int main() {
	
	char c;
	cin >> c;
	
	if ((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z')) cout << "lletra" << endl;
	//else if (c >= 'A' and c <= 'Z') cout << "lletra" << endl;
	else if (c <= '9' and c >= '0') cout << "digit" << endl;
	else cout << "res" << endl;

}