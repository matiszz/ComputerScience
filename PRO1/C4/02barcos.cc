#include <iostream>
#include <vector>
using namespace std;

// PRE: f, c: 3 <= f <= 26//c >= 3
//		f linies amb c caracters: V = vaixell. Només oritzontals
//      i no es toquen entre ells, ni toquen els marges.
//		Sequencia de trets, [fc]; Left Up = a0;

// POST: Escriure "aigua", "tocat", o "enfonsat" per cada tret.
//       endl, i estat final. V = Vaixell; T = tocat (i no enfonsat).

typedef vector<char> FIL;
typedef vector<FIL> Camp;


void llegir(Camp& C, int f, int c) {
	for (int i = 0; i < f; ++i) for (int j = 0; j < c; ++j) cin >> C[i][j];
}

string tir(Camp& C, int f, int c, int fil, int col) {
	
	if (C[fil][col] == '.') return "aigua";
	else if (C[fil][col] == 'T') return "tocat";
	
	else if (C[fil][col] == 'V') {
		C[fil][col] = 'T';
		
		bool aL, aR;
		aL = aR = false;
		
		while (not aL) {
			--col;
			if (C[fil][col] == 'V') return "tocat";
			if (C[fil][col] == '.') aL = true;
		}
		while (not aR) {
			++col;
			if (C[fil][col] == 'V') return "tocat";
			if (C[fil][col] == '.') aL = true;
		}
		
		return "enfonsat";
		
		aL = aR = false;
		while (not aL) {
			--col;
			C[fil][col] = '.';
		}
		while (not aR) {
			++col;
			C[fil][col] = '.';
		}
	}
		
}

int main() {
	
	/// Lectura camp:
	int f, c;
	cin >> f >> c;
	Camp C(f, FIL(c));
	llegir(C, f, c);
	
	char t;
	int col;
	
	while (cin >> t >> col) {
		
		int fil = t - 'a'; /// Converteix el char a int
		cout << t << col << ": ";
		cout << tir(C, f, c, fil, col+1) << endl;
		
	}
	
	/// Imprimir matriu final
	for (int i = 0; i < f; ++i) {
		cout << endl;
		for (int j = 0; j < c; ++j) cout << C[i][j];
	}
	
}
