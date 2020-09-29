#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Pre : Una matriu, amb fila = nº equip, columna = nº equip contrincant.
// Post: Matriu amb identificador, punts, gols a favor, gols en contra. Ordenat:
// CRITERI: + a - punts // + a - (gols favor - gols contra) // identificador.
// PUNTUACIÓ: Guanyador = 3 punts, perdedor = 0 // EMPAT = 1 punt cadascu

typedef pair<int,int> Pareja;
typedef vector< vector<int> > MatS;
typedef vector< vector<Pareja> > MatE;

void llegirMatriu(MatE& e) {
	int n;
	cin >> n;
	
	e =  MatE (n, vector<Pareja>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> e[i][j].first >> e[i][j].second;
		}
	}
}

void escriureMatriu(const MatS& s) {
	int n = s.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (j != 0) cout << " ";
			cout << s[i][j];
		}
		cout << endl;
	}
}

int calcularPunts(const MatE& e, int eq) {
	
	int punts = 0;
	
	for (int i = 0; i < 4; ++i) { //Filas, 1o casa, 2o visitor.
		if (i != eq) {
			if (e[eq][i].first > e[eq][i].second) punts += 3;
			else if (e[eq][i].first < e[eq][i].second) punts += 0;
			else punts += 1;
		}
	}
	
	for (int i = 0; i < 4; ++i) { //Columnas, 2o casa, 1o visitor.
		if (i != eq) {
			if (e[i][eq].first < e[i][eq].second) punts += 3;
			else if (e[i][eq].first > e[i][eq].second) punts += 0;
			else punts += 1;
		}
	}

	return punts;
}

int calcularFavor(const MatE& e, int eq) {
	
	int gols = 0;
	
	for (int i = 0; i < 4; ++i) { //Columnas, 2o casa, 1o visitor.
		if (i != eq) gols += e[i][eq].second;
	}
	for (int i = 0; i < 4; ++i) { //Filas, 1o casa, 2o visitor.
		if (i != eq) gols += e[eq][i].first;
	}

	return gols;
	
}

int calcularContra(const MatE& e, int eq) {
	
	int gols = 0;
	
	for (int i = 0; i < 4; ++i) { //Columnas, 2o casa, 1o visitor.
		if (i != eq) gols += e[eq][i].second;
	}
	for (int i = 0; i < 4; ++i) { //Filas, 1o casa, 2o visitor.
		if (i != eq) gols += e[i][eq].first;
	}

	return gols;
	
}

bool criteri(const vector<int>& a, const vector<int>& b) {
	if (a[1] == b[1]) {
		if (a[2]-a[3] == b[2]-b[3]) {
			return a[0] < b[0];
		}
		else return a[2]-a[3] > b[2]-b[3];
	}
	else return a[1] > b[1];
}

MatS calcularSortida(const MatE& e, int n) {
	
	MatS s(n, vector<int>(4));
	for (int i = 0; i < n; ++i) {
		s[i][0] = i + 1;
		s[i][1] = calcularPunts(e, i);
		s[i][2] = calcularFavor(e, i);
		s[i][3] = calcularContra(e, i);
	}
	
	return s;
}

int main() {
	MatE e;
	llegirMatriu(e);
	int n = e.size();
	MatS s;
	
	s = calcularSortida(e, n);
	sort(s.begin(), s.end(), criteri);
	escriureMatriu(s);
}
