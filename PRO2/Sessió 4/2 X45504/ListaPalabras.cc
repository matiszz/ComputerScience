#include "ListaPalabras.hh"
#include <algorithm>

ListaPalabras::ListaPalabras() {
  paraules = vector<palfrec>(MAXNUMPAL);
  nparaules = 0;
  npar_long = vector<int>(Palabra::longitud_maxima(), 0);
  suma_frec_long = vector<int>(Palabra::longitud_maxima(), 0);
}

int ListaPalabras::longitud_maxima() {
  return MAXNUMPAL;
}

int ListaPalabras::longitud() const {
  return nparaules;
}

double ListaPalabras::frec_media_long(int l) const {
  if (npar_long[l - 1] == 0)
    return 0;
  else
    return double(suma_frec_long[l - 1])/npar_long[l - 1];
}

bool ListaPalabras::comp(const palfrec& p1, const palfrec& p2) {
  return p1.par.menor_igual(p2.par);
}

void ListaPalabras::escribir() const {
  vector<palfrec> palaux(paraules);
  sort(palaux.begin(), palaux.begin() + nparaules, comp);
  for(int i = 0; i < nparaules; ++i) {
    palaux[i].par.escribir();
    cout << " " << palaux[i].freq << endl;
  }
}

