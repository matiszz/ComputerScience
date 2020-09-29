#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Provincia {
	string nom;
	string capital;
	int habitants;
	int area;
	double pib;
};

struct Pais {
	string nom;
	string capital;
	vector<Provincia> provs;
};


typedef vector<Pais> Paisos;


double pib(const Paisos& p, char c, double d) { // Retorna la suma dels PIBs de províncies amb densitat > d, i només dels països començats amb 'c'
	double a = 0;
	for (int i = 0; i < p.size(); ++i) {
		if (p[i].nom[0] == c) {
			for (int j = 0; j < p[i].provs.size(); ++j) {
				if (p[i].provs[j].habitants / double(p[i].provs[j].area) > d) {
					a += p[i].provs[j].pib;
				}
			}
		}
	}
	return a;
}

/*
void llegeix_paisos(Paisos& pais) {
	
	for (int i = 0; i < pais.size(); ++i) {
		cin << pais[i].nom;
		cin << pais[i].capital;
		
		int num_pr;
		cin >> num_pr;
		vector<Provincia> prov(num_pr);
		
		for (int j = 0; k < nprov; ++j= {
			cin >> provis[j].nom;
			cin >> provis[j].capital;
			cin >> provis[j].habitants;
			cin >> provis[j].area;
			cin >> provis[j].pib;
		}
		pais[i].provs = provis;
	}
}

int main() {
	int n;
	cin >> n;
	
	Paisos pais(n);
	
	for (int i = 0; i < n; ++i) llegeix_paisos(pais);
	
	cout << endl << "Densitat mínima: ";
	double d;
	cin >> d;
	cout << endl << "Primera lletra del païs: ";
	char c;
	cin >> c;
	
	cout << endl << pib(pa, c, d) << endl;
	
} */
