#include <iostream>
using namespace std;

int main() {
	int a1, b1, a2, b2;
	cin >> a1 >> b1 >> a2 >> b2;
		
	if (a1 == a2 and b1 == b2) cout << "= , [" << a1 << "," << b1 << "]" << endl; //Son iguales
		
	else if (a1 >= a2 and b1 <= b2) cout << "1 , [" << a1 << "," << b1 << "]" << endl; //1 dentro de 2
	
	/*Es importante ver que la priemra fue falsa, porque esta opción tambien
	recoge la opcion que los dos sean iguales */
		
	else if (a1 <= a2 and b1 >= b2) cout << "2 , [" << a2 << "," << b2 << "]" << endl; //2 dentro de 1
		
	else if (b1 < a2 or b2 < a1) cout << "? , []" << endl; //Sin intersección
	
	/*Estrictamente menor. Sólo hay que ver que b1 es menor que a2 o que
	 b2 es menor que a1 para ver que no hay intersección */
		
	else { //Con intersección
		cout << "? , [";
		if (a1 >= a2) cout << a1 << ",";
		else cout << a2 << ",";
		
		if (b1 <= b2) cout << b1 << "]" << endl;
		else cout << b2 << "]" << endl;
	}	

}
