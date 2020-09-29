#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<bool> vec;

vec garbell() {
	const int N = 1000000;
	vec v(N + 1, true);
	v[0] = false;
	v[1] = false;
	for (int i = 2; i <= sqrt(N); ++i) {
		if (v[i]) {
			for (int j = i*i; j <= N; j = j+i) v[j] = false;
		}
	}
	return v;
}

int main() {
	vec gar = garbell();
	
	int x;
	while (cin >> x) {
		if (gar[x]) cout << x << " es primer" << endl;
		else cout << x << " no es primer" << endl;
	}
}
