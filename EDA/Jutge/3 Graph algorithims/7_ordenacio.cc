/*
 * Created by Matias Szarfer - 2016
 * 
 * Donades n tasques i m precedències, seguit de m parells xy
 */

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

typedef vector< vector<int> > Grafo;

void leer(Grafo& G, int m) {
    
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }
}

list<int> topological_sort(Grafo& G) {
    
    int n = G.size();
    
    // Crea un vector con las entradas de cada nodo del grafo.
    vector<int> ent(n, 0); // Contiene las entradas de cada nodo.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < G[i].size(); ++j) {
            ++ent[G[i][j]];
        }
    }
    
    // Prepara la cola, donde va agregando todos
    // los nodos que no tienen entradas.
    priority_queue<int, vector<int>, greater<int> > S;
    
    for (int i = 0; i < n; ++i) {
        if (ent[i] == 0) S.push(i);
    }
    
    // Bucle principal, que ordena en una lista topologicamente los nodos.
    list<int> L;
    while (not S.empty()) {
        
        int u = S.top(); // Agarra el primer elemento de la cola, que
        S.pop();         // no tiene entradas, y lo pone en la lista.
        L.push_back(u);
        
        for (int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i];               // Siguiente nodo.
            if (--ent[v] == 0) S.push(v);  // Si u es su única entrada, lo
        }                                  // pone en la pila.
    }
    
    return L;
}

void imprimir_lista(list<int>& L) {
    
    bool primero = true;
    list<int>::iterator it;
    for (it = L.begin(); it != L.end(); ++it) {
        if (primero) {
            primero = false;
            cout << *it;
        }
        else cout << ' ' << *it;
    }
    cout << endl;
}

int main() {
	
    int n, m;
    while (cin >> n >> m) {
        Grafo G(n);
        leer(G, m);
        
        list<int> L;
        L = topological_sort(G);
        
        imprimir_lista(L);
    }
}

