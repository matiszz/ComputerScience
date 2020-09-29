#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct Punt {
	double x, y;
};
	
double distancia(const Punt& a, const Punt& b) {
	return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2));
}



int main() {
	Punt a;
	Punt b;
	
	cin >> a.x >> b.y >> a.x >> b.y;
	cout << distancia(a,b) << endl;
}
