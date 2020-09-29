/*
 * Created by Matias Szarfer - 2016
 * 
 * Dado n, seguido de n consonantes y n vocales en
 * orden alfabético,
 * Dar una lista de palabras tal que:
 *      - Todas empiezan con consonante.
 *      - Alternan consonantes y vocales.
 *      - Cada letra aparece una sola vez.
 *      - 'y' es vocal
 */

#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> vecCha;
typedef vector<bool> vecBol;

int n;
vecCha pal, cons, voc;
vecBol conLoc, vocLoc;

void escribir() {
    for (int i = 0; i < n*2; ++i) cout << pal[i];
    cout << endl;
}

void hablar(int i) {
    int let = cons.size();
    
    if (i == let) escribir();
    else {
        for (int j = 0; j < let; ++j) {
            if (not conLoc[j]) {
                conLoc[j] = true;
                pal[i*2] = cons[j];
                
                for (int k = 0; k < let; ++k) {
                    if (not vocLoc[k]) {
                        vocLoc[k] = true;
                        pal[i*2 + 1] = voc[k];
                        hablar(i+1);
                        vocLoc[k] = false;
                    }
                }
                conLoc[j] = false;
            }
        }
    }
}

int main() {
	cin >> n;
    
    cons = voc = vecCha(n);
    conLoc = vocLoc = vecBol(n, false);
    
    for (int i = 0; i < n; ++i) cin >> cons[i];
    for (int i = 0; i < n; ++i) cin >> voc[i];
    
    pal = vecCha(2*n);
    
    hablar(0);
}
