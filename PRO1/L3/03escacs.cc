#include <iostream>
using namespace std;

int main(){
	int n;
	cin >> n; // Esta n indica el tamaño
	
	int sblanc = 0;
	int snegre = 0;
	
	for (int fila = 0; fila < n; ++fila) { // La variable fila representa las filas
		
		for (int columna = 0; columna < n; ++columna) { // Esta variable se refiere a las columnas (horizontales) del tablero
			char x; // Tratamos cada columna (horizontal) como carácter, para poder leer cáda dígito por separado
			cin >> x;
			
			//La condición para saber si la casilla es blanca o negra es que la suma de los dos sea impar (par+par=par; impar+impar=par; par+impar=impar)
			if ((columna + fila)%2 == 0) sblanc = sblanc + x-'0'; //Si está en una casilla blanca
			else snegre = snegre + x-'0'; //Si está en una casilla negra...
			//OJU: Hay que pasarlo a tipo int, porqué antes era un char
		}
	}
	cout << sblanc << "-" << snegre << " = " << sblanc - snegre << endl;
}
