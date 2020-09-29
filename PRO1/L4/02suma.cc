#include <iostream>
using namespace std;

// Torna la suma dels valors mínim i màxim del seus paràmetres

int max(int a, int b) {
	if (a >= b) return a;
	else return b;
}

int min(int a, int b) {
	if (a <= b) return a;
	else return b;
}

int sum_min_max(int x, int y, int z) {
	int a = max(max(x, y), z);
	int b = min(min(x, y), z);
	
	return a+b;
}
