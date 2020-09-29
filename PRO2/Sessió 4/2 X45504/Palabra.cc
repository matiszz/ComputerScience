#include "Palabra.hh"

/*
 * Implementacion de la clase Palabra
 */

/* 
   Sólo pueden estar en una palabra los caracteres a..z A..Z 0..9
   El resto se consideran separadores.

   Sólo son relevantes las letras del vector situadas en las
   posiciones 0..longitud-1; las demás no se pueden visitar salvo
   para ocuparlas, aumentando por tanto la longitud.

   Las operaciones de lectura requieren un parámetro que se usará para
   distinguir un separador especial, que sirva por ejemplo para marcar el
   final de un texto. Dicho separador especial puede ser cualquier
   caracter ASCII del rango 0-127, "visible" y distinto de "a".."z",
   "A".."Z" y "0".."9", como "$", "." o "+" (pero no el blanco, el salto
   de línea o el tabulador, por no ser visibles, o "ç", "ñ", etc., por no
   ser del rango 0-127).
*/


/* Constructoras */
Palabra::Palabra ()
{
  letras = vector<char> (MAXLONG);
  longitud = 0; 
}

/* Privada para filtrar los caracteres no válidos */ 
bool Palabra::es_separador (char c)
{ 
  return (not(((47 < c) and (c < 58)) or	//numeros
	      ((64 < c) and (c < 91)) or	//mayusculas
	      ((96 < c) and (c < 123))));	//minusculas
}


/* Modificadoras de los campos */

void Palabra::anadir_letra (char c)
{
  if (longitud >= MAXLONG)
    throw PRO2Excepcio ("Palabra demasiado larga");
  if (es_separador (c)  ){ cout << c << " no es un caracter valido" << endl;
    throw PRO2Excepcio ("Has intentado anadir un caracter no valido");
  }
  letras[longitud] = c;
  longitud++;
}


/* Consultoras de los campos */
int Palabra::longitud_maxima ()
{
  return MAXLONG;
}

int Palabra::long_pal () const
{
  return longitud;
}

char Palabra::consultar_letra (int i) const
{
  i--;
  if (i < 0)
    throw PRO2Excepcio ("Posicion negativa o cero");
  if (i >= longitud)
    throw PRO2Excepcio ("Posicion mayor que la longitud");
  
  return letras[i];
}


bool Palabra::iguales (const Palabra & p) const
{
  bool b;
  if (this->longitud != p.longitud) b = false;   
  else
    {
      b = true;
      int i = 0;
      while (b and i < this->longitud)
	{
	  b = letras[i] == p.letras[i];
	  i++;
	}
    }
  return b;
}

bool Palabra::menor_igual (const Palabra & p) const
{
  bool b=true; char a,a2;
  int i =0; int m=longitud;
  if (longitud > p.longitud) m = p.longitud;
  while (i<m and b){
    a = letras[i];
    a2 = p.letras[i];
    b=(a==a2);
    if (b)  i++;
  }
  // si sale por b=false, el resultado depende de los cars. a y a2
  // si no, el resultado depende de las longitudes
  bool menor;
  if (not b) menor = (a<a2);
  else menor = (m == longitud);
  return menor;
}

/* Entrada / Salida */

void saltar_separador (char m)
// para al llegar al primer no separador o a la marca
{
  while (Palabra::es_separador (cin.peek ()) and cin.peek ()!=m)	// and (cin.peek () != EOF)) //Para secuencias sin palabra final
    { 
      cin.ignore ();
    }
}


void Palabra::leer (char marca)
{
  if (not (((marca>=33)and (marca <= 47)) // de ! a /
	   or ((marca>=58)and (marca <= 64)) // de : a @
	   or ((marca>=91)and (marca <= 96)) // de [ a `
	   or ((marca>=123)and (marca <= 126)))) // de { a ~
    throw PRO2Excepcio ("Marca no valida");

  //Navega hasta a la siguinte palabra o la marca
  saltar_separador (marca);

  //iniciem la paraula
  longitud = 0;

  if  (cin.peek()== marca) cin.ignore();
  else { 
    // leemos los caracteres
    while (not es_separador (cin.peek ())) // and (cin.peek () != EOF))//Para secuencias sin palabra final
      {
	if (longitud >= MAXLONG)
	  throw PRO2Excepcio ("Palabra demasiado larga");
     
	letras[longitud] = readchar ();
	longitud++;
      }
  }
}


void Palabra::escribir() const
{
  for (int i = 0; i < longitud; i++)
    cout << letras[i];
}
