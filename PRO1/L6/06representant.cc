#include <iostream>
#include <string>
#include <cmath>
using namespace std;


double distancia(double x1, double y1, double x2, double y2) {
	int x = (x1 - x2) * (x1 - x2);
	int y = (y1 - y2) * (y1 - y2);
	return sqrt(x + y);
}

/*
double trajecte (int x_act, int y_act, int x_primer, int y_primer) {
	
	int x_ant = x_primer;
	int y_ant = y_primer;
	
	bool parar = false;
	double dist = 0;
	
	while (not parar) {
		dist = dist + distancia(x_ant, y_ant, x_act, y_act);
		
		// Todo este if es para tratar el último punto, ya que de forma normal, en el while no se sumaria.
		if (x_act == x_primer and y_act == y_primer) parar = true;
		else {
			x_ant = x_act;
			y_ant = y_act;
			cin >> x_act >> y_act;
		}
	}
}


int main() {
	
	cout.setf(ios::fixed);
	cout.precision(4);
	
	int x_act, y_act, x_primer, y_primer;
	string nom;
	
	while(cin >> nom >> x_primer >> y_primer >> x_act >> y_act) {
		cout << "Trajecte " << nom << ": " << trajecte(x_act, y_act, x_primer, y_primer) << endl;
	}
	
} */

int main() {
	
	cout.setf(ios::fixed);
	cout.precision(4);

	int x_act, y_act, x_primer, y_primer;
	
	cin >> x_primer >> y_primer >> x_act >> y_act;
	int x_ant = x_primer;
	int y_ant = y_primer;
	
	bool parar = false;
	double dist = 0;
	
	while (not parar) {
		dist = dist + distancia(x_ant, y_ant, x_act, y_act);
		
		// Todo este if es para tratar el último punto, ya que de forma normal, en el while no se sumaria.
		if (x_act == x_primer and y_act == y_primer) parar = true;
		else {
			x_ant = x_act;
			y_ant = y_act;
			cin >> x_act >> y_act;
		}
	}
	
	cout << dist << endl;
	
}
