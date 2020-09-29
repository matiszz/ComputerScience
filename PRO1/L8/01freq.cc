#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> V(1001, 0); // V(x, y) = vector de x elementos inicializados a y
	
	int n, a;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a;
		a -= 1000000000;
		++V[a];
	}
	
	for (int i = 0; i < 1001; ++i) {
		if (V[i] != 0) cout << 1000000000 + i << " : " << V[i] << endl;
	}
}
