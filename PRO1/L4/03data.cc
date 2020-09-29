#include <iostream>
using namespace std;

// Diu si una data és valida o no.

bool traspas(int any) {
	if (any%4 == 0 and any%100 != 0) return true;
	else if (any%100 == 0 and (any/100)%4==0) return true;
	else return false;
}

bool es_data_valida(int d, int m, int a) {
	int cor = 0;
	int t = 0;
	if (d < 1 or m <1 or m > 12) ++cor; //Dia negatiu i mesos correcte
	if (m == 2) { //Dies de febrer
		if (a%4 == 0 and a%100 != 0) t = 1;
		else if (a%100 == 0 and (a/100)%4==0) t = 1;
		else t = 0;
		
		if (t == 1 and d > 29) ++cor;
		else if (t == 0 and d > 28) ++cor;
	}
	if (m == 1 or m == 3 or m == 5 or m == 7 or m == 8 or m == 10 or m == 12) { //Des 31
		if (d > 31) ++cor;
	} else if (m == 4 or m == 6 or m == 9 or m == 11) { //Dies 30
		if (d > 30) ++cor;
	}
	return (cor == 0);
}

int main() {
	int di, an, me;
	cin >> di >> an >> me;
	cout << es_data_valida(di, an, me) << endl;
}
