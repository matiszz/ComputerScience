#include <iostream>
#include <vector>
using namespace std;

// PRE: Dos vector ordenats de forma estrictament creixent.
// POST: Retorna quants elements comuns hi ha.


 
int elements_comuns(const vector<int>& X, const vector<int>& Y){
	int count = 0;
	int lx = X.size();
	int ly = Y.size();
	int i = 0;
	int j = 0;
	
	while (i <= lx-1 && j <= ly-1) {
		if (X[i] == Y[j]) {
			++count;
			++i;
			++j;
		}
		else if (X[i] > Y[j]) ++j;
		else if (X[i] < Y[j]) ++i;
	}
	return count;
}
/*
int main() {
	int n, m;
	cin >> n >> m;
	vector<int> X(n);
	vector<int> Y(m);
	cout << elements_comuns(X,Y);
}*/
