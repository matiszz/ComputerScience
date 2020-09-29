#ifndef CONJ_EST_HH
#define CONJ_EST_HH

#include <vector>
#include <iostream>
#include "Estudiant.hh"

using namespace std;

class Cjt_estudiants {

private:

  // Representa un conjunt d'estudiants ordenat per DNI.  
  
  vector<Estudiant> vest; // vector amb els estudiants del conjunt 
  int nest; // nombre d'estudiants del conjunt
  static const int MAX_NEST = 60; // nombre maxim d'estudiants del conjunt
  int imax; // posició de l'estudiant amb nota màxima

  /*
     Invariant de la representació: 
     - vest[0..nest-1] està ordenat creixentment pel dni dels estudiants i no conté estudiants repetits
     - 0 <= nest <= vest.size() = MAX_NEST
     - imax és la posició de l'estudiant amb nota màxima a vest[0..nest-1];
       cas que hi hagi més d'un estudiant amb nota màxima, imax assenyala el de dni menor 
       si no hi ha cap estudiant amb nota imax val -1
  */

  void ordenar();
  /* Pre: cert */
  /* Post: el elements del paràmetre implícit passen a estar ordenats
     creixentment per DNI. */
     
  static int cerca_dicot(const vector<Estudiant> &vest, int left, int right, int x);
  /* Pre: els elements de vest estan ordenats creixentment per DNI,
     0<=left, right<vest.size(), right>=left+1 */
  /* Post: si x hi és vest[left..right], el resultat és la posició que
     hi ocupa, si no, és la posició que hauria d'ocupar */
 
  void recalcular_posicio_imax();
  /* Pre: el campo imax del parámetro implícito no necesariamente tiene
     el valor que le corresponde */
  /* Post: el camp imax conté la posició de l'element del paràmetre implícit
     amb la nota més gran; si no hi ha cap estudiant amb nota, val -1 */
  
public:

  //Constructores

  Cjt_estudiants();
  /* Pre: cert */
  /* Post: crea un conjunt d'estudiants buit */

  //Modificadores

  void afegir_estudiant(const Estudiant &est, bool& b);
  /* Pre: el paràmetre implícit no està ple */
  /* Post: b = indica si el p.i. original conté un estudiant amb el dni d'est;
     si b = fals, s'ha afegit l'estudiant est al paràmetre implícit */

  void modificar_estudiant(const Estudiant &est, bool& b);
  /* Pre: cert */
  /* Post: b indica si el paràmetre implícit original tenia un estudiant 
     amb el dni d'est; si b, aquest ha quedat sustituit per est */

  void eliminar_estudiants_sense_nota();
  /* Pre: cert */
  /* Post: el paràmetre implicit no conté cap estudiant sense nota */

  //Consultores
	
  int mida() const;
  /* Pre: cert */
  /* Post: El resultat és el nombre d'estudiants del paràmetre implícit */

  Estudiant estudiant_nota_max() const;
  /* Pre: el paràmetre implícit conté almenys un estudiant amb nota */
  /* Post: el resultat és l'estudiant del paràmetre implícit amb nota
     màxima; si en té més d'un, és el de DNI més petit */ 
 
  // Lectura i escriptura
	
  void llegir();
  /* Pre: cert */
  /* Post: el paràmetre implícit conté el conjunt d'estudiants llegits
     del canal estàndar d'entrada */

  void escriure() const;
  /* Pre: cert */
  /* Post: s'han escrit pel canal estàndar de sortida 
     els estudiants del conjunt que conté el paràmetre 
     implícit en ordre ascendent per DNI */

};

#endif

