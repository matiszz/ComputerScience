#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool criteri(int a, int b) {
	return a >= b;
}

int main() {
	int a;
	while (cin >> a) {
		
		vector<int> v(a);
		for (int i = 0; i < a; ++i) cin >> v[i];
		
		sort(v.begin(), v.end(), criteri);
		
		bool primer = true;
		for (int i = 0; i < a; ++i) {
			if (primer) {
				cout << v[i];
				primer = false;
			} else cout << ' ' << v[i];
		}
		
		cout << endl;
	}
}
