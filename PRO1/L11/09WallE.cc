#include <iostream>
#include <vector>
#include <string>
using namespace std;


// PRE: f, c (files i columnes)
//		f files amb c caracters. X = mur, . = buida, dig = deixalles.
//		f files amb c digits.    dig = quantitat energia
//		pos inicial (fila, columna) nivell energia.
//		Paraula amb N, S, E, o O (Nord, Sud, Est o Oest).

// POST: Escriure nº deixalles recollides abans d'acabar ordres o abans de E=0.
//		 Nivell d'energia i pos final.


struct Info {
	char contingut; // Mur (’X’), buit (’.’) o deixalles (dígit)
	int energia; // Aportacio d’energia solar de la casella
};
	
typedef vector< vector<Info> > Camp;
typedef vector<int> Final;


Final executa(int f, int c, Camp& C, int inx, int iny, int ine, string o) {
	
	Final I(4);
	int l = o.length();
	int es = 0; /// Escombreries
	int en = ine; /// Eneregia
	
	int i = 0;
	while (i < l or ine == 0) {
		
		if (o[i] == 'N') {
			int a = inx;
			bool stop = false;
			while (a < 1 and not stop) {
				/// Si troba brossa
				if (C[inx][a].contingut <= 0 and C[inx][a].contingut >= 9) {
					 es += C[inx][a].contingut; // Guarda brossa
					 C[inx][a].contingut = 0; // Posa brossa a 0
					 --en; // Perd energia
				}
				/// Si troba un mur
				else if (C[inx][a].contingut == 'X') stop = true;
				
				en += C[inx][a].energia;
				--a;
			}
			a = inx;
		}
		
		
		else if (o[i] == 'S') {
			int a = inx;
			bool stop = false;
			while (a < c-1 and not stop) {
				/// Si troba brossa
				if (C[inx][a].contingut <= 0 and C[inx][a].contingut >= 9) {
					 es += C[inx][a].contingut; // Guarda brossa
					 C[inx][a].contingut = 0; // Posa brossa a 0
					 --en; // Perd energia
				}
				/// Si troba un mur
				else if (C[inx][a].contingut == 'X') stop = true;
				
				en += C[inx][a].energia;
				++a;
			}
			a = inx;
		}
		
		
		else if (o[i] == 'E') {
			int b = iny;
			bool stop = false;
			while (b < f-1 and not stop) {
				/// Si troba brossa
				if (C[b][iny].contingut <= 0 and C[b][iny].contingut >= 9) {
					 es += C[b][iny].contingut; // Guarda brossa
					 C[b][iny].contingut = 0; // Posa brossa a 0
					 --en; // Perd energia
				}
				/// Si troba un mur
				else if (C[b][iny].contingut == 'X') stop = true;
				
				en += C[b][iny].energia;
				++b;
			}
			b = iny;
		}
		
		
		else if (o[i] == 'O') {
			int b = iny;
			bool stop = false;
			while (b < 1 and not stop) {
				/// Si troba brossa
				if (C[b][iny].contingut <= 0 and C[b][iny].contingut >= 9) {
					 es += C[b][iny].contingut; // Guarda brossa
					 C[b][iny].contingut = 0; // Posa brossa a 0
					 --en; // Perd energia
				}
				/// Si troba un mur
				else if (C[b][iny].contingut == 'X') stop = true;
				
				en += C[b][iny].energia;
				--b;
			}
			b = iny;
		}
		
		++i;
	}
	
	I[0] = es;
	I[1] = en;
	I[2] = iny;
	I[3] = inx;
	
	return I;
	
}


void llegirc(Camp& M) { /// Llegeix contingut
	int f = M.size();
	int c = M[0].size();
	
	for (int i = 0; i < f; ++i) for (int j = 0; j < c; ++j) {
		cin >> M[i][j].contingut;
	}	 
}

void llegire(Camp& M) { /// Llegeix energia
	int f = M.size();
	int c = M[0].size();
	
	for (int i = 0; i < f; ++i) for (int j = 0; j < c; ++j) {
		cin >> M[i][j].energia;
	}
}

int main() {
	
	/// Lectura ///
	int f, c;
	cin >> f >> c;
	Camp C(f, vector<Info>(c));
	llegirc(C);
	llegire(C);
	
	int inx, iny, ine;
	string ordre;
	cin >> inx >> iny >> ine >> ordre;
	/// Fi lectura ///
	
	Final Ifi(4); /// Info Final: contindra [escombreries, energia, posy, posx);
	Ifi = executa(f, c, C, inx, iny, ine, ordre);
	
	cout << "escombraries: " << Ifi[0];
	cout << "energia: " << Ifi[1];
	cout << "posicio: (" << Ifi[2] << ',' << Ifi[3] << ')' << endl; 
}
