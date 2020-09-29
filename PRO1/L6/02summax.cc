#include <iostream>
using namespace std;

// Matias Szarfer Barenblit

int main() {
	
	int n;
	
	while (cin >> n) { // Cantidad de valores que tendrá la seq.
		
		int total, max, min, x;
		total = max = min = 0;
		
		for(int i = 0; i < n; ++i) { // En cada iteración suma en max y en min 
			cin >> x;
			total = total + x;
			if (total >= max) max = total;
			else if (total <= min) min = total;
		}
		
		cout << max << ' ' << total - min << endl;
	}
}
