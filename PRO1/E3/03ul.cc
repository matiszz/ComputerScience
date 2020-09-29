#include <iostream>
#include <string>
using namespace std;

// PRE: String T de 26 caracters U o L. Seguit de sequència de caràcters.
// POST: Sequència de caracters amb les lletres U o L segons s'hagi definit.

bool es_mayuscula(char c) {
	if (c <= 'A' and c >= 'Z') return true;
	else return false;
}

char transforma(char c, char m) {
	
	if (es_mayuscula(c)) {
		if 		(m == 'U') return c;
		else if (m == 'L') {
			int dist = c - 'A';
			return ('a' + dist);
		}
	} else {
		if 		(m == 'L') return c;
		else if (m == 'U') {
			int dist = c - 'a';
			return ('U' + dist);
		}
	}
}

// Lee el input y escribe cada letra transformándola en mayúsucla o minúscula.
void make_uppercase_lowercase(const string& T) {
	
	string I;
	cin >> I;
	
	for (int j = 0; j < I.length(); ++j) {
		int dist = 0;
		if (es_mayuscula(I[j])) dist = I[j] - 'A';
		else if (not es_mayuscula(I[j])) dist = I[j] - 'a';
		
		cout << transforma(I[j], T[dist]);
	}
	
	cout << endl;
	
}

int main() {
    string T; 
    cin >> T;
    
    make_uppercase_lowercase(T);
}
