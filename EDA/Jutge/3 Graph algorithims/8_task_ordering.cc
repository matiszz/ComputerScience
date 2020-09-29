/*
 * Created by Matias Szarfer - 2016
 * 
 * Dados n, seguido de n palabras.
 * Dependencias m, seguido de m pares xy.
 * 
 * Imprimir el string lexic. más pequeño posbile,
 * o "NO VALID ORDERING" en su defecto.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map>
using namespace std;

typedef vector< vector<int> > Grafo;
typedef map<string, int> Map;

void leer(Grafo& G, Map& M, int n, int& m) {
    
    int i = 0;
    for (int j = 0; j < n; ++j) { // Leemos todas las palabras
        string pal;
        cin >> pal;
        
        M[pal] = i;
        ++i;
    }
    
    cin >> m;
    for (int j = 0; j < m; ++j) {
        string pal1, pal2;
        cin >> pal1 >> pal2;
        
        int p1 = M[pal1];
        int p2 = M[pal2];
        G[p1].push_back(p2);
    }
}

map<string, int>::iterator mi_busqueda(int n, Map& M) {
    
    map<string, int>::iterator it;
    for (it = M.begin(); it != M.end(); ++it) {
        if (it->second == n) return it;
    }
    return it;
}

void imprimir(list<int>& L, Map& M) {
    
    list<int>::iterator it;
    for (it = L.begin(); it != L.end(); ++it) {
        map<string, int>::iterator mt;
        
        int aux = *it;
        mt = mi_busqueda(aux, M);
        
        cout << mt->first;
    }
    cout << endl;
}

list<int> topological_sort(Grafo& G) {
    
    int n = G.size();
    
    // Vector de apuntados
    vector<int> apunt(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < G[i].size(); ++j) {
            ++apunt[G[i][j]];
        }
    }
    
    // Pila o cola de no apuntados.
    priority_queue<int, vector<int>, greater<int> > Q;
    for (int i = 0; i < n; ++i) {
        if (apunt[i] == 0) Q.push(i);
    }
    
    // Bucle principal
    list<int> L;
    while (not Q.empty()) {
        
        int a = Q.top();
        Q.pop();
        L.push_back(a);
        
        for (int i = 0; i < G[a].size(); ++i) {
            int b = G[a][i];
            if (--apunt[b] == 0) Q.push(b);
        }
    }
    
    return L;
}

bool existe(int a, int b, Grafo& G) {
    
    for (int i = 0; i < G[a].size(); ++i) {
        if (G[a][i] == b) return true;
    }
    return false;
}

bool puedeAcabar(Grafo& G) {

    int n = G.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < G[i].size(); ++j) {
            int a = G[i][j];
            int b = i;
            if (existe(a, b, G)) return false;
        }
    }
    return true;
}

int main() {
	
    int n;
    while (cin >> n) {
        Grafo G(n);
        Map M;
        int m;
        
        leer(G, M, n, m);
        
        if (puedeAcabar(G)) {
            list<int> L = topological_sort(G);
            imprimir(L, M);
        } else 
            cout << "NO VALID ORDERING" << endl;
    }
}

