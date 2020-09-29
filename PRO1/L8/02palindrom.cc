#include <iostream>
#include <vector>
using namespace std;

bool es_palindrom(const string& s) {
	
	int i = 0;
	int k = s.size() - 1;
	
	while (i < k) {
		if (s[i] != s[k]) return false;
		++i;
		--k;
	}
	return true;
}

int main() {
	
	string s;
	cin >> s;
	cout << es_palindrom(s) << endl;
	
}
