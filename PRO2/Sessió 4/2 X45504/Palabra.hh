#ifndef PALABRA_HH
#define PALABRA_HH

#include "utils.PRO2"
#include <vector>

class Palabra {

  // Tipo de módulo: datos 
  // Descripción del tipo: una secuencia indexada y acotada de caracteres, 
  // escogidos entre a..z, A..Z y 0..9.  El resto se consideran separadores. 

private:
  static const int MAXLONG = 20;
  vector<char> letras; 
  int longitud;
  /* Invariante de la representacion:
       - 0 <= longitud <= letras.size() = MAXLONG
       - letras[0..longitud] no son separadores
  */

public:
   /* Constructoras */ 
  Palabra ();
  /* Pre: cert */ 
  /* Post: el resultado es una palabra sin caracteres y longitud 0 */

  /* Modificadoras */
  void anadir_letra (char c);
  /* Pre: c no es un separador; la longitud del parametro implícito es menor 
     que la máxima permitida */
  /* Post: El parametro implícito queda como el original pero con c añadido 
     al final */

  /* Consultoras  */
  static int longitud_maxima ();
  /* Pre: cierto */ 
  /* Post: El resultado es la longitud máxima permitida para la clase */
 
  int long_pal () const;
  /* Pre: cierto */ 
  /* Post: El resultado es la longitud del parámetro implícito */
 
  static bool es_separador (char c);  
  /* Pre: cierto */ 
  /* Post: El resultado indica si c es un separador para la clase (c no puede 
     formar parte de una palabra) */

  char consultar_letra (int i) const;
  /* Pre: i está entre 1 y la longitud del parametro implícito */ 
  /* Post: El resultado es el caracter i-ésimo del parametro implícito */

  bool iguales (const Palabra & p) const;
  /* Pre: cierto */
  /* Post: El resultado indica si p es igual al parametro implícito */

  bool menor_igual (const Palabra & p) const;
  /* Pre: cierto */
  /* Post: El resultado indica si el parametro implícito es menor o igual
     que p en orden alfabético */

  /* Lectura y escritura */
 
  void leer (char marca);
  /* Pre: En el canal standard de entrada hay uno o más caracteres a..z A..Z 
     0..9 o "marca"; "marca" es un separador visible del rango (0-127) */
  /* Post: El parámetro implícito contiene el primer grupo de caracteres 
     válidos leídos del canal standard de entrada, hasta el primer separador 
     posterior a éstos; si antes del primer carácter válido aparece "marca", 
     se obtiene una palabra de longitud cero. */

  void escribir () const;
  /* Pre: cierto */
  /* Post: Se han escrito los caracteres del parámetro implícito en el canal
     standard de salida */

};

#endif
