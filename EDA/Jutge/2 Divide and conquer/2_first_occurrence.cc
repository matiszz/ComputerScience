#include <iostream>
#include <vector>
using namespace std;

// v ordenado crecientemente. Devuelve pos del primer x, sino -1
int first_occurrence(double x, const vector<double>& v) {
	int i = 0;
	int j = v.size()-1;
	while (i <= j) {
		int mid = (i+j)/2;
		if (x == v[mid] and (mid == 0 or v[mid-1] != x)) return mid;
		else if (x > v[mid]) i = mid+1;
		else j = mid-1;
	}
	return -1;
}
