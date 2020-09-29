#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// PRE: Enter n, seguit de n enters.
// POST: Dir cuants numeros compleixen que x apareix a la sequencia, però -x no.

int main() {
	int n;
	cin >> n;
	
	vector <int> v(n); // Construcción del vector.
	for (int i = 0; i < n; ++i) cin >> v[i];
	
	int count = 0;
	
	int i = 0;
	int j = n - 1;
	
	sort(v.begin(), v.end());
	
	while (i <= j) {
		if (-v[i] == v[j]) {
			++i;
			--j; }
		else if (-v[i] < v[j]) {
			++count;
			--j;
		}
		else if (-v[i] > v[j]) {
			++count;
			++i;
		}
	}
	
	cout << count << endl;
	
}
