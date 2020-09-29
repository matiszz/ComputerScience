#include <iostream>
using namespace std;

// Matias Szarfer Barenlbit

int digit_maxim_i_minim(int n, int& maxim, int& minim) {
	
	if (n < 10) return n;
	else if (digit_maxim_i_minim(n/10) > maxim) maxim = n/10;
	else if (digit_maxim_i_minim(n/10) < minim) minim = n/10;
}

int main() {
	
	int x, maxim, minim;
	cin >> x;
	
	digit_maxim_i_minim(x, maxim, minim);
	
	cout << "Max: " << maxim << " Mínim: " << minim << endl;
	
}

/*
if (n%10 != 0) {
		if (n%10 > maxim) maxim = n%10;
		if (n%10 < minim) minim = n%10;
		
		digit_maxim_i_minim(n/10, maxim, minim);
	}
	
	cout << maxim << " " << minim;
*/
