#include <iostream>
#include <vector>
using namespace std;

// PRE: A dd/mm/aaaa   per Afegir data al vector.
//		E 			   per Esborrar la última data.
//		C data1 data2  per consultar distància entre dos dates dins del vector.
// Vector ordenat!

// POST: Retornar distàncies per a cada Consulta

struct Data { int dia, mes, any; };

typedef vector<Data> Dates;

Data data_llegida() { // Funció que llegeix una Data
	Data d;
	char b;
	cin >> d.dia >> b >> d.mes >> b >> d.any;
	return d;
}

int main() {
	char c;
	Dates dates(0); // Crear vector de Dates amb 0 elements
	
	while (cin >> c) {
		
		if (c == 'A') { // Cas A: Afegir una Data al final.
			Data da = data_llegida(); // Llegeix
			dates.push_back(da); // Efegeix
		}
		
		if (c == 'E') dates.pop_back(); // Cas E: Esborrar la última Data.
		
		if (c == 'C') { // Cas C: Comptar distància entre dos dates;
			int ini, fin;  //  Variables per saber en quin punt del
			ini = fin = 0; // vector es troben la Data "a" i la "b"
			int j = 0;
			
			Data dca = data_llegida(); // Data "a"
			Data dcb = data_llegida(); // Data "b"
			
			bool trobat = false;
			
			while (not trobat and j < dates.size()) {
				
				if (ini == 0     // Per trobar la Data "a"
					and dates[j].dia == dca.dia
					and dates[j].mes == dca.mes
					and dates[j].any == dca.any) ini = j;
				else if (ini != 0 // Per trobar la Data "b"
					and dates[j].dia == dcb.dia
					and dates[j].mes == dcb.mes
					and dates[j].any == dcb.any) {
					fin = j;
					trobat = true; }
					
				++j;
			}
			cout << fin - ini << endl;
		}
	}
}
