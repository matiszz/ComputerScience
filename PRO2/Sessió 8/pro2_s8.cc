/**
 * @mainpage Ejemplo de diseño modular:  Gestión de una lavadora.
 
En este ejemplo se construye un programa modular que ofrece un menú de opciones para gestionar una lavadora. Se introducen las clases <em>Lavadora</em>, <em>Cubeta</em> y <em>Prenda</em>.

Sólo se documentan elementos públicos. En una próxima sesión se verá un ejemplo
de proyecto completamente documentado, incluyendo los elementos privados.
*/

/** @file pro2_s8.cc
    @brief Programa principal para el ejercicio <em>Gestión de una lavadora</em>.
*/

// para que el diagrama modular quede bien se han escrito includes redundantes;
// en los ficheros .hh de la documentación de las clases ocurre lo mismo.
#include "Prenda.hh"
#include "Lavadora.hh"
#include "Cubeta.hh"
#ifndef NO_DIAGRAM // explicado en Prenda.hh
#include "readbool.hh"
#endif

/** @brief Programa principal para el ejercicio <em>Gestión de una lavadora</em>.
*/
int main () {
	
	Lavadora l;
	Cubeta c;
	Prenda p;
	
	int peso;
	bool col;
	int op;
	cin >> op;
	
	while (op != -8) {
		
		switch (op) {
			case -1: // Inicializar lavadora (datos: peso máximo y color)
				cin >> peso;
				col = readbool();
				if (not l.esta_inicializada()) l.inicializar(peso, col);
				break;
			case -2: // Añadir una prenda a la lavadora (datos: peso y color de la prenda)
				cin >> peso;
				col = readbool();
				p.modificar(peso, col);
				l.anadir_prenda(p);
				break;
				
			case -3: // Añadir una prenda a la cubeta (datos: peso y color de la prenda)
				cin >> peso;
				col = readbool();
				p.modificar(peso, col);
				c.anadir_prenda(p);
				break;
				
			case -4: // Completar la lavadora
				c.completar_lavadora(l);
				break;
				
			case -5: // Realizar un lavado
				l.lavado();
				break;
				
			case -6: // Escribir el contenido de la cubeta
				cout << "   Cubeta: " << endl;
				c.escribir();
				break;
				
			case -7: // Escribir el contenido de la lavadora
				cout << "   Lavadora: " << endl;
				l.escribir();
				break;
				
		}
		cin >> op;
	}
	
}
