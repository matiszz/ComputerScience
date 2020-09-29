#include <iostream>
using namespace std;

// Matias Szarfer Barenblit


int suma_digits(int x) {
	
	if (x < 10) return x;
	else return suma_digits(x/10) + x%10;
	
}

bool primer(int n) {
	
	if (n <= 1) return false;
	int sum = 0;
	for (int i = 2; i*i <= n; ++i) {
		if (n%i == 0) ++sum;
	}
	return (sum == 0); 

}

bool es_primer_perfecte(int n) {
	
	if (primer(n) == 0) return false;
	if (n < 10) return primer(n);
	else return es_primer_perfecte(suma_digits(n));
	
}

int main() {
	int n;
	cin >> n;
	cout << es_primer_perfecte(n) << endl;
}
