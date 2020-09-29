#include <map>
#include <iostream>
#include <string>
using namespace std;

/* ENTRADA:
 * nom enters
 * nom leaves
 * nom wins int

 * SORTIDA:
 * <<nom leaves>> "nom has won int"
 * "---------", seguida de jugadors que no han sortit:
	* "nom is winning int"
 * nom enters i ja es a dins --> Error
 * nom leaves i no es a dins --> Error
 * nom wins i no es a dins --> Error

 */

int main() {
	map<string, int> casino;
	string nom;
	string accio;
	
	while (cin >> nom >> accio) {
		if (accio == "enters"){
			if (casino.find(nom) != casino.end()) cout << nom << " is already in the casino" << endl;
			else casino[nom] = 0;
		}
		else if (accio == "leaves"){
			if (casino.find(nom) == casino.end()) cout << nom << " is not in the casino" << endl;
			else {
				cout << nom << " has won " << casino[nom] << endl; 
				casino.erase(nom);
			}
		}
		else if (accio == "wins"){
			int money;
			cin >> money;
			if (casino.find(nom) == casino.end()) cout << nom << " is not in the casino" << endl;
			else casino[nom] += money;
		}
	}
	cout << "----------" << endl;
	for (map<string, int>::iterator it = casino.begin(); it != casino.end(); ++it) {
		cout << it->first << " is winning " << it->second << endl;
	}
}
