#include <iostream>
#include <vector>
using namespace std;

struct Rectangle { int x_esq, x_dre, y_baix, y_dalt; };


void llegeix(Rectangle& r) {
	cin >> r.x_esq >> r.x_dre >> r.y_baix >> r.y_dalt;
}


int relacio(const Rectangle& act, const Rectangle& next) {
	if (act.x_esq  == next.x_esq  and act.x_dre   == next.x_dre  and act.y_baix  == next.y_baix and act.y_dalt  == next.y_dalt) return 4;
	if (next.x_esq <= act.x_esq   and next.x_dre  >= act.x_dre   and next.y_baix <= act.y_baix  and next.y_dalt >= act.y_dalt)  return 1;
	if (act.x_esq  <= next.x_esq  and act.x_dre   >= next.x_dre  and act.y_baix  <= next.y_baix and act.y_dalt  >= next.y_dalt) return 2;
	if (act.y_baix >= next.y_dalt or  next.y_baix >= act. y_dalt or  act.x_esq   >= next.x_dre  or  next.x_esq  >= act.x_dre)   return 0;
	else return 3;
}


int main() {
	int n;
	while (cin >> n and n!=0) {
		Rectangle act, next;
		llegeix(next);
		--n;
		bool interseccio = true;
		
		while (interseccio and n != 0) {
			act.x_esq = next.x_esq;
			act.x_dre = next.x_dre;
			act.y_baix = next.y_baix;
			act.y_dalt = next.y_dalt;
			llegeix(next);
			
			if (relacio(act, next) == 0) interseccio = false;
			else if (relacio(act, next) == 1) {
				
				next.x_esq = act.x_esq;
				next.x_dre = act.x_dre;
				next.y_dalt = act.y_dalt;
				next.y_baix = act.y_baix;
			
			} else if (relacio(act, next) == 3) {
				
				if (act.x_esq > next.x_esq) next.x_esq = act.x_esq;
				if (act.x_dre < next.x_dre) next.x_dre = act.x_dre;
				if (act.y_baix > next.y_baix) next.y_baix = act.y_baix;
				if (act.y_dalt < next.y_dalt) next.y_dalt = act.y_dalt;
			
			}
			--n;
		}
		
		if (not interseccio) {
			
			cout << "interseccio buida" << endl;
			while (n != 0) {
				llegeix(next);
				--n;
			}
			
		} else cout << "punt inferior esquerre = (" << next.x_esq << ", " << next.y_baix << "); punt superior dret = (" << next.x_dre << ", " << next.y_dalt << ")" << endl;
	}
}
