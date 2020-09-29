#ifndef LISTAPALABRAS_HH
#define LISTAPALABRAS_HH

#include "Palabra.hh"

class ListaPalabras
{
private:

  struct palfrec {
    Palabra par;
    int freq;
  };

  static const int MAXNUMPAL = 20; // longitud m�xima permitida
  int nparaules; // n�mero de palabras de la lista, 
                 // la lista est� formada por las posiciones de 0 a nparaules-1

  vector<palfrec> paraules; // vector de palabras y frecuencias
  
  vector<int> npar_long; // n�mero de palabras distintas de cada longitud 
  vector<int> suma_frec_long; // suma de frecuencias de las palabras
                              // de cada longitud  
  
  /* 
     Invariante de la representaci�n: 
     - los campos par de paraules[0..nparaules-1] no pueden tener palabras repetidas en posiciones distintas ni palabras vac�as
     - los campos freq de paraules[0..nparaules-1] han de ser mayor que 0
     - 0 <= nparaules <= Palabra::longitud_maxima() = MAXNUMPAL    
     - npar_long[l - 1] = n�mero de palabras distintas de longitud l en paraules[0..nparaules-1] para 1 <= l <= Palabra::longitud_maxima()
     - sum_freq_long[l-1] = suma de las frecuencias de las palabras de longitud l en paraules[0..nparaules-1] para 1 <= l <= Palabra::longitud_maxima()  
  */
   
  static bool comp(const palfrec& p1, const palfrec& p2);
  /* Pre: cierto */
  /* Post: el resultado indica si la palabra de p1 es menor que la de p2
     (saldr�a antes en un diccionario) */

  void buscar_palabra_posicion(const Palabra & p, bool & b, int & i) const;
  /* Pre: cierto */
  /* Post: b indica si p est� en el par�metro impl�cito;
     si b entonces i es la posici�n en la que est� p; si no, i es la 
     longitud del par�metro impl�cito */ 
  
public:

  /* Constructoras */

  ListaPalabras ();
  /* Pre: cierto */
  /* Post: el resultado es una lista vac�a, que puede contener palabras y sus
     respectivas frecuencias */
  
  /* Modificadoras */

  void anadir_palabra(const Palabra & p);
  /* Pre: el n�mero de palabras en el par�metro impl�cito es menor que la 
     longitud m�xima o p ya est� en �l; p no es la palabra vac�a */
  /* Post: si p estaba en el par�metro impl�cito original, su frecuencia se ha
     incrementado en 1; si no, p pasa a estar en �l, con frecuencia 1 */

  void borrar_palabra(const Palabra & p);
  /* Pre: si p pertence al p.i., tiene frecuencia f */
  /* Post:
     si p no pertence al p.i, no cambia nada; 
     si f = 1, p ya no pertenece al p.i.; 
     si f > 1, la frecuencia de p se ha decrementado en 1 
  */ 
  
  /* Consultoras */

  double frec_media_long(int l) const;
  /* Pre: 0 < l <= Palabra::longitud_maxima() */
  /* Post: el resultado es la frecuencia media de las palabras de
     longitud l en el par�metro impl�cito (cero si no hay ninguna) */

  static int longitud_maxima();
  /* Pre: cierto */
  /* Post: el resultado es la longitud m�xima de una lista permitida por la
     implementaci�n */
  
  int longitud() const;
  /* Pre: cierto */
  /* Post: el n�mero de palabras diferentes almacenadas en el par�metro impl�cito */

  /* Escritura */  

  void escribir() const;
  /* Pre: cierto */
  /* Post: por el canal est�ndar de salida se ha escrito cada palabra del
     par�metro impl�cito y su frecuencia separadas por un espacio en blanco,
     un par palabra-frecuencia por l�nea, en el orden que las palabras saldr�an
     en un diccionario */
};

#endif
