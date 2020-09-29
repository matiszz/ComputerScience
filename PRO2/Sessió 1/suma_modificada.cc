#include <iostream>
using namespace std;

int  main () {
  cout << "Entra nombres: " << endl;
  int sum = 0;
  int x = 1;
  while (x != 0) {
	  cin >> x;
	  sum += x;
  }
  cout << "La suma dels nombres es " << sum << endl;
}

