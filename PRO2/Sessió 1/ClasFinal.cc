#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
struct Partit {
        int x, y;
};
 
typedef vector<Partit> Row;
typedef vector<Row> MatE;
 
typedef vector<int> Fila;
typedef vector<Fila> MatS;
 
void llegirMatriu(MatE& e) {
	int n = e.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> e[i][j].x >> e[i][j].y;
		}
	}
}
 
void classificar(MatS& s, const MatE& e) {
	int n = s.size();
	//Número equip
	for (int i = 0; i < n; ++i) s[i][0] = i+1;
	//Puntuacio
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j) {
				//Punts
				if (e[i][j].x == e[i][j].y) {
					++s[i][1];
					++s[j][1];
				}
				else if (e[i][j].x > e[i][j].y) s[i][1] += 3;
				else s[j][1] += 3;
				//Gols
				
				//Favor
				s[i][2] += e[i][j].x;
				s[j][2] += e[i][j].y;
				//Contra
				s[i][3] += e[i][j].y;
				s[j][3] += e[i][j].x;
			}
		}
	}
}
 
bool criteri(const vector<int>& a, const vector<int>& b) {
	if (a[1] == b[1]) {
		if (a[2]-a[3] == b[2]-b[3]) {
			return a[0] < b[0];
		} else return a[2]-a[3] > b[2]-b[3];
	} else return a[1] > b[1];
}
 
void escriureMatriu(const MatS& s) {
	int n = s.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (j != 0) cout << " ";
			cout << s[i][j];
		} cout << endl;
	}
}
 
 
int main() {
	int n;
	cin >> n;
	MatE e(n, Row(n));
	llegirMatriu(e);
	MatS s(n, Fila(4, 0));
	classificar(s, e);
	sort(s.begin(), s.end(), criteri);
	escriureMatriu(s);
}
