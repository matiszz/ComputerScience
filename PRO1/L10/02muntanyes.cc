#include <iostream>
#include <vector>
using namespace std;

// PRE: n >= 3, que indica punts del vector. Seguit de n alçades
// POST: Indicar nombre total de cims, i l'alçada dels cims

vector<int> calcula_cims(const vector<int>& v) { // Retorna un vector amb l’alçada de tots els cims de v
	
	vector<int> cims(0);
	int n = v.size();
	
	for (int i = 0; i < n; ++i) {
		if (v[i] < v[i-1] and v[i-1] > v[i-2]) cims.push_back(v[i-1]);
	}
	
	return cims;
	
}

int main() {
	int n;
	cin >> n;
	
	vector<int> v(n);
	
	for (int i = 0; i < n; ++i) cin >> v[i]; // Construir vector
	
	vector<int> cims = calcula_cims(v);
	
	int s = cims.size();
	cout << s << ':'; // Num de cims
	for (int i = 0; i < s; ++i) cout << ' ' << cims[i]; // Cims totals
	
	cout << endl;
	
	int counter = 0;
	bool primer = true;
	
	for (int j = 0; j < s - 1; ++j) {
		//cout << endl << "Element: " << cims[j] << endl; 
		if (cims[j] > cims[s]) {
			if (primer) primer = false;
			else cout << ' ';
			
			cout << cims[j];
			++counter;
		}
	}
	if (counter == 0) cout << '-' << endl;
	cout << endl;
}
