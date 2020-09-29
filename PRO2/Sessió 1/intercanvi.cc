#include <iostream>
#include "vectorIOint.hh"
using namespace std;

// Pre: un vector i dos posicions.
// Post: escirure el vector amb les dos posicions intercanviades.

vector<int> canvia(vector<int> &v, int a, int b) {
	int aux;
	aux = v[a];
	v[a] = v[b];
	v[b] = aux;
	return v;
}

int main() {
	
	vector<int> v;
	leerVector_int(v);
	
	cout << "Quines dues posicions intercanvio?" << endl;
	int a,b;
	cin >> a >> b;
	
	vector<int> f = canvia(v, a, b);
	cout << "Aqui tens el nou vector:" << endl;
	escribirVector_int(f);
	
}
