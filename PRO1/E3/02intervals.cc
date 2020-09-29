#include <iostream>
#include <vector>
using namespace std;

// PRE: n, seguit de n intervals (2*n reals). ai <= bi.
//		nombre m de casos de x, seguit de m reals x
// POST: Retorna yes si x esta al menys dins d'un interval, i no si no ho està en cap.

struct interval {
	double a, b;
};

typedef vector<interval> set_of_intervals;

// Llegeix n intervals de cin, donats com a0 b0 a1 b1...
set_of_intervals read_intervals(int n) {
	
	set_of_intervals I(n); // Construir vector I
	for (int i = 0; i < n; ++i) cin >> I[i].a >> I[i].b;
	
	return I;
}

bool inside_some_interval(double x, const vector<interval>& I) {

	int j = 0;
	
	while (j < I.size()) { // No cal bool found, perquè quan en trobi 1, farem un return true;
		if (x >= I[j].a and x <= I[j].b) return true;
		++j;
	}
	return false;
	
}

int main() {
	int n;
	cin >> n;
	set_of_intervals I = read_intervals(n);
	
	int m;
	cin >> m;
	for (int i = 0 ; i < m ; ++i) {
		double x;
		cin >> x;
		
		if (inside_some_interval(x, I)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}
