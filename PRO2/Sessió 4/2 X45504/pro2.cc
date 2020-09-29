#include "ListaPalabras.hh"

int main() {
  ListaPalabras lista;
  int op = readint();
  while (op!= -5){
    Palabra pal; 
    int l; 
    switch(op){ 
    case -1:  // anadir
      pal.leer('.'); 
      lista.anadir_palabra(pal);
      break;
    case -2:  // borrar
      pal.leer('.'); 
      lista.borrar_palabra(pal);
      break;
    case -3: // frec_media_long
      l = readint();  // lee longitud  
      cout << endl << "La frecuencia media de longitud " << l << 
           " es: " << lista.frec_media_long(l) << endl;
      break;
    case -4: // escribir_lista 
      cout << endl << "La lista es: " << endl;
      lista.escribir();
      break;    
    }
    op = readint();
  }
}
