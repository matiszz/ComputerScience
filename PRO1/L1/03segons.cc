#include <iostream>
using namespace std;

//Codi creat per Matias Szarfer
//Feu un programa que passi una quantitat donada d’anys, dies, hores, minuts i segons a segons.

int main() {
	int anys, dies, hores, min, seg;
	cin >> anys >> dies >> hores >> min >> seg;
	cout << anys*31536000 + dies*86400 + hores*3600 + min*60 + seg << endl;
}