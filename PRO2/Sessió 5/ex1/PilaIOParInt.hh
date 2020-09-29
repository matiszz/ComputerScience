#ifndef PILA_IO_INT
#define PILA_IO_INT

#include <iostream>
#include <stack>
#include "ParInt.hh"

using namespace std;

void llegirPilaParInt(stack<ParInt>& p);
// Pre: cert
// Post: s’apilen el elements llegits a la pila p



void escriurePilaParInt(stack<ParInt> p);
// Pre: cert
// Post: s’escriuen el elements de la pila p i p queda buida 

#endif
