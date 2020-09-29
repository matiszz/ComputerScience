#include <iostream>
using namespace std;

//Matias Szarfer Barenblit

//Entrada: Interès i (un nombre real estrictament positiu), seguit de la paraula “setmanal”, “mensual”, “trimestral”, o “semestral”.
//Sortida: Escriviu el TAE amb 4 decimals. Fixeu-vos que no us cal c per calcular-lo.

int main() {
        cout.setf(ios::fixed);
        cout.precision (4);
		
        double interes, b, temps;
        string freq;
        cin >> interes >> freq;
		
        if 		 (freq == "setmanal") temps = 52;
        else if (freq == "mensual") temps = 12;
        else if (freq == "trimestral") temps = 4;
        else if (freq == "semestral") temps = 2;
		
        interes = (interes/100)/temps;
        b = interes + 1;
        while (temps != 1) {
                b = b*(interes + 1);
                temps = temps - 1;
        }
        cout << 100*(b-1) << endl;
}