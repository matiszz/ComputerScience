#include <iostream>
#include <vector>
using namespace std;

void llegirVector(vector<int>& v){
	int numEst;
	cin >> numEst;
	v = vector<int> (numEst);
	for (int i = 0; i < numEst; ++i) cin >> v[i];
}

vector<int> maxMin(const vector<int>& v) {
	int mida = v.size();
	int min = v[0];
	int max = v[0];
	for (int i = 0; i < mida; ++i) {
		if (min > v[i]) min = v[i];
		if (max < v[i]) max = v[i];
	}
	
	vector <int> m(2);
	m[0] = min;
	m[1] = max;
	return m;
}

int main() {
	vector<int> v;
	llegirVector(v);
	
	vector<int> q(2);
	q = maxMin(v);
	cout << q[1] << ' ' << q[0] << endl;
}
