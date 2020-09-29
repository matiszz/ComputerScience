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

  static const int MAXNUMPAL = 20; // longitud máxima permitida
  int nparaules; // número de palabras de la lista, 
                 // la lista está formada por las posiciones de 0 a nparaules-1

  vector<palfrec> paraules; // vector de palabras y frecuencias
  
  vector<int> npar_long; // número de palabras distintas de cada longitud 
  vector<int> suma_frec_long; // suma de frecuencias de las palabras
                              // de cada longitud  
  
  /* 
     Invariante de la representación: 
     - los campos par de paraules[0..nparaules-1] no pueden tener palabras repetidas en posiciones distintas ni palabras vacías
     - los campos freq de paraules[0..nparaules-1] han de ser mayor que 0
     - 0 <= nparaules <= Palabra::longitud_maxima() = MAXNUMPAL    
     - npar_long[l - 1] = número de palabras distintas de longitud l en paraules[0..nparaules-1] para 1 <= l <= Palabra::longitud_maxima()
     - sum_freq_long[l-1] = suma de las frecuencias de las palabras de longitud l en paraules[0..nparaules-1] para 1 <= l <= Palabra::longitud_maxima()  
  */
   
  static bool comp(const palfrec& p1, const palfrec& p2);
  /* Pre: cierto */
  /* Post: el resultado indica si la palabra de p1 es menor que la de p2
     (saldría antes en un diccionario) */

  void buscar_palabra_posicion(const Palabra & p, bool & b, int & i) const;
  /* Pre: cierto */
  /* Post: b indica si p está en el parámetro implícito;
     si b entonces i es la posición en la que está p; si no, i es la 
     longitud del parámetro implícito */ 
  
public:

  /* Constructoras */

  ListaPalabras ();
  /* Pre: cierto */
  /* Post: el resultado es una lista vacía, que puede contener palabras y sus
     respectivas frecuencias */
  
  /* Modificadoras */

  void anadir_palabra(const Palabra & p);
  /* Pre: el número de palabras en el parámetro implícito es menor que la 
     longitud máxima o p ya está en él; p no es la palabra vacía */
  /* Post: si p estaba en el parámetro implícito original, su frecuencia se ha
     incrementado en 1; si no, p pasa a estar en él, con frecuencia 1 */

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
     longitud l en el parámetro implícito (cero si no hay ninguna) */

  static int longitud_maxima();
  /* Pre: cierto */
  /* Post: el resultado es la longitud máxima de una lista permitida por la
     implementación */
  
  int longitud() const;
  /* Pre: cierto */
  /* Post: el número de palabras diferentes almacenadas en el parámetro implícito */

  /* Escritura */  

  void escribir() const;
  /* Pre: cierto */
  /* Post: por el canal estándar de salida se ha escrito cada palabra del
     parámetro implícito y su frecuencia separadas por un espacio en blanco,
     un par palabra-frecuencia por línea, en el orden que las palabras saldrían
     en un diccionario */
};

#endif
